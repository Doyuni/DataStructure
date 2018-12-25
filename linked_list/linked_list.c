#pragma disable(warning: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

typedef struct __node {
	int data;
	struct __node * link;
}Node;

/*��� ����*/
Node *createnode() {
	Node *p;
	p = (Node*)malloc(sizeof(Node));
	p->link = NULL;
	return p;
}

/*������������ ����*/
void insertReverseOrder(Node *node, int data) {
	Node *newnode = createnode();
	Node *curnode = node;
	if (node->link == NULL) { // ��� ���� �� 
		newnode->link = node->link;
		newnode->data = data;
		node->link = newnode;
		return;
	}
	while (curnode != NULL) { // ������� ������ Ȯ��
		if (curnode->data < data) { 
			if (curnode->link == NULL) { // ���� ��尡 ������� �� �ٷ� ����
				newnode->link = NULL;
				newnode->data = data;
				curnode->link = newnode;
				break;
			}
			else if (curnode->link->data < data) {  // ���� ����� ���� data���� ���� ��� ����
				newnode->link = curnode->link;
				newnode->data = data;
				curnode->link = newnode;
				break;
			}
		}
		else {  
			newnode->link = curnode->link;
			newnode->data = data;
			curnode->link = newnode;
			break;
		}
		curnode = curnode->link;
	}
}
/*��� ����*/
void deletenode(Node *h, int data) {
	Node *p;
	Node *q;
	q = createnode();
	p = h;

	while (p->link != NULL) {
		q = p;
		p = p->link;
		if (p->data == data) {
			q->link = p->link;
			free(p); 
			break;
		}
	}
}

int searchnode(Node *h, int data) { /*��� Ž�� : ���� ���� �� ���*/
	Node *p;
	p = h;
	int cnt = 0;

	while (p->link != NULL) {
		p = p->link;
		cnt++;
		if (p->data == data) {
			return cnt;
		}
	}
	return -1; // ã�� �� ��
}

/*����*/
void reverse(Node *h) {
	Node *p;
	Node *q;
	Node *r;

	q = NULL;
	r = NULL;
	p = h->link;

	while (p != NULL) {
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	h->link = q;
}

void printnode(Node* h) {
	Node *p;
	p = h;
	if (p->link == NULL) {
		printf("����Ʈ�� ����ֽ��ϴ�.\n");
	}
	else {
		while (p->link != NULL) {
			p = p->link;
			printf("%2d ", p->data);
		}
		printf("\n");
	}
}

int main() {
	Node *h = createnode();
	int num, input;
	do {
		printf("1: �߰�, 2: ����, 3: ���, 4: ���� ���, 5: ����\n");
		scanf("%d", &input);
		getchar();
		switch (input) {
		case 1:
			printf("\"�Է�\" ");
			scanf("%d", &num);
			getchar();
			if (searchnode(h, num) != -1) {
				printf("�ߺ��� �������Դϴ�.\n");
			}
			else {
				insertReverseOrder(h, num);
				printf("�����߽��ϴ�.\n");
			}
			break;
		case 2:
			printf("\"����\" ");
			scanf("%d", &num);
			getchar();
			if (searchnode(h, num) != -1) {
				deletenode(h, num);
				printf("�����߽��ϴ�.\n");
			}
			else {
				printf("ã�� ���� �����ϴ�.\n");
			}
			break;
		case 3:
			printf("\"���\" ");
			printnode(h);
			break;
		case 4:
			reverse(h);
			printf("\"���� ���\" ");
			printnode(h);
			reverse(h); // ������� �ǵ�����
			break;
		}
	} while (input != 5);

	system("pause");
	return 0;
}