//
//  History.cpp
//  Project1
//
//  Created by David Li on 1/9/17.
//  Copyright © 2017 cs32. All rights reserved.
//

#include "History.h"
#include "globals.h"

#include <iostream>
#include <cstdlib>

using namespace std;


History::History(int nRows, int nCols){
    
    m_row = nRows;
    m_col = nCols;
    
    for(int r = 1; r <= nRows; r++){
        for(int c = 1; c <= nCols; c++){
            m_grid[r - 1][c - 1] = '.';
        }
    }
}
bool History::record(int r, int c){
    
    if(r > m_row || c > m_col || r <= 0 || c <= 0)
        return false;
    
    else {
        if(m_grid[r - 1][c - 1]=='.')
            m_grid[r - 1][c - 1] = 'A';
        
        else if (m_grid[r - 1][c - 1] >= 'A' && m_grid[r - 1][c - 1] <= 'Z')
            m_grid[r - 1][c - 1]+=1;
        
        return true;
    }
}
void History::display() const{
    clearScreen();
    
    for(int r = 1; r <= m_row; r++){
        for(int c = 1; c <= m_col; c++)
            cout << m_grid[r - 1][c - 1];
        cout << endl;
    }
    cout << endl;
}
