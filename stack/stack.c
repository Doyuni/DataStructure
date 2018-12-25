#pragma disable(warning: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

typedef struct {
	int max; //���� �뷮
	int num; // ���� ��� ����
	int *stk; // ���� ��ҿ� ���� ������
}Stack;

int pairs =0; // ¦ ����

//���� �ʱ�ȭ
void Initialize(Stack *s, int max) {
	s->num = 0;
	s->stk = (char*)malloc(sizeof(char)*(max+1));
	s->max = max;
	return;
}

void push(Stack *s, char input) {
	if (s->num >= s->max) {
		printf("������\n");
	}
	else {
		s->stk[s->num++] = input;
	}
}

int pop(Stack *s, char input) { // ������ ��ȣ�̸� ������ ������ ���ؼ� ¦�̸� 0����
	if (input == ')') {
		if (s->stk[s->num-1] == '(') {
			s->stk[s->num--];
			pairs++;
			return 0;
		}
	}
	else if (input == ']') {
		if (s->stk[s->num-1] == '[') {
			s->stk[s->num--]; 
			pairs++;
			return 0;
		}
	}
	else {
		if (s->stk[s->num-1] == '{') {
			s->stk[s->num--];
			pairs++;
			return 0;
		}
	}
	return -1;
}

int check(char *input, int length, Stack *s) {
	for (int i = 0; i < length; i++)
	{
		if (input[i] == '(' || input[i] == '{' || input[i] == '[') { // ���� ��ȣ�� push
			push(s, input[i]);
		}
		else {
			if (pop(s, input[i]) == -1) { 
				printf("%c is error.\n", input[i]);
				printf("The string is unbalanced.\n");
				return -1;
			}
		}
	}
	if (s->num != 0) { // ¦�� ���� ���� ��Ұ� ���� ��
		printf("%c is error.\n", input[0]);
		printf("The string is unbalanced.\n");
		return -1;
	}
	return 0;
}

int main() {
	char input[51];
	Stack *s = (Stack*)malloc(sizeof(Stack));
	do {
		printf("input string(q�Է½� ����)\n");
		scanf("%s", input);
		getchar();
		if (input[0] != 'q') {
			int length = strlen(input);
			Initialize(s, length);
			if (check(input, length, s) == 0) {
				printf("There are %d pairs of parenthesis\n", pairs);
				pairs = 0; // ¦ ���� �ʱ�ȭ
			}
		}
	} while (input[0] != 'q');

	system("pause");
	return 0;
}
