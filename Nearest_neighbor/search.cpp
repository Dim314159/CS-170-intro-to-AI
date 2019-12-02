#include "search.h"

Search::Search() { }
Search::Search(std::string file_name)
{
   read_the_file(file_name);
   x_data_rows = x_data_original.size();
   x_data_columns_original = x_data_original[0].size();
   create_e_d_table_original();
   e_d_t_all_features_flag = false;
}
Search::~Search() { }

void Search::read_the_file(std::string file_name)
{
   std::ifstream my_File(file_name);
   
   if (!my_File.is_open()) {
      std::cout << "\n\tUnable to open file\n";
      return;
   }
   
   std::string line;
   while (getline(my_File, line)) {
      std::stringstream row(line);
      double value;
      std::vector<double> tempo;
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
      x_data_original.push_back(tempo);
   }
   
   my_File.close();
}

void Search::create_e_d_table_original()
{
   for (int i = 0; i < x_data_columns_original; i++) {
      std::vector<std::vector<double>> tempo_j;
      for (int j = 1; j < x_data_rows; j++) {
         std::vector<double> tempo_k;
         for (int k = 0; k < j; k++) {
            double d = pow(x_data_original[j][i] - x_data_original[k][i], 2);
            tempo_k.push_back(d);
         }
         tempo_j.push_back(tempo_k);
      }
      eucl_dist_table_original.push_back(tempo_j);
   }
}

void Search::forward_tree()
{
   features.clear();
   features_to_test.clear();
   for (int i = 0; i < x_data_columns; i++) {
      features_to_test.push_back(i);
   }
   best_features.clear();
   
   best_accuracy = 0;
   
   std::vector<std::vector<double>> e_d_table_current;
   for (int i = 0; i < x_data_rows - 1; i++) {
      std::vector<double> tempo;
      for (int j = 0; j < i + 1; j++) {
         tempo.push_back(0);
      }
      e_d_table_current.push_back(tempo);
   }
   
   std::cout << "\nBeginnig Search.\n";
   
   while (features.size() < x_data_columns) {
      int max_accuracy = 0;
      int best_feature;
      int best_feature_index;
      std::vector<std::vector<double>> e_d_t_best;
      for (int ii = 0; ii < features_to_test.size(); ii++) {
         int i = features_to_test[ii];
         int feature_accuracy = 0;
         std::vector<std::vector<double>> e_d_t_tempo = e_d_table_current;
         for (int j = 0; j < x_data_rows; j++) {
            double min_distance = std::numeric_limits<double>::max();
            int neighbor;
            for (int k = 0; k < x_data_rows; k++) {
               if (k != j) {
                  int jj = j;
                  int kk = k;
                  if (k < j) {
                     jj = k;
                     kk = j;
                  }
                  e_d_t_tempo[kk - 1][jj] += eucl_dist_table[i][kk - 1][jj];
                  if (e_d_t_tempo[kk - 1][jj] < min_distance) {
                     min_distance = e_d_t_tempo[kk - 1][jj];
                     neighbor = k;
                  }
               }
            }
            if (y_data[j] == y_data[neighbor]) {
               feature_accuracy++;
            }
         }
         double d = (double)feature_accuracy * 100 / x_data_rows;
         std::cout << "\n\tUsing feature(s) {" << i << "} accuracy is " << d << "%\n";
         if (feature_accuracy > max_accuracy) {
            max_accuracy = feature_accuracy;
            best_feature = i;
            best_feature_index = ii;
            e_d_t_best = e_d_t_tempo;
         }
      }
      features.push_back(best_feature);
      
      double d = (double)max_accuracy * 100 / x_data_rows;
      std::cout << "\nFeature set {";
      for (int i = 0; i < features.size(); i++) {
         std::cout << features[i] << ",";
      }
      std::cout << "} was best, accuracy is " << d << "%\n";
      
      features_to_test.erase(features_to_test.begin() + best_feature_index);
      e_d_table_current = e_d_t_best;
      if (max_accuracy > best_accuracy) {
         best_accuracy = max_accuracy;
         best_features = features;
      }
   }
   std::cout << "\n\nFeature set {"; 
   for (int i = 0; i < best_features.size(); i++) {
      std::cout << best_features[i] << " ";
   }
   
   best_accuracy_percent = (double)best_accuracy * 100 / x_data_rows;
   std::cout << "} was best, accuracy is " << best_accuracy_percent << "%\n";
   
   e_d_t_all_features = e_d_table_current;
   e_d_t_all_features_flag = true;
}

