#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

class list_element {
	public:
		string element;
		list_element *next;
		list_element () {
			element = "";
			next = NULL;
		}

};

class list {
	public:
		list_element head;
		list_element *current;
//these two could be private
		int insert(string);
		string pop();
		string search_id_tmp_value(string);
		void show();
		int search(string);
		int is_empty();
		list ()
		{
			head.element="";
			current = &head;
		}
		~list ()
		{
			//cout<<"destroy"<<endl;
		}
		
};

int list::is_empty () {
	if (head.next == NULL) {
		return 1;
	} else {
		return 0;
	}
}

int list::search (string a) {
	if (head.next != NULL) {
		current = head.next;
		if (current->element == a) {
			return 1;
		}
		while (current->next != NULL) {
			if (current->element == a) {
				return 1;
			} else {
				current = current->next;
			}
		}
	}
	return 0;
}

string list::pop () {
	string poped_string;
	if (head.next != NULL) {
		current = head.next;
		head.next=current->next;
		poped_string = current->element;
		delete (current);
		if (head.next == NULL) {
			current = &head;
		}
	} else {
		return "";
	}

	return poped_string;
}

int list::insert(string a) {
	list_element *new_element;
	new_element=new(list_element);
	new_element->element = a;
	current->next = new_element;
	current = new_element;

	return 0;
}

void list::show() {
	if (head.next != NULL) {
		current = head.next;
		cout<<current->element<<endl;

		while (current->next != NULL) {
			current = current->next;
			cout<<current->element<<endl;
		}
	} else {
		
	}
}
