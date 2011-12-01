#include "VertexCover.hpp"
#include <fstream>
#include <algorithm>

//default Constructor
//vertexCover::vertexCover(graph g): G(g){}

//copy construtor
vertexCover::vertexCover(const vertexCover & incoming): verticesV(incoming.verticesV), G(incoming.G){
    
}

//default constructor
vertexCover::vertexCover(vector<int> newVertices, graph * Graph): verticesV(newVertices), G(Graph){
    
}


/*Union of Covers*/
vertexCover vertexCover::unionVertexCover(vertexCover VC1, vertexCover VC2){
    
    //Debug
    static int count = 0; 
    //cout << " Calling unionVertexCover " <<count++ << endl <<flush;
    
    //vertices vector from VC1 & VC2
    vector<int> VerticesUnion = VC1.verticesV;
    
    //Include the vertices which are set VC2
    for(int loop = 0; loop < VC2.verticesV.size() ; ++loop){
        if(VC2.verticesV[loop] == 1)
            VerticesUnion[loop] = 1;
    }
    
    //Form the new VertexCover
    vertexCover result(VerticesUnion, VC1.G);
    
    return result;    
}

//getter
vector<int> vertexCover::getVertices(){
    return verticesV;
}

//For a given Vertex Cover, is the vertex removable . DS used is Adj Matrix
bool vertexCover::isRemovableUsingMatrix(int vertex){
    
    //Get a reference to the adjacency matrix
    vector< vector <int> > & adjMatrix = (*G).getMatrix();
    
    //Get the neighbor vector
    vector<int> neighbor = adjMatrix[vertex];
    
    //Check the neighbor
    for(int loop = 0; loop < neighbor.size(); ++loop){
        
        //Each element is a neighbor, so all element should be present in the cover
        if(verticesV[neighbor[loop]] == 0){            
            return false;
        }
    }
    
    //Did not break so true;
    return true;
}

//Calculates the row(mathematical term) i.e. No of elements that can be removed
//if vertex is removed
int vertexCover::removalNo(int vertex){
    
    //Debug
    //static int count1 = 0;
    //cout<<"calling removalNo " << count1++ << endl << flush;
    
    //If the number cannot be removed then return -1
    if(!isRemovableUsingMatrix(vertex)){
        //cout << "Non removeable vertices: " << vertex <<endl;
        return -1;
    }
    
//    cout <<vertex<<" is removable"<<endl;
    
    //create an instance of the set of already available vertices
    vector<int> tempVertices = verticesV;
    
    
    //Since the vertex is removable, remove it from the tempVertices
    tempVertices[vertex] = 0;
    
    //create a new vertex cover with the new removed vertex set.
    vertexCover tempVC(tempVertices, G);
    
    int count =0;
    
    //Iterate through all the elements
    for(int loop =0 ; loop < tempVertices.size(); ++loop){
        
        //We have found a vertex from vertex cover
        if(tempVertices[loop] == 1){
        
            //Check if the vertex can be removed
            if(tempVC.isRemovableUsingMatrix(loop))
                ++count;
        }
    }
    
    
    //cout << count  << " == " << vertex-1 <<endl; 
    //return the answer
    return count;
}

//Returns the mapping of vertex to its corresponding row
/*The map says the no of vertices that can be removed if 
 *any particular vertex can be removed
 */

map<int,int> vertexCover::removeableSet(){
    
    //This will be returned
    map<int,int> result;
 
    for( int loop =0 ; loop < verticesV.size(); ++loop ){
        
        //The removal number of all the vertices are found and 
        //populated in the matrix
        if(verticesV[loop] == 1){
            int temp = removalNo(loop);
            if(temp != -1){
                result[loop] = temp;
            }
        }
    }
    
    return result;
}

