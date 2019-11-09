#ifndef MY_HEAP_H
#define MY_HEAP_H

#include "state.h"

#include <vector>
#include <limits>

struct My_heap
{
   My_heap();
   ~My_heap();
   
   std::vector<State> heap;
   int q;
   int q_max;
   
   void push_in(State, int);
   State pop_out(int);
   void swappp(int&, int);
   bool is_empty();
};

#endif
