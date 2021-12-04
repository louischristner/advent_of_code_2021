#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

struct BingoNumber {
    size_t value;
    bool checked;

    BingoNumber(size_t v): value(v), checked(false) {}
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

int check_horizontal_lines(const std::vector<std::vector<BingoNumber>> &board)
{
    for (size_t index = 0; index < board.size(); index++) {
        bool isCheckedLine = true;
        for (size_t jndex = 0; jndex < board[index].size(); jndex++) {
            if (board[index][jndex].checked == false)
                isCheckedLine = false;
        }

        if (isCheckedLine) {
            return index;
        }
    }

    return -1;
}

int check_vertical_lines(const std::vector<std::vector<BingoNumber>> &board)
{
    for (size_t index = 0; index < board[0].size(); index++) {
        bool isCheckedLine = true;
        for (size_t jndex = 0; jndex < board.size(); jndex++) {
            if (board[jndex][index].checked == false)
                isCheckedLine = false;
        }

        if (isCheckedLine) {
            return index;
        }
    }

    return -1;
}

bool check_if_board_win(std::vector<std::vector<BingoNumber>> &board, const size_t &number)
{
    for (size_t index = 0; index < board.size(); index++) {
        for (size_t jndex = 0; jndex < board[index].size(); jndex++) {
            if (board[index][jndex].value == number)
                board[index][jndex].checked = true;
        }
    }

    int vertical = check_vertical_lines(board);
    int horizontal = check_horizontal_lines(board);

    return (vertical >= 0 || horizontal >= 0);
}

size_t get_board_unchecked_sum(const std::vector<std::vector<BingoNumber>> &board)
{
    size_t result = 0;

    for (size_t index = 0; index < board.size(); index++) {
        for (size_t jndex = 0; jndex < board[index].size(); jndex++) {
            if (board[index][jndex].checked == false)
                result += board[index][jndex].value;
        }
    }

    return result;
}

int main(int ac, char **av)
{
    std::string line;
    std::ifstream myfile(av[1]);

    int board_index = -1;
    std::vector<size_t> numbers;
    std::vector<std::vector<std::vector<BingoNumber>>> boards;

    if (myfile.is_open()) {
        for (size_t index = 0; std::getline(myfile, line); index++) {
            if (index == 0) {
                std::vector<std::string> str_numbers = string_split(line, ",");

                for (std::string str_number : str_numbers)
                    numbers.push_back(std::stoll(str_number));
            } else if (line == "") {
                board_index += 1;
                boards.push_back(std::vector<std::vector<BingoNumber>>());
            } else {
                std::vector<std::string> str_numbers = string_split(line, " ");

                boards[board_index].push_back(std::vector<BingoNumber>());
                for (std::string str_number : str_numbers) {
                    if (str_number != "") {
                        boards[board_index][boards[board_index].size() - 1].push_back(BingoNumber(std::stoll(str_number)));
                    }
                }
            }
        }

        myfile.close();
    }

    for (size_t number : numbers) {
        for (auto board_ptr = boards.begin(); board_ptr != boards.end(); board_ptr++) {
            if (check_if_board_win((*board_ptr), number)) {
                std::cout << get_board_unchecked_sum((*board_ptr)) * number << std::endl;
                return 0;
            }
        }
    }

    return 0;
}