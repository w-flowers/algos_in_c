#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define SIZE 50000

/* Implementation of shellsort with sentinal key */
int shellsort(int a[], int size)
{
   int i, j, h, v;

   for(h = 1; h < size/9; h = 4*h - 1);

   for(; h >= 1; h = (h + 1)/4)
   {
      for(i = h + 1; i <= size; i += h)
      {
         v = a[i], j = i;

         while(j > h && a[j - h] > v)
         {
            a[j] = a[j - h];

            j -= h;
         }
         a[j] = v;
      }
   }
   return 0;
}

int main()
{
   int array[SIZE + 1];

   array[0] = INT_MIN;

   srand((int) time(NULL));

   for(int i = 1; i < SIZE + 1; i++){
      array[i] = (int) rand() % 10000;

      //printf("%d ", array[i]);
   }
   
   printf("\n");

   clock_t start = clock();

   shellsort(array, SIZE);

   clock_t end = clock();

   for(int i = 1; i < SIZE; i++) if(array[i] > array[i+1])
   {
      printf("Array not sorted!!\n");

      break;
   }

   printf("%ld\n", (end - start));

   //for(int i = 1; i < SIZE + 1; i++) printf("%d ", array[i]);

   return 0;
}

