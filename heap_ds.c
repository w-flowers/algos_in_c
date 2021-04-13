/* ****************************************************************************
 * heap_ds.c - a simple implementation of a heap data structure
 *
 * A heap data structure which takes integer keys. Implemented as an array.
 * Operations implemented allow use as a priority queue.
 *
 * Author - William Flowers
 * ***************************************************************************/

#include <string.h>

#include <stdlib.h>

#include <limits.h>

#define HEAP_INIT_SIZE 128
struct heap
{
   int buffer[];

   // position of last element
   int offset;

   // Size allocated to buffer
   int size;
}


// Declarations


// Should be called before any removes or replaces
int heap_empty( struct heap *h );

// Internal method, not part of API - Reallocate if out of space
int resize_heap( struct heap *h );

// Insert element into heap
int insert_heap( struct heap *h, int data );

// Internal method, not part of API - rebalance heap from bottom
int upheap( struct heap *h, int pos );

// Create new heap at stack pointer h, populate with init_arr of size
int construct_heap( struct heap *h, int init_arr[], int size );

// Get element from top of heap
int remove_heap( struct heap *h );

// Internal method, rebalance heap from top
int downheap( struct heap *h, int pos );

// Replace element on top of heap and rebalance
int replace_heap( struct heap *h, int data );

// Delete element in position to_del in heap
int delete_heap( struct heap *h, int to_del );

// Change priority of element in position to_ch in heap
int change_heap( struct heap *h, int to_ch, int new_val );

// Destroy heap - deallocate memory
int destroy_heap( struct heap *h );

// Definitions


int heap_empty( struct heap *h )
{
   return offset;
}

int resize_heap( struct heap *h )
{
   int nb[] = malloc(  h->size * 2 );

   if( !nb )
   {
      h->size = 0;

      return 1;
   }

   memcpy( nb, h->buffer, h->size );

   free( h->buffer );

   h->buffer = nb;

   h->size *= 2;

   return 0;
}

int insert_heap( struct heap *h, int data )
{
   if( ++( h->offset ) == h->size )
   {
      if( resize_heap( h ) ) return 1;
   }

   h->buffer[ h->offset ] = data;
   
   upheap( h , h->offset );

   return 0;
}

int upheap( struct heap *h, int pos )
{
   int dmy = h->buffer[pos];

   while( ( h->buffer[ pos / 2 ] <= dmy ) )
   {
      h->buffer[ pos ] = h->buffer[ pos / 2 ];

      pos /= 2;
   }

   h->buffer[ pos ] = dmy;

   return 0;
} 

int construct_heap( struct heap *h, int init_arr[], int size )
{
   h->buffer = malloc( HEAP_INIT_SIZE * sizeof( int ) );

   if( !h->buffer )
   {
      h->size = 0;

      return 1;
   }

   h->buffer[0] = INT_MAX;

   h->size = HEAP_INIT_SIZE;

   h->offset = 0;

   for( int i = 0; ( i < size && !insert_heap( h, init_arr[i] ) ); i++ )

   return 0;
}

int remove_heap( struct heap *h )
{
   int val = h->buffer[1];

   h->buffer[1] = h->buffer[ h->offset-- ];

   downheap( h, 1 );

   return val;
}

int downheap( struct heap *h, int pos )
{
   int val = h->buffer[ pos ];

   int max_child = 0;

   while( pos * 2 + 1 <= offset )
   {
      max_child = ( h->buffer[2*pos] > h->buffer[2*pos + 1] ) ? 
         2*pos : 2*pos + 1;

      if( h->buffer[max_child] > val )
      {
         h->buffer[pos] = h->buffer[max_child];

         pos = max_child;
      }
      else break;
   }

   if( pos*2 == offset && h->buffer[pos*2] > val )
   {
      h->buffer[pos] = h->buffer[2*pos];

      pos *= 2;
   }

   h->buffer[pos] = val;

   return 0;
}

int replace_heap( struct heap *h, int data )
{
   int val = h->buffer[1];

   h->buffer[1] = data;

   downheap( h, 1 );

   return val;
}

int delete_heap( struct heap *h, int to_del )
{
   if( to_del <= offset && to_del > 0 )
   {
      h->buffer[to_del] = h->buffer[offset--];

      upheap( h, to_del );

      downheap( h, to_del );

      return 0;
   }
   
   else return 1;
}

int change_heap( struct heap *h, int to_ch, int new_val )
{
   if( to_ch <= offset && to_ch > 0 )
   {
      h->buffer[to_ch] = new_val;

      upheap( h, to_ch );

      downheap( h, to_ch );

      return 0;
   }
   else return 1;
}

int destroy_heap( struct heap *h )
{
   free( h->buffer );

   h->size = 0;

   h->offset = 0;

   return 0;
}

