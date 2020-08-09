#include "data_structures_int.c"
#include <time.h>
#include <stdio.h>
#include <string.h>
#define TREE_SIZE 150000000

long external_path_length(struct bt_node_int *t, long level);

long external_path_length_norc(struct bt_node_int *t);

long external_path_length_norc_noexpstack(struct bt_node_int *t);

struct bt_node_int *build_tree(long size);

int main(){
	/*int array[TREE_SIZE];
	for(int i = 0; i < TREE_SIZE; i++) array[i] = i+1;
	struct bt_node_int *root = tree_init_int(array[0]);
	for(int i = 1; i < TREE_SIZE; i++) add_node_int(array[i], root);*/
	for(int i = 49999999; i < 50000000; i++){
		clock_t mid_t, end_t, mid_tt, end_tt, midttt, endttt;
		struct bt_node_int *root = build_tree(i);
		mid_t = clock();
		long length = external_path_length(root, 0);
		printf("External Path Length is %ld\n", length);
		end_t = clock();
		printf("recursive algo took %lu cycles\n", end_t - mid_t);
		/*mid_tt = clock();
		int length2 = external_path_length_norc(root);
		printf("External Path Length is %d\n", length2);
		end_tt = clock();
		printf("non-recursive algo took %lu cycles\n", end_tt - mid_tt);*/
		midttt = clock();
		long length3 = external_path_length_norc_noexpstack(root);
		printf("External Path Length is %ld\n", length3);
		endttt = clock();
		printf("non-recursive algo nostack took %lu cycles\n", endttt - midttt);
		//destroy_tree_int(root);
		return 0;
	}
	return 0;
}

 long external_path_length(struct bt_node_int *t, long level){
	if(t == NULL) return level;
	else return level + external_path_length(t->l, level+1) + external_path_length(t->r, level+1);
}

//non-recursive implementation
long external_path_length_norc(struct bt_node_int *t){
	struct stack_btree *nodes = stack_init_btree();
	
	struct stack_int *dmy_nodes = stack_init_int();
	
	long level = 0;
	long length = 0;
	push_btree(nodes, t);
	push_int(dmy_nodes, level);
	
	while(!stackempty_btree(nodes)){
		t = pop_btree(nodes);
		level = pop_int(dmy_nodes);
		length += level;
		if(t != NULL){
			push_btree(nodes, t->r);
			push_int(dmy_nodes, level+1);
			push_btree(nodes, t->l);
			push_int(dmy_nodes, level+1);
		}
	}
	destroy_stack_btree(nodes);
	destroy_stack_int(dmy_nodes);
	return length;
}

 long external_path_length_norc_noexpstack(struct bt_node_int *t){
	int size = 27;
	//int *arrayint = malloc(size * sizeof(*arrayint));
	//struct bt_node_int **arraybtree = malloc(size * sizeof(*arraybtree));
	int arrayint[27];
	struct bt_node_int *arraybtree[27];
	int top = 0;
	long level = 0;
	long length = 0;
	*arrayint = level;
	top++;
	*arraybtree = t;
	while(top){
		t = *(arraybtree + top - 1);
		level = *(arrayint + top - 1);
		top--;
		length += level;
		if(t != NULL){
			*(arraybtree + top) = t->r;
			*(arrayint + top) = level+1;
			top++;
			if(top == size){
				return -1;
				/*int *dmyint = arrayint;
				arrayint = malloc(2* size * sizeof(*arrayint));
				struct bt_node_int **dmybtree = arraybtree;
				arraybtree = malloc(2 * size * sizeof(*arraybtree));
				memcpy(arrayint, dmyint, size*sizeof(*dmyint));
				memcpy(arraybtree, dmybtree, size*sizeof(*dmybtree));
				free(dmyint);
				free(dmybtree);
				size *= 2;*/
			}
			*(arraybtree + top) = t->l;
			*(arrayint + top) = level+1;
			top++;
		}
	}
	//free(arrayint);
	//free(arraybtree);
	return length;
}

struct bt_node_int *build_tree(long size){
	struct bt_node_int *root = malloc(sizeof(*root));
	if(!root) return NULL;
	struct bt_node_int *curr_node = root;
	struct queue_btree  *q = queue_init_btree();
	if(!q) return NULL;
	int i = 0;
	root->key = i;
	root->l = NULL;
	root->r = NULL;
	put_btree(q, curr_node);
	while(i < size){
		curr_node = get_btree(q);
		struct bt_node_int *left = malloc(sizeof(*left));
		left->key = i;
		left->l = NULL;
		left->r = NULL;
		curr_node->l = left;
		i++;
		put_btree(q, left);
		if(i < size){
			struct bt_node_int *right = malloc(sizeof(*right));
			right->key = i;
			right->l = NULL;
			right->r = NULL;
			curr_node->r = right;
			i++;
			put_btree(q, right);
		}
	}
	destroy_queue_btree(q);
	return root;
}