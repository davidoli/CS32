#include "provided.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class MapLoaderImpl
{
public:
    MapLoaderImpl();
    ~MapLoaderImpl();
    bool load(string mapFile);
    size_t getNumSegments() const;
    bool getSegment(size_t segNum, StreetSegment& seg) const;
private:
    vector<StreetSegment*> segments;
    string lowerCase(string input) const{
        string lower;
        for(int i = 0; i<input.size();i++){
            if(isupper(input[i]))
                lower += tolower(input[i]);
        }
        return lower;
    }
};

MapLoaderImpl::MapLoaderImpl()
{
    
}

MapLoaderImpl::~MapLoaderImpl()
{
    for (long int i = segments.size()-1; i >= 0; i--)
        delete segments[i];
    //delete stuff?
}

bool MapLoaderImpl::load(string mapFile)
{
    ifstream reader(mapFile);
    
    if(!reader){
        return false;
    }
    else
    {
        
        while(true)
        {
            string segName;
            getline(reader, segName);
            
            if(!reader)
                break;
            StreetSegment * seg = new StreetSegment;
            seg->streetName = segName;
            
            string GeoLine;                          //read in GeoSeg coordinates
            getline(reader, GeoLine);
            
            
            string sLat = "";
            string sLong = "";
            string eLat = "";
            string eLong = "";
            int pos = 0;
            while (GeoLine[pos] != ',')
            {
                sLat += GeoLine[pos];
                pos++;
            }
            
            while ((!isdigit(GeoLine[pos])) && GeoLine[pos] != '-')
            {
                pos++;
            }
            
            // Get longitude for the
            // starting coordinate
            while (GeoLine[pos] != ' ')
            {
                sLong += GeoLine[pos];
                pos++;
            }
            
            while ((!isdigit(GeoLine[pos])) && GeoLine[pos] != '-')
            {
                pos++;
            }
            
            // Get latitude for the
            // ending coordinate
            while (GeoLine[pos] != ',')
            {
                eLat += GeoLine[pos];
                pos++;
            }
            
            while ((!isdigit(GeoLine[pos])) && GeoLine[pos] != '-')
            {
                pos++;
            }
            
            // Get longitude for the
            // ending coordinate
            while (pos < GeoLine.size())
            {
                eLong += GeoLine[pos];
                pos++;
            }
            
            (*seg).segment = GeoSegment(GeoCoord(sLat, sLong), GeoCoord(eLat, eLong)); //put in coords of GeoSeg
            
            
            //read in number of attractions into variable
            int numberOfAttractions;
            reader >> numberOfAttractions;
            reader.ignore(10000, '\n');
            string aLat = "";
            string aLong = "";
            for(int a = 0; a<numberOfAttractions; a++)
            {
                string attractionstuff;
                getline(reader, attractionstuff);          //read in line of attraction info
                Attraction newattract;
                
                for(int b = 0; b<attractionstuff.size(); b++)
                {
                    if(attractionstuff.at(b) == '|')
                    {
                        newattract.name = attractionstuff.substr(0, b);   //put in name of attraction
                        string latCoord = attractionstuff.substr(b+1, 10);
                        string longCoord = attractionstuff.substr(b+13, 12);
                        newattract.geocoordinates = GeoCoord(latCoord, longCoord); //put in coords for attraction
                    }
                }
                seg->attractions.push_back(newattract);
            }
            segments.push_back(seg);
        }
        return true;
    }
    return false;
}


size_t MapLoaderImpl::getNumSegments() const         //returns number of segments in member vector variable
{
    if(!segments.empty())
        return segments.size();
    else
        return 0;
}

bool MapLoaderImpl::getSegment(size_t segNum, StreetSegment &seg) const //stores segment in "seg" parameter variable
{
    if(segNum >= getNumSegments())
        return false;
    seg = *segments[segNum];
    return true;
}

//******************** MapLoader functions ************************************

// These functions simply delegate to MapLoaderImpl's functions.
// You probably don't want to change any of this code.

MapLoader::MapLoader()
{
    m_impl = new MapLoaderImpl;
}

MapLoader::~MapLoader()
{
    delete m_impl;
}

bool MapLoader::load(string mapFile)
{
    return m_impl->load(mapFile);
}

size_t MapLoader::getNumSegments() const
{
    return m_impl->getNumSegments();
}

bool MapLoader::getSegment(size_t segNum, StreetSegment& seg) const
{
    return m_impl->getSegment(segNum, seg);
}
