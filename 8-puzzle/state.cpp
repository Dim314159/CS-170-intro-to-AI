#include "state.h"

State::State() { }

State::State(std::vector<int> vec) : g(0), comb(vec) { }

State::~State() { }

int State::h(int n)
{
   int h = 0;
   if (n == 2) {
      for (int i = 0; i < 9; i++) {
         int k = i + 1;
         if (k == 9) {
            k = 0;
         }
         if (comb[i] != k) {
            h++;
         }
      }
   }
   
   if (n == 3) {
      for (int i = 0; i < 9; i++) {
         int m = comb[i] - 1;
         if (comb[i] == 0) {
            m = 8;
         }
         int x = abs(m % 3 - i % 3) + abs(m / 3 - i / 3);
         h += x;
      }
   }
   
   return h;
}

int State::rank(int n)
{
   return g + h(n);
}

