#define _CRT_SECURE_NO_DEPRECATE
#define MAX_DEVICE 50
#include <locale.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
NetworkCard[];

//��������� ������
typedef struct {
	char name[50];
	char interface[50];
	int speed;
	int ports45;
	bool usb_hub;
	char model[50];
} Cards;

//���������� � ����
int addCards(Cards adapters[], int* count, char const* filename) {

	printf(" ���������� ����� ������ \n");

	// ���� ��������
	printf("������� �������������: ");
	scanf("%s", adapters[*count].name);

	printf("������� ��������� (��������, PCI-E, USB_3.0, Type-C): ");
	scanf("%s", adapters[*count].interface);

	printf("������� �������� (� ����/�): ");
	scanf("%d", &adapters[*count].speed);

	printf("������� ���������� ������: ");
	scanf("%d", &adapters[*count].ports45);

	printf("������������ usb (��/���): ");
	while (scanf("%d", &adapters[*count].usb_hub) != 1 || (adapters[*count].usb_hub != 0 && adapters[*count].usb_hub != 1)) {
		printf("������: ������� 1 - (��) ��� 0 - (���).\n");
		while (getchar() != '\n'); // �������� ������ �����
	}

	printf("������� ������: ");
	scanf("%s", adapters[*count].model);

	printf("������ ������� ��������� � ���� ������!\n");

	(*count)++;

	return 1;
}

//����� �������
int searchCards(const Cards adapters[], int count, Cards results[], char* name, char* interface, int searchOption) {
	int resultCount = 0;

	for (int i = 0; i < count; i++) {
		int names = (searchOption == 1 || searchOption == 3) && strcmp(adapters[i].name, name) == 0;
		int interfaces = (searchOption == 2 || searchOption == 3) && strcmp(adapters[i].interface, interface) == 0;

		if (searchOption == 1 && names)
			results[resultCount++] = adapters[i]; // ���������� ��������� �� ������ � ���������� ������ � ����� ������
		else if (searchOption == 2 && interfaces)
			results[resultCount++] = adapters[i];
		else if (searchOption == 3 && names && interfaces)
			results[resultCount++] = adapters[i];
	}
	return resultCount;
}

//������ � ����
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

//������ �� �����
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

