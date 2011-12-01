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
    
    //This is the adjacency matrix
    vector< vector <int> > matrix;
    
    //Represent the vertices as a Vector rather than set<int>
    vector<int> verticesVector;
       
public:
    
    //Static Object
    //static graph globalGraph;
     
    //Constructors
    graph(int , int , int , vector< vector <int> > , vector<int> );
    graph(string filename);
    graph(string filename, bool flag);
    
    //Printing
    void printMatrix();    
    void printVertices();
    
    //Get functions
    vector <vector <int> > & getMatrix();
    int getMaxDegree();
    int getK();
    int getTotalVertices();
    vector<int> getVerticesVector();
    
};

#endif	/* GRAPH_HPP */

