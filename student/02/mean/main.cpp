#include <iostream>

// Write here a function counting the mean value


int main()
{
    double syote;
    float mean;
    double summa;
    std::cout << "From how many integer numbers you want to count the mean value? ";
    int maara;
    std::cin >> maara;
    if (maara < 1){
        std::cout << "Cannot count mean value from " << maara << " numbers" << std::endl;
    }
    else if (maara == 1){
        std::cout << "Input 1. number: ";
        std::cin >> syote;
        mean = syote;
        std::cout << "Mean value of the given numbers is " << mean << std::endl;
    }
    else {


        for (int luku = 1; luku < maara + 1; ++luku) {
            std::cout << "Input " << luku <<". number: ";
            std::cin >> syote;

            summa += syote;

        }

        mean = summa / maara;
        std::cout << "Mean value of the given numbers is " << mean << std::endl;
    }
}
