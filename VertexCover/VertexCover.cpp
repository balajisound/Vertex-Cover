#include "VertexCover.hpp"

//copy construtor
vertexCover::vertexCover(const vertexCover & incoming): vertices(incoming.vertices), G(incoming.G){
    
}

//default constructor
vertexCover::vertexCover(set<int> newVertices, graph Graph): vertices(newVertices), G(Graph){
    
}

//getter
set<int> vertexCover::getVertices(){
    return vertices;
}

//setter
void vertexCover::setVertices(set<int> temp){
    vertices = temp;
}

//For a given Vertx Cover, is the vertex removable
bool vertexCover::isRemovable(int vertex){
    
    //create an instance of the set of already available vertices
    set<int> tempVertices = vertices;
    
    //Remove that particular element from the set
    tempVertices.erase(vertex);
    
    //Get the edge set of the graph
    set<edge> tempEdges = G.getEdgesSet();
    
    //Default. If it fails at any stage , it is set to false.
    bool flag = true;
    
    //Iterate through all the edges
    for(set<edge>::iterator it=tempEdges.begin() ; it != tempEdges.end(); ++it){
        
        //Take the first vertex
        edge e = *it;
        int firstVertex = e.getVertexOne();
        
        //Find it in the set of vertices
        set<int>::iterator findIt = tempVertices.find(firstVertex);
        
        //The vertex is found i.e. The edge is incident
        if(findIt != tempVertices.end())
            continue;
        
        //Take the second vertex
        int secondVertex = e.getVertexTwo();
        
        //Find it in the set of vertices
        findIt = tempVertices.find(secondVertex);
        
        //The vertex is found i.e. The edge is incident
        if(findIt != tempVertices.end())
            continue;
        
        //Then no need to check the rest of the edges.
        flag = false;
        break;
    }
    
    //returns the result.
    return flag;
}

//Calculates the row(mathematical term) i.e. No of elements that can be removed
//if vertex is removed
int vertexCover::removalNo(int vertex){
    
    //If the number cannot be removed then return 0
    if(!isRemovable(vertex)){
        return 0;
    }
    
    //create an instance of the set of already available vertices
    set<int> tempVertices = vertices;
    
    //create a new vertex cover with the new removed vertex set.
    vertexCover tempVC(tempVertices, G);
    
    set<int>::iterator it;
    int count =0;
    
    //Iterate through all the elements
    for(it = tempVertices.begin(); it != tempVertices.end(); ++it){
        
        //If the element can be removed then increment the count of removables.
        if(tempVC.isRemovable((*it)))
            ++count;
    }
}

//Returns the mapping of vertex to its corresponding row
map<int,int> vertexCover::removeableSet(){
    
    //This will be returned
    map<int,int> result;
    
    set<int>::iterator it;
    
    for(it = vertices.begin(); it != vertices.end(); ++it){
        
        //The removal number of all the vertices are found and 
        //populated in the matrix
        int temp;        
        if(temp = removalNo((*it)) != 0 )
            result[(*it)] = temp;
    }
    
    return result;
}

//Finding the minimal vertex cover for a given vertex cover
//Procedure 3.1
void vertexCover::minimalize(){
    
    //get the resulting map
    map<int,int> result = removeableSet();
    
    //The minimalization is done. Recursion is stopped
    if(result.size() == 0)
        return;
    
    
    //Get the vertex with the max value
    int candidateVertex = 0 ;
    int maxValue = 0;
    
    map<int,int>::iterator it;
    
    for( it = result.begin(); it != result.end() ; ++it ){
        if( (*it).second > maxValue ){
            maxValue = (*it).second;
            candidateVertex = (*it).first;
        }
    }
    
    //Remove that particular vertex
    vertices.erase(candidateVertex);
    
    //Repeat the process until the result
    minimalize();
}

//Procedure3.2
//The function performs the removal of the lone point and replace it with the
//other vertex of the edge
//Returns true if the swap is possible
bool vertexCover::swapLoneVertex(){
    
    //Get a dummy reference
    set<int> & vert = vertices;
    
    //Lots of code to go in !!!
    
    
}

//This function is used to create a new vertex cover after the removal of the
//desired vertex
vertexCover vertexCover::VCAfterRemoval(int v){
    set<int> tempSet = vertices;
    
    //Remove the element
    tempSet.erase(v);
    
    //Create the new VertexCover
    vertexCover newVertexCover(tempSet,G);
    
    //Return the newly formed vertexCover
    return newVertexCover;
}

