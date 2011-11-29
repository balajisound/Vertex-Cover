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
    vector<int> verticesV;
    graph * G;
    
public:
    
    //constructor
    //vertexCover(graph);
    vertexCover(const vertexCover & ); //implemented
    vertexCover(vector<int> newVertices, graph * Graph); //implemented
    
    //Checking functionalities
    map<int,int> removeableSet();
    int removalNo(int);
    bool isRemovable(int vertex);
    bool isRemovableUsingMatrix(int);
    
    //Finding the minimal vertex cover for a given vertex cover
    void minimalize();
    
    //Creation
    vertexCover VCAfterRemoval(int);
    
    //Modification
    void swapLoneVertex(int);
    
    //Compute the part1 of the Ashay Dharwadkar
    void computeMinimalVC();
    
    //getter
    vector<int> getVertices();
    int getVertexCoverSize();
    
    
    //Union of Covers
    static vertexCover unionVertexCover(vertexCover VC1, vertexCover VC2);
    
    //Print the vertex cover
    void PrintVertexCover();
    
};



#endif	/* VERTEXCOVER_HPP */

