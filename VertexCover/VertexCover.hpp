/* 
 * File:   VertexCover.hpp
 * Author: balajisoundrarajan
 *
 * Created on October 16, 2011, 12:52 AM
 */

#include "Graph.hpp"
#include <set>
#include <map>

using namespace std;

#ifndef VERTEXCOVER_HPP
#define	VERTEXCOVER_HPP

struct vertexCover{
private :
    set<int> vertices;
    graph G;
    
public:
    //constructor
    vertexCover(const vertexCover & ); //implemented
    vertexCover(set<int> newVertices, graph Graph); //implemented
    
    //Checking functionalities
    map<int,int> removeableSet();
    int removalNo(int);
    bool isRemovable(int vertex);
    
    //Finding the minimal vertex cover for a given vertex cover
    void minimalize();
    
    //getter
    set<int> getVertices();
    
    //setter
    void setVertices(set<int>);
    
};



#endif	/* VERTEXCOVER_HPP */

