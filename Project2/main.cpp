//
//  main.cpp
//  Project2
//
//  Created by David Li on 1/25/17.
//  Copyright © 2017 cs32. All rights reserved.
//

#include <iostream>
#include <cassert>
#include "Sequence.h"

using namespace std;

int main() {
    
    Sequence test;
    test.insert(5);
    test.insert(6);
    test.insert(3);
    test.insert(4);
    test.insert(9);
    test.insert(9001);
    
    assert(test.find(3) == 0 && test.find(9001) == test.size()-1); //making sure values are inputed in ascending order.
    Sequence hi(test);
    assert(hi.find(3) == 0 && test.find(9001) == test.size() - 1); // Ensures the copy constructor works properly.
    
    Sequence a;
    Sequence b;
    Sequence c;
    
    c.insert(c.size(), 10);    //test insert function with last position
    c.insert(c.size(), 20);
    assert(c.find(20) == 1);    // checks to see if find is input in the correct location
    assert(!c.insert(5, 100));   // makes sure that we cant insert something into position greater than the size
    assert(!c.erase(3));    // makes sure we cant erase something at position that is greater than the size
    assert(c.erase(1));     // test erase function
    assert(c.size() == 1);
    unsigned long item = 33;
    assert(c.get(0, item) && item == 10);   // tests to make sure that at position 0 we have 21 and x will get that value
    unsigned long item2 = 9090;
    assert(c.set(0, item2) && c.find(9090) == 0);    // replaces 10 with 9090 at position 0 and makes sure its located there using find
    
    
    assert(a.empty()); // check to see if s set is empty
    assert(b.empty()); // check to see if a set is empty
    
    
    for (int i = 0; i < 100; i++)
    {
        a.insert(i);        // Insert 100 items in s
    }
    
    assert(a.size() == 100);    // Check to see if a size is 100
    a.swap(b);                  // Test swap function
    assert(b.size() == 100);    // Check to see if the size is 100
    
    for (int k = 0; k < 50; k++)
    {
        b.erase(0);    //remove the first 50 numbers
    }
    assert(b.size() == 50);    // Checks if size is now 50
    
    
    
    Sequence seq1;
    seq1.insert(0,0);  // The following inserts test if the data is correctly inserted in the sequence
    seq1.insert(1,10);
    seq1.insert(2,20);
    seq1.insert(3,30);
    seq1.insert(4,40);
    seq1.insert(5,50);
    seq1.insert(6,60);
    seq1.insert(7,70);
    seq1.insert(8,80);
    seq1.insert(9,90);
    
    
    Sequence seq2;
    seq2.insert(0, 111);
    seq2.insert(1, 222);
    seq2.insert(2, 333);

    
    assert(subsequence(seq1, seq2)==-1);    // tests that seq2 is not a subsequence of seq2
    seq2 = seq1;                            // Tests that the assignment operator works, which in turn means the copy constructor works since it is implemented using the copy swap method
    
    assert(subsequence(seq1, seq2) == 0);   // now that seq1 and seq2 are the same, they are a subsequence of each other starting at 0
    assert(subsequence(seq1, seq1) == 0);   // Checks that subsequence works for aliasing.
    assert(seq2.size() == seq1.size());
    assert(seq2.find(30) == 3 && seq2.find(70) == 7);
    
    Sequence seq3;
    Sequence seq4;
    Sequence result;
    for (int p = 0; p < 55; p++)    // insert 0-54 into result in positions 0-54
    {
        result.insert(p, p);
    }
    ItemType arr1[6] = {1, 3, 5, 7, 9, 11};
    ItemType arr2[4] = {2,4,6,8};
    for (int j = 0; j < 6; j++)
        seq3.insert(j, arr1[j]);
    for (int k = 0; k < 4; k++)
        seq4.insert(k, arr2[k]);
    
    interleave(seq3, seq4, result); // Interleave test
    assert(result.find(1) == 0 && result.find(8) == 7); // Makes sure that the values inputted correctly
    interleave(seq3, seq2, result); // Interleave test
    
    assert(result.find(0) == 1 && result.find(9) == 8);  // Makes sure that the values inputted correctly.
    
    interleave(seq1, seq1, seq1); // Tests for aliasing
    
    assert(result.size() == 16);

    
    cout << "Passed all tests" << endl;

    return 0;
}
