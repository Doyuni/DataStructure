#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#define MAX_VERTICES 100

typedef struct element{
	int vertex;
	char name[20];
} element;
typedef struct element *ePointer;
ePointer city[MAX_VERTICES];
int id = -1;
int distance[MAX_VERTICES]; // start vertex ~ other vertex path
int pi[MAX_VERTICES]; // predecessor index
int found[MAX_VERTICES]; // the shortest path 인지 확인용도
int adj_matrix[MAX_VERTICES][MAX_VERTICES]; //인접행렬

void intValue(int num) {
	for (int i = 0; i < num; ++i) {
		for (int j = 0; j < num; ++j) {
			adj_matrix[i][j] = 1000;
		}
	}
}

ePointer createData(int v, char *name) {
	ePointer e = (ePointer*)malloc(sizeof(element));
	e->vertex = v;
	strcpy(e->name, name);
	return e;
}

int nameToInt(char *name) {
	id++;
	for (int i = 0; i < id; ++i) {
		if (city[i] != NULL) {
			if (strcmp(city[i]->name, name) == 0) {
				id--;
				return i; //이름과 상응하는 인접리스트 인덱스 리턴
			}
		}
	}
	return id;
}

//경로를 확인하지 않은 것 중 distance 최소 값의 인덱스
int choose(int num) { 
	int min = 1000;
	int index = -1;
	for (int i = 0; i < num; ++i) {
		if (min > distance[i] && !found[i]) {
			min = distance[i];
			index = i;
		}
	}
	return index;
}

void shortestPath(int source, int num) {
	//initialize values
	int i, j;
	found[source] = 1;
	for (i = 0; i < num; ++i) {
		distance[i] = adj_matrix[source][i];
		pi[i] = source; // 시작 vertex로 돌아와야 하니 기본 값은 모두 시작 vertex의 인덱스 값이다.
	}
	distance[source] = 0;
	//function
	for (i = 0; i < num - 2; ++i) {
		int min = choose(num);
		found[min] = 1;
		for (j = 0; j < num; ++j) {
			if (!found[j] && adj_matrix[min][j] != 1000 && distance[j] > distance[min] + adj_matrix[min][j]) {
				distance[j] = distance[min] + adj_matrix[min][j];
				pi[j] = min;
			}
		}
	}
}

void printShortestPath(int source, int dest) {
	int temp = pi[dest];
	if (source == dest) {
		printf("%s ", city[dest]->name);
		return;
	}
	printShortestPath(source, temp);
	printf("%s ", city[dest]->name);
}

int main() {
	int num;
	printf("그래프 입력\n");
	printf("Insert City Count : ");
	scanf("%d", &num);
	getchar();
	char *name = (char *)malloc(sizeof(char) * num);
	char *input = (char *)malloc(sizeof(char) * 20 * 3);
	char *ptr;
	printf("Insert City Names : ");
	gets(name);
	ptr = strtok(name, " ");
	int cnt = 0;
	while (ptr != NULL) {
		city[cnt++] = createData(nameToInt(ptr), ptr);
		ptr = strtok(NULL, " ");
	}
	intValue(num);
	printf("도시간 연결 입력, 종료하려면 \".\" 입력\n");
	do {
		gets(input);
		if (input[0] == '.') break;
		ptr = strtok(input, "-");
		int v = nameToInt(ptr);
		ptr = strtok(NULL, " ");
		int u = nameToInt(ptr);
		ptr = strtok(NULL, " ");
		int cost = atoi(ptr);
		adj_matrix[v][u] = cost;
		adj_matrix[u][v] = cost;
	} while (input[0] != '.');
	printf("최단 거리 기준 도시 입력:\n");
	char city_name[20];
	scanf("%s", city_name);
	int source = nameToInt(city_name);
	shortestPath(source, num);
	for (int i = 0; i < num; ++i) {
		if (i != source) {
			printf("%s : %d ", city[i]->name, distance[i]);
			printShortestPath(source, i);
			printf("\n");
		}
	}
	system("pause");
	//free(name)과 free(input)을 쓰면 error, why?
	return 0;
}
