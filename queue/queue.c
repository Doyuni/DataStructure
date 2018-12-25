#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

typedef struct {
	int max; //ť�� �뷮
	int num; //���� ��� ��
	int front;
	int rear;
	char **name; //����� ���

} CircularQueue;

//���� ����
void Hospital_Arrive(CircularQueue *q) { 
	char tmp[20]; // ��� �Է� ����
	int input;
	if (q->num == q->max) { // ����� 5���� ��
		printf("Service is not available\n");
	}
	else {
		printf("���� ����� ��: %d\n", q->num);
		printf("����� ����� �Ͻðڽ��ϱ�? 1. Yes 2. No : ");
		scanf("%d", &input);
		getchar();
		if (input == 1){ 
			q->num++; // ��� 1 ����
			q->rear++; // rear 1 ����
			if (q->rear == q->max) { // ���� ť Ư¡(����Ȱ��)
				q->rear = 0;
			}
			printf("����� ����� �Է����ּ���: ");
			scanf("%s", tmp);
			q->name[q->rear] = (char *)malloc(sizeof(tmp + 1) * sizeof(char)); // ���ڿ� ���� NULL�� ����Ͽ� tmp+1�� �����ŭ �����Ҵ�
			strcpy(q->name[q->rear], tmp); // ���ڿ� ����
		} 
	}
	return;
}
//���� �Ϸ�
void Hospital_Complete(CircularQueue *q) {
	if (q->num != 0) { // ��Ұ� 0�� �ƴ� ��� dequeue ����
		q->num--; 
		q->front++;
		if (q->front == q->max) { //���� ť Ư¡(����Ȱ��)
			q->front = 0;
		}
		printf("���� ������ �մ�: %s\n", q->name[q->front]);
	}
	else {
		printf("There is no patient waiting\n");
	}
	return;
}

int main() {
	//ť �ʱ�ȭ
	CircularQueue *q;
	q = (CircularQueue*)malloc(sizeof(CircularQueue));
	q->name = (char**)malloc(sizeof(char*)*5); // 5���� ����� ���� �Ҵ�
	q->num = 0; 
	q->max = 5; // �ִ� ����� �� 5��
	q->front = 0;
	q->rear = 0;
	//�޴�
	int menu;
	do {
		printf("1. ���� ����  2. ���� �Ϸ�  3. ���� ����: ");
		scanf("%d", &menu);
		getchar(); // scanf �Է� �� ���๮�� ó��
		switch (menu)
		{
		case 1:
			Hospital_Arrive(q);
			break;
		case 2:
			Hospital_Complete(q);
			break;
		}
	} while (menu != 3); // ���� ���ᰡ ������ ������ �ݺ�
	system("pause");
	return 0;
}