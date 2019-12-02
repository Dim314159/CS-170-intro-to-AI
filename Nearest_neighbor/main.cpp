/************************************************
 *       CS 170, Nearest Neighbor
 *       2019.11.06     D.Koltsov
 * 
 * *********************************************/


#include "search.h"

int main()
{
   Search my_search("my_data.txt");
   
   std::cout << "\n\t\tChoose:\n\t1 for Forward Selection only\n\t2 for Forward and Bacward Selections\n\t3 for Modification Forward and Backward Selections\n\t4 for print out Default Rate\n\t0 for Exit\n\t";
   
   int n;
   std::cin >> n;
   std::cin.ignore();
   
   switch (n) {
      case 1:
         my_search.forward_tree_sipmle();
         break;
      case 2:
         my_search.forward_tree_sipmle();
         my_search.backward_tree_simple();
         break;
      case 3:
         my_search.both_trees_mod();
         break;
      case 4:
         std::cout << my_search.default_rate() << " out of " << my_search.x_data_rows << "\n";
         break;
      case 0:
         break;
   }
      
   return 0;
}
