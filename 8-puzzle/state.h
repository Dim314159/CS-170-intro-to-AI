#ifndef STATE_H
#define STATE_H

#include <vector>
#include <algorithm>

struct State
{
   State();
   State(std::vector<int>);
   ~State();
   
   std::vector<int> comb;
   int g;
   
   int h(int);
   int rank(int);
};


#endif
