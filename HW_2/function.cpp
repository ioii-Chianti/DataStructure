#include <iostream>
#include "function.h"
using namespace std;

const long long Lhs = 0;
const long long Equal = 1;
const long long Rhs = 2;

template <class T>
Node<T>::Node(T x, T y, T fence) : x(x), y(y), fence(fence), next(NULL) {}

template <class T>
T Node<T>::compare(T x, T y) {
    // compare this node and param node
    if (this->y > y || this->y == y && this->x > x)
        return Lhs;
    else if (this->x == x && this->y == y)
        return Equal;
    return Rhs;
}

template <class T>
LinkedList<T>::LinkedList() : length(0) {
    first = new Node<T>(__LONG_LONG_MAX__, __LONG_LONG_MAX__, 1);
}

template <class T>
void LinkedList<T>::insert(T x, T y, T fence) {
    Node<T> *pre = first, *cur = first->next;
    while (cur) {
        if (cur->compare(x, y) == Rhs) {
            pre = pre->next;
            cur = cur->next;
        } else if (cur->compare(x, y) == Equal) {
            if (cur->fence == 0 && fence == 1)
                cur->fence = 1;
            return;
        } else if (cur->compare(x, y) == Lhs)
            break;
    }
    Node<T> *newNode = new Node<T>(x, y, fence);
    pre->next = newNode;
    newNode->next = cur;
    length++;
}

template <class T>
void LinkedList<T>::deletion(T x, T y) {
    Node<T> *pre = first, *cur = first->next;
    while (cur) {
        if (cur->compare(x, y) == Equal) {
            // has fence
            if (cur->fence == (T)1)
                return;
            // doesn't have fence, then delete node
            pre->next = cur->next;
            length--;
            return;
        }
        pre = pre->next;
        cur = cur->next;
    }
}

template <class T>
void LinkedList<T>::show() {
    cout << "Display\n";
    if (length == 0)
        return;
    Node<T> *node = first->next;
    while (node) {
        cout << '(' << node->x << ',' << node->y << ")\n";
        node = node->next;
    }
}

LinkedList<long long> ls;

void plant(long long x, long long y, int withFence) {
    ls.insert(x, y, withFence);
}

void thief(long long x, long long y) {
    ls.deletion(x, y);
    ls.deletion(x - 1, y);
    ls.deletion(x + 1, y);
    ls.deletion(x, y - 1);
    ls.deletion(x, y + 1);
}

void superThief(long long x, long long y) {
    ls.deletion(x, y);
    ls.deletion(x - 1, y);
    ls.deletion(x + 1, y);
    ls.deletion(x, y - 1);
    ls.deletion(x, y + 1);
    ls.deletion(x - 1, y - 1);
    ls.deletion(x + 1, y + 1);
    ls.deletion(x + 1, y - 1);
    ls.deletion(x - 1, y + 1);
}

void display() { ls.show(); }