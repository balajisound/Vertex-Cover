/* 
 * File:   VertexCover.hpp
 * Author: balajisoundrarajan
 *
 * Created on October 16, 2011, 12:52 AM
 */

#include "Graph.hpp"
#include <set>
#include <map>
#include <iostream>

using namespace std;

#ifndef VERTEXCOVER_HPP
#define	VERTEXCOVER_HPP

struct vertexCover{
private :
    set<int> vertices;
    graph * G;
    
public:
    
    //constructor
    //vertexCover(graph);
    vertexCover(const vertexCover & ); //implemented
    vertexCover(set<int> newVertices, graph * Graph); //implemented
    
    //Checking functionalities
    map<int,int> removeableSet();
    int removalNo(int);
    bool isRemovable(int vertex);
    
    //Finding the minimal vertex cover for a given vertex cover
    void minimalize();
    
    //Creation
    vertexCover VCAfterRemoval(int);
    
    //Modification
    bool swapLoneVertex();
    
    //Compute the part1 of the Ashay Dharwadkar
    void computeMinimalVC();
    
    //getter
    set<int> getVertices();
    int getVertexCoverSize();
    
    //setter
    void setVertices(set<int>);
    
    //Union of Covers
    static vertexCover unionVertexCover(vertexCover VC1, vertexCover VC2);
    
    //Print the vertex cover
    void PrintVertexCover();
    
};



#endif	/* VERTEXCOVER_HPP */

