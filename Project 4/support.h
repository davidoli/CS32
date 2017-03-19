//
//  support.h
//  Project 4
//
//  Created by David Li on 3/15/17.
//  Copyright © 2017 cs32. All rights reserved.
//

#ifndef support_h
#define support_h

#include "provided.h"


inline bool operator==(const GeoCoord& lhs, const GeoCoord& rhs ) {
    return lhs.latitude == rhs.latitude && lhs.longitude == rhs.longitude;
}
inline bool operator!=(const GeoCoord& lhs, const GeoCoord& rhs ) {
    return (!(lhs.latitude == rhs.latitude && lhs.longitude == rhs.longitude));
}

inline bool operator<(const GeoCoord& lhs, const GeoCoord& rhs ) {
    if(lhs.latitude < rhs.latitude){
        return true;
    }
    if(lhs.latitude == rhs.latitude && lhs.longitude < rhs.longitude){
        return true;
    }
    return false;
}
inline bool operator>(const GeoCoord& lhs, const GeoCoord& rhs ) {
    if(lhs.latitude > rhs.latitude){
        return true;
    }
    if(lhs.latitude == rhs.latitude && lhs.longitude > rhs.longitude){
        return true;
    }
    return false;
}


inline bool operator==(const StreetSegment& lhs, const StreetSegment& rhs ) {
    return ((lhs.streetName == rhs.streetName) && (lhs.segment.start == rhs.segment.start) && (lhs.segment.end == rhs.segment.end) && (lhs.attractions.size() == rhs.attractions.size()));
}


struct Node
{
    Node(double length, double distance, GeoCoord location){
        g = length;
        h = distance;
        f = g + h;
        coord = location;
    }
    Node(){
        g = 0;
        h = 0;
        f = 0;
    }
    GeoCoord coord;
    double f; // node FINAL cost
    double g; // Cost from start to node
    double h; // Cost from node to end
};

inline bool operator<(Node a, Node b)
{
    return a.f > b.f;
}

inline bool operator==(const Node a, const Node b)
{
    return a.coord == b.coord;
}

#endif
