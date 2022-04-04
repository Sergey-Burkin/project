#include "string"
class Player_data {
private:
    std::string nick_name;
    int score = 0;
public:
    void set_nick_name(const std::string& new_nick);
    std::string get_nick_name();
    int get_score();
    void add_score(int value);
};
