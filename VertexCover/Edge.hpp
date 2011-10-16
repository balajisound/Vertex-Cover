/* 
 * File:   Edge.hpp
 * Author: balajisoundrarajan
 *
 * Created on October 15, 2011, 7:44 PM
 */

#ifndef EDGE_HPP
#define	EDGE_HPP

struct edge{
private:
    
    //The vertices
    int v1;
    int v2;
    
public:
    
    //Constructor
    edge(int V1, int V2);
    
    //Overridden 
    bool operator==(const edge & ) const;
    bool operator<(const edge &) const;
    
    //Questioning
    bool isVertexPresent(int vertex);
    
    //getter functions
    int getVertexOne();
    int getVertexTwo();
    
    //Print
    void printEdge() const;
};


#endif	/* EDGE_HPP */

