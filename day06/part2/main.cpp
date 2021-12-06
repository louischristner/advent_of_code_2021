#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

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

size_t get_lanternfish_amount(const std::unordered_map<int, size_t> &lanternfishs)
{
    size_t lanternfish_amout = 0;

    for (auto l_pair : lanternfishs)
        lanternfish_amout += l_pair.second;
    return lanternfish_amout;
}

void init_lanternfishs(std::unordered_map<int, size_t> &lanternfishs)
{
    for (int i = 0; i <= 8; i++) {
        lanternfishs.emplace(i, 0);
    }
}

void set_lanternships(
    std::unordered_map<int, size_t> &l1,
    std::unordered_map<int, size_t> &l2
) {
    for (int i = 0; i <= 8; i++) {
        l1[i] = l2[i];
    }
}

void run_algo(std::unordered_map<int, size_t> &lanternfishs, const size_t &nbr_days)
{
    std::unordered_map<int, size_t> tmp_lanternfishs;

    for (size_t day = 0; day < nbr_days; day++) {

        init_lanternfishs(tmp_lanternfishs);

        for (auto l_pair : lanternfishs) {
            if (l_pair.first == 0) {
                tmp_lanternfishs[8] += l_pair.second;
                tmp_lanternfishs[6] += l_pair.second;
            } else {
                tmp_lanternfishs[l_pair.first - 1] += l_pair.second;
            }
        }

        set_lanternships(lanternfishs, tmp_lanternfishs);

        tmp_lanternfishs.clear();
    }
}

int main(int ac, char **av)
{
    std::string line;
    std::ifstream myfile(av[1]);

    std::unordered_map<int, size_t> lanternfishs;

    init_lanternfishs(lanternfishs);

    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
            std::vector<std::string> splitted_line = string_split(line, ",");
            for (std::string str_value : splitted_line)
                lanternfishs[std::stoi(str_value)] += 1;
            break;
        }

        myfile.close();
    }

    run_algo(lanternfishs, 256);

    std::cout << get_lanternfish_amount(lanternfishs) << std::endl;

    return 0;
}