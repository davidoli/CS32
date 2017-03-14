//
//  History.hpp
//  Project1
//
//  Created by David Li on 1/9/17.
//  Copyright © 2017 cs32. All rights reserved.
//

#ifndef History_hpp
#define History_hpp

#include <stdio.h>
#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_row;
    int m_col;
    char m_grid[MAXROWS][MAXCOLS];          //use . for 0, A-Z for 1-26+
};


#endif /* History_hpp */
