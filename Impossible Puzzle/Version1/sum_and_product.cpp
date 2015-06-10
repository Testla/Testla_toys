#include <iostream>
#include <utility>
#include <vector>
#include <functional>
#include "PQ_problem_solver.h"

int plus(const pair<int, int> &x) {
    return x.first + x.second;
}

int multiplies(const pair<int, int> &x) {
    return x.first * x.second;
}

int main(void) {
    std::vector<std::pair<int, int> > solution_space;
    vector<line_identifier_t (*)(const solution_t&)> get_line_indetifiers;
    int a, b;
    for (b = 2; b <= 99; ++b)
        for (a = b; a <= 99; ++a)
            solution_space.push_back(std::make_pair(a, b));
    get_line_indetifiers.push_back(plus);
    get_line_indetifiers.push_back(multiplies);
    PQ_problem_solver solver(solution_space, get_line_indetifiers);
    solver.X_knows_that_Y(0, 1, false);
    solver.X(0, false);
    solver.X(1, true);
    solver.X(0, true);
    solver.print_all_remaining_solution();
    return 0;
}

