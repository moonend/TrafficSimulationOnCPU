/*
 * Connection.h
 *
 *  Created on: 2018. 1. 29.
 *      Author: SDJ
 */

#ifndef OBJECTT_CONNECTION_H_
#define OBJECTT_CONNECTION_H_

#include <list>
#include <string>
#include <utils/config.h>


namespace SALT{

class Node;
class Link;
class CellInterface;
class VehicleInterface;

class Connection {
public:
	Connection();
//	Connection(Lane* _fromLane, Lane* _toLane);
	Connection(Link* _from, Link* _to, int _myFromLane, int _myToLane, string info="");
	virtual ~Connection();

	Link* getMyFrom() {
		return myFromLink;
	}
	Link* getMyTo() {
		return myToLink;
	}

	int getMyFromLane() {
		return myFromLane;
	}
	int getMyToLane() {
		return myToLane;
	}



private:
	Link* myFromLink=0;
	Link* myToLink=0;
	int myFromLane=-1;
	int myToLane=-1;

	Node* myNode=0;

//	Lane* myFromLaneInstance;
//	Lane* myToLaneInstance;

	CellInterface* myFromCell=0;
	CellInterface* myToCell=0;


	list<VehicleInterface*> myOnVehicleList;
	list<VehicleInterface*> myWaitingVehicleList;
public:
	string myInfo="";
};
}
#endif /* OBJECTT_CONNECTION_H_ */
