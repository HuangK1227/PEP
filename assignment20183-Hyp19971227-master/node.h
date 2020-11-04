#ifndef NODE_H
#define NODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code for the Node class goes here:
// (Note the 'NodeIterator' class will report lots of errors until Node exists




template<typename T>
class Node{

public:

    T data;
    Node<T>* next;
    Node<T>* previous;

    Node(T dataIn):
    data(dataIn),next(nullptr),previous(nullptr){
    }
};

//create a class Node above

template<typename T>
class NodeIterator {
  
public:
    
    Node<T>* current;
    

    NodeIterator(Node<T>* currentIn)
        : current(currentIn) {        
    }

    T & operator*() {
        return current->data;
    }
    // TODO: complete the code for NodeIterator here

    NodeIterator<T> operator++(){
        
        current = current ->next;
        
        return *this;
    }

    bool operator==(const NodeIterator<T> & i){
        if(current == nullptr || i.current == nullptr){
            return false;
        }
        else{
            return (current == i.current);
        }
    }

    bool operator!=(const NodeIterator<T> & i){
        if (current == nullptr){
            return false;
        }
        else{
            return (current != i.current);
        }
    }

    Node<T>* getNode() const {
        return current;
    }
};

// do not edit below this line


#endif
