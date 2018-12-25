#pragma disable(warning: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

typedef struct {
	char name[11];
	char date[9];
	char region[21];
} element;
typedef struct Node *treePointer;
typedef struct Node {
	element data;
	treePointer leftChild;
	treePointer rightChild;
} Node;
int cnt = 0;

treePointer BSTsearch(treePointer root, char *name) {
	treePointer parent = NULL;
	while (root) {
		int cmp = strcmp(name, root->data.name);
		if (cmp == 0 && parent) return parent;
		else if (cmp == 0) return root;
		if (cmp < 0) {
			parent = root;
			root = root->leftChild;
		}
		else {
			parent = root;
			root = root->rightChild;
		}
	}
	return NULL;
}

treePointer findPosition(treePointer root, element newOne) {
	if (root == NULL) return NULL;
	while (root->leftChild || root->rightChild) {
		int cmp = strcmp(newOne.name, root->data.name);
		if (cmp == 0) return NULL;
		if (cmp < 0) {
			if (root->leftChild == NULL) {
				return root;
			}
			root = root->leftChild;
		}
		else {
			if (root->rightChild == NULL) {
				return root;
			}
			root = root->rightChild;
		}
	}
	return root;
}

void insertNode(treePointer *node, element newOne) {
	treePointer temp = findPosition(*node, newOne);
	int cnt = 0;
	if (!(*node)|| temp) {
		treePointer ptr = (treePointer)malloc(sizeof(Node));
		ptr->data = newOne;
		ptr->leftChild = ptr->rightChild = NULL;
		if (*node) {
			int cmp = strcmp(newOne.name, temp->data.name);
			if (cmp == 0) {
				printf("같은 입력 값이 존재 합니다.\n");
				return;
			}
			if (cmp < 0) {
				temp->leftChild = ptr;
				cnt = -1;
			}
			else {
				temp->rightChild = ptr;
				cnt = 1;
			}
		}
		else {
			*node = ptr;
			printf("The first node\n");
		}
		if (cnt == -1) {
			printf("%s is inserted as the left child of %s\n", ptr->data.name, temp->data.name);
		}
		else if (cnt == 1) {
			printf("%s is inserted as the right child of %s\n", ptr->data.name, temp->data.name);
		}
	}
	else if (!(temp)) {
		printf("같은 입력 값이 존재 합니다.\n");
		return;
	}
}

treePointer childNode(treePointer parent, treePointer node, char *name) {
	treePointer childNode = NULL;
	if (parent) {
		if (parent == node) {
			childNode = node;
		}
		if (parent->leftChild && strcmp(parent->leftChild->data.name, name) == 0) {
			childNode = parent->leftChild;
		}
		else if (parent->rightChild && strcmp(parent->rightChild->data.name, name) == 0) {
			childNode = parent->rightChild;
		}
	}
	return childNode;
}

treePointer minNode(treePointer *node) {
	treePointer cur = node;
	while (cur->leftChild != NULL) {
		cur = cur->leftChild;
	}
	return cur;
}

void deleteNode(treePointer *node, char *name) {
	treePointer parent = BSTsearch(*node, name);
	treePointer deNode = NULL;
	treePointer temp = NULL;
	if (parent) {
		deNode = childNode(parent, *node, name);
	}
	else {
		printf("Not Available\n");
		return;
	}
	//no child node
	if (deNode->leftChild == NULL && deNode->rightChild == NULL) {
		if (deNode != *node) { // 부모 노드 있으면 부모노드 링크도 NULL 시키고 free해야함.
			if (parent->leftChild == deNode) {
				parent->leftChild = NULL;
			}
			else {
				parent->rightChild = NULL;
			}
		}
		else { // 오직 루트노드만 있을 경우
			*node = NULL;
		}
		free(deNode);
		if (cnt == 0) {
			printf("참가가 취소 되었습니다.\n");
		}
		return;
	}
	//two child nodes
	else if (deNode->leftChild && deNode->rightChild) {
		temp = minNode(deNode->rightChild); //inorder successor 찾기
		deNode->data = temp->data; // 삭제할 노드에 그 노드의 successor를 넣기
		printf("대체될 정보의 이름%s 신청날짜%s 지역%s\n", temp->data.name, temp->data.date, temp->data.region);
		printf("참가가 취소 되었습니다.\n");
		cnt = 1;
		deleteNode(&(deNode->rightChild), temp->data.name); //successor 제거
		cnt = 0;
		return;
	}
	else {//one child node
		temp = (deNode->leftChild == NULL) ? deNode->rightChild : deNode->leftChild;
		if (cnt == 0) {
			printf("대체될 정보의 이름%s 신청날짜%s 지역%s\n", temp->data.name, temp->data.date, temp->data.region);
			printf("참가가 취소 되었습니다.\n");
		}
		if (deNode != *node) { // 삭제된 노드가 루트노드가 아닐 경우
			if (parent->leftChild == deNode) {
				parent->leftChild = temp;
			}
			else {
				parent->rightChild = temp;
			}
		}
		else { // 삭제된 노드가 루트노드일 경우
			*node = temp;
		}
		free(deNode);
		return;
	}
}

void modifyRecord(treePointer root, char *name, char *info) {
	treePointer parent = BSTsearch(root, name);
	treePointer node = childNode(parent, root, name);
	if (node) {
		if (info[0] >= '0' && info[0] <= '9') { //날짜 정보
			strcpy(node->data.date, info);
		}
		else { // 신청지역
			strcpy(node->data.region, info);
		}
		printf("수정완료\n");
		printf(" 이름 %s\n 참가날짜 %s\n 신청지역 %s\n", node->data.name, node->data.date, node->data.region);
	}
	else {
		printf("참가자 검색이 되지 않습니다.\n");
	}
	return;
}

int main() {
	int input = 0;
	treePointer tree = NULL;
	char name[11];
	char date[9];
	char region[21];
	do {
		printf("1.신규\n2.검색\n3.정보변경\n4.참가취소\n5.종료\n");
		scanf("%d", &input);
		switch (input) {
		case 1: // insert
			printf("신규정보를 입력하십시오(이름(10자이내), 참가날짜(YYYYMMDD), 신청지역(20자이내))\n");
			scanf("%s %s %s", name, date, region);
			element data;
			strcpy(data.name, name);
			strcpy(data.date, date);
			strcpy(data.region, region);
			insertNode(&tree, data);
			break;
		case 2: // search
			printf("찾으실 이름을 입력하십시오\n");
			scanf("%s", name);
			treePointer parent = BSTsearch(tree, name);
			treePointer node = childNode(parent, tree, name);
			if (node) {
				printf("검색완료\n");
				printf(" 이름 %s\n 참가날짜 %s\n 신청지역 %s\n", node->data.name, node->data.date, node->data.region);
			}
			else {
				printf("검색하신 이름이 존재하지 않습니다.\n");
			}
			break;
		case 3: // change
			printf("변경하실 정보를 입력하십시오(이름, 정보)\n");
			scanf("%s %s", name, region);
			modifyRecord(tree, name, region);
			break;
		case 4: // delete
			printf("취소하실 이름을 입력하십시오\n");
			scanf("%s", name);
			deleteNode(&tree, name);
			break;
		default:
			break;
		}
	} while (input != 5);
	system("pause");
	return 0;
}


