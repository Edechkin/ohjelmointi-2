#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string syote;
    cout << "Input file: ";
    getline(cin, syote);
    cout << "Output file: ";
    string syote2;
    getline(cin, syote2);

    ifstream stiedosto(syote);
    if (not stiedosto){
    cout << "Error! The file " << syote << " cannot be opened." << endl;
    return EXIT_FAILURE;
    }
    ofstream otiedosto(syote2);
    int i = 1;
    string rivi;
    while( getline(stiedosto, rivi)){
        otiedosto << i << " " << rivi << endl;
        ++i;
    }
    stiedosto.close();
    otiedosto.close();
}
