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
            if (other[i] != board[i]) {
                //Serial.print(other[i]);
                //Serial.print(", ");
                //Serial.println(board[i]);
                char x = (char) (i / 8);
                char y = (char) (i % 8);
                char c1 = 'a' + x;
                char c2 = '1' + y;
                String str1 = String(c1);
                String str2 = String(c2);
                String str3 = str1 + str2;

                Action action = other[i] ? Lift : Drop;
                change = Change {action, str3};
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
