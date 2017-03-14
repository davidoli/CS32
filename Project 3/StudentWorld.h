#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_
 
#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "Field.h"
#include <string>
#include <vector>
#include <list>

using namespace std;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    

    void removeDeadActor(int x, int y);
    void removeNull(int x, int y);
    void storeObject(Actor* temp);
    
    //bool checkData(int x, int y, int ID);
    bool checkInsect(int x, int y);
    bool checkFood(int x, int y);
    bool checkPebble(int x, int y);
    Actor* checkPheromone(int x, int y);
    bool checkDanger(int x, int y);
    
    bool checkAntOnOwnHill(int x, int y, Ant* ant);
    void getActor(int x, int y, int ID, Actor*& ptr);
    void updateArray(int x, int y, int image, GraphObject::Direction dir);
    void updateJump(int x, int y, int image, int newX, int newY);
    void setDisplayText(int tick_count);
    
    void poisonAll(int x, int y);
    void stunAll(int x, int y);
    void addFood(int x, int y, int amt);
    Actor* chooseRandomInsect(int x, int y);
private:
    vector<Actor*> actors[64][64];
    //list<Actor*> actors;
    //vector<vector<list<Actor*>>> actors;
    Field* field;
    int tick_count;
    int total_actors;
    int total_anthills;
};

#endif // STUDENTWORLD_H_
