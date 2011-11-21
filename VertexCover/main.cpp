/* 
 * File:   main.cpp
 * Author: balajisoundrarajan
 *
 * Created on October 15, 2011, 6:25 PM
 */

#include "Graph.hpp"
#include "VertexCover.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * 
 */

//This is the driver file function
int main(int argc, char** argv) {
    
    // Code block to check the input file parsing
    string filename("graph.txt");
    graph G(filename, 97);
    //G.printEdges();
    //G.printVertices();
    vertexCover result(G.getVerticesSet(),G);
    result.computeMinimalVC();
    
    
    /* code block driver to check the edge equality and set addition
    edge e1(3,5);
    edge e2(5,3);
    edge e3(2,3);
    
    if(e1 == e2){
        cout << "same";
    }
    else{
        cout << "no same";
    }
    
    set<edge> check;
    
    check.insert(e1);
    
    cout << check.size() << endl;
    
    check.insert(e2);
    
    cout << check.size() << endl;
    
    check.insert(e3);
    
    cout << check.size() << endl;
     * 
     */

    return 0;
}

