#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

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

std::vector<char> get_containing(const std::vector<char> &getter, const std::vector<char> &container)
{
    std::vector<char> result;

    for (const char &g : getter)
        if (std::find(container.begin(), container.end(), g) != container.end())
            result.push_back(g);
    return result;
}

std::vector<char> get_not_containing(const std::vector<char> &getter, const std::vector<char> &container)
{
    std::vector<char> result;

    for (const char &g : getter)
        if (std::find(container.begin(), container.end(), g) == container.end())
            result.push_back(g);
    return result;
}

std::vector<char> string_to_vector(const std::string &str)
{
    std::vector<char> result;

    for (const char &c : str)
        result.push_back(c);
    return result;
}

bool is_unique(
    const int &digit,
    const size_t &size,
    const std::string &pattern,
    std::unordered_map<int, std::vector<char>> &digits
) {
    if (pattern.size() != size)
        return false;
    digits[digit] = string_to_vector(pattern);
    return true;
}

bool is_two(
    const std::string &pattern,
    const std::vector<char> &four_specials,
    std::unordered_map<int, std::vector<char>> &digits
) {
    std::vector<char> pattern_digits;

    if (pattern.size() != 5)
        return false;
    pattern_digits = string_to_vector(pattern);
    if (get_containing(four_specials, pattern_digits).size() != 1)
        return false;
    if (get_containing(digits[1], pattern_digits).size() != 1)
        return false;
    digits[2] = pattern_digits;
    return true;
}

bool is_three(
    const std::string &pattern,
    const std::vector<char> &four_specials,
    std::unordered_map<int, std::vector<char>> &digits
) {
    std::vector<char> pattern_digits;

    if (pattern.size() != 5)
        return false;
    pattern_digits = string_to_vector(pattern);
    if (get_containing(four_specials, pattern_digits).size() != 1)
        return false;
    if (get_containing(digits[1], pattern_digits).size() != 2)
        return false;
    digits[3] = pattern_digits;
    return true;
}

bool is_five(
    const std::string &pattern,
    const std::vector<char> &four_specials,
    std::unordered_map<int, std::vector<char>> &digits
) {
    std::vector<char> pattern_digits;

    if (pattern.size() != 5)
        return false;
    pattern_digits = string_to_vector(pattern);
    if (get_containing(four_specials, pattern_digits).size() != 2)
        return false;
    digits[5] = pattern_digits;
    return true;
}

bool is_six(
    const std::string &pattern,
    const std::vector<char> &four_specials,
    std::unordered_map<int, std::vector<char>> &digits
) {
    std::vector<char> pattern_digits;

    if (pattern.size() != 6)
        return false;
    pattern_digits = string_to_vector(pattern);
    if (get_containing(four_specials, pattern_digits).size() != 2)
        return false;
    if (get_containing(digits[1], pattern_digits).size() != 1)
        return false;
    digits[6] = pattern_digits;
    return true;
}

bool is_nine(
    const std::string &pattern,
    const std::vector<char> &four_specials,
    std::unordered_map<int, std::vector<char>> &digits
) {
    std::vector<char> pattern_digits;

    if (pattern.size() != 6)
        return false;
    pattern_digits = string_to_vector(pattern);
    if (get_containing(digits[4], pattern_digits).size() != 4)
        return false;
    digits[9] = pattern_digits;
    return true;
}

bool is_zero(
    const std::string &pattern,
    const std::vector<char> &four_specials,
    std::unordered_map<int, std::vector<char>> &digits
) {
    std::vector<char> pattern_digits;

    if (pattern.size() != 6)
        return false;
    pattern_digits = string_to_vector(pattern);
    if (get_containing(four_specials, pattern_digits).size() != 1)
        return false;
    if (get_containing(digits[1], pattern_digits).size() != 2)
        return false;
    digits[0] = pattern_digits;
    return true;
}

size_t resolve(const std::vector<Entry> &entries)
{
    size_t result = 0;
    std::vector<bool (*)(
        const std::string &,
        const std::vector<char> &,
        std::unordered_map<int, std::vector<char>> &)
    > func_ptr = {
        is_two, is_three, is_five,
        is_six, is_nine, is_zero
    };

    for (Entry entry : entries) {
        std::string output_result = "";
        std::vector<char> four_specials;
        std::unordered_map<int, std::vector<char>> digits;

        digits.emplace(0, std::vector<char>());
        digits.emplace(1, std::vector<char>());
        digits.emplace(2, std::vector<char>());
        digits.emplace(3, std::vector<char>());
        digits.emplace(4, std::vector<char>());
        digits.emplace(5, std::vector<char>());
        digits.emplace(6, std::vector<char>());
        digits.emplace(7, std::vector<char>());
        digits.emplace(8, std::vector<char>());
        digits.emplace(9, std::vector<char>());

        for (std::string signal : entry.signal_patterns) {
            if (is_unique(1, 2, signal, digits)) continue;
			if (is_unique(4, 4, signal, digits)) continue;
			if (is_unique(7, 3, signal, digits)) continue;
			if (is_unique(8, 7, signal, digits)) continue;
        }

        four_specials = get_not_containing(digits[4], digits[1]);

        for (std::string signal : entry.signal_patterns)
            for (auto f_ptr : func_ptr)
                if (f_ptr(signal, four_specials, digits))
                    continue;

        for (std::string signal : entry.output_value)
            for (const std::pair<int, std::vector<char>> &digit : digits)
                if (digit.second.size() == signal.size() && get_containing(string_to_vector(signal), digit.second).size() == signal.size())
                    output_result += std::to_string(digit.first);

        result += std::stoi(output_result);
    }

    return result;
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

    std::cout << resolve(entries) << std::endl;

    return 0;
}