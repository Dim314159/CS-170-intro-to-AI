/************************************************
 *       CS 170, Nearest Neighbor
 *       2019.11.06     D.Koltsov
 * 
 * *********************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <sstream>

#include "search.h"

using namespace std;

void read_the_file(vector<double>&, vector<vector<double>>&);
void relation_table(vector<vector<double>>&, vector<vector<vector<double>>>&);
vector<int> forward_tree(vector<double>, vector<vector<double>>, vector<vector<vector<double>>>);
vector<int> backward_tree(vector<double>, vector<vector<double>>, vector<vector<vector<double>>>);
vector<int> features_to_test(vector<int>, int);
int error_rate_of_feature_set(vector<int>, vector<vector<double>>, vector<vector<vector<double>>>);

int main()
{
   Search my_search("my_data.txt");
   my_search.forward_tree_sipmle();
   my_search.backward_tree_simple();
   
   
//    vector<double> y_data;
//    vector<vector<double>> x_data;
//    read_the_file(y_data, x_data);
//    
//    vector<vector<vector<double>>> eucl_dist_table;
//    relation_table(x_data, eucl_dist_table);
//    
//    vector<int> best_features = forward_tree(y_data, x_data, eucl_dist_table);
//    
//    for (int i = 0; i < best_features.size(); i++) {
//       cout << best_features[i] << " ";
//    }
//    cout << "\n";
   
   return 0;
}

void read_the_file(vector<double> &y_data, vector<vector<double> > &x_data)
{
   ifstream my_File("my_data.txt");
   
   if (!my_File.is_open()) {
      cout << "\n\tUnable to open file\n";
      return;
   }
   
   string line;
   while (getline(my_File, line)) {
      stringstream row(line);
      double value;
      vector<double> tempo;
      bool y = true;
      while (row >> value) {
         if (y) {
            y_data.push_back(value);
            y = false;
         }
         else {
            tempo.push_back(value);
         }
      }
      x_data.push_back(tempo);
   }
   
   my_File.close();
}

void relation_table(vector<vector<double>>& x, vector<vector<vector<double> > >& table)
{
   int m = x.size();
   int n = x[0].size();
   vector<vector<vector<double>>> tempo(n, vector<vector<double>>(m, vector<double>(m, 0)));
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < m - 1; j++) {
         for (int k = j + 1; k < m; k++) {
            tempo[i][j][k] = tempo[i][k][j] = pow(x[j][i] - x[k][i], 2);
         }
      }
   }
   table = tempo;
}

vector<int> forward_tree(vector<double> y_data, vector<vector<double> > x_data, vector<vector<vector<double> > >eucl_dist_table)
{
   vector<int> features;
   vector<int> best_features;
   int best_error_rate = numeric_limits<int>::max();
   int number_of_neighbors = x_data.size();
   int number_of_features = x_data[0].size();
   
   while (features.size() < number_of_features) {
      int min_error_rate = numeric_limits<int>::max();
      int best_feature;
      vector<int> features_to_test_arr = features_to_test(features, number_of_features); 
      for (int ii = 0; ii < features_to_test_arr.size(); ii++) {
         int i = features_to_test_arr[ii];
         int feature_error_rate = 0;
         for (int j = 0; j < number_of_neighbors; j++) {
            double min_distance = numeric_limits<double>::max();
            int neighbor;
            for (int k = 0; k < number_of_neighbors; k++) {
               if (k != j) {
                  double distance = eucl_dist_table[i][j][k];
                  for (int l = 0; l < features.size(); l++) {
                     distance += eucl_dist_table[features[l]][j][k];
                  }
                  if (distance < min_distance) {
                     min_distance = distance;
                     neighbor = k;
                  }
               }
            }
            if (y_data[j] != y_data[neighbor]) {
               feature_error_rate++;
            }
         }
         if (feature_error_rate < min_error_rate) {
            min_error_rate = feature_error_rate;
            best_feature = i;
         }
      }
   
      features.push_back(best_feature);
      if (min_error_rate < best_error_rate) {
         best_error_rate = min_error_rate;
         best_features = features;
      }
   }
   
   return best_features;
}

vector<int> backward_tree(vector<double> y_data, vector<vector<double> > x_data, vector<vector<vector<double> > > eucl_dist_table)
{
   vector<int> features;
   vector<int> best_features;
   int best_error_rate;
   int number_of_neighbors = x_data.size();
   int number_of_features = x_data[0].size();
   
   for (int i = 0; i < number_of_features; i++) {
      features.push_back(i);
      for (int j = 0; j < number_of_neighbors; j++) {
         for (int k = 0; k < number_of_neighbors; k++) {
            
         }
      }
   }
   
   while (int n = features.size() > 0) {
      int min_error_rate = numeric_limits<int>::max();
      int best_feature_to_take_out;
      for (int ii = 0; ii < n; ii++) {
         int i = features[ii];
         int feature_error_rate = 0;
      }
   }
}


vector<int> features_to_test(vector<int> features, int number_of_features)
{
   vector<int> tempo;
   int n = features.size();
   for (int i = 0; i < number_of_features; i++) {
      bool flag = true;
      for (int j = 0; j < n; j++) {
         if (features[j] == i) {
            flag = false;
            break;
         }
      }
      if (flag) {
         tempo.push_back(i);
      }
   }
   return tempo;
}

int error_rate_of_feature_set(vector<int> features, vector<vector<double> >, vector<vector<vector<double> > > eucl_dist_table)
{
   int number_of_features = features.size();
   int number_of_neighbors = eucl_dist_table[0].size();
   for (int ii = 0; ii < number_of_features; ii++) {
      int i = features[ii];
      for (int j = 0; j < number_of_neighbors; j++) {
         for (int k = 0; k < number_of_neighbors; k++) {
            
         }
      }
   }
}
