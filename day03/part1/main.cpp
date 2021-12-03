#include <vector>
#include <fstream>
#include <iostream>

struct Vect2 {
    size_t x, y;
};

Vect2 get_bit_amount(
    const std::vector<std::string>& diagnostic_report,
    const size_t &index
) {
    size_t zero_count = 0;
    size_t one_count = 0;

    for (size_t i = 0; i < diagnostic_report.size(); i++) {
        zero_count += (diagnostic_report[i][index] == '0') ? 1 : 0;
        one_count += (diagnostic_report[i][index] == '1') ? 1 : 0;
    }

    return { zero_count, one_count };
}

int main(int ac, char **av)
{
    std::string line;
    std::ifstream myfile(av[1]);

    std::vector<std::string> diagnostic_report;

    std::string gamma("");
    std::string epsilon("");

    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
            diagnostic_report.push_back(line);
        }
        myfile.close();
    }

    for (size_t i = 0; i < diagnostic_report[0].size(); i++) {
        Vect2 amount = get_bit_amount(diagnostic_report, i);
        gamma += (amount.x > amount.y) ? '0' : '1';
        epsilon += (amount.x > amount.y) ? '1' : '0';
    }

    std::cout << std::stoi(gamma, 0, 2) * std::stoi(epsilon, 0, 2) << std::endl;

    return 0;
}