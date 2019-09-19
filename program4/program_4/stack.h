#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

class stack_element {
	public:
		string element;
		stack_element *next;
		stack_element () {
			element = "";
			next = NULL;
		}

};

class stack {
	private:
		stack_element head;
		stack_element *current;
	public:
		int push(string);
		string pop();
		void show();
		int search(string);
		int is_empty();
		stack ()
		{
			head.element="";
		}
		~stack()
		{
			//cout<<"destroy"<<endl;
		}
		
};

int stack::is_empty () {
	if (head.next == NULL) {
		return 1;
	} else {
		return 0;
	}

}

int stack::search (string a) {
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


string stack::pop () {
	string poped_string;
	if (head.next != NULL) {
		current = head.next;
		head.next=current->next;
		poped_string = current->element;
		delete (current);
	} else {
		return "";
	}

	return poped_string;
}

int stack::push(string a) {
	stack_element *new_element;
	new_element=new(stack_element);
	new_element->element = a;
	new_element->next = head.next;
	head.next = new_element;

	return 0;
}

void stack::show() {
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




