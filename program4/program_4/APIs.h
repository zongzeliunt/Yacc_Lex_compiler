#include "defs.h"
#include "list.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;
int in_function = 0;



void increaseTemp();
int getTemp();
void increaseArrayTemp();
int getArrayTemp();
void step_operation(string);
void exponentiation_operation();
void get_address();
void get_reverse();

void id_single_declare(string, string);
void id_array_declare(string, string, string);
void var_equal(string);
void var_asg_expr();
void var_asg_var();
string get_var_tmp_expr (string, string);
string get_var_name_with_func (string);
int is_global_id (string);
string get_id_tmp_value(string);
string get_id_type(string);
string get_id_array_range(string);
string get_id_offset(string);
string get_type_byte(string);


void loop_begin (string, string, string, string, string);
void loop_end (string);
string getLoopName ();

void print_head ();
void print_step (string);
void print_tail ();
string int_to_string(int);
string gen_value_tmp();
string gen_array_tmp();
string get_id_real_globalarray_position (string, string);
string calculate_id_flat_addr(string, string);

string get_real_opt_symbol (string);
void if_step_opt(string, string, string);
void if_start (int);
void if_finish ();
void if_and();
void if_or();
string get_if_step_num();
string get_if_loop_num();

void func_start();
void func_finish();
void main_func_start();
string func_call_gen(string, list, int);
void return_call_gen();
string get_real_func_name (string);

int temp = 1;
int arraytemp = 0;
int loop_name_num = 0;
int global_offset=0;
stack global_value_stack;
list var_list_list;
stack var_under_opt_stack;
stack need_declare_stack;
stack loop_stack;

stack if_step_stack;
stack if_loop_num_stack;
stack else_loop_num_stack;
stack else_stack;
int if_step_num = 0;
int if_loop_num = 0;
stack if_else_func_stack;

list func_name_variable_list;
stack func_name_stack;
list func_occupied_reg_list;
stack func_call_stack;

string cm_file_name = "cmachine_exe.c";
fstream cm_file_handle;
list global_id_list;
string tmp_string = "";

//loop related
//{{{
string get_id_real_globalarray_position (string id, string addr) {
	string id_tmp_value = get_id_tmp_value (id);
	string array_range = get_id_array_range(id);
	string type = get_id_type(id);
	string offset = get_id_offset (id);	
	string byte = get_type_byte (type);	
	
	string total_string = "";
	string var_string = "";
	if (array_range == "0") {
		var_string = "*(";
		var_string += id_tmp_value;
		var_string += " + ";
		var_string += offset; 
		var_string += ")";
	} else {
		int range_space_pos = 0;
		int addr_space_pos = 0;
		int total_range = 1;
		string s;
		string pos_addr;
		string pos_range;
		string total_value = gen_value_tmp();
		string tmp_value = gen_value_tmp();

		total_string = total_value;
		total_string += " = ";
		total_string += offset;
		total_string += ";";
		print_step (total_string);
		
		while (addr != "") {
			addr_space_pos = addr.find(" ");
			range_space_pos = array_range.find(" ");
			if (range_space_pos != 0) {
				s = array_range.substr(0, range_space_pos);
				pos_range = s;
				array_range.erase(0,range_space_pos + 1);
				range_space_pos = 0;
			}
			if (addr_space_pos != 0) {
				s = addr.substr(0, addr_space_pos);
				pos_addr = s;
				addr.erase(0,addr_space_pos + 1);
				addr_space_pos = 0;
				if (is_global_id(pos_addr) ) {
				//pos_addr is not a int, it's a variable!
					pos_addr = get_id_real_globalarray_position (pos_addr, "0");
				}
			}
			
			total_string = tmp_value;
			total_string += " = ";
			total_string += pos_addr;
			total_string += ";";
			print_step (total_string);
			
			total_string = tmp_value;
			total_string += " = ";
			total_string += tmp_value;
			total_string += " * ";
			total_string += int_to_string(total_range);
			total_string += ";";
			print_step (total_string);
			
			total_string = tmp_value;
			total_string += " = ";
			total_string += tmp_value;
			total_string += " * ";
			total_string += byte;
			total_string += ";";
			print_step (total_string);
			
			total_string = total_value ;
			total_string += " = ";
			total_string += total_value ;
			total_string += " + ";
			total_string += tmp_value;			
			total_string += ";";
			print_step (total_string);

			total_range *= atoi(pos_range.c_str());

		}
		//TODO
		//april 8:
		//here must support A[i,j,k]
		//r0 = A_offset;
		//r1 = k;
		//r0 = r0 + r1;
		//r1 = j*30;
		//r0 = r0 + r1;
		//r1 = i*30*20;
		//r0 = r0 + r1;
		//generate the above
		//A[i,j,k] = *(global_array + r0);
		//return *(global_array + r0);
		
		var_string = "*(";
		var_string += id_tmp_value;
		var_string += " + ";
		var_string += total_value; 
		var_string += ")";
	}

	return var_string;
}

