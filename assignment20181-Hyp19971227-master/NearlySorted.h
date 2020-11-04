#ifndef NEARLYSORTED_H
#define NEARLYSORTED_H


#include <vector>
using std::vector;

/** @brief Class that describes how to sort a nearly-sorted vector */
class HowToSort {
protected:
    
    /** @brief The index of the first element to use */
    int firstElement;
    
    /** @brief The index of the second element to use */
    int secondElement;
    
    /** @brief If true, firstElement and secondElement should be swapped; if false, the range of elements should be reversed */
    bool swapThem;
    
public:
    
    /** @brief Default constructor.
     * 
     * This assumes that we can't sort the vector by swapping/reversing a range -- it sets both elements
     * to have an index -1.
     */
    HowToSort() 
      : firstElement(-1),
        secondElement(-1),
        swapThem(false) {
    }
    
    /** @brief The actual constructor: use this to define how to sort a nearly-sorted vector
     * 
     * @param firstElementIn   The first element to use
     * @param secondElementIn  The second element to use
     * @param swapThemIn       If true, swap firstElementIn and secondElementIn; if false, reverse the range of elements
     */
    HowToSort(const int firstElementIn, const int secondElementIn,
              const bool swapThemIn)
      : firstElement(firstElementIn),
        secondElement(secondElementIn),
        swapThem(swapThemIn) {
    }
    
    /** @brief Returns false if no way to sort the vector could be found (i.e. if firstElement == -1) */
    bool canBeMadeSorted() const {
        return (firstElement != -1);
    }
    
    /** @brief Accessor function -- get the first element to use */
    int getFirstElement() const {
        return firstElement;
    }

    /** @brief Accessor function -- get the second element to use */
    int getSecondElement() const {
        return secondElement;
    }

    /** @brief If true, the element indices denote a swap.  If false, they denote a range reversal. */
    bool isASwap() const {
        return swapThem;
    }
    
};

// TODO your code goes here:
bool isSorted(vector<int> v){
    int i = 0;
    while( i < v.size()-1){
        
        if(v[i]>v[i+1]){
            return false;
        }
        i++;
    }
    return true;
}

HowToSort nearlySorted(vector<int> v){
    if(isSorted(v)){
        return HowToSort(0,0,true);
    }else{
        int head = 0;
        int tail = 0;   
        int range = 0;

        while(v[head]<v[head+1]){
            head++;
            tail = head;
        }
        for(int i = tail;i<v.size();i++){
            if(v[tail]<v[i]){
                tail = i-1;
            }
        }

        int k = tail;
        for(int i = head;i<k;i++){
            range++;
            int swapNumber = v[i];
            v[i] = v[k];
            v[k] = swapNumber;
            k--;
        }
        if(isSorted(v) && range < 2){
            return HowToSort(head,tail,true);
        }
        else if( isSorted(v) && range>=2){
            return HowToSort(head,tail,false);
        }
        else{
            return HowToSort();
        }
    }

}
 



// Don't write any code below this line

#endif
