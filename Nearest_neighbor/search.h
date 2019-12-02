#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <sstream>
#include <set>

struct Search
{
   Search();
   Search(std::string);
   ~Search();
   
   std::vector<double> y_data;
   std::vector<std::vector<double>> x_data_original;
   std::vector<std::vector<double>> x_data;
   
   int x_data_rows;
   int x_data_columns_original;
   int x_data_columns;
   
   std::vector<std::vector<std::vector<double>>> eucl_dist_table_original;
   std::vector<std::vector<std::vector<double>>> eucl_dist_table;
   std::vector<std::vector<double>> e_d_t_all_features;
   bool e_d_t_all_features_flag;
   
   std::vector<int> features;
   std::vector<int> features_to_test;
   std::vector<int> best_features;
   int best_accuracy;
   double best_accuracy_percent;
   
   void read_the_file(std::string);
   
   void create_e_d_table_original();
   
   void forward_tree();
   void backward_tree();
   
   void forward_tree_sipmle();
   void backward_tree_simple();
   
   void both_trees_mod();
   
   void create_x_data(int);
   void create_e_d_table(int);
   
   int default_rate();
};

#endif 