void loop_begin (string loop_name, string loop_index, string loop_start, string loop_finish, string loop_step) {
	string loop_tmp_name = getLoopName();
	string loop_count = get_id_real_globalarray_position (loop_index, "0");
	//string loop_count = get_id_tmp_value(loop_index); 	
	string loop_number = gen_value_tmp(); 	
	string total_string = "";
	
	loop_stack.push(loop_count);
	loop_stack.push(loop_number);
	loop_stack.push(loop_step);	
	loop_stack.push(loop_finish);	
	loop_stack.push(loop_start);	
	loop_stack.push(loop_index);	
	loop_stack.push(loop_tmp_name);	
	loop_stack.push(loop_name);

//100 L0 i 3 7 1
/*
	r0 = 0; //loop count
	r1 = 10; //loop number 
L1:
*/

//r0=0; //loop count
	
	string tmp_variable = gen_value_tmp();
	total_string = tmp_variable;
	total_string += " = ";
	total_string += loop_start;
	total_string += " ;";
	print_step (total_string);
	
	total_string = loop_count;
	total_string += " = ";
	total_string += tmp_variable;
	total_string += ";";
	print_step (total_string);
//r0=10; //loop number	
	total_string = loop_number;
	total_string += " = ";
	total_string += loop_finish;
	total_string += ";";
	print_step (total_string);
//L1:
	total_string = loop_tmp_name;
	total_string += ":";
	print_step (total_string);
}

void loop_end (string loop_name) {
	/*
	r0 = r0 + 1;
	if (r1 > r0) goto L1;
	*/
	string tmp_variable = gen_value_tmp();
	string stack_loop_name = loop_stack.pop();	
	if (loop_name != stack_loop_name) {
		//error
	}	
	string total_string = "";
	
	string loop_tmp_name = loop_stack.pop();
	string loop_index = loop_stack.pop();
	string loop_start = loop_stack.pop();
	string loop_finish = loop_stack.pop();
	string loop_step = loop_stack.pop();
	string loop_number = loop_stack.pop();
	string loop_count = loop_stack.pop();
	
//r0 = r0 + 1;
	total_string = tmp_variable;
	total_string += " = ";
	total_string += loop_count;
	total_string += ";";
	print_step (total_string);
	
	total_string = tmp_variable;
	total_string += " = ";
	total_string += tmp_variable;
	total_string += " + ";
	total_string += loop_step;
	total_string += ";";
	print_step (total_string);
	
	total_string = loop_count;
	total_string += " = "; 
	total_string += tmp_variable;
	total_string += ";";
	print_step (total_string);
//r1 = r0;
	total_string = tmp_variable;
	total_string += " = ";
	total_string += loop_count;
	total_string += ";";
	print_step (total_string);
//if (r1 > r0) goto L1;

	total_string = "if (";
	total_string += loop_number;
	total_string += " > ";
	total_string += tmp_variable;
	total_string += ") ";
	total_string += "goto ";
	total_string += loop_tmp_name;
	total_string += ";";
	print_step (total_string);
}

