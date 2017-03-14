//
//  Sequence.cpp
//  Project2
//
//  Created by David Li on 1/25/17.
//  Copyright © 2017 cs32. All rights reserved.
//

#include "Sequence.h"
#include <iostream>

Sequence::Sequence():list_size(0){
    head = nullptr;
    tail = nullptr;
}


Sequence::Sequence(const Sequence& other){                            // copy constructor
    list_size = 0;
    for(int i = 0; i<other.size(); i++){
        ItemType x;
        other.get(i, x);
        insert(i,x);
    }
    head = other.head;
    tail = other.tail;
}
/*
Sequence::~Sequence(){                                                      //destructor for sequence
    
    Node* delme = head;
    while( delme != nullptr) {
        Node* next = delme->next;
 
        delete delme;
        delme = next;
    }
    head = nullptr;
    tail = nullptr;
}
*/
Sequence::~Sequence(){
    while (!this->empty())
        erase(0);
    
    head = nullptr;
    tail = nullptr;
}
Sequence& Sequence::operator=(const Sequence &src){                     //assignment operator
    if (this != &src){
        Sequence temp(src);
        swap(temp);
    }
    
    return *this;
}

bool Sequence::empty() const{                                           //Checks if empty
    if (list_size == 0)
        return true;
    else
        return false;
}

int Sequence::size() const{
                                                                            //Checks for size
    return list_size;
    
}

bool Sequence::insert(int pos, const ItemType& value){   //Inputs a value into sequence at position pos
    //POSITION STARTS AT 0.
    if (pos < 0 || pos > size())
        return false;
    
    if(list_size == 0){                 //if Sequence contains no items
        Node * noob = new Node;
        
        noob->value = value;
        noob->next = nullptr;
        noob->prev = nullptr;
        
        head = noob;
        tail = noob;
        
        list_size += 1;
        return true;
    }
    else if(pos == size()){                        //if value is being placed at end
        Node *p = head;
        while(p->next != nullptr){
            p = p->next;
        }
        Node *noob = new Node;
        noob->value = value;
        p->next = noob;
        noob->next = nullptr;
        noob->prev = p;
        
        tail = noob;
            
        list_size += 1;
        return true;
    }
    else {                                            //other cases
        if(pos == 0){                                //if value is being placed at beginning
            Node * noob = new Node;
            
            noob->value = value;
            noob->next = head;
            head->prev = noob;
            noob->prev = nullptr;
            
            head = noob;
            
            list_size += 1;
            return true;
        }
        else {
            
            Node *p = head;
            int position = 0;
            while (p->next != nullptr){
                if (position == pos){
                
                    Node* noob = new Node;
                
                    noob->value = value;
                    noob->next = p;
                    noob->prev = p->prev;
                    p->prev->next = noob;
                    p->prev = noob;
                
                    list_size++;
                    return true;
                }
                position++;
                p = p->next;
            }
        }
    }
    return false;
}

int Sequence::insert(const ItemType& value){
    int pos = 0;
    
    Node *p = head;
    while(p!=nullptr){
        if(p->value >= value)
            break;
        pos++;
        p=p->next;
    }
    if(0 <= pos && pos <=size()){
        insert(pos, value);
        return pos;
    }
    return -1;
}

bool Sequence::erase(int pos){
    
    if(pos == 0){                                 // if erasing first value in Sequence
        Node* killme = head;
        head = head->next;
        killme = nullptr;
        list_size--;
        return true;
    }
    else if(pos == size()-1){                          //if erasing last value in sequence
        Node* killme = tail;
        tail = tail->prev;
        delete killme;
        list_size--;
        return true;
    }
    else{
        Node*p = head;
        
        for (int i = 0; i < size(); i++){
            if (i == pos){
            
                Node* killme = p;
                
                p->prev->next = p->next;
                p->next->prev = p->prev;
                delete killme;
                list_size--;
                return true;
            }
            p = p->next;
        }
       

    }
    return false;
}

