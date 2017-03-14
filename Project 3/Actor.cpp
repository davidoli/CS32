#include "Actor.h"
#include "StudentWorld.h"
#include <algorithm>
//////////////////////////////////////////////////////////////////////////Actor classes
GraphObject::Direction Actor::randDir(){
    int randint = randInt(0,3);
    switch(randint){
        case 0:
            return GraphObject::up;
            break;
        case 1:
            return GraphObject::right;
            break;
        case 2:
            return GraphObject::down;
            break;
        case 3:
            return GraphObject::left;
            break;
        default:
            return GraphObject::none;
    }
}
bool Actor::areThereRocks(int x, int y){
    switch(getDirection()){
        case up:
            return getWorld()->checkPebble(x,y-1);
        case right:
            return getWorld()->checkPebble(x+1,y);
        case down:
            return getWorld()->checkPebble(x,y+1);
        case left:
            return getWorld()->checkPebble(x-1,y);
        default:
            break;
    }
    return false;
}

void EnergyHolder::eatFood(int amt){
    Actor *food = nullptr;
    getWorld()->getActor(getX(), getY(), IID_FOOD, food);
    if(food->getHealth() < amt)
        addHealth(getHealth());
    else if(food->getHealth() >= amt)
        addHealth(amt);
    food->pickUpFood(amt);
}

void Insect::moveInsectFrom(int x, int y){               //Actor walks in direction by 1 and data structure is updated.

    switch(getDirection()){
        case up:
            if(getY()-1 >= 0)
                moveTo(x, y-1);
            break;
        case right:
            if(getX()+1 <= 64)
                moveTo(x+1, y);
            break;
        case down:
            if(getY()+1 <= 64)
                moveTo(x, y+1);
            break;
        case left:
            if(getX()-1 >= 0)
            moveTo(x-1, y);
            break;
        default:
            break;
    }
    int image = this->getID();
    getWorld()->updateArray(x, y, image, getDirection());
}
void Insect::gotBit(int amt){
    minusHealth(amt);
    if(getHealth()<=0){
        getWorld()->addFood(getX(), getY(), 100);
        setDead();
    }
}
void Ant::gotBit(int amt){
    minusHealth(amt);
    if(getHealth()<=0){
        getWorld()->addFood(getX(), getY(), 100);
        setDead();
    }
    bitX = getX();
    bitY = getY();
    prevBitten = true;
}
void Insect::biteBug(int m){
    getWorld()->chooseRandomInsect(getX(), getY())->gotBit(m);
}
                                               ///////////////////////////////////WORK ON THIS PART
/////////////////////////////////////////////////////////////////////////////////////Ant functions
void Ant::doSomething(){
     dropHealth();
     if(getHealth() == 0){
         getWorld()->addFood(getX(), getY(), 100);  //put 100 units of food at spot of ant.
         setDead();
         return;
     }
     else if(isStunned()){
         dropStun();
         return;
     }
    for(int i = 0; i < 10; i++){
        if(!simpleInterpreter()){
            setDead();
            return;
        }
    }
}

