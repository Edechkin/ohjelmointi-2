#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

bool contains(const std::vector< std::pair<std::string, std::vector<int> >>& data, const std::string& word) {
    for (const auto& i : data) {
        if (i.first == word)
            return true;
    }

    return false;
}

void push_or_add (std::vector< std::pair<std::string, std::vector<int> >>& data, const std::string& word, const int& rowNum) {


    if (contains(data, word)) {
        for (auto& i : data) {
            if (i.first == word) {
                if (i.second.empty()) {
                    i.second.push_back(rowNum);
                } else if (i.second.back() != rowNum) {
                    i.second.push_back(rowNum);
                }
            }
        }
    } else {
        std::vector<int> rows = {rowNum};
        data.push_back(std::make_pair(word, rows));
    }
}

bool sort_name(std::pair<std::string, std::vector<int>> f, std::pair<std::string, std::vector<int>> s) {
    return f.first < s.first;
}

bool read_file(const std::string& filename, std::vector< std::pair<std::string, std::vector<int> >>& data) {


    std::ifstream file(filename);

    if (!file) {
        return false;
    }
    int rowNum = 0;
    std::string line;
    while ( getline(file, line) ) {
        rowNum++;
        std::vector<std::string> result;
        std::istringstream iss(line);
        for(std::string s; iss >> s; ) {
            push_or_add(data, s, rowNum);
        }
    }

    std::sort(data.begin(), data.end(), sort_name);
    return true;
}

int main()
{
    std::string filename;
    std::cout << "Input file: ";
    getline(std::cin, filename);
    std::vector< std::pair<std::string, std::vector<int> >> data = {};
    if (read_file(filename, data)) {
        for (const auto& i : data) {
            std::cout << i.first << " " << i.second.size() << ": ";
            for (size_t j = 0; j < i.second.size()-1; j++) {
                std::cout << i.second.at(j) << ", ";
            }
            std::cout << i.second.back() << std::endl;
        }
    } else {
        std::cout << "Error! The file " << filename << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }

    return 0;

}
