#include <iostream>
#include <stdexcept>
#include "node.h"

template <typename T>
class LinkedList
{
private:
    Node<T> *head;
    Node<T> *tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~LinkedList()
    {
        clear();
    }

    void add(T data)
    {
        Node<T> *newNode = new Node<T>(data);
        if (head == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void insert(int index, T data)
    {
        if (index < 0 || index > size)
        {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0)
        {
            Node<T> *newNode = new Node<T>(data, head);
            head = newNode;
            if (size == 0)
            {
                tail = head;
            }
        }
        else
        {
            Node<T> *current = head;
            for (int i = 0; i < index - 1; ++i)
            {
                current = current->next;
            }
            current->next = new Node<T>(data, current->next);
            if (index == size)
            {
                tail = current->next;
            }
        }
        size++;
    }

    T remove(int index)
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        Node<T> *toDelete;
        T data;
        if (index == 0)
        {
            toDelete = head;
            head = head->next;
            if (size == 1)
            {
                tail = nullptr;
            }
        }
        else
        {
            Node<T> *current = head;
            for (int i = 0; i < index - 1; ++i)
            {
                current = current->next;
            }
            toDelete = current->next;
            current->next = toDelete->next;
            if (index == size - 1)
            {
                tail = current;
            }
        }
        data = toDelete->data;
        delete toDelete;
        size--;
        return data;
    }

    void clear()
    {
        while (head != nullptr)
        {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    int getSize() const
    {
        return size;
    }

    Node<T> *getHead() const
    {
        return head;
    }
};