bool Ant::simpleInterpreter(){
    int food_ct, checkX, checkY, rand_num;
    Actor* pheromoneptr = nullptr;
    Actor* foodptr = nullptr;
    
    Compiler::Command cmd;
    for (int i = 0; i < 10; i++) {
        if (!getCompiler()->getCommand(commandCount, cmd))
            return false;
        else {
            checkX = getX(); checkY = getY();
            switch (getDirection()) {
                case right:
                    checkX = getX() + 1;
                    break;
                case up:
                    checkY = getY() - 1;
                    break;
                case left:
                    checkX = getX() - 1;
                    break;
                case down:
                    checkY = getY() + 1;
                    break;
                case none:
                    break;
            }
            
            switch (cmd.opcode)
            {
                case Compiler::Opcode::moveForward:
                    moveInsectFrom(getX(), getY());
                    resetBit();
                    resetBlock();
                    commandCount++;
                    return true;
                    break;
                case Compiler::Opcode::generateRandomNumber:
                    rand_num = randInt(0, stoi(cmd.operand1));
                    commandCount++;
                    break;
                case Compiler::Opcode::if_command:
                    switch (stoi(cmd.operand1)) {
                        case 9:
                            if (rand_num == 0)
                                commandCount = stoi(cmd.operand2);
                            else
                                commandCount++;
                            break;
                        case 3: //carrying food?
                            if (getFood() > 0)
                                commandCount = stoi(cmd.operand2);
                            else
                                commandCount++;
                            break;
                        case 4: //am hungry
                            if(getHealth()<=25)
                                commandCount = stoi(cmd.operand2);
                            else
                                commandCount++;
                            break;
                        case 7:
                            if (getWorld()->checkInsect(getX(), getY()))
                                commandCount = stoi(cmd.operand2);
                            else
                                commandCount++;
                            break;
                        case 6:
                            getWorld()->getActor(getX(), getY(), IID_FOOD, foodptr);
                            if (foodptr != nullptr) {
                                if (foodptr->getHealth() >= 1)
                                    commandCount = stoi(cmd.operand2);
                                else
                                    commandCount++;
                            }
                            else
                                commandCount++;
                            break;
                        case 5:
                            if (getWorld()->checkAntOnOwnHill(getX(), getY(), this))
                                commandCount = stoi(cmd.operand2);
                            else
                                commandCount++;
                            break;
                        case 1:
                            pheromoneptr=getWorld()->checkPheromone(checkX, checkY);
                            if (pheromoneptr != nullptr) {
                                if (pheromoneptr->getHealth() >= 1)
                                    commandCount = stoi(cmd.operand2);
                                else
                                    commandCount++;
                            }
                            else
                                commandCount++;
                            break;
                        case 0:
                            if (getWorld()->checkInsect(getX(), getY()) || getWorld()->checkPebble(checkX, checkY))
                                commandCount = stoi(cmd.operand2);
                            else
                                commandCount++;
                            break;
                        case 2:
                            if (getBit())
                                commandCount = stoi(cmd.operand2);
                            else
                                commandCount++;
                            break;
                        case 8:
                            if (getBlocked())
                                commandCount = stoi(cmd.operand2);
                            else
                                commandCount++;
                            break;
                        default:
                            commandCount++;
                            break;
                    }
                    break;
                case Compiler::Opcode::goto_command:
                    commandCount=stoi(cmd.operand1);
                    break;
                case Compiler::Opcode::emitPheromone:
                    pheromoneptr=getWorld()->checkPheromone(getX(), getY());
                    if(pheromoneptr == nullptr)
                        getWorld()->storeObject(new Pheromones(getPheromoneID(),getX(), getY(), getWorld()));
                    else if(pheromoneptr->getID() == getPheromoneID()){
                        if(pheromoneptr->getHealth()==512)
                            pheromoneptr->setHealth(768);
                        pheromoneptr->addHealth(256);
                    }
                    commandCount++;
                    return true;
                    break;
                case Compiler::Opcode::faceRandomDirection:
                    //		cerr << "changdir" << endl;
                    setDirection(randDir());
                    commandCount++;
                    return true;
                    break;
                case Compiler::Opcode::rotateClockwise:
                    if (getDirection() == left)
                        setDirection(up);
                    else
                        setDirection(Direction(getDirection() + 1));
                    commandCount++;
                    return true;
                    break;
                case Compiler::Opcode::rotateCounterClockwise:
                    if (getDirection() == up)
                        setDirection(left);
                    else
                        setDirection(Direction(getDirection() - 1));
                    commandCount++;
                    return true;
                    break;
                case Compiler::Opcode::bite:
                    if(getWorld()->checkInsect(getX(), getY()))
                    {
                        biteBug(15);
                    }
                    commandCount++;
                    return true;
                    break;
                case Compiler::Opcode::pickupFood:
                    if(getWorld()->checkFood(getX(), getY())){
                        Actor* foodOnFloor = nullptr;
                        getWorld()->getActor(getX(), getY(), IID_FOOD, foodOnFloor);
                        if(foodOnFloor != nullptr){
                            food_ct = min(400, foodOnFloor->getHealth());
                            if (getFood() + food_ct > 1800) {
                                food_ct = 1800 - getFood();
                            }
                            addFood(food_ct);
                            foodOnFloor->pickUpFood(food_ct);
                        }
                    }
                    commandCount++;
                    return true;
                    break;
                case Compiler::Opcode::dropFood:
                    if(getWorld()->checkFood(getX(), getY())){
                        Actor* foodOnFloor = nullptr;
                        getWorld()->getActor(getX(), getY(), IID_FOOD, foodOnFloor);
                        if(foodOnFloor != nullptr){
                            foodOnFloor->addHealth(getFood());
                        }
                    }
                    else if(!getWorld()->checkFood(getX(), getY()))
                            getWorld()->addFood(getX(), getY(), getFood());
                    setFood(0);
                    commandCount++;
                    return true;
                    break;
                case Compiler::Opcode::eatFood:
                    if(getFood()<100){
                        addHealth(getFood());
                        food = 0;
                    }
                    else{
                        addHealth(100);
                        food = food - 100;
                    }
                    commandCount++;
                    return true;
                    break;
                case Compiler::Opcode::invalid:
                    return false;
                    break;
                case Compiler::Opcode::label:
                    break;
            }
        }
    }
    return true;
    
}
////////////////////////////////////////////////////////////////////////////////////////////////////
     

void Grasshopper::gotBit(int amt){
    minusHealth(amt);
    if(getHealth()<=0){
        getWorld()->addFood(getX(), getY(), 100);
        setDead();
    }
    else if(getHealth() > 0){
        if(randInt(0,2) == 0){
            biteBug(50); //randomly select a bug to bite.  reduce bug's health by 50.
        }
    }
}

