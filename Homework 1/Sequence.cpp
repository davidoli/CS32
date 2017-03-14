//
//  Sequence.cpp
//  Homework 1
//
//  Created by David Li on 1/19/17.
//  Copyright © 2017 cs32. All rights reserved.
//
/*
#include "Sequence.h"

Sequence::Sequence():seq_size(0){
}

bool Sequence::empty() const{
    if (seq_size > 0)
        return false;
    else
        return true;
}

int Sequence::size() const{
    return seq_size;
}

bool Sequence::insert(int pos, const ItemType& value){
    if(0 <= pos && pos <=size()){
        
        if (size() > DEFAULT_MAX_ITEMS){
            return false;
        }
        if (pos == size()){
            seq_size++;
            seq[pos] = value;
            return true;
        }
        seq_size++;
        for (int i = size()-1; i > pos; i--){
            seq[i] = seq[i-1];
        }
        seq[pos] = value;
        return true;
    }
    
    return false;
}
int Sequence::insert(const ItemType& value){
    
    int p = 0;
    
    for(int i = 0; i < size(); i++){
      
        if (seq[i] >= value){
            p = i;
            break;
        }
        else
            p = size();
    }
    if(0 <= p && p <=size()){              //essentially just taking the portion from the previous insert function
        seq_size++;
        if (size() > DEFAULT_MAX_ITEMS){
            return -1;
        }
        if (p == size()){
            seq[p - 1] = value;
        }
        
        for (int i = size()-1; i >= p; i--){
            seq[i] = seq[i-1];
        }
        
        seq[p] = value;
        return p;
    }
    return -1;
}

bool Sequence::erase(int pos){
    if (pos >= 0 && pos < size()){
        
        for(int i = pos; i < size(); i++)
            seq[i] = seq[i+1];
        
        seq_size--;
        
        return true;
    }
    
    else
        return false;
    
}
int Sequence::remove(const ItemType& value){
    
    int count = 0;
    
    for(int i = 0; i < size(); i++){
        if (seq[i] == value){
            for(int j = i; j < size(); j++)
                seq[j] = seq[j+1];
            seq_size--;
            count++;
        }
    }
    return count;
}

bool Sequence::get(int pos, ItemType& value) const{
    
    if (pos >= 0 && pos < size()){
        value = seq[pos];
        return true;
    }
    return false;
}

bool Sequence::set(int pos, const ItemType& value){
    
    if (pos >= 0 && pos < size()){
        seq[pos] = value;
        return true;
    }
    return false;
}

int Sequence::find(const ItemType& value) const{
    int p = -1;
    for(int i = 0; i < size(); i++){
        if(seq[i] == value){
            p = i;
            return p;
        }
    }
    return p;
}

void Sequence::swap(Sequence& other){
    
    int temp_size = seq_size;                       //to switch, we need three array sequences.  And temp variables.
    seq_size = other.seq_size;
    other.seq_size = temp_size;
    
    ItemType temp_seq[DEFAULT_MAX_ITEMS];
    
    for(int i = 0; i < DEFAULT_MAX_ITEMS; i++){
        temp_seq[i] = seq[i];
        seq[i] = other.seq[i];
        other.seq[i] = temp_seq[i];
    }
}
*/