void Search::backward_tree()
{
   features.clear();
   for (int i = 0; i < x_data_columns; i++) {
      features.push_back(i);
   }
   
   best_features.clear();
   
   best_accuracy = 0;
   
   std::vector<std::vector<double>> e_d_table_current = e_d_t_all_features;
      
   std::cout << "\nBeginnig Search.\n";
   
    while (features.size() > 0) {
      int max_accuracy = 0;
      int best_feature_index;
      std::vector<std::vector<double>> e_d_t_best;
      for (int ii = 0; ii < features.size(); ii++) {
         int i = features[ii];
         int feature_accuracy = 0;
         std::vector<std::vector<double>> e_d_t_tempo = e_d_table_current;
         for (int j = 0; j < x_data_rows; j++) {
            double min_distance = std::numeric_limits<double>::max();
            int neighbor;
            for (int k = 0; k < x_data_rows; k++) {
               if (k != j) {
                  int jj = j;
                  int kk = k;
                  if (k < j) {
                     jj = k;
                     kk = j;
                  }
                  e_d_t_tempo[kk - 1][jj] -= eucl_dist_table[i][kk - 1][jj];
                  if (e_d_t_tempo[kk - 1][jj] < min_distance) {
                     min_distance = e_d_t_tempo[kk - 1][jj];
                     neighbor = k;
                  }
               }
            }
            if (y_data[j] == y_data[neighbor]) {
               feature_accuracy++;
            }
         }
         double d = (double)feature_accuracy * 100 / x_data_rows;
         std::cout << "\n\tTaking out feature(s) {" << i << "} accuracy is " << d << "%\n";
         if (feature_accuracy > max_accuracy) {
            max_accuracy = feature_accuracy;
            best_feature_index = ii;
            e_d_t_best = e_d_t_tempo;
         }
      }
      features.erase(features.begin() + best_feature_index);
      
      double d = (double)max_accuracy * 100 / x_data_rows;
      std::cout << "\nFeature set {";
      for (int i = 0; i < features.size(); i++) {
         std::cout << features[i] << ",";
      }
      std::cout << "} was best, accuracy is " << d << "%\n";
      
      e_d_table_current = e_d_t_best;
      if (max_accuracy > best_accuracy) {
         best_accuracy = max_accuracy;
         best_features = features;
      }
   }
   std::cout << "\n\nFeature set {"; 
   for (int i = 0; i < best_features.size(); i++) {
      std::cout << best_features[i] << " ";
   }
   best_accuracy_percent = (double)best_accuracy * 100 / x_data_rows;
   std::cout << "} was best, accuracy is " << best_accuracy_percent << "%\n";
}

void Search::forward_tree_sipmle()
{
   x_data = x_data_original;
   x_data_columns = x_data_columns_original;
   eucl_dist_table = eucl_dist_table_original;
   
   forward_tree();
}

void Search::backward_tree_simple()
{
   if (!e_d_t_all_features_flag) {
      std::cout << "\n\tRun Forward Tree first.\n";
      return;
   }
   
   x_data = x_data_original;
   x_data_columns = x_data_columns_original;
   eucl_dist_table = eucl_dist_table_original;
   
   backward_tree();
}

void Search::both_trees_mod()
{
   int chunk = x_data_columns_original / 10;
   x_data_columns = x_data_columns_original - chunk;
   std::vector<std::vector<int>> best_features_forward;
   std::vector<std::vector<int>> best_features_backward;
   std::cout << x_data_columns;
   
   std::vector<double> vec_forward_accuracy_of_chunks;
   std::vector<double> vec_backward_accuracy_of_chunks;
   
   for(int i = 0; i < 10; i++) {
      int set = i;
      
      x_data.clear();
      create_x_data(set);
      
      eucl_dist_table.clear();
      create_e_d_table(set);
      
      std::cout << "\nSet " << i << " forward ";
      forward_tree();
      best_features_forward.push_back(best_features);
      vec_forward_accuracy_of_chunks.push_back(best_accuracy_percent);
      
      std::cout << "\nSet " << i << " backward ";
      backward_tree();
      best_features_backward.push_back(best_features);
      vec_backward_accuracy_of_chunks.push_back(best_accuracy_percent);
   }
   
   std::set<int> all_forward_features;
   std::set<int> all_backward_features;
   
   for (int i = 0; i < 10; i++) {
      for (int j = 0; j < best_features_forward[i].size(); j++) {
         if (best_features_forward[i][j] >= i * chunk) {
            best_features_forward[i][j] += chunk;
         }
         all_forward_features.insert(best_features_forward[i][j]);
      }
      for (int j = 0; j < best_features_backward[i].size(); j++) {
         if (best_features_backward[i][j] >= i * chunk) {
            best_features_backward[i][j] += chunk;
         }
         all_backward_features.insert(best_features_backward[i][j]);
      }
   }
   
   
   std::cout << "\nBest forward features\n";
   for (int i = 0; i < 10; i++) {
      for (int j = 0; j < best_features_forward[i].size(); j++) {
         std::cout << best_features_forward[i][j] << " ";
      }
      std::cout << " with accuracy " << vec_forward_accuracy_of_chunks[i] << "%";
      std::cout << "\n";
   }
   for  (int i : all_forward_features) {
      std::cout << i << " ";
   }
   std::cout << "\n";
   
   std::cout << "\nBest backward features\n";
   for (int i = 0; i < 10; i++) {
      for (int j = 0; j < best_features_backward[i].size(); j++) {
         std::cout << best_features_backward[i][j] << " ";
      }
      std::cout << " with accuracy " <<  vec_backward_accuracy_of_chunks[i] << "%";
      std::cout << "\n";
   }
   for  (int i : all_backward_features) {
      std::cout << i << " ";
   }
   std::cout << "\n";
}

void Search::create_x_data(int set)
{
   x_data = x_data_original;
   int chunk = x_data_columns_original / 10;
   int start = set * chunk;
   int finish = start + chunk;
   for (int i = 0; i < x_data_rows; i++) {
      x_data[i].erase(x_data[i].begin() + start, x_data[i].begin() + finish);
   }
}

void Search::create_e_d_table(int set)
{
   eucl_dist_table = eucl_dist_table_original;
   int chunk = x_data_columns_original / 10;
   int start = set * chunk;
   int finish = start + chunk;
   eucl_dist_table.erase(eucl_dist_table.begin() + start, eucl_dist_table.begin() + finish);
}

int Search::default_rate()
{
   int n = 0;
   for (int i = 0; i < x_data_rows; i++) {
      if (y_data[i] == 2) {
         n++;
      }
   }
   return n;
}
