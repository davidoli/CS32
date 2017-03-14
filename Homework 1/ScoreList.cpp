//
//  ScoreList.cpp
//  Homework 1
//
//  Created by David Li on 1/19/17.
//  Copyright © 2017 cs32. All rights reserved.
//

#include "ScoreList.h"

ScoreList::ScoreList():seq(){                         // Create an empty score list.
        
}
bool ScoreList::add(unsigned long score){
    if (score <= 100 && seq.size()<DEFAULT_MAX_ITEMS){
        seq.insert(score);
        return true;
    }
    
    return false;
}
bool ScoreList::remove(unsigned long score){
    if(seq.find(score)!=-1){
        seq.erase(seq.find(score));
        return true;
    }
    return false;
}

int ScoreList::size() const{
    
    return seq.size();
    
}
unsigned long ScoreList::minimum() const{
    if(seq.size() == 0)
        return NO_SCORE;
    
    unsigned long lowest = 0;
    unsigned long x = 0;
    seq.get(0, x);
    
    for(int i = 0; i < seq.size(); i++){
        unsigned long y = 0;
        seq.get(i, y);
        if(x <= y)
            lowest = x;
        else
            lowest = y;
    }
    return lowest;
}
    // Return the lowest score in the score list.  If the list is
    // empty, return NO_SCORE.
    
unsigned long ScoreList::maximum() const{
    if(seq.size() == 0)
        return NO_SCORE;
    
    unsigned long max = 0;
    unsigned long x = 0;
    seq.get(0, x);
    
    for(int i = 0; i < seq.size(); i++){
        unsigned long y = 0;
        seq.get(i, y);
        if(x >= y)
            max = x;
        else
            max = y;
    }
    
    return max;
}
    // Return the highest score in the score list.  If the list is
    // empty, return NO_SCORE.
    
