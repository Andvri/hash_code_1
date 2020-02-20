#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <vector>

using namespace std;

struct lib_data {
    int lib_number_of_books;
    int signup;
    int books_per_day;
    vector<int> lib_books;
    vector<int> books_to_scan;
} typedef lib_data;

lib_data lib_search(int& B, int&, int& D, vector<int>& score_books, vector<lib_data>& libs) {
    int max_points = 0;
    int current_points = 0;
    int days_left = D;
    int day_counter = 0;
    int book_per_day_counter = 0;

    for (unsigned i = 0; i < libs.size(); i++) {
        days_left -= libs[i].signup;
        for (unsigned j = 0; j < libs[i].lib_books.size(); j++) {
            current_points += score_books[libs[i].lib_books[j]];
        }
    }
}

int main() {
    // Extract data:
    vector<string> data;
    string line;
    ifstream file;
    int B = 0;
    int L = 0;
    int D = 0;
    vector<int> score_books;
    vector<lib_data> libs;

    file.open("../data/a_example.txt");

    if (!file) {
        cout << "File not found";
        return 0;
    }
    
    int line_counter = 0;

    while (getline(file, line)) {
        boost::split(data, line,  boost::is_any_of(" "));
        if(line_counter == 0){
            B = stoi(data[0]);
            L = stoi(data[1]);
            D = stoi(data[2]);
            cout << "B: " << B << " L: " << L << " D: " << D << endl;
        }
        else{
            if(line_counter == 1){
                for(unsigned i = 0; i < data.size(); i++){
                    score_books.emplace_back(stoi(data[i]));
                }
                cout << "Score books" << endl;
                for(unsigned i = 0; i < score_books.size(); i++){
                    cout << " " << score_books[i] << " ";
                }
                cout << endl;
            }
            else{
                if(line_counter % 2 == 0){
                    libs.emplace_back(lib_data{stoi(data[0]), stoi(data[1]), stoi(data[2])});
                }
                else {
                    for(unsigned i = 0; i < data.size(); i++){
                        libs.back().lib_books.emplace_back(stoi(data[i]));
                    }
                }
            }
        }
        
        line_counter++;
    }
    cout << "Libraries: " << endl;
    for(unsigned i = 0; i < libs.size(); i++){
        cout << "n_books: " << libs[i].lib_number_of_books << " signup: " << libs[i].signup << " books_per_day: " << libs[i].books_per_day << endl;
        for(unsigned j = 0; j < libs[i].lib_books.size(); j++){
            cout << " " << libs[i].lib_books[j] << " ";
        }
        cout << endl;
    }
    file.close();

    // Algorithm:    
    int number_of_scanned_libs = 0;
    int scanned_libs_indices[number_of_scanned_libs];
    // TODO 

    // Save results:
    ofstream result_file;
    string books_line = "";
    result_file.open("../data/result_a.txt");
    result_file << to_string(number_of_scanned_libs) + "\n";
    cout << "Number of libs to scan: " + to_string(number_of_scanned_libs) << endl;
    for (int i = 0; i < number_of_scanned_libs; i++) {
        result_file << to_string(scanned_libs_indices[i]) + " " + to_string(libs[scanned_libs_indices[i]].books_to_scan.size()) + "\n";
        books_line = "";
        for (unsigned j = 0; j < libs[scanned_libs_indices[i]].books_to_scan.size(); j++) {
            books_line += to_string(libs[scanned_libs_indices[i]].books_to_scan[j]);
            if (j < libs[scanned_libs_indices[i]].books_to_scan.size() - 1)
                books_line += " ";
            else if (j == libs[scanned_libs_indices[i]].books_to_scan.size() - 1)
                books_line += "\n";
        }
        result_file << books_line;
    }
    result_file.close(); 

    return 0;
}