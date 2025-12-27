#include <iostream>
#include <random>
#include <vector>

#include <string>
using namespace std;



int getRandomInt(int min, int max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(min, max);
    return dist(gen);
}
 
void westRoad(char road[5][15]) {
    

    // initialize with spaces
    for (int i = 0; i < road[i]; i++)
        for (int j = 0; j < cols; j++)
            road[i][j] = ' ';

    // fill rows 0 and 4 with consecutive *'s
    for (int j = 0; j < road[j]; j++) {
        road[0][j] = '*';
        road[4][j] = '*';
    }

    // fill row 2 with consecutive -'s
    for (int j = 0; j < road[j]; j++) {
        road[2][j] = '-';
    }

    // print the road
    for (int i = 0; i < road[i]; i++) {
        for (int j = 0; j < road[j]; j++) {
            cout << road[i][j];
        }
        cout << endl;
    }
    
}

struct car
{   char represent='c';
    int col;
    int row;
    string position;

};


void startwestcar(road,&car,vector &westcar)
{
  car temp;
  road[2][5]=temp.represent;
  temp.position="West";
  push_back(westcar);
}
















int main() {;
    vector<car> westcar;
    char road[5][15];
    westRoad(road);
    startwestcar(road,car,westcar);
  

  
    return 0;
}

