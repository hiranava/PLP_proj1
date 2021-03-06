// PLP.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <stack>
#include <cstdio>
#include <stdlib.h>
#include <string>
#include "Node.h"

using namespace std;

char prog[100000];
int indexP = 0;
int progLength;
std::stack<Node*> tokenStack;
void buildTree(string token, int numOfChild){
	//cout <<token << "\t" << numOfChild<< endl;
	Node* newNode = new Node();
	newNode->value = token;
	if (numOfChild == 1){
		Node* temp = tokenStack.top();
		tokenStack.pop();
		newNode->leftchild = temp;
	}
	else if (numOfChild > 1){
		while (numOfChild > 1){
			Node* temp = tokenStack.top();
			tokenStack.pop();
			tokenStack.top()->rightSibling = temp;
			numOfChild--;
		}
		Node* temp = tokenStack.top();
		tokenStack.pop();
		newNode->leftchild = temp;
	}
	
	tokenStack.push(newNode);
}
void preOrderTraversal(Node* parentNode, int depthCounter){
	for (int i = 0; i < depthCounter; i++)
		cout << ".";
	cout << parentNode->value << endl;
	depthCounter++;
	if (parentNode->leftchild != NULL){
		preOrderTraversal(parentNode->leftchild, depthCounter);
	}
	if (parentNode->rightSibling != NULL){
		preOrderTraversal(parentNode->rightSibling, --depthCounter);
	}
}

