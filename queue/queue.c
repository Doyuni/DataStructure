#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

typedef struct {
	int max; //큐의 용량
	int num; //현재 요소 수
	int front;
	int rear;
	char **name; //대기자 명단

} CircularQueue;

//병원 도착
void Hospital_Arrive(CircularQueue *q) { 
	char tmp[20]; // 명단 입력 변수
	int input;
	if (q->num == q->max) { // 대기자 5명일 때
		printf("Service is not available\n");
	}
	else {
		printf("현재 대기자 수: %d\n", q->num);
		printf("대기자 등록을 하시겠습니까? 1. Yes 2. No : ");
		scanf("%d", &input);
		getchar();
		if (input == 1){ 
			q->num++; // 요소 1 증가
			q->rear++; // rear 1 증가
			if (q->rear == q->max) { // 원형 큐 특징(공간활용)
				q->rear = 0;
			}
			printf("대기자 명단을 입력해주세요: ");
			scanf("%s", tmp);
			q->name[q->rear] = (char *)malloc(sizeof(tmp + 1) * sizeof(char)); // 문자열 끝의 NULL도 계산하여 tmp+1한 사이즈만큼 동적할당
			strcpy(q->name[q->rear], tmp); // 문자열 복사
		} 
	}
	return;
}
//진료 완료
void Hospital_Complete(CircularQueue *q) {
	if (q->num != 0) { // 요소가 0이 아닌 경우 dequeue 가능
		q->num--; 
		q->front++;
		if (q->front == q->max) { //원형 큐 특징(공간활용)
			q->front = 0;
		}
		printf("진료 가능한 손님: %s\n", q->name[q->front]);
	}
	else {
		printf("There is no patient waiting\n");
	}
	return;
}

int main() {
	//큐 초기화
	CircularQueue *q;
	q = (CircularQueue*)malloc(sizeof(CircularQueue));
	q->name = (char**)malloc(sizeof(char*)*5); // 5명의 대기자 공간 할당
	q->num = 0; 
	q->max = 5; // 최대 대기자 수 5명
	q->front = 0;
	q->rear = 0;
	//메뉴
	int menu;
	do {
		printf("1. 병원 도착  2. 진료 완료  3. 서비스 종료: ");
		scanf("%d", &menu);
		getchar(); // scanf 입력 후 개행문자 처리
		switch (menu)
		{
		case 1:
			Hospital_Arrive(q);
			break;
		case 2:
			Hospital_Complete(q);
			break;
		}
	} while (menu != 3); // 서비스 종료가 나오기 전까지 반복
	system("pause");
	return 0;
}