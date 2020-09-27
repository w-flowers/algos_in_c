/***********************************
 * William Flowers
 *
 * Solution to Problem 2 Chapter 9 of Algorithms in C
 *
 * Implementation of quicksort which switches to insert sort for
 * files below a ceratin size - NOTE: non-recursive quicksort
 * *******************************/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "data_structures_int.c"

#define SIZE 500000

#define THRSH 30 

//NOTE:  a sentinel key is used in position l

int insert_sort_range(int arr[], int l, int r)
{
   int j = 0;
   
   int dmy = 0;

   for( int i = l + 1; i < r + 1; i++)
   {
      dmy = arr[i];
      
      j = i;
      
      while( arr[j - 1] > dmy )
      {
         arr[j] = arr[j - 1];

         j--;
      }

      arr[j] = dmy;

   }

   return 0;

}

// NOTE: As above, designed to operate with sentinal key
// l should be 1 to the left of the last element to be sorted

int qsort_w_insort(int arr[], int l, int r)
{
   int i, j, k, m;

   int dmy = 0;

   int stack[SIZE/2];

   int top = 0;

   stack[0] = r; stack[1] = l; top = 2;

   while(top)
   {
      i = stack[--top]; j = stack[--top];

      while(1)
      {
         k = i; m = j;

         if( m - k < THRSH )
         {
            insert_sort_range( arr, k, m);

            break;
         }

         while(1)
         {
            while( arr[++k] < arr[j] );

            while( arr[--m] > arr[j] );

            if( k >= m ) break;

            dmy = arr[k], arr[k] = arr[m], arr[m] = dmy;
         }
         dmy = arr[j]; arr[j] = arr[k]; arr[k] = dmy;
         
         if( k - 1 - i < j - k )
         {
            stack[top++] = j; stack[top++] = k; j = k - 1;
         }
         else
         {
            stack[top++] = k - 1; stack[top++] = i; i = k;
         }
      }
   }

   return 0;

}

int myqsort(int arr[], int l, int r)
{
   int i, j, k, m;

   int dmy = 0;

   int stack[SIZE/2];

   int top = 0;

   stack[0] = r; stack[1] = l; top = 2;

   while(top)
   {
      i = stack[--top]; j = stack[--top];

      while(j > i + 1)
      {
         k = i; m = j;

         while(1)
         {
            while( arr[++k] < arr[j] );

            while( arr[--m] > arr[j] );

            if( k >= m ) break;

            dmy = arr[k], arr[k] = arr[m], arr[m] = dmy;
         }
         dmy = arr[j]; arr[j] = arr[k]; arr[k] = dmy;
         
         if( k - 1 - i < j - k )
         {
            stack[top++] = j; stack[top++] = k; j = k - 1;
         }
         else
         {
            stack[top++] = k - 1; stack[top++] = i; i = k;
         }
      }
   }

   return 0;
}



int main()
{
   int array[SIZE + 1], array1[SIZE + 1];

   array[0] = INT_MIN;   array1[0] = INT_MIN;

   srand((int) time(NULL));

   for(int i = 1; i < SIZE + 1; i++){
      array[i] = (int) rand() % 10000;

      array1[i] = array[i];

      //printf("%d ", array[i]);
   }
   
   printf("\n");

   clock_t start = clock();

   qsort_w_insort(array, 0, SIZE);

   clock_t end = clock();

   for(int i = 1; i < SIZE; i++) if(array[i] > array[i+1])
   {
      printf("qwi: Array not sorted!!\n");

      break;
   }

   printf("qwi: %ld\n", (end - start));

   //for(int i = 1; i < SIZE + 1; i++) printf("%d ", array[i]);
   
   start = clock();

   myqsort(array1, 0, SIZE);

   end = clock();

   for(int i = 1; i < SIZE; i++) if(array1[i] > array1[i+1])
   {
      printf("qs: Array not sorted!!\n");

      break;
   }

   printf("qs: %ld\n", (end - start));


   return 0;
}

