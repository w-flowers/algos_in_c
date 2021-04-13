#include <stdlib.h>


/* Author: W-Flowers
//
// Purpose: This library exists to provide some basic data structures and operations pertaining to 
// them. Defined herein are trees, linked lists, stacks and queues. The main intended usage of this
// module is to demonstrate example algorithms for the various data structures defined herein. This
// module is NOT intended for usage in production code.
//
// Usage: All of these data structures take an void pointer "key". It is the responsibility of the
// caller to ensure that the data entered and returned is of the correct type.
*/



struct bt_node {
	void *key;
	struct bt_node *l;
	struct bt_node *r;
};

struct ll_node {
	void *key;
	struct ll_node *next;
};

struct queue {
	struct ll_node *front;
	struct ll_node *back;
};

struct stack {
	struct ll_node *top;
	struct ll_node *freelist;
};

//Creates an empty queue, with front and back initialised as NULL
struct queue *queue_init();

//Adds an element to the back of the passed queue. If queue is empty, element becomes front and back
int put(struct queue *q, void *k);

//Gets an element from the front of a queue. If element is the last element of the queue, the back
//of the queue is set to NULL as well
//If not called in conjunction with put, may result in freeing of non-allocated memory
void *get(struct queue *q);

//returns 0 if the queue has elements, or 1 if it does not
int queueempty(struct queue *q);

//De-initialises the queue and frees all allocated memory
int destroy_queue(struct queue *q);

//creates an empty stack, with top initialised as NULL
struct stack *stack_init();

//Adds an element to the top of the stack.
int push(struct stack *s, void *k);

//Gets an element from the top of the stack. If stack is empty, returns NULL
//If called not in conjunction with push, may result in freeing of non-allocated memory
void *pop(struct stack *s);


//Looks at top element of stack
void *peek(struct stack *s);

//returns 0 if the stack has elements, else returns 1
int stackempty(struct stack *s);

int destroy_stack(struct stack *s);

//A function that takes an integer key k and initialises a tree with a root node with a value of k
struct bt_node *tree_init(void *k);

//A function that adds a node to the tree, going through the tree level by level, left to right, until
//it finds a NULL, at which point it adds the integer k, returns 0 for success, 1 for malloc failure
//If passed a NULL pointer, makes the new element the root node
int t_add_node(void *k, struct bt_node *tree_p);

//destroy tree moves through the tree in level order and deallocates the memory for the structure.
//This must be called if a tree is created and built using "tree_init" and "t_add_node".
//Do not call this on any tree allocated manually on the stack.
int destroy_tree(struct bt_node *tree_p);

struct queue *queue_init(){
	struct queue *p = malloc(sizeof(struct queue));
	if(p){
		p->front = NULL;
		p->back = NULL;
		return p;
	}
	else return NULL;
}

int put(struct queue *q, void *k){
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

void *get(struct queue *q){
	if(q->front == NULL) return NULL;
	void *k = q->front->key;
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

int destroy_queue(struct queue *q){
	for(struct ll_node *dummy = q->front; dummy != NULL;){
		struct ll_node *dlt = dummy;
		dummy = dummy->next;
		free(dlt);
	}
	free(q);
	return 0;
}

struct stack *stack_init(){
	struct stack *s = malloc(sizeof(struct stack));
	if(s){
		s->top = NULL;
		s->freelist = NULL;
		return s;
	}
	else return NULL;
}

int push(struct stack *s, void *k){
	if(s->freelist != NULL){
		struct ll_node *dmynode = NULL;
		s->freelist->key = k;
		dmynode = s->freelist->next;
		s->freelist->next = s->top;
		s->top = s->freelist;
		s->freelist = dmynode;
	}
	else{
		struct ll_node *new_ele = malloc(sizeof(struct ll_node));
		if(!new_ele) return 1;
		new_ele->key = k;
		new_ele->next = s->top;
		s->top = new_ele;
	}
	return 0;
}

void *pop(struct stack *s){
	if(s->top == NULL) return NULL;
	void *k = s->top->key;
	struct ll_node *dlt = s->top;
	s->top = s->top->next;
	dlt->next = s->freelist;
	s->freelist = dlt;
	return k;
}

void *peek(struct stack *s){
	if(!stackempty(s)){
		return s->top->key;
	}
	else return 0;
}

int stackempty(struct stack *s){
	if(s->top == NULL) return 1;
	else return 0;
}

int destroy_stack(struct stack *s){
	for(struct ll_node *dummy = s->top; dummy != NULL;){
		struct ll_node *dlt = dummy;
		dummy = dummy->next;
		free(dlt);
	}
	for(struct ll_node *dummy = s->freelist; dummy != NULL;){
		struct ll_node *dlt = dummy;
		dummy = dummy->next;
		free(dlt);
	}
	free(s);
	return 0;
}

struct bt_node *tree_init(void *k){
	struct bt_node *p = malloc(sizeof(struct bt_node));
	if(p){
		p->l = NULL;
		p->r = NULL;
		p->key = k;
		return p;
	}
	else return NULL;
}

int add_node(void *k, struct bt_node *tree_p){
	struct bt_node *p = malloc(sizeof(struct bt_node));
	struct bt_node *t = tree_p;
	if(!p) return 1;
	struct queue *q = queue_init();
	if(!q) return 1;
	put(q, t);
	p->l = NULL;
	p->r = NULL;
	p->key = k;
	while(!queueempty(q)){
		t = get(q);
		if(t->l == NULL){
			t->l = p;
			break;
		}
		else{
			put(q, t->l);
		}
		if(t->r == NULL){
			t->r = p;
			break;
		}
		else{
			put(q, t->r);
		}
	}
	destroy_queue(q);
	return 0;
}

int destroy_tree(struct bt_node *tree_p){
	if(tree_p == NULL) return 0;
	struct queue *q = queue_init();
	if(!q) return 1;
	struct bt_node *t = tree_p;
	put(q, t);
	while(!queueempty(q)){
		t = get(q);
		if(t->l != NULL){
			put(q, t->l);
		}
		if(t->r != NULL){
			put(q, t->r);
		}
		free(t);
	}
	destroy_queue(q);
	return 0;
}