//}}}

//ID related
//{{{
string get_id_tmp_value (string id) {
	list_element head;
	list_element *current;
	head = global_id_list.head;
	if (head.next != NULL) {
		current = head.next;
		while (current != NULL) {
			if (current->element == id) {
				return current->next->element;
			} else if (current->next->next->next->next != NULL){
				for (int i =0; i < 5 ; i++) {
					current = current->next;
				}
			}
		}
	}
	return "";
}

string get_id_type (string id) {
	list_element head;
	list_element *current;
	head = global_id_list.head;
	if (head.next != NULL) {
		current = head.next;
		while (current != NULL) {
			if (current->element == id) {
				return current->next->next->element;
			} else {
				for (int i =0; i < 5 ; i++) {
					current = current->next;
				}
			}
		}
	}
	return "";
}

string get_id_array_range (string id) {
	list_element head;
	list_element *current;
	head = global_id_list.head;
	if (head.next != NULL) {
		current = head.next;
		while (current != NULL) {
			if (current->element == id) {
				return current->next->next->next->element;
			} else {
				for (int i =0; i < 5 ; i++) {
					current = current->next;
				}
			}
		}
	}
	return "";
}

string get_id_offset (string id) {
	list_element head;
	list_element *current;
	head = global_id_list.head;
	if (head.next != NULL) {
		current = head.next;
		while (current != NULL) {
			if (current->element == id) {
				return current->next->next->next->next->element;
			} else {
				for (int i =0; i < 5 ; i++) {
					current = current->next;
				}
			}
		}
	}
	return "";
}

void id_array_declare (string id, string type, string range) {
	string value;
	string value_tmp;
	string total_string = "";
	
	string s;
	string pos_range;
	int range_space_pos = 0;
	int total_range = 1;
	string initial_range = range;
	if (range == "-1") {
		//error
	}
	
	if (range == "0") {
		total_range = 1;
	} else {
		while (range != "") {
			range_space_pos = range.find(" ");
			if (range_space_pos != 0) {
				s = range.substr(0, range_space_pos);
				pos_range = s;
				range.erase(0,range_space_pos + 1);
				range_space_pos = 0;
			}
			total_range *= atoi(pos_range.c_str());
		}	
	}	
	string byte = get_type_byte (type);

	if (global_offset + total_range * atoi(byte.c_str()) > 24000) {
		global_offset = 0;
		increaseArrayTemp();
	}
	value_tmp = gen_array_tmp();
	
	if (!global_id_list.search(id)) {
		global_id_list.insert(id);
		global_id_list.insert(value_tmp);
		global_id_list.insert(type);
		global_id_list.insert(initial_range);
		global_id_list.insert(int_to_string(global_offset));
	}
	global_offset += total_range * atoi(byte.c_str());

}

/*
void id_single_declare (string id, string type) {
	string value;
	string value_tmp;
	string total_string = "";
	string range = "0";
	value_tmp = gen_value_tmp();
	if (!global_id_list.search(id)) {
		global_id_list.insert(id);
		global_id_list.insert(value_tmp);
		global_id_list.insert(type);
		global_id_list.insert(range);
	}
}
*/

