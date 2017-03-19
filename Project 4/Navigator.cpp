
#include "provided.h"
#include "support.h"
#include "MyMap.h"
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <iostream>

using namespace std;

class NavigatorImpl
{
public:
    NavigatorImpl();
    ~NavigatorImpl();
    bool loadMapData(string mapFile);
    NavResult navigate(string start, string end, vector<NavSegment>& directions) const;
private:
    SegmentMapper sm;
    AttractionMapper am;
    MapLoader ml;
    list<StreetSegment> open;
    list<StreetSegment> closed;
    
    string getDirection(int angle) const {
        if((angle >= 0 && angle <=22.5) || (angle >= 337.5 && angle <= 360.5))
            return "east";
        else if(angle >= 22.5 && angle <= 67.5)
            return "northeast";
        else if(angle >= 67.5 && angle <= 112.5)
            return "north";
        else if(angle >= 112.5 && angle <= 157.5)
            return "northwest";
        else if(angle >= 157.5 && angle <= 202.5)
            return "west";
        else if(angle >= 202.5 && angle <= 247.5)
            return "southwest";
        else if(angle >= 247.5 && angle <= 292.5)
            return "south";
        else if(angle >= 292.5 && angle <= 337.5)
            return "southeast";
        else
            return "error";
    }
    
    Node findLeastNode(list<Node> list) const {  //finds the Node with lowest f value to be evaluated by navigate function
        std::list<Node>::iterator current;
        std::list<Node>::iterator next;
        
        current = list.begin();
        Node lowest = *current;          //set first in list as lowest
        while (current != list.end())   //iterate through list of Nodes to find smallest value Node
        {
            next = ++current;
            --current;
            Node temp = *current;
            if (temp.f < lowest.f) // Update smallest Node (measured by f value)
                lowest = temp;
            
            current = next;
        }
        return lowest;
    }
    bool checkBetterNode(list<Node> nodes, Node compare) const{
        list<Node>::iterator current;
        list<Node>::iterator next;
        
        // Start at the first value
        current = nodes.begin();
        while (current != nodes.end())
        {
            next = ++current;
            --current;
            Node comparethis = *current;
            
            if (comparethis.f <= compare.f && comparethis.coord == compare.coord)
                return false;
            
            current = next;
        }
        return true;
    }
};

NavigatorImpl::NavigatorImpl()
{
    
}

NavigatorImpl::~NavigatorImpl()
{
}

bool NavigatorImpl::loadMapData(string mapFile)
{
    if(!ml.load(mapFile))
        return false;
    am.init(ml);
    sm.init(ml);
    
    return true;
}

NavResult NavigatorImpl::navigate(string start, string end, vector<NavSegment> &directions) const
{
    //Utilizing a rendition of an A* algorithm.....
    
    
    GeoCoord startCoord, endCoord;             //check if inputs are valid first
    if (!(am.getGeoCoord(start, startCoord)))
        return NAV_BAD_SOURCE;
    
    if (!(am.getGeoCoord(end, endCoord)))
        return NAV_BAD_DESTINATION;
    
    list<Node> open, close;  //create the open and closed lists for A*
    
    Node startHere(0,0,startCoord); //create Node from first coordinate and push into open list to evaluate
    
    //addDirection(startHere);
    
    open.push_back(startHere);
    
    while(!open.empty()){
        Node thisNode = findLeastNode(open);
        open.remove(thisNode);              //pop off current Node being evaluated
        
        //find neighbors of the current Node being evaluated
        vector<StreetSegment> vec = sm.getSegments(thisNode.coord);
        
        for(int i = 0; i < vec.size(); i++)
        {                                                    //check if destination is at neighboring node
            if(!vec.at(i).attractions.empty()){
                for(int j = 0; j<vec.at(i).attractions.size();j++){
                    if(endCoord == vec.at(i).attractions.at(j).geocoordinates)
                        return NAV_SUCCESS;
                }
            }
            GeoCoord neighborCoord;
            Node neighbor;
            
            {
                if(thisNode.coord != vec.at(i).segment.start)    //check to make sure not to repeat coordinates
                {
                    neighborCoord = vec[i].segment.start;
                    
                    neighbor.coord = neighborCoord;
                    neighbor.g = thisNode.g + distanceEarthMiles(thisNode.coord, neighbor.coord);
                    neighbor.h = distanceEarthMiles(neighbor.coord, endCoord);
                    neighbor.f = neighbor.g + neighbor.h;
                    if (checkBetterNode(open, neighbor) && checkBetterNode(close, neighbor)){
                        open.push_back(neighbor);
                    }
                }
                if(thisNode.coord != vec.at(i).segment.end)   //check to make sure not to repeat coordinates
                {
                    neighborCoord = vec[i].segment.end;
                    
                    neighbor.coord = neighborCoord;
                    neighbor.g = thisNode.g + distanceEarthMiles(thisNode.coord, neighbor.coord);
                    neighbor.h = distanceEarthMiles(neighbor.coord, endCoord);
                    neighbor.f = neighbor.g + neighbor.h;
                    if(checkBetterNode(open, neighbor) && checkBetterNode(close, neighbor)){
                        open.push_back(neighbor);
                    }
                }
            }
        }
        close.push_back(thisNode);
    }
    return NAV_NO_ROUTE;
}

//******************** Navigator functions ************************************

// These functions simply delegate to NavigatorImpl's functions.
// You probably don't want to change any of this code.

Navigator::Navigator()
{
    m_impl = new NavigatorImpl;
}

Navigator::~Navigator()
{
    delete m_impl;
}

bool Navigator::loadMapData(string mapFile)
{
    return m_impl->loadMapData(mapFile);
}

NavResult Navigator::navigate(string start, string end, vector<NavSegment>& directions) const
{
    return m_impl->navigate(start, end, directions);
}
