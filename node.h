#pragma once

template <typename T>
class Node
{
public:
    Node(const T &val) : value(val), next(nullptr), prev(nullptr) {}

    T get_value() const { return value; }
    void set_value(const T &val) { value = val; }
    Node *get_next() const { return next; }
    void set_next(Node *n) { next = n; }
    Node *get_prev() const { return prev; }
    void set_prev(Node *p) { prev = p; }

private:
    T value;
    Node *next;
    Node *prev;
};
