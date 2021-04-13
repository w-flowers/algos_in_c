/* ****************************************************************************
 * allgcd.c
 *
 * A program to list to create a 2D array with 1's if i and j are coprime, and
 * 0 if they are not.
 *
 * Author - William Flowers
 * ***************************************************************************/

#include<stdio.h>

#include"euclidsalg.c"

#define MAX 51

int main()
{
	int array[MAX][MAX];

	for(int i = 1; i < MAX; i++)
   {
		for(int j = 1; j < MAX; j++)
      {
			if(gcd((long)i, (long)j) == 1) array[i][j] = 1;
		
         else array[i][j] = 0;
		
         printf("%d ", array[i][j]);
		}
		
      printf("\n");
	}
	
   return 0;
}
