#ifndef MAPOFITEMS_H
#define MAPOFITEMS_H

#include "Item.h"
#include <vector>
using std::vector; 
using namespace std;

// TODO: your code goes here

class MapOfItems{
private:

    vector<Item> items;

public:
   	MapOfItems(){ 
  
  
    } 
       
    void addItem(const Item & itemin){
           items.push_back(itemin);
    }

    int size(){
          return items.size();
    }
      
    const vector<Item> &getItems() const {
          return items;
    }

    

    Item* nextItem(Item * latVisited, const vector<Item*> & notVisited, double & tourTime, const double walkingSpeed){
        int tempTime = 3600;
        Item* next = latVisited;

       	for (int j = 0; j < notVisited.size(); j++){
            int distance = latVisited->distanceTo(*notVisited[j]);
     	int WalkTime = distance/walkingSpeed;
     	int Thattime = WalkTime + tourTime;
     	if(Thattime >notVisited[j]->getAvailableTime() + 900){
      		continue;
     	}
     	if(Thattime < notVisited[j]->getAvailableTime()){
      		Thattime =  notVisited[j]->getAvailableTime();
     	}
     	if(Thattime <tempTime){
        	tempTime = Thattime;
       		next =  notVisited[j];
     	}    
    }
    tourTime = tempTime;

    return next;

    }

    int getIndex(const vector<Item*> & notVisited, const Item * item)  {
        int index;
        for (int i = 0; i < notVisited.size(); ++i) {
    		if (item->getID() == notVisited[i]->getID()) {
    			return index = i;
   			}
  		}
 	}

    bool Visited(const vector<Item*>  tour, const Item * item) const {
      	for (int i = 0; i < tour.size(); ++i) {
    		if (item->getID() == tour[i]->getID()) {
    			return true;
   			}
  		}
  		return false;
 	}

	vector<Item*> getTour (const double  walkingSpeed) {
        vector<Item*> tour;
   		vector<Item*> nonVisitedList;


   		for(int i = 0; i < items.size(); i++){ 
    		nonVisitedList.push_back(&(items[i])); 
    	} 
    	tour.push_back(nonVisitedList[0]); 


   		double currentTime = nonVisitedList[0]->getAvailableTime();


    	Item* currentItem = nonVisitedList[0];
   		nonVisitedList.erase(nonVisitedList.begin());
         

         
 		for (int i = 1; i < items.size() && currentTime < 3600; i++){
           
    		currentItem = nextItem(currentItem,nonVisitedList,currentTime, walkingSpeed);
              
    		if(!Visited(tour,currentItem) ){
    			tour.push_back(currentItem);
    		}
    		nonVisitedList.erase(nonVisitedList.begin() + (getIndex(nonVisitedList, currentItem)));
		}
  			return tour;
   	}
};



// don't write any code below this line

#endif