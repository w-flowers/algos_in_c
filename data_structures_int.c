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



struct bt_node_int {
	int key;
	struct bt_node_int  *l;
	struct bt_node_int  *r;
};

struct ll_node_int  {
	int key;
	struct ll_node_int  *next;
};

struct queue_int  {
	struct ll_node_int  *front;
	struct ll_node_int  *back;
};

struct stack_int  {
	int *array;
	int top;
	int size;
};

struct ll_node_btree  {
	struct bt_node_int * key;
	struct ll_node_btree  *next;
};

struct queue_btree  {
	struct ll_node_btree  *front;
	struct ll_node_btree  *back;
};

struct stack_btree  {
	struct bt_node_int * *array;
	int top;
	int size;
};

//Creates an empty queue, with front and back initialised as NULL
struct queue_btree  *queue_init_btree();

//Adds an element to the back of the passed queue. If queue is empty, element becomes front and back
int put_btree(struct queue_btree  *q, struct bt_node_int * k);

//Gets an element from the front of a queue. If element is the last element of the queue, the back
//of the queue is set to NULL as well
//If not called in conjunction with put, may result in freeing of non-allocated memory
struct bt_node_int * get_btree(struct queue_btree  *q);

//returns 0 if the queue has elements, or 1 if it does not
int queueempty_btree(struct queue_btree  *q);

//De-initialises the queue and frees all allocated memory
int destroy_queue_btree(struct queue_btree  *q);

//creates an empty stack_btree , with top initialised as NULL
struct stack_btree  *stack_init_btree();

//Adds an element to the top of the stack.
int push_btree(struct stack_btree *s, struct bt_node_int * k);

//Gets an element from the top of the stack. If stack is empty, returns NULL
//If called not in conjunction with push, may result in freeing of non-allocated memory
struct bt_node_int * pop_btree(struct stack_btree  *s);


//Looks at top element of stack
struct bt_node_int * peek_btree(struct stack_btree  *s);

//returns 0 if the stack has elements, else returns 1
int stackempty_btree(struct stack_btree *s);

int destroy_stack_btree(struct stack_btree  *s);

//Creates an empty queue, with front and back initialised as NULL
struct queue_int  *queue_init_int();

//Adds an element to the back of the passed queue. If queue is empty, element becomes front and back
int put_int(struct queue_int  *q, int k);

//Gets an element from the front of a queue. If element is the last element of the queue, the back
//of the queue is set to NULL as well
//If not called in conjunction with put, may result in freeing of non-allocated memory
int get_int(struct queue_int  *q);

//returns 0 if the queue has elements, or 1 if it does not
int queueempty_int(struct queue_int  *q);

//De-initialises the queue and frees all allocated memory
int destroy_queue_int(struct queue_int  *q);

//creates an empty stack_int , with top initialised as NULL
struct stack_int  *stack_init_int();

//Adds an element to the top of the stack.
int push_int(struct stack_int *s, int k);

//Gets an element from the top of the stack. If stack is empty, returns NULL
//If called not in conjunction with push, may result in freeing of non-allocated memory
int pop_int(struct stack_int  *s);


//Looks at top element of stack
int peek_int(struct stack_int  *s);

//returns 0 if the stack has elements, else returns 1
int stackempty_int(struct stack_int *s);

int destroy_stack_int(struct stack_int  *s);

//A function that takes an integer key k and initialises a tree with a root node with a value of k
struct bt_node_int  *tree_init_int(int k);

int balance_tree(struct bt_node_int *t);

//A function that adds a node to the tree, going through the tree level by level, left to right, until
//it finds a NULL, at which point it adds the integer k, returns 0 for success, 1 for malloc failure
//If passed a NULL pointer, makes the new element the root node
int t_add_node_int(int k, struct bt_node_int  *tree_p);

//destroy tree moves through the tree in level order and deallocates the memory for the structure.
//This must be called if a tree is created and built using "tree_init" and "t_add_node".
//Do not call this on any tree allocated manually on the stack.
int destroy_tree_int(struct bt_node_int  *tree_p);

struct queue_btree  *queue_init_btree(){
	struct queue_btree  *p = malloc(sizeof (struct queue_btree));
	if(p){
		p->front = NULL;
		p->back = NULL;
		return p;
	}
	else return NULL;
}

