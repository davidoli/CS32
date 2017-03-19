#include "provided.h"
#include "MyMap.h"
#include <string>
#include <iostream>
#include<cstdlib>
#include <ctype.h>

using namespace std;

class AttractionMapperImpl
{
public:
    AttractionMapperImpl();
    ~AttractionMapperImpl();
    void init(const MapLoader& ml);
    bool getGeoCoord(string attraction, GeoCoord& gc) const;
private:
    MyMap<string, GeoCoord> map;
    string lowerCase(string input) const{
        string lower;
        for(int i = 0; i<input.size();i++){
            if(isupper(input[i]))
                lower += tolower(input[i]);
            else
                lower += input[i];
        }
        return lower;
    }
};

AttractionMapperImpl::AttractionMapperImpl()
{}

AttractionMapperImpl::~AttractionMapperImpl()
{}

void AttractionMapperImpl::init(const MapLoader& ml)               //make sure the function meets the algorithm speed req.
{
    
    StreetSegment temp;
    size_t amt = ml.getNumSegments();
    for(int i = 0; i < amt; i++)
    {
        bool check = ml.getSegment(i, temp);
        
        if(!temp.attractions.empty() && check)
        {
            for(int j = 0; j < temp.attractions.size(); j++){
                map.associate(lowerCase(temp.attractions.at(j).name), temp.attractions.at(j).geocoordinates);
            }
        }
    }
}

bool AttractionMapperImpl::getGeoCoord(string attraction, GeoCoord& gc) const //make sure the function meets the algorithm speed req.
{
    for(int i = 0; i < attraction.size(); i++)
        attraction[i] = tolower(attraction[i]);
    
    const GeoCoord * geoPoint = map.find(attraction);
    if(geoPoint != nullptr){
        gc = *geoPoint;
        return true;
    }
    return false;
}

//******************** AttractionMapper functions *****************************

// These functions simply delegate to AttractionMapperImpl's functions.
// You probably don't want to change any of this code.

AttractionMapper::AttractionMapper()
{
    m_impl = new AttractionMapperImpl;
}

AttractionMapper::~AttractionMapper()
{
    delete m_impl;
}

void AttractionMapper::init(const MapLoader& ml)
{
    m_impl->init(ml);
}

bool AttractionMapper::getGeoCoord(string attraction, GeoCoord& gc) const
{
    return m_impl->getGeoCoord(attraction, gc);
}
