#include <iostream>

//1) Содержит ли возрастающию последовательность
//2) Вывести на печать все дубликаты из списка
//3) Обратить список
//4) Найти средние значение элемента списка

//5) Удалить все дубликаты (двусзвязанный список)
//6) определить содержится ли 2-ой список в 1-ом

struct ListElm {
	int info;
	ListElm* link;
};
ListElm* head;

//1)
bool isPos(ListElm* p) {
	while (p->link) {
		if (p->link->info < p->info) {
			return false;
		}
		p = p->link;
	}
	return true;
}

//2)
void print_list(ListElm* p) {
	while (p) {
		ListElm* q = p->link;
		while (q) {
			if (p->info == q->info) {
				std::cout << p->link;
			}
			q = q->link;
		}
		p = p->link;
	}
}

//3)
ListElm* ReverseList(ListElm* head) {
	ListElm* prev = nullptr;
	ListElm* current = head;
	while (current != nullptr) {
		ListElm* next = current->link;
		current->link = prev;
		prev = current;
		current = next;
	}
	return prev;
}

//4)
double Average(ListElm* p) {
	if (p == nullptr)
		return 0.0;
	double sum = 0;
	int count = 0;
	while (p) {
		sum += p->info;
		count++;
		p = p->link;
	}
	return sum / count;
}

struct DListElm {
	int info;
	DListElm* next;
	DListElm* prev;
};

//5)
void removeDuplicates(DListElm*& head) {
	if (head == nullptr || head->next == nullptr) {
		return;
	}

	DListElm* current = head;
	while (current != nullptr) {
		DListElm* runner = current->next;
		while (runner != nullptr) {
			if (runner->info == current->info) {
				DListElm* toDelete = runner;
				runner->prev->next = runner->next;
				if (runner->next != nullptr) {
					runner->next->prev = runner->prev;
				}
				runner = runner->next;
				delete toDelete;
			}
			else {
				runner = runner->next;
			}
			
		}
		current = current->next;
	}
}

//6)
bool isSublist(ListElm* first, ListElm* second) {
	if (!second) {
		return true;
	}
	if (!first) {
		return false;
	}

	ListElm* p1 = first;
	while (p1 != nullptr) {
		ListElm* p1_runner = p1;
		ListElm* p2_runner = second;
		while (p1_runner != nullptr && p2_runner != nullptr && p1_runner->info == p2_runner->info) {
			p1_runner = p1_runner->link;
			p2_runner = p2_runner->link;
		}
		if (p2_runner == nullptr) {
			return true;
		}
		p1 = p1->link;
	}
	return false;
}