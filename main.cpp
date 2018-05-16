// Author: Darius Sherman
// Assignment Title:  Racing
// Assignment Description: This program will determine where to put cameras
//                         on a racetrack so that racecars must pass at least
//                         one camera
// Due Date: 04/29/2018
// Date Created: 04/29/2018
// Date Last Modified: 04/29/2018

#include <iostream>
#include <vector>

using namespace std;

struct data{
    int vertexA;
    int vertexB;
    int weight;
};

class disjointSet{

private:
    vector<int> pset;
    const int MAX = 100000;

public:

    disjointSet(){
        pset.assign(MAX,0);
    }

    void initSet(int N ){

        for(int i = 0; i < N; i++)
            pset[i] = i;
    }

    int findSet(int i){
        if (pset[i] == i)
            return i;
        else
            return (pset[i]=findSet(pset[i]));
    }

    bool isSameSet(int i, int j){
        return findSet(i) == findSet(j);
    }

    void unionSet(int i, int j){
        pset[findSet(i)] = findSet(j);
    }

    int countSets(int N){
        int count = 0;

        for(int i = 0; i < N; i++){
            if(pset[i] == i) count++;
        }

        return count;
    }

};

void sortData(data* data, int edges){
    for ( int k = 0; k < edges; k++ ){
        for( int l = 0; l < edges - k; l++){
            if( data[l].vertexB < data[l+1].vertexB ){
                swap( data[l], data[l+1] );
            }
        }
    }

    for ( int k = 0; k < edges; k++ ){
        for( int l = 0; l < edges - k; l++){
            if( data[l].vertexA < data[l+1].vertexA ){
                swap( data[l], data[l+1] );
            }
        }
    }

    // Sort data based on weight
    for ( int k = 0; k < edges; k++ ){
        for( int l = 0; l < edges - k; l++){
            if( data[l].weight < data[l+1].weight ){
                swap( data[l], data[l+1] );
            }
        }
    }
}

int main() {

    int dataSets = 0, edges = 0, vertices = 0, theZero;
    int cost = 0;

    cin >> dataSets;

    disjointSet map;
    data data[100000];

    __asm__( mov eax, ecx);

    for ( int i = 0; i < dataSets; i++ ){
        cin >> vertices >> edges;
        map.initSet(vertices);

        // Cin all of the data into the array
        for ( int j = 0; j < edges; j++ ){
            cin >> data[j].vertexA >> data[j].vertexB >> data[j].weight;
        }

        sortData(data, edges);

        // Go through edges and determine if a cycle or not
        for ( int m = 0; m < edges; m++ ){
            if ( !map.isSameSet(data[m].vertexA, data[m].vertexB) ){
                map.unionSet(data[m].vertexA, data[m].vertexB);
            }
            else{
                cost += data[m].weight;
            }
        }

        // Output cost
        cout << cost << endl;
        cost = 0;
    }

    cin >> theZero;

    return 0;
}