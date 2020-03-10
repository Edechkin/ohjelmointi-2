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
#include <set>
#include <iomanip>
#include <algorithm>

using namespace std;


struct Product {
    string productName;
    double price;

    bool operator <(const Product& rhs) {
        return  productName < rhs.productName ;
    }
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
/* Prints all chains from data structure
 *
 * @param data contains stored data from a file
 */
    for ( auto chainName : data ) {
        cout << chainName.first << endl;
    }
}

void print_stores(map<string, map<string, vector<Product>>> data, string chain){
/* Prints all stores of wanted chain
 *
 * @param data contains stored data from a file
 * @param chain is a shopping chain that info we want
 */

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
/* Finds the cheapest product on the market
 *
 * @param productToFind is users product that he wants info about
 * @param catalogue contains stored data from a file
 *
 * returns list of cheapest price and stores who got that price
  */
    double reference = 1000000;
    pair<double, map<string, vector<string>>> list ;
    for (const auto chain : catalogue) {
        for (const auto store : chain.second){
            for (const auto product : store.second) {
                if (product.productName == productToFind) {
                    if (product.price < reference or product.price == -1
                            or reference == -1) {
                        if (product.price > -1 ) {
                        reference = product.price;
                        list.second.clear();
                        list.first = reference;
                        list.second[chain.first].push_back(store.first);
                        }
                        else {
                            if (list.second.empty()){
                                list.first = -1.0;
                                reference = -1.0;
                            }
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
/* Prints cheapest specific product on the market
 *
 * @param cheapestData contains price of the product and stores who sell it on that price
 */
    if (cheapestData.first == -1.0) {
        cout << "The product is temporarily out of stock everywhere" << endl;
    }
    else{
        cout<<fixed<<setprecision(2) << cheapestData.first << " euros" << endl;


        for (const auto chain : cheapestData.second) {
            for (const auto store : chain.second)

                cout << chain.first << " " << store << endl;
        }
    }
}

void print_all_products(map<string, map<string, vector<Product>>> data) {
/* Prints all products on the market
 *
 * @param data contains stored data from inputfile
 */
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

int main()
{
    map<string, map<string, vector<Product>>> data;
    string fileName;
    cout << "Input file: ";
    getline(cin, fileName);
    ifstream file(fileName);
    if (not file){
        cout << "Error: the input file cannot be opened" << endl;
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
                            if(tmpData.at(3) == "out-of-stock") {
                                data[chain][store][findItem].price = -1.0;
                                foundItem = true;
                            }
                            else{
                            data[chain][store][findItem].price =
                                    stod(tmpData.at(3));
                            foundItem = true;
                            }
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

    // Userinterface for info searches

    while(true){
        cout << "> ";
        string input;
        getline(cin, input);
        vector<string> parts = split(input, ' ');
        string command = parts.at(0);
        parts.erase(parts.begin());
        if (command == "quit") {
            return EXIT_SUCCESS;
        }

        else if (command == "chains") {
            if ( parts.size() != 0) {
                cout << "Error: error in command " << command << endl;
                continue;
            }
            else {
            print_chains(data);
            continue;
            }
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
                vector<Product> tuotteet = data[parts.at(0)][parts.at(1)];
                sort(tuotteet.begin(), tuotteet.end());
                for (const auto product : tuotteet)
                    if (product.price != -1 and product.price != 0.0){

                        cout << product.productName << " "
                             << fixed<<setprecision(2) << product.price
                             << endl;
                    }
                    else {
                        cout << product.productName << " out of stock" << endl;
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
            }
            print_all_products(data);
        }
        else {
            cout << "Error: unknown command: " << command << endl;
        }
    }
}
