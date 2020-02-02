#include <iostream>
#include <string>
#include <cctype>

using namespace std;

char encrypt(string key, char alph){
    string alphabets = "abcdefghijklmnopqrstuvwxyz";
    string::size_type encrypted = alphabets.find(alph);
    return key[encrypted];
}

int main()
{
    cout << "Enter the encryption key: ";
    string key;
    getline(cin, key);
    if ( key.length() != 26 ){
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
    }
    for (char& item : key){

        if (isupper(item)){
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return EXIT_FAILURE;
        }
        for (char alph = 'a'; alph < 'z'; alph++){
            if (key.find(alph) == string::npos){
                cout << "Error! The encryption key must contain all alphabets a-z." << endl;
                return EXIT_FAILURE;
            }
        }
        cout << "Enter the text to be encrypted: ";
            string line;
            getline(cin, line);

            string encrypted = "";

            for (char& item2 : line) {
                encrypted += encrypt(key, item2);
            }

            cout << "Encrypted text: " << encrypted << endl;

            return 0;
        }

}
