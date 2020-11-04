#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include <memory>
using std::unique_ptr;

#include <utility>
using std::pair;

// TODO your code for the TreeNode class goes here:
template<typename T>
class TreeNode{

public:
    T data;
    unique_ptr<TreeNode> leftChild;
    unique_ptr<TreeNode> rightChild;
    TreeNode<T>* parent;

    TreeNode(T dataIn):
    data(dataIn),parent(nullptr){

    }

    void setLeftChild(TreeNode* child){
        leftChild.reset(child);
        child->parent = this;
    }
    
    void setRightChild(TreeNode* child){
        rightChild.reset(child);
        child->parent = this;
    }
    
    const void write( ostream & h){
        if(leftChild != nullptr){
            leftChild->write(h);
        }
        h<<' '<<data<<' '; 
        if(rightChild != nullptr){
            rightChild->write(h);
        }
    }

    T getData() const{
        return data;
   		}

	int maxDepth(){
		int depth = 1;
		if(leftChild || rightChild){
	    	int left = 0;
			int right = 0;
			if(leftChild){
				left = leftChild.get()->maxDepth();
			}
			if(rightChild){
				right = rightChild.get()->maxDepth();
			}

			if(left > right){
				depth = 1 + left;
			}
			else{
				depth = 1+right;
			}
		}
			return depth;
	}
};

template<typename T>
class TreeNodeIterator {

private:

    TreeNode<T>* current;

public:

    TreeNodeIterator(TreeNode<T>* currentIn)
        : current(currentIn) {
    }

    T & operator*() {
        return current->data;
    }

    bool operator==(const TreeNodeIterator<T> & secondItr){
        return current == secondItr.current;
    }

    bool operator!=(const TreeNodeIterator<T> & secondItr){
        return current != secondItr.current;
    }

  	void operator++() {
        TreeNode<T>* mostLeft = current;
        TreeNode<T>* curParent = current;        
        if (current->rightChild.get()){
            current = current->rightChild.get();
            mostLeft = getLeft(current);

            if (mostLeft != current){
                current = mostLeft;
            } 
        } else if (current->parent) {

            T x = current->getData();
            curParent = current->parent;
            T y = curParent->getData();

            while(y < x){

                if (curParent->parent) {
                    curParent = curParent->parent;
                    y = curParent->getData();
                } else {
                    y = x;
                    current = nullptr;
                }
            }
            if (x < y){
                current = curParent;
            }
        } else {
            current = nullptr;
        }        
    }

    TreeNode<T>* getLeft(TreeNode<T>* root) {
        TreeNode<T>* currentNode = root;
        while(currentNode->leftChild.get()) {
            currentNode = currentNode->leftChild.get();
        }
        return currentNode;
    }
};
    
// do not edit below this line

#endif
