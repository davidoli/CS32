 #include "StudentWorld.h"
 #include <string>
 #include <iostream>
 #include <iomanip>
 #include <sstream>
 #include <vector>
 
 using namespace std;
 
 GameWorld* createStudentWorld(string assetDir)
 {
	return new StudentWorld(assetDir);
 }
 
 StudentWorld::StudentWorld(std::string assetDir)
: GameWorld(assetDir)
{
    
}
StudentWorld::~StudentWorld(){
    cleanUp();
}
int StudentWorld::init()
{
    tick_count = 0;
    // initalize data structure to keep track of simulation virtual world
    for(int x = 0; x < VIEW_WIDTH; x++){
        for(int y = 0; y < VIEW_HEIGHT; y++){
            actors[y][x].clear();
        }
    }
    
    field = new Field;
    Field::FieldItem item;
    string error;
    
    
    Field::LoadResult result = field->loadField(getFieldFilename()/*/Users/macbookpro/Documents/College Yr3/CS32/Project 3/Project3/field.txt"*/);
    
    //////////////Checking Compiler
    vector<Compiler*> compilers = { new Compiler , new Compiler , new Compiler , new Compiler };
    vector<string> files = getFilenamesOfAntPrograms();
    
    total_anthills = files.size(); //check whether all four files are
    
    for (int i = 0; i < total_anthills; i++) {
        if (!(compilers[i]->compile(files[i], error))) {
            setError(files[i] + " " + error);
            return GWSTATUS_LEVEL_ERROR;
        }
    }
                                                         /////////////Checking field.txt
    
    if (result == Field::LoadResult::load_fail_bad_format) {
        setError(getFieldFilename());
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Field::load_fail_file_not_found)
        return GWSTATUS_LEVEL_ERROR;
    
    else {
        for (int x = 0; x < VIEW_WIDTH; x++){
            for(int y = 0; y < VIEW_HEIGHT; y++){
                item = field->getContentsOf(x, y);
                //empty, anthill0, anthill1, anthill2, anthill3, food, grasshopper, water, rock, poison
                switch(item){
                    default:
                    case Field::empty:
                        break;
                    case Field::grasshopper:
                        actors[y][x].push_back(new BabyGrasshopper(x, y, this));
                        total_actors++;
                        break;
                    case Field::rock:
                        actors[y][x].push_back(new Pebble(x,y, this));
                        total_actors++;
                        break;
                    case Field::anthill0:
                        actors[y][x].push_back(new AntHill(x,y, 0, compilers[0], this));
                        total_actors++;
                        break;
                    case Field::anthill1:
                        actors[y][x].push_back(new AntHill(x,y, 1, compilers[1], this));
                        total_actors++;
                        break;
                    case Field::anthill2:
                        actors[y][x].push_back(new AntHill(x,y, 2, compilers[2], this));
                        total_actors++;
                        break;
                    case Field::anthill3:
                        actors[y][x].push_back(new AntHill(x,y, 3, compilers[3], this));
                        total_actors++;
                        break;
                    case Field::food:
                        actors[y][x].push_back(new Food(x,y,6000, this));
                        total_actors++;
                        break;
                    case Field::water:
                        actors[y][x].push_back(new Pool(x, y, this));
                        total_actors++;
                        break;
                    case Field::poison:
                        actors[y][x].push_back(new Poison(x,y, this));
                        total_actors++;
                        break;
                }
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    //increments tick
    tick_count++;
    setDisplayText(tick_count);
  
    for(int x = 0; x < VIEW_WIDTH; x++){
        for(int y = 0; y < VIEW_HEIGHT; y++){
            int origSize = actors[y][x].size();
            int i = 0;
            if(!actors[y][x].empty() && actors[y][x].size() != 0){
                vector<Actor*>::const_iterator it = actors[y][x].begin();
                while(it != actors[y][x].end()){
                    if(*it == nullptr){
                        break;
                    }
                    (*it)->doSomething();
                    
                    if(origSize > actors[y][x].size() )
                    {
                        if(i >= actors[y][x].size() )
                            break;
                        it = actors[y][x].begin();
                        origSize = actors[y][x].size();
                        for(int j = 0; j < i; j++)
                        {
                            ++it;
                        }
                    }
                    else if (origSize < actors[y][x].size() )
                    {
                        origSize = actors[y][x].size();
                        i++;
                        it = actors[y][x].begin();
                        
                        for(int j = 0; j < i; j++)
                        {
                            ++it;
                        }
                    }
                    else
                    {
                        origSize = actors[y][x].size();
                        i++;
                        ++it;
                    }
                    
                }
            }
            removeDeadActor(x, y);
            removeNull(x , y);
        }
    }
    if (tick_count < 2000)
        return GWSTATUS_CONTINUE_GAME;
    else
        return GWSTATUS_PLAYER_WON;
}

void StudentWorld::cleanUp(){
    for(int x = 0; x < VIEW_WIDTH; x++){
        for(int y = 0; y < VIEW_HEIGHT; y++){
            for(int i=0; i<actors[y][x].size(); i++)
                delete actors[y][x][i];
            actors[y][x].clear();
        }
    }
}
void StudentWorld::removeDeadActor(int x, int y) {
    vector<Actor*>::iterator it = actors[y][x].begin();
    while (it != actors[y][x].end())
    {
        if ((*it)==nullptr)
            it = actors[y][x].erase(it);
        if((*it)->isitDead())
        {
            delete *it;
            it = actors[y][x].erase(it);
            total_actors--;
        }
        else
            ++it;
    }
}
void StudentWorld::removeNull(int x, int y){
    /*std::vector<Actor*>::iterator it = actors[y][x].begin();
    while (it != actors[y][x].end()){
        if ((*it)==nullptr)
            it = actors[y][x].erase(it);
        else
            ++it;
    }
*/}
void StudentWorld::storeObject(Actor* temp){
    actors[temp->getY()][temp->getX()].push_back(temp);
    total_actors++;
}

/*bool StudentWorld::checkData(int x, int y, int ID){
    if(!actors[y][x].empty()){
        for(int i=0; i<actors[y][x].size(); i++)
        {
            int id = actors[y][x].at(i)->getID();
            if(id==ID)
                return true;
        }
    }
    return false;
}*/

bool StudentWorld::checkInsect(int x, int y){
    if(!actors[y][x].empty()){
        for(int i=0; i<actors[y][x].size(); i++){
            if(actors[y][x].at(i)->isInsect())
                return true;
        }
    }
    return false;
}

bool StudentWorld::checkFood(int x, int y){
    if(!actors[y][x].empty()){
        for(int i=0; i<actors[y][x].size(); i++)
        {
            if(actors[y][x].at(i)->isFood())
                return true;
        }
    }
    return false;
}

bool StudentWorld::checkPebble(int x, int y){
    if(!actors[y][x].empty()){
        for(int i=0; i<actors[y][x].size(); i++)
        {
            if(actors[y][x].at(i)->isPebble())
                return true;
        }
    }
    return false;
}
Actor* StudentWorld::checkPheromone(int x, int y){
    if(!actors[y][x].empty()){
        for(int i=0; i<actors[y][x].size(); i++)
        {
            if(actors[y][x].at(i)->isPheremone())
                return actors[y][x].at(i);
        }
    }
    return nullptr;
}
bool StudentWorld::checkAntOnOwnHill(int x, int y, Ant* ant){
    Actor* anthill = nullptr;
    getActor(x, y, IID_ANT_HILL, anthill);
    if(ant->getColony() == anthill->getColony())
        return true;
    else
        return false;
}
bool StudentWorld::checkDanger(int x, int y){
    if(!actors[y][x].empty()){
        for(int i=0; i<actors[y][x].size(); i++){
            if(actors[y][x].at(i)->isDanger())
                return true;
        }
    }
    return false;
}

void StudentWorld::getActor(int x, int y, int ID, Actor*& ptr){
    if(!actors[y][x].empty()){
        for(int i=0; i<actors[y][x].size(); i++)
        {
            int id = actors[y][x].at(i)->getID();
            if(id==ID)
                ptr = actors[y][x].at(i);
        }
    }
}

void StudentWorld::updateArray(int x, int y, int image, GraphObject::Direction dir){         //changes actor's array slot
    Actor*transfer;
    for(int i = 0; i < actors[y][x].size(); i++){
        if(actors[y][x][i]->getID() == image && (actors[y][x][i]->getX()!=x || actors[y][x][i]->getY()!=y)){
            transfer = actors[y][x][i];
            actors[y][x].erase(actors[y][x].begin()+i);
        }
    }
    switch (dir) {
        case GraphObject::up:
            actors[y-1][x].push_back(transfer);
            break;
        case GraphObject::right:
            actors[y][x+1].push_back(transfer);
            break;
        case GraphObject::down:
            actors[y+1][x].push_back(transfer);
            break;
        case GraphObject::left:
            actors[y][x-1].push_back(transfer);
            break;
        default:
            break;
    }
}

void StudentWorld::updateJump(int x, int y, int image, int newX, int newY){
    Actor*transfer;
    for(int i = 0; i < actors[y][x].size(); i++){
        if(actors[y][x][i]->getID() == image && (actors[y][x][i]->getX()!=x || actors[y][x][i]->getY()!=y)){
            transfer = actors[y][x][i];
            actors[y][x].erase(actors[y][x].begin()+i);
            break;
        }
    }
    actors[newY][newX].push_back(transfer);
}

void StudentWorld::setDisplayText(int tick_count) {
    int antCount=0; //update later
    ostringstream tick, ant0, ant1, ant2, ant3;
    tick << setw(5) << tick_count;
    tick.fill(' ');
    ant0 << setw(2) << antCount;
    ant0.fill('0');
    ant1 << setw(2) << antCount;
    ant1.fill('0');
    ant2 << setw(2) << antCount;
    ant2.fill('0');
    ant3 << setw(2) << antCount;
    ant3.fill('0');
    string s = "Ticks " + tick.str() + ant0.str() + ant1.str() +ant2.str() +ant3.str();
    setGameStatText(s);
}

void StudentWorld::poisonAll(int x, int y){
    for(int i = 0; i < actors[y][x].size(); i++){
        if(actors[y][x].at(i)->isInsect())
            actors[y][x].at(i)->gotPoisoned();
    }
}
void StudentWorld::stunAll(int x, int y){
    for(int i = 0; i < actors[y][x].size(); i++){
        if(actors[y][x].at(i)->isInsect())
            actors[y][x].at(i)->gotStunned();
    }
}

void StudentWorld::addFood(int x, int y, int amt){
    Actor* food = nullptr;
    if(!checkFood(x, y)){                     //checks if there isn't food at the square
        Food* f = new Food(x, y, amt, this);    //put 100 units of food at spot of ant.
        storeObject(f);                              //store food
    }
    else{
        getActor(x, y, IID_FOOD, food);
        food->addHealth(amt);
    }
}
Actor* StudentWorld::chooseRandomInsect(int x, int y){
    vector<Actor*>Insects;
    int amt_insects = 0;
    for(int i = 0; i < actors[y][x].size(); i++){
        if(actors[y][x].at(i)->isInsect()){
            Insects.push_back(actors[y][x].at(i));
            amt_insects++;
        }
    }
    int randomnumber = randInt(0,amt_insects-1);
    return Insects.at(randomnumber);
}
