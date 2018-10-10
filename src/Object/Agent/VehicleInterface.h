/*
 * VehicleInterface.h
 *
 *  Created on: 2018. 3. 13.
 *      Author: SDJ
 */

#ifndef VEHICLEINTERFACE_H_
#define VEHICLEINTERFACE_H_

#include <utils/config.h>
#include <iostream>
#include <list>
#include <string>
#include <utility>


namespace SALT{
class Route;
class CellInterface;
class Link;

class VehicleInterface {
public:
	VehicleInterface();
	VehicleInterface(Route* _route, string _departTime, int _routeIndex,  ID _ID);
	virtual ~VehicleInterface();

	// update function
	virtual void updateStatus(SALTTime nextTime)=0;
	void updateStatusWhenNewCell();
	void updateStatusWhenNewLink();
	void handleStartingLinkException();

	void clearCellSeries();
	void appendCellPosition(int section, int lane);
	const pair<int, int>& getNextCellPosition();

	// getter / setter
	ID& getMyName()  {	return myID; }
	string& getMyShape()  {	return myShape;	}
	SALTTime getMyDepartTime() const {	return myDepartTime;}
	int getMyCellIndex() const {return myCellIndex;	}

	Link* getLink(int linkIndex);
	Link* getRouteDepartingLink();
//	CellInterface* getRouteDepartingCell();
	Link* getNextValidLink();

	Link* getCurrentLink();
//	CellInterface* getCurrentCell();

	Link* getNextLink(Link* link);
	Link* getNextLink();


	void setMyCellIndex(int myCellIndex = -1) {
		this->myCellIndex = myCellIndex;
	}

	void setMyLinkIndex(int myLinkIndex = -1) {
		// FIXME range check
		this->myLinkIndex = myLinkIndex;
	}

	// utility
	string print(void);
	string getStatusString(void);

	int getMyRouteDepartingLaneIndex() const {
		return myRouteDepartingLaneIndex;
	}

	int getMyRouteDepartingSectionIndex() const {
		return myRouteDepartingSectionIndex;
	}

protected:
	//	(constant) fixed values during simulation
public:

	Route* myRoute=0;
	string myRouteString="";
	ID myID;
	string myType="";
	string myShape="";
	// TODO - input file doesn't have the below info(length, max speed)
	Length myLength = 5.0; // static 5 meter
	// max speed is deprecated because
	// almost vehicle can move with 100km/s, and
	// in urban city, speed limits are under 60km/s
//	Speed myMaxSpeed = 16.6; // static 60km/h -> 16.6m/s


	// (constant) fixed values during sub-simulation
	SALTTime myDepartTime=-1;
	int myRouteDepartingLinkIndex = -1;
	int myRouteDepartingSectionIndex = -1;
	int myRouteDepartingLaneIndex = -1;


	// (variable) status - position, speed
	int myLinkIndex = -1; // [0,myRoute.size()]
	int myCellIndex = -1; // [0,myCellSeries.size()] //myCellSeries.size()<=link's #sections
	list<pair<int,int>> myCellSeries;
	Speed mySpeed=-1;
};
ostream& operator << (ostream& strm, VehicleInterface& obj);
}
#endif /* VEHICLEINTERFACE_H_ */
