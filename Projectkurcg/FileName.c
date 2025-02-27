#define _CRT_SECURE_NO_DEPRECATE
#define MAX_DEVICE 50
#include <locale.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
NetworkCard[];

//Структура данных
typedef struct {
	char name[50];
	char interface[50];
	int speed;
	int ports45;
	bool usb_hub;
	char model[50];
} Cards;

//Добавление в файл
int addCards(Cards adapters[], int* count, char const* filename) {

	printf(" Добавление новой записи \n");

	// Ввод значений
	printf("Введите производителя: ");
	scanf("%s", adapters[*count].name);

	printf("Введите интерфейс (например, PCI-E, USB_3.0, Type-C): ");
	scanf("%s", adapters[*count].interface);

	printf("Введите скорость (в Мбит/с): ");
	scanf("%d", &adapters[*count].speed);

	printf("Введите количество портов: ");
	scanf("%d", &adapters[*count].ports45);

	printf("Разветлитель usb (Да/Нет): ");
	while (scanf("%d", &adapters[*count].usb_hub) != 1 || (adapters[*count].usb_hub != 0 && adapters[*count].usb_hub != 1)) {
		printf("Ошибка: введите 1 - (да) или 0 - (нет).\n");
		while (getchar() != '\n'); // отчистка буфера ввода
	}

	printf("Введите модель: ");
	scanf("%s", adapters[*count].model);

	printf("Запись успешно добавлена в базу данных!\n");

	(*count)++;

	return 1;
}

//Поиск записей
int searchCards(const Cards adapters[], int count, Cards results[], char* name, char* interface, int searchOption) {
	int resultCount = 0;

	for (int i = 0; i < count; i++) {
		int names = (searchOption == 1 || searchOption == 3) && strcmp(adapters[i].name, name) == 0;
		int interfaces = (searchOption == 2 || searchOption == 3) && strcmp(adapters[i].interface, interface) == 0;

		if (searchOption == 1 && names)
			results[resultCount++] = adapters[i]; // сохранение указателя на запись и добавление записи в новый массив
		else if (searchOption == 2 && interfaces)
			results[resultCount++] = adapters[i];
		else if (searchOption == 3 && names && interfaces)
			results[resultCount++] = adapters[i];
	}
	return resultCount;
}

//Запись в файл
int saveDevicesToFile(Cards adapters[], int count, const char* filename) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		return 2;
	}

	for (int i = 0; i < count; i++) {
		fprintf(file, "%s,%s,%d,%d,%d,%s\n",
			adapters[i].name,
			adapters[i].interface,
			adapters[i].speed,
			adapters[i].ports45,
			adapters[i].usb_hub,
			adapters[i].model);
	}

	fclose(file);
	return 1;
}

//Чтение из файла
int loadDevicesFromFile(Cards adapters[], int* count, char const* filename) {
	FILE* file = fopen(filename, "r");

	*count = 0;
	while
		(fscanf(file, "%49[^,],%19[^,],%d,%d,%d,%19[^\n]\n",
			adapters[*count].name,
			adapters[*count].interface,
			&adapters[*count].speed,
			&adapters[*count].ports45,
			&adapters[*count].usb_hub,
			adapters[*count].model) == 6) {
		(*count)++;
		if (*count >= MAX_DEVICE) {
			return 2;
			break;
		}
	}
	fclose(file);
	return 1;
}

//Сортировка
int bubblesort(Cards* adapters, int count, int criterion) {
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - i - 1; j++) {
			int swapNeeded = 0;

			if (criterion == 1) {
				//сортировка по производитель
				if (adapters[j].name < adapters[j + 1].name) {
					swapNeeded = 1;
				}
			}
			else if (criterion == 2) {
				//сортировка скорость передачи 
				if (adapters[j].interface > adapters[j + 1].interface) {
					swapNeeded = 1;
				}
			}
			else if (criterion == 3) {
				//сортировка по 2-ум критериям
				if (adapters[j].name < adapters[j + 1].name || (adapters[j].name == adapters[j + 1].name && adapters[j].interface > adapters[j + 1].interface)) {
					swapNeeded = 1;
				}
			}

			if (swapNeeded) {
				Cards temp = adapters[j];
				adapters[j] = adapters[j + 1];
				adapters[j + 1] = temp;
			}
		}
	}
	return 1;
}

