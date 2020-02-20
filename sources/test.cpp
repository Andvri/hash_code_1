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
    int ship_days;
    vector<int> lib_books;
} typedef lib_data;

int main() {
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
                for(int i = 0; i < data.size(); i++){
                    score_books.emplace_back(stoi(data[i]));
                }
                cout << "Score books" << endl;
                for(int i = 0; i < score_books.size(); i++){
                    cout << " " << score_books[i] << " ";
                }
                cout << endl;
            }
            else{
                if(line_counter % 2 == 0){
                    libs.emplace_back(lib_data{stoi(data[0]), stoi(data[1]), stoi(data[2])});
                }
                else {
                    for(int i = 0; i < data.size(); i++){
                        libs.back().lib_books.emplace_back(stoi(data[i]));
                    }
                }
            }
        }
        
        line_counter++;
    }
    cout << "Libraries: " << endl;
    for(int i = 0; i < libs.size(); i++){
        cout << "n_books: " << libs[i].lib_number_of_books << " signup: " << libs[i].signup << " ship_days: " << libs[i].ship_days << endl;
       /* sort(libs[i].lib_books.begin(), libs[i].lib_books.end(), [&] (int book_a, int book_b) {
            return true; 
        });*/
        for(int j = 0; j < libs[i].lib_books.size(); j++){
            cout << " " << libs[i].lib_books[j] << " ";
        }
        cout << endl;
    }
    file.close();
    return 0;
}