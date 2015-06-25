#include <iostream>
#include "Impossible_Puzzle_solver.h"

Impossible_Puzzle_solver::Impossible_Puzzle_solver(
    const vector<solution_t> &solution_space,
    const vector<line_identifier_t (*)(const solution_t&)> &get_line_indetifiers
) {
    /* add perspectives */
    vector<line_identifier_t (*)(const solution_t&)>::const_iterator get_line_indetifier;
    for (get_line_indetifier = get_line_indetifiers.begin();
    get_line_indetifier != get_line_indetifiers.end(); ++get_line_indetifier)
        perspectives.push_back(perspective_t(*get_line_indetifier));
    /* add entire solution_space */
    vector<solution_t>::const_iterator new_solution;
    for (new_solution = solution_space.begin();
    new_solution != solution_space.end(); ++new_solution) {
        all_solutions.insert(*new_solution);
        for (vector<perspective_t>::iterator perspective = perspectives.begin();
        perspective != perspectives.end(); ++perspective)
            perspective->lines[perspective->get_line_identifier(*new_solution)].insert(*new_solution);
    }
}

void Impossible_Puzzle_solver::print_all_remaining_solution() {
    for (set<solution_t>::iterator solution = all_solutions.begin(); solution != all_solutions.end(); ++solution)
        std::cout << solution->first << ", " << solution->second << std::endl;
}

void Impossible_Puzzle_solver::X(int x, bool knows) {
    map<line_identifier_t, line_t>::iterator line_it;
    line_t::iterator solution;
    /* delete mustn't be done immediately */
    vector<map<line_identifier_t, line_t>::iterator> lines_to_delete;
    vector<map<line_identifier_t, line_t>::iterator>::iterator line_to_delete;
    for (line_it = perspectives[x].lines.begin(); line_it != perspectives[x].lines.end(); ++line_it)
        if (!(knows ? (line_it->second.size() == 1) : (line_it->second.size() != 1)))
            lines_to_delete.push_back(line_it);
    for (line_to_delete = lines_to_delete.begin();
    line_to_delete != lines_to_delete.end(); ++line_to_delete) {
        for (solution = (*line_to_delete)->second.begin(); solution != (*line_to_delete)->second.end(); ++solution) {
            all_solutions.erase(*solution);
            for (int perspective = 0; perspective < perspectives.size(); ++perspective)
                if (perspective != x) {
                    line_identifier_t line_id = perspectives[perspective].get_line_identifier(*solution);
                    perspectives[perspective].lines[line_id].erase(*solution);
                    if (perspectives[perspective].lines[line_id].empty())
                        perspectives[perspective].lines.erase(line_id);
                }
        }
        perspectives[x].lines.erase(*line_to_delete);
    }
}

/* all solutions in X's line is single line in Y */
void Impossible_Puzzle_solver::X_knows_that_Y(int x, int y, bool knows) {
    perspective_t &target_perspective = perspectives[y];
    map<line_identifier_t, line_t>::iterator line_it;
    line_t::iterator solution;
    /* delete mustn't be done immediately */
    vector<map<line_identifier_t, line_t>::iterator> lines_to_delete;
    vector<map<line_identifier_t, line_t>::iterator>::iterator line_to_delete;
    for (line_it = perspectives[x].lines.begin(); line_it != perspectives[x].lines.end(); ++line_it)
        for (solution = line_it->second.begin(); solution != line_it->second.end(); ++solution) {
            int size = target_perspective.lines[target_perspective.get_line_identifier(*solution)].size();
            if (!(knows ? (size == 1) : (size != 1))) {
                lines_to_delete.push_back(line_it);
                break;
            }
        }
    for (line_to_delete = lines_to_delete.begin();
    line_to_delete != lines_to_delete.end(); ++line_to_delete) {
        for (solution = (*line_to_delete)->second.begin(); solution != (*line_to_delete)->second.end(); ++solution) {
            all_solutions.erase(*solution);
            for (int perspective = 0; perspective < perspectives.size(); ++perspective)
                if (perspective != x) {
                    line_identifier_t line_id = perspectives[perspective].get_line_identifier(*solution);
                    perspectives[perspective].lines[line_id].erase(*solution);
                    if (perspectives[perspective].lines[line_id].empty())
                        perspectives[perspective].lines.erase(line_id);
                }
        }
        perspectives[x].lines.erase(*line_to_delete);
    }
}

void Impossible_Puzzle_solver::show_perspective(int x) {
    map<line_identifier_t, line_t>::iterator line_it;
    line_t::iterator solution;
    for (line_it = perspectives[x].lines.begin(); line_it != perspectives[x].lines.end(); ++line_it) {
        std::cout << "** " << line_it->first << ": ";
        for (solution = line_it->second.begin(); solution != line_it->second.end(); ++solution)
            std::cout << "(" << solution->first << ", " << solution->second << ") ";
        std::cout << std::endl;
    }
}

void Impossible_Puzzle_solver::show_perspective(int x, bool knows) {
    map<line_identifier_t, line_t>::iterator line_it;
    line_t::iterator solution;
    for (line_it = perspectives[x].lines.begin(); line_it != perspectives[x].lines.end(); ++line_it) {
        int size = line_it->second.size();
        if (knows ? (size == 1) : (size != 1)) {
            std::cout << "** " << line_it->first << ": ";
            for (solution = line_it->second.begin(); solution != line_it->second.end(); ++solution)
                std::cout << "(" << solution->first << ", " << solution->second << ") ";
            std::cout << std::endl;
        }
    }
}
