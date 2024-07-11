#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>

typedef struct student {
	char name[8];
	float score;
} Student;

void quickSort(Student arr[], int left, int right) {
	if (left < right) {
		int i = left, j = right;
		int pivot = arr[(left + right) / 2].score;

		while (i <= j) {
			while (arr[i].score > pivot) i++;
			while (arr[j].score < pivot) j--;

			if (i <= j) {
				// 交换元素
				Student temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
				i++;
				j--;
			}
		}

		// 递归排序左半部分和右半部分
		if (left < j) quickSort(arr, left, j);
		if (i < right) quickSort(arr, i, right);
	}
}

int main() {
	int n = 0;
	Student students[100];

	while (1) {
		scanf("%s %f", students[n].name, &students[n].score);

		// Check if input has ended
		if (students[n].score == 0 && strcmp(students[n].name, "00") == 0)
			break;

		n++;
	}

	quickSort(students, 0, n - 1);

	int prevRank = 1;

	printf("%d %s %.2f\n", prevRank, students[0].name, students[0].score);

	for (int i = 1; i < n; ++i) {
		if (students[i].score != students[i - 1].score) {
			prevRank = i + 1;
		}
		printf("%d %s %.2f\n", prevRank, students[i].name, students[i].score);
	}

	return 0;
}