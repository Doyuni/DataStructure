#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define MAX_SIZE 26
typedef struct {
	char name[10];
	char t_name[20];
	int money;
}tableEntry;
tableEntry bucket[MAX_SIZE];

int searchRecord(char *name, int* found) {
	int i = name[0] - 'a';
	int count = 0;
	int b = 1;
	int e = 1;
	int tmp = i;
	while (count < 26) {
		int check = strcmp(bucket[i].name, name);
		if (strcmp(bucket[i].name, "") == 0) { // bucket[i]가 비어있을 때
			*found = 1; 
			break;
		}
		else if (check == 0) { // 검색하고자 하는 name이 있는 경우
			*found = 2;
			break;
		}
		else {
			printf("probing: %d\n", i);
			i = (tmp + b) % 26;
			e++;
			b = e * e;
			*found = 0;
		}
		count++;
	}
	return i;
}

void AddRecord(tableEntry subscriberTable[], tableEntry new) {
	int found = 0;
	int index = searchRecord(new.name, &found);
	if (found) {
		subscriberTable[index] = new;
	}
}

int main() {
	tableEntry new;
	int num;
	char name[10];
	printf("입력할 값의 개수는 얼마입니까? : ");
	scanf("%d", &num);
	for (int i = 1; i <= num; ++i) {
		printf("%d번째 값을 입력하세요 : ", i);
		scanf("%s %s %d", new.name, new.t_name, &new.money);
		AddRecord(bucket, new);
	}
	while (1) {
		printf("검색할 값을 입력하세요 : ");
		scanf("%s", name);
		if (name[0] == '.') break;
		int check = 0;
		int id = searchRecord(name, &check);
		if (check == 2) {
			printf("      %s %s %d\n", bucket[id].name, bucket[id].t_name, bucket[id].money);
		}
		else {
			printf("      존재하지 않습니다.\n");
		}
	}
	system("pause");
	return 0;
}