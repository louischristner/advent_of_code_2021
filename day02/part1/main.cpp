#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

struct Vect2 {
    int x;
    int y;
};

void forward(Vect2 &pos, std::vector<std::string> args)
{
    pos.x += std::stoi(args[1]);
}

void up(Vect2 &pos, std::vector<std::string> args)
{
    pos.y -= std::stoi(args[1]);
}

void down(Vect2 &pos, std::vector<std::string> args)
{
    pos.y += std::stoi(args[1]);
}

std::vector<std::string> string_split(const std::string& str)
{
	std::vector<std::string> result;
	std::istringstream iss(str);

	for (std::string s; iss >> s; )
		result.push_back(s);
	return result;
}

int main(int ac, char **av)
{
    std::string line;
    std::ifstream myfile(av[1]);

    std::unordered_map<std::string, void (*)(Vect2 &, std::vector<std::string>)> func_pointer;

    func_pointer.emplace("forward", &forward);
    func_pointer.emplace("down", &down);
    func_pointer.emplace("up", &up);

    Vect2 pos = {0, 0};

    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
            std::vector<std::string> args = string_split(line);
            func_pointer[args[0]](pos, args);
        }
        myfile.close();
    }

    std::cout << pos.x * pos.y << std::endl;

    return 0;
}