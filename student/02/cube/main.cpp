#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a number: ";
    int no;
    cin >> no;
    int cube = no * no * no;
    if (cube < 0 or cube / no / no != no){
        cout << "Error! The cube of " << no << " is not " << cube << "." << endl;
    }
    else{
        cout << "The cube of " << no << " is " << cube << "." << endl;
        }

}
