/* This program stores and processes data from a file related to
* product range of retail chains.
* Prints all chains
* Prints chain's stores
* Prints product selection of specific store
* Prints cheapest product on the market and where to find it
*Names: Tommi Mehtanen, Eetu Jokinen
* Student numbers: 279330, 273281
* UserID: teekkart ( Necessary due to gitlab folder naming. )
* E-Mails: tommi.mehtanen@tuni.fi; eetu.jokinen@tuni.fi
* */

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <set>

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

void print_stores(map<string, map<string, vector<Product>>> data, string chain){
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

pair<double, map<string, vector<string>>> find_cheapest(string productToFind,
                     map<string, map<string, vector<Product>>> catalogue){
    double reference = 1000000;
    pair<double, map<string, vector<string>>> list ;
    for (const auto chain : catalogue) {
        for (const auto store : chain.second){
            for (const auto product : store.second) {
                if (product.productName == productToFind) {
                    if (product.price < reference) {
                        if (product.price > 0) {
                        reference = product.price;
                        list.second.clear();
                        list.first = reference;
                        list.second[chain.first].push_back(store.first);
                        }                        
                    }
                    else if (product.price == reference) {
                        list.second[chain.first].push_back(store.first);
                    }
                }                
            }
        }       
    }
    return list;
}

void print_cheapest(pair<double, map<string, vector<string>>> cheapestData) {
    cout << cheapestData.first << endl;
    for (const auto chain : cheapestData.second) {
        for (const auto store : chain.second)
            cout << chain.first << " " << store << endl;
    }
}

void print_all_products(map<string, map<string, vector<Product>>> data) {
    set<string> products;
    for (const auto chain : data) {
        for (const auto store : chain.second) {
            for (const auto product : store.second) {
                products.insert(product.productName);
            }
        }
    }
    for (const auto product : products) {
            cout << product << endl;  
}
}

//bool check_overlap(map<string, map<string, vector<Product>>> data, map chain,
  //                 string) {
    
//}

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
        if (data.empty()) {    
            data[tmpData.at(0)][tmpData.at(1)].push_back(product);

        }
         
        else {
            string chain = tmpData.at(0);
            string store = tmpData.at(1);
            string name = product.productName;
            int findItem = 0;
            bool foundItem = false;
                    for (auto product : data[chain][store]){
                        if ( product.productName == tmpData.at(2)) {
                            data[chain][store][findItem].price = stod(tmpData.at(3));
                            foundItem = true;
                        }
                        else{
                           findItem++ ;
                        }
                    }
                    if (!foundItem) {
                        data[tmpData.at(0)][tmpData.at(1)].push_back(product);
                    }

        }
    }
    file.close();

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
            else if (data.find(parts.at(0)) == data.end()){
                cout << "Error: unknown chain name " << endl;
                continue;
            }
            else if( data[parts.at(0)].find(parts.at(1))
                     == data[parts.at(0)].end()) {
                cout << "Error: unknown store " << endl;
                continue;
            }
            else {
                for (const auto product : data[parts.at(0)][parts.at(1)])
                    if (product.price != -1){
                        cout << product.productName << " "
                             << fixed<<setprecision(2)<< product.price << endl;

                    }
                    else {
                        cout << product.productName << " OUT OF STOCK" << endl;
                    }
            }
        }
        else if (command == "cheapest") {
            if ( parts.size() != 1) {
                cout << "Error: error in command " << command << endl;
                continue;
            }
            int test = 0;
            for (const auto chain : data){
                for (const auto store : chain.second){
                    for (const auto product : store.second) {
                        if (product.productName == parts.at(0)) {
                            ++test;
                        }
                    }
                }
            }
            if (test == 0) {
            cout << "The product is not part of product selection" << endl;
            continue;
            }
            pair<double, map<string, vector<string>>> cheapest =
            find_cheapest(parts.at(0), data);
            print_cheapest(cheapest);

        }

        else if (command == "products") {
            if ( parts.size() != 0) {
                cout << "Error: error in command " << command << endl;
                continue;
            //set<string> products = collect_products(data);
            //print_products(products);
            }
            print_all_products(data);
        }
        else {
            cout << "Error: unknown command: " << command << endl;
        }
    }
}
