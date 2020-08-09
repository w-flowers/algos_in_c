#include <stdlib.h>
#include <string.h>
#define DATATYPE bt_node_int *
#define MARKER btree

/* Author: W-Flowers
//
// Purpose: This library exists to provide some basic data structures and operations pertaining to 
// them. Defined herein are trees, linked lists, stacks and queues. The main intended usage of this
// module is to demonstrate example algorithms for the various data structures defined herein. This
// module is NOT intended for usage in production code.
//
// Usage: All of these data structures take a "key" of the type defined by the macro DATATYPE. It 
// is the responsibility of the caller to ensure that the data entered and returned is of the 
// correct type. The macro MARKER is there to give functions alternate names in case of multiple
// usages.
*/



struct bt_node_MARKER {
	DATATYPE key;
	struct bt_node_MARKER  *l;
	struct bt_node_MARKER  *r;
};

struct ll_node_MARKER  {
	DATATYPE key;
	struct ll_node_MARKER  *next;
};

struct queue_MARKER  {
	struct ll_node_MARKER  *front;
	struct ll_node_MARKER  *back;
};

struct stack_MARKER  {
	DATATYPE *array;
	int top;
	int size;
};

//Creates an empty queue, with front and back initialised as NULL
struct queue_MARKER  *queue_init_MARKER();

//Adds an element to the back of the passed queue. If queue is empty, element becomes front and back
int put_MARKER(struct queue_MARKER  *q, DATATYPE k);

//Gets an element from the front of a queue. If element is the last element of the queue, the back
//of the queue is set to NULL as well
//If not called in conjunction with put, may result in freeing of non-allocated memory
DATATYPE get_MARKER(struct queue_MARKER  *q);

//returns 0 if the queue has elements, or 1 if it does not
int queueempty_MARKER(struct queue_MARKER  *q);

//De-initialises the queue and frees all allocated memory
int destroy_queue_MARKER(struct queue_MARKER  *q);

//creates an empty stack_MARKER , with top initialised as NULL
struct stack_MARKER  *stack_init_MARKER();

//Adds an element to the top of the stack.
int push_MARKER(struct stack_MARKER *s, DATATYPE k);

//Gets an element from the top of the stack. If stack is empty, returns NULL
//If called not in conjunction with push, may result in freeing of non-allocated memory
DATATYPE pop_MARKER(struct stack_MARKER  *s);


//Looks at top element of stack
DATATYPE peek_MARKER(struct stack_MARKER  *s);

//returns 0 if the stack has elements, else returns 1
int stackempty_MARKER(struct stack_MARKER *s);

int destroy_stack_MARKER(struct stack_MARKER  *s);

//A function that takes an integer key k and initialises a tree with a root node with a value of k
struct bt_node_MARKER  *tree_init_MARKER(DATATYPE k);

//A function that adds a node to the tree, going through the tree level by level, left to right, until
//it finds a NULL, at which point it adds the integer k, returns 0 for success, 1 for malloc failure
//If passed a NULL pointer, makes the new element the root node
int t_add_node_MARKER(DATATYPE k, struct bt_node_MARKER  *tree_p);

//destroy tree moves through the tree in level order and deallocates the memory for the structure.
//This must be called if a tree is created and built using "tree_init" and "t_add_node".
//Do not call this on any tree allocated manually on the stack.
int destroy_tree_MARKER(struct bt_node_MARKER  *tree_p);

struct queue_MARKER  *queue_init_MARKER(){
	struct queue_MARKER  *p = malloc(sizeof struct queue_MARKER));
	if(p){
		p->front = NULL;
		p->back = NULL;
		return p;
	}
	else return NULL;
}

int put_MARKER(struct queue_MARKER  *q, DATATYPE k){
	struct ll_node_MARKER  *new_ele = malloc(sizeof(struct ll_node_MARKER ));
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

DATATYPE get_MARKER(struct queue_MARKER  *q){
	if(q->front == NULL) return 0;
	DATATYPE k = q->front->key;
	struct ll_node_MARKER  *dlt = q->front;
	q->front = q->front->next;
	if(q->front == NULL) q->back = NULL;
	free(dlt);
	return k;
}

int queueempty_MARKER(struct queue_MARKER  *q){
	if(q->front == NULL) return 1;
	else return 0;
}

int destroy_queue_MARKER(struct queue_MARKER  *q){
	for(struct ll_node_MARKER  *dummy = q->front; dummy != NULL;){
		struct ll_node_MARKER  *dlt = dummy;
		dummy = dummy->next;
		free(dlt);
	}
	free(q);
	return 0;
}

struct stack_MARKER  *stack_init_MARKER(){
	struct stack_MARKER  *s = malloc(sizeof struct stack_MARKER));
	if(s){
		s->size = 64;
		s->array = malloc((s->size)*sizeof(*(s->array)));
		s->top = 0;
		return s;
	}
	else return NULL;
}

int push_MARKER(struct stack_MARKER  *s, DATATYPE k){
	if(s->top == s->size){
		DATATYPE *dmyptr = s->array;
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

DATATYPE pop_MARKER(struct stack_MARKER  *s){
	if(s->top <= 0) return 0;
	s->top--;
	DATATYPE k = *((s->array)+(s->top));
	return k;
}

DATATYPE peek_MARKER(struct stack_MARKER  *s){
	if(!stackempty_MARKER(s)){
		return *((s->array)-(s->top)-1);
	}
	else return 0;
}

int stackempty_MARKER(struct stack_MARKER  *s){
	if(s->top == 0) return 1;
	else return 0;
}

int destroy_stack_MARKER(struct stack_MARKER  *s){
	free(s->array);
	free(s);
	return 0;
}

struct bt_node_MARKER  *tree_init_MARKER(DATATYPE k){
	struct bt_node_MARKER  *p = malloc(sizeof(struct bt_node_MARKER ));
	if(p){
		p->l = NULL;
		p->r = NULL;
		p->key = k;
		return p;
	}
	else return NULL;
}

int add_node_MARKER(DATATYPE k, struct bt_node_MARKER  *tree_p){
	struct bt_node_MARKER  *p = malloc(sizeof(struct bt_node_MARKER ));
	struct bt_node_MARKER  *t = tree_p;
	if(!p) return 1;
	struct queue_MARKER  *q = queue_init_MARKER();
	if(!q) return 1;
	put_MARKER(q, t);
	p->l = NULL;
	p->r = NULL;
	p->key = k;
	while(!queueempty_MARKER(q)){
		if(t->l == NULL){
			t->l = p;
			break;
		}
		else{
			put_MARKER(q, t->l);
		}
		if(t->r == NULL){
			t->r = p;
			break;
		}
		else{
			put_MARKER(q, t->r);
		}
		t = get_MARKER(q);
	}
	destroy_queue_MARKER(q);
	return 0;
}

int destroy_tree_MARKER(struct bt_node_MARKER  *tree_p){
	if(tree_p == NULL) return 0;
	struct queue_MARKER  *q = queue_init_MARKER();
	if(!q) return 1;
	struct bt_node_MARKER  *t = tree_p;
	put_MARKER(q, t);
	while(!queueempty_MARKER(q)){
		t = get_MARKER(q);
		if(t->l != NULL){
			put_MARKER(q, t->l);
		}
		if(t->r != NULL){
			put_MARKER(q, t->r);
		}
		free(t);
	}
	destroy_queue_MARKER(q);
	return 0;
}