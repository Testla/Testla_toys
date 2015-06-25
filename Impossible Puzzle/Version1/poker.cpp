#include <iostream>
#include <utility>
#include <vector>
#include <functional>
#include "Impossible_Puzzle_solver.h"

enum Suit {
    DIAMOND,
    CLUBS,
    HEART,
    SPADE
};

int get_suit(const solution_t &solution) {
    return solution.first;
}

int get_points(const solution_t &solution) {
    return solution.second;
}

int main(void) {
    std::vector<std::pair<int, int> > solution_space;
    vector<line_identifier_t (*)(const solution_t&)> get_line_indetifiers;
    int candidates[][2] = {
        {HEART, 1}, {HEART, 12}, {HEART, 4},
        {SPADE, 11}, {SPADE, 8}, {SPADE, 4}, {SPADE, 2}, {SPADE, 7}, {SPADE, 3},
        {CLUBS, 13}, {CLUBS, 12}, {CLUBS, 5}, {CLUBS, 4}, {CLUBS, 6}, 
        {DIAMOND, 1}, {DIAMOND, 5}
    };
    for (int i = 0; i < sizeof(candidates) / (2 * sizeof(int)); ++i)
        solution_space.push_back(std::make_pair(candidates[i][0], candidates[i][1]));
    get_line_indetifiers.push_back(get_suit);
    get_line_indetifiers.push_back(get_points);
    Impossible_Puzzle_solver solver(solution_space, get_line_indetifiers);
    solver.X_knows_that_Y(0, 1, false);
    solver.X(1, true);
    solver.X(0, true);
    solver.print_all_remaining_solution();
    return 0;
}

