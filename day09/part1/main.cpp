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

    std::vector<std::string> height_map;

    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
            height_map.push_back(line);
        }

        myfile.close();
    }

    size_t risk_sum = 0;

    size_t i_size = height_map.size();
    size_t j_size = height_map[0].size();

    for (int i = 0; i < i_size; i++) {
        for (int j = 0; j < j_size; j++) {
            char pos = height_map[i][j];
            char a = (j + 1 < j_size) ? height_map[i][j + 1] : '9' + 1;
            char c = (i + 1 < i_size) ? height_map[i + 1][j] : '9' + 1;
            char b = (j - 1 >= 0) ? height_map[i][j - 1] : '9' + 1;
            char d = (i - 1 >= 0) ? height_map[i - 1][j] : '9' + 1;

            if (pos < a && pos < b && pos < c && pos < d) {
                std::cout << i << "," << j << " " << pos << std::endl;
                risk_sum += ((pos - '0') + 1);
            }
        }
    }

    std::cout << risk_sum << std::endl;

    return 0;
}