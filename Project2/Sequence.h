//
//  Sequence.h
//  Project2
//
//  Created by David Li on 1/25/17.
//  Copyright © 2017 cs32. All rights reserved.
//

#ifndef Sequence_h
#define Sequence_h

#include <stdio.h>
#include <string>

typedef unsigned long ItemType;

class Sequence
{
public:
    Sequence();                //create empty sequence
    
    Sequence(const Sequence& other);           // copy constructor
    
    ~Sequence();                        //destructor for sequence
    
    Sequence& operator=(const Sequence &src);         //assignment operator
    
    bool empty() const;
    
    int size() const;
    
    bool insert(int pos, const ItemType& value);
    
    int insert(const ItemType& value);
    
    bool erase(int pos);
    
    int remove(const ItemType& value);
    
    bool get(int pos, ItemType& value) const;
    
    bool set(int pos, const ItemType& value);
    
    int find(const ItemType& value) const;
    
    void swap(Sequence& other);
    
    void dump() const;
    

private:

    struct Node{
    
        ItemType value;
        Node* next;
        Node* prev;
    
    };
    int list_size;
    Node* head;
    Node* tail;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif /* Sequence_hpp */
