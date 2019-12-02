#include "search.h"

Search::Search() { }
Search::Search(std::string file_name)
{
   read_the_file(file_name);
   x_data_rows = x_data.size();
   x_data_columns = x_data[0].size();
   create_e_d_table();
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
      x_data.push_back(tempo);
   }
   
   my_File.close();
}

void Search::create_e_d_table()
{
   for (int i = 0; i < x_data_columns; i++) {
      std::vector<std::vector<double>> tempo_j;
      for (int j = 1; j < x_data_rows; j++) {
         std::vector<double> tempo_k;
         for (int k = 0; k < j; k++) {
            double d = pow(x_data[j][i] - x_data[k][i], 2);
            tempo_k.push_back(d);
         }
         tempo_j.push_back(tempo_k);
      }
      eucl_dist_table.push_back(tempo_j);
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
   std::cout << "} was best, accuracy is " << (double)best_accuracy * 100 / x_data_rows << "%\n";
}

void Search::backward_tree()
{
   features.clear();
   for (int i = 0; i < x_data_columns; i++) {
      features.push_back(i);
   }
   features_to_test.clear();
   best_features.clear();
   
   
}
