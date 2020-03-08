#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Product {
    string productName;
    double price;
};

vector<string> split(string line, char sep, bool passEmpty = false) {
    vector<string> result = {};
    string temp;
    for (auto i : line) {

        if (i == sep) {
            if (passEmpty and temp.length() < 1) {
                temp = "";
                continue;
            }
            result.push_back(temp);
            temp = "";
        }
        else {
            temp += i;
        }
    }

    if (passEmpty and temp.length() < 1) {
        return result;
    }
    result.push_back(temp);

    return result;
}

void print_chains(map<string, map<string, vector<Product>>> data){
    for ( auto chainName : data ) {
        cout << chainName.first << endl;
    }
}

void print_stores(map<string, map<string, vector<Product>>> data, string chain) {
        for ( auto store : data[chain] ) {
            cout  << "  " << store.first << endl;
    }
}

vector<string> get_command(string input){

    vector<string> parts = split(input, ' ');
    string command = parts.at(0);
    parts.erase(parts.begin());
    return parts;
}



int main()
{
    map<string, map<string, vector<Product>>> data;
    string fileName;
    cout << "Input file: ";
    getline(cin, fileName);
    ifstream file(fileName);
    if (not file){
        cout << "Error! The input file cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    string row;
    while (getline(file, row)) {
        if (row.back() == ';') {
            cout << "Error: the input file has an erroneous line" << endl;
            return EXIT_FAILURE;
        }
        vector<string> tmpData = split(row, ';');
        vector<int>::size_type length = tmpData.size();
        for (auto i : tmpData)
            if (i == "") {
                cout << "Error: the input file has an erroneous line" << endl;
                return EXIT_FAILURE;
            }
        if (length != 4) {
            cout << "Error: the input file has an erroneous line" << endl;
            return EXIT_FAILURE;
        }

        Product product;
        if (tmpData.at(3) == "out-of-stock") {
            product = {tmpData.at(2), -1.0};
        }
        else {
            product = {tmpData.at(2), stod(tmpData.at(3))};
        }

        data[tmpData.at(0)][tmpData.at(1)].push_back(product);

    }
    file.close();
    for ( auto tietopari : data ) {
        cout << tietopari.first << endl;
        for ( auto tpari : tietopari.second ) {
            cout  << "  " << tpari.first << endl;
            for (auto tuote : tpari.second){
                if (tuote.price != -1.0){
                cout << "      " << tuote.productName << "   "
                     << tuote.price << endl;
                }
                else {
                    cout << "      " << tuote.productName << "   "
                         << "OUT OF STOCK" << endl;
                }
            }
        }

    }

    while(true){
        cout << "> ";
        string input;
        getline(cin, input);
        vector<string> parts = split(input, ' ');
        string command = parts.at(0);
        parts.erase(parts.begin());
        //for (auto const& value : parts) {
          //  std::cout << value << std::endl;
        //}
        if (command == "quit") {
            return EXIT_SUCCESS;
        }

        else if (command == "chains") {
            print_chains(data);
            continue;
        }

        else if (command == "stores") {
            if ( parts.size() != 1) {
                cout << "Error: error in command " << command << endl;
                continue;
            }
            else if (data.find(parts.at(0)) == data.end()) {
                cout << "Error: unknown chain name" << endl;
                continue;
            }
            else {
                for (const auto store : data[parts.at(0)]) {
                    cout << store.first  << endl;
                }
            }
         }
        else if (command == "selection") {
            if ( parts.size() != 2) {
                cout << "Error: error in command " << command << endl;
                continue;
            }
            else if (data.find(parts.at(0)) == data.end() or
                      data[parts.at(0)].find(parts.at(1)) == data.end()) {
                cout << "Error: error in command " << command << endl;
                continue;
            }
        }

        else {
            cout << "Error: unknown command: " << command << endl;
        }
    }
}
