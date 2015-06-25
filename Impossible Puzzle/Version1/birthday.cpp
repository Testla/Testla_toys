#include <iostream>
#include <utility>
#include <vector>
#include <functional>
#include "Impossible_Puzzle_solver.h"

int month(const pair<int, int> &x) {
    return x.first;
}

int date(const pair<int, int> &x) {
    return x.second;
}

int main(void) {
    std::vector<std::pair<int, int> > solution_space;
    vector<line_identifier_t (*)(const solution_t&)> get_line_indetifiers;
    int candidates[][2] = {
        {5, 15}, {5, 16}, {5, 19},
        {6, 17}, {6, 18},
        {7, 14}, {7, 16},
        {8, 14}, {8, 15}, {8, 17}
    };
    for (int i = 0; i < sizeof(candidates) / (2 * sizeof(int)); ++i)
        solution_space.push_back(std::make_pair(candidates[i][0], candidates[i][1]));
    get_line_indetifiers.push_back(month);
    get_line_indetifiers.push_back(date);
    Impossible_Puzzle_solver solver(solution_space, get_line_indetifiers);
    solver.X(0, false);
    solver.X_knows_that_Y(0, 1, false);
    solver.X(1, true);
    solver.X(0, true);
    solver.print_all_remaining_solution();
    return 0;
}

