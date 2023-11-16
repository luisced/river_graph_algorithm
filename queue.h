#pragma once
#include <iostream>
#include "node.h"

template <typename T>
class Queue
{
private:
    Node<T> *front;
    Node<T> *rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    ~Queue()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }

    void enqueue(T data)
    {
        Node<T> *newNode = new Node<T>(data);
        if (isEmpty())
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    T dequeue()
    {
        if (isEmpty())
        {
            throw std::out_of_range("Queue is empty");
        }
        Node<T> *temp = front;
        T data = front->data;
        front = front->next;
        if (front == nullptr)
        {
            rear = nullptr;
        }
        delete temp;
        size--;
        return data;
    }

    T peek() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("Queue is empty");
        }
        return front->data;
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    int getSize() const
    {
        return size;
    }
};
