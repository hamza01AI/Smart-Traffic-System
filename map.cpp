#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include <conio.h>
#include <unistd.h>
using namespace std;

// ANSI Color Codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"

void clearScreen()
{
    cout << "\033[2J\033[1;1H";
}
int seriesRandom(const std::vector<int> &numbers)
{
    if (numbers.empty())
    {
        throw std::runtime_error("List is empty");
    }

    static std::random_device rd;  // Seed
    static std::mt19937 gen(rd()); // Random engine
    std::uniform_int_distribution<> dist(0, numbers.size() - 1);

    return numbers[dist(gen)];
}

// random number generator for 4 roads
int rangeRandom(int min, int max)
{
    static mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

void deleteElement(std::vector<int> &v, int value)
{
    v.erase(std::remove(v.begin(), v.end(), value), v.end());
}

struct leftjunction
{
    int noofcars = 0;
    char signal = 'R';
};

struct rightJunction
{
    int noofcars = 0;
    char signal = 'R';
};

struct carsGraph
{
    int noOfCars;
    vector<int> positions;
};
struct joint
{
    int laneNum;
    int noOfCars;
    vector<int> positionsofCars;
    char signal = 'R'; // Traffic signal: 'G' for Green, 'R' for Red
};

// Build Function to Build each road
void buildHorizontalRoad(char road[5][15])
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 15; j++)
            road[i][j] = ' ';
    for (int j = 0; j < 15; j++)
    {
        road[0][j] = '*';
        road[4][j] = '*';
        road[2][j] = '-';
    }
}

void buildverticalRoad(char road[15][9])
{
    for (int i = 0; i < 15; i++)
    {
        road[i][0] = '*';
        road[i][8] = '*';
        road[i][4] = '-';
        road[i][1] = ' ';
        road[i][2] = ' ';
        road[i][3] = ' ';
        road[i][5] = ' ';
        road[i][6] = ' ';
        road[i][7] = ' ';
    }
}

carsGraph carsInfoInitializer(carsGraph carInfo)
{
    int numbers = rangeRandom(1, 6);
    carInfo.noOfCars = numbers;
    vector<int> early_Positions = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    for (int i = 0; i < numbers; i++)
    {

        int randomNo = seriesRandom(early_Positions);
        carInfo.positions.push_back(randomNo);
        deleteElement(early_Positions, randomNo);
    }
    return carInfo;
}

void placeCars(char leftRoad[5][15], char rightRoad[5][15], 
               char topRoad[15][9], char bottomRoad[15][9], 
               const vector<joint>& joints) {
    
    for (const joint& j : joints) {
        int laneNum = j.laneNum;
        
        for (int pos : j.positionsofCars) {
            if (laneNum == 0) {
                topRoad[pos][2] = 'c';
            }
            else if (laneNum == 1) {
                topRoad[pos][6] = 'c';
            }
            else if (laneNum == 2) {
                
                leftRoad[1][pos] = 'c';
            }
            else if (laneNum == 3) {
                
                leftRoad[3][pos] = 'c';
            }
            else if (laneNum == 4) {
                rightRoad[1][pos] = 'c';
            }
            else if (laneNum == 5) {
                rightRoad[3][pos] = 'c';
            }
            else if (laneNum == 6) {
                bottomRoad[pos][2] = 'c';
            }
            else if (laneNum == 7) {
                bottomRoad[pos][6] = 'c';
            }
        }
    }
}