//Изменение записей
int editDevice(Cards adapters[], int count, const char* name) {
	int found = 0;
	for (int i = 0; i < count; i++) {
		if (strcmp(adapters[i].name, name) == 0) {
			found = 1;
			printf("Редактирование записи для производителя %s\n", name);
			int choice;
			do {
				printf("\nВыберите поле для изменения:\n");
				printf("1. Название\n");
				printf("2. Интерфейс: \n");
				printf("3. Скорость\n");
				printf("4. Количество портов\n");
				printf("5. Разветлитель usb\n");
				printf("6. Модель\n");
				printf("0. Выход\n");
				printf("Ваш выбор: ");
				scanf("%d", &choice);
				switch (choice) {
				case 1:
					printf("Введите название\n");
					scanf("%s", adapters[i].name);
					break;
				case 2:
					printf("Введите интерфейс\n");
					scanf("%s", adapters[i].interface);
					break;
				case 3:
					printf("Введите скорость\n");
					scanf("%d", &adapters[i].speed);
					break;
				case 4:
					printf("Введите количество портов\n");
					scanf("%d", &adapters[i].ports45);
					break;
				case 5:
					printf("Введители разветлитель\n");
					scanf("%s", &adapters[i].usb_hub);
					break;
				case 6:
					printf("Введите модель\n");
					scanf("%s", adapters[i].model);
					break;
				case 0:
					printf("Выход из режима редактирования.\n");
					break;
				default:
					printf("Неверный выбор. Попробуйте снова.\n");
				}

				if (choice != 0) {
					return 1;
				}
			} while (choice != 0);

			return 0;
		}
	}
	if (!found) {
		printf("Запись не найдена.\n");
	}
}
//Меню и вызов функций
int main() {
	setlocale(LC_ALL, "RUS");
	Cards* adapters = (Cards*)malloc(MAX_DEVICE * sizeof(Cards));
	int action;
	int count = 0;
	int sortCr = 0;
	int cnt;
	char filename[] = "database.txt";

	do {
		printf("Меню:\n");
		printf("1. Создание новой записи\n");
		printf("2. Поиск записи по производителю или интерфейсу\n");
		printf("3. Запись всех данных в файл\n");
		printf("4. Чтение всех данных из файла\n");
		printf("5. Сортировка\n");
		printf("6. Изменение записей в файле\n");
		printf("0. Выход\n");
		printf("Выберите действие:\n");
		scanf("%d", &action);

		switch (action) {
		case 1: {
			printf("Сколько записей добавить?\n");
			scanf("%d", &cnt);
			for (int i = 0; i < cnt; i++) {
				printf("Запись %d\n", i + 1);
				int result1 = addCards(adapters, &count, filename);
				if (result1 == 1) {
					printf("\nЗапись добавлена.\n");
				}
				else
					printf("\nОшибка добавления записи\n");
			}
			printf("Файл сохранён.\n");
			saveDevicesToFile(adapters, count, filename);
			break;
		}
		case 2: {
			int searchOption;
			printf("Выберите вариант поиска:\n1. По производитель\n2. По интерфейсу\n");
			scanf("%d", &searchOption);

			char name[20];
			char interface[20];

			if (searchOption == 1 || searchOption == 3) {
				printf("Введите производителя: ");
				scanf("%19s", name);
			}
			if (searchOption == 2 || searchOption == 3) {
				printf("Введите интерфейс подключения: ");
				scanf("%19s", interface);
			}
			Cards results[MAX_DEVICE];
			int foundCount = searchCards(adapters, count, results, name, interface, searchOption);

			if (foundCount > 0) {
				printf("Найдено %d записей:\n", foundCount);
				for (int i = 0; i < foundCount; i++) {
					printf("Производитель: %s, Интерфейс подключения:  %s\n", results[i].name, results[i].interface);
				}
			}
			else {

				printf("Записи не найдены.\n");
			}
			break;
		}
		case 3: {
			int result3 = saveDevicesToFile(adapters, count, filename);
			if (result3 == 1)
				printf("\nДанные успешно сохранены в текстовый файл.\n");
			else if (result3 == 2)
				printf("Ошибка: невозможно открыть файл для записи.\n");
			else
				printf("\nОшибка сохранения данных\n");
			break;
		}
		case 4: {
			int result4 = loadDevicesFromFile(adapters, &count, filename);
			if (result4 == 1)
				printf("\nДанные успешно загружены из текстового файла.\n");
			else if (result4 == 2)
				printf("\nДостигнуто максимальное количество записей.\n");
			else
				printf("\nОшибка считывания данных\n");

			break;
		}

		case 5: {
			printf("Выберите параметр сортировки:\n1. Производитель\n2. Интерфейс \n3. По обоим критериям\n");
			scanf("%d", &sortCr);

			int result7 = bubblesort(adapters, count, sortCr);
			if (result7 == 1) {
				printf("Запись после сортировки\n");
				for (int i = 0; i < count; i++) {
					printf("Производитель: %s,n", adapters[i].name);
				}
			}
			if (result7 == 2) {
				printf("Запись после сортировки\n");
				for (int i = 0; i < count; i++) {
					printf("Интерфейс: %s\n", adapters[i].interface);
				}
				if (result7 == 3) {
					printf("Записи после сортировки:\n");
					for (int i = 0; i < count; i++) {
						printf("Производитель: %s, Интерфейс: %s\n", adapters[i].name, adapters[i].interface);
					}
					break;
				}
			}
		case 6: {

		}
		case 7:
			for (int i = 0; i < count; i++) {
				printf("Производитель: %s, Интерфейс: %s, Скорость передачи: %d, Количество разъемов: %d, USB разветлитель: %d, Модель: %s\n",
					adapters[i].name, adapters[i].interface,
					adapters[i].speed, adapters[i].ports45,
					adapters[i].usb_hub, adapters[i].model);
			}
			break;
		case 0:
			printf("Выход из программы.\n");
			break;
		default:
			printf("Неверный выбор.\n");
		}
		} 
	}while (action != 0);
}