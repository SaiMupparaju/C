
//TODO: Remember to add include statement here. 
#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
cll_node *cll_head(cll_node *list){
    //TODO: Implement this function, see header file for description
    //TODO: Update return statement. 
	if(list == NULL) {
		return NULL; 
	} else if((list->is_head) == 1) {
		return list; 
	} else {	
		cll_node *node = list->next; 
		while(!(node == list)) {
			if((node->is_head)==1){
				return node;
			}
			node = node->next;
		}
	}
	return NULL;  
}


cll_node *cll_tail(cll_node *list) {
    //TODO: Implement this function, see header file for description
    //TODO: Update return statement. 
	cll_node *head = cll_head(list); 
	if(head == NULL){
		return NULL; 
	}
	return head->prev;  
}


unsigned long cll_length(cll_node *list) {
    //TODO: Implement this function, see header file for description
    //TODO: Update return statement. 
	if(list == NULL) {
		return 0;
	} 
	int length = 1;
	cll_node *node = list->next;
	while(!(node == list)){
		length++;
		node=node->next;
	}
	return length; 
}

cll_node *cll_find(cll_node *list, int value) {
    //TODO: Implement this function, see header file for description
    //TODO: Update return statement. 
    	if(list == NULL) {
		return NULL; 
	}else if((list)->value == value){
		return list; 
	}else {
		cll_node *node = list->next;
		while(node != list) {
			if((node->value)==value){
				return node;
			}
			node = node->next;
		}
	}
	return NULL; 
}


cll_node *cll_remove(cll_node *list) {
    //TODO: Implement this function, see header file for description
    //TODO: Update return statement. 
	if(list == NULL){
		return NULL;
	}else if(cll_length(list)==1){
		free(list);
		return NULL; 
	}
	(list->prev)->next = list->next;
	(list->next)->prev = list->prev;
	cll_node *next = list->next; 
	free(list);  		
	return next; 
}


cll_node *cll_insert(int value, cll_node *list, int before) {  
    //TODO: Implement this function, see header file for description
    //TODO: Update return statement. 
	cll_node *newNode = (cll_node *) malloc(sizeof(cll_node)); 
	newNode->value = value; 
	if(list == NULL){
		newNode -> is_head = 1; 
		newNode -> next = newNode; 
		newNode -> prev = newNode; 
	}else if(before == 0){
		newNode->prev = list;
		newNode->next = list->next;
		(list->next)->prev = newNode;
		list->next = newNode; 
	}else{
		newNode->next = list; 
		newNode->prev = list->prev; 
		(list->prev)->next = newNode; 
		list->prev = newNode; 
	}
	return newNode;
}


/**
 * Displays the contents of the list separated by commas and surrounded by
 * brackets, with the pointed-to node highlighted with asterisks.
 *
 * Reference solution provided with assignment description
 */
void cll_show(cll_node *list) {
    // Find the head of the linked list
    cll_node *head = cll_head(list);
    cll_node *ptr = head;
    // Print opening [
    putchar('[');
    // Loop through list printing values
    if (ptr) {
        do {
            if (!ptr->is_head) 
                printf(", "); // include a comma if not the first element
            if (ptr == list) 
                putchar('*'); // include * surrounding parameter element
            printf("%d", ptr->value);
            if (ptr == list) 
                putchar('*');
            ptr = ptr->next; // next pointer
        } while (ptr != head);
    }
    // Print closing ]
    puts("]");
}


int main(int argc, const char *argv[]) {

    // Example debugging code.  You should write other
    // tests, including testing corner cases.
    cll_node *x = NULL;
    putchar('A'); cll_show(x);
    x = cll_insert(25, x, 1);
    putchar('B'); cll_show(x);
    x = cll_insert(1, x, 0);
    putchar('C'); cll_show(x);
    x = cll_insert(98, x, 1);
    putchar('D'); cll_show(x);
    x = cll_insert(0, x, 1);
    putchar('E'); cll_show(x);
    x = cll_insert(-8, cll_tail(x), 0);
    putchar('F'); cll_show(x);
    cll_node *y = cll_head(x);
    putchar('G'); cll_show(y);
    printf("Length: %lu (or %lu)\n", cll_length(y), cll_length(x));
    x = cll_remove(x);
    putchar('H'); cll_show(x);
    putchar('I'); cll_show(y);
    x = cll_remove(cll_find(y, 98));
    putchar('J'); cll_show(x);
    putchar('K'); cll_show(y);

    return 0;
}
