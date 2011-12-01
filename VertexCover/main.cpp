/* 
 * File:   main.cpp
 * Author: balajisoundrarajan
 *
 * Created on October 15, 2011, 6:25 PM
 */

#include "Graph.hpp"
#include "VertexCover.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <cmath>

using namespace std;

/*
 * 
 */

//This is the driver file function
int main(int argc, char** argv) {
    
    bool print = false;
    
    cout << print << endl <<flush;
    
    if(argc == 2){
        string str(argv[1]);
        
        if(!str.compare("-c")){
            print = true;
        }
    }
    
    cout << print << endl <<flush;
    string strr;
    
    bool flag = true;
    int maxDegree = 0;
    int vertices = 0;
    vector<int> vertexC;
    vector<vector <int> > Matrix;
    
    while(getline(cin,strr)){
        
        if(flag == true){
            istringstream iss(strr);
            vector<int> info;
            copy(istream_iterator<int>(iss), istream_iterator<int>(), back_inserter(info));
            
            //No of Vertices
            vertices = info[0];
            flag = false;
            
            cout << vertices <<endl <<flush;
            
            //This is the vertex cover
            vector<int> VC(vertices+1, 1);
            VC[0]=0;
            vertexC = VC;
            
            //Generate Matrix
            for(int first = 0; first < vertices+1; ++first){
                vector<int> temp(vertices+1,0);
                Matrix.push_back(temp);
            }
            
            continue;
        }
        else{
            vector<int> array;
            istringstream isss(strr);
            copy(istream_iterator<int>(isss), istream_iterator<int>(), back_inserter(array));
            for(int i=1; i <array.size() ; ++i){
                Matrix[array[0]][array[i]]=1; // This is where we built the adjacency matrix
            }
            
            cout << "Array Size = " << array.size()-1 <<endl;
            
            cout << "array.size() - 1 = " << array.size()-1 << "; maxDegree = "<< maxDegree<<endl<<flush;
            
            //int length = array.size() -1;
            
            if(array.size()-1 > maxDegree){
                
                cout << "Yes" <<endl <<flush;
                maxDegree = array.size()-1;
            }
        }
    }
    
    vector< vector <int> > neighbors;
    {
        
        for(int i =0; i < Matrix.size(); ++i){
            //For each vertex
            vector <int> neighbor;
            
            for(int j =0; j < Matrix[i].size() ; ++j ){
                if(Matrix[i][j] == 1)
                    neighbor.push_back(j);
            }
            
            neighbors.push_back(neighbor);
        }
        
    }
    
    Matrix = neighbors;
    
    cout << "maxDegree = "<<maxDegree <<endl <<flush;
    cout << "vertices = "<<vertices <<endl <<flush;
    
    //maxDegree = vertices - ceil ( vertices / (maxDegree +1));
    //maxDegree = (9/10 * maxDegree);
    
    int k=1;
    
    graph G(vertices,maxDegree,1, Matrix, vertexC);
    vertexCover verC(G.getVerticesVector(),&G);
    verC.computeMinimalVC();
    
    return 0;
}

