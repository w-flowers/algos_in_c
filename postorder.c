#include <stdio.h>
#include "data_structures.c"

/* Author: W-Flowers
//
// This module exists to demonstrate an implementation of a postorder traversal of a binary tree.
// It is a proof of concept.
*/

int main(){
	int array[1024];
	for(int i = 0; i<1024; i++) array[i] = i+1;
	struct t_node *root = tree_init(&array[0]);
	for(int i = 2; i < 1024; i++) add_node(&array[i], root);
	struct t_node *t = root;
	struct stack *s = stack_init();
	do{
		while(t != NULL){
			if(t->r != NULL){
				push(s, t->r);
			}
			push(s, t);
			t = t->l;
		}
		t = pop(s);
		if(t->r == peek(s)){
			pop(s);
			push(s, t);
			t = t->r;
		}
		else{
			printf("%d\n", *(int *)(t->key));
			t = NULL;
		}
	}while(!stackempty(s));
	destroy_tree(root);
	destroy_stack(s);
	return 0;
}