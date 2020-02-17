#include <iostream>
#include <map>
#include <fstream>

using namespace std;

int main()
{
    string syote;
    cout << "Input file: ";
    getline(cin, syote);
    ifstream tiedosto(syote);
    if (not tiedosto){
    cout << "Error! The file " << syote << " cannot be opened." << endl;
    return EXIT_FAILURE;
    }
    
    map<string, int> pisteet;
    string rivi = "";
    while ( getline(tiedosto, rivi)){
        string::size_type i = rivi.find(":");
        string nimi = rivi.substr(0, i);
        int pistemaara = stoi(rivi.substr(i + 1));
        if( pisteet.find(nimi) == pisteet.end())
            pisteet.insert({nimi, pistemaara});
        else
            pisteet[nimi] += pistemaara;
    }
    cout << "Final scores:" << endl;
    for ( auto it : pisteet){
        cout << it.first << ": " << it.second << endl;
    }
}
