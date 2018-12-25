#pragma disable(warning: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

typedef struct TreeNode* TreePointer;
typedef struct TreeNode {
	char data;
	TreePointer leftChild;
	TreePointer rightChild;
} TreeNode;


TreePointer createNode(char data) {
	TreePointer newNode = (TreePointer)malloc(sizeof(TreeNode));
	newNode->data = data;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;
	return newNode;
}

TreePointer createTree(char ** expr) {
	TreePointer ptr = createNode(**expr);
	if (**expr < 48) {
		*expr = *expr + 1;
		ptr->leftChild = createTree(expr);
		*expr = *expr + 1;
		ptr->rightChild = createTree(expr);
	}
	else {
		return ptr;
	}
	if (ptr->leftChild != NULL && ptr->rightChild != NULL) {
		return ptr;
	}
}

int evalExprTree(TreePointer head) {

	if (head->leftChild == NULL && head->rightChild == NULL) {
		return head->data - '0';
	}
	else {
		
		int op1 = evalExprTree(head->leftChild);
		int op2 = evalExprTree(head->rightChild);

		switch (head->data) {
		case '+':
			return op1 + op2;

		case '-':
			return op1 - op2;

		case '*':
			return op1 * op2;

		case '/':
			return op1 / op2;
		}
	}
	return 0;
}

int main() {
	char buffer[20];
	do {
		scanf("%s", buffer);
		getchar();
		if (buffer[0] != 'q') {
			char *input = &buffer;
			TreePointer head = createTree(&input);
			printf("result: %d\n", evalExprTree(head));
		}

	} while (buffer[0] != 'q');

	system("pause");
	return 0;
}