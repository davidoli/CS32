//
//  testNewSequence.cpp
//  Homework 1
//
//  Created by David Li on 1/20/17.
//  Copyright © 2017 cs32. All rights reserved.
//

#include <stdio.h>
#include "newSequence.h"
#include <iostream>
#include <cassert>

using namespace std;

int main(){
    
   /* Sequence a(1000);   // a can hold at most 1000 items
    Sequence b(5);      // b can hold at most 5 items
    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
    ItemType v = 100;
    
    // No failures inserting 5 items into b
    for (int k = 0; k < 5; k++)
        assert(b.insert(k, v));
    
    for (int i = 0; i < b.size(); i++){
        unsigned long x = 0;
        b.get(i, x);
        cout << "position " << i << ": " << x << endl;
    }
    
    // Failure if we try to insert a sixth item into b
    assert(!b.insert(5, v));
    
    // When two Sequences' contents are swapped, their capacities are
    // swapped as well:
    a.swap(b);
    assert(!a.insert(5, v));
    for (int k = 0; k < 1000; k++)
        assert(b.insert(k, v));
    
    cout << "All tests succeeded." << endl;
    */
    
    Sequence c;
    
    c.insert(0);
    c.insert(1);
    c.insert(2);
    c.insert(3);
    c.insert(4, 4);
    
    for(int i = 0; i<c.size(); i++){
        ItemType x;
        c.get(i, x);
        cout << "position " << i << ": " << x << " size is now " << i + 1 << endl;
    }
    
    return 0;
}
