#include <stdlib.h>
#include <string.h>

/* Author: W-Flowers
//
// Purpose: This library exists to provide some basic data structures and operations pertaining to 
// them. Defined herein are trees, linked lists, stacks and queues. The main intended usage of this
// module is to demonstrate example algorithms for the various data structures defined herein. This
// module is NOT intended for usage in production code.
//
// Usage: 
*/


#ifndef MACRO1
#define MACRO1

struct ll_node_btree  {
	bt_node_int * key;
	struct ll_node_btree  *next;
};

struct queue_btree  {
	struct ll_node_btree  *front;
	struct ll_node_btree  *back;
	struct ll_node_btree *freelist;
};

struct stack_btree  {
	bt_node_int * *array;
	int top;
	int size;
};

//Creates an empty queue, with front and back initialised as NULL
struct queue_btree  *queue_init_btree();

//Adds an element to the back of the passed queue. If queue is empty, element becomes front and back
int put_btree(struct queue_btree  *q, bt_node_int * k);

//Gets an element from the front of a queue. If element is the last element of the queue, the back
//of the queue is set to NULL as well
//If not called in conjunction with put, may result in freeing of non-allocated memory
bt_node_int * get_btree(struct queue_btree  *q);

//returns 0 if the queue has elements, or 1 if it does not
int queueempty_btree(struct queue_btree  *q);

//De-initialises the queue and frees all allocated memory
int destroy_queue_btree(struct queue_btree  *q);

//creates an empty stack_btree , with top initialised as NULL
struct stack_btree  *stack_init_btree();

//Adds an element to the top of the stack.
int push_btree(struct stack_btree *s, bt_node_int * k);

//Gets an element from the top of the stack. If stack is empty, returns NULL
//If called not in conjunction with push, may result in freeing of non-allocated memory
bt_node_int * pop_btree(struct stack_btree  *s);


//Looks at top element of stack
bt_node_int * peek_btree(struct stack_btree  *s);

//returns 0 if the stack has elements, else returns 1
int stackempty_btree(struct stack_btree *s);

int destroy_stack_btree(struct stack_btree  *s);

struct queue_btree  *queue_init_btree(){
	struct queue_btree  *p = malloc(sizeof struct queue_btree));
	if(p){
		p->front = NULL;
		p->back = NULL;
		p->freelist = NULL;
		return p;
	}
	else return NULL;
}

int put_btree(struct queue_btree  *q, bt_node_int * k){
	if(freelist != NULL){
		struct ll_node_btree *dummy = freelist;
		freelist = freelist->next;
		dummy->key = k;
		dummy->next = NULL;
		if(q->back == NULL){
			q->front = dummy;
			q->back = dummy;
		}
		else{
			q->back->next = dummy;
			q->back = dummy;
		}
		return 0;
	}
	struct ll_node_btree  *new_ele = malloc(sizeof(struct ll_node_btree));
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

bt_node_int * get_btree(struct queue_btree  *q){
	if(q->front == NULL) return 0;
	bt_node_int * k = q->front->key;
	struct ll_node_btree  *dlt = q->front;
	q->front = q->front->next;
	if(q->front == NULL) q->back = NULL;
	dlt->next = freelist;
	freelist = dlt;
	return k;
}

int queueempty_btree(struct queue_btree  *q){
	if(q->front == NULL) return 1;
	else return 0;
}

int destroy_queue_btree(struct queue_btree  *q){
	for(struct ll_node_btree  *dummy = q->front; dummy != NULL;){
		struct ll_node_btree  *dlt = dummy;
		dummy = dummy->next;
		free(dlt);
	}
	for(struct ll_node_btree  *dummy = q->freelist; dummy != NULL;){
			struct ll_node_btree  *dlt = dummy;
			dummy = dummy->next;
			free(dlt);
		}
	free(q);
	return 0;
}

struct stack_btree  *stack_init_btree(){
	struct stack_btree  *s = malloc(sizeof struct stack_btree));
	if(s){
		s->size = 64;
		s->array = malloc((s->size)*sizeof(*(s->array)));
		s->top = 0;
		return s;
	}
	else return NULL;
}

int push_btree(struct stack_btree  *s, bt_node_int * k){
	if(s->top == s->size){
		bt_node_int * *dmyptr = s->array;
		s->array = malloc(2*(s->size)*sizeof(*s->array));
		if(!s->array) return 1;
		
		memcpy(s->array, dmyptr, (s->size)*sizeof(*dmyptr));
		s->size *= 2;
		free(dmyptr);
		*((s->array)+(s->top)) = k;
		s->top++;
	}
	*((s->array)+(s->top)) = k;
	s->top++;
	return 0;
}

bt_node_int * pop_btree(struct stack_btree *s){
	if(s->top <= 0) return 0;
	s->top--;
	bt_node_int * k = *((s->array)+(s->top));
	return k;
}

bt_node_int * peek_btree(struct stack_btree *s){
	if(!stackempty_btree(s)){
		return *((s->array)-(s->top)-1);
	}
	else return 0;
}

int stackempty_btree(struct stack_btree *s){
	if(s->top == 0) return 1;
	else return 0;
}

int destroy_stack_btree(struct stack_btree *s){
	free(s->array);
	free(s);
	return 0;
}

#endif