/***********************************
 * W Flowers
 *
 * Solution to Problems 1, 2 and 3 of Chapter 9 of Algorithms in C
 *
 * Implementation of quicksort which switches to insert sort for
 * files below a ceratin size, removes recusion, and uses "median
 * of 3" methods for selecting the partitioning element.
 *
 * TO DO: Modifications in progress, need to check that qsismd3, 
 * qsismd3nrc and qsisnrc all actually sort arrays and modify 
 * performance checking code.
 * *******************************/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define SIZE 80000

#define THRSH 25 

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
   int i = l, j = r;

   int dmy = 0;

   if( r - l < THRSH ) insert_sort_range( arr, l, r );

   else
   {
      while(1)
      {
         while( arr[++i] < arr[r] );

         while( arr[--j] > arr[r] );

         if( i >= j ) break;

         dmy = arr[i], arr[i] = arr[j], arr[j] = dmy;
      }
      dmy = arr[i], arr[i] = arr[r], arr[r] = dmy;

      qsort_w_insort( arr, l, i - 1 );

      qsort_w_insort( arr, i, r );
   }

   return 0;

}

//qsort w/ median of 3 partitioning
int qsort_w_insort_md3(int arr[], int l, int r)
{
   int i = l, j = r;

   int dmy = 0;

   if( r - l < THRSH ) insert_sort_range( arr, l, r );

   else
   {
      ++i;

      int mid = ( i + j ) / 2;

      if( arr[i] > arr[mid] )
      {
         dmy = arr[i]; arr[i] = arr[mid]; arr[mid] = dmy;
      }

      if( arr[i] > arr[j] )
      {
         dmy = arr[i]; arr[i] = arr[j]; arr[j] = dmy;
      }

      if( arr[mid] > arr[j] )
      {
         dmy = arr[mid]; arr[mid] = arr[j]; arr[j] = dmy;
      }

      j = r - 1;

      dmy = arr[j]; arr[j] = arr[mid]; arr[mid] = dmy;

      while(1)
      {
         while( arr[++i] < arr[r - 1] );

         while( arr[--j] > arr[r - 1] );

         if( i >= j ) break;

         dmy = arr[i], arr[i] = arr[j], arr[j] = dmy;
      }
      dmy = arr[i], arr[i] = arr[r - 1], arr[r - 1] = dmy;

      qsort_w_insort_md3( arr, l, i - 1 );

      qsort_w_insort_md3( arr, i, r );
   }

   return 0;

}
int myqsort(int arr[], int l, int r)
{
   int i = l, j = r;

   int dmy = 0;

   if(r - l > 1)
   {
      while(1)
      {
         while( arr[++i] < arr[r] );

         while( arr[--j] > arr[r] );

         if( i >= j ) break;

         dmy = arr[i], arr[i] = arr[j], arr[j] = dmy;
      }
      dmy = arr[i], arr[i] = arr[r], arr[r] = dmy;

      myqsort( arr, l, i - 1 );

      myqsort( arr, i, r );
   }

   return 0;

}

int qsort_w_insort_nrc_md3(int arr[], int l, int r)
{
   int i, j, k, m;

   int dmy = 0;

   int stack[SIZE/20];

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

         ++k;

         int mid = ( k + m ) / 2;

         if( arr[k] > arr[mid] )
         {
            dmy = arr[k]; arr[k] = arr[mid]; arr[mid] = dmy;
         }

         if( arr[k] > arr[m] )
         {
            dmy = arr[k]; arr[k] = arr[m]; arr[m] = dmy;
         }

         if( arr[mid] > arr[m] )
         {
            dmy = arr[mid]; arr[mid] = arr[m]; arr[m] = dmy;
         }

         m = j - 1;

         dmy = arr[m]; arr[m] = arr[mid]; arr[mid] = dmy;


         while(1)
         {
            while( arr[++k] < arr[j - 1] );

            while( arr[--m] > arr[j - 1] );

            if( k >= m ) break;

            dmy = arr[k], arr[k] = arr[m], arr[m] = dmy;
         }
         dmy = arr[j - 1]; arr[j - 1] = arr[k]; arr[k] = dmy;
         
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

int qsort_w_insort_nrc(int arr[], int l, int r)
{
   int i, j, k, m;

   int dmy = 0;

   int stack[SIZE/20];

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
int myqsort_nrc(int arr[], int l, int r)
{
   int i, j, k, m;

   int dmy = 0;

   int stack[SIZE/20];

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
   int array[SIZE + 1], array1[SIZE + 1], array2[SIZE + 1], array3[SIZE + 1], array4[SIZE + 1], array5[SIZE + 1];

   array[0] = INT_MIN;   array1[0] = INT_MIN; array2[0] = INT_MIN;
   array3[0] = INT_MIN; array4[0] = INT_MIN; array5[0] = INT_MIN;


   srand((int) time(NULL));

   long qs_timer = 0; long qs_nrc_timer = 0; long qsis_timer = 0; long qsis_nrc_timer = 0; long qsis_md3_timer = 0; long qsis_nrc_md3_timer = 0;

   clock_t start, end;

   for(int rep = 0; rep < 1000; rep++)
   {
      for(int i = 1; i < SIZE + 1; i++)
      {
         array[i] = (int) rand() % 100000000;

         array1[i] = array[i];

         array2[i] = array[i];

         array3[i] = array[i];

         array4[i] = array[i];

         array5[i] = array[i];

         //printf("%d ", array[i]);
      }
      start = clock();

      qsort_w_insort(array, 0, SIZE);

      end = clock();

      qsis_timer += (end - start);

      start = clock();

      myqsort(array1, 0, SIZE);

      end = clock();

      qs_timer += (end - start);

      start = clock();

      myqsort_nrc(array2, 0, SIZE);

      end = clock();

      qs_nrc_timer += (end - start);

      start = clock();

      qsort_w_insort_nrc(array3, 0, SIZE);

      end = clock();

      qsis_nrc_timer += (end - start);

      start = clock();

      qsort_w_insort_md3(array4, 0, SIZE);

      end = clock();

      qsis_md3_timer += (end - start);

      start = clock();

      qsort_w_insort_nrc_md3(array5, 0, SIZE);

      end = clock();

      qsis_nrc_md3_timer += (end - start);


   }
   
   printf("qwi: %ld\n", qsis_timer);

   printf("qs: %ld\n", qs_timer);
  
   printf("qwi_nrc: %ld\n", qsis_nrc_timer);

   printf("qs_nrc: %ld\n", qs_nrc_timer);

   printf("qwi_md3: %ld\n", qsis_md3_timer);

   for(int i = 1; i <= SIZE; i++)
   {
      if(array4[i-1] > array4[i])
      {
         printf("qwimd3 not sorted!\n");

         break;
      }
   }

   printf("qwi_nrc_md3: %ld\n", qsis_nrc_md3_timer);

   for(int i = 1; i <= SIZE; i++)
   {
      if(array5[i-1] > array5[i])
      {
         printf("qwinrcmd3 not sorted!\n");

         break;
      }
   }

   return 0;
}

