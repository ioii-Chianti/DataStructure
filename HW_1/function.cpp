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

BaseStack<int> *stage;
BaseQueue<string> special;
int *level, maxLevel;
int numCol, numRow;


void InitialzeStage(int W, int H) {
    stage = new BaseStack<int>[W];

    level = new int[W]();
    maxLevel = 0;

    char input;
    for (int row = 0; row < H; row++) {
        for (int col = 0; col < W; col++) {
            cin >> input;
            if ('0' < input && input <= '5') {
                stage[col].push(input - '0');
            } else if (input == '_') {
                stage[col].push(0);
            }
        }
    }
    // ShowResult(W);
}

void generateEnemies(int col) {
    int leftBound = col - 2 >= 0 ? col - 2 : 0;
    int rightBound = col + 2 < numCol ? col + 2 : numCol - 1;
    cout << "--- genetare\n";
}

void ShootNormal(int col, int W) {
    if (col >= W)
        return;
    stage[col].pop();
}

void ShootSpecial(int col, int W) {

}

void FrontRow(int W) {

}

void ShowResult(int W) {
    cout << "END_RESULT:\n";
    BaseStack<int> *revStage = new BaseStack<int>[W];
    for (int i = 0; i < W; i++) {
        while (!stage[i].empty()) {
            revStage[i].push(stage[i].top());
            stage[i].pop();
            
        }
    }

    for (int level = 1; level <= 5; level++) {
        for (int i = 0; i < W; i++) {
            char ch = (!revStage[i].empty() && revStage[i].top()) ? revStage[i].top() + '0' : '_';
            revStage[i].pop();
            cout << ch << ' ';
        }
        cout << '\n';
    }
}

void deleteStage() {
    delete[] stage;
    special.~BaseQueue();
}