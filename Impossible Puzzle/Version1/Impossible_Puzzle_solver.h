/* include guard */
#ifndef IMPOSSIBLE_PUZZLE_SOLVER_H
#define IMPOSSIBLE_PUZZLE_SOLVER_H

#include <set>
#include <map>
#include <utility>
#include <vector>

using std::set;
using std::pair;
using std::map;
using std::vector;

/* may be template parameter*/
typedef pair<int, int> solution_t;
typedef set<solution_t> line_t;
/* in fact, different perspective may have different type
 * for line identifier, but I'm too lazy to implement it...
 * (at least not this version) */
/* may be template parameter */
typedef int line_identifier_t;
struct perspective_t {
    map<line_identifier_t, line_t> lines;
    line_identifier_t (*get_line_identifier)(const solution_t&);
    perspective_t(line_identifier_t (*get_line_indetifier_)(const solution_t&)) : get_line_identifier(get_line_indetifier_) {}
};

class Impossible_Puzzle_solver {

private:
    vector<perspective_t> perspectives;
    set<solution_t> all_solutions;

public:
    explicit Impossible_Puzzle_solver(
        const vector<solution_t>& solution_space,
        const vector<line_identifier_t (*)(const solution_t&)> &get_line_indetifier_
    );
    void print_all_remaining_solution();
    void X(int x, bool knows);
    void X_knows_that_Y(int x, int y, bool knows);
    void show_perspective(int x);
    void show_perspective(int x, bool knows);
};

#endif  /* Impossible_Puzzle_SOLVER_H */

