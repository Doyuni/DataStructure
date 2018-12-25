#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#define MAX_ELEMENTS 200

typedef struct {
	int v;
	int u;
	int cost;
} edge;

edge heap[MAX_ELEMENTS];
edge MST[MAX_ELEMENTS];
int connectedSet[MAX_ELEMENTS];
int count[MAX_ELEMENTS]; // 집합의 노드 개수
int heap_size = 0;
int MST_size = 0;

void init() {
	for (int i = 0; i < MAX_ELEMENTS; i++)
	{
		connectedSet[i] = -1;
		count[i] = 1; // 자신 포함해서 1개로 카운트하기에 1로 초기화
	}
}
void insertMinEdgeHeap(edge edgeMinHeap[], edge newEdge, int *numberOfEdges) {
	int i = ++(*numberOfEdges); // 1부터 채워가야 하므로
	while (i != 1 && newEdge.cost < edgeMinHeap[i / 2].cost) { // 루트노드 x, 부모노드보다 cost가 작을 떄까지 탐색
		edgeMinHeap[i] = edgeMinHeap[i / 2]; // 원래 부모노드가 자식노드로 감
		i /= 2;
	}
	edgeMinHeap[i] = newEdge;
}

edge deleteMinEdgeHeap(edge edgeMinHeap[], int *numberOfEdges) {
	int parent = 1, child = 2;
	edge deleted_data, temp;
	deleted_data = edgeMinHeap[parent]; // 삭제될 대상
	temp = edgeMinHeap[(*numberOfEdges)--];
	while (child <= *numberOfEdges) {
		if ((child < *numberOfEdges) && (edgeMinHeap[child].cost > edgeMinHeap[child + 1].cost)) child++; // 형제 노드보다 크면 비교 대상 작은걸로 교체
		if (temp.cost <= edgeMinHeap[child].cost) break; //제일 큰 cost가 되면 종료
		edgeMinHeap[parent] = edgeMinHeap[child]; // 비교 대상의 자식 노드 탐색을 위해 비교 대상이 부모 노드가 됨
		parent = child;
		child *= 2; // 다음 자식 노드와 비교
	}
	edgeMinHeap[parent] = temp;
	return deleted_data;
}

int doesItMakeCycle(edge minCostEdge, int connectedSet[], edge MST[]) {
	int index1 = minCostEdge.v;
	int temp = index1, lead;
	for (; connectedSet[index1] >= 0; index1 = connectedSet[index1]);
	int index2 = minCostEdge.u;
	temp = index2;
	for (; connectedSet[index2] >= 0; index2 = connectedSet[index2]);
	if (index1 == index2) {
		return 0;
	}
	return 1;
}

void addEdge(edge selectedEdge, edge MST[], int connectedSet[]) {
	int v = selectedEdge.v;
	int u = selectedEdge.u;
	MST[MST_size].u = u;
	MST[MST_size].v = v;
	MST[MST_size].cost = selectedEdge.cost;
	MST_size++;
	if (count[v] > count[u]) {
		connectedSet[u] = v;
		count[u] += count[v];
	}
	else {
		connectedSet[v] = u;
		count[v] += count[u];
	}
}

void kruskal(int n) {
	edge e;
	int edgeCount = 0, costSum = 0;
	init();
	while (edgeCount < n) // edge의 개수가 n-1이 될 때 까지 반복
	{
		e = deleteMinEdgeHeap(heap, &heap_size); // 최소 비용 간선
		if (doesItMakeCycle(e, connectedSet, MST)) { // cycle 없으면 edge 추가
			addEdge(e, MST, connectedSet);
			edgeCount++;
		}
	}
	for (int i = 0; i < MST_size; i++)
	{
		printf("(%d, %d)", MST[i].v, MST[i].u);
		costSum += MST[i].cost;
	}
	printf(" 총 비용: %d\n", costSum);
}

int main() {
	int num;
	char *input = (char*)malloc(sizeof(char) * 20);
	printf("몇 개의 노드를 입력하시겠습니까?\n");
	scanf("%d", &num);
	getchar();
	printf("시작도시와 끝도시와 가중치를 입력하시오(.으로 종료)\n");
	int cnt = 0;
	do {
		edge newEdge = { -1,-1,-1 }; // 구조체 변수 초기화
		gets(input);
		if (input[0] != '.') {
			char *ptr = strtok(input, " ");
			int cnt = 0;
			while (ptr != NULL && cnt < 3) {
				if (cnt == 0) {
					newEdge.v = atoi(ptr);
				}
				else if (cnt == 1) {
					newEdge.u = atoi(ptr);
				}
				else {
					newEdge.cost = atoi(ptr);
				}
				cnt++;
				ptr = strtok(NULL, " ");
			}
			insertMinEdgeHeap(heap, newEdge, &heap_size);
		}
	} while (input[0] != '.');
	kruskal(num - 1);
	system("pause");
	return 0;
}