void Grasshopper::doSomething(){
    dropHealth();
    if(getHealth() == 0){
        getWorld()->addFood(getX(), getY(), 100);
        setDead();
        return;
    }
    else if(isStunned()){
        dropStun();
        return;
    }
    
    else if(getWorld()->checkInsect(getX(), getY())){
        if(randInt(0,2) == 0){           //1/3 chance of biting bug
            biteBug(50); //randomly select a bug to bite by 50.
            setStun(2);
            return;
        }
    }
    
    else if(randInt(0,9)==0){     //otherwise, there's a 1/10 chance of jumping to a random open square within 10 radius.
        jump();
        setStun(2);
        return;
    }
    
    if(getWorld()->checkFood(getX(), getY())){
        eatFood(200);        //attempts to eat food
        if(randInt(0,1)==0)  //50% of resting ...
            setStun(2);     //number of ticks stunned to 2
        return;
    }
    if(lengthWalk == 0){                 //check if random walking direction is finished
        setDirection(randDir());
        lengthWalk = randInt(2, 10);
        return;
    }
    else{
        if(!areThereRocks(getX(),getY())){ //else, continue walking in direction facing by 1
            moveInsectFrom(getX(), getY());
            lengthWalk--;
            return;
        }
        else if(areThereRocks(getX(),getY())){ //if blocked, set direction to move to 0, go to sleep.
            lengthWalk = 0;
            setStun(2);
            return;
        }
    }
}
void Grasshopper::jump(){
    int radius = randInt(1,10);
    
    int theta, jumpX, jumpY;
    bool success = false;
    while(!success){
        theta = randInt(0, 360);
        jumpX = getX() + (int)(radius*cos(theta* 3.14159265359/180));
        jumpY = getY() + (int)(radius*sin(theta* 3.14159265359/180));
        if((jumpX < VIEW_WIDTH && jumpX > 0 && jumpY < VIEW_HEIGHT && jumpY > 0) && !getWorld()->checkPebble(jumpX, jumpY)){
            moveTo(jumpX, jumpY);
            int image = this->getID();                                     //update array
            getWorld()->updateJump(getX(), getY(), image, jumpX, jumpY);
            success = true;
        }
    }
    return;
}

void BabyGrasshopper::doSomething(){
    dropHealth();
    if(getHealth() == 0){
        getWorld()->addFood(getX(), getY(), 100);
        setDead();
        return;
     }
    else if(isStunned()){
        dropStun();
        return;
    }
    else if(getHealth() >= 1600){
        Grasshopper* ag = new Grasshopper(getX(),getY(), getWorld());
        getWorld()->storeObject(ag);                            //store grasshopper
        getWorld()->addFood(getX(),getY(), 100);
        setDead();
        return;
     }
    if(getWorld()->checkFood(getX(), getY())){
        eatFood(200);                                       //attempts to eat food
        if(randInt(0,1)==0)                                 //50% of resting ...
            setStun(2);
    }

    
    if(lengthWalk == 0){                 //check if random walking direction is finished
        setDirection(randDir());
        lengthWalk = randInt(2, 10);
        setStun(2);
        return;
    }
    else{
        if(!areThereRocks(getX(),getY())){ //else, continue walking in direction facing by 1
            moveInsectFrom(getX(), getY());
            lengthWalk--;
            return;
        }
        else if(areThereRocks(getX(),getY())){ //if blocked, set direction to move to 0.
            lengthWalk = 0;
            return;
        }
    }
}
void BabyGrasshopper::gotPoisoned(){
    minusHealth(150);
    if(getHealth()<=0){
        getWorld()->addFood(getX(), getY(), 100);
        setDead();
    }
}
void BabyGrasshopper::gotStunned(){
    if(getStun()!=0)
        setStun(2);
}


void AntHill::doSomething(){
    dropHealth();
    if(getHealth() == 0){
        setDead();
        return;
    }
    if(getWorld()->checkFood(getX(), getY())){ //check content on its square
        eatFood(10000);                 //eat up to 10,000 of food if there's food and directly increase hitpoints
        return;
    }
    if(getHealth() >= 2000){
        Ant* newant;
        if(colony == 0){
            newant = new Ant(IID_ANT_TYPE0, getX(), getY(), getCompiler(), 0, getWorld());
        }
        else if(colony == 1){
            newant = new Ant(IID_ANT_TYPE1, getX(), getY(), getCompiler(), 1, getWorld());
        }
        else if(colony == 2){
            newant = new Ant(IID_ANT_TYPE2, getX(), getY(), getCompiler(), 2, getWorld());
        }
        else if(colony == 3){
            newant = new Ant(IID_ANT_TYPE3, getX(), getY(), getCompiler(), 3, getWorld());
        }
        getWorld()->storeObject(newant);                //StudentWorld increase count of total number of ants
    }
}

void Poison::doSomething(){
    getWorld()->poisonAll(getX(), getY());
}

void Pool::doSomething(){
    getWorld()->stunAll(getX(),getY());
}

void Food::pickUpFood(int amt){
    minusHealth(amt);
    if(getHealth()<=0){
        setDead();
    }
}