//Finding the minimal vertex cover for a given vertex cover
//Procedure 3.1
void vertexCover::minimalize(){
    
//    cout <<"Entering Procedure 1"<<endl;
    
    //get the resulting map
    map<int,int> result = removeableSet();
    
    //The minimalization is done. Recursion is stopped
    //AT THIS POINT MINIMALIZATION IS DONE
    if(result.size() == 0){
//        cout <<"Exiting Procedure 1================================================="<<endl;
        return;
    }
    
    
    //Get the vertex with the max value
    int candidateVertex = 0 ;
    int maxValue = -1;
    bool flag =true;
    
    map<int,int>::iterator it;
    
    for( it = result.begin(); it != result.end() ; ++it ){
        if( (*it).second > maxValue ){
            if(flag==true){
                maxValue = (*it).second;
                candidateVertex = (*it).first;
 //               cout << "Removing " <<candidateVertex <<" ; count =" <<maxValue<<endl;
                flag =false;
            }
            else {
                vector<vector <int> > & adjMatrix = (*G).getMatrix();
                vector<int> previousNeighbor = adjMatrix[candidateVertex];
                vector<int> presentNeighbor = adjMatrix[((*it).first)];
 //               cout <<"previousNeighbor.size() = " << previousNeighbor.size()<< "presentNeighbor.size() = " << presentNeighbor.size()<<endl;
                if(previousNeighbor.size() >= presentNeighbor.size()){
                    maxValue = ((*it).second);
                    candidateVertex = ((*it).first);
 //                   cout << "Candidate " <<candidateVertex <<" ; count =" <<maxValue<<endl;
                }
            }
        }
    }
    
    //Remove that particular vertex
    if(verticesV[candidateVertex] == 0)
    {
        cout <<"Trying to remove a vertex which is not present"<<endl;
        exit(1);
    }
    
//    cout << "Removing Now :  "<<candidateVertex<<endl;
    verticesV[candidateVertex] = 0;
    
    //Repeat the process until the result
    minimalize();
}

//Procedure3.2
//The function performs the removal of the lone point and replace it with the
//other vertex of the edge
void vertexCover::swapLoneVertex(int k){
    
//    cout<<"Entering Procedure 2" << endl << flush;
    
    //counter to check k
    int count = 0;
    
    //Neighbor count - temp variable
    int neighborCount = 0;
    
    //Get reference to the Matrix
    vector< vector <int> > & adjMatrix = (*G).getMatrix();
    
    //Get a reference to the existing Vertex Cover to avoid repeated swapping
    vector<int> VCAvoidSwap = verticesV;
    
    //Iterate through the vertex cover
    for(int loop = 1; loop < verticesV.size(); ++loop){
        
        
        //Find the vertex within the vertexCover
        if(verticesV[loop] == 1){
            
            //validate neighor count is maintained here.
            int neighbor = 0;
            
            //We are getting the neighbors of vertex 'loop'
            vector<int> neighborVector = adjMatrix[loop];
            
            //Look into all the neighbors and find the count
            for(int loop2 = 0 ; loop2 < neighborVector.size(); ++loop2){
                
                //Found a neighbor
                if(verticesV[neighborVector[loop2]] == 0){
                    ++neighborCount;
                    neighbor = neighborVector[loop2];
                }
                
                //This is not a candidate
                if(neighborCount > 1){
                    neighborCount=0;
                    break;
                }
            }
            
            //This is a candidate
            if(neighborCount == 1 && VCAvoidSwap[neighbor] == 0 ){
                //Now swap the vertices
            
                if(verticesV[loop] == 0){
                    cout << "Error verticesV[loop] == 0 " << loop ;
                    exit(1);
                }
                verticesV[loop]=0;

                if(verticesV[neighbor] == 1){
                    cout << "Error verticesV[neighbor] == 1" <<neighbor;
                    exit(1);
                }
                verticesV[neighbor] = 1;

                //Following the algo
//                cout << "Procedure 2 IN->" << neighbor <<"; OUT ->" <<loop<<endl;
                minimalize();
                
                //Increment the counter
                ++count;
                
            }
            
            if(count > k)
                break;
        }
    }
    
//    cout<<"Exiting Procedure 2" << endl << flush;
}

//This function is used to create a new vertex cover after the removal of the
//desired vertex
vertexCover vertexCover::VCAfterRemoval(int v){
    vector<int> tempSet = verticesV;
    
    if(tempSet[v] == 0){
//        cout << "VCAfterRemoval trying to remove a removed vertex" <<endl;
        exit(1);
    }
    
    //Remove the element
    tempSet[v] = 0;
    
    //Create the new VertexCover
    vertexCover newVertexCover(tempSet, G);
    
    //Return the newly formed vertexCover
    return newVertexCover;
}

