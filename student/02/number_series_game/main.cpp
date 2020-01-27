#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";
    int maara;
    std::cin >> maara;
    for ( int luku = 1; luku < maara + 1; ++luku){
        if (luku % 3 == 0 and luku % 7 == 0){
            std::cout << "zip boing" << std::endl;
        }
        if (luku % 3 == 0){
            std::cout << "zip" << std::endl;
        }
        if (luku % 7 == 0){
            std::cout << "boing" << std::endl;
        }
        else{
            std::cout << luku << std::endl;
        }
    }

}
