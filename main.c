#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <windows.h>


#define ALFAVIT "ABCDEFGHIJGKLMNOPQRSTUVWXYZ"
#define TEXT_LEN 20


typedef struct Product {
	char name[TEXT_LEN];
	int date[3];
	int exp_date[3];
	int price;
	int number;
} product_t;

int getRandomNumber(int min, int max);
char* getRandomString(char* text, int size);

product_t* fill_rand_array(product_t* array, int size);
product_t* fill_manual_array(product_t* array, int size);
product_t* search_name(product_t* array, int size, char name[20]);
product_t* sort_array(product_t* array, int size);
void print_array(product_t* array, int size);
void print_product(product_t* product);
int compare(const void* a, const void* b);

int main() {
	// Настройки локализации для работы со структурами
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	int size, command;
	char text, name[TEXT_LEN];
	product_t *search_elem, *products;

	printf("Введите количество позиций > ");
	scanf("%d", &size);

	products = (product_t*)malloc(size * sizeof(product_t));

	printf("Выберите способ заполнения:\n");
	printf("\t1. Ручное заполнеие\n");
	printf("\t2. Рандомное заполнение\n");
	printf("Номер команды > ");
	scanf("%d", &command);

	switch (command) {
	case 1:
		fill_manual_array(products, size);
		break;
	case 2:
		fill_rand_array(products, size);
		break;
	default:
		printf("Команда введена неверно");
		return 0;
	}
	
	while (1) {
		printf("Выберите команду:\n");
		printf("\t1. Вывести все элементы\n");
		printf("\t2. Найти элемент\n");
		printf("\t3. Выполнить сортировку\n");
		printf("Номер команды > ");
		scanf("%d", &command);

		switch (command) {
		case 1:
			print_array(products, size);
			break;
		case 2:
			printf("Введите имя искомого > ");
			scanf("%s", name);
			search_elem = search_name(products, size, name);
			print_product(search_elem);
			break;
		case 3:
			qsort(products, size, sizeof(product_t), compare);
			printf("Сортировка выполнена!!!\n");
			break;
		default:
			break;
		}
		printf("Продолжить выполнение программы? (Да - y, нет - n)\n");
		getchar();
		if ((text = getchar()) == 'n')
			break;
	}
	free(products);
}

int getRandomNumber(int min, int max) {
	int rand_i;
	rand_i = rand() % (max - min + 1) + min;
	return rand_i;
}

char* getRandomString(char* text, int size) {
	for (int i = 0;i < size - 1; i++) {
		text[i] = ALFAVIT[rand() % (size + 1)];
	}
	text[size - 1] = '\0';
	return text;
}

product_t* fill_rand_array(product_t* array, int size) {
	int min, max;
	min = 374; max = 21367;
	for (int i = 0; i < size; i++) {
		getRandomString(array[i].name, TEXT_LEN);
		array[i].date[0] = getRandomNumber(1, 31);	array[i].date[1] = getRandomNumber(1, 12); array[i].date[2] = getRandomNumber(2000, 2024);
		array[i].exp_date[0] = getRandomNumber(1, 31); array[i].exp_date[1] = getRandomNumber(1, 12); array[i].exp_date[2] = getRandomNumber(2025, 2027);
		array[i].price = getRandomNumber(min, max);
		array[i].number = getRandomNumber(1, 9999);
	}
	return array;
}

product_t* fill_manual_array(product_t* array, int size) {
	for (int i = 0; i < size; i++) {
		printf("Введите название > ");
		scanf("%s", array[i].name);
		printf("Введите дату изготовления (Д М Г)> ");
		scanf("%d %d %d", &array[i].date[0], &array[i].date[1], &array[i].date[2]);
		printf("Введите срок годности (Д М Г)> ");
		scanf("%d %d %d", &array[i].exp_date[0], &array[i].exp_date[1], &array[i].exp_date[2]);
		printf("Введите цену > ");
		scanf("%d", &array[i].price);
		printf("Введите номер серии > ");
		scanf("%d", &array[i].number);
		printf("\n");
	}
	return array;
}

void print_array(product_t* array, int size) {
	product_t position;
	for (int i = 0; i < size; i++) {
		position = array[i];
		printf("Название: %s\n", position.name);
		printf("Дата изготовления: %d.%d.%d\n", position.date[0], position.date[1], position.date[2]);
		printf("Срок годности: %d.%d.%d\n", position.exp_date[0], position.exp_date[1], position.exp_date[2]);
		printf("Цена: %d\n", position.price);
		printf("Серийный номер: %d\n", position.number);
		printf("\n");
	}
}

void print_product(product_t* product) {
	product_t array = *product;
	printf("| %s | %d.%d.%d | %d.%d.%d | %d | %d |\n", array.name, array.date[0], array.date[1], array.date[2], array.exp_date[0],
		array.exp_date[1], array.exp_date[2], array.price, array.number);
}

product_t* search_name(product_t* array, int size, char name[TEXT_LEN]) {
	for (int i = 0; i < size; i++) {
		if (strcmp(array[i].name, name) == 0) {
			return (array + i);
		}
	}
	return NULL;
}

int compare(const void* a, const void* b) {
	const product_t* productA = (const product_t*)a;
	const product_t* productB = (const product_t*)b;
	int dayA, monthA, yearA, 
		dayB, monthB, yearB;

	dayA = (*productA).date[0]; monthA = (*productA).date[1]; yearA = (*productA).date[2];
	dayB = (*productB).date[0]; monthB = (*productB).date[1]; yearB = (*productB).date[2];

	if (yearA < yearB) {
		return -1;
	} else if (yearA == yearB) {
		if (monthA < monthB) {
			return -1;
		} else if (monthA > monthB) {
			return 1;
		} else if (monthA == monthB) {
			if (dayA < dayB) {
				return -1;
			} else if (dayA > dayB) {
				return 1;
			}
			return 0;
		}
	} else if (yearA > yearB) {
		return 1;
	}
}




