#include "Graph.hpp"
#include "VertexCover.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>

using namespace std;

//This Constructor is used to construct the first Graph from the input file
//for adjacency Matrix
graph::graph(string filename){
    
    cout << "Running Ashay's Format" << endl;
    
    //Opening file after converting the string to a c-style string
    ifstream ifs(filename.c_str());
    
    //Check if there is no error opening the file.
    if(!ifs.good()){
        cout << "Error Opening File";
        exit(1);
    }
    
    //Read the first line that contains the no of vertices
    string s;
    getline (ifs, s);
    istringstream iss(s);
    iss >> nVertices;
    
    /*Constructing the Adjacency Matrix, where the dimension are 
     *[nVertices+1, nVertices+1], since the elements can be accessed without
     * adjusting the offset there by eliminating the errors. 
     **/
    
    //Initialize the vector of vertices
    vector<int> tempDummy(nVertices+1,1);
    tempDummy[0]=0;
    verticesVector = tempDummy;
    
    //Generating the first line which is a dummy line of line nVertices+1
    vector<int> firstLine(nVertices+1,0);
    
    //Push the line
    matrix.push_back(firstLine);
    
    //used as a checker to see if the file has nVertices entries
    int count = 0;
    
    //Iterate through the rest of the file to populate the Matrix
    while(getline(ifs,s)){
        
        //Feed s to istringstream to generate the numbers
        istringstream issTemp(s);
        
        //The line should have one dummy value at 0. So 
        // inserting it .
        vector<int> line(1,0);
        
        //Copy the elements to the vector
        copy(istream_iterator<int>(issTemp), istream_iterator<int>(), back_inserter(line));
        
        //error checking for the number of elements in one row is not checked 
        //it is assumed to be enter right !!! Later to be done
        matrix.push_back(line);
        
        count++;
    }
    
    //If the number of entries do not equal the 
    if(count != nVertices){
        cout << "The no of entries for input is not equal to the no of vertices"
                "\n Program Terminating";
        exit(1);
    }  
    
    nMaxDegree = 0;
    int counting =0;
    //Populate the edge set
    for(int i=0; i< matrix.size();++i){
        for(int j=0 ; j < matrix[i].size() ; ++j){
            if(matrix[i][j] == 1){
                ++counting;
            }
        }
        if(counting > nMaxDegree){
            nMaxDegree = counting;
        }
        counting = 0;
    }
    
    //This code will generate the neighboring matrix in a temporary variable
    //After creation we assign this to the matrix member variable.
    vector< vector <int> > neighbors;
    {
        
        for(int i =0; i < matrix.size(); ++i){
            //For each vertex
            vector <int> neighbor;
            
            for(int j =0; j < matrix[i].size() ; ++j ){
                if(matrix[i][j] == 1)
                    neighbor.push_back(j);
            }
            
            neighbors.push_back(neighbor);
        }
        
    }
    
    matrix = neighbors;
    
    
    //nMaxdegree no longer represents max degree but it represents K
    nMaxDegree = nVertices - ceil ( nVertices / (nMaxDegree +1));
    nMaxDegree = (9/10 * nMaxDegree);
    
    //But we are setting it to zero
    k = 1;
    
    
}

/*Constructor for Suresh's Format*/
graph::graph(string filename, bool flag): nMaxDegree(0){
    
    cout << "Running Suresh's Format" << endl;
 
    //Opening file after converting the string to a c-style string
    ifstream ifs(filename.c_str());
    
    //Check if there is no error opening the file.
    if(!ifs.good()){
        cout << "Error Opening File";
        exit(1);
    }
    
    //Read the first line that contains the no of vertices and no of edges
    string s;
    getline (ifs, s);
    istringstream iss(s);
    vector<int> info;
    copy(istream_iterator<int>(iss), istream_iterator<int>(), back_inserter(info));
    nVertices = info[0];
    
    //Initialize the verticesVector
    vector<int> tempDummy(nVertices+1, 1);
    tempDummy[0]=0;
    verticesVector = tempDummy;
    
    //This code block is to initialize the matrix
    {
        for(int first = 0; first < nVertices+1; ++first){
            vector<int> temp(nVertices+1,0);
            matrix.push_back(temp);
        }
    }
    
    nMaxDegree = 0;
        
    //Read the adjacency list
    while(getline(ifs,s)){
        vector<int> array;
        istringstream isss(s);
        copy(istream_iterator<int>(isss), istream_iterator<int>(), back_inserter(array));
        for(int i=1; i <array.size() ; ++i){
            matrix[array[0]][array[i]]=1; // This is where we built the adjacency matrix
        }
        if((array.size()-1) > nMaxDegree){
            nMaxDegree = array.size()-1;
        }
    }
    
    //This code will generate the neighboring matrix in a temporary variable
    //After creation we assign this to the matrix member variable.
    vector< vector <int> > neighbors;
    {
        
        for(int i =0; i < matrix.size(); ++i){
            //For each vertex
            vector <int> neighbor;
            
            for(int j =0; j < matrix[i].size() ; ++j ){
                if(matrix[i][j] == 1)
                    neighbor.push_back(j);
            }
            
            neighbors.push_back(neighbor);
        }
        
    }
    
    matrix = neighbors;
    
    //nMaxdegree no longer represents max degree but it represents K
    nMaxDegree = nVertices - ceil ( nVertices / (nMaxDegree +1));
    nMaxDegree = (9/10 * nMaxDegree);
    
    cout << "nMaxDegree = " <<nMaxDegree<<endl;
        
    //But we are setting it to zero
    k = 420;
}

/*Print the adjacency matrix*/
void graph::printMatrix(){
    cout << endl << "Printing the Adjacency Matrix" <<endl;
    for(int i =0 ; i < matrix.size() ;++i){
        for(int j=0 ; j < matrix[i].size();++j){
            cout<<matrix[i][j]<< " ";
        }
        cout<<endl;
    }
}

/*Print the vertices set of the matrix*/
void graph::printVertices(){
    cout << endl << "Printing the vertices" << endl;
    set<int>::iterator it;
    for(int loop = 0 ; loop < verticesVector.size(); ++loop){
        cout << verticesVector[loop] <<  " " ;
    }
    cout<<endl;
}

/*Return Max Degree*/
int graph::getMaxDegree(){
    return nMaxDegree;
}

/*Return the value of k i.e. atmost value of the size of VC*/
int graph::getK(){
    return k;
}

/*Return the total number of vertices in the graph*/
int graph::getTotalVertices(){
    return nVertices;
}

/*Return the adjacency matrix*/
vector< vector <int> > & graph::getMatrix(){
    return matrix;
}

/*Return the vertices representation in the vector*/
vector<int> graph::getVerticesVector(){
    return verticesVector;
}