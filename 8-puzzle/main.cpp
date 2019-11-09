/**********************************
 *       8-puzzle
 *    D.Koltsov   2019.10.06
 * *******************************/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#include "state.h"
#include "my_heap.h"

using namespace std;

void Search(vector<int>, vector<int>, int);
void print_state(vector<int>);
void possible_moves(vector<int>, vector<int>&);
void move_the_tile(vector<int>&, int, int);
bool check_the_history(vector<int>, vector<vector<int>>);

int main()
{
   cout << "\n\tWelcome to 8-puzzle solver\n\tType 1 to use a default puzzle, or 2 to enter your own puzzle\n\t";
   
   int n;
   cin >> n;
   
   vector<int> puzzle(9);
      
   if (n == 1) {
      puzzle = {0,1,2,4,5,3,7,8,6};
   }
   else if (n == 2) {
      cout << "\tEnter your puzzle, use a zero to represent the blank\n\tEnter the first row, use space or tabs between numbers\n\t";
      cin >> puzzle[0] >> puzzle[1] >> puzzle[2];
      cout << "\n\tEnter the second row, use space or tabs between numbers\n\t";
      cin >> puzzle[3] >> puzzle[4] >> puzzle[5];
      cout << "\n\tEnter the third row, use space or tabs between numbers\n\t";
      cin >> puzzle[6] >> puzzle[7] >> puzzle[8];
   }
   
   vector<int> goal = {1, 2, 3, 4, 5, 6, 7, 8, 0};
   
   if (goal == puzzle) {
      cout << "\n\tNothing to solve here.";
      return 0;
   }
   
   cout << "\n\tEnter your choice of algorithm\n\t\t1. Uniform Cost Search\n\t\t2. A* with the Misplaced Tile heuristic.\n\t\t3. A* with the Manhattan distance heuristic.\n\t";
   
   cin >> n;
   
   Search(puzzle, goal, n);
   
   
   cout << "\n";
   return 0;
}

void Search(vector<int> state, vector<int> goal, int choice)
{
   cout << "\n\t\tExpanding state:\n\t";
   print_state(state);
   
   int counter = 1;
   My_heap my_queue;
   State combination(state);
   vector<vector<int>> my_history;
   my_queue.push_in(combination, choice);
   
   bool flag_1 = false;
   
   while (true) {
      if (my_queue.is_empty()) {
         cout << "No solutions\n";
         break;
      }
      
      State tempo = my_queue.pop_out(choice);
      
      counter++;
      
      if (flag_1) {
         cout << "\n\t\tThe best state to expand with g(n) = " << tempo.g
         << " and h(n) = " << tempo.h(choice);
         print_state(tempo.comb);
      }
      else {
         flag_1 = true;
      }
      
      if (tempo.comb == goal) {
         cout << "\n\tGoal!!\n\n\tTo solve this problem the search algorithm expanded a total of " << counter << " nodes.\n\tThe maximum number of nodes in the queue at any one time was " << my_queue.q_max << ".\n\tThe depth of the goal node was " << tempo.g << ".\n";
         break;
      }
      
      vector<int> moves;
      possible_moves(tempo.comb, moves);
      
      for (int i = 0; i < moves.size() - 1; i++) {
         State new_state = tempo;
         move_the_tile(new_state.comb, moves[i], moves.back());
         if (!check_the_history(new_state.comb, my_history)) {
            new_state.g++;
            my_queue.push_in(new_state, choice);
         }
      }
      my_history.push_back(tempo.comb);
   }
}

void print_state(vector<int> vec)
{
   for (int i = 0; i < 3; i++) {
      cout << "\n\t";
      for (int j = 0; j < 3; j++) {
         cout << vec[i * 3 + j] << " ";
      }
   }
   cout << "\n";
}

void possible_moves(vector<int> tempo, vector<int>& vec)
{
   int empty_index = 0;
      for (int i = 0; i < 9; i++) {
         if (tempo[i] == 0) {
            empty_index = i;
            break;
         }
      }
   if (empty_index % 3 > 0) {
      vec.push_back(empty_index - 1);
   }
   if ((empty_index + 1) % 3 != 0) {
      vec.push_back(empty_index + 1);
   }
   if (empty_index > 2) {
      vec.push_back(empty_index - 3);
   }
   if (empty_index < 6) {
      vec.push_back(empty_index + 3);
   }
   vec.push_back(empty_index);
}

void move_the_tile(vector<int>& vec, int old_pos, int new_pos)
{
   int i = vec[old_pos];
   vec[old_pos] = vec[new_pos];
   vec[new_pos] = i;
}

bool check_the_history(vector<int> state, vector<vector<int>> hist)
{
   for (int i = 0; i < hist.size(); i++) {
      if (state == hist[i]) {
         return true;
      }
   }
   return false;
}
