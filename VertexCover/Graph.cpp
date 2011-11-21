#include "Graph.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>

using namespace std;

//This constructor helps creating a new Graph
graph::graph(set<int> vertices, set<edge> edges):verticesSet(vertices),edgesSet(edges){
    
}

//This Constructor is used to construct the first Graph from the input file
graph::graph(string filename){
    
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
    
    //Populate the vertices set
    for(int i=1 ; i <= nVertices; ++i){
        verticesSet.insert(i);
    }
    
    //Populate the edge set
    for(int i=0; i< matrix.size();++i){
        for(int j=0 ; j<i ; ++j){
            if(matrix[i][j] == 1){
                edgesSet.insert(edge(i,j));
            }
        }
    }
}

/*Construct for Suresh's Format*/
graph::graph(string filename, int flag): nMaxDegree(0){
    
    flag = 96;
    
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
    vector<int> info;
    copy(istream_iterator<int>(iss), istream_iterator<int>(), back_inserter(info));
    nVertices = info[0];
    
    while(getline(ifs,s)){
        vector<int> array;
        istringstream isss(s);
        copy(istream_iterator<int>(isss), istream_iterator<int>(), back_inserter(array));
        verticesSet.insert(array[0]);
        for(int i=1; i <array.size() ; ++i){
            edgesSet.insert(edge(array[0],array[i]));
        }
        
        //Calculate nMaxDegree
        if(nMaxDegree < array.size())
            nMaxDegree = array.size();
    }
    
    k = nVertices - ceil(nVertices / (nMaxDegree +1));
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

/*Return Vertices set*/
set<int> graph::getVerticesSet(){
    return verticesSet;
}

/*Return Edges Set*/
set<edge> graph::getEdgesSet(){
    return edgesSet;
}

/*Return Max Degree*/
int graph::getMaxDegree(){
    return nMaxDegree;
}

/*Return the value of k i.e. atmost value of the size of VC*/
int graph::getK(){
    return k;
}

/*Print the edge set of the matrix*/
void graph::printEdges(){
    cout <<endl << "Printing the edges" <<endl;
    set<edge>::iterator it;
    for (it= edgesSet.begin(); it !=  edgesSet.end(); ++it){
        (*it).printEdge();
    }
}

/*Print the vertices set of the matrix*/
void graph::printVertices(){
    cout << endl << "Printing the vertices" << endl;
    set<int>::iterator it;
    for(it = verticesSet.begin(); it != verticesSet.end(); ++it){
        cout << *it <<  " " ;
    }
    cout<<endl;
}

/*Return the total number of vertices in the graph*/
int graph::getTotalVertices(){
    return nVertices;
}