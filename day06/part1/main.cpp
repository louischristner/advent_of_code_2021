#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

std::vector<std::string> string_split(std::string str, const std::string &delimiter)
{
    std::vector<std::string> result;

    for (size_t pos = 0; (pos = str.find(delimiter)) != std::string::npos; ) {
        result.push_back(str.substr(0, pos));
        str.erase(0, pos + delimiter.length());
    }

    result.push_back(str);

    return result;
}

int main(int ac, char **av)
{
    std::string line;
    std::ifstream myfile(av[1]);

    std::list<int> lanternfishs;

    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
            std::vector<std::string> splitted_line = string_split(line, ",");
            for (std::string str_value : splitted_line)
                lanternfishs.push_back(std::stoi(str_value));
            break;
        }

        myfile.close();
    }

    for (size_t day = 0; day < 80; day++) {
        for (int &lanternfish : lanternfishs) {
            if (lanternfish == 0) {
                lanternfishs.push_front(8);
                lanternfish = 6;
            } else {
                lanternfish -= 1;
            }
        }
    }

    std::cout << lanternfishs.size() << std::endl;

    return 0;
}