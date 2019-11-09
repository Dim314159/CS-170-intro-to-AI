#include "my_heap.h"

My_heap::My_heap() : q(0), q_max(0) { }
My_heap::~My_heap() { }

void My_heap::push_in(State comb, int n)
{
   heap.push_back(comb);
   
   if (++q > q_max) {
      q_max = q;
   }
   
   int child = heap.size();
   if (child == 1) {
      return;
   }
   
   child--;
   int parent;
   
   while (child > 0) {
      parent = (child - 1) / 2;
      if  (heap[parent].rank(n) <= heap[child].rank(n)) {
         return;
      }
      swappp(child, parent);
   }
}

State My_heap::pop_out(int n)
{
   State tempo = heap[0];
   heap[0] = heap.back();
   heap.pop_back();
   q--;
   
   int s = heap.size();
   if (s > 1) {
      int parent = 0;
      int child = 2 * parent + 1;
   
      while(child < s) {
         bool flag = false;
         int wrong_rank = heap[parent].rank(n);
         for (int i = 0; i < 2 && child + i < s; i++) {
            if (heap[child + i].rank(n) < wrong_rank) {
               wrong_rank = heap[child + i].rank(n);
               child = child + i;
               flag = true;
            }
         }
         if (!flag) {
            break;
         }
         swappp(parent, child);
         child = 2 * parent + 1;
      }
   }
   return tempo;
}

void My_heap::swappp(int& from, int to)
{
   State temp_state = heap[from];
   heap[from] = heap[to];
   heap[to] = temp_state;
   
   from = to;
}

bool My_heap::is_empty()
{
   return heap.empty();
}

