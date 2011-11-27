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
    
    //Maximum degree of the graph
    int nMaxDegree;
    
    //Atmost size of Vertex cover for this graph
    int k;
    
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
    
    //Static Object
    //static graph globalGraph;
     
    //Constructors
    graph(set<int>, set<edge>);
    graph(string filename);
    graph(string filename, bool flag);
    
    //Printing
    void printMatrix();    
    void printEdges();
    void printVertices();
    
    //Get functions
    set<int> getVerticesSet();
    set<edge> getEdgesSet();
    int getMaxDegree();
    int getK();
    int getTotalVertices();
    
};

#endif	/* GRAPH_HPP */

