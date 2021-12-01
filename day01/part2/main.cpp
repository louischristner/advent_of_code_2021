#include <vector>
#include <fstream>
#include <iostream>

int main(int ac, char **av)
{
    std::string line;
    std::ifstream myfile(av[1]);

    std::vector<size_t> values;

    size_t count_increase = 0;

    if (myfile.is_open()) {
        while (std::getline(myfile, line))
            values.push_back(std::stoull(line));
        myfile.close();
    }


    for (size_t index = 1; index < values.size() - 1; index++) {
        size_t first_sum = values[index - 1] + values[index] + values[index + 1];
        size_t second_sum = values[index] + values[index + 1] + values[index + 2];

        if (second_sum > first_sum) {
            count_increase += 1;
        }
    }

    std::cout << count_increase << std::endl;

    return 0;
}