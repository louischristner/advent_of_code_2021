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

int get_rating(
    std::vector<std::string> diagnostic_report,
    char (*condition)(const Vect2 &)
) {
    size_t index = 0;
    char result = '0';

    while (diagnostic_report.size() > 1) {
        result = condition(get_bit_amount(diagnostic_report, index));

        for (std::vector<std::string>::iterator ptr = diagnostic_report.begin();
            ptr != diagnostic_report.end(); ptr++) {

            if ((*ptr)[index] != result) {
                diagnostic_report.erase(ptr);
                ptr--;
            }
        }

        if (index + 1 >= diagnostic_report[0].size()) {
            index = 0;
        } else index += 1;
    }

    return std::stoi(diagnostic_report[0], 0, 2);
}

char oxygen_generator_condition(const Vect2 &amount)
{
    return (amount.x > amount.y) ? '0' : '1';
}

char co2_scrubber_condition(const Vect2 &amount)
{
    return (amount.y < amount.x) ? '1' : '0';
}

int main(int ac, char **av)
{
    std::string line;
    std::ifstream myfile(av[1]);

    std::vector<std::string> diagnostic_report;

    if (myfile.is_open()) {
        while (std::getline(myfile, line))
            diagnostic_report.push_back(line);
        myfile.close();
    }

    int oxygen_rating = get_rating(diagnostic_report, &oxygen_generator_condition);
    int co2_rating = get_rating(diagnostic_report, &co2_scrubber_condition);

    std::cout << oxygen_rating * co2_rating << std::endl;

    return 0;
}