#pragma disable(warning: 4996)
#include <stdio.h>
#include <Windows.h>
#include <math.h>

void getchild(int index, int hn, int n, int leaf) {
	int tmp = hn / 2 - 1;
	if (index > n) {
		printf("�߸��� index���� �Է��߽��ϴ�.\n");
	}
	else if (index > n-leaf) {
		printf("ã���ô� ����� child�� ���� 0�Դϴ�.\n");
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
		printf("ã���ô� ����� child�� ���� %d�Դϴ�.\n", cnt);
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
int gethn(int h) { // 2�� h������ ���ϱ�
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
		printf("Tree�� ��� ������ �Է��Ͻÿ�(0�Է½� ����)\n");
		scanf("%d", &n);
		getchar();
		if (n != 0) {
			int h = getheight(n);
			int hn = gethn(h);
			printf("���̴� %d�Դϴ�.\n", h);
			printf("���̴� %d�Դϴ�.\n", getwidth(n, hn));
			double leaf = getleaf(n);
			printf("��������� ������ %.0lf���Դϴ�.\n", leaf);
			printf("ã�� ����� index�� �Է��Ͻÿ�\n");
			scanf("%d", &index);
			getchar();
			getchild(index, hn, n, leaf);
		}
	} while (n != 0);

	system("pause");
	return 0;
}