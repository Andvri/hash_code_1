#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <boost/algorithm/string.hpp>

using namespace std;

struct lib_data {
    int lib_number_of_books;
    int signup;
    int ship_days;
    vector<int> lib_books;
} typedef lib_data;

int main() {
    vector<string> books_libraries_days;
    string line;
    ifstream file;
    
    file.open("../data/b_read_on.txt");

    if (!file) {
        cout << "File not found";
        return 0;
    }
    
    int line_counter = 0;

    while (getline(file, line)) {
        // if (line_counter == 0) {
        //     boost::split(books_libraries_days.data(), &line, " ");
        // }
    }
    
    file.close();
    return 0;
}