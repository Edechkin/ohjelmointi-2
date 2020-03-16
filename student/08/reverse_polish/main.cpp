#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>

std::vector<std::string> split(const std::string& a, const char delimiter,
                               const bool ignore_empty = false) {
    std::vector<std::string> result;
    std::string tmp = a;

    while(tmp.find(delimiter) != std::string::npos) {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty())) {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty())) {
        result.push_back(tmp);
    }
    return result;
}

bool is_int(std::string goal){
    try  {
        throw(std::stoi(goal));
    }
    catch (const std::invalid_argument&)  {
        return false;
    }
    catch (...){
        return true;
    }
}


int main()
{
    std::string expression;
    std::string input;
    std::cout << "Input an expression in reverse Polish notation (end with #):" << std::endl;
    std::cout << "EXPR> ";
    std::getline(std::cin, input);
    if (!isdigit(input.at(0))){
        std::cout << "Error: Expression must start with a number" << std::endl;
        return EXIT_FAILURE;
    }
    expression = input.substr(0, input.size()-2);
    std::vector<std::string> tokens = split(expression, ' ');
    std::stack<int> stack;
    int result;
    for (std::string item : tokens){
        if (!is_int(item)){
            if (item != "+" && item != "-" && item != "*" && item != "/"){
                std::cout << "Error: Unknown character" << std::endl;
                return EXIT_FAILURE;
            }
            int num1 = stack.top();
            stack.pop();
            if (stack.size() == 0){
                std::cout << "Error: Too few operands" << std::endl;
                return EXIT_FAILURE;
            }
            int num2 = stack.top();
            stack.pop();
            if (item == "+"){
                result = num1 + num2;
                stack.push(result);
            }
            else if (item == "-"){
                result = num2 - num1;
                stack.push(result);
            }
            else if(item == "*"){
                result = num1 * num2;
                stack.push(result);
            }
            else if(item == "/"){
                if(num1 == 0){
                    std::cout << "Error: Division by zero" << std::endl;
                    return EXIT_FAILURE;
                }else{
                    result = num2 / num1;
                    stack.push(result);
                }
            }
        }
        else if(is_int(item)){
            int num = std::stoi(item);
            stack.push(num);
        }
    }
    if (stack.size() > 1){
        std::cout << "Error: Too few operators" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Correct: " << stack.top() << " is the result" << std::endl;
}
