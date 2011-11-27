#include "VertexCover.hpp"

//default Constructor
//vertexCover::vertexCover(graph g): G(g){}

//copy construtor
vertexCover::vertexCover(const vertexCover & incoming): vertices(incoming.vertices), G(incoming.G){
    
}

//default constructor
vertexCover::vertexCover(set<int> newVertices, graph Graph): vertices(newVertices), G(Graph){
    
}


/*Union of Covers*/
vertexCover vertexCover::unionVertexCover(vertexCover VC1, vertexCover VC2){
    
    //Debug
    static int count = 0; 
    cout << " Calling unionVertexCover " <<count++ << endl <<flush;
    
    //vertices set from VC1 & VC2
    set<int> VC1Vertices = VC1.vertices;
    set<int> VC2Vertices = VC2.vertices;
    set<int> VerticesUnion;
    
    set<int>::iterator it;
    
    //Debug
    //static int i=0;
    
    //cout << "Union" << i++ <<flush;
    
    for(it = VC1Vertices.begin(); it != VC1Vertices.end(); ++it){
        VerticesUnion.insert(*it);        
    }
    
    for(it = VC2Vertices.begin(); it != VC2Vertices.end(); ++it){
        VerticesUnion.insert(*it); 
    }
    
    //Debug
    /*for(set<int>::iterator ite=VerticesUnion.begin(); ite!=VerticesUnion.end() ; ++ite){
        cout << " " << *ite;
    }
    
    cout << endl <<flush;**/
    
    vertexCover cover(VerticesUnion, VC1.G);
    
    return cover;    
}

//getter
set<int> vertexCover::getVertices(){
    return vertices;
}

//setter
void vertexCover::setVertices(set<int> temp){
    vertices = temp;
}

//For a given Vertex Cover, is the vertex removable
bool vertexCover::isRemovable(int vertex){
    
    //Debug
    //static int count = 0;
    //cout<<"calling isRemovable " << count++ << endl<<flush;
    
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
    
    //Debug
    static int count1 = 0;
    cout<<"calling removalNo " << count1++ << endl << flush;
    
    //If the number cannot be removed then return -1
    if(!isRemovable(vertex)){
        return -1;
    }
    
    //create an instance of the set of already available vertices
    set<int> tempVertices = vertices;
    
    
    //Since the vertex is removable, remove it from the tempVertices
    if(tempVertices.erase(vertex) == 0)
        cout <<"There is a problem";
    
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
    
    //return the answer
    return count;
}

//Returns the mapping of vertex to its corresponding row
/*The map says the no of vertices that can be removed if 
 *any particular vertex can be removed
 */

map<int,int> vertexCover::removeableSet(){
    
    //Debug
    static int count = 0;
    cout<<"calling removeableSet()" <<count++ <<endl<<flush;
    
    //This will be returned
    map<int,int> result;
    
    set<int>::iterator it;
    
    for(it = vertices.begin(); it != vertices.end(); ++it){
        
        //The removal number of all the vertices are found and 
        //populated in the matrix
        int temp = removalNo((*it));        
        if(temp != -1 )
            result[(*it)] = temp;
    }
    
    return result;
}