int Sequence::remove(const ItemType& value){
    
    int del_count = 0;                 //return value of how many items deleted
    
    if (size() == 0)               //if there's nothing in sequence...
        return del_count;
    
    if (head->value == value){             //if the very first item is to be removed
        Node *killme = head;
        head = head->next;
        delete killme;
        del_count += 1;
        list_size -= 1;
    }
    else if (tail->value == value){
        Node* killme = tail;
        tail = tail->prev;
        delete killme;
        del_count += 1;
        list_size--;
    }
    Node *p = head;
    while (p!=nullptr){
        if(p->next!=nullptr && p->next->value == value){       //Test this......
            Node *killme = p->next;
            p->next->next->prev = p;
            p->next = p->next->next;
            
            
            delete killme;
            
            del_count += 1;
            list_size -= 1;
        }
        p=p->next;
    }
    return del_count;
}

bool Sequence::get(int pos, ItemType& value) const{
    if(pos >= 0 || pos < size()){
        Node *p = head;
        int count = 0;
        while (p != nullptr){
            
            if(count == pos){
                value = p->value;
                break;
            }
            p = p->next;
            count++;
        }
        return true;
    }
    else
        return false;
}

bool Sequence::set(int pos, const ItemType& value){
    if(pos >= 0 || pos < size()){
        Node *p = head;
        int count = 0;
        while (p != nullptr){   //   or is it p->value != nullptr?
            if(count == pos){
                p->value = value;
                break;
            }
            p = p->next;
            count++;
        }
        return true;
    }
    return false;
}

int Sequence::find(const ItemType& value) const{
        Node *p = head;
        int count = 0;
        while (p != nullptr){
            if(p->value == value)
                return count;
            p = p->next;
            count++;
        }
    return -1;

}

void Sequence::swap(Sequence& other){         //swap head pointer and size
    Node* temp_head = other.head;
    other.head = head;
    head = temp_head;
    
    Node* temp_tail = other.tail;
    other.tail = tail;
    tail = temp_tail;
    
    int temp_size = other.list_size;
    other.list_size = list_size;
    list_size = temp_size;
    
}

int subsequence(const Sequence& seq1, const Sequence& seq2){
    
    if (seq2.empty() || seq2.size() > seq1.size())  // If sequence 2 is empty or larger
        return -1;
    
    ItemType one, two = 0;
    bool subseq = false;
    
    for(int i = 0; i < seq1.size(); i++){
        seq1.get(i, one);
        seq2.get(0, two);
        if(one == two){
            int one_start = i;
            
            for(int two_start = 0, one_start = i; two_start < seq2.size(); two_start++, one_start++){
                subseq = true;
                seq2.get(two_start, two);
                seq1.get(one_start, one);
                if(two != one){
                    subseq = false;
                    break;
                }
            }
            if(subseq)
                return one_start;
        }
    }
    return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result){
    
    Sequence new_result = result;             //in case of aliasing.......
    while (!new_result.empty())             // Erase all the items currently in temp_result.
       new_result.erase(0);
    if(seq1.empty() && !seq2.empty())                       //if either seq1 or seq2 is empty, result = the nonempty one
        new_result = seq2;
    else if(seq2.empty() && !seq1.empty())
        new_result = seq1;
    else{                                //if neither is empty, then function goes through both sequences
        ItemType val1, val2;
        int seq1pos = 0; int seq2pos = 0;
        int resultpos = 0;
        while(seq1pos < seq1.size() || seq2pos < seq2.size()){ //runs through both sequences
            if(seq1pos < seq1.size()){                       //inputs sequence1 value into result first
                seq1.get(seq1pos, val1);
                new_result.insert(resultpos, val1);
                seq1pos++;
                resultpos++;
            }
            if(seq2pos < seq2.size()){
                seq2.get(seq2pos, val2);
                new_result.insert(resultpos, val2);
                seq2pos++;
                resultpos++;
            }
        }
    result = new_result;
    }
}
