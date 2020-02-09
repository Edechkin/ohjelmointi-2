#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}

// TODO: Implement your solution here
bool same_values(const std::vector <int>& ints){
    int c = 0;
    int prev = 0;
    if (ints.at(0) != ints.at(1)){
        return false;
    }
    else{
        for (int item : ints){
            if ( c > 1){
                if (item != prev){
                        return false;
                    }
                }
            prev = item;
            ++c;
        }
        return true;
    }
}

bool is_arithmetic_series(const std::vector <int>& ints){
    int c = 0;
    int prev = 0;
    int diff = ints.at(1) - ints.at(0);
    for (int item : ints){
        if ( c > 1){
            if (item - prev != diff){
                    return false;
                }
            }
        prev = item;
        ++c;
    }
    return true;
}

bool is_ordered_non_strict_ascending(const std::vector <int>& ints){
    int c = 0;
    int prev = 0;

    for (int item : ints){
        if ( c > 1){
            if (item < prev){
                    return false;
                }
            }
        prev = item;
        ++c;
    }
    return true;
}

bool is_geometric_series(const std::vector <int>& ints){
    int c = 0;
    int first = ints.at(0);
    int second = ints.at(1);
    double prev = 0;
    double rel = static_cast <double> (first) / static_cast <double> (second);
    for (int item : ints){
        if (item == 0){
            return false;
        }
        else if ( c > 1){
            if (prev / item != rel){
                    return false;
                }
            }
        prev = item;
        ++c;
    }
    return true;
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