/*This function calculates the single minimal vertex cover of the initial
 vertex cover i.e. all vertices of the graph. The algorithm followed is 
 * Ashay Dharwadker's Algorithm Part1*/
void vertexCover::computeMinimalVC(){
    
    //Flag to signal the end of iteration
    bool found = false;
    
    //Dummy initial value that will be replaced
    int minimum = (*G).getTotalVertices()+1;
    vector<int> dummy;
    vertexCover minimalVC(dummy, G);
    
    //Answer that will be stored to be used for the union cover
    vector<vertexCover> allCover;
    
    //Iterate through all the vertices
    for(int loop1 = 1 ; loop1 <= ((*G).getTotalVertices()); ++loop1 ){
        
        cout << "Making the "<<loop1<<" th vertex zero"<<endl;
        
        //Create a new vertex cover with loop1 removed
        vertexCover cover = VCAfterRemoval(loop1);
        
        //Performing procedure 3.1
        cover.minimalize();
        
        //get the cover size
        int s = cover.getVertexCoverSize();
        
        if(s < minimum){
            cout << " Vertex Cover size:" << s <<endl<<flush;
            minimum = s;
            minimalVC = cover;
        }
        
        //This should never execute
        if(s <= (*G).getK()){
            
            cout << "Finding a value which is never lesser than k = " << (*G).getK();
            //allCover.push_back(cover);
            minimalVC = cover;
            found = true;
            break;
        }
        
//        cout <<"Entering P2"<<endl;
        //cout<< "((*G).getTotalVertices())-((*G).getMaxDegree()) : " << ((*G).getTotalVertices())-((*G).getK())<<endl;
        for(int j=0 ; j < (((*G).getTotalVertices())-((*G).getMaxDegree())); ++j){
            cover.swapLoneVertex(j);
        }
//        cout <<"Exiting P2"<<endl;
        
        //get the cover size
        s = cover.getVertexCoverSize();
        //cout <<"Part2";
        //cover.PrintVertexCover();
        
        if(s < minimum){
            cout << " Vertex Cover size:" << s <<endl<<flush;
            minimum = s;
            minimalVC = cover;
        }
        
        //cout << (count++) << " " << cover.getVertexCoverSize()<<endl;
        
        allCover.push_back(cover);
        
        //This should never execute
        if(s <= (*G).getK()){
            
            cout << "Finding a value which is never lesser than k = " << (*G).getK();            
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
            if(s<= (*G).getK()){
                cout << "Finding a value which is never lesser than k = " << (*G).getK();     
                //This is the answer
                minimalVC = unionCover;
                found = true;
                break;
            }
            
            for(int k = 0 ; k < (*G).getMaxDegree(); ++k){
                unionCover.swapLoneVertex(k);
            }
            
            s = unionCover.getVertexCoverSize();
            
            if(s < minimum){
                cout << " Vertex Cover size:" << s <<endl<<flush;
                minimum = s;
                minimalVC = unionCover;
            }
            
            //This should never execute
            if(s<= (*G).getK()){
                cout << "Finding a value which is never lesser than k = " << (*G).getK();     
                //This is the answer
                minimalVC = unionCover;
                found = true;
                break;
            }
            
            //cout << count++ << " " << unionCover.getVertexCoverSize()<<endl;
        }
    }
    
    //Result is stored in minimal VC . So print the answer.
    cout <<  minimalVC.getVertexCoverSize() << endl;
    vector<int> vertices = minimalVC.getVertices();
    for(int loop=0; loop < vertices.size(); ++loop){
        if(vertices[loop] == 1)
        cout << loop <<endl;
    }
    
}

/*Get the size of the vertex cover*/
int vertexCover::getVertexCoverSize(){
    int count=0;
    for(int loop = 0; loop < verticesV.size() ; ++loop){
        if(verticesV[loop] == 1)
            ++count;
    }
    return count;
}

/*Print the vertex cover*/
void vertexCover::PrintVertexCover(){
    static int count =1;
    cout << "1. Printing the vertex cover ";
    for(int loop=0; loop < verticesV.size(); ++loop)
        if(verticesV[loop] == 1)
            cout << loop << " ";
    cout << endl <<flush;
}