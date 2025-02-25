#include "expression.h"

int main() {
	string str = "(124+20/10)/2";
	cout << str << endl;

	queue<Lexema> lex_res;
 	lex_res = lex(str);
	try {
		error(lex_res);
	}
	catch (const char* st){
		cout << "Error: " << st << endl;
			cout << "Try again!" << endl;
			return 0;
	}
	cout << lex_res << endl;
	cout << "------------" << endl;

	queue<Lexema> result;
	result = ToPostfix(lex_res);
	cout << result << endl;
	cout << "-----------------" << endl;
	int result_1 = Calculate(result);
	cout << result_1 << endl;

	return 0;
}

//int main() {
//	string str = "(123++10*2-1)+20/10";
//	cout << str << endl;
//
//	queue<Lexema> lex_res;
//	lex_res = lex(str);
//	try {
//		error(lex_res);
//	}
//	catch (const char* st) {
//		cout << "Error: " << st << endl;
//		cout << "Try again!" << endl;
//		return 0;
//	}
//	print(lex_res);
//	cout << "-------------------" << endl;
//
//	queue<Lexema> result;
//	result = ToPostfix(lex_res);
//	print(result);
//	cout << "-----------------" << endl;
//	int result_1 = Calculate(result);
//	cout << result_1 << endl;
//
//
//	return 0;
//}