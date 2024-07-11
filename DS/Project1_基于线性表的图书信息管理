#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
	char number[20];
	char title[100];
	float price;
};

int main() {
	int i;
	int choice, n = 0, insertPosition, deletePosition;
	struct Book books[100];
	float totalPrice, maxPrice;
	struct Book newBook;


	while (1) {
		printf("选择功能:\n");
		printf("1. 图书信息表的创建和输出\n");
		printf("2. 图书信息表的修改\n");
		printf("3. 查找价格最高的图书\n");
		printf("4. 新图书的入库\n");
		printf("5. 旧图书的出库\n");
		printf("6. 退出\n");
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				n = 0;
				while (1) {
					scanf("%s", books[n].number);
					if (strcmp(books[n].number, "000") == 0) {
						break;
					}
					scanf("%s%f", books[n].title, &books[n].price);
					n++;
				}
				printf("%d\n", n);
				int i;
				for (i = 0; i < n; i++) {
					printf("%s %s %.2f\n", books[i].number, books[i].title, books[i].price);
				}
				break;

			case 2:
				n = 0;
				totalPrice = 0.0;
				while (1) {
					scanf("%s", books[n].number);//if (strcmp(books[n].number, "0") == 0 && strcmp(books[n].title, "0") == 0 && books[n].price == 0)

					if (strcmp(books[n].number, "000") == 0) {
						break;
					}
					scanf("%s%f", books[n].title, &books[n].price);
					totalPrice += books[n].price;
					n++;
				}
				float averagePrice = totalPrice / n;
				for (i = 0; i < n; i++) {
					if (books[i].price < averagePrice) {
						books[i].price *= 1.2;
					} else {
						books[i].price *= 1.1;
					}
				}
				printf("%.2f\n", averagePrice);
				for (int i = 0; i < n; i++) {
					printf("%s %s %.2f\n", books[i].number, books[i].title, books[i].price);
				}
				break;

			case 3:
				scanf("%d", &n);
				maxPrice = 0.0;
				for (int i = 0; i < n; i++) {
					scanf("%s %s %f", books[i].number, books[i].title, &books[i].price);
					if (books[i].price > maxPrice) {
						maxPrice = books[i].price;
					}
				}
				int count = 0;
				for (int i = 0; i < n; i++) {
					if (books[i].price == maxPrice) {
						count++;
					}
				}
				printf("%d\n", count);
				for (int i = 0; i < n; i++) {
					if (books[i].price == maxPrice) {
						printf("%s %s %.2f\n", books[i].number, books[i].title, books[i].price);
					}
				}
				break;

			case 4:
				scanf("%d", &n);
				for (int i = 0; i < n; i++) {
					scanf("%s %s %f", books[i].number, books[i].title, &books[i].price);
				}
				scanf("%d", &insertPosition);
				scanf("%s %s %f", newBook.number, newBook.title, &newBook.price);
				if (insertPosition < 1 || insertPosition > n + 1) {
					printf("抱歉，入库位置非法!\n");
				} else {
					for (int i = n; i >= insertPosition; i--) {
						books[i] = books[i - 1];
					}
					books[insertPosition - 1] = newBook;
					n++;
					for (int i = 0; i < n; i++) {
						printf("%s %s %.2f\n", books[i].number, books[i].title, books[i].price);
					}
				}
				break;

			case 5:
				scanf("%d", &n);
				for (int i = 0; i < n; i++) {
					scanf("%s %s %f", books[i].number, books[i].title, &books[i].price);
				}
				scanf("%d", &deletePosition);
				if (deletePosition < 1 || deletePosition > n) {
					printf("抱歉，出库位置非法!\n");
				} else {
					for (int i = deletePosition - 1; i < n - 1; i++) {
						books[i] = books[i + 1];
					}
					n--;
					for (int i = 0; i < n; i++) {
						printf("%s %s %.2f\n", books[i].number, books[i].title, books[i].price);
					}
				}
				break;

			case 6:
				exit(0);
				break;

			default:
				printf("输入无效，请重新输入。\n");
		}
	}

	return 0;
}
