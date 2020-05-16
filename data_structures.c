#include <stdlib.h>

/* Author: William Flowers
//
// Purpose: This library exists to provide some basic data structures and operations pertaining to 
// them. Defined herein are trees, linked lists, stacks and queues
//
// Usage: All of these data structures take an integer "key". One possible way of using these more
// generally would be to store your data in an array, and use these keys to access those elements.
*/

struct t_node {
	int key;
	struct t_node *l;
	struct t_node *r;
};

struct ll_node {
	int key;
	struct ll_node *next;
};

struct queue {
	struct ll_node *front;
	struct ll_node *back;
};

struct stack {
	struct ll_node *top;
}

//Creates an empty queue, with front and back initialised as NULL
struct queue *queue_init(int k);

//Adds an element to the back of the passed queue. If queue is empty, element becomes front and back
int put(int k, struct queue *q);

//Gets an element from the front of a queue. If element is the last element of the queue, the back
//of the queue is set to NULL as well
//If not called in conjunction with put, may result in freeing of non-allocated memory
int get(struct queue *q);

//returns 0 if the queue has elements, or 1 if it does not
int queueempty(struct queue *q);

//creates an empty stack, with top initialised as NULL
struct stack *stack_init(int k);

//Adds an element to the top of the stack.
int push(struct stack *s, int k);

//Gets an element from the top of the stack. If stack is empty, returns 0
//If called not in conjunction with push, may result in freeing of non-allocated memory
int pop(struct stack *s);

//returns 0 if the stack has elements, else returns 1
int stackempty(struct stack *s);

//A function that takes an integer key k and initialises a tree with a root node with a value of k
struct t_node *tree_init(int k);

//A function that adds a node to the tree, going through the tree level by level, left to right, until
//it finds a NULL, at which point it adds the integer k, returns 0 for success, 1 for malloc failure
//If passed a NULL pointer, makes the new element the root node
int t_add_node(int k, struct node *tree_p);

struct queue *queue_init(int k){
	struct queue *p = malloc(sizeof(struct queue));
	if(p){
		p->front = NULL;
		p->back = NULL;
		return p;
	}
	else return NULL;
}

int put(int k, struct queue *q){
	struct ll_node *new_ele = malloc(sizeof(struct ll_node));
	if(!new_ele) return 1;
	new_ele->key = k;
	new_ele->next = NULL;
	if(q->back == NULL){
		q->front = new_ele;
		q->back = new_ele;
	}
	else{
		q->back->next = new_ele;
		q->back = new_ele;
	}
	return 0;
}

int get(struct queue *q){
	if(q->front == NULL) return 0;
	int k = q->front->key;
	struct ll_node *dlt = q->front;
	q->front = q->front->next;
	if(q->front == NULL) q->back = NULL;
	free(dlt);
	return k;
}

int queueempty(struct queue *q){
	if(q->front == NULL) return 1;
	else return 0;
}

struct stack *stack_init(int k){
	struct queue *s = malloc(sizeof(struct stack));
	if(s){
		s->top = NULL;
		return s;
	}
	else return NULL;
}

int push(struct stack *s, int k){
	struct ll_node *new_ele = malloc(sizeof(struct ll_node));
	if(!new_ele) return 1;
	new_ele->key = k;
	new_ele->next = s->top;
	s->top = new_ele;
	return 0;
}

int pop(struct stack *s){
	if(s->top == NULL) return 0;
	int k = s->top->key;
	struct ll_node *dlt = s->top;
	s->top = s->top->next;
	free(dlt);
	return k;
}

int stackempty(struct stack *s){
	if(s->top == NULL) return 1;
	else return 0;
}

struct t_node *tree_init(int k){
	struct t_node *p = malloc(sizeof(struct t_node));
	if(p){
		p->l = NULL;
		p->r = NULL;
		key = k;
		return p;
	}
	else return NULL;
}

int add_node(int k, struct t_node *tree_p){
	struct t_node *p = malloc(sizeof(struct node));
	if(p){
		p->l = NULL;
		p->r = NULL;
		p->key = k;
		while(tree_p != NULL){
			if(tree_p->l == NULL) tree_p->l = p;
			if(tree_p->r == )
		}
		else tree_p = p;
	}
	else return 1;
}