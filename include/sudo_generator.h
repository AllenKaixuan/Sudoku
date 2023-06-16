#include "command.h"
class SudoGenerator
{

public:
    SudoGenerator();
    ~SudoGenerator();
    void generate_end_map(const Command& command);
    void generate_sudo_game(const Command& command);
    
};

