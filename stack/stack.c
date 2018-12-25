#pragma disable(warning: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

typedef struct {
	int max; //스택 용량
	int num; // 스택 요소 개수
	int *stk; // 스택 요소에 대한 포인터
}Stack;

int pairs =0; // 짝 개수

//스택 초기화
void Initialize(Stack *s, int max) {
	s->num = 0;
	s->stk = (char*)malloc(sizeof(char)*(max+1));
	s->max = max;
	return;
}

void push(Stack *s, char input) {
	if (s->num >= s->max) {
		printf("가득참\n");
	}
	else {
		s->stk[s->num++] = input;
	}
}

int pop(Stack *s, char input) { // 오른쪽 괄호이면 스택의 꼭대기와 비교해서 짝이면 0리턴
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
		if (input[i] == '(' || input[i] == '{' || input[i] == '[') { // 왼쪽 괄호는 push
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
	if (s->num != 0) { // 짝이 되지 못한 요소가 있을 때
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
		printf("input string(q입력시 종료)\n");
		scanf("%s", input);
		getchar();
		if (input[0] != 'q') {
			int length = strlen(input);
			Initialize(s, length);
			if (check(input, length, s) == 0) {
				printf("There are %d pairs of parenthesis\n", pairs);
				pairs = 0; // 짝 개수 초기화
			}
		}
	} while (input[0] != 'q');

	system("pause");
	return 0;
}
