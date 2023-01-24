enum Action {
    Lift, Drop
};

struct Change {
    Action action;
    String location;

    String toString() {
        return (action == Lift ? "lift " : "drop ") + location;
    }
};

class Board {
private:
    bool board[64];
public:
    bool difference(const Board& other, Change& change) const {
        for (size_t i = 0; i < 8 * 8; i++) {
            if (board[i] != other[i]) {
                int x = i / 8;
                int y = i % 8;
                String uci = String('a' + x) + String('1' + y);
                change = Change {other[i] ? Lift : Drop, uci};
                return true;
            }
        }
        return false;
    }

    bool operator[] (size_t index) const {
        return board[index];
    }

    void setTile(int x, int y, bool value) {
        board[x * 8 + y] = value;
    }
};
