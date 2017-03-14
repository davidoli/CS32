//
//  mazestack.cpp
//  Homework 2
//
//  Created by David Li on 2/2/17.
//  Copyright © 2017 cs32. All rights reserved.
//

#include <cassert>
#include <iostream>
#include <string>
#include <stack>

using namespace std;


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise



/////////////////////////////////////////////////////////////////////////////////////////
class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const
    { return m_r; }
    int c() const
    { return m_c; }
private:
    int m_r;
    int m_c;
};
/////////////////////////////////////////////////////////////////////////////////////////


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    stack<Coord> coords;
    Coord start = Coord(sr, sc);
    coords.push(start);
    
    maze[sr][sc]='*';
    
    while(!coords.empty()){
        start = coords.top();
        int row = start.r();
        int col = start.c();
        coords.pop();
        
        if(row == er && col == ec)
            return true;
        if(row != 0 && maze[row - 1][col] != 'X' && maze[row - 1][col] != '*'){        //Check north
            Coord move(row - 1, col);
            coords.push(move);                //move north
            maze[row - 1][col] = '*';          //mark as visited.
        }
        if(col != nCols-1 && maze[row][col + 1] != 'X' && maze[row][col + 1] != '*'){   //Check east
            Coord move(row, col + 1);
            coords.push(move);                   //move east
            maze[row][col] = '*';           //mark as visited
        }
        if(row != nRows && maze[row + 1][col] != 'X' && maze[row + 1][col] != '*'){        //Check south
            Coord move(row + 1, col);
            coords.push(move);                //move north
            maze[row + 1][col] = '*';          //mark as visited.
        }
        if(col != 0 && maze[row][col - 1] != 'X' && maze[row][col - 1] != '*'){   //Check west
            Coord move(row, col - 1);
            coords.push(move);                   //move east
            maze[row - 1][col] = '*';           //mark as visited
        }
    }
    return false;
}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X........X",
        "XX.X.XXXXX",
        "X..X.X...X",
        "X..X...X.X",
        "XXXX.XXX.X",
        "X.X....XXX",
        "X..XX.XX.X",
        "X...X....X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 6,4, 1,1))
        cout << "Solvable with stack!" << endl;
    else
        cout << "Out of luck!" << endl;
}
