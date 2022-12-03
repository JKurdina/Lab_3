#include "expression.h"

int main() {
	string str = "(123+10*2-1)  +20/10\n";
	cout << str;
	queue<Lexema> lex_res;
	//queue<Lexema> lex_res();
 	lex_res = lex(str);
	cout << lex_res << endl;;

	return 0;
}