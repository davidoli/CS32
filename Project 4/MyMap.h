#ifndef MyMap_h
#define MyMap_h

#include <stdio.h>
#include <string>
#include "support.h"

using namespace std;
// MyMap.h

// Skeleton for the MyMap class template.  You must implement the first six
// member functions.

template<typename KeyType, typename ValueType>
class MyMap
{
public:
    MyMap(){
        mapCount = 0;
        m_root = NULL;
    }
    ~MyMap(){this->clear();}
    
    void clear(){
        clearNode(m_root);
        mapCount = 0;
        m_root = NULL;
    }
    int size() const{return mapCount;}
    
    void associate(const KeyType& key, const ValueType& value){
        if(m_root == nullptr){ //if tree is empty
            Node * p = new Node(key, value); //add a new node to tree
            m_root = p;
            mapCount++;
            return;
        }
        
        Node * cur = m_root;
        for(;;){
            if(key == cur->key){
                cur->value = value;
                return;
            }
            if(key < cur->key){
                if(cur->left != nullptr)
                    cur = cur->left;
                else {//otherwise, add a node at that left branch
                    cur->left = new Node(key, value);
                    mapCount++;
                    return;
                }
            } else if(cur->key < key){
                if(cur->right != nullptr)     //if it isn't nullptr, go down right branch
                    cur = cur->right;
                else {                  //otherwise add new node at right branch
                    cur->right = new Node(key, value);
                    mapCount++;
                    return;
                }
            }
        }
        
        /*if (m_root == NULL){
            m_root = new Node;
            m_root->key = key;
            m_root->value = value;
            m_root->right = NULL;
            m_root->left = NULL;
        }
        else{
            addNode(m_root, key, value);
        }*/
    }
    
    // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const{
        Node* returnValue = findNode(m_root, key);                      //use private function to find Node
        if(returnValue != NULL)
            return &(returnValue->value);                              //returns address of value
        else
            return nullptr;
    }
    
    // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyMap*>(this)->find(key));
    }
    
    // C++11 syntax for preventing copying and assignment
    MyMap(const MyMap&) = delete;
    MyMap& operator=(const MyMap&) = delete;
    
private:
    struct Node{
        Node(const KeyType& k, const ValueType& v):key(k), value(v), left(nullptr), right(nullptr){}
        KeyType key;
        ValueType value;
        Node* right;
        Node* left;
    };
    
    int mapCount;
    Node* m_root;
    
    Node* findNode(Node* node, const KeyType& key) const{
        if (node == NULL)
            return NULL;
        else if(node->key == key)
            return node;
        else if(node->key < key)
            return findNode(node->right, key);
        else if(node->key > key)
            return findNode(node->left, key);
        
        return NULL;
    }
    
    void clearNode(Node* p){
        if (p == NULL)
            return;
        
        clearNode(p->left);
        clearNode(p->right);
        delete p;
        p = nullptr;
        mapCount--;
    }
    

};

#endif
