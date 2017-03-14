#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include "GameController.h"
#include "GameWorld.h"
#include "Compiler.h"
#include <iostream>
#include <string>

class StudentWorld;

class Actor: public GraphObject{
public:
    Actor(int imageID, int startX, int startY, Direction dir, unsigned int depth, StudentWorld* world):GraphObject(imageID, startX, startY, dir, depth, .25), world(world){
    }
    virtual ~Actor(){setVisible(false);}
    virtual void doSomething() = 0;
    GraphObject::Direction randDir();
    StudentWorld* getWorld() const { return world; }
    
    
    bool areThereRocks(int x, int y);
    virtual bool isitDead(){return false;}
    virtual bool isInsect(){return false;}
    virtual bool isFood(){return false;}
    virtual bool isPebble(){return false;}
    virtual bool isPheremone(){return false;}
    virtual bool isDanger(){return false;}
    
    virtual void gotPoisoned(){return;}
    virtual void gotStunned(){return;}
    virtual void gotBit(int amt){return;}
    
    virtual int getHealth(){return 0;}
    virtual void addHealth(int health){return;}
    virtual void setHealth(int amt){return;}
    virtual void pickUpFood(int amt){return;}
    
    virtual int getColony(){return -1;}
private:
    StudentWorld* world;
};
//____________________________________________________________________________________
class EnergyHolder: public Actor{
public:
    EnergyHolder(int imageID, int startX, int startY, Direction dir, int depth, int amount, StudentWorld* w):Actor(imageID, startX, startY, dir, 1, w), hitpoints(amount), isDead(false){
    }
    virtual void setDead(){isDead = true;}       //how do you remove actor from field when dead?
    virtual bool isitDead(){return isDead;}
    
    virtual void doSomething(){return;}
    
    
    int getHealth() { return hitpoints; }
    void dropHealth() { hitpoints--; }
    void setHealth(int health) { hitpoints = health; }
    void minusHealth(int health) { hitpoints = hitpoints - health; }
    void addHealth(int health) { hitpoints = hitpoints + health; }
    
    void eatFood(int amt);
    
private:
    bool isDead;
    int hitpoints;
};
//-----------------------------------------------------------------------------------
class Insect: public EnergyHolder {
public:
    Insect(int imageID, int startX, int startY, Direction dir, int depth, int health, StudentWorld* w) :
    EnergyHolder(imageID, startX, startY, dir, depth, health, w){
        stunned = 0;
    }
    void moveInsectFrom(int x, int y);
    
    bool isStunned(){
        if(stunned == 0)
            return false;
        else
            return true;
    }
    void dropStun() { stunned--; }
    int getStun(){ return stunned;}
    void setStun(int amt) { stunned = amt; }
    
    virtual void gotPoisoned(){return;}
    virtual void gotStunned(){return;}
    virtual void gotBit(int amt);
     void biteBug(int amt);
    
    virtual bool isInsect(){return true;}
private:
    int stunned;
};
//___________________________________________________________________________________

class Ant: public Insect{                       //IID_ANT_TYPE_0(through 3)
public:
    Ant(int imageID, int startX, int startY, Compiler* compiler, int colony, StudentWorld* w):Insect(imageID, startX, startY, none, 1, 1500, w), colony(colony), commandCount(0), food(0), bitX(-1), bitY(-1), prevBlocked(false){
        setDirection(randDir());
        c = compiler;
    }
    Compiler* getCompiler(){ return c;}
    
