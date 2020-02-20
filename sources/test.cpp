#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <vector>

using namespace std;

int main() {
    vector<string> books_libraries_days;
    string line;
    ifstream file;
    int B = 0;
    int L = 0;
    int D = 0;

    file.open("../data/b_read_on.txt");

    if (!file) {
        cout << "File not found";
        return 0;
    }
    
    int line_counter = 0;

    while (getline(file, line)) {
        boost::split(books_libraries_days, line,  boost::is_any_of(" "));
        switch (line_counter)
        {
        case 0:
            B = stoi(books_libraries_days[0]);
            L = stoi(books_libraries_days[1]);
            D = stoi(books_libraries_days[2]);
            cout << "B: " << B << " L: " << L << " D: " << D << endl;
            break;
        case 1:

            break;
        }

        line_counter++;
    }
    
    file.close();
    return 0;
}