#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";

    int lampotila;
    cin >> lampotila;
    float celsius;
    float fahrenheit;
    fahrenheit = lampotila * 1.8 + 32;
    celsius = (lampotila - 32) / 1.8;
    cout << lampotila << " degrees Celsius is " << fahrenheit << " degrees Fahrenheit" << endl;
    cout << lampotila << " degrees Fahrenheit is " << celsius << " degrees Celsius" << endl;

    return 0;
}
