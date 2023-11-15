#pragma once

#include <iostream> // for std::cout, std::endl
#include "node.h"   // Include the Node header

template <typename T>
class List
{
public:
    List() : head(nullptr), tail(nullptr), size(0) {}
    ~List();

    // List methods
    void insert(const T &val);
    void insert(const T &val, int index);
    void set_at(const T &val, int index);
    T getAt(int index) const;
    T remove_at(int index);
    int size_of_list() const { return size; }

private:
    Node<T> *head;
    Node<T> *tail;
    int size;
};

// Definitions for the List methods.

template <typename T>
List<T>::~List()
{
    Node<T> *current = head;
    while (current)
    {
        Node<T> *next = current->get_next();
        delete current;
        current = next;
    }
}

template <typename T>
void List<T>::insert(const T &val)
{
    Node<T> *newNode = new Node(val);
    if (!head)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->set_next(newNode);
        newNode->set_prev(tail);
        tail = newNode;
    }
    ++size;
}

template <typename T>
void List<T>::insert(const T &val, int index)
{
    if (index < 0 || index > size)
    {
        std::cout << "Index out of bounds" << std::endl;
        return;
    }
    Node<T> *newNode = new Node(val);
    if (index == 0)
    {
        newNode->set_next(head);
        if (head)
            head->set_prev(newNode);
        head = newNode;
        if (!tail)
            tail = newNode;
    }
    else
    {
        Node<T> *prev = head;
        for (int i = 0; i < index - 1; ++i)
            prev = prev->get_next();
        newNode->set_next(prev->get_next());
        if (prev->get_next())
            prev->get_next()->set_prev(newNode);
        prev->set_next(newNode);
        newNode->set_prev(prev);
        if (!newNode->get_next())
            tail = newNode;
    }
    ++size;
}

template <typename T>
void List<T>::set_at(const T &val, int index)
{
    if (index < 0 || index >= size)
    {
        std::cout << "Index out of bounds" << std::endl;
        return;
    }
    Node<T> *current = head;
    for (int i = 0; i < index; ++i)
        current = current->get_next();
    current->set_value(val);
}

template <typename T>
T List<T>::getAt(int index) const
{
    if (index < 0 || index >= size)
    {
        std::cout << "Index out of bounds" << std::endl;
        return T(); // Return default-constructed object of type T
    }
    Node<T> *current = head;
    for (int i = 0; i < index; ++i)
        current = current->get_next();
    return current->get_value();
}

template <typename T>
T List<T>::remove_at(int index)
{
    if (index < 0 || index >= size)
    {
        std::cout << "Index out of bounds" << std::endl;
        return T(); // Return default-constructed object of type T
    }
    Node<T> *toDelete = head;
    T value;
    if (index == 0)
    {
        head = toDelete->get_next();
        if (head)
            head->set_prev(nullptr);
        else
            tail = nullptr;
        value = toDelete->get_value();
        delete toDelete;
    }
    else
    {
        Node<T> *prev = head;
        for (int i = 0; i < index - 1; ++i)
            prev = prev->get_next();
        toDelete = prev->get_next();
        value = toDelete->get_value();
        prev->set_next(toDelete->get_next());
        if (toDelete->get_next())
            toDelete->get_next()->set_prev(prev);
        else
            tail = prev;
        delete toDelete;
    }
    --size;
    return value;
}