void printHorizontal(const char leftRoad[5][15], const char rightRoad[5][15], const vector<joint>& joints)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 15; j++) {
            if (i == 1 && leftRoad[i][j] == 'c') {
                cout << BLUE << leftRoad[i][j] << RESET;
            } else {
                cout << leftRoad[i][j];
            }
        }
        
        if (i == 2) {
            if (joints[2].signal == 'G') {
                cout << " " << GREEN << joints[2].signal << RESET << " ";
            } else {
                cout << " " << RED << joints[2].signal << RESET << " ";
            }
        } else {
            cout << "   ";
        }
        
        cout << string(7, ' ');
        
        if (i == 2) {
            if (joints[5].signal == 'G') {
                cout << " " << GREEN << joints[5].signal << RESET << " ";
            } else {
                cout << " " << RED << joints[5].signal << RESET << " ";
            }
        } else {
            cout << "   ";
        }
        
        for (int j = 0; j < 15; j++) {
            if (i == 3 && rightRoad[i][j] == 'c') {
                cout << BLUE << rightRoad[i][j] << RESET;
            } else {
                cout << rightRoad[i][j];
            }
        }
        cout << endl;
    }
}
void printVertical(char road[15][9], const vector<joint>& joints, bool isTopRoad)
{
    for (int i = 0; i < 15; i++)
    {
        cout << "                 ";
        for (int j = 0; j < 9; j++)
        {
            if (isTopRoad && j == 6 && road[i][j] == 'c') {
                cout << BLUE << road[i][j] << RESET;
            } else if (!isTopRoad && j == 2 && road[i][j] == 'c') {
                cout << BLUE << road[i][j] << RESET;
            } else {
                cout << road[i][j];
            }
        }
        
        if (i == 7) {
            if (isTopRoad) {
                if (joints[1].signal == 'G') {
                    cout << " " << GREEN << joints[1].signal << RESET;
                } else {
                    cout << " " << RED << joints[1].signal << RESET;
                }
            } else {
                if (joints[6].signal == 'G') {
                    cout << " " << GREEN << joints[6].signal << RESET;
                } else {
                    cout << " " << RED << joints[6].signal << RESET;
                }
            }
        }
        
        cout << endl;
    }
}

joint joiner(joint join, int laneNumber, carsGraph carInfo)
{
    join.laneNum = laneNumber;
    int numOfCars = carInfo.noOfCars;
    join.noOfCars = numOfCars;
    join.positionsofCars = carInfo.positions;
    return join;
}
void controlTrafficSignals(vector<joint>& joints) {
    vector<int> controlLanes = {1, 2, 5, 6};
    
    int maxCars = -1;
    int laneWithMaxCars = -1;
    
    for (int laneNum : controlLanes) {
        if (joints[laneNum].noOfCars > maxCars) {
            maxCars = joints[laneNum].noOfCars;
            laneWithMaxCars = laneNum;
        }
    }
    
    for (int laneNum : controlLanes) {
        joints[laneNum].signal = 'R';
    }
    
    if (laneWithMaxCars != -1) {
        joints[laneWithMaxCars].signal = 'G';
    }
    
    cout << endl << "=== Traffic Signal Control ===" << endl;
    cout << "Comparing lanes: 1, 2, 5, 6" << endl;
    cout << "Lane 1 has " << joints[1].noOfCars << " cars" << endl;
    cout << "Lane 2 has " << joints[2].noOfCars << " cars" << endl;
    cout << "Lane 5 has " << joints[5].noOfCars << " cars" << endl;
    cout << "Lane 6 has " << joints[6].noOfCars << " cars" << endl;
    cout << endl;
    cout << "Decision: Lane " << laneWithMaxCars << " gets GREEN signal (maximum " << maxCars << " cars)" << endl;
    cout << "Other lanes get RED signal" << endl;
    cout << endl;
}

int main()
{
    char leftRoad[5][15];
    char rightRoad[5][15];
    char topRoad[15][9];
    char bottomRoad[15][9];
    vector<carsGraph> carsInfoStore;
    vector<joint> joints;
    
    for (int i = 0; i < 8; i++)
    {
        carsGraph carInfo;
        carsInfoStore.push_back(carsInfoInitializer(carInfo));
    }
    
    for (int i = 0; i < 8; i++)
    {
        joint join;
        joints.push_back(joiner(join, i, carsInfoStore[i]));
    }

    buildHorizontalRoad(leftRoad);
    buildHorizontalRoad(rightRoad);
    buildverticalRoad(topRoad);
    buildverticalRoad(bottomRoad);
    
    controlTrafficSignals(joints);
    
    placeCars(leftRoad, rightRoad, topRoad, bottomRoad, joints);
    
    cout << "=== Traffic Intersection Simulation ===" << endl << endl;
    printVertical(topRoad, joints, true);
    printHorizontal(leftRoad, rightRoad, joints);
    printVertical(bottomRoad, joints, false);
    
    cout << endl << "=== Lane Information with Signals ===" << endl;
    for (joint join : joints)
    {
        cout << "Lane Number: " << join.laneNum << endl;
        cout << "Number of Cars: " << join.noOfCars << endl;
        cout << "Signal Status: " << (join.signal == 'G' ? "GREEN" : "RED") << " (" << join.signal << ")" << endl;
        cout << "Positions of Cars: ";
        for (int position : join.positionsofCars)
        {
            cout << position << " ";
        }
        cout << endl << endl;
    }

    getchar();
    return 0;
}
