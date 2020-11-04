#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include <cmath>
using std::ostream;
using std::string;

// TODO: your code  goes here

class Item{
	
public:

	double latitude;
	double longitude;
	string ID;
	int availableTime;

public:
	Item(double latitude1,double longitude1,string ID1,int availableTime1):
		latitude(latitude1),longitude(longitude1),ID(ID1),availableTime(availableTime1){
	}	
	
	double getLatitude() const {
		return latitude;	
	}
	
	double getLongitude() const {
		return longitude;	
	}
	
	string getID() const {
		return ID;	
	}
	
	int getAvailableTime() const {
		return availableTime;
	}
	
	double distanceTo(const Item & p){
		double rlon1 = getLongitude() * (3.1415926/180);
		double rlon2 = p.getLongitude() * (3.1415926/180);
		double rlat1 = getLatitude() * (3.1415926/180);
		double rlat2 = p.getLatitude() * (3.1415926/180);
		double dlon = rlon2 - rlon1;
		double dlat = rlat2 - rlat1;
		double a = pow((sin(dlat/2)), 2) + cos(rlat1) * cos(rlat2) * pow((sin(dlon/2)), 2);
		double c = 2 * atan2( sqrt(a), sqrt(1-a) );
		double distance = 6373000 * c; 
		return distance;
	}
};
	
ostream & operator<<(ostream & o, const Item & i){
		o 	<<  "{"
			<<  i.getLatitude()
			<<	", "
			<<  i.getLongitude()
			<<  ", \""
			<<  i.getID()
			<<  "\", "
			<<	i.getAvailableTime()
			<<  "}";
		return o;
}








// don't write any code below this line

#endif