//Finding the minimal vertex cover for a given vertex cover
//Procedure 3.1
void vertexCover::minimalize(){
    
    //Debug
    static int count = 0;
    cout<<"calling minimalize()" << count++ << endl << flush;
    
    //get the resulting map
    map<int,int> result = removeableSet();
    
    //The minimalization is done. Recursion is stopped
    //AT THIS POINT MINIMALIZATION IS DONE
    if(result.size() == 0)
        return;
    
    
    //Get the vertex with the max value
    int candidateVertex = 0 ;
    int maxValue = -1;
    
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
    
    //Debug
    static int count = 0;
    cout<<"calling swapLoneVertex()" << count++ << endl << flush;
    
    
    //Label A:
    //The below code helps in deciding with there exists a lone vertex
    
    //Get a dummy reference
    set<int> & thisVertices = vertices;
    set<edge> thisEdges = G.getEdgesSet();
    
    //Maps the vertex to the no of neighboring vertices 
    map<int,int> countOfOutNeigh;
    
    //Iterate through all the elements to get the neighbors
    set<int>::iterator it;
    set<edge>::iterator edgeIt;
    for(it = thisVertices.begin(); it != thisVertices.end(); ++it){
        
        //Stores all the neighbors of that edge that are not in the Vertexcover
        set<int> neighbor;
        for(edgeIt = thisEdges.begin(); edgeIt != thisEdges.end(); ++edgeIt){
            
            edge temp = *edgeIt;
            
            //If the vertex is present
            if(temp.isVertexPresent(*it)){
                
                //This is the other vertex of the given edge
                int otherVertex = temp.getOtherVertex(*it);
                
                //Check if the other vertex is notpresent in the vertex cover
                if(vertices.find(otherVertex) == vertices.end()){
                    
                    //Add it.
                    neighbor.insert(temp.getOtherVertex(*it));
                }
            }
            
            //Even if the size of neighbors is more than 1 then it is not
            //a candidate
            if(neighbor.size()>1)
                break;
        }
        
        //Check if the neighbor is of size 1 and the vertex is outside VertexCover
        if(neighbor.size() != 1){
            
            //start examining the next vertex
            continue;
        }
        
        //Debug
        //cout << neighbor.size() <<endl <<flush;
        
        //Iterates the neighbors
        set<int>::iterator neighborIt;
        
        //Iterates the one element
        for(neighborIt = neighbor.begin(); neighborIt != neighbor.end(); ++neighborIt ){
            
            //Now we insert the code to remove the vertex and include the new vertex
            thisVertices.erase(*it);
            
            //The neighbor vertex is inserted in place for the removed vertex
            thisVertices.insert(*neighborIt);
            
        }
        
        //Run the Procedure 3.1 again
        minimalize();
        
        //The swapping is done, we return true
        return true;
    }
    
    //If swapping is not done, we return false
    return false;
    //End Label     
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

/*This function calculates the single minimal vertex cover of the initial
 vertex cover i.e. all vertices of the graph. The algorithm followed is 
 * Ashay Dharwadker's Algorithm Part1*/
void vertexCover::computeMinimalVC(){
    
    //Debug
    static int count = 0;
    cout<<"calling computeMinimalVC() "<<count++ <<endl<<flush;
    
    //Flag to signal the end of iteration
    bool found = false;
    
    //Dummy initial value that will be replaced
    int minimum = INT_MAX;
    set<int> dummy;
    vertexCover minimalVC(dummy, G);
    
    //Answer that will be returned
    vector<vertexCover> allCover;
    
    //Iterator for the set of vertices
    set<int>::iterator setIt;
    
    //Create a temporary reference to whole vertex set
    set<int> vertexSet = G.getVerticesSet();
    
    //Iterate through all the vertices
    for(setIt = vertexSet.begin(); setIt != vertexSet.end() ; ++setIt  ){
        
        //copy constructor is used to create a copy
        vertexCover cover = VCAfterRemoval((*setIt));
        
        //Performing procedure 3.1
        cover.minimalize();
        
        //get the cover size
        int s = cover.getVertexCoverSize();
        cout <<"Part1";
        cover.PrintVertexCover();
        
        if(s < minimum){
            cout << " Vertex Cover size:" << s <<endl<<flush;
            minimum = s;
            minimalVC = cover;
        }
        
        //This should never execute
        if(s <= G.getK()){
            
            //allCover.push_back(cover);
            minimalVC = cover;
            found = true;
            break;
        }
        
        for(int j=0 ; j < (G.getTotalVertices()-G.getK()); ++j){
            if(!cover.swapLoneVertex()){
                break;
            };
        }
        
        //get the cover size
        s = cover.getVertexCoverSize();
        cout <<"Part2";
        cover.PrintVertexCover();
        
        if(s < minimum){
            cout << " Vertex Cover size:" << s <<endl<<flush;
            minimum = s;
            minimalVC = cover;
        }
        
        allCover.push_back(cover);
        
        //This should never execute
        if(s <= G.getK()){
            
            //This is the answer
            minimalVC = cover;
            found = true;
            break;
        }
    }

    //Pair-wise Union
    for(int i=0 ; i < allCover.size(); ++i){
        
        //Found is calculated in the previous loop also
        if(found)
            break;
        
        for(int j=i+1; j < allCover.size(); ++j){
            if(found)
                break;
            
            vertexCover unionCover = unionVertexCover(allCover[i],allCover[j]);
            
            //Debug
            //unionCover.PrintVertexCover();
            
            //Calling Procedure 1
            unionCover.minimalize();
            
            //Get the size of the vertex cover
            int s = unionCover.getVertexCoverSize();
            
            if(s < minimum){
                cout << " Vertex Cover size:" << s <<endl<<flush;
                minimum = s;
                minimalVC = unionCover;
            }
            
            //This should never execute
            if(s<= G.getK()){
                //This is the answer
                minimalVC = unionCover;
                found = true;
                break;
            }
            
            for(int k = 0 ; k < G.getK(); ++k){
                if(!unionCover.swapLoneVertex()){
                    break;
                }
            }
            
            s = unionCover.getVertexCoverSize();
            
            if(s < minimum){
                cout << " Vertex Cover size:" << s <<endl<<flush;
                minimum = s;
                minimalVC = unionCover;
            }
            
            //This should never execute
            if(s<= G.getK()){
                //This is the answer
                minimalVC = unionCover;
                found = true;
                break;
            }
        }
    }
    
    //Result is stored in minimal VC . So print the answer.
    cout <<  minimalVC.getVertexCoverSize() << endl;
    set<int> vertices = minimalVC.getVertices();
    set<int>::iterator It;
    
    for(It = vertices.begin(); It != vertices.end(); ++It){
        cout << (*It) <<endl;
    }
    
}

/*Get the size of the vertex cover*/
int vertexCover::getVertexCoverSize(){
    return vertices.size();
}

/*Print the vertex cover*/
void vertexCover::PrintVertexCover(){
    cout << "Printing the vertex cover";
    for(set<int>::iterator ite=vertices.begin(); ite != vertices.end() ; ++ite)
        cout << *ite << " ";
    cout << endl <<flush;
}