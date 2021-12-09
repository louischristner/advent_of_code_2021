#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

struct Entry {
    Entry(std::vector<std::string> signals, std::vector<std::string> output):
        signal_patterns(signals), output_value(output) {}

    std::vector<std::string> signal_patterns;
    std::vector<std::string> output_value;
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

bool is_one(const std::string &pattern)
{
    return pattern.size() == 2;
}

bool is_four(const std::string &pattern)
{
    return pattern.size() == 4;
}

bool is_seven(const std::string &pattern)
{
    return pattern.size() == 3;
}

bool is_eight(const std::string &pattern)
{
    return pattern.size() == 7;
}

int main(int ac, char **av)
{
    std::string line;
    std::ifstream myfile(av[1]);

    std::vector<Entry> entries;

    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
            std::vector<std::string> splitted_line = string_split(line, " | ");
            std::vector<std::string> signals = string_split(splitted_line[0], " ");
            std::vector<std::string> output = string_split(splitted_line[1], " ");

            entries.push_back(Entry(signals, output));
        }

        myfile.close();
    }

    size_t count_unique_segments = 0;

    for (Entry entry : entries) {
        for (std::string signal : entry.output_value) {
            if (is_one(signal) || is_four(signal) || is_seven(signal) || is_eight(signal))
                count_unique_segments += 1;
        }
    }

    std::cout << count_unique_segments << std::endl;

    return 0;
}