string calculate_id_flat_addr (string id, string id_addr) {
	string array_range = get_id_array_range(id);

	if (array_range == "0") {
		//single
		return "0";
	} 
	string pos_addr;
	string total_addr = "";
	string total_range = "1";
	string pos_range;
	int range_space_pos = 0;
	int addr_space_pos = 0;
	int round = 0;
	string s;
	while (id_addr != "") {
		addr_space_pos = id_addr.find(" ");
		range_space_pos = array_range.find(" ");
		if (range_space_pos != 0) {
			s = array_range.substr(0, range_space_pos);
			pos_range = s;
			array_range.erase(0,range_space_pos + 1);
			range_space_pos = 0;
		}
		if (addr_space_pos != 0) {
			s = id_addr.substr(0, addr_space_pos);
			pos_addr = s;
			id_addr.erase(0,addr_space_pos + 1);
			addr_space_pos = 0;
		}
		if (total_addr == "") {
			total_addr = pos_addr;
			total_addr += "*";
			total_addr += total_range;
		} else {
			total_addr += "+";
			total_addr += pos_addr;
			total_addr += "*";
			total_addr += total_range;
		}
//TODO, I need to add byte judgement here!
		total_range += "*";
		total_range += pos_range;
	}

	return total_addr;	
}
//}}}

//var related
//{{{
string get_var_name_with_func (string var_name) {
	string var_name_with_func_name = "";
	
	if (!func_name_stack.is_empty() ) {
		string func_name = func_name_stack.pop();
		func_name_stack.push(func_name);
		var_name_with_func_name = func_name;
		var_name_with_func_name += "_";
		var_name_with_func_name += var_name;
	}
	if (global_id_list.search(var_name)) {
		return var_name;
	} else if (global_id_list.search(var_name_with_func_name)){
		return var_name_with_func_name;
	}
	return "";
}

string get_var_tmp_expr (string id, string addr_reg) {
	string tmp_value = get_id_tmp_value(id);	
	string type = get_id_type(id);	

	string total_var_string;
	total_var_string = "*(";
	total_var_string += tmp_value;
	total_var_string += " + ";
	total_var_string += addr_reg; 
	total_var_string += ")";  
	
	return total_var_string;
}

string get_type_byte (string type) {
	if (type == "int") {
		return "4";
	}
	if (type == "boolean") {
		return "1";
	}
	if (type == "bool") {
		return "1";
	}
	if (type == "unsigned") {
		return "4";
	}
	if (type == "char") {
		return "1";
	}
	return "1";
}

void var_asg_var () {
	string id = var_under_opt_stack.pop();
	string addr = var_under_opt_stack.pop();
	string var_string = get_id_real_globalarray_position (id, addr);
	
	string tmp_value = gen_value_tmp ();
	string total_string = tmp_value;
	total_string += " = ";	
	total_string += var_string;	
	total_string += ";";	
	print_step (total_string);

	global_value_stack.push(tmp_value);
}

void var_asg_expr () {
	string id = var_under_opt_stack.pop();
	string addr = var_under_opt_stack.pop();
	string var_string = get_id_real_globalarray_position (id, addr);
	var_equal(var_string);
}


void var_equal (string var) {
	string value;
	string total_string = "";
	value = global_value_stack.pop();
	if (value == "") {
		//error
	}
	string tmp_variable = gen_value_tmp();
	total_string = tmp_variable;
	total_string += " = ";
	total_string += value;
	total_string += " ;";
	print_step (total_string);

	total_string = var;
	total_string += " = ";
	total_string += tmp_variable;
	total_string += " ;";

	print_step (total_string);
}

//}}}

//if related
//{{{
void if_start (int if_else_switch) {
	string total_string = "";
	string if_condition = "";
	string correct_bit = gen_value_tmp();
	if (if_else_switch == 0) {
		if_condition = if_step_stack.pop();
		else_stack.push(if_condition);
		total_string = correct_bit;
		total_string += " = 1;";
		print_step(total_string);
	} else {
		if_condition = else_stack.pop();
		total_string = correct_bit;
		total_string += " = 0;";
		print_step(total_string);
	}
	

//if (result == 1) goto execuate1
	total_string = "if (";
	total_string += if_condition;
	total_string += " == ";
	total_string += correct_bit;
	total_string += " ) goto execuate";
	string tmp_if_loop_num = get_if_loop_num();
	total_string += tmp_if_loop_num;
	total_string += ";";
	print_step(total_string);
//goto end1
	total_string = "goto end";
	total_string += tmp_if_loop_num;
	total_string += ";";
	print_step(total_string);
//goto execuate1
	total_string = "execuate";
	total_string += tmp_if_loop_num;
	total_string += ":";
	print_step(total_string);

	if (if_else_switch == 0) {
		if_loop_num_stack.push(tmp_if_loop_num);
	} else {
		else_loop_num_stack.push(tmp_if_loop_num);
	}

/*
	if (result == 1) goto execuate1
		(push execuate/end number to if loop number stock)
		goto end1
	execuate1:
*/	

}

