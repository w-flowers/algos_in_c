/* ****************************************************************************
 * drawtree.c - a program which uses SDL to draw a binary tree
 *
 * 
 *
 * Author - w-flowers
 * ***************************************************************************/
#include <stdio.h>

#include <SDL2/SDL.h>

#include "data_structures_int.c"

//This tree drawing program can accomodate about 7 levels of a tree.


const long TREE_SIZE = 127;
const int NODE_SIZE = 20;
const int LEVEL_SIZE = 120;
const int MARGIN = 60;
int SCREEN_WIDTH = 1440;
int SCREEN_HEIGHT = 1080;

struct bt_node_int *build_tree(long size);
int draw_tree(SDL_Renderer *renderer, struct bt_node_int *root, int level, int left_bound, int right_bound, SDL_Point *par_middle);

int main(){
	struct bt_node_int *root = build_tree(TREE_SIZE);
	if(!root) return 0;
	
	SDL_Window *window = NULL;
	
	SDL_Renderer *renderer = NULL;
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0) printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	else{
        window = SDL_CreateWindow("Draw Tree", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if( window == NULL )
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
		else{
			renderer = SDL_CreateRenderer(window, -1, 0);
			SDL_Rect text_rect;
			text_rect.x = 0;
			text_rect.y = 0;
			text_rect.h = SCREEN_HEIGHT;
			text_rect.w = SCREEN_WIDTH;
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect(renderer, &text_rect);
			draw_tree(renderer, root, 0, 0, SCREEN_WIDTH, NULL);
			SDL_Event e;
			int quit = 0;
			while(!quit){
				SDL_WaitEvent( &e );
	         	if( e.type == SDL_QUIT )
	         	{
	                quit = 1;
					break;
	        	}
				SDL_RenderPresent(renderer);
			}
			SDL_DestroyRenderer(renderer);
		}
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
	destroy_tree_int(root);
	return 0;
}

int draw_tree(SDL_Renderer *renderer, struct bt_node_int *root, int level, int left_bound, int right_bound, SDL_Point *par_middle){
	SDL_Rect curr_node_rect;
	curr_node_rect.w = NODE_SIZE; curr_node_rect.h = NODE_SIZE;
	curr_node_rect.y = level*LEVEL_SIZE + MARGIN;
	int centrex = (left_bound + right_bound)/2;
	curr_node_rect.x = centrex - NODE_SIZE/2;
	SDL_SetRenderDrawColor(renderer, 45, 45, 45, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &curr_node_rect);
	if(par_middle != NULL){
		SDL_Point topmid;
		topmid.x = centrex;
		topmid.y = curr_node_rect.y;
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(renderer, topmid.x, topmid.y, par_middle->x, par_middle->y);
	}
	SDL_Point bottommid;
	bottommid.x = centrex;
	bottommid.y = curr_node_rect.y + NODE_SIZE;
	if(root->l != NULL) draw_tree(renderer, root->l, level+1, left_bound, centrex, &bottommid);
	if(root->r != NULL) draw_tree(renderer, root->r, level+1, centrex, right_bound, &bottommid);
	return 0;
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
	i++;
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