    virtual void doSomething();
    bool simpleInterpreter();
    int getFood(){return food;}
    void addFood(int amt){food = food+amt;}
    void setFood(int amt){food = amt;}
    int getPheromoneID(){
        switch (getID()){
            case IID_ANT_TYPE0:
                return IID_PHEROMONE_TYPE0;
                break;
            case IID_ANT_TYPE1:
                return IID_PHEROMONE_TYPE1;
                break;
            case IID_ANT_TYPE2:
                return IID_PHEROMONE_TYPE2;
                break;
            case IID_ANT_TYPE3:
                return IID_PHEROMONE_TYPE3;
                break;
        }
        return -1;
    }
    virtual int getColony(){return colony;}
    virtual void gotBit(int amt);
    bool getBit(){return prevBitten;}
    void resetBit(){bitX = -1; bitY = -1; prevBitten = false;}
    bool getBlocked(){return prevBlocked;}
    void resetBlock(){prevBlocked = false;}
private:
    int colony;
    int commandCount;
    int food;
    int bitX, bitY;
    bool prevBitten;
    bool prevBlocked;
    Compiler *c = nullptr;
};
//__________________________________________________________________________________
class Grasshopper: public Insect{                 //IID_ADULT_GRASSHOPPER
 public:
    Grasshopper(int startX, int startY, StudentWorld* w):Insect(IID_ADULT_GRASSHOPPER, startX, startY, none, 1, 1600, w){
        setDirection(randDir());
        lengthWalk = randInt(2,10);
    }
    virtual void doSomething();
    
    virtual void gotBit(int amt);
    virtual void gotPoisoned(){return;}
    virtual void gotStunned(){return;}
    void jump();
    virtual bool isDanger(){return true;}
private:
    int lengthWalk;
 };
//__________________________________________________________________________________
class BabyGrasshopper: public Insect{
public:
    BabyGrasshopper(int startX, int startY, StudentWorld* w):Insect(IID_BABY_GRASSHOPPER, startX, startY, none, 1, 500, w){
        setDirection(randDir());
        lengthWalk = randInt(2,10);
    }
    virtual void doSomething();
    
    virtual void gotPoisoned();
    virtual void gotStunned();
    virtual bool isDanger(){return true;}
private:
    int lengthWalk;
};
//__________________________________________________________________________________
class AntHill: public EnergyHolder{
public:
    AntHill(int startX, int startY, int col_num, Compiler* compiler, StudentWorld* w):EnergyHolder(IID_ANT_HILL, startX, startY, none, 2, 8999, w){
        colony = col_num;
        c = compiler;
    }
    Compiler* getCompiler(){return c;}
    //Each AntHill object must have a Compiler object passed in (by the StudentWorld::init() method), where the Compiler object holds the compiled Bugs Commands that will govern the behavior of ants born from that anthill.
    virtual void doSomething();
    virtual int getColony(){return colony;}
private:
    int colony;
    Compiler* c = nullptr;
};
//__________________________________________________________________________________
class Pebble: public Actor{
public:
    Pebble(int startX, int startY, StudentWorld* world):Actor(IID_ROCK, startX, startY, right, 1, world){
    }
    virtual void doSomething(){ return; }
    virtual bool isPebble(){return true;}
private:
};

//__________________________________________________________________________________
class Poison: public Actor{
 public:
    Poison(int startX, int startY, StudentWorld* w):Actor(IID_POISON, startX, startY, right, 2, w){}
    
    virtual void doSomething();
    virtual bool isDanger(){return true;}
 };
//__________________________________________________________________________________
class Pool: public Actor{                       //IID_WATER_POOL
 public:
    Pool(int startX, int startY, StudentWorld* w):Actor(IID_WATER_POOL, startX, startY, right, 2, w){}
    bool hasBug(){       //how i do dis??????????????????????????????????????????????????????????
        return false;
    }
    virtual void doSomething();
    virtual bool isDanger(){return true;}
 };
//__________________________________________________________________________________
class Pheromones: public EnergyHolder{                 //IID_PHEREMONE_TYPE0(through 3)
 public:
    Pheromones(int imageID, int startX, int startY, StudentWorld* w):EnergyHolder(imageID, startX, startY, right, 2, 256, w){
    }
    virtual bool isPheremone(){return true;}
    virtual void doSomething(){
        dropHealth();
        if(getHealth() == 0){
            setDead();
            return;
        }
    }
 };

//_________________________________________________________________________________
class Food: public EnergyHolder{  //or is it derived from Actor?
 public:
    Food(int startX, int startY, int un, StudentWorld* w):EnergyHolder(IID_FOOD, startX, startY, right, 2, un, w){}
    virtual void doSomething(){return;}
    void pickUpFood(int amt);                     //is this and dropFood in this class?
    void dropFood(int amt);
    virtual bool isFood(){return true;}

 };
#endif // ACTOR_H_






