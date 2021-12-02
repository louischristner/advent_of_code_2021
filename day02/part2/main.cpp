#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

struct Vect3 {
    int x;
    int y;
    int z;
};

void forward(Vect3 &pos, std::vector<std::string> args)
{
    pos.x += std::stoi(args[1]);
    pos.y += std::stoi(args[1]) * pos.z;
}

void up(Vect3 &pos, std::vector<std::string> args)
{
    pos.z -= std::stoi(args[1]);
}

void down(Vect3 &pos, std::vector<std::string> args)
{
    pos.z += std::stoi(args[1]);
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

    std::unordered_map<std::string, void (*)(Vect3 &, std::vector<std::string>)> func_pointer;

    func_pointer.emplace("forward", &forward);
    func_pointer.emplace("down", &down);
    func_pointer.emplace("up", &up);

    Vect3 pos = {0, 0, 0};

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