void if_else_finish (int if_else_switch) {
	string tmp_if_loop_num = "";
	if (if_else_switch == 0) {
		tmp_if_loop_num = if_loop_num_stack.pop();
	} else {
		tmp_if_loop_num = else_loop_num_stack.pop();
	}
	string total_string = "";
	total_string = "end";
	total_string += tmp_if_loop_num;
	total_string += ":";
	print_step (total_string);
}

void if_and () {
	string tmp_variable_1 = if_step_stack.pop();
	string tmp_variable_2 = if_step_stack.pop();
	string result = gen_value_tmp ();
	string step_num = get_if_step_num();
	string total_string = "";

	string correct_bit = gen_value_tmp();
	total_string = correct_bit;
	total_string += " = 0;";
	print_step(total_string);
// r3 = 0; 
	total_string = result;
	total_string += " = 0;";
	print_step (total_string);
//if (r1 == 0) goto end1
	total_string = "if (";
	total_string += tmp_variable_1;
	total_string += " == ";
	total_string += correct_bit;
	total_string += ") goto AssignEnd";
	total_string += step_num;
	total_string += ";";
	print_step (total_string);
//if (r2 == 0) goto end1
	total_string = "if (";
	total_string += tmp_variable_2;
	total_string += " == ";
	total_string += correct_bit;
	total_string += ") goto AssignEnd";
	total_string += step_num;
	total_string += ";";
	print_step (total_string);
//r3 = 1;
	total_string = result;
	total_string += " = ";
	total_string += "1;";
	print_step (total_string);
//end:
	total_string = "AssignEnd";
	total_string += step_num;
	total_string += ":";
	print_step (total_string);

	if_step_stack.push(result);
}

void if_or () {
	string tmp_variable_1 = if_step_stack.pop();
	string tmp_variable_2 = if_step_stack.pop();
	string result = gen_value_tmp ();
	string step_num = get_if_step_num();
	string total_string = "";

	string correct_bit = gen_value_tmp();
	total_string = correct_bit;
	total_string += " = 1;";
	print_step(total_string);
// r3 = 0; 
	total_string = result;
	total_string += " = 0;";
	print_step (total_string);
//if (r1 == 0) goto assign1
	total_string = "if (";
	total_string += tmp_variable_1;
	total_string += " == ";
	total_string += correct_bit;
	total_string += ") goto assign";
	total_string += step_num;
	total_string += ";";
	print_step (total_string);
//if (r2 == 0) goto assign1
	total_string = "if (";
	total_string += tmp_variable_2;
	total_string += " == ";
	total_string += correct_bit;
	total_string += ") goto assign";
	total_string += step_num;
	total_string += ";";
	print_step (total_string);
//goto AssignEnd1;
	total_string = "goto AssignEnd";
	total_string += step_num;
	total_string += ";";
	print_step (total_string);
//assign1:
	total_string = "assign";
	total_string += step_num;
	total_string += ":";
	print_step (total_string);
//r3 = 1;
	total_string = result;
	total_string += " = ";
	total_string += "1;";
	print_step (total_string);
//end:
	total_string = "AssignEnd";
	total_string += step_num;
	total_string += ":";
	print_step (total_string);

	if_step_stack.push(result);
}

