#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

struct Vect2 {
    int x, y;
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

bool find_if_pos_is_in_basin_pos(
    const Vect2 &pos,
    const Vect2 &direction,
    std::vector<Vect2> &basin_pos
) {
    return std::find_if(basin_pos.begin(), basin_pos.end(), [pos, direction](const Vect2 &b_pos){
        return pos.x + direction.x == b_pos.x && pos.y + direction.y == b_pos.y;
    }) != basin_pos.end();
}

void get_basin_from_pos(
    const std::vector<std::string> &height_map,
    const Vect2 &pos,
    std::vector<Vect2> &basin_pos
) {
    size_t i_size = height_map.size();
    size_t j_size = height_map[0].size();

    Vect2 a = {0, 1};
    Vect2 c = {1, 0};
    Vect2 b = {0, -1};
    Vect2 d = {-1, 0};

    basin_pos.push_back(pos);
    if (pos.y + 1 < j_size && height_map[pos.x][pos.y + 1] != '9' && !find_if_pos_is_in_basin_pos(pos, a, basin_pos))
        get_basin_from_pos(height_map, { pos.x, pos.y + 1 }, basin_pos);
    if (pos.x + 1 < i_size && height_map[pos.x + 1][pos.y] != '9' && !find_if_pos_is_in_basin_pos(pos, c, basin_pos))
        get_basin_from_pos(height_map, { pos.x + 1, pos.y }, basin_pos);
    if (pos.y - 1 >= 0 && height_map[pos.x][pos.y - 1] != '9' && !find_if_pos_is_in_basin_pos(pos, b, basin_pos))
        get_basin_from_pos(height_map, { pos.x, pos.y - 1 }, basin_pos);
    if (pos.x - 1 >= 0 && height_map[pos.x - 1][pos.y] != '9' && !find_if_pos_is_in_basin_pos(pos, d, basin_pos))
        get_basin_from_pos(height_map, { pos.x - 1, pos.y }, basin_pos);
}

void get_low_points_pos(
    const std::vector<std::string> &height_map,
    std::vector<Vect2> &low_points_pos
) {
    size_t i_size = height_map.size();
    size_t j_size = height_map[0].size();

    for (int i = 0; i < i_size; i++) {
        for (int j = 0; j < j_size; j++) {
            char pos = height_map[i][j];
            char a = (j + 1 < j_size) ? height_map[i][j + 1] : '9' + 1;
            char c = (i + 1 < i_size) ? height_map[i + 1][j] : '9' + 1;
            char b = (j - 1 >= 0) ? height_map[i][j - 1] : '9' + 1;
            char d = (i - 1 >= 0) ? height_map[i - 1][j] : '9' + 1;

            if (pos < a && pos < b && pos < c && pos < d) {
                low_points_pos.push_back({ i, j });
            }
        }
    }
}

int main(int ac, char **av)
{
    std::string line;
    std::ifstream myfile(av[1]);

    std::vector<std::string> height_map;
    std::vector<Vect2> low_points_pos;
    std::vector<size_t> basin_size;

    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
            height_map.push_back(line);
        }

        myfile.close();
    }

    get_low_points_pos(height_map, low_points_pos);

    for (Vect2 &low_point : low_points_pos) {
        std::vector<Vect2> basin_pos;
        get_basin_from_pos(height_map, low_point, basin_pos);
        basin_size.push_back(basin_pos.size());
    }

    std::sort(basin_size.begin(), basin_size.end(), std::greater<size_t>());
    std::cout << basin_size[0] * basin_size[1] * basin_size[2] << std::endl;

    return 0;
}