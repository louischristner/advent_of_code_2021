#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
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

void display_caves(const std::unordered_map<std::string, std::vector<std::string>> &caves)
{
    for (auto cave : caves) {
        std::cout << cave.first << ": ";
        for (auto link : cave.second)
            std::cout << link << ",";
        std::cout << std::endl;
    }
}

template<typename T>
void display_vector(const std::vector<T> &v)
{
    for (const T &value : v)
        std::cout << value << ",";
    std::cout << std::endl;
}

bool is_lowercase(const std::string &str)
{
    for (const char &c : str)
        if (!islower(c))
            return false;
    return true;
}

std::vector<std::vector<std::string>> resolve(
    std::unordered_map<std::string, std::vector<std::string>> &caves,
    std::vector<std::string> visited_caves,
    const std::string &current_cave
) {
    std::vector<std::vector<std::string>> paths;

    visited_caves.push_back(current_cave);

    if (current_cave == "end")
        return std::vector<std::vector<std::string>>(1, visited_caves);

    for (const std::string &linked_cave : caves[current_cave]) {
        if (is_lowercase(linked_cave) && std::find(visited_caves.begin(), visited_caves.end(), linked_cave) != visited_caves.end())
            continue;
        for (std::vector<std::string> path : resolve(caves, visited_caves, linked_cave)) {
            paths.push_back(path);
        }
    }

    return paths;
}

int main(int ac, char **av)
{
    std::string line;
    std::ifstream myfile(av[1]);

    std::unordered_map<std::string, std::vector<std::string>> caves;

    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
            std::vector<std::string> cave_link = string_split(line, "-");
            if (caves.find(cave_link[0]) == caves.end())
                caves.emplace(cave_link[0], std::vector<std::string>());
            caves[cave_link[0]].push_back(cave_link[1]);
            if (caves.find(cave_link[1]) == caves.end())
                caves.emplace(cave_link[1], std::vector<std::string>());
            caves[cave_link[1]].push_back(cave_link[0]);
        }

        myfile.close();
    }

    std::cout << resolve(caves, std::vector<std::string>(), "start").size() << std::endl;

    return 0;
}