string get_real_opt_symbol (string opt) {
	if (opt == ".lt.") {
		return "<";
	}
	if (opt == ".gt.") {
		return ">";
	}
	if (opt == ".ge.") {
		return ">=";
	}
	if (opt == ".le.") {
		return "<=";
	}
	if (opt == ".eq.") {
		return "==";
	}
	if (opt == ".neq.") {
		return "!=";
	}
	return "=";

}

void if_step_opt (string var_1, string var_2, string opt ) {
	opt = get_real_opt_symbol (opt);
	string tmp_variable_1 = gen_value_tmp ();
	string tmp_variable_2 = gen_value_tmp ();
	string result = gen_value_tmp ();

	string total_string = "";
// r3 = 0; 
	total_string = result;
	total_string += " = 0;";
	print_step (total_string);
//r1 = a;
	total_string = tmp_variable_1;
	total_string += " = ";
	total_string += var_1;
	total_string += ";";
	print_step (total_string);
	
//r2 = b;
	total_string = tmp_variable_2;
	total_string += " = ";
	total_string += var_2;
	total_string += ";";
	print_step (total_string);
	
//if (A == 1) goto assign1
	total_string = "if (";
	total_string += tmp_variable_1;
	total_string += opt;
	total_string += tmp_variable_2;
	total_string += ") goto assign";
	string step_num = get_if_step_num();
	total_string += step_num;
	total_string += ";";
	print_step (total_string);
//goto AssignEnd1;
	total_string = "goto AssignEnd";
	total_string += step_num;
	total_string += ";";
	print_step (total_string);
//assign1:
	total_string = "assign";
	total_string += step_num;
	total_string += ":";
	print_step (total_string);
//r3 = 1;
	total_string = result;
	total_string += " = ";
	total_string += "1;";
	print_step (total_string);
//end:
	total_string = "AssignEnd";
	total_string += step_num;
	total_string += ":";
	print_step (total_string);

	if_step_stack.push (result);	
	
/*	
	result = 0; 
if (A == 1) goto assign
	goto end;
	assign:
		result = 1;
		(push result to if result stock)
	end:
*/

}

string get_if_step_num () {
	int tmp_if_step_num = if_step_num;	
	if_step_num += 1;
	return int_to_string (tmp_if_step_num);
}

string get_if_loop_num () {
	int tmp_if_loop_num = if_loop_num;	
	if_loop_num += 1;
	return int_to_string (tmp_if_loop_num);
}
///}}}

//func related
//{{{
string get_real_func_name (string func_name) {
	if (func_name == "printInt") {
		return "printi";
	}	
	if (func_name == "printLine") {
		return "printline";
	}	
	if (func_name == "printString") {
		return "prints";
	}	


	return func_name;
}

void return_call_gen () {
	string id = "";
	string range = "";
	if (!var_list_list.is_empty()) {
		id = var_list_list.pop();
		range = var_list_list.pop();
	}
	string total_string = "";
	if (range == "-1") {
		total_string = "r0 = ";
		total_string += id;
		total_string += ";";
		print_step (total_string);
	} else {
		string var_string = get_id_real_globalarray_position (id, range);
		total_string = "r0 = ";
		total_string += var_string;
		total_string += ";";
		print_step (total_string);
	}
}

string func_call_gen(string func_name, list func_call_variable_list, int arg_count) {
	int counter = 1;
	func_name = get_real_func_name(func_name);
	string func_total_string = func_name;
	func_total_string += "(";
	while (!func_call_variable_list.is_empty()) {
		string id = func_call_variable_list.pop();
		string range = func_call_variable_list.pop();
		if ( range != "-1") {
			string var_string = get_id_real_globalarray_position (id, range);
			
			string tmp_value = gen_value_tmp ();
			string total_string = tmp_value;
			total_string += " = ";	
			total_string += var_string;	
			total_string += ";";	
			print_step (total_string);
			func_total_string += tmp_value;
		} else {
//integer
			func_total_string += id;
		}
		if (counter != arg_count) {
			func_total_string += ",";
		}
		counter ++;
	}
	func_total_string += ");";
	return func_total_string;
}