bool isOperator(char ch);
string getTypeofToken(string token){
	//check for keywords
	string keyword[] = { "let", "in", "fn", "where", "aug", "or", "not", "gr", "ge", "ls", "le", "eq", "ne", "true", "false", "nil",
		"dummy", "within", "and", "rec" };
	for (int i = 0; i < 20; i++){
		if (token == keyword[i]){
			return("keyword");
		}
	}
	//check Integer
	bool isInteger = true;
	for (int i = 0; i<token.length(); i++){
		if (!isdigit(token[i])){
			isInteger = false;
		}
	}
	if (isInteger){
		return("integer");
	}
	//check identifier
	bool isIdentifier = true;
	if (!isalpha(token[0])){
		isIdentifier = false;
	}
	for (int i = 1; i<token.length(); i++){
		if (isalnum(token[i]) || token[i] == '_'){
			//do nothing
		}
		else{
			isIdentifier = false;
		}
	}
	if (isIdentifier){
		return("identifier");
	}
	//check String
	bool isString = true;
	int n = token.length();
	if (token[0] != '\'' && token[n - 1] != '\''){
		isString = false;
	}
	for (int i = 1; i<token.length(); i++){
		if (isalnum(token[i]) || token[i] == '\t' || token[i] == '\n' || token[i] == '\\'
			|| token[i] == '\'' || token[i] == '(' || token[i] == ')' || token[i] == ';' || token[i] == ','|| isOperator(token[i])){

		}
		else{
			isString = false;
		}
	}
	if (isString){
		return("string");
	}
	//check for operator
	if (isOperator(token[0])){
		return("operator");
	}
	//if none of the above then return the token
	return(token);
}
bool isOperator(char ch){
	if (ch == '+' || ch == '-' || ch == '*' || ch == '<' || ch == '>' || ch == '&' || ch == '.' || ch == '@' || ch == '/' || ch == ':' 
		|| ch == '=' || ch == '~' || ch == '|' || ch == '$' || ch == '!' || ch == '#' || ch == '%' || ch == '^' || ch == '_' || ch == '[' 
		|| ch == ']' || ch == '{' || ch == '}' || ch == '-' || ch == '"' || ch == '`' || ch== '?'){
		return true;
	}
	return false;
}
string currentToken;
string getNextToken(){
	currentToken.clear();
	while (true){
		//check if the program has been completely parsed.
		if (indexP > progLength){
			cout<<"No more tokens left";
			exit(0);
		}
		else{
			//check for spaces
			char ch = prog[indexP];
			if (prog[indexP] == ' ' || prog[indexP] == '\t' || prog[indexP] == '\n'){
				indexP = indexP + 1;
				//cout << "checking space";//do nothing
			}
			else if (prog[indexP] == '/' && prog[indexP + 1] == '/'){
				while (prog[indexP] != '\n'){
					indexP = indexP + 1;
				}
			}
			else if (isalnum(prog[indexP])){
				//bool chkOperator = isOperator(prog[indexP]);
				while (isalnum(prog[indexP]) || prog[indexP] == '_'){//prog[indexP] != ' ' && prog[indexP] != '\t' && prog[indexP] != '\n' && prog[indexP] != '(' && prog[indexP] != ')' && prog[indexP] != ';' && prog[indexP] != ',' && !isOperator(prog[indexP])){
					currentToken.push_back(prog[indexP++]);
					
				}
				break;
			}
			else if (prog[indexP] == '\''){
				do{
					currentToken.push_back(prog[indexP++]);
				} while (prog[indexP] != '\'');
				currentToken.push_back(prog[indexP++]);
				break;
			}
			else if (prog[indexP] == '(' || prog[indexP] == ')' || prog[indexP] == ';' || prog[indexP] == ','){
				currentToken.push_back(prog[indexP++]);
				break;
			}
			else if (isOperator(prog[indexP])){
				while (isOperator(prog[indexP])){
					currentToken.push_back(prog[indexP++]);
				}
				break;
			}
			else{
				currentToken = prog[indexP++];
				break;
			}
		}


	}
	//cout << "Token " << currentToken << endl;
	return(currentToken);
}
void readToken(string token){
	
	string modToken;
	if (token != currentToken){
		cout << "Error! Expected " << token << "but found " << currentToken;
		exit(0);
	}
	string type = getTypeofToken(token);
	if (type == "identifier" || type == "string" || type == "integer"){
		if (type == "identifier"){
			 modToken = "<ID:" + token + ">";
		}
		else if (type == "string"){
			modToken = "<STR:" + token + ">";
		}
		else{
			modToken = "<INT:" + token + ">";
		}
		buildTree(modToken, 0);
	}
	string nextToken = getNextToken();
}
void processA();
void processAf();
void processAp();
void processAt();
void processB();
void processBp();
void processBs();
void processBt();
void processD();
void processDa();
void processDb();
void processDr();
void processEw();
void processR();
void processRn();
void processT();
void processTa();
void processTc();
void processV1();
void processVb();
void processE(){
	if (currentToken == "let"){
		readToken("let");
		processD();
		readToken("in");
		processE();
		buildTree("let", 2);
	}
	else if (currentToken == "fn"){
		readToken("fn");
		int n = 1;
		do{
			processVb();
			n = n + 1;
		} while (currentToken == "(" || currentToken == "identifier");
		readToken(".");
		processE();
		buildTree("lambda", n);
	}
	else{
		processEw();
	}
}
void processEw(){
	processT();
	if (currentToken == "where"){
		readToken("where");
		processDr();
		buildTree("where", 2);
	}
}

