#pragma disable(warning: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define MAX 100
#define MIN2(x, y) ((x) < (y) ? (x) : (y))

typedef struct node *nodePointer;
typedef struct node {
	int vertex;
	char name[20];
	nodePointer link;
}node;

int visited[MAX];
nodePointer graph[MAX];
int *dfn;
int *low;
int stack[MAX];
// n: dfn과 low의 값, pos: stack 인덱스, id: 인접리스트 인덱스, len: buf의 크기 
int n, pos = 0, id = -1, len = 0; 
int buf[MAX]; // biconnected components 저장할 array
//초기화 함수
void init(int num) {
	for (int i = 0; i < num; ++i) {
		visited[i] = 0;
		stack[i] = -1;
		buf[i] = 0;
		dfn[i] = low[i] = -1;
	}
	n = 0;
	pos = 0;
	len = 0;
}

void push(int u, int v) {
	stack[pos++] = v;
	stack[pos++] = u;
}

int pop() {
	return stack[--pos];
}

nodePointer createNode(int v, char *name) {
	nodePointer newNode = (nodePointer *)malloc(sizeof(node));
	newNode->link = NULL;
	newNode->vertex = v;
	strcpy(newNode->name, name);
	return newNode;
}

int nameToInt(char *name) {
	id++;
	for (int i = 0; i < id; ++i) {
		if (graph[i] != NULL) {
			if (strcmp(graph[i]->name, name) == 0) { 
				id--;
				return i; //이름과 상응하는 인접리스트 인덱스 리턴
			}
		}
	}
	return id;
}

int parseString(char *inputString, char *outputName1, char *outputName2) {
	if (inputString[0] == '.') return 0;
	char *ptr = strtok(inputString, "-");
	int cnt = 0;
	while (ptr != NULL) {
		if (graph[nameToInt(ptr)] != NULL) {
			if (nameToInt(ptr) == graph[nameToInt(ptr)]->vertex) { // 인덱스로 판별
				if (cnt == 0) {
					strcpy(outputName1, ptr);
					cnt++;
				}
				else if (cnt == 1) {
					strcpy(outputName2, ptr);
				}
			}
			else {
				printf("[%s] is not exist in city names\n", ptr);
				return 0;
			}
			ptr = strtok(NULL, " ");
		}
	}
	return 1;
}

void insertList(char *name1, char *name2) {
	nodePointer n1, n2;
	int a = nameToInt(name1);
	int b = nameToInt(name2);
	n1 = createNode(a, name1);
	n2 = createNode(b, name2);
	if (graph[a]->link == NULL) {
		graph[a]->link = n2;
	}
	else {
		nodePointer tail = graph[a];
		while (tail->link != NULL) {
			tail = tail->link;
		}
		tail->link = n2;
	}
	if (graph[b]->link == NULL) {
		graph[b]->link = n1;
	}
	else {
		nodePointer tail = graph[b];
		while (tail->link != NULL) {
			tail = tail->link;
		}
		tail->link = n1;
	}
}

void searchBicon(int u, int v) { //v is parent of u
	nodePointer ptr;
	int w, x, y;
	dfn[u] = low[u] = n++;
	for (ptr = graph[u]; ptr; ptr = ptr->link) {
		w = ptr->vertex;
		if (v != w && dfn[w] < dfn[u]) {
			push(u, w);
		}
		if (dfn[w] < 0) {
			searchBicon(w, u);
			low[u] = MIN2(low[u], low[w]);
			if (low[w] >= dfn[u]) {
				int cnt = 0;
				do {
					if (cnt == 1) {
						len--;
					}
					if (cnt == 0) { //ex. (4, 5) 둘 다 저장
						buf[len++] = x = pop();
						buf[len++] = y = pop();
					}
					else { //ex. (3, 1) (4, 3), (2, 4), (1, 2)=>3, 4, 2, 1 저장
						buf[len++] = x = pop();
						y = pop();
					}
					cnt++;
				} while (!((x == u) && (y == w)));	
				buf[len++] = -1; // components 구분 역할: -1
			}
		}
		else if (w != v) {
			low[u] = MIN2(low[u], dfn[w]);
		}
	}
}

void printBicon(char *city) {
	int n = nameToInt(city);
	int i, j, start = 0, end =0, index = -1;
	int temp[100], cur= 0; // 중복없는 data만을 위해 temp array 사용 , cur: temp 인덱스
	for (i = 0; i < len; i++) // buf 순차탐색
	{
		if (n == buf[i]) {
			index = i;
		}
		if (buf[i] == -1 && index != -1) {
			end = i;
			index = -1;
			for (start; start < end; start++)
			{
				int num = buf[start];
				if (n != num) {
					for (j = 0; j <= cur; j++)
					{
						if (temp[j] == num) { // 중복된 data 존재
							break;
						}
						else if (j == cur) { //중복된 data 없음
							temp[cur++] = num;
							break;
						}
					}
				}
			}
			start = end + 1;
		}
		else if (buf[i] == -1) { // biconnected components 그룹에 n이 없는 경우
			start = i + 1;
		}
	}
	for (j = 0; j < cur; j++)
	{
		printf("%s ", graph[temp[j]]->name);
	}
	printf("\n");
}

void release(int num) { //또 다른 입력을 위해 초기화
	for (int i = 0; i < num; i++)
	{
		free(graph[i]);
	}
}

int main() {
	int num = 0, input = 0, count =0;
	char *name = (char*)malloc(sizeof(char) * 100);
	do {
		printf("1: 입력 2: 검색 3: 종료\n");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			if (count > 0) {
				release(num);
				id = -1;
			}
			printf("도시 개수 입력 :\n");
			scanf("%d", &num);
			getchar();
			dfn = (int*)malloc(sizeof(int)*num);
			low = (int*)malloc(sizeof(int)*num);
			printf("도시 이름 입력 :\n");
			gets(name);
			int cnt = 0;
			char *ptr = strtok(name, " ");
			while (ptr != NULL) {
				graph[cnt++] = createNode(nameToInt(ptr), ptr);
				ptr = strtok(NULL, " ");
			}
			printf("도시 이름 입력 종료. 총 %d개의 도시\n", num);
			printf("도시 간 연결 입력, 종료하려면 \".\"입력\n");
			char *n1 = (char*)malloc(sizeof(char) * 20);
			char *n2 = (char*)malloc(sizeof(char) * 20);
			while (name[0] != '.') {
				gets(name);
				if (parseString(name, n1, n2)&& name[0] != '.') {
					insertList(n1, n2);
				}
			}
			free(n1);
			free(n2);
			count = 1;
			break;
		case 2:
			scanf("%s", name);
			init(num);
			searchBicon(0, -1); 
			printf("%s 과 biconnected 관계인 도시\n", name);
			printBicon(name);
			break;
		case 3:
		default:
			printf("종료되었습니다.\n");
			break;
		}
	} while (input != 3);
	free(name);
	free(dfn);
	free(low);
	release(num);
	system("pause");
	return 0;
}