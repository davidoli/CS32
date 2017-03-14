//
//  Game.hpp
//  Project1
//
//  Created by David Li on 1/9/17.
//  Copyright © 2017 cs32. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp
#include <string>
#include <stdio.h>

class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRats);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
    
    // Helper functions
    std::string takePlayerTurn();
};


#endif /* Game_hpp */