void func_start() {
	string func_name = func_name_stack.pop();
	func_name_stack.push(func_name);
	string vari_count;
	int variable_count;
	int i;
	list tmp_list;
	string total_string;
	string value;
	string range;
	string real_variable;
	string tmp_variable;

	if (func_name == "main") {
		main_func_start();
	} else {
		list_element head;
		list_element *current;
		head = func_name_variable_list.head;
		if (head.next != NULL) {
			current = head.next;
			while (current != NULL) {
				vari_count = current->next->element;
				variable_count = atoi(vari_count.c_str());
				if (current->element != func_name) {
					for (i = 0; i < variable_count*2 + 1; i++) {
						current = current->next;
					}
				} else {
					break;
				}				
			}
		}
		if (current != NULL) {
			//found
			current = current->next;	
			vari_count = current->element;
			variable_count = atoi(vari_count.c_str());
			current = current->next;
			total_string = func_name;
			total_string += "(";
			for (i = 0; i < variable_count - 1; i = i + 1) {
				value = current->element;
				range = current->next->element;
				current = current->next->next;
				real_variable = get_id_real_globalarray_position (value,range);
				tmp_variable = gen_value_tmp();
				func_occupied_reg_list.insert(tmp_variable);			
				total_string += tmp_variable;
				total_string += " ,";
				tmp_list.insert(real_variable);
				tmp_list.insert(tmp_variable);
			}
			value = current->element;
			range = current->next->element;
			current = current->next->next;
			real_variable = get_id_real_globalarray_position (value,range);
			tmp_variable = gen_value_tmp();
			func_occupied_reg_list.insert(tmp_variable);			
			total_string += tmp_variable;
			total_string += " )";
			cm_file_handle<<total_string<<endl;
			cm_file_handle<<"{"<<endl;
			tmp_list.insert(real_variable);
			tmp_list.insert(tmp_variable);
			while (!tmp_list.is_empty()) {
				real_variable = tmp_list.pop();
				tmp_variable = tmp_list.pop();
				total_string = 	real_variable;
				total_string += " = ";
				total_string += tmp_variable;
				total_string += ";";
				print_step (total_string);
			}
		}
	
	}
}

void func_finish() {
	string func_name = func_name_stack.pop();
	cm_file_handle<<"	printline();"<<endl<<endl;
	cm_file_handle<<"}"<<endl<<endl;
}

void main_func_start() {
	cm_file_handle<<"main ()"<<endl; 
	cm_file_handle<<"{"<<endl;
	cm_file_handle<<"    initstack();"<<endl;
}

//}}}

//APIs:
//{{{
void print_head () {
	cm_file_handle.open (cm_file_name.c_str(), fstream::out);
	cm_file_handle<<"int r0, r1, r2, r3, r4, r5, r6, r7,"<<endl;
	cm_file_handle<<"	r8, r9, r10, r11, r12, r13, r14, r15,"<<endl;
	cm_file_handle<<"	r16, r17, r18, r19, r20, r21, r22, r23,"<<endl;
	cm_file_handle<<"	r24, r25, r26, r27, r28, r29, r30, r31;"<<endl;
	cm_file_handle<<"int *iptr1;"<<endl;
	cm_file_handle<<"char *cptr1;"<<endl;
	cm_file_handle<<"char *fp, *sp;"<<endl;
	cm_file_handle<<"char global_array_0[24000];"<<endl;
	cm_file_handle<<"char global_array_1[24000];"<<endl;
	cm_file_handle<<"char global_array_2[24000];"<<endl;
	cm_file_handle<<"char global_array_3[24000];"<<endl;
}

void print_step (string total_string) {
	cm_file_handle<<"    "<<total_string<<endl;

}

void print_tail () {
	cm_file_handle.close();
}

