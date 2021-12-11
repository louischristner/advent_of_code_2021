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

template<typename T>
void print_grid(const std::vector<std::vector<T>> &grid)
{
    for (const std::vector<T> &a : grid) {
        for (const T &b : a)
            std::cout << b;
        std::cout << std::endl;
    }
}

bool update_grid(std::vector<std::vector<size_t>> &octopus_grid, std::vector<std::vector<bool>> &updated_grid)
{
    bool has_been_updated = false;
    size_t i_size = octopus_grid.size();
    size_t j_size = octopus_grid[0].size();

    for (size_t i = 0; i < i_size; i++) {
        for (size_t j = 0; j < j_size; j++) {
            if (octopus_grid[i][j] > 9 && updated_grid[i][j] == false) {
                for (int i_p = -1; i_p <= 1; i_p++) {
                    for (int j_p = -1; j_p <= 1; j_p++) {
                        if (i_p == 0 && j_p == 0) continue;
                        if (i + i_p >= 0 && i + i_p < i_size && j + j_p >= 0 && j + j_p < j_size) {
                            octopus_grid[i + i_p][j + j_p] += 1;
                            updated_grid[i][j] = true;
                            has_been_updated = true;
                        }
                    }
                }
            }
        }
    }

    return has_been_updated;
}

size_t resolve(std::vector<std::vector<size_t>> &octopus_grid)
{
    size_t flash_count = 0;
    size_t last_flash_count = 0;
    size_t i_size = octopus_grid.size();
    size_t j_size = octopus_grid[0].size();
    std::vector<std::vector<bool>> updated_grid =
        std::vector<std::vector<bool>>(i_size, std::vector<bool>(j_size, false));

    for (size_t step = 0; true; step++) {
        for (size_t i = 0; i < i_size; i++) {
            for (size_t j = 0; j < j_size; j++) {
                octopus_grid[i][j] += 1;
                updated_grid[i][j] = false;
            }
        }

        while (update_grid(octopus_grid, updated_grid));

        for (size_t i = 0; i < i_size; i++) {
            for (size_t j = 0; j < j_size; j++) {
                if (octopus_grid[i][j] > 9) {
                    octopus_grid[i][j] = 0;
                    flash_count += 1;
                }
            }
        }

        // print_grid(octopus_grid);
        // std::cout << "----------" << std::endl;

        if (flash_count - last_flash_count == i_size * j_size)
            return step + 1;
        last_flash_count = flash_count;
    }

    return 0;
}

int main(int ac, char **av)
{
    std::string line;
    std::ifstream myfile(av[1]);

    std::vector<std::vector<size_t>> octopus_grid;

    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
            octopus_grid.push_back(std::vector<size_t>());
            for (char value : line)
                octopus_grid[octopus_grid.size() - 1].push_back(value - '0');
        }

        myfile.close();
    }

    std::cout << resolve(octopus_grid) << std::endl;

    return 0;
}