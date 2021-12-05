#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

struct Vect2 {
    int x, y;
};

struct Line {
    Vect2 first, second;
};

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

    std::vector<Line> lines;

    std::vector<std::vector<int>> field(1000, std::vector<int>(1000, 0));

    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
            std::vector<std::string> line_parts = string_split(line, " -> ");
            std::vector<std::string> first_part = string_split(line_parts[0], ",");
            std::vector<std::string> second_part = string_split(line_parts[1], ",");
            Line new_line = {
                {std::stoi(first_part[0]), std::stoi(first_part[1])},
                {std::stoi(second_part[0]), std::stoi(second_part[1])}
            };

            if (new_line.first.x == new_line.second.x || new_line.first.y == new_line.second.y) {
                for (int i = std::min(new_line.first.x, new_line.second.x); i <= std::max(new_line.first.x, new_line.second.x); i++) {
                    for (int j = std::min(new_line.first.y, new_line.second.y); j <= std::max(new_line.first.y, new_line.second.y); j++) {
                        field[i][j] += 1;
                    }
                }
            }
        }

        myfile.close();
    }

    size_t overlaps = 0;

    for (size_t i = 0; i < 1000; i++)
        for (size_t j = 0; j < 1000; j++)
            if (field[i][j] >= 2)
                overlaps += 1;

    std::cout << overlaps << std::endl;

    return 0;
}