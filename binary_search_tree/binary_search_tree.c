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
				printf("���� �Է� ���� ���� �մϴ�.\n");
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
		printf("���� �Է� ���� ���� �մϴ�.\n");
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
		if (deNode != *node) { // �θ� ��� ������ �θ��� ��ũ�� NULL ��Ű�� free�ؾ���.
			if (parent->leftChild == deNode) {
				parent->leftChild = NULL;
			}
			else {
				parent->rightChild = NULL;
			}
		}
		else { // ���� ��Ʈ��常 ���� ���
			*node = NULL;
		}
		free(deNode);
		if (cnt == 0) {
			printf("������ ��� �Ǿ����ϴ�.\n");
		}
		return;
	}
	//two child nodes
	else if (deNode->leftChild && deNode->rightChild) {
		temp = minNode(deNode->rightChild); //inorder successor ã��
		deNode->data = temp->data; // ������ ��忡 �� ����� successor�� �ֱ�
		printf("��ü�� ������ �̸�%s ��û��¥%s ����%s\n", temp->data.name, temp->data.date, temp->data.region);
		printf("������ ��� �Ǿ����ϴ�.\n");
		cnt = 1;
		deleteNode(&(deNode->rightChild), temp->data.name); //successor ����
		cnt = 0;
		return;
	}
	else {//one child node
		temp = (deNode->leftChild == NULL) ? deNode->rightChild : deNode->leftChild;
		if (cnt == 0) {
			printf("��ü�� ������ �̸�%s ��û��¥%s ����%s\n", temp->data.name, temp->data.date, temp->data.region);
			printf("������ ��� �Ǿ����ϴ�.\n");
		}
		if (deNode != *node) { // ������ ��尡 ��Ʈ��尡 �ƴ� ���
			if (parent->leftChild == deNode) {
				parent->leftChild = temp;
			}
			else {
				parent->rightChild = temp;
			}
		}
		else { // ������ ��尡 ��Ʈ����� ���
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
		if (info[0] >= '0' && info[0] <= '9') { //��¥ ����
			strcpy(node->data.date, info);
		}
		else { // ��û����
			strcpy(node->data.region, info);
		}
		printf("�����Ϸ�\n");
		printf(" �̸� %s\n ������¥ %s\n ��û���� %s\n", node->data.name, node->data.date, node->data.region);
	}
	else {
		printf("������ �˻��� ���� �ʽ��ϴ�.\n");
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
		printf("1.�ű�\n2.�˻�\n3.��������\n4.�������\n5.����\n");
		scanf("%d", &input);
		switch (input) {
		case 1: // insert
			printf("�ű������� �Է��Ͻʽÿ�(�̸�(10���̳�), ������¥(YYYYMMDD), ��û����(20���̳�))\n");
			scanf("%s %s %s", name, date, region);
			element data;
			strcpy(data.name, name);
			strcpy(data.date, date);
			strcpy(data.region, region);
			insertNode(&tree, data);
			break;
		case 2: // search
			printf("ã���� �̸��� �Է��Ͻʽÿ�\n");
			scanf("%s", name);
			treePointer parent = BSTsearch(tree, name);
			treePointer node = childNode(parent, tree, name);
			if (node) {
				printf("�˻��Ϸ�\n");
				printf(" �̸� %s\n ������¥ %s\n ��û���� %s\n", node->data.name, node->data.date, node->data.region);
			}
			else {
				printf("�˻��Ͻ� �̸��� �������� �ʽ��ϴ�.\n");
			}
			break;
		case 3: // change
			printf("�����Ͻ� ������ �Է��Ͻʽÿ�(�̸�, ����)\n");
			scanf("%s %s", name, region);
			modifyRecord(tree, name, region);
			break;
		case 4: // delete
			printf("����Ͻ� �̸��� �Է��Ͻʽÿ�\n");
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


