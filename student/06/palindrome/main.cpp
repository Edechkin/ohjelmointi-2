#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
  RECURSIVE_FUNC
  // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
  // ------------


  // Add your implementation here
        int b = 0;
        int length = s.length();
        int e = length - 1;
        if (length <= 1)
          return true;
        else if (length == 2 and s.at(b) == s.at(e))
                return true;
        else{
            if (s.at(b) == s.at(e)){
                return palindrome_recursive(s.substr(1, length-2));
            }
            else if (b != e){
                return false;
            }
        }
        return true;
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
