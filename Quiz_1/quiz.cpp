#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

stack<int> *spots;
queue<int> layer;

void ShowStack(int numSpot) {
    for (int i = 0; i < numSpot; i++) {
        cout << "--- spot " << i << " --- \n";
        while (!spots[i].empty()) {
            cout << spots[i].top() << " ";
            spots[i].pop();
        }
        cout << '\n';
    }
}

int findMaxLevel(int numSpot) {
    int ret = 0;
    for (int i = 0; i < numSpot; i++)
        ret = (ret >= spots[i].size() ? ret : spots[i].size());
    return ret;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int numSpot, numIns;
        cin >> numSpot >> numIns;
        spots = new stack<int>[numSpot];
        while (numIns--) {
            int spot, num, treasure;
            cin >> spot >> num;
            for (int i = 0; i < num; i++) {
                cin >> treasure;
                spots[spot].push(treasure);
            }
        }

        // ShowStack(numSpot);

        int numLayer;
        cin >> numLayer;
        for (int i = 0; i < numLayer; i++) {
            int input;
            cin >> input;
            layer.push(input);
        }

        int maxLevel = findMaxLevel(numSpot);
        for (int i = 1; i <= maxLevel; i++) {
            if (layer.empty()) break;

            if (i == layer.front()) {
                for (int s = 0; s < numSpot; s++) {
                    if (!spots[s].empty()) {
                        cout << spots[s].top();
                        spots[s].pop();
                    } else
                        cout << 0;

                    if (s != numSpot - 1)
                        cout << ' ';
                }
                cout << '\n';
                layer.pop();
            } else if (layer.front() == 0 || i != layer.front()) {
                for (int s = 0; s < numSpot; s++) {
                    if (!spots[s].empty())
                        spots[s].pop();
                }
            }
        }

        delete[] spots;
    }
}