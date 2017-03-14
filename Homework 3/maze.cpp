//
//  maze.cpp
//  Homework 3
//
//  Created by David Li on 2/10/17.
//  Copyright © 2017 cs32. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>

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
    
    if(sr == er && sc == ec)
        return true;
    
    maze[sr][sc]='*';
    //cout << "north of (" << sr-1 << ", "<< sc << "): "<< maze[sr-1][sc] << " " << "east of (" << sr << ", "<< sc+1 << "): " << maze[sr][sc+1] << " " <<"south of (" << sr+1 << ", "<< sc << "): "<< maze[sr+1][sc] << " " <<"west of (" << sr << ", "<< sc-1 << "): "<< maze[sr][sc-1] << endl;
    
    if(sr != 0 && maze[sr-1][sc] == '.'){                                 //north
        if(sr != 0 && pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
            return true;
    }
    
    if(sc != nCols-1 && maze[sr][sc+1] == '.'){                         //east
        if(pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
            return true;
    }
    
    if(sr != nRows && maze[sr+1][sc] == '.'){                            //south
        if(pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
            return true;
    }
    
    if(sc != 0 && maze[sr][sc-1] == '.'){                              //west
        if(pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
            return true;
    }
    
    return false;
}
/*
#include <cassert>

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",   //0
        "X........X",   //1
        "XX.X.XXXXX",   //2
        "X..X.X...X",   //3
        "X..X...X.X",   //4
        "XXXX.XXX.X",   //5
        "X.X....XXX",   //6
        "X..XX.XX.X",   //7
        "X...X....X",   //8
        "XXXXXXXXXX"    //9
    }; //0123456789
    
    if (pathExists(maze, 10,10, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
    
    string maze1[10] = {
        "XXXXXXXXXX'",
        "X.X..X...X'",
        "X.XX.X.XXX'",
        "X....X.X.X'",
        "XX.X.X...X'",
        "XXX..X.X.X'",
        "X...X...XX'",
        "X.XX..X.XX'",
        "X....X...X'",
        "XXXXXXXXXX'",
    };
    
    string maze2[10] = {
        "XXXXXXXXXX'",
        "X.X..X...X'",
        "XXXX.X.XXX'",
        "X....X.X.X'",
        "XX.X.X...X'",
        "XXX..X.X.X'",
        "X...X...XX'",
        "X.XX..X.XX'",
        "X....X...X'",
        "XXXXXXXXXX'",
    };
    
    string maze3[10] = {
        "XXXXXXXXXX'",
        "XX.....XXX'",
        "X..XX....X'",
        "X...X...XX'",
        "X.X.XXX..X'",
        "XXXX..X..X'",
        "XX....X..X'",
        "X.......XX'",
        "X..XXXXXXX'",
        "XXXXXXXXXX'",
    };
    
    string maze4[10] = {
        "XXXXXXXXXX'",
        "XX.....XXX'",
        "X..XX....X'",
        "X...X...XX'",
        "X.X.XXX..X'",
        "XXXX..X..X'",
        "XX....X..X'",
        "X.X.....XX'",
        "X..XXXXXXX'",
        "XXXXXXXXXX'",
    };
    
    assert(pathExists(maze1, 10, 10, 8, 6, 1, 1));
    assert(!pathExists(maze2, 10, 0, 8, 6, 1, 1));
    assert(pathExists(maze3, 10, 10, 4, 3, 7, 1));
    assert(!pathExists(maze4, 10, 10, 4, 3, 7, 1));
    
    cout << "Boom" << endl;
    
}*/
