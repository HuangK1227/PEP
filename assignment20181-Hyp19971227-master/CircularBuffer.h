#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

// NB: Do not add any extra #include statements to this file
#include "SimpleVector.h"
#include <iostream>


/** TODO: complete the definition of the class CircularBuffer here
 *
 * Its constructor should take the size of the buffer as an argument
 *
 * It needs to have the functions:
 * - count() which returns how many things are in the buffer
 * - full() which returns true iff the buffer is full
 * - add() which takes an element and adds it to the buffer (you can assume the buffer is not full)
 * - remove() which removes the next element from the buffer (you can assume the buffer is not empty)
 */
class CircularBuffer {

private:

    SimpleVector<char> buffer;
    int indexOfFirst;
    int indexOfLast;
    int size;
    int currentLength;

public:
    
    CircularBuffer(const int maxNumber):
    size(maxNumber),buffer(maxNumber),indexOfFirst(0),indexOfLast(0),currentLength(0)
    {
    }

    int count(){
        return currentLength; 
    }

    bool full(){
        if(count() == size){
            return true;
        }
        else{
            return false;
        }
    }

    char add(const char newCharacter){
        if(!full()){
            buffer[indexOfLast] = newCharacter;
            indexOfLast++;
            currentLength++;
            return newCharacter;
        }
        else{
            std::cout<<"buffer is full"<<std::endl;
            return 0;
        }
    }

    char remove(){
        if(count() > 0){
            char removedCharacter = buffer[indexOfFirst];
            buffer[indexOfFirst] = 0;
            indexOfFirst++;
            currentLength--;
            return removedCharacter;
        }
        else{
            std::cout<<"buffer is empty"<<std::endl;
            return 0;
        }
    }
};


// don't write any code below this line

#endif
