#include "Restaurant.h"
#include <iostream>
using namespace std;

int main() {
    Restaurant restaurant;
    cout << "Choose mode (1 for Interactive, 2 for Silent): ";
    int mode;
    cin >> mode;
    restaurant.isSilentMode = (mode == 2);

    if (restaurant.isSilentMode) {
        cout << "Simulation Starts in Silent mode ...\n";
    }

    if (restaurant.LoadFile("input.txt")) {
        restaurant.Simulate();
        restaurant.GenerateOutputFile("output.txt");
        if (restaurant.isSilentMode) {
            cout << "Simulation ends, Output file created\n";
        }
    }
    else {
        cout << "[Fatal] Simulation aborted due to file loading error.\n";
    }

    restaurant.CleanUp();
    return 0;
}