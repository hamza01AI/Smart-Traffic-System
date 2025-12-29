#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <string>
using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

// random number generator for 4 roads
int westrandom(int min, int max) {
    static mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}
int eastrandom(int min, int max) {
    static mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}
//int northrandom(int min, int max) {
   // static mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
    //uniform_int_distribution<int> dist(min, max);
    //return dist(gen);
//}
//int southrandom(int min, int max) {
    //static mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
    //uniform_int_distribution<int> dist(min, max);
    //return dist(gen);
//}
 














// function to reduces the time for next car to start 
int reducewest(const int &value)
{
  value=value-1;
  int val=1-1;s
  if(val==0)
  {
    return 1;
  }
  return 0;
}

// Blueprints
struct car {
    char represent = 'c';
    int col;
    int row;
    string position;
};

struct westjunction {
    int noofcars = 0;
    char signal = 'R';
};

struct EastJunction {
    int noofcars = 0;
    char signal = 'R';
};

// Build Function to Build each road
void buildWestRoad(char road[5][15]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 15; j++)
            road[i][j] = ' ';
    for (int j = 0; j < 15; j++) {
        road[0][j] = '*';
        road[4][j] = '*';
        road[2][j] = '-';
    }
}

void buildEastRoad(char road[5][15]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 15; j++)
            road[i][j] = ' ';
    for (int j = 0; j < 15; j++) {
        road[0][j] = '*';
        road[4][j] = '*';
        road[2][j] = '-';
    }
}

void printVertical(const char westroad[5][15], const char eastroad[5][15]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 15; j++)
            cout << westroad[i][j];
        cout << string(10, ' ');  // 10 spaces between roads
        for (int j = 0; j < 15; j++)
            cout << eastroad[i][j];
        cout << endl;
    }
}

void startWestCar(char westroad[5][15], vector<car>& westcar,int value,const westjunction &westjunc) {
    
    if(char check=reducewest(value,westjunc)==1)
    {
    car temp;
    temp.row = 1;
    temp.col = 0;
    temp.position = "West";
    westroad[temp.row][temp.col] = temp.represent;
    westcar.push_back(temp);
    }
}


void Run()
{
    while
    {
        clearscreen();

    }
}

int main() {
    char westroad[5][15];
    char eastroad[5][15];
    int val=westrandom(3,7);
    int val1=reducewest(val);
    

    vector<car> westcar;
    WestJunction westJunc;
    EastJunction eastJunc;

    

    buildWestRoad(westroad);
    buildEastRoad(eastroad);

    startWestCar(westroad, westcar);

    printVertical(westroad, eastroad);

    return 0;
}
