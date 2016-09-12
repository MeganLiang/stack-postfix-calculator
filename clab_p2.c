#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;
struct stackNode {
	int data;
	struct stackNode *nextPtr;
}; 
void push( StackNodePtr *topPtr, int value ); //Push a value on the stack.
int pop( StackNodePtr *topPtr ); // Pop a value off the stack.
int stackTop( StackNodePtr topPtr ); //Return the top value of the stack without popping the stack.
int isEmpty( StackNodePtr topPtr ); //Determine if the stack is empty.
void printStack( StackNodePtr topPtr );// print stack
int evaluatePostfixExpression( char *expr );
int calculate( int op1, int op2, char operator );
int isOperator(char c);


int main(void) {
  int answer;
  char postfix[50];
  
  printf("Enter a postfix expression: ");
  scanf("%s", postfix);
  strcat(postfix, "\0"); //append '\0' at end of postfix
  answer = evaluatePostfixExpression(postfix);
  printf("The value of the expression is: %d\n", answer);
  return 0; 
}
int evaluatePostfixExpression(char *expr) {
 
  StackNodePtr snp = NULL; //initialise empty stack
  int x, y, calc;
  
  int i;
  for(i = 0; *(expr+i) != '\0'; i++) { //While '\0' has not been encountered
    if(isdigit(expr[i])) { //is digit
      push(&snp, expr[i]-'0'); // push ascii coded digit 
      printStack(snp); 
    }else if(isOperator(expr[i])==1) {
       x=pop(&snp);
       printStack(snp);
       y=pop(&snp);
       printStack(snp);
       calc=calculate(y,x,expr[i]);
       push(&snp, calc);          
       printStack(snp);
    }
  }
  return pop(&snp);
   
}

int calculate(int op1, int op2, char operator) {
  if(operator == '*') { //multiply
    return (op1*op2);
  }else if(operator=='/') {//divide
    return (int)(op1/op2);
  }else if(operator=='+') {//add
    return (op1+op2);
  }else if(operator=='-') {//substract
    return (op1-op2);
  }else if(operator=='%') {//remainder
    return op1%op2;
  }else if(operator=='^') {//power
	if(op2 == 0){
		return 1; //power of 0 is 1
	}
	int value = op1;
	for(int i = 1; i < op2; i ++){ //loop through op2 times
		value = op1 * value; //multiply op1 by itself 
	}
	return value;
  }
}
int isEmpty(StackNodePtr topPtr) {
	if(topPtr==NULL) { //empty
		return 1;
	}
	return 0;
}
void push (StackNodePtr *topPtr, int value) {
	StackNodePtr snp;
	snp = malloc(sizeof(StackNode)); //allocate memory for snp
	if(snp != NULL) { //memory allocation succeeded
		snp->data = value; 
		snp->nextPtr = *topPtr;
		*topPtr = snp;
	}
}
int pop( StackNodePtr *topPtr ) {
	StackNodePtr snp = *topPtr;
	int data = snp->data;
	*topPtr = (*topPtr)->nextPtr; //move topPtr to new top
	free(snp);
	return data;
}

int stackTop( StackNodePtr topPtr ) {
	if(topPtr != NULL){
		return topPtr -> data; //peek at top
	}
}
void printStack( StackNodePtr topPtr ) {
	while(topPtr != NULL) {
		printf("%d\t", topPtr->data);
		topPtr=topPtr->nextPtr; //update topPtr
	}
	printf("NULL \n");
}

int isOperator(char c) {
	if(c=='+' || c=='-' || c=='*' || c=='/' || c=='^' || c=='%') {
		return 1; //is operator
	}
	return -1;//is not an operator
}

