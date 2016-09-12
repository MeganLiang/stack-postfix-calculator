/*
 ============================================================================
 Name        : clab_p1.c
 Author      : megan liang
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;
struct stackNode {
	char data;
	struct stackNode *nextPtr;
};

void convertToPostfix( char infix[], char postfix[] ); //Convert the infix expression to postfix notation.
int isOperator( char c ); //Determine if c is an operator.
int precedence( char operator1, char operator2 );//Determine if the precedence of operator1 is less than, equal to, or greater than the precedence of operator2. The function returns -1, 0 and 1, respectively.
void push( StackNodePtr *topPtr, char value ); //Push a value on the stack.
char pop( StackNodePtr *topPtr ); // Pop a value off the stack.
char stackTop( StackNodePtr topPtr ); //Return the top value of the stack without popping the stack.
int isEmpty( StackNodePtr topPtr ); //Determine if the stack is empty.
void printStack( StackNodePtr topPtr );// print stack

int main(void) {   
	char infix[256]; //initialise empty infix array
	char postfix[256]; //initialise empty postfix array
	printf("Enter an infix expression: ");
	scanf("%s", &infix);
	printf("The original infix expression is: \n");
	printf("%s\n", infix);
	convertToPostfix(infix, postfix);
	printf("The expression in postfix notation is: %s\n",postfix);  //answer

}
void convertToPostfix( char infix[], char postfix[] ) {	
	int infixIndex=0; //iterates through infix
	int postfixIndex=0;//iterates through postfix

	StackNodePtr head = NULL; //initialise empty stack
	push(&head, '(');
	printStack(head);
	strcat(infix,")"); //append ")" onto infix
	while(isEmpty(head) == 1) { //stack not empty  
		if(isdigit(infix[infixIndex])){ //is digit
			postfix[postfixIndex++] = infix[infixIndex++];
		}
		if(infix[infixIndex]=='(') { //is "("
			push(&head, infix[infixIndex++]);
			printStack(head);
		}
	 
		if(isOperator(infix[infixIndex])==1) {//is ^,/,*,%,+,-
			while((isOperator(stackTop(head)) == 1) && ((precedence(stackTop(head), infix[infixIndex]) != -1))) { //is operator with higher precedence than current infix value
				postfix[postfixIndex++] = pop(&head);   //insert operator in postfix	    
			}
			push(&head ,infix[infixIndex++]);
			printStack(head);
		}
		if(infix[infixIndex]==')') { //is ")"
			infixIndex++;
			while(stackTop(head) != '(') {
				postfix[postfixIndex++] = pop(&head);
				printStack(head);
			}
			pop(&head);
			printStack(head);
		}    
	}
}

int isEmpty(StackNodePtr topPtr) {
	if(topPtr == NULL){
		return 0; // empty, return 0
	}else{
		return 1; //not empty
	}
}
void push (StackNodePtr *topPtr, char value) {
	StackNodePtr snp;
	snp = malloc(sizeof(StackNode)); //allocate memory for snp
	if(snp != NULL) { //memory allocation succeeded
	  snp->data = value; 
	  snp->nextPtr = *topPtr;
	  *topPtr = snp;
	}
	
}
char pop( StackNodePtr *topPtr ) {
	StackNodePtr snp = *topPtr;
	char data = snp->data;
	*topPtr = (*topPtr)->nextPtr; //move topPtr to new top
	free(snp);
	return data;
}
int isOperator(char c) {
	if(c=='+' || c=='-' || c=='*' || c=='/' || c=='^' || c=='%') {
		return 1; //is operator
	}
	return -1; //is not an operator
}
int precedence(char operator1, char operator2) {
	//precedence: ^ < / <= *<= % < + <= - 
	if(operator1 == '+' || operator1 == '-'){ //compare + and -, they equal precedence
		if(operator2 == '+' || operator2 == '-'){
			return 0;		
		}else{
			return -1;		
		}
	}else if(operator1 == '*' || operator1 == '/' || operator1 == '%'){ //compare * , / and %, they equal precedence
		if(operator2 == '+' || operator2 == '-'){
			return 1;		
		}else if(operator2 == '*' || operator2 == '/' || operator2 == '%'){
			return -0;		
		}else{
			return -1;		
		}
	}else if(operator1 == '^'){ //^ has the greatest precedence
		if(operator2 == '^'){
			return 0;	
		}else{
			return 1;		
		}
	}
}
char stackTop( StackNodePtr topPtr ) {
	if(topPtr != NULL){
		return topPtr -> data; //peek at top
	}
}
void printStack( StackNodePtr topPtr ) {
	while(topPtr != NULL) {
		printf("%c\t", topPtr->data);
		topPtr=topPtr->nextPtr; //update topPtr
	}
	printf("NULL \n");

}