void processT(){
	processTa();
	int n = 1;
	if (currentToken == ","){
		while (currentToken == ","){
			readToken(",");
			processTa();
			n = n + 1;
		}
		buildTree("tau", n);
	}
}
void processTa(){
	processTc();
	while (currentToken == "aug"){
		readToken("aug");
		processTc();
		buildTree("aug", 2);
	}
}
void processTc(){
	processB();
	if (currentToken == "->"){
		readToken("->");
		processTc();
		if (currentToken == "|"){
			readToken("|");
			processTc();
		}
		buildTree("->", 3);
	}
	
}
void processB(){
	processBt();
	//string nextToken = getNextToken();
	while (currentToken == "or"){
		readToken("or");
		processBt();
		buildTree("or", 2);
		//nextToken = getNextToken();
	}
}
void processBt(){
	processBs();
	//string nextToken = getNextToken();
	while (currentToken == "&"){
		readToken("&");
		processBs();
		buildTree("&", 2);
		//nextToken = getNextToken();
	}
}
void processBs(){
	//string nextToken = getNextToken();
	if (currentToken == "not"){
		readToken("not");
		processBp();
		buildTree("not", 1);
	}
	else{
		processBp();
	}
}
void processBp(){
	processA();
	//string nextToken = getNextToken();
	if (currentToken == "gr"){
		readToken("gr");
		processA();
		buildTree("gr", 2);
	}
	else if (currentToken == ">"){
		readToken(">");
		processA();
		buildTree("gr", 2);
	}
	else if (currentToken == "ge"){
		readToken("ge");
		processA();
		buildTree("ge", 2);
	}
	else if (currentToken == ">="){
		readToken(">=");
		processA();
		buildTree("ge", 2);
	}
	else if (currentToken == "ls"){
		readToken("ls");
		processA();
		buildTree("ls", 2);
	}
	else if (currentToken == "<"){
		readToken("<");
		processA();
		buildTree("ls", 2);
	}
	else if (currentToken == "le"){
		readToken("le");
		processA();
		buildTree("le", 2);
	}
	else if (currentToken == "<="){
		readToken("<=");
		processA();
		buildTree("le", 2);
	}
	else if (currentToken == "eq"){
		readToken("eq");
		processA();
		buildTree("eq", 2);
	}
	else if (currentToken == "ne"){
		readToken("ne");
		processA();
		buildTree("ne", 2);
	}

}
void processA(){
	//string nextToken = getNextToken();
	if (currentToken == "+"){
		readToken("+");
		processAt();
	}
	else if (currentToken == "-"){
		readToken("-");
		processAt();
		buildTree("neg", 1);
	}
	else{
		processAt();
		while (currentToken == "+" || currentToken == "-"){
			if (currentToken == "+"){
				readToken("+");
				processAt();
				buildTree("+", 2);
			}
			else if (currentToken == "-"){
				readToken("-");
				processAt();
				buildTree("-", 2);
			}
			//nextToken = getNextToken();
		}
	}
}
void processAt(){
	processAf();
	//string nextToken = getNextToken();
	while (currentToken == "*" || currentToken == "/"){
		if (currentToken == "*"){
			readToken("*");
			processAf();
			buildTree("*", 2);
		}
		else if (currentToken == "/"){
			readToken("/");
			processAf();
			buildTree("/", 2);
		}
		//nextToken = getNextToken();
	}
}
void processAf(){
	processAp();
	//string nextToken = getNextToken();
	if (currentToken == "**"){
		readToken("**");
		processAf();
		buildTree("**", 2);
	}
}
void processAp(){
	processR();
	//string nextToken = getNextToken();
	while (currentToken == "@"){
		readToken("@");
		//nextToken = getNextToken();
		string type = getTypeofToken(currentToken);
		if (type == "identifier"){
			readToken(currentToken);
			processR();
			buildTree("@", 3);
		}
		else{
			//showError();
		}
	}
}
void processR(){
	processRn();
	//string nextToken = getNextToken();
	string type = getTypeofToken(currentToken);
	while (type == "identifier" || type == "integer" || type == "string" || type == "boolean" || currentToken == "nil" || currentToken == "true" || currentToken == "false" || type == "(" || type == "dummy"){
		//readToken(currentToken);
		processRn();
		type = getTypeofToken(currentToken);
		buildTree("gamma", 2);
	}
}
void processRn(){
	string type = getTypeofToken(currentToken);
	if (type == "identifier"){
		readToken(currentToken);
		
	}
	else if (type == "integer"){
		readToken(currentToken);
		
	}
	else if (type == "string"){
		type = getTypeofToken(currentToken);
		readToken(currentToken);
		
	}
	else if (currentToken == "true"){
		readToken("true");
		buildTree("true", 0);
	}
	else if (currentToken == "false"){
		readToken("false");
		buildTree("false", 0);
	}
	else if (currentToken == "nil"){
		readToken("nil");
		buildTree("<nil>", 0);
	}
	else if (currentToken == "("){
		readToken("(");
		processE();
		readToken(")");
	}
	else if (currentToken =="dummy"){
		readToken("dummy");
		buildTree("<dummy>", 0);
	}
}
void processD(){
	processDa();
	if (currentToken == "within"){
		readToken("within");
		processD();
		buildTree("within", 2);
	}
}
void processDa(){
	processDr();
	int n = 1;
	//string nextToken = getNextToken();
	if (currentToken == "and"){
		while (currentToken == "and"){
			readToken("and");
			processDr();
			n = n + 1;
		}
		buildTree("and", n);
	}
}
void processDr(){
	//string nextToken = getNextToken();
	if (currentToken == "rec"){
		readToken("rec");
		processDb();
		buildTree("rec", 1);
	}
	else{
		processDb();
	}
}
void processDb(){
	//string nextToken = getNextToken();
	if (currentToken == "("){
		readToken("(");
		processD();
		readToken(")");
	}
	else {
		string type = getTypeofToken(currentToken);
		if (type == "identifier"){
			readToken(currentToken);
			type = getTypeofToken(currentToken);
			if (currentToken == "(" || type == "identifier"){ //currentToken == ","
				int n = 2;
				type = getTypeofToken(currentToken);
				while (currentToken == "(" || type == "identifier"){
					processVb();
					n = n + 1;
					type = getTypeofToken(currentToken);
				}
				readToken("=");
				processE();
				buildTree("function_form", n);
				
			}
			else{
				processV1();
				readToken("=");
				processE();
				buildTree("=", 2);
			}
		}
	}
}
void processVb(){
	if (currentToken == "("){
		readToken("(");
		if (currentToken == ")"){
			readToken(")");
			buildTree("()", 0);
		}
		else{
			processV1();
			readToken(")");
		}

	}
	else{
		string type = getTypeofToken(currentToken);
		if (type == "identifier"){
			readToken(currentToken);
		}
	}

}
void processV1(){
	string  type = getTypeofToken(currentToken);
	if (type == "identifier" || type == ","){
		if (type == "identifier"){
			readToken(currentToken);
		}
		if (currentToken == ","){
			int n = 1;
			while (currentToken == ","){
				readToken(",");
				type = getTypeofToken(currentToken);
				if (type == "identifier"){
					readToken(currentToken);
				}
				n++;
			}
		buildTree(",", n);
		}
	}
}

int main(int argc, char* argv[])
{
	string line;
	bool printTreeFlag = false, printCodeFLag = false;
	int j = 0;
	//-----process the command line param
	for (int j = 1; j < argc; j++){
		std::string param;
		param = argv[j];
		if (param == "-ast"){
			printTreeFlag = true;
		}
		else if (param == "-l"){
			printCodeFLag = true;
		}
	}
	//-------------------------------------

	//-----read from file------------------
	if (argc > 1){
	ifstream myfile(argv[argc - 1]);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (int i = 0; i<line.length(); i++)
			{
				prog[j] = line[i];
				j++;
			}
			if (printCodeFLag){
				cout << line << endl;
			}
			prog[j++] = '\n';

		}
		myfile.close();
	}
	else
	{
		cout << "Unable to read file";
	}
	}
	else{
		cout << "Please provide valid file name";
	}
	progLength = j;
	
	//---------Process E --------------------
	if (printTreeFlag){
		string nextToken = getNextToken();
		processE();

		//---------- Preorder traversal of tree ----
		int depthCounter = 0;
		Node* parentNode = tokenStack.top();
		preOrderTraversal(parentNode, depthCounter);
		//-------------------------------------------
	}
	//---------------------------------------
	return 0;
}

