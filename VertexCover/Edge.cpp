#include "Edge.hpp"
#include <iostream>

using namespace std;

//edge contructor. The edge cannot be of any other type
edge::edge(int V1, int V2){
    
    v1 = min(V1,V2);
    v2 = max(V1,V2);
    
}

//To check if the vertex is present in the edge
bool edge::isVertexPresent(int vertex){
    if(vertex == v1 || vertex == v2)
        return true;
    return false;
}

//Return the vertex 1
int edge::getVertexOne(){
    return v1;
}

//Return the vertex 2
int edge::getVertexTwo(){
    return v2;
}

//Given vertex of the edge , return the other vertex
int edge::getOtherVertex(int v){
    if(v == v1){
        return v2;
    }
    
    if(v == v2){
        return v1;
    }
    
    //Wrong v.
    return 0;
}

//To check if the edge is same ,  just a rearrangement of vertices are checked
bool edge::operator==(const edge & incoming) const{
    
    //Xor-ing the 2 vertices of the 2 edges
    int XOR = incoming.v1 ^ incoming.v2 ^ v1 ^ v2 ;
    
    //If the XOR value is zero then the edges are the same
    if(XOR == 0)
        return true;
    
    //Else the are different edges.
    return false;
}

//To implement weak strict ordering among the elements
bool edge::operator <(const edge& incoming) const{
    
    //If the incoming elements are same by operator== then return false;
    //if(*this == incoming)
    //    return false;
    if((incoming.v1 == v1) && (incoming.v2 == v2))
        return false;
    
    //If the incoming element is small, then place it first i.e. small
    if(incoming.v1 > v1)
        return false;
    
    if(incoming.v1 < v1)
        return true;
    
    if(incoming.v2 > v2)
        return false;
    
    return true;
}

//Print the edges
void edge::printEdge() const{
    cout << "(" << v1 << "," << v2 <<")";
}