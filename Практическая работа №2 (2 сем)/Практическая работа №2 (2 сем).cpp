#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

struct List {
	List* head;
	int data;
	List* tail;
};

struct Client {
	int accountNumber;
	float balance;
	string status;
};

struct ClientList {
	ClientList* head;
	Client data;
	ClientList* tail;
};

void unitedArrays(Client*& unitedArr, Client* arr1, Client* arr2, int size1, int size2, int uniteSize) {
	unitedArr = new Client[uniteSize];
	int i = 0, j = 0, k = 0;
	Client temp;
	for (int i = 0; i <= size1; i++) {
		for (int j = 0; j < size1 - i - 1; j++) {
			if (arr1[j].accountNumber > arr1[j + 1].accountNumber) {
				temp = arr1[j];
				arr1[j] = arr1[j + 1];
				arr1[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i <= size2; i++) {
		for (int j = 0; j < size2 - i - 1; j++) {
			if (arr2[j].accountNumber > arr2[j + 1].accountNumber) {
				temp = arr2[j];
				arr2[j] = arr2[j + 1];
				arr2[j + 1] = temp;
			}
		}
	}
	while (i < size1 && j < size2) {
		if (arr1[i].accountNumber < arr2[j].accountNumber) {
			unitedArr[k] = arr1[i];
			k++;
			i++;
		}
		else {
			unitedArr[k] = arr2[j];
			k++;
			j++;
		}
	}

	while (i < size1) {
		unitedArr[k] = arr1[i];
		k++;
		i++;
	}
	while (j < size2) {
		unitedArr[k] = arr2[j];
		k++;
		j++;
	}
}

void clientArrayOutput(Client* unitedArr, int uniteSize) {
	for (int i = 0; i < uniteSize; i++) {
		cout << unitedArr[i].accountNumber << ' ' << unitedArr[i].balance << ' ' << unitedArr[i].status << '\n';
	}
}

void addClientToEnd(ClientList*& first, ClientList*& last, Client client) {
	ClientList* newNode = new ClientList;
	newNode->data = client;
	newNode->head = last;
	newNode->tail = nullptr;

	if (first == nullptr) {
		first = newNode;
	}
	else {
		last->tail = newNode;
	}

	last = newNode;
}

void unitedLists(ClientList*& unitedList, ClientList* list1, ClientList* list2) {
	ClientList* unitedTail = nullptr;

	while (list1 != nullptr && list2 != nullptr) {
		if (list1->data.accountNumber < list2->data.accountNumber) {
			addClientToEnd(unitedList, unitedTail, list1->data);
			list1 = list1->tail;
		}
		else {
			addClientToEnd(unitedList, unitedTail, list2->data);
			list2 = list2->tail;
		}
	}

	while (list1 != nullptr) {
		addClientToEnd(unitedList, unitedTail, list1->data);
		list1 = list1->tail;
	}

	while (list2 != nullptr) {
		addClientToEnd(unitedList, unitedTail, list2->data);
		list2 = list2->tail;
	}
}

int listIsCycled(List* first) {
	List* fast = first;
	List* slow = first;
	while (fast && fast->tail) {
		slow = slow->tail;
		fast = fast->tail->tail;
		if (slow == fast) {
			return 1;
		}
	}
	return 0;
}

void clientListOutput(ClientList* unitedList) {
	while (unitedList) {
		cout << unitedList->data.accountNumber << ' ' << unitedList->data.balance << ' ' << unitedList->data.status << '\n';
		unitedList = unitedList->tail;
	}
}

void deleteClientList(ClientList*& first) {
	while (first) {
		ClientList* temp = first;
		first = first->tail;
		delete temp;
	}
}

void workWithIDZ() {
	int i;
	Client arr1[3];
	Client arr2[2];
	arr1[0].accountNumber = 1;
	arr1[0].balance = 42155.0;
	arr1[0].status = "счёт активен";
	arr1[1].accountNumber = 5;
	arr1[1].balance = 193214.55;
	arr1[1].status = "счёт активен";
	arr1[2].accountNumber = 3;
	arr1[2].balance = 1.0;
	arr1[2].status = "счёт заблокирован";

	arr2[0].accountNumber = 4;
	arr2[0].balance = 9993.322;
	arr2[0].status = "счёт активен";
	arr2[1].accountNumber = 2;
	arr2[1].balance = 67.76;
	arr2[1].status = "счёт активен";

	Client* unitedArr = nullptr;
	int uniteSize = 5;

	ClientList* list1 = new ClientList;
	list1->data.accountNumber = 1;
	list1->data.balance = 1000;
	list1->data.status = "счёт активен";
	list1->head = nullptr;

	ClientList* subList1_1 = new ClientList;
	subList1_1->data.accountNumber = 3;
	subList1_1->data.balance = 1500;
	subList1_1->data.status = "счёт активен";

	list1->tail = subList1_1;
	subList1_1->head = list1;

	ClientList* subList1_2 = new ClientList;
	subList1_2->data.accountNumber = 5;
	subList1_2->data.balance = 1200;
	subList1_2->data.status = "счёт заблокирован";

	subList1_1->tail = subList1_2;
	subList1_2->head = subList1_1;
	subList1_2->tail = nullptr;

	ClientList* list2 = new ClientList;
	list2->data.accountNumber = 2;
	list2->data.balance = 2000;
	list2->data.status = "счёт активен";
	list2->head = nullptr;

	ClientList* subList2_1 = new ClientList;
	subList2_1->data.accountNumber = 4;
	subList2_1->data.balance = 1700;
	subList2_1->data.status = "счёт активен";

	list2->tail = subList2_1;
	subList2_1->head = list2;
	subList2_1->tail = nullptr;

	ClientList* unitedList = nullptr;
	do {
		system("cls");
		cout << "Что вы хотите сделать: 1 - вывести массивы клиентов, 2 - вывести списки клиентов, 3 - объединить массивы и списки, 0 - для выхода" << '\n';
		cin >> i;
		switch (i) {
		case 1:
			system("cls");
			cout << "Первый массив:" << '\n';
			clientArrayOutput(arr1, 3);
			cout << '\n';
			cout << "Второй массив:" << '\n';
			clientArrayOutput(arr2, 2);
			system("pause");
			break;
		case 2:
			system("cls");
			cout << "Первый список:" << '\n';
			clientListOutput(list1);
			cout << '\n';
			cout << "Второй список:" << '\n';
			clientListOutput(list2);
			system("pause");
			break;
		case 3:
			system("cls");
			delete[] unitedArr;
			unitedArr = nullptr;
			deleteClientList(unitedList);
			unitedList = nullptr;

			unitedArrays(unitedArr, arr1, arr2, 3, 2, uniteSize);
			unitedLists(unitedList, list1, list2);
			cout << "Объединённый массив:" << '\n';
			clientArrayOutput(unitedArr, uniteSize);
			cout << '\n';
			cout << "Объединённый список:" << '\n';
			clientListOutput(unitedList);
			system("pause");
			break;
		}
	} while (i != 0);

	delete[] unitedArr;
	deleteClientList(list1);
	deleteClientList(list2);
	deleteClientList(unitedList);
}

List* createListlengthN(int n) {
	List* curr = 0;
	List* next = 0;
	for (int i = 1; i <= n; i++) {
		curr = new List;
		curr->data = rand() % 100;
		curr->tail = next;
		if (next) {
			next->head = curr;
		}
		next = curr;
	}
	if (curr != nullptr) {
		curr->head = nullptr;
	}
	return curr;
}

List* createListFill() {
	cin.ignore();
	List* curr = 0;
	List* next = 0;
	string line;
	getline(cin, line);
	istringstream numbers(line);
	int i;
	while (numbers >> i) {
		curr = new List;
		curr->data = i;
		curr->tail = next;
		if (next) {
			next->head = curr;
		}
		next = curr;
		curr->head = nullptr;
	}
	return curr;
}

void listOutput(List* first) {
	while (first) {
		cout << first->data << ' ';
		first = first->tail;
	}
}

List* listLastElement(List* first) {
	if (first == nullptr) return nullptr;
	List* current = first;
	while (current->tail != nullptr) {
		current = current->tail;
	}
	return current;
}

void listOutputReversed(List* last) {
	while (last) {
		cout << last->data << ' ';
		last = last->head;
	}
}

int listlength(List* first) {
	int len = 0;
	while (first) {
		len++;
		first = first->tail;
	}
	return len;
}

List* listElement(List* first, int number) {
	int index = --number;
	while (first && (index--)) {
		first = first->tail;
	}
	return first;
}

void deleteListElement(List*& first, int number) {
	if (first == nullptr) {
		return;
	}

	int index = --number;

	if (index == 0) {
		List* element = first->tail;
		delete first;
		first = element;
		if (first != nullptr) {
			first->head = nullptr;
		}
		return;
	}

	List* element = listElement(first, index);
	if (element == nullptr || element->tail == nullptr) {
		return;
	}

	List* dElement = element->tail;
	element->tail = dElement->tail;
	if (dElement->tail != nullptr) {
		dElement->tail->head = element;
	}
	delete dElement;
}

void deleteListElementValue(List*& first, int value) {
	List* element = first;
	int k = 0;

	while (element != nullptr) {
		List* next = element->tail;
		if (element->data == value) {
			k++;
			if (element->head != nullptr) {
				element->head->tail = element->tail;
			}
			else {
				first = element->tail;
			}
			if (element->tail != nullptr) {
				element->tail->head = element->head;
			}
			delete element;
		}
		element = next;
	}
	if (k == 0) {
		cout << "Элемента с данным значением не найдено" << '\n';
	}
	else {
		cout << "Элемент(ы) со значением " << value << " удалены" << '\n';
	}
}

List* listElementValue(List* first, int value) {
	List* element = first;
	while (element) {
		if (element->data == value) {
			return element;
		}
		element = element->tail;
	}
	cout << "Элемента с данным значением не найдено" << '\n';
	return 0;
}

List* listElementValueTime(List* first, int value) {
	List* element = first;
	while (element) {
		if (element->data == value) {
			return element;
		}
		element = element->tail;
	}
	return 0;
}

List* addElement(List*& first, int number, int value) {
	List* newElem = new List;
	newElem->data = value;
	newElem->head = nullptr;
	newElem->tail = nullptr;

	if (first == nullptr) {
		first = newElem;
		return newElem;
	}

	int index = --number;
	if (index == 0) {
		first->head = newElem;
		newElem->tail = first;
		first = newElem;
		return newElem;
	}

	List* elem = first;
	while (elem->tail && (--index)) {
		elem = elem->tail;
	}

	newElem->tail = elem->tail;
	newElem->head = elem;
	if (elem->tail != nullptr) {
		elem->tail->head = newElem;
	}
	elem->tail = newElem;
	return newElem;
}

void changeElements(List*& first, int n1, int n2) {
	if (n1 == n2) {
		return;
	}

	List* elem1 = listElement(first, n1);
	List* elem2 = listElement(first, n2);

	if (elem1 == nullptr || elem2 == nullptr) {
		cout << "Один из элементов не найден" << '\n';
		return;
	}

	List* rightElem1 = elem1->head;
	List* leftElem1 = elem1->tail;
	List* rightElem2 = elem2->head;
	List* leftElem2 = elem2->tail;

	if (elem1->tail == elem2) {
		elem1->tail = leftElem2;
		elem1->head = elem2;
		elem2->tail = elem1;
		elem2->head = rightElem1;
		if (leftElem2) {
			leftElem2->head = elem1;
		}
		if (rightElem1) {
			rightElem1->tail = elem2;
		}
	}
	else if (elem2->tail == elem1) {
		elem2->tail = leftElem1;
		elem2->head = elem1;
		elem1->tail = elem2;
		elem1->head = rightElem2;
		if (leftElem1) {
			leftElem1->head = elem2;
		}
		if (rightElem2) {
			rightElem2->tail = elem1;
		}
	}
	else {
		if (rightElem1) {
			rightElem1->tail = elem2;
		}
		if (leftElem1) {
			leftElem1->head = elem2;
		}
		if (rightElem2) {
			rightElem2->tail = elem1;
		}
		if (leftElem2) {
			leftElem2->head = elem1;
		}
		elem1->head = rightElem2;
		elem1->tail = leftElem2;
		elem2->head = rightElem1;
		elem2->tail = leftElem1;
	}

	if (first == elem1) {
		first = elem2;
	}
	else if (first == elem2) {
		first = elem1;
	}
}

void deleteList(List*& first) {
	while (first) {
		List* temp = first;
		first = first->tail;
		delete temp;
	}
}

int* createArrayLengthN(int length) {
	int* arr = new int[length];
	for (int i = 0; i < length; i++) {
		arr[i] = rand() % 100;
	}
	return arr;
}

int* createArrayFill(int& length1) {
	cin.ignore();
	int length = 1;
	int numbers = 0;
	int* arr = new int[length];
	int n;
	string line;
	getline(cin, line);
	istringstream number(line);
	while (number >> n) {
		if (length <= numbers) {
			length++;
			int* newArray = new int[length];
			for (int i = 0; i < length - 1; i++) {
				newArray[i] = arr[i];
			}
			delete[] arr;
			arr = newArray;
		}
		arr[numbers] = n;
		numbers++;
	}
	length1 = numbers;
	return arr;
}

void deleteArrayElement(int*& arr, int& length, int number) {
	if (arr == nullptr || length <= 0) {
		return;
	}

	int index = --number;
	if (index < 0 || index >= length) {
		return;
	}

	int* newArray = nullptr;
	if (length - 1 > 0) {
		newArray = new int[length - 1];
	}

	for (int i = 0, j = 0; i < length; i++) {
		if (i == index) {
			continue;
		}
		newArray[j] = arr[i];
		j++;
	}

	delete[] arr;
	arr = newArray;
	length--;
}

void deleteArrayElementValue(int*& arr, int& length, int value) {
	int k = 0;
	int index = 0;
	for (int i = 0; i < length; i++) {
		if (arr[i] == value) {
			k++;
			index = i;
			break;
		}
	}

	if (k == 0) {
		cout << "Элемент с таким значением не найден!" << '\n';
	}
	else {
		deleteArrayElement(arr, length, index + 1);
	}
}

void arrayOutput(int* arr, int length) {
	for (int i = 0; i < length; i++) {
		cout << arr[i] << ' ';
	}
}

void addArrayElement(int*& arr, int& length, int value, int number) {
	int index = --number;
	int* newArray = new int[length + 1];
	for (int i = 0, j = 0; i < length + 1; i++, j++) {
		if (i == index) {
			newArray[i] = value;
			--j;
			continue;
		}
		newArray[i] = arr[j];

	}
	delete[] arr;
	arr = newArray;
	length++;
}

void swapArrayElements(int* arr, int n1, int n2) {
	int index1 = --n1;
	int index2 = --n2;
	int temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;
}

void arrayElementByValue(int* arr, int length, int value) {
	int k = 0;
	for (int i = 0; i < length; i++) {
		if (arr[i] == value) {
			cout << "Ваш элемент: " << value << " найден, он находится на " << i + 1 << " позиции" << '\n';
			k++;
		}
	}
	if (k == 0) {
		cout << "Элемент с таким значением не найден!" << '\n';
	}
}

void arrayElementByValueTime(int* arr, int length, int value) {
	for (int i = 0; i < length; i++) {
		if (arr[i] == value) {
			i = length;
		}
	}
}

void workWithList() {
	int j;
	do {
		system("cls");
		cout << "Что вы хотите сделать: 1 - создать список из N рандомных элементов, 2 - создать список и заполнить его вручную, 0 - для выхода" << '\n';
		cin >> j;
		switch (j) {
		case 1: {
			int w;
			system("cls");
			int k;
			cout << "Введите N (размер списка):" << '\n';
			cin >> k;
			List* list = createListlengthN(k);
			cout << "Список создан" << '\n' << '\n';
			system("pause");
			system("cls");
			do {
				cout << "Вы работаете со списком... " << '\n' << '\n';
				cout << "Что вы хотите сделать:" << '\n';
				cout << "1 - вывести список" << '\n';
				cout << "2 - вставить новый элемент в список" << '\n';
				cout << "3 - удалить элемент из списка(по индексу)" << '\n';
				cout << "4 - удалить элемент из списка (по значению)" << '\n';
				cout << "5 - поменять 2 элемента списка местами" << '\n';
				cout << "6 - получить элемент из списка (по индексу)" << '\n';
				cout << "7 - получить элемент из списка (по значению)" << '\n';
				cout << "8 - показать время вставки и удаления элемента из списка" << '\n';
				cout << "9 - показать время поиска эллемента списка по значению и по номеру" << '\n';
				cout << "0 - для выхода" << '\n';
				cin >> w;
				switch (w) {
				case 1:
					system("cls");
					cout << "Ваш список :" << '\n';
					listOutput(list);
					cout << '\n';
					system("pause");
					system("cls");
					break;
				case 2:
					system("cls");
					int number1;
					int value1;
					cout << "Введите номер элемента в новом списке: (от 1 до " << listlength(list) + 1 << ')' << '\n';
					cin >> number1;
					while (number1 > (listlength(list) + 1) || number1 < 1) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << listlength(list) + 1 << ')' << '\n';
						cin >> number1;
					}
					cout << "Введите значение элемента в новом списке:" << '\n';
					cin >> value1;
					addElement(list, number1, value1);
					system("pause");
					system("cls");
					break;
				case 3:
					system("cls");
					int number2;
					cout << "Введите порядковый номер элемента для удаления: (от 1 до " << listlength(list) << ')' << '\n';
					cin >> number2;
					while (number2 > listlength(list) || number2 < 1) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << listlength(list) << ')' << '\n';
						cin >> number2;
					}
					if (listlength(list) == 1) {
						cout << "Удалить данный список и создать новый: 1 - да, 0 - нет" << '\n';
						int choice;
						cin >> choice;
						cout << '\n';
						if (choice == 0) {
							break;
						}
						if (choice == 1) {
							w = 0;
							break;
						}
					}
					deleteListElement(list, number2);
					system("pause");
					system("cls");
					break;
				case 4:
					system("cls");
					int number3;
					cout << "Введите значение элемента, который вы хотите удалить:" << '\n';
					cin >> number3;
					if (listlength(list) == 1) {
						cout << "Удалить данный массив и создать новый: 1 - да, 0 - нет" << '\n';
						int choice;
						cin >> choice;
						cout << '\n';
						if (choice == 0) {
							break;
						}
						if (choice == 1) {
							w = 0;
							break;
						}
					}
					deleteListElementValue(list, number3);
					system("pause");
					system("cls");
					break;
				case 5:
					system("cls");
					int number4, number5;
					cout << "Введите порядковые номера тех элементов, которые вы хотите поменять местами, допустимые значения: 1 - " << listlength(list) << ')' << '\n';
					cin >> number4;
					cout << '\n';
					cin >> number5;
					while (number4 < 1 || number4 > listlength(list) || number5 < 1 || number5 > listlength(list)) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << listlength(list) << ')' << '\n';
						cin >> number4;
						cout << '\n';
						cin >> number5;
					}
					changeElements(list, number4, number5);
					system("pause");
					system("cls");
					break;
				case 6:
					system("cls");
					int number6;
					cout << "Введите номер элемента для получения: (от 1 до " << listlength(list) << ')' << '\n';
					cin >> number6;
					while (number6 > listlength(list) || number6 < 1) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << listlength(list) << ')' << '\n';
						cin >> number6;
					}
					cout << "Адрес данного элемента: ";
					cout << listElement(list, number6) << '\n';
					cout << "Значение данного элемента: ";
					cout << listElement(list, number6)->data << '\n';
					system("pause");
					system("cls");
					break;
				case 7:
					system("cls");
					int number7;
					cout << "Введите значение элемента для получения:" << '\n';
					cin >> number7;
					if (listElementValue(list, number7) != 0) {
						cout << "Адрес данного элемента: " << '\n';
						cout << listElementValue(list, number7) << '\n';
						cout << "Значение данного элемента: " << '\n';
						cout << listElementValue(list, number7)->data << '\n';
					}
					system("pause");
					system("cls");
					break;
				case 8: {
					system("cls");
					auto start1 = high_resolution_clock::now();
					addElement(list, 1, 1);
					auto end1 = high_resolution_clock::now();
					auto duration1 = duration_cast<nanoseconds>(end1 - start1).count();
					cout << "Вставка элемента завершилась за " << duration1 << " наносекунд.\n";
					auto start2 = high_resolution_clock::now();
					deleteListElement(list, 1);
					auto end2 = high_resolution_clock::now();
					auto duration2 = duration_cast<nanoseconds>(end2 - start2).count();
					cout << "Удаление элемента завершилось за " << duration2 << " наносекунд.\n";
					system("pause");
					system("cls");
					break;
				}
				case 9:
					system("cls");
					int number8;
					int value2;
					cout << "Введите номер элемента, который вы хотите получить: ";
					cin >> number8;
					while (number8 < 1 || number8 > listlength(list)) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << listlength(list) << ')' << '\n';
						cin >> number8;
					}
					cout << '\n';
					cout << "Введите значение элемента, который вы хотите получить: ";
					cin >> value2;
					cout << '\n';
					auto start3 = high_resolution_clock::now();
					listElement(list, number8);
					auto end3 = high_resolution_clock::now();
					auto duration3 = duration_cast<nanoseconds>(end3 - start3).count();
					cout << "Получение элемента по номеру завершилось за " << duration3 << " наносекунд.\n";
					auto start4 = high_resolution_clock::now();
					listElementValueTime(list, value2);
					auto end4 = high_resolution_clock::now();
					auto duration4 = duration_cast<nanoseconds>(end4 - start4).count();
					cout << "Получение элемента по значению завершилось за " << duration4 << " наносекунд.\n";
					system("pause");
					system("cls");
					break;
				}
			} while (w != 0);
			deleteList(list);
			break;
		}
		case 2: {
			int o;
			system("cls");
			cout << "Введите числа через пробел:" << '\n';
			List* list1 = createListFill();
			cout << "Список создан" << '\n';
			system("pause");
			system("cls");
			do {
				cout << "Вы работаете со списком... " << '\n' << '\n';
				cout << "Что вы хотите сделать:" << '\n';
				cout << "1 - вывести список" << '\n';
				cout << "2 - вставить новый элемент в список" << '\n';
				cout << "3 - удалить элемент из списка(по индексу)" << '\n';
				cout << "4 - удалить элемент из списка (по значению)" << '\n';
				cout << "5 - поменять 2 элемента списка местами" << '\n';
				cout << "6 - получить элемент из списка (по индексу)" << '\n';
				cout << "7 - получить элемент из списка (по значению)" << '\n';
				cout << "8 - показать время вставки и удаления элемента из списка" << '\n';
				cout << "9 - показать время поиска эллемента списка по значению и по номеру" << '\n';
				cout << "0 - для выхода" << '\n';
				cin >> o;
				switch (o) {
				case 1:
					system("cls");
					cout << "Ваш список :" << '\n';
					listOutput(list1);
					cout << '\n';
					system("pause");
					system("cls");
					break;
				case 2:
					system("cls");
					int number;
					int value2;
					cout << "Введите номер элемента в новом списке: (от 1 до " << listlength(list1) + 1 << ')' << '\n';
					cin >> number;
					while (number > (listlength(list1) + 1) || number < 1) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << listlength(list1) + 1 << ')' << '\n';
						cin >> number;
					}
					cout << "Введите значение элемента в новом списке:" << '\n';
					cin >> value2;
					addElement(list1, number, value2);
					system("pause");
					system("cls");
					break;
				case 3:
					system("cls");
					int number1;
					cout << "Введите порядковый номер элемента для удаления: (от 1 до " << listlength(list1) << ')' << '\n';
					cin >> number1;
					while (number1 > listlength(list1) || number1 < 1) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << listlength(list1) << ')' << '\n';
						cin >> number1;
					}
					if (listlength(list1) == 1) {
						cout << "Удалить данный список и создать новый: 1 - да, 0 - нет" << '\n';
						int choice;
						cin >> choice;
						cout << '\n';
						if (choice == 0) {
							break;
						}
						if (choice == 1) {
							o = 0;
							break;
						}
					}
					deleteListElement(list1, number1);
					system("pause");
					system("cls");
					break;
				case 4:
					system("cls");
					int number2;
					cout << "Введите значение элемента, который вы хотите удалить:" << '\n';
					cin >> number2;
					if (listlength(list1) == 1) {
						cout << "Удалить данный массив и создать новый: 1 - да, 0 - нет" << '\n';
						int choice;
						cin >> choice;
						cout << '\n';
						if (choice == 0) {
							break;
						}
						if (choice == 1) {
							o = 0;
							break;
						}
					}
					deleteListElementValue(list1, number2);
					system("pause");
					system("cls");
					break;
				case 5:
					system("cls");
					int number3, number4;
					cout << "Введите порядковые номера тех элементов, которые вы хотите поменять местами, допустимые значения: 1 - " << listlength(list1) << ')' << '\n';
					cin >> number3;
					cout << '\n';
					cin >> number4;
					while (number3 < 1 || number3 > listlength(list1) || number4 < 1 || number4 > listlength(list1)) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << listlength(list1) << ')' << '\n';
						cin >> number3;
						cout << '\n';
						cin >> number4;
					}
					changeElements(list1, number3, number4);
					system("pause");
					system("cls");
					break;
				case 6:
					system("cls");
					int number5;
					cout << "Введите номер элемента для получения: (от 1 до " << listlength(list1) << ')' << '\n';
					cin >> number5;
					while (number5 > listlength(list1) || number5 < 1) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << listlength(list1) << ')' << '\n';
						cin >> number5;
					}
					cout << "Адрес данного элемента: ";
					cout << listElement(list1, number5) << '\n';
					cout << "Значение данного элемента: ";
					cout << listElement(list1, number5)->data << '\n';
					system("pause");
					system("cls");
					break;
				case 7:
					system("cls");
					int number6;
					cout << "Введите значение элемента для получения:" << '\n';
					cin >> number6;
					if (listElementValue(list1, number6) != 0) {
						cout << "Адрес данного элемента: " << '\n';
						cout << listElementValue(list1, number6) << '\n';
						cout << "Значение данного элемента: " << '\n';
						cout << listElementValue(list1, number6)->data << '\n';
					}
					system("pause");
					system("cls");
					break;
				case 8: {
					system("cls");
					auto start1 = high_resolution_clock::now();
					addElement(list1, 1, 1);
					auto end1 = high_resolution_clock::now();
					auto duration1 = duration_cast<nanoseconds>(end1 - start1).count();
					cout << "Вставка элемента завершилась за " << duration1 << " наносекунд.\n";
					auto start2 = high_resolution_clock::now();
					deleteListElement(list1, 1);
					auto end2 = high_resolution_clock::now();
					auto duration2 = duration_cast<nanoseconds>(end2 - start2).count();
					cout << "Удаление элемента завершилось за " << duration2 << " наносекунд.\n";
					system("pause");
					system("cls");
					break;
				}
				case 9:
					system("cls");
					int number8;
					int value3;
					cout << "Введите номер элемента, который вы хотите получить: ";
					cin >> number8;
					while (number8 < 1 || number8 > listlength(list1)) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << listlength(list1) << ')' << '\n';
						cin >> number8;
					}
					cout << '\n';
					cout << "Введите значение элемента, который вы хотите получить: ";
					cin >> value3;
					cout << '\n';
					auto start3 = high_resolution_clock::now();
					listElement(list1, number8);
					auto end3 = high_resolution_clock::now();
					auto duration3 = duration_cast<nanoseconds>(end3 - start3).count();
					cout << "Получение элемента по номеру завершилось за " << duration3 << " наносекунд.\n";
					auto start4 = high_resolution_clock::now();
					listElementValueTime(list1, value3);
					auto end4 = high_resolution_clock::now();
					auto duration4 = duration_cast<nanoseconds>(end4 - start4).count();
					cout << "Получение элемента по значению завершилось за " << duration4 << " наносекунд.\n";
					system("pause");
					system("cls");
					break;
				}
			} while (o != 0);
			deleteList(list1);
			break;
		}
		}
	} while (j != 0);
}

