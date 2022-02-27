#include <iostream>
#include <string>
using namespace std;
struct node {
	int data;
	struct node* link;
};
node* XOR(node* node_1, node* node_2) {
	return (node*)((uintptr_t)(node_1) ^ (uintptr_t)(node_2));
}
void actual(node* act) {
	if (act)
		cout << act->data << endl;
	else
		cout << "NULL" << endl;
}
void next(node** act, node** prev, node* tail, node* head) {
	if (*act == nullptr) {
		cout << "NULL" << endl;
		return;
	}
	if (*act == tail) {
		*act = head;
		*prev = tail;
	}
	else if (*act == head) {
		*act = head->link;
		*prev = head;
	}
	else {
		node* tmp = *act;
		*act = XOR(*prev, (*act)->link);
		*prev = tmp;
	}
	cout << (*act)->data << endl;
}
void previous(node** act, node** prev, node* tail, node* head) {
	if (*act == nullptr) {
		cout << "NULL" << endl;
		return;
	}
	if (*act == head) {
		*act = tail;
		*prev = tail->link;
	}
	else if (*prev == head) {
		*act = head;
		*prev = tail;
	}
	else {
		node* tmp = *prev;
		*prev = XOR(*act, (*prev)->link);
		*act = tmp;
	}
	cout << (*act)->data << endl;
}
void add_beg(node** head, int value, node** act, node** tail, node** prev) {
	node* newNode = new node;
	newNode->data = value;
	if (!*head) {
		newNode->link = XOR(nullptr, nullptr);
		*act = *prev = *tail = newNode;
	}
	else {
		newNode->link = XOR(nullptr, *head);
		(*head)->link = XOR(newNode, XOR((*head)->link, nullptr));
		if (*prev == *tail) {
			*prev = newNode;
		}
	}
	*head = newNode;
}
void add_end(node **tail, int value, node** act, node** head, node** prev) {
	node* newNode = new node;
	newNode->data = value;
	if (!*tail) {
		newNode->link = nullptr;
		*act = *prev = *head = newNode;
	}
	else {
		newNode->link = XOR(nullptr, *tail);
		(*tail)->link = XOR(newNode, XOR((*tail)->link, nullptr));
		if (*act == *head) {
			*prev = newNode;
		}
	}
	*tail = newNode;
}
void add_act(node** act, node** prev, int value, node** head, node** tail) {
	node* newNode = new node;
	newNode->data = value;
	if (!*head) {
		newNode->link = nullptr;
		*act = *prev = *head = *tail = newNode;
	}
	else {
		if (*act == *head) {
			newNode->link = XOR(nullptr, *head);
			(*act)->link = XOR(newNode, (*head)->link);
			*head = *prev = newNode;
		}
		else {
			if ((*head)->link == *tail) {
				newNode->link = XOR(*head, *tail);
				(*act)->link = (*head)->link = (*tail)->link = newNode;
			}
			else {
				newNode->link = XOR(*prev, *act);
				node* tmp = *prev;
				(*prev)->link = XOR(newNode, XOR((*prev)->link, *act));
				(*act)->link = XOR(newNode, XOR(tmp, (*act)->link));
			}
			*prev = newNode;
		}
	}
}
void del_beg(node** head, node** tail, node** act, node** prev ) {
	if (*head) {
		if ((*head)->link != nullptr) {
			node* tmp = (*head)->link;
			node* tmp2 = XOR(*head, tmp->link);
			tmp->link = XOR(nullptr, tmp2);
			if (*act == *head) {
				*act = *tail;
				*prev = (*tail)->link;
			}
			else if (*prev == *head)
				*prev = *tail;
			delete* head;
			*head = tmp;
		}
		else {
			delete* head;
			*head = *tail = *act = *prev = nullptr;
		}
	}
}
void del_end(node** head, node** tail, node** act, node** prev) {
	if (*head) {
		if ((*tail)->link != nullptr) {
			node* tmp = (*tail)->link;
			node* tmp2 = XOR(*tail, tmp->link);
			tmp->link = XOR(nullptr, tmp2);
			if (*act == *tail) {
				*act = tmp;
				*prev = tmp2;
			}
			else if (*prev == *tail)
				*prev = tmp;
			delete* tail;
			*tail = tmp;
		}
		else {
			delete* tail;
			*head = *tail = *act = *prev = nullptr;
		}
	}
}
void del_act(node** head, node** tail, node** act, node** prev) {
	if (*act) {
		if (*act == *head)
			del_beg(head, tail, act, prev);
		else if (*act == *tail)
			del_end(head, tail, act, prev);
		else {
			if (*prev == *head) {
				node* tmp = XOR((*act)->link, *head);
				(*head)->link = tmp;
				tmp->link = XOR(*head, XOR(tmp->link, *act));
				*prev = *tail;
				delete* act;
				*act = *head;
			}
			else {
				node* tmp = *prev;
				*prev = XOR((*prev)->link, *act);
				tmp->link = XOR(*prev, XOR(tmp, (*act)->link));
				if ((*tail)->link == *act)
					(*tail)->link = tmp;
				delete* act;
				*act = tmp;
			}
		}
	}
}
void del_val(int value, node** head, node** tail, node** act, node** prev) {
	if (*head) {
		node* tmp = nullptr, *tmp2 = nullptr, * tmp3 = nullptr;
		*act = *head;
		*prev = *tail;
		while (*act != nullptr) {
			tmp = *prev;
			if ((*act)->data == value) {
				del_act(head, tail, act, &tmp);
				if (*act == *tail)
					*act = *head;
				tmp2 = *act;
				tmp3 = tmp;
			}
			*prev = *act;
			if (*head) {
				if (*act == *head) {
					if ((*head)->link != nullptr)
						*act = (*head)->link;
					else break;
				}
				else
					*act = XOR(tmp, (*act)->link);
			}
			else {
				delete* act;
				delete* prev;
				delete* head;
				delete* tail;
				break;
			}
				
		}
		*act = tmp2;
		*prev = tmp3;
	}
}
void print_forward(node *head) {
	if (head) {
		node* act = head, * prev = nullptr;
		node* tmp = new node;
		while (act != nullptr) {
			tmp = prev;
			prev = act;
			cout << act->data << " ";
			if (act == head)
				act = head->link;
			else
				act = XOR(tmp, act->link);
		}
	}
	else
		cout << "NULL";
	cout << endl;
}
void print_backward(node* tail) {
	if (tail) {
		node* act = tail, * next = nullptr;
		node* tmp = new node;
		while (act != nullptr) {
			tmp = next;
			next = act;
			cout << act->data << " ";
			if (act == tail)
				act = tail->link;
			else
				act = XOR(tmp, act->link);
		}
	}
	else
		cout << "NULL";
	cout << endl;
}
int main() {
	string command;
	node* head = nullptr, * tail = nullptr, * act = nullptr, * prev = nullptr;
	int data;
	while (cin >> command) {
		if (command == "ACTUAL")
			actual(act);
		else if (command == "NEXT")
			next(&act, &prev, tail, head);
		else if (command == "PREV")
			previous(&act, &prev, tail, head);
		else if (command == "ADD_BEG") {
			cin >> data;
			add_beg(&head, data, &act, &tail, &prev);
		}
		else if (command == "ADD_END") {
			cin >> data;
			add_end(&tail, data, &act, &head, &prev);
		}
		else if (command == "ADD_ACT") {
			cin >> data;
			add_act(&act, &prev, data, &head, &tail);
		}
		else if (command == "DEL_BEG")
			del_beg(&head, &tail, &act, &prev);
		else if (command == "DEL_END")
			del_end(&head, &tail, &act, &prev);
		else if (command == "DEL_ACT")
			del_act(&head, &tail, &act, &prev);
		else if (command == "DEL_VAL") {
			cin >> data;
			del_val(data, &head, &tail, &act, &prev);
		}
		else if (command == "PRINT_FORWARD")
			print_forward(head);
		else if (command == "PRINT_BACKWARD")
			print_backward(tail);
		else {
			while (act)
				del_act(&head, &tail, &act, &prev);
			return 0;
		}
	}
}