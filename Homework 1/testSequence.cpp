//
//  main.cpp
//  Homework 1
//
//  Created by David Li on 1/19/17.
//  Copyright © 2017 cs32. All rights reserved.
//
/*
#include "Sequence.h"
#include <iostream>
#include <cassert>
#include <stdio.h>

using namespace std;

int main()
{
    Sequence s;
    assert(s.empty());
    assert(s.find(2) == -1);
    s.insert(1);                                        // 0
    assert(s.size() == 1  &&  s.find(5) == -1);
    
    s.insert(1, 2);                                        //1
    s.insert(2, 3);                                        //2
    s.insert(3,4);                                           //3
    s.insert(4,5);                                            //4
    
    for(int i = 0; i < s.size(); i++){
        unsigned long x = 0;
        s.get(i, x);
        cout << "position " << i << " " << x << endl;
    }
    cout << "insert 10 at position 2." << endl;
    
    s.insert(2,10);                                           //5
    
    for(int i = 0; i < s.size(); i++){
        unsigned long x = 0;
        s.get(i, x);
        cout << "position " << i << " " << x << endl;
    }
    cout << endl;
    cout << "after erasing..." << endl;
    s.erase(1);
    for(int i = 0; i < s.size(); i++){
        unsigned long x = 0;
        s.get(i, x);
        cout << "position " << i << " " << x << endl;
    }
    
    cout << "Passed all tests" << endl;
}
*/