void workWithArray() {
	int j;
	do {
		system("cls");
		cout << "Что вы хотите сделать: 1 - создать массив из N рандомных элементов, 2 - создать массив и заполнить его вручную, 0 - для выхода" << '\n';
		cin >> j;
		switch (j) {
		case 1: {
			int w;
			system("cls");
			int length;
			cout << "Введите N (размер массива):" << '\n';
			cin >> length;
			int* array = createArrayLengthN(length);
			cout << "Массив создан" << '\n' << '\n';
			system("pause");
			system("cls");
			do {
				cout << "Вы работаете с массивом... " << '\n' << '\n';
				cout << "Что вы хотите сделать:" << '\n';
				cout << "1 - вывести массив" << '\n';
				cout << "2 - вставить новый элемент в массив" << '\n';
				cout << "3 - удалить элемент из массива(по индексу)" << '\n';
				cout << "4 - удалить элемент из массива (по значению)" << '\n';
				cout << "5 - поменять 2 элемента массива местами" << '\n';
				cout << "6 - получить элемент из массива (по индексу)" << '\n';
				cout << "7 - получить элемент из массива (по значению)" << '\n';
				cout << "8 - показать время вставки и удаления элемента из динамического массива" << '\n';
				cout << "9 - показать время поиска эллемента динамического массива по значению и по номеру" << '\n';
				cout << "0 - для выхода" << '\n';
				cin >> w;
				switch (w) {
				case 1:
					system("cls");
					cout << "Ваш массив :" << '\n';
					arrayOutput(array, length);
					cout << '\n';
					system("pause");
					system("cls");
					break;
				case 2:
					system("cls");
					int number;
					int value;
					cout << "Введите номер нового элемента: (от 1 до " << length + 1 << ')' << '\n';
					cin >> number;
					while (number > length + 1 || number < 1) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << length + 1 << ')' << '\n';
						cin >> number;
					}
					cout << "Введите значение нового элемента:" << '\n';
					cin >> value;
					addArrayElement(array, length, value, number);
					system("pause");
					system("cls");
					break;
				case 3:
					system("cls");
					int number1;
					if (length == 0) {
						cout << "Массив пуст!" << '\n';
						system("pause");
						system("cls");
						break;
					}
					cout << "Введите номер элемента для удаления: (от 1 до " << length << ')' << '\n';
					cin >> number1;
					while (number1 > length || number1 < 1) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << length << ')' << '\n';
						cin >> number1;
					}
					deleteArrayElement(array, length, number1);
					system("pause");
					system("cls");
					break;
				case 4:
					system("cls");
					int number2;
					cout << "Введите значение элемента, который вы хотите удалить:" << '\n';
					cin >> number2;
					deleteArrayElementValue(array, length, number2);
					system("pause");
					system("cls");
					break;
				case 5:
					system("cls");
					int number4, number5;
					cout << "Введите порядковые номера тех элементов, которые вы хотите поменять местами, допустимые значения:" << '\n';
					cin >> number4;
					cout << '\n';
					cin >> number5;
					while (number4 < 1 || number4 > length || number5 < 1 || number5 > length) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << length << ')' << '\n';
						cin >> number4;
						cout << '\n';
						cin >> number5;
					}
					swapArrayElements(array, number4, number5);
					system("pause");
					system("cls");
					break;
				case 6:
					system("cls");
					int number6;
					cout << "Введите номер элемента для получения: (от 1 до " << length << ')' << '\n';
					cin >> number6;
					while (number6 > length || number6 < 1) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << length << ')' << '\n';
						cin >> number6;
					}
					cout << "Значение данного элемента: ";
					--number6;
					cout << array[number6] << '\n';
					system("pause");
					system("cls");
					break;
				case 7:
					system("cls");
					int number7;
					cout << "Введите значение элемента для получения:" << '\n';
					cin >> number7;
					arrayElementByValue(array, length, number7);
					system("pause");
					system("cls");
					break;

				case 8: {
					system("cls");
					auto start1 = high_resolution_clock::now();
					addArrayElement(array, length, 1, 1);
					auto end1 = high_resolution_clock::now();
					auto duration1 = duration_cast<nanoseconds>(end1 - start1).count();
					cout << "Вставка элемента завершилась за " << duration1 << " наносекунд.\n";
					auto start2 = high_resolution_clock::now();
					deleteArrayElement(array, length, 1);
					auto end2 = high_resolution_clock::now();
					auto duration2 = duration_cast<nanoseconds>(end2 - start2).count();
					cout << "Удаление элемента завершилось за " << duration2 << " наносекунд.\n";
					system("pause");
					system("cls");
					break;
				}
				case 9:
					system("cls");
					int number8;
					int value1;
					cout << "Введите номер элемента, который вы хотите получить: ";
					cin >> number8;
					while (number8 < 1 || number8 > length) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << length << ')' << '\n';
						cin >> number8;
					}
					cout << '\n';
					cout << "Введите значение элемента, который вы хотите получить: ";
					cin >> value1;
					cout << '\n';
					auto start3 = high_resolution_clock::now();
					volatile int temp = array[number8 - 1];
					auto end3 = high_resolution_clock::now();
					auto duration3 = duration_cast<nanoseconds>(end3 - start3).count();
					cout << "Получение элемента по номеру завершилось за " << duration3 << " наносекунд.\n";
					auto start4 = high_resolution_clock::now();
					arrayElementByValueTime(array, length, value1);
					auto end4 = high_resolution_clock::now();
					auto duration4 = duration_cast<nanoseconds>(end4 - start4).count();
					cout << "Получение элемента по значению завершилось за " << duration4 << " наносекунд.\n";
					system("pause");
					system("cls");
					break;
				}
			} while (w != 0);
			delete[] array;
			break;
		}
		case 2: {
			int o;
			system("cls");
			int length1;
			cout << "Введите числа через пробел:" << '\n';
			int* array1 = createArrayFill(length1);
			cout << "Массив создан" << '\n';
			system("pause");
			system("cls");
			do {
				cout << "Вы работаете с массивом... " << '\n' << '\n';
				cout << "Что вы хотите сделать:" << '\n';
				cout << "1 - вывести массив" << '\n';
				cout << "2 - вставить новый элемент в массив" << '\n';
				cout << "3 - удалить элемент из массива(по индексу)" << '\n';
				cout << "4 - удалить элемент из массива (по значению)" << '\n';
				cout << "5 - поменять 2 элемента массива местами" << '\n';
				cout << "6 - получить элемент из массива (по индексу)" << '\n';
				cout << "7 - получить элемент из массива (по значению)" << '\n';
				cout << "8 - показать время вставки и удаления элемента из динамического массива" << '\n';
				cout << "9 - показать время поиска эллемента динамического массива по значению и по номеру" << '\n';
				cout << "0 - для выхода" << '\n';
				cin >> o;
				switch (o) {
				case 1:
					system("cls");
					cout << "Ваш массив :" << '\n';
					arrayOutput(array1, length1);
					cout << '\n';
					system("pause");
					system("cls");
					break;
				case 2:
					system("cls");
					int number;
					int value;
					cout << "Введите номер нового элемента: (от 1 до " << length1 + 1 << ')' << '\n';
					cin >> number;
					while (number > length1 + 1 || number < 1) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << length1 + 1 << ')' << '\n';
						cin >> number;
					}
					cout << "Введите значение нового элемента:" << '\n';
					cin >> value;
					addArrayElement(array1, length1, value, number);
					system("pause");
					system("cls");
					break;
				case 3:
					system("cls");
					int number1;
					if (length1 == 0) {
						cout << "Массив пуст!" << '\n';
						system("pause");
						system("cls");
						break;
					}
					cout << "Введите номер элемента для удаления: (от 1 до " << length1 << ')' << '\n';
					cin >> number1;
					while (number1 > length1 || number1 < 1) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << length1 << ')' << '\n';
						cin >> number1;
					}
					deleteArrayElement(array1, length1, number1);
					system("pause");
					system("cls");
					break;
				case 4:
					system("cls");
					int number2;
					cout << "Введите значение элемента, который вы хотите удалить:" << '\n';
					cin >> number2;
					deleteArrayElementValue(array1, length1, number2);
					system("pause");
					system("cls");
					break;
				case 5:
					system("cls");
					int number4, number5;
					cout << "Введите порядковые номера тех элементов, которые вы хотите поменять местами, допустимые значения:" << '\n';
					cin >> number4;
					cout << '\n';
					cin >> number5;
					while (number4 < 1 || number4 > length1 || number5 < 1 || number5 > length1) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << length1 << ')' << '\n';
						cin >> number4;
						cout << '\n';
						cin >> number5;
					}
					swapArrayElements(array1, number4, number5);
					system("pause");
					system("cls");
					break;
				case 6:
					system("cls");
					int number6;
					cout << "Введите номер элемента для получения: (от 1 до " << length1 << ')' << '\n';
					cin >> number6;
					while (number6 > length1 || number6 < 1) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << length1 << ')' << '\n';
						cin >> number6;
					}
					cout << "Значение данного элемента: ";
					--number6;
					cout << array1[number6] << '\n';
					system("pause");
					system("cls");
					break;
				case 7:
					system("cls");
					int number7;
					cout << "Введите значение элемента для получения:" << '\n';
					cin >> number7;
					arrayElementByValue(array1, length1, number7);
					system("pause");
					system("cls");
					break;
				case 8: {
					system("cls");
					auto start1 = high_resolution_clock::now();
					addArrayElement(array1, length1, 1, 1);
					auto end1 = high_resolution_clock::now();
					auto duration1 = duration_cast<nanoseconds>(end1 - start1).count();
					cout << "Вставка элемента завершилась за " << duration1 << " наносекунд.\n";
					auto start2 = high_resolution_clock::now();
					deleteArrayElement(array1, length1, 1);
					auto end2 = high_resolution_clock::now();
					auto duration2 = duration_cast<nanoseconds>(end2 - start2).count();
					cout << "Удаление элемента завершилось за " << duration2 << " наносекунд.\n";
					system("pause");
					system("cls");
					break;
				}
				case 9:
					system("cls");
					int number8;
					int value1;
					cout << "Введите номер элемента, который вы хотите получить: ";
					cin >> number8;
					while (number8 < 1 || number8 > length1) {
						cout << "Введено неправильное значение номера, допустимые значения: 1 - " << length1 << ')' << '\n';
						cin >> number8;
					}
					cout << '\n';
					cout << "Введите значение элемента, который вы хотите получить: ";
					cin >> value1;
					cout << '\n';
					auto start3 = high_resolution_clock::now();
					volatile int temp = array1[number8 - 1];
					auto end3 = high_resolution_clock::now();
					auto duration3 = duration_cast<nanoseconds>(end3 - start3).count();
					cout << "Получение элемента по номеру завершилось за " << duration3 << " наносекунд.\n";
					auto start4 = high_resolution_clock::now();
					arrayElementByValueTime(array1, length1, value1);
					auto end4 = high_resolution_clock::now();
					auto duration4 = duration_cast<nanoseconds>(end4 - start4).count();
					cout << "Получение элемента по значению завершилось за " << duration4 << " наносекунд.\n";
					system("pause");
					system("cls");
					break;
				}
			} while (o != 0);
			delete[] array1;
			break;
		}
		}
	} while (j != 0);
}

int main() {
	setlocale(0, "");
	srand(time(NULL));
	int n;
	do {
		system("cls");
		cout << "С чем вы хотите работать: 1 - со списком, 2 - с динамическим массивом,3 - ИДЗ, 0 - для выхода" << '\n';
		cin >> n;
		switch (n) {
		case 1:
			system("cls");
			workWithList();
			break;
		case 2:
			system("cls");
			workWithArray();
			break;
		case 3:
			system("cls");
			workWithIDZ();
			break;
		}
	} while (n != 0);

	return 0;
}