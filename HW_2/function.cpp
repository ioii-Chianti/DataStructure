#include <iostream>
#include "function.h"
#define MODE 0
using namespace std;

const int Lhs = 0;
const int Equal = 1;
const int Rhs = 2;

template <class T>
Node<T>::Node(T x, T y, T fence) : x(x), y(y), fence(fence), next(NULL) {}

template <class T>
T Node<T>::compare(T x, T y) {
    // compare this node and param node
    // 0: this is bigger, 1: equals, 2: param is bigger
    if (this->x > x || this->x == x && this->y > y)
        return (T)Lhs;
    else if (this->x == x && this->y == y)
        return (T)Equal;
    return (T)Rhs;
}

template <class T>
LinkedList<T>::LinkedList() : length(0) {
    first = new Node<T>(__LONG_LONG_MAX__, __LONG_LONG_MAX__, 0);
}

template <class T>
void LinkedList<T>::insert(T x, T y, T fence) {
    // empty
    if (length == 0) {
        first->next = new Node<T>(x, y, fence);
        length++;
        return;
    }
    // nonempty
    Node<T> *pre = first, *cur = first->next;
    while (cur != NULL) {
        if (cur->compare(x, y) == (T)Rhs) {
            pre = pre->next;
            cur = cur->next;
        } else if (cur->compare(x, y) == (T)Equal) {
            if (cur->fence == 0 && fence == 1)
                cur->fence = 1;
            return;
        } else if (cur->compare(x, y) == (T)Lhs)
            break;
    }
    Node<T> *newNode = new Node<T>(x, y, fence);
    pre->next = newNode;
    newNode->next = (cur == NULL ? NULL : cur);
    length++;
    
}

template <class T>
void LinkedList<T>::deletion(T x, T y) {
    // empty
    if (length == 0)
        return;
    // nonempty
    Node<T> *pre = first, *cur = first->next;
    while (cur != NULL) {
        if (cur->compare(x, y) == (T)Equal) {
            // has fence
            if (cur->fence == 1)
                return;
            // doesn't have fence, then delete node
            pre->next = cur->next;
            length--;
            return;
        } else {
            pre = pre->next;
            cur = cur->next;
        }
    }
}

template <class T>
void LinkedList<T>::show() {
    cout << "Display\n";
    if (length == 0)
        return;
    Node<T> *node = first->next;
    while (node != NULL) {
        cout << '(' << node->x << ',' << node->y << ")\n";
        node = node->next;
    }
    if (MODE) cout << "--- end show\n";
}

LinkedList<long long> ls;

void plant(long long x,long long y,int withFence) {
    ls.insert(x, y, withFence);
    if (MODE) ls.show();
}

void thief(long long x,long long y) {
    ls.deletion(x, y);
    ls.deletion(x - 1, y);
    ls.deletion(x + 1, y);
    ls.deletion(x, y - 1);
    ls.deletion(x, y + 1);
    if (MODE) ls.show();
}

void superThief(long long x,long long y) {
    ls.deletion(x, y);
    ls.deletion(x - 1, y);
    ls.deletion(x + 1, y);
    ls.deletion(x, y - 1);
    ls.deletion(x, y + 1);
    ls.deletion(x - 1, y - 1);
    ls.deletion(x + 1, y + 1);
    ls.deletion(x + 1, y - 1);
    ls.deletion(x - 1, y + 1);
    if (MODE) ls.show();
}

void display() { ls.show(); }