int put_btree(struct queue_btree  *q, struct bt_node_int * k){
	struct ll_node_btree  *new_ele = malloc(sizeof(struct ll_node_btree ));
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

struct bt_node_int * get_btree(struct queue_btree  *q){
	if(q->front == NULL) return 0;
	struct bt_node_int * k = q->front->key;
	struct ll_node_btree  *dlt = q->front;
	q->front = q->front->next;
	if(q->front == NULL) q->back = NULL;
	free(dlt);
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
	free(q);
	return 0;
}

struct stack_btree  *stack_init_btree(){
	struct stack_btree  *s = malloc(sizeof (struct stack_btree));
	if(s){
		s->size = 64;
		s->array = malloc((s->size)*sizeof(*(s->array)));
		s->top = 0;
		return s;
	}
	else return NULL;
}

 int push_btree(struct stack_btree  *s, struct bt_node_int * k){
	if(s->top == s->size){
		struct bt_node_int * *dmyptr = s->array;
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

 struct bt_node_int * pop_btree(struct stack_btree *s){
	if(s->top <= 0) return 0;
	s->top--;
	struct bt_node_int * k = *((s->array)+(s->top));
	return k;
}

struct bt_node_int * peek_btree(struct stack_btree *s){
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

struct queue_int  *queue_init_int(){
	struct queue_int  *p = malloc(sizeof (struct queue_int));
	if(p){
		p->front = NULL;
		p->back = NULL;
		return p;
	}
	else return NULL;
}

int put_int(struct queue_int  *q, int k){
	struct ll_node_int  *new_ele = malloc(sizeof(struct ll_node_int ));
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

int get_int(struct queue_int  *q){
	if(q->front == NULL) return 0;
	int k = q->front->key;
	struct ll_node_int  *dlt = q->front;
	q->front = q->front->next;
	if(q->front == NULL) q->back = NULL;
	free(dlt);
	return k;
}

int queueempty_int(struct queue_int  *q){
	if(q->front == NULL) return 1;
	else return 0;
}

int destroy_queue_int(struct queue_int  *q){
	for(struct ll_node_int  *dummy = q->front; dummy != NULL;){
		struct ll_node_int  *dlt = dummy;
		dummy = dummy->next;
		free(dlt);
	}
	free(q);
	return 0;
}

struct stack_int  *stack_init_int(){
	struct stack_int  *s = malloc(sizeof (struct stack_int));
	if(s){
		s->size = 64;
		s->array = malloc((s->size)*sizeof(*(s->array)));
		s->top = 0;
		return s;
	}
	else return NULL;
}

int push_int(struct stack_int  *s, int k){
	if(s->top == s->size){
		int *dmyptr = s->array;
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

int pop_int(struct stack_int  *s){
	if(s->top <= 0) return 0;
	s->top--;
	int k = *((s->array)+(s->top));
	return k;
}

int peek_int(struct stack_int  *s){
	if(!stackempty_int(s)){
		return *((s->array)-(s->top)-1);
	}
	else return 0;
}

int stackempty_int(struct stack_int  *s){
	if(s->top == 0) return 1;
	else return 0;
}

int destroy_stack_int(struct stack_int *s){
	free(s->array);
	free(s);
	return 0;
}

struct bt_node_int  *tree_init_int(int k){
	struct bt_node_int  *p = malloc(sizeof(struct bt_node_int ));
	if(p){
		p->l = NULL;
		p->r = NULL;
		p->key = k;
		return p;
	}
	else return NULL;
}

int size_tree_int(struct bt_node_int *t){
	if(t == NULL) return 0;
	else return 1 + size_tree_int(t->l) + size_tree_int(t->r);
}

int balance_tree_int(struct bt_node_int *t){
	
}

int add_node_int(int k, struct bt_node_int  *tree_p){
	struct bt_node_int  *p = malloc(sizeof(struct bt_node_int ));
	struct bt_node_int  *t = tree_p;
	if(!p) return 1;
	struct queue_btree  *q = queue_init_btree();
	if(!q) return 1;
	put_btree(q, t);
	p->l = NULL;
	p->r = NULL;
	p->key = k;
	while(!queueempty_btree(q)){
		if(t->l == NULL){
			t->l = p;
			break;
		}
		else{
			put_btree(q, t->l);
		}
		if(t->r == NULL){
			t->r = p;
			break;
		}
		else{
			put_btree(q, t->r);
		}
		t = get_btree(q);
	}
	destroy_queue_btree(q);
	return 0;
}

int destroy_tree_int(struct bt_node_int  *tree_p){
	if(tree_p == NULL) return 0;
	struct queue_btree  *q = queue_init_btree();
	if(!q) return 1;
	struct bt_node_int  *t = tree_p;
	put_btree(q, t);
	while(!queueempty_btree(q)){
		t = get_btree(q);
		if(t->l != NULL){
			put_btree(q, t->l);
		}
		if(t->r != NULL){
			put_btree(q, t->r);
		}
		free(t);
	}
	destroy_queue_btree(q);
	return 0;
}