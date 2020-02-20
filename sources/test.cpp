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
    bool marked;
    vector<int> lib_books;
    vector<int> books_to_scan;
} typedef lib_data;

struct book_data {
    int score;
    bool marked = false;
} typedef book_data;

int lib_search(int& D, vector<book_data>& books, vector<lib_data>& libs) {
    int max_points = 0;
    int best_library_index = -1;
    int current_points = 0;
    int days_left = D;
    int day_counter = 0;
    int book_per_day_counter = 0;
    string books_mark = "";
    string books_max_mark = "";
    
    for (unsigned i = 0; i < libs.size(); i++) {
        if(libs[i].marked){
            continue;
        }
        days_left -= libs[i].signup;
        books_mark = "";
        unsigned j = 0;
        for (; j < libs[i].lib_books.size(); j++) {

            if (books[libs[i].lib_books[j]].marked)
                continue;

            books_mark += to_string(j) + ",";

            current_points += books[libs[i].lib_books[j]].score;
            book_per_day_counter++;

            if (book_per_day_counter == libs[i].books_per_day) {
                day_counter++;
                book_per_day_counter = 0;
            }

            if (day_counter == days_left) {
                break;
            }
        }

        if(book_per_day_counter != 0){
            day_counter++;
        }

        if(j > 0)
            current_points = current_points / (day_counter + libs[i].signup);
        else
            current_points = 0;

        if (current_points > max_points) {
            max_points = current_points;
            books_max_mark = books_mark;
            best_library_index = i;
        }

        current_points = 0;
        day_counter = 0;
        days_left = D;
    }

    vector<string> result;
    boost::split(result, books_max_mark,  boost::is_any_of(","));
    for(int k = 0; k < result.size() - 1; k++){
       int value = libs[best_library_index].lib_books[stoi(result[k])];
        libs[best_library_index].books_to_scan.emplace_back(value);
        books[value].marked = true;
    }
    libs[best_library_index].marked = true;

    return best_library_index;
}

int main() {
    // Extract data:
    vector<string> data;
    string line;
    ifstream file;
    int B = 0;
    int L = 0;
    int D = 0;
    vector<book_data> books;
    vector<lib_data> libs;

    file.open("../data/d_tough_choices.txt");

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
        }
        else{
            if(line_counter == 1){
                for(unsigned i = 0; i < data.size(); i++){
                    books.emplace_back(book_data{stoi(data[i]), false});
                }
            }
            else{
                if(line_counter % 2 == 0){
                    libs.emplace_back(lib_data{stoi(data[0]), stoi(data[1]), stoi(data[2]), false});
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

    for(unsigned i = 0; i < libs.size(); i++){
       sort(libs[i].lib_books.begin(), libs[i].lib_books.end(), [&] (int book_a, int book_b) {
            return books[book_a].score > books[book_b].score; 
        });
    }
    file.close();

    vector<int> scanned_libs_indices;

    while(D > 0 && scanned_libs_indices.size() < libs.size()) {
        int best = lib_search(D, books, libs);
        if(best == -1){
            break;
        }
        cout << "Best: " << best << endl;
        scanned_libs_indices.emplace_back(best);
        D -= libs[best].signup;
    }
    
    unsigned number_of_scanned_libs = scanned_libs_indices.size();
    
    unsigned value = 0;
    for(int i = 0; i < books.size(); i++){
        if(books[i].marked){
            value += books[i].score;
        }
    }
    cout << "value: " << value << endl;
    // TODO 

    // Save results:
    ofstream result_file;
    string books_line = "";
    result_file.open("../data/result_d.txt");
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