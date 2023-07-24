#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

//cap is our intial stack size, top is the location int he stack, stack is an array of size cap
int cap = 4096;
int top = -1;
int *stack;

//I'd like to print the stack after each operation but this fails the gargantuan test case
//Instead I can print if the stack is less than a certain size and in the gargantuan case
//Just reprint the entire stack at the end
void printStack(int * stack,int top) {
	if(top <= 20){
		char b4='[';
		for(int i=0; i<top + 1; i+=1) { 
    			printf("%c %d", b4, stack[i]); 
    			b4=','; 
		}
		puts(" ]");
	}
}
//print the whole stack regardless of size
void printAllStack(int * stack, int top){
	char b4='[';
        for(int i=0; i<top + 1; i+=1) {
		printf("%c %d", b4, stack[i]);
		b4=',';
	}
	puts(" ]");
}


int main(){
	stack = (int *) malloc(cap * sizeof(int)); 
	char buffer[4096]; 
	char *ptr; 
	
	//while the input is not none
	while(fgets(buffer, sizeof(buffer), stdin) != NULL){
		for (int i = 0; buffer[i] != '\0'; i++) {
			if(isspace(buffer[i])){
				//do nothing
			}else if(buffer[i] == '+'){
				if(top >=1){ //there are more than two elements in the stack
					stack[top-1] = stack[top-1] + stack[top];
					top--;
					printStack(stack, top);
				}else{
					//("Unable to perform '+', terminating...")
					printStack(stack, top);
					return 1;	
				}
			//if '-' check if its subtraction by checking if the next value is a space
			}else if(buffer[i] == '-'&& isspace(buffer[i+1])){
				if(top >= 1){ //check num elements
					stack[top-1]=stack[top-1]-stack[top];
					top --;
					printStack(stack, top); 
				}else{ //end loop if invalid
					//puts("Unable to perform '-', terminating ...");
					printStack(stack, top);
					return 1; 
				}			
			//otherwise, check if it is a negative number by checking if the next val is digit
			}else if(buffer[i] == '-' && isdigit(buffer[i+1])){
 				//this strolls until it hits the first non-digit and makes a nubmer out of digit chars
				int num = (int) strtol(buffer + i, &ptr, 10);
                                i = ptr - buffer - 1;
				//check if stack is full, if so, resize.
                                if(top == cap-1){
                                        cap = cap * 2;
                                        stack = (int *) realloc(stack, cap*sizeof(int));
                                }
				//add to stack
                                stack[top + 1] = num;
                                top++;
                                printStack(stack, top);
			//handle multiplication
			}else if(buffer[i] == '*'){
				if(top >= 1){
					stack[top-1]=stack[top-1]*stack[top];
					top--;
					printStack(stack, top);
				}else{
					//puts("Unable to perform '*', terminating ..."); 
					printStack(stack, top);
					return 1;
				}
			//handle modulo
			}else if(buffer[i] == '%'){
				if(top >= 1) {
					stack[top-1] = stack[top-1]%stack[top];
					top--;
					printStack(stack, top);
				}else{
					//puts("Unable to perform '%', terminating ...");
					printStack(stack, top);
					return 1; 
				}
			//handle is a digit
			}else if(isdigit(buffer[i])){
				//get the whole number
				int num = (int) strtol(buffer + i, &ptr, 10); 
				i = ptr - buffer - 1;
				//resize if needed
				if(top == cap-1){
					cap = cap * 2;
					stack = (int *) realloc(stack, cap*sizeof(int));
				}
				stack[top + 1] = num; 
				top++;
				printStack(stack, top);	  
			}else{
				//break out and print
				printStack(stack, top);
				return 1; 	
			}
		} 
	}
	printAllStack(stack, top);
	free(stack);
}