//����������
int bubblesort(Cards* adapters, int count, int criterion) {
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - i - 1; j++) {
			int swapNeeded = 0;

			if (criterion == 1) {
				//���������� �� �������������
				if (adapters[j].name < adapters[j + 1].name) {
					swapNeeded = 1;
				}
			}
			else if (criterion == 2) {
				//���������� �������� �������� 
				if (adapters[j].interface > adapters[j + 1].interface) {
					swapNeeded = 1;
				}
			}
			else if (criterion == 3) {
				//���������� �� 2-�� ���������
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

//��������� �������
int editDevice(Cards adapters[], int count, const char* name) {
	int found = 0;
	for (int i = 0; i < count; i++) {
		if (strcmp(adapters[i].name, name) == 0) {
			found = 1;
			printf("�������������� ������ ��� ������������� %s\n", name);
			int choice;
			do {
				printf("\n�������� ���� ��� ���������:\n");
				printf("1. ��������\n");
				printf("2. ���������: \n");
				printf("3. ��������\n");
				printf("4. ���������� ������\n");
				printf("5. ������������ usb\n");
				printf("6. ������\n");
				printf("0. �����\n");
				printf("��� �����: ");
				scanf("%d", &choice);
				switch (choice) {
				case 1:
					printf("������� ��������\n");
					scanf("%s", adapters[i].name);
					break;
				case 2:
					printf("������� ���������\n");
					scanf("%s", adapters[i].interface);
					break;
				case 3:
					printf("������� ��������\n");
					scanf("%d", &adapters[i].speed);
					break;
				case 4:
					printf("������� ���������� ������\n");
					scanf("%d", &adapters[i].ports45);
					break;
				case 5:
					printf("��������� ������������\n");
					scanf("%s", &adapters[i].usb_hub);
					break;
				case 6:
					printf("������� ������\n");
					scanf("%s", adapters[i].model);
					break;
				case 0:
					printf("����� �� ������ ��������������.\n");
					break;
				default:
					printf("�������� �����. ���������� �����.\n");
				}

				if (choice != 0) {
					return 1;
				}
			} while (choice != 0);

			return 0;
		}
	}
	if (!found) {
		printf("������ �� �������.\n");
	}
}
//���� � ����� �������
int main() {
	setlocale(LC_ALL, "RUS");
	Cards* adapters = (Cards*)malloc(MAX_DEVICE * sizeof(Cards));
	int action;
	int count = 0;
	int sortCr = 0;
	int cnt;
	char filename[] = "database.txt";

	do {
		printf("����:\n");
		printf("1. �������� ����� ������\n");
		printf("2. ����� ������ �� ������������� ��� ����������\n");
		printf("3. ������ ���� ������ � ����\n");
		printf("4. ������ ���� ������ �� �����\n");
		printf("5. ����������\n");
		printf("6. ��������� ������� � �����\n");
		printf("0. �����\n");
		printf("�������� ��������:\n");
		scanf("%d", &action);

		switch (action) {
		case 1: {
			printf("������� ������� ��������?\n");
			scanf("%d", &cnt);
			for (int i = 0; i < cnt; i++) {
				printf("������ %d\n", i + 1);
				int result1 = addCards(adapters, &count, filename);
				if (result1 == 1) {
					printf("\n������ ���������.\n");
				}
				else
					printf("\n������ ���������� ������\n");
			}
			printf("���� �������.\n");
			saveDevicesToFile(adapters, count, filename);
			break;
		}
		case 2: {
			int searchOption;
			printf("�������� ������� ������:\n1. �� �������������\n2. �� ����������\n");
			scanf("%d", &searchOption);

			char name[20];
			char interface[20];

			if (searchOption == 1 || searchOption == 3) {
				printf("������� �������������: ");
				scanf("%19s", name);
			}
			if (searchOption == 2 || searchOption == 3) {
				printf("������� ��������� �����������: ");
				scanf("%19s", interface);
			}
			Cards results[MAX_DEVICE];
			int foundCount = searchCards(adapters, count, results, name, interface, searchOption);

			if (foundCount > 0) {
				printf("������� %d �������:\n", foundCount);
				for (int i = 0; i < foundCount; i++) {
					printf("�������������: %s, ��������� �����������:  %s\n", results[i].name, results[i].interface);
				}
			}
			else {

				printf("������ �� �������.\n");
			}
			break;
		}
		case 3: {
			int result3 = saveDevicesToFile(adapters, count, filename);
			if (result3 == 1)
				printf("\n������ ������� ��������� � ��������� ����.\n");
			else if (result3 == 2)
				printf("������: ���������� ������� ���� ��� ������.\n");
			else
				printf("\n������ ���������� ������\n");
			break;
		}
		case 4: {
			int result4 = loadDevicesFromFile(adapters, &count, filename);
			if (result4 == 1)
				printf("\n������ ������� ��������� �� ���������� �����.\n");
			else if (result4 == 2)
				printf("\n���������� ������������ ���������� �������.\n");
			else
				printf("\n������ ���������� ������\n");

			break;
		}

		case 5: {
			printf("�������� �������� ����������:\n1. �������������\n2. ��������� \n3. �� ����� ���������\n");
			scanf("%d", &sortCr);

			int result7 = bubblesort(adapters, count, sortCr);
			if (result7 == 1) {
				printf("������ ����� ����������\n");
				for (int i = 0; i < count; i++) {
					printf("�������������: %s,n", adapters[i].name);
				}
			}
			if (result7 == 2) {
				printf("������ ����� ����������\n");
				for (int i = 0; i < count; i++) {
					printf("���������: %s\n", adapters[i].interface);
				}
				if (result7 == 3) {
					printf("������ ����� ����������:\n");
					for (int i = 0; i < count; i++) {
						printf("�������������: %s, ���������: %s\n", adapters[i].name, adapters[i].interface);
					}
					break;
				}
			}
		case 6: {

		}
		case 7:
			for (int i = 0; i < count; i++) {
				printf("�������������: %s, ���������: %s, �������� ��������: %d, ���������� ��������: %d, USB ������������: %d, ������: %s\n",
					adapters[i].name, adapters[i].interface,
					adapters[i].speed, adapters[i].ports45,
					adapters[i].usb_hub, adapters[i].model);
			}
			break;
		case 0:
			printf("����� �� ���������.\n");
			break;
		default:
			printf("�������� �����.\n");
		}
		} 
	}while (action != 0);
}