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
        vector<string> tmpData = split(row, ';');
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
        //for ( auto tpari : tietopari.second ) {
          //  cout  << "  " << tpari.first << endl;
            //for (auto tuote : tpari.second){
              //  if (tuote.price != -1.0){
                //cout << "      " << tuote.productName << "   "
                  //   << tuote.price << endl;
                }
                //else {
                  //  cout << "      " << tuote.productName << "   "
                    //     << "OUT OF STOCK" << endl;
                }
            //}
        //}

    //}
//}
