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
// n: dfn�� low�� ��, pos: stack �ε���, id: ��������Ʈ �ε���, len: buf�� ũ�� 
int n, pos = 0, id = -1, len = 0; 
int buf[MAX]; // biconnected components ������ array
//�ʱ�ȭ �Լ�
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
				return i; //�̸��� �����ϴ� ��������Ʈ �ε��� ����
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
			if (nameToInt(ptr) == graph[nameToInt(ptr)]->vertex) { // �ε����� �Ǻ�
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
					if (cnt == 0) { //ex. (4, 5) �� �� ����
						buf[len++] = x = pop();
						buf[len++] = y = pop();
					}
					else { //ex. (3, 1) (4, 3), (2, 4), (1, 2)=>3, 4, 2, 1 ����
						buf[len++] = x = pop();
						y = pop();
					}
					cnt++;
				} while (!((x == u) && (y == w)));	
				buf[len++] = -1; // components ���� ����: -1
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
	int temp[100], cur= 0; // �ߺ����� data���� ���� temp array ��� , cur: temp �ε���
	for (i = 0; i < len; i++) // buf ����Ž��
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
						if (temp[j] == num) { // �ߺ��� data ����
							break;
						}
						else if (j == cur) { //�ߺ��� data ����
							temp[cur++] = num;
							break;
						}
					}
				}
			}
			start = end + 1;
		}
		else if (buf[i] == -1) { // biconnected components �׷쿡 n�� ���� ���
			start = i + 1;
		}
	}
	for (j = 0; j < cur; j++)
	{
		printf("%s ", graph[temp[j]]->name);
	}
	printf("\n");
}

void release(int num) { //�� �ٸ� �Է��� ���� �ʱ�ȭ
	for (int i = 0; i < num; i++)
	{
		free(graph[i]);
	}
}

int main() {
	int num = 0, input = 0, count =0;
	char *name = (char*)malloc(sizeof(char) * 100);
	do {
		printf("1: �Է� 2: �˻� 3: ����\n");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			if (count > 0) {
				release(num);
				id = -1;
			}
			printf("���� ���� �Է� :\n");
			scanf("%d", &num);
			getchar();
			dfn = (int*)malloc(sizeof(int)*num);
			low = (int*)malloc(sizeof(int)*num);
			printf("���� �̸� �Է� :\n");
			gets(name);
			int cnt = 0;
			char *ptr = strtok(name, " ");
			while (ptr != NULL) {
				graph[cnt++] = createNode(nameToInt(ptr), ptr);
				ptr = strtok(NULL, " ");
			}
			printf("���� �̸� �Է� ����. �� %d���� ����\n", num);
			printf("���� �� ���� �Է�, �����Ϸ��� \".\"�Է�\n");
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
			printf("%s �� biconnected ������ ����\n", name);
			printBicon(name);
			break;
		case 3:
		default:
			printf("����Ǿ����ϴ�.\n");
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