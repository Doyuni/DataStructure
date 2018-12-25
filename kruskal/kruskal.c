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
int count[MAX_ELEMENTS]; // ������ ��� ����
int heap_size = 0;
int MST_size = 0;

void init() {
	for (int i = 0; i < MAX_ELEMENTS; i++)
	{
		connectedSet[i] = -1;
		count[i] = 1; // �ڽ� �����ؼ� 1���� ī��Ʈ�ϱ⿡ 1�� �ʱ�ȭ
	}
}
void insertMinEdgeHeap(edge edgeMinHeap[], edge newEdge, int *numberOfEdges) {
	int i = ++(*numberOfEdges); // 1���� ä������ �ϹǷ�
	while (i != 1 && newEdge.cost < edgeMinHeap[i / 2].cost) { // ��Ʈ��� x, �θ��庸�� cost�� ���� ������ Ž��
		edgeMinHeap[i] = edgeMinHeap[i / 2]; // ���� �θ��尡 �ڽĳ��� ��
		i /= 2;
	}
	edgeMinHeap[i] = newEdge;
}

edge deleteMinEdgeHeap(edge edgeMinHeap[], int *numberOfEdges) {
	int parent = 1, child = 2;
	edge deleted_data, temp;
	deleted_data = edgeMinHeap[parent]; // ������ ���
	temp = edgeMinHeap[(*numberOfEdges)--];
	while (child <= *numberOfEdges) {
		if ((child < *numberOfEdges) && (edgeMinHeap[child].cost > edgeMinHeap[child + 1].cost)) child++; // ���� ��庸�� ũ�� �� ��� �����ɷ� ��ü
		if (temp.cost <= edgeMinHeap[child].cost) break; //���� ū cost�� �Ǹ� ����
		edgeMinHeap[parent] = edgeMinHeap[child]; // �� ����� �ڽ� ��� Ž���� ���� �� ����� �θ� ��尡 ��
		parent = child;
		child *= 2; // ���� �ڽ� ���� ��
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
	while (edgeCount < n) // edge�� ������ n-1�� �� �� ���� �ݺ�
	{
		e = deleteMinEdgeHeap(heap, &heap_size); // �ּ� ��� ����
		if (doesItMakeCycle(e, connectedSet, MST)) { // cycle ������ edge �߰�
			addEdge(e, MST, connectedSet);
			edgeCount++;
		}
	}
	for (int i = 0; i < MST_size; i++)
	{
		printf("(%d, %d)", MST[i].v, MST[i].u);
		costSum += MST[i].cost;
	}
	printf(" �� ���: %d\n", costSum);
}

int main() {
	int num;
	char *input = (char*)malloc(sizeof(char) * 20);
	printf("�� ���� ��带 �Է��Ͻðڽ��ϱ�?\n");
	scanf("%d", &num);
	getchar();
	printf("���۵��ÿ� �����ÿ� ����ġ�� �Է��Ͻÿ�(.���� ����)\n");
	int cnt = 0;
	do {
		edge newEdge = { -1,-1,-1 }; // ����ü ���� �ʱ�ȭ
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
