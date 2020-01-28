#include <iostream>

using namespace std;

unsigned long int kertoma(unsigned long int luku){
    unsigned long int summa = 1;
    unsigned long int luku2 = luku;
    while (luku2 > 1){
        summa *= luku2;
        --luku2;
    }
    return summa;
}

int main()
{
    unsigned long int odd;
    int total;
    int drawn;
    cout << "Enter the total number of lottery balls: ";
    cin >> total;
    cout << "Enter the number of drawn balls: ";
    cin >> drawn;
    if (total < 1 or drawn < 1){
        cout << "The number of balls must be a positive number." << endl;
    }
    else if (drawn > total){
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
    }
    else{
        odd = kertoma(total) / (kertoma(total - drawn) * kertoma(drawn));
        cout << "The probability of guessing all " << drawn <<  " balls correctly is 1/" << odd << endl;
    }



}
