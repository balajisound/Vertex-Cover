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
    
    string filename("sample.txt");
    graph G(filename,97);/*Suresh Format*/
    //graph G(filename);/*Aashay Format*/
    //cout << "K : " << G.getK() << endl;
    vertexCover result(G.getVerticesVector(),&G);
    result.computeMinimalVC();

    return 0;
}

