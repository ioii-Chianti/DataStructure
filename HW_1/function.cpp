#include <iostream>
#include <string>
#include <cstring>
#include "function.h"
#define STACKSIZE 1000
#define QUEUESIZE 1000001
using namespace std;

const string SG = "shotgun shells";
const string P = "penetration bullets";
const string SB = "super bullets";

/* Stack Implementation */

template <class T>
BaseStack<T>::BaseStack() {
    _stack = new T[STACKSIZE];
    _top = -1;
    _capacity = STACKSIZE;
}

template<class T>
BaseStack<T>::~BaseStack() {
    delete[] _stack;
}

template <class T>
bool BaseStack<T>::empty() {
    return _top == -1;
}

template <class T>
int BaseStack<T>::size() {
    return _top + 1;
}

template <class T>
T& BaseStack<T>::top() {
    if (!empty())
        return _stack[_top];
}

template <class T>
void BaseStack<T>::push(const T& item) {
    // double size
    if (size() >= _capacity) {
        int newCapacity = _capacity * 2;
        T *newStack = new T[newCapacity];
        memcpy(newStack, _stack, _capacity * sizeof(T));
        
        delete[] _stack;
        _stack = newStack;
        _capacity = newCapacity;
    }
    _stack[++_top] = item;
}

template <class T>
void BaseStack<T>::pop() {
    if (!empty())
        _top--;
}


/* Queue Implementation */

template <class T>
BaseQueue<T>::BaseQueue() {
    _queue = new T[QUEUESIZE];
    _front = _rear = -1;
    _capacity = QUEUESIZE;
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
        int rear = _rear + _capacity;
        return rear - _front;
    } else
        return _rear - _front;
}

template <class T>
T& BaseQueue<T>::front() {
    return _queue[(_front + 1) % _capacity];
}

template <class T>
void BaseQueue<T>::push(const T& item) {
    if (size() >= _capacity) {
        int newCapacity = _capacity * 2;
        T* newQueue = new T[newCapacity];
        int Size = size(), index = _front + 1;
        for (int i = 0; i < Size; i++) {
            newQueue[i] = _queue[index++];
            if (index == _capacity)
                index = 0;
        }
        delete[] _queue;
        _queue = newQueue;
        _capacity = newCapacity;
    }
    if ((_rear + 1) % _capacity != _front) {
        _rear = (_rear + 1) % _capacity;
        _queue[_rear] = item;
    }
}

template <class T>
void BaseQueue<T>::pop() {
    if (!empty()) {
        _front = (_front + 1) % _capacity;
    }
}

/* Core Functions */

BaseStack<char> *stage;
BaseQueue<string> special;

void InitialzeStage(int W, int H) {
    stage = new BaseStack<char>[W];

    char input;
    for (int row = 0; row < H; row++) {
        for (int col = 0; col < W; col++) {
            cin >> input;
            stage[col].push(input);
        }
    }

    // pop ending zeros
    for (int i = 0; i < W; i++) {
        while (!stage[i].empty() && stage[i].top() == '_')
            stage[i].pop();
    }
}

int findMaxLevel(int left, int right) {
    int ret = 0;
    for (int i = left; i <= right; i++)
        ret = max(ret, stage[i].size());
    return ret;
}

void generateEnemies(int col, int W) {
    int left = (col - 2 >= 0) ? col - 2 : 0;
    int right = (col + 2 < W) ? col + 2 : W - 1;
    int maxLevel = findMaxLevel(left, right);

    for (int i = left; i <= right; i++) {
        while (stage[i].size() < maxLevel)
            stage[i].push('_');
        stage[i].push('1');
        stage[i].push('1');
        stage[i].push('1');
    }
}

void ShootNormal(int col, int W) {
    if (col >= W || col < 0 || stage[col].empty())
        return;

    char ch = stage[col].top();
    stage[col].pop();

    while (!stage[col].empty() && stage[col].top() == '_')
        stage[col].pop();
    
    switch (ch) {
        case '2': special.push(SG); break;
        case '3': special.push(P); break;
        case '4': special.push(SB); break;
        case '5': generateEnemies(col, W); break;
        default: break;
    }
}

void ShootSpecial(int col, int W) {
    if (col < 0 || col >= W || special.empty())
        return;
        
    string bullet = special.front();
    special.pop();
    
    if (bullet == SG) {
        int left = (col - 2 >= 0) ? col - 2 : 0;
        int right = (col + 2 < W) ? col + 2 : W - 1;
        for (int i = left; i <= right; i++)
            ShootNormal(i, W);
    } else if (bullet == P) {
        int cnt = 0;
        while (cnt < 3) {
            ShootNormal(col, W);
            cnt++;
        }
    } else if (bullet == SB) {
        char type = stage[col].top();
        while (!stage[col].empty() && stage[col].top() == type)
            ShootNormal(col, W);
    }
}

void FrontRow(int W) {
    int maxLevel = findMaxLevel(0, W - 1);
    cout << "FRONT_ROW, LEVEL:" << maxLevel << '\n';
    if (maxLevel) {
        for (int i = 0; i < W; i++) {
            if (stage[i].size() == maxLevel)
                cout << stage[i].top();
            else
                cout << '_';
            if (i != W - 1) cout << ' ';
        }
        cout << '\n';
    }
}

void ShowResult(int W) {
    cout << "END_RESULT:\n";

    int maxLevel = findMaxLevel(0, W - 1);
    if (maxLevel) {
        BaseStack<char> *revStage = new BaseStack<char>[W];
        for (int i = 0; i < W; i++) {
            while (!stage[i].empty()) {
                revStage[i].push(stage[i].top());
                stage[i].pop();
            }
        }
        
        for (int level = 1; level <= maxLevel; level++) {
            for (int i = 0; i < W; i++) {
                char ch = !revStage[i].empty() ? revStage[i].top() : '_';
                revStage[i].pop();
                cout << ch;
                if (i != W - 1) cout << ' ';
            }
            cout << '\n';
        }

        delete[] revStage;
    }
}

void deleteStage() {
    delete[] stage;
}