void exponentiation_operation() {
	string value_1;
	string value_2;
	string total_string = "";
	string total_value = gen_value_tmp(); 	
	value_2 = global_value_stack.pop(); //expon size
	value_1 = global_value_stack.pop(); //loop size

	if (value_1 == "" || value_2 == "") {
		//error
	}
	
	string loop_name = "expon_loop";
	string loop_index = "expon_index";
//this is an inner value, 
	id_array_declare(loop_index, "int", "0");

//r1=1;
	total_string = total_value;
	total_string += " = 1;";
	print_step (total_string);
//r0=0;
//r2=10;
//L1:
	loop_begin (loop_name, loop_index, "0", value_2, "1");


//r0 = r0 * 2;
	total_string = total_value;
	total_string += " = ";		
	total_string += total_value;
	total_string += " * ";
	total_string += value_1;		
	total_string += ";";
	print_step (total_string);
//r0=r0+1;
//if(r2>r0) goto L1;
	loop_end (loop_name);
	
	global_value_stack.push(total_value);

}

void get_address () {
	string value; 
	string total_string;
	value = global_value_stack.pop(); //loop size
	total_string = "iptr1";
	total_string += " = &";
	total_string += value;
	total_string += ";";
	print_step (total_string);
	global_value_stack.push("iptr1");

}

void get_reverse () {
	string value; 
	string total_string;
	value = global_value_stack.pop(); //loop size
	string tmp_value = gen_value_tmp();
	total_string = tmp_value;
	total_string += " = ~";
	total_string += value;
	total_string += ";";
	print_step (total_string);
	global_value_stack.push(tmp_value);
}

void step_operation (string opt) {
	string value_1;
	string value_2;
	string value_tmp = "";
	string total_string = "";
	value_2 = global_value_stack.pop();
	value_1 = global_value_stack.pop();
	if (value_1 == "" || value_2 == "") {
		//error
	}
	value_tmp = gen_value_tmp();
	total_string = value_tmp;
	total_string += " = ";
	total_string += value_1;
	total_string += " ";
	total_string += opt;
	total_string += " ";
	total_string += value_2;
	total_string += ";";
	print_step (total_string);
	global_value_stack.push(value_tmp);
}

string gen_array_tmp () {
	string value_tmp = "";
	
	value_tmp = "global_array_";
	value_tmp += int_to_string(getArrayTemp());

	return value_tmp;
}

int is_global_id (string id) {
	list_element head;
	list_element *current;
	head = global_id_list.head;
	if (head.next != NULL) {
		current = head.next;
		while (current != NULL) {
			if (current->element == id) {
				return 1;
			} else {
				for (int i =0; i < 5 ; i++) {
					current = current->next;
				}
			}
		}
	}
	return 0;
}

string gen_value_tmp () {
	string value_tmp = "";
	
	value_tmp = "r";
	value_tmp += int_to_string(getTemp());
	increaseTemp();
	while ( is_global_id(value_tmp) || global_value_stack.search(value_tmp) || if_step_stack.search(value_tmp) || loop_stack.search(value_tmp) || func_occupied_reg_list.search(value_tmp)) {
		value_tmp = "r";
		value_tmp += int_to_string(getTemp());
		increaseTemp();
	}
	

	return value_tmp;
}

string int_to_string (int num) {
	char t[256];
	string s;
	sprintf (t,"%d",num);
	s=t;	
	return s;
}

void increaseTemp()
{
	if(temp == 31)
		temp = 1;
	else
		temp++;
}

int getTemp()
{
	return temp;
}

void increaseArrayTemp()
{
	if(arraytemp == 3)
		arraytemp = 0;
	else
		arraytemp++;
}

int getArrayTemp()
{
	return arraytemp;
}

string getLoopName () {
	string total_string = "L";
	total_string += int_to_string(loop_name_num);
	loop_name_num ++;
	return total_string;
} 
//}}}
