#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

int main() {
    int numTestCases;
    cin >> numTestCases;
    while (numTestCases--) {
        int destination, start;
        cin >> destination >> start;
        queue<pair<int, int>> bfsQueue;
        bfsQueue.push({start, 0});
        int result = -1;
        while (!bfsQueue.empty()) {
            auto current = bfsQueue.front();
            bfsQueue.pop();
            
            int value = current.first;
            int steps = current.second;

            if (value == destination) {
                result = steps;
                break;
            }
            if (value == 0 || value == 1) {
                result = steps + 1;
                break;
            }
            if (value % 2 == 0) {
                bfsQueue.push({value / 2, steps + 1});
            }
            int sqrtValue = sqrt(value);
            if (sqrtValue * sqrtValue == value) {
                bfsQueue.push({sqrtValue, steps + 1});
            }
        }
        cout << result << endl;
    }
    return 0;
}

