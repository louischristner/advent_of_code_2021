#include <fstream>
#include <iostream>

int main(int ac, char **av)
{
    std::string line;
    std::ifstream myfile(av[1]);

    int current_val = -1;
    int prev_val = -1;

    size_t count_increase = 0;

    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
            current_val = std::stoi(line);
            if (prev_val > 0) {
                if (current_val > prev_val)
                    count_increase += 1;
            }

            prev_val = current_val;
        }
        myfile.close();
    }

    std::cout << count_increase << std::endl;

    return 0;
}