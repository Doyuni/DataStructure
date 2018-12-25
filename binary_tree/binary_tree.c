#pragma disable(warning: 4996)
#include <stdio.h>
#include <Windows.h>
#include <math.h>

void getchild(int index, int hn, int n, int leaf) {
	int tmp = hn / 2 - 1;
	if (index > n) {
		printf("잘못된 index값을 입력했습니다.\n");
	}
	else if (index > n-leaf) {
		printf("찾으시는 노드의 child의 수는 0입니다.\n");
	}
	else {
		int cnt = 0;
		for (int i = n; i > 0; i--) 
		{
			if (i == index * 2) {
				cnt++;
			}
			else if (i == index * 2 + 1) {
				cnt++;
			}
			if (cnt >= 2) {
				break;
			}
		}
		printf("찾으시는 노드의 child의 수는 %d입니다.\n", cnt);
	}
}

double getleaf(int n) {
	double num = (double)n;
	return ceil(num/2);
}

int getwidth(int n, int hn) {
	int tmp = n - (hn / 2 - 1);
	if (tmp <= hn / 4) {
		return hn / 4;
	}
	else {
		return tmp;
	}
}
int gethn(int h) { // 2의 h제곱값 구하기
	int hn = 1;
	for (int i = 0; i < h; i++)
	{
		hn *= 2;
	}
	return hn;
}

int getheight(int n) {
	int h = 1;
	int hn = 1;
	while (1) {
		for (int i = 0; i < h; i++)
		{
			hn *= 2;
			if (n >= hn / 2 && n < hn) {
				return h;
			}
			h++;
		}
	}
	return -1;
}

int main() {
	int index, n;
	do {
		printf("Tree의 노드 개수를 입력하시오(0입력시 종료)\n");
		scanf("%d", &n);
		getchar();
		if (n != 0) {
			int h = getheight(n);
			int hn = gethn(h);
			printf("높이는 %d입니다.\n", h);
			printf("넓이는 %d입니다.\n", getwidth(n, hn));
			double leaf = getleaf(n);
			printf("리프노드의 개수는 %.0lf개입니다.\n", leaf);
			printf("찾을 노드의 index를 입력하시오\n");
			scanf("%d", &index);
			getchar();
			getchild(index, hn, n, leaf);
		}
	} while (n != 0);

	system("pause");
	return 0;
}