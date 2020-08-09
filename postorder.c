#include <stdio.h>
#include <time.h>
#include "data_structures.c"
#define TREE_SIZE 64

/* Author: W-Flowers
//
// This module exists to demonstrate an implementation of a postorder traversal of a binary tree.
// It is a proof of concept. The insertion is ridiculously slow (O(n) for each insertion)
*/

int main(){
	clock_t start_t, mid_t, end_t, total_t;
	start_t = clock();
	int array[TREE_SIZE];
	for(int i = 0; i < TREE_SIZE; i++) array[i] = i+1;
	struct bt_node *root = tree_init(&array[0]);
	for(int i = 1; i < TREE_SIZE; i++) add_node(&array[i], root);
	mid_t = clock();
	
	//postorder traversal algorithm
	struct bt_node *t = root;
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
	//end postorder traversal algo
	
	destroy_tree(root);
	destroy_stack(s);
	end_t = clock();
	total_t = end_t - start_t;
	printf("Time Elapsed: %lu Setup: %lu Traversal: %lu\n", total_t, mid_t - start_t, end_t - mid_t);
	return 0;
}