/* 
 * File:   Graph.hpp
 * Author: balajisoundrarajan
 *
 * Created on October 15, 2011, 6:29 PM
 */

#include "Edge.hpp"
#include <vector>
#include <string>
#include <set>

using namespace std;

#ifndef GRAPH_HPP
#define	GRAPH_HPP

struct graph{
private:
   
    //The no of vertices of the graph
    //This nVertices is not required later
    int nVertices;
    
    /*Constructing the Adjacency Matrix, where the dimension are 
     *[nVertices+1, nVertices+1], since the elements can be accessed without
     * adjusting the offset there by eliminating the errors. 
     **/
    
    //This matrix is not required later.
    vector< vector <int> > matrix;
    
    //The set of Vertices
    set<int> verticesSet;
    
    //The set of edges
    set<edge> edgesSet;
    
public:
     
    //Constructors
    graph(set<int>, set<edge>);
    graph(string filename);
    
    //Printing
    void printMatrix();    
    void printEdges();
    void printVertices();
    
    //Get functions
    set<int> getVerticesSet();
    set<edge> getEdgesSet();
    
};

#endif	/* GRAPH_HPP */

