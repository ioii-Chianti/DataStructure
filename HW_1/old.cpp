#include <iostream>
#include <string>
#include <cstring>
#include "function.h"
#define SIZE 1000000
using namespace std;

const string SG = "shotgun shells";
const string P = "penetration bullets";
const string SB = "super bullets";

/* Stack Implementation */

template <class T>
BaseStack<T>::BaseStack() {
    _stack = new T[SIZE];
    _top = -1;
    _capacity = SIZE;
}

template<class T>
BaseStack<T>::~BaseStack() {
    delete[] _stack;
}

template <class T>
bool BaseStack<T>::empty() {
    return (_top == -1 && size() == 0);
}

template <class T>
int BaseStack<T>::size() {
    return (_top + 1);
}

template <class T>
T& BaseStack<T>::top() {
    if (!empty())
        return _stack[_top];
}

template <class T>
void BaseStack<T>::push(const T& item) {
    if (size() < _capacity)
        _stack[++_top] = item;
}

template <class T>
void BaseStack<T>::pop() {
    if (!empty())
        _stack[_top--].~T();
}

/* Queue Implementation */

template <class T>
BaseQueue<T>::BaseQueue() {
    _queue = new T[SIZE];
    _front = _rear = -1;
    _capacity = SIZE;
}

template <class T>
BaseQueue<T>::~BaseQueue() {
    delete[] _queue;
}

template <class T>
bool BaseQueue<T>::empty() {
    return (size() == 0);
}

template <class T>
int BaseQueue<T>::size() {
    if (_rear < _front) {
        int fix_rear = _rear + _capacity;
        return fix_rear - _front;
    } else
        return _rear - _front;
}

template <class T>
T& BaseQueue<T>::front() {
    return _queue[(_front + 1) % _capacity];
}

template <class T>
void BaseQueue<T>::push(const T& item) {
    if ((_rear + 1) % _capacity != _front) {
        _rear = (_rear + 1) % _capacity;
        _queue[_rear] = item;
    }
}

template <class T>
void BaseQueue<T>::pop() {
    if (!empty()) {
        _front = (_front + 1) % _capacity;
        _queue[_front].~T();
    }
}

/* Core Functions */

int **stage;
int *level, maxLevel;
int numCol, numRow;
int *zeros;
BaseQueue<string> special;

void InitialzeStage(int W, int H) {
    stage = new int *[SIZE];
    for (int i = 0; i < SIZE; i++)
        stage[i] = new int[W]();
    numCol = W, numRow = H;

    level = new int[W]();
    maxLevel = 0;

    zeros = new int[W]();

    char input;
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < W; c++) {
            cin >> input;
            if ('0' < input && input <= '5') {
                stage[r][c] = input - '0';
                level[c]++;
                maxLevel = max(level[c], maxLevel);
            } else if (input == '_') {
                stage[r][c] = 0;
            }
        }
    }
    // ShowResult(W);
}

void generateEnemies(int col) {
    int leftBound = col - 2 >= 0 ? col - 2 : 0;
    int rightBound = col + 2 < numCol ? col + 2 : numCol - 1;
    for (int i = maxLevel; i <= maxLevel + 2; i++)
        for (int j = leftBound; j <= rightBound; j++)
            stage[i][j] = 1;
    maxLevel += 3;
}

void ShootNormal(int col, int W) {
    // 只有 col == 0 會錯誤
    if (col >= W || col < 0)
        return;
    for (int i = maxLevel - 1; i >= 0; i--) {
        if (stage[i][col] == 0)
            continue;
        else {
            switch (stage[i][col]) {
                case 1: break;
                case 2: special.push(SG); break;
                case 3: special.push(P); break;
                case 4: special.push(SB); break;
                case 5: generateEnemies(col); break;
            }
            
            stage[i][col] = 0;
            level[col]--;
            // int hasEnemy = memcmp(stage[i], zeros, W);
            // cout << "--- hasEne in " << i << "? " << hasEnemy << " \n";
            // if (!hasEnemy) maxLevel--;
            break;
        }
    }
    ShowResult(numCol);
}

void ShootSpecial(int col, int W) {

}

void FrontRow(int W) {

}

void ShowResult(int W) {
    cout << "END_RESULT:\n";
    cout << numCol << ' ' << numRow << '\n';
    for (int i = 0; i <= maxLevel; i++) {
        for (int j = 0; j < numCol; j++) {
            int hasEnemy = memcmp(stage[i], zeros, W);
            if (!hasEnemy)
                return;
            char ch = stage[i][j] ? stage[i][j] + '0' : '_';
            cout << ch << ' ';
        }
        cout << '\n';
    }
}

void deleteStage() {
    for (int i = 0; i < numCol; i++)
        delete[] stage[i];
    delete[] stage;
}