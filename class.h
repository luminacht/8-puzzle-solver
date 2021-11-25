#define n 3
using namespace std;

extern int Goal[n][n];
extern bool search;

class State {
public:
    int A[n][n], g, h, total_cost;
    State *parent;
    int moves;

    State();
    bool is_goal();
    bool operator==(const State &) const;
    bool operator<(const State &) const;
    void manhattanHeuristic();
};

State::State() {
    g = h = total_cost = 0;
    parent = NULL;
}

void State::manhattanHeuristic() {
    int h_val = 0;
    bool found;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            found = false;
            for (int i2 = 0; i2 < n; i2++) {
                for (int j2 = 0; j2 < n; j2++) {

                    if (Goal[i][j] == A[i2][j2]) {
                        //dx + dy
                        h_val += abs(i - i2) + abs(j - j2);
                        found = true;
                    }
                    if (found)
                        break;
                }
                if (found)
                    break;
            }
        }
    }
    h = h_val;
}

bool State::is_goal() {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // if any two items not equal - not goal
            if (A[i][j] != Goal[i][j])
                return false;
        }
    }
    //reaching this point means all items are equal - goal state found
    return true;
}

bool State::operator==(const State &r) const {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            //if any two items not equal - not goal
            if (A[i][j] != r.A[i][j])
                return false;
        }
    }
    // states are equal
    return true;
}

bool State::operator<(const State &r) const {

    if (search) { // for heuristic based algorithms
        return total_cost < r.total_cost;
    }
    else {
        return g < r.g; // for normal search algorithms
    }
}

list< State > closed_list, active_list;
State start_state, current_state, temp_state, goal_state;