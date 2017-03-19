
#include "provided.h"
#include "MyMap.h"
#include "support.h"
#include <vector>
#include <iostream>

using namespace std;

class SegmentMapperImpl
{
public:
    SegmentMapperImpl();
    ~SegmentMapperImpl();
    void init(const MapLoader& ml);
    vector<StreetSegment> getSegments(const GeoCoord& gc) const;
private:
    MyMap<GeoCoord, vector<StreetSegment>> map;
};

SegmentMapperImpl::SegmentMapperImpl()
{}

SegmentMapperImpl::~SegmentMapperImpl()
{}

void SegmentMapperImpl::init(const MapLoader& ml)
{
    for(size_t i = 0; i < ml.getNumSegments(); i++)
    {
        
        StreetSegment temp;
        
        ml.getSegment(i,temp);
        vector<StreetSegment>startloc;
        vector<StreetSegment>endloc;
        
        if(map.find(temp.segment.start) == nullptr){          //associate the start coord with street segment
            startloc.push_back(temp);
            map.associate(temp.segment.start, startloc);
        }
        else{                                             //if start coord already has a vector associated with it....
            startloc = *map.find(temp.segment.start);
            startloc.push_back(temp);
        }
        
        if(map.find(temp.segment.end) == nullptr){          //associate the end coord with street segment
            endloc.push_back(temp);
            map.associate(temp.segment.end, endloc);
        }
        else{
            endloc = *map.find(temp.segment.end);
            endloc.push_back(temp);
        }
        if(!temp.attractions.empty()) //for each attraction at each street segment, associate coord with street segment
        {
            for(int j = 0; j < temp.attractions.size(); j++){
                if(map.find(temp.attractions.at(j).geocoordinates) == nullptr){
                    vector<StreetSegment>attractionloc;
                    attractionloc.push_back(temp);
                    map.associate(temp.attractions.at(j).geocoordinates, attractionloc);
                }
                else{
                    vector<StreetSegment> loc = *map.find(temp.attractions.at(j).geocoordinates);
                    loc.push_back(temp);
                }
            }
        }
    }
    
}
vector<StreetSegment> SegmentMapperImpl::getSegments(const GeoCoord& gc) const
{
    
    const vector<StreetSegment> *segments = map.find(gc);
    if (segments == nullptr){
        vector<StreetSegment> returnthis;
        return returnthis;
    }
    vector<StreetSegment> returnthis = *segments;
    return returnthis;
}

//******************** SegmentMapper functions ********************************

// These functions simply delegate to SegmentMapperImpl's functions.
// You probably don't want to change any of this code.

SegmentMapper::SegmentMapper()
{
    m_impl = new SegmentMapperImpl;
}

SegmentMapper::~SegmentMapper()
{
    delete m_impl;
}

void SegmentMapper::init(const MapLoader& ml)
{
    m_impl->init(ml);
}

vector<StreetSegment> SegmentMapper::getSegments(const GeoCoord& gc) const
{
    return m_impl->getSegments(gc);
}
