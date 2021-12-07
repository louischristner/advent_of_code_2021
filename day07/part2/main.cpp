#include <cmath>
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

size_t get_fuel_from_distance(const int &distance)
{
    if (distance <= 0)
        return 0;
    return distance + get_fuel_from_distance(distance - 1);
}

size_t get_fuel_amount(const std::vector<int> &crabs_pos)
{
    int mean = 0;
    size_t fuel_amount = 0;

    for (const int &pos : crabs_pos)
        mean += pos;
    mean = std::floor((double) mean / crabs_pos.size());

    for (const int &pos : crabs_pos)
        fuel_amount += get_fuel_from_distance(std::abs(mean - pos));

    return fuel_amount;
}

int main(int ac, char **av)
{
    std::string line;
    std::ifstream myfile(av[1]);

    std::vector<int> crabs_pos;

    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
            std::vector<std::string> splitted_line = string_split(line, ",");
            for (std::string str_value : splitted_line)
                crabs_pos.push_back(std::stoi(str_value));
        }

        myfile.close();
    }

    std::cout << get_fuel_amount(crabs_pos) << std::endl;

    return 0;
}