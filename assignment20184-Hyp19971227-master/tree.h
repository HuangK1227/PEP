#ifndef TREE_H
#define TREE_H

#include "treenode.h"

// TODO your code goes here:
template<typename T>
class BinarySearchTree{

private:
    unique_ptr<TreeNode<T> > root;
    int count = 0;

public:
    BinarySearchTree()
    {

    }

    void write(ostream & h) const {
        root->write(h);
    }

     TreeNode<T>* insert( T dataIn)   {
        TreeNode<T>* foundNode = find(dataIn);

        if(foundNode){ 
            return foundNode; 
        }
		if(!root) {
    		TreeNode<T>* trial = new TreeNode<T>(dataIn);
		
			root.reset(trial);

			++count;

			return trial;


		} else { 


	    TreeNode<T>* compareNode = root.get();


	    TreeNode<T>* parent = nullptr;

	    while(compareNode)

	    {
	    	   parent = compareNode;
	         
	         if(dataIn < compareNode->data) {

	         	compareNode = compareNode->leftChild.get();

	         }	 else {

	         	compareNode = compareNode->rightChild.get();
	         }

	    }
	    if(dataIn < parent->data) {

	    	TreeNode<T>* returnTo =  new TreeNode<T>(dataIn);
	      
	         parent->setLeftChild( returnTo );

	         ++count;

	         if(parent->parent) {

	         	if(parent->parent->rightChild.get() == parent) {

	         		TreeNode<T>* lastelem = parent->leftChild.release();
	         		
	         		TreeNode<T>* subParent = parent->parent->rightChild.release();

	         		parent->parent->setRightChild(lastelem);

	         		lastelem->setRightChild(subParent);


	         		TreeNode<T>*  newParent = root.get()->rightChild.release();
	         		TreeNode<T>* oldRoot = root.release();
	         		TreeNode<T>* last  = parent->rightChild.release();

	         		newParent->parent = nullptr;

	         		root.reset(newParent);

	         		newParent->setLeftChild(oldRoot);


	         	}


		         if(balanceFactor(parent->parent) == 2) {
			        if(count == 3) {

		         		TreeNode<T>*  newParent = root.get()->leftChild.release();
		         		TreeNode<T>* oldRoot = root.release();
		         		TreeNode<T>* last  = parent->leftChild.release();

		         		newParent->parent = nullptr;
		         		last->parent = nullptr;

		         		root.reset(newParent);

		         		root.get()->setLeftChild(last);
		         		root.get()->setRightChild(oldRoot); 


		         	} else if(count > 3)  {


		         		if(balanceFactor(parent->parent) == 2) {

				         	TreeNode<T>* newParent = parent->parent->leftChild.release();

			         		TreeNode<T>* grand = parent->parent->parent->leftChild.release();

			         		TreeNode<T>* last = parent->leftChild.release();

			         	
			         		parent->parent->parent->setLeftChild(newParent);

			         		newParent->setLeftChild(last);

			         		newParent->setRightChild(grand); 


		         		}

			         }
		         }
	        }

	         return returnTo;


	    } else {

	    	TreeNode<T>* toReturn =  new TreeNode<T>(dataIn);

	    	if( parent->data < dataIn) {

	         parent->setRightChild( toReturn );

	         ++count;


	         if(parent->parent) {
	         	if(parent->parent->leftChild.get() == parent) {
		         		TreeNode<T>* subParent = parent->parent->leftChild.release();
		         		TreeNode<T>* lastItem = parent->rightChild.release();

						parent->parent->setLeftChild(lastItem);
		         		lastItem->setLeftChild(subParent);

		         		subParent->rightChild.reset(nullptr);

		         		TreeNode<T>*  newParent = root.get()->leftChild.release();
		         		TreeNode<T>* oldRoot = root.release();
		         		TreeNode<T>* last  = parent->leftChild.release();

		         		newParent->parent = nullptr;
		         		
                        root.reset(newParent);
                        root.get()->setRightChild(oldRoot); 
	         	}

	         

	         if( balanceFactor(parent->parent) == -2) {


	         	if(count == 3) {
	         		TreeNode<T>*  newParent = root.get()->rightChild.release();
	         		TreeNode<T>* oldRoot = root.release();
	         		TreeNode<T>* last  = parent->rightChild.release();

	         		newParent->parent = nullptr;
	         		last->parent = nullptr;

	         		root.reset(newParent);

	         		newParent->setLeftChild(oldRoot);
	         		newParent->setRightChild(last); 

	         	} else if(count > 3)  {

	         		TreeNode<T>* newParent = parent->parent->rightChild.release();


	         		TreeNode<T>* grand = parent->parent->parent->rightChild.release();

	         		TreeNode<T>* last = parent->rightChild.release();

	         	
	         		parent->parent->parent->setRightChild(newParent);

	         		newParent->setLeftChild(grand);

	         		newParent->setRightChild(last); 

		         		}
	         		}

	         		return toReturn;  
 				}

		}
	  }
	}

	return foundNode;
}

    TreeNode<T>* find( T  dataIn) const {
        TreeNode<T>* current = root.get();
        while (current != nullptr) {
            if (dataIn < current->data) {
                if (current->leftChild) {
                    current = current->leftChild.get();
                } else {
                    return nullptr;
                }
            } else if (current->data < dataIn) {
                if (current->rightChild) {
                    current = current->rightChild.get();
                } else {
                    return nullptr;
                }
            } else {
                return current;
            }
        }
        return nullptr;
    }

     TreeNodeIterator<T> begin() {

    	if(!root) {  TreeNodeIterator<T> toReturn(nullptr);   return toReturn;  }

    	TreeNode<T>* temp = nullptr;

    	TreeNode<T>* current = root.get();

    	TreeNode<T>* something = nullptr;
    	

    	if(current->leftChild) {

    		temp =  current->leftChild.get();
    		something = current->leftChild.get();


    	} else {

    		temp = current;

    		TreeNodeIterator<T> toReturn(temp);

    		return toReturn;

    	}

    	 
    	while(something->leftChild) {	

    		something = something->leftChild.get();
    	
    	} 

    	temp = something;


    	TreeNodeIterator<T> toReturn(temp);

    	return toReturn;


    }


    TreeNodeIterator<T> end()  {

    	TreeNodeIterator<T> toReturn(nullptr);

    	return toReturn;


    }

    int maxDepth() {

    	if(!root) {return 0;} else {

    	return root.get()->maxDepth();


    	}

    }


    int balanceFactor(TreeNode<T>* node ) const {
 
 		int max = 0;
 		int left = 0;
 		int right = 0;

    	if(node->leftChild.get()) {

    		left = node->leftChild.get()->maxDepth();
    	}

    	if(node->rightChild.get()) {

    		right = node->rightChild.get()->maxDepth();
    	}

    	max = left - right;

    	return max;

    }

  

    TreeNode<T>* getRoot() const  {

    	return root.get();

    }



};

// do not edit below this line

#endif