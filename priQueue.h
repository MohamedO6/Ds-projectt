#pragma once
#include "priNode.h"


//This class impelements the priority queue as a sorted list (Linked List)
//The item with highest priority is at the front of the queue
template <typename T>
class priQueue
{
    priNode<T>* head;
public:
    priQueue() : head(nullptr) {}

    ~priQueue() {
        T tmp;
        int p;
        while (dequeue(tmp, p));
    }
    priQueue<T>& operator=(const priQueue<T>& rhs)
    {
        if (this == &rhs) return *this;
        T item;
        int pri;
        while (dequeue(item, pri)) {}

        priNode<T>* curr = rhs.head;
        while (curr != nullptr)
        {
            enqueue(curr->getItem(pri), curr->getPri());
            curr = curr->getNext();
        }

        return *this;
    }
    //insert the new node in its correct position according to its priority
    void enqueue(const T& data, int priority) {
        priNode<T>* newNode = new priNode<T>(data, priority);

        if (head == nullptr || priority > head->getPri()) {

            newNode->setNext(head);
            head = newNode;
            return;
        }

        priNode<T>* current = head;
        while (current->getNext() && priority <= current->getNext()->getPri()) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
    }

    bool dequeue(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        priNode<T>* temp = head;
        head = head->getNext();
        return true;
    }

    bool peek(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem();
        pri = head->getPri();
        return true;
    }

    bool isEmpty() const {
        return head == nullptr;
    }
	int size() const {
		int count = 0;
		priNode<T>* current = head;
		while (current != nullptr) {
			count++;
			current = current->getNext();
		}
		return count;
	}
    void clear()
    {
        T x;
        int p;
        if (head == nullptr) return;
        while (!isEmpty())
        {
            dequeue(x , p);
        }
    }
};
