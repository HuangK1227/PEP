#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

#include <utility>

#include <initializer_list>


// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code goes here:

using namespace std;

template<typename T>
class LinkedList{

private:

    int elementNumber;
    Node<T>* head;
    Node<T>* tail;

public:

    LinkedList():
    head(nullptr),tail(nullptr),elementNumber(0)
    {}

   

    void push_front(const T item){
        Node<T>* newNode = new Node<T>(item);
        
		if(elementNumber == 0){
            head = newNode;
        }	
		else{
            newNode->next = head;
            head->previous = newNode;
            head = newNode;
           }
        elementNumber++;
    }

    T front(){
        return head->data;
    }

    void push_back(const T item){
        Node<T>* newNode = new Node<T>(item);
        
		if(elementNumber == 0){
             head = newNode;
        }	
        else{
            if(tail != nullptr){
                newNode->previous = tail;
                tail->next = newNode;
            }else{
                newNode->previous = head;
                head->next = newNode;
            }
            tail = newNode;
            }
            
        elementNumber++;
    }
    

    T back(){
        return tail->data;
    }

    int size(){
        return elementNumber;
    }

    NodeIterator<T> begin(){
        return NodeIterator<T>(head);
    }
    
    NodeIterator<T> end(){
        return NodeIterator<T>(nullptr);
    }

    ~LinkedList(){
        Node<T>* current = head;
        while(current != nullptr){
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head = 0;
    }    

    void reverse(){
        Node<T>* current = head;
        Node<T>* previous = nullptr;
        Node<T>* next = nullptr;
        while(current!=nullptr){
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        head = previous;
    }    

    LinkedList(initializer_list<T> l): elementNumber(0),tail(nullptr),head(nullptr){
	    for(T t : l){
		    push_back(t);
		}
	}

    NodeIterator<T> &insert(NodeIterator<T> & i,const T & e){
		T firstElement = i.current->data;
		i.current->data = e;
		Node<T> *secondElement = new Node<T>(firstElement);
		secondElement->next = i.current->next;
		secondElement->previous = i.current;
		i.current->next->previous = secondElement;
		i.current->next = secondElement;
		++elementNumber;
		return i;
	}

	NodeIterator<T> erase(const NodeIterator<T> & i) {
		Node<T>* nodeToErase = i.getNode();
		NodeIterator<T> newItr = i;
		if (!(head == nodeToErase) && !(tail == nodeToErase)){
			Node<T>* newPrevious = nodeToErase->previous;
			newPrevious->next = nodeToErase->next;
			newPrevious->next->previous = newPrevious;
			newItr = NodeIterator<T>(newPrevious->next);
		} else if (head == nodeToErase){
			head->next->previous = nullptr;
			head = head->next;
			newItr = NodeIterator<T>(head);
		} else if (tail == nodeToErase){
			tail->previous->next = nullptr;
			tail = tail->previous;
			newItr = NodeIterator<T>(nullptr);
		} else {
			head = nullptr;
			tail = nullptr;
			newItr = NodeIterator<T>(nullptr);
		}

		delete nodeToErase;
		elementNumber--;
		return newItr;
	}
};


// do not edit below this line

#endif
