#pragma disable(warning: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

typedef struct __node {
	int data;
	struct __node * link;
}Node;

/*노드 생성*/
Node *createnode() {
	Node *p;
	p = (Node*)malloc(sizeof(Node));
	p->link = NULL;
	return p;
}

/*내림차순으로 삽입*/
void insertReverseOrder(Node *node, int data) {
	Node *newnode = createnode();
	Node *curnode = node;
	if (node->link == NULL) { // 노드 없을 때 
		newnode->link = node->link;
		newnode->data = data;
		node->link = newnode;
		return;
	}
	while (curnode != NULL) { // 헤더부터 끝까지 확인
		if (curnode->data < data) { 
			if (curnode->link == NULL) { // 다음 노드가 비어있을 때 바로 삽입
				newnode->link = NULL;
				newnode->data = data;
				curnode->link = newnode;
				break;
			}
			else if (curnode->link->data < data) {  // 현재 노드의 값이 data보다 작은 경우 삽입
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
/*노드 삭제*/
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

int searchnode(Node *h, int data) { /*노드 탐색 : 삭제 삽입 시 사용*/
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
	return -1; // 찾지 못 함
}

/*역순*/
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
		printf("리스트가 비어있습니다.\n");
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
		printf("1: 추가, 2: 삭제, 3: 출력, 4: 역순 출력, 5: 종료\n");
		scanf("%d", &input);
		getchar();
		switch (input) {
		case 1:
			printf("\"입력\" ");
			scanf("%d", &num);
			getchar();
			if (searchnode(h, num) != -1) {
				printf("중복된 데이터입니다.\n");
			}
			else {
				insertReverseOrder(h, num);
				printf("성공했습니다.\n");
			}
			break;
		case 2:
			printf("\"삭제\" ");
			scanf("%d", &num);
			getchar();
			if (searchnode(h, num) != -1) {
				deletenode(h, num);
				printf("성공했습니다.\n");
			}
			else {
				printf("찾는 값이 없습니다.\n");
			}
			break;
		case 3:
			printf("\"출력\" ");
			printnode(h);
			break;
		case 4:
			reverse(h);
			printf("\"역순 출력\" ");
			printnode(h);
			reverse(h); // 원래대로 되돌리기
			break;
		}
	} while (input != 5);

	system("pause");
	return 0;
}