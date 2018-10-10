/*
 * Link.h
 *
 *  Created on: 2018. 1. 29.
 *      Author: SDJ
 */

#ifndef OBJECTT_EDGE_H_
#define OBJECTT_EDGE_H_

#include <utils/config.h>
#include <list>
#include <map>


namespace SALT{
class Node;
class Connection;
class CellInterface;
class VehicleInterface;

class Link {
public:
	Link();
	Link(Node* _fromNode, Node* _toNode);
	Link(ID _ID, Node* _fromNode, Node* _toNode, int _numLanes, string _info);
	Link(ID _ID, Node* _fromNode, Node* _toNode, int _numLanes, string shape, string _info);
	Link(string _ID, string _fromNode, string _toNode, string _numLanes, string _info);
	virtual ~Link();

	void addNextLink(Link* _link, Connection* _connection);

	void addCell(int sectionIdx,int lane, CellInterface* _cell);

	CellInterface*& getCellByIndex(int sectionIdx, int lane);
	void determineCellSeries(VehicleInterface* veh, int departingCellRow, int departingCellCol, Link* nextLink);


	// functions that manages vehicle on link
	CellInterface* insertVehicle(VehicleInterface* veh, SALTTime t,int lane);
	CellInterface* pendVehicle(VehicleInterface* veh, SALTTime t,int lane);
	void appendOnVeh(VehicleInterface* veh);
	void removeOnVeh(VehicleInterface* veh);

	// traffic signal related functions
	TrafficSignalState getTrafficSignalState(Link* nextLink);
	Connection* getConnectionTo(Link* nextLink, int fromLane=-1);

	string getStatusString();

	// @Getter functions for rendering
	ID getID(){ return myID; }
	Node* getFromNode(){return myFromNode;	}
	Node* getToNode(){	return myToNode;	}
	// link[section_index][lane_index] is cell
	int getNumLane(){ return myNumLanes; }
	int getNumSection() const {	return myNumSections;	}

	Length getLength() const {	return myLength;	}

	//@brief returns the series of coordinates
	// every gap b\w coordinates is blank space(i.e. " ")
	// @case1 - no optional attribute 'shape' on "link" tag
	//		--> return "x1,y1 x2,y2" (fromNodeShape toNodeShape)
	// @case2 - optional attribute 'shape' exists
	//		--> return "x_from,y_from x_middle1,y_middle1 .... x_to,y_to" (fromNodeShape,myShape,toNodeShape)
	string getShape();


	void setNumSection(int _numSections = 0) {
		this->myNumSections = _numSections;
	}

	Speed getMySpeedLimit() const {	return mySpeedLimit;	}

	bool isExceptionalLink(){return myExceptionFlag;}
	void setAsExceptionalLink(){
		myExceptionFlag = true;
	}


private:
	ID myID;

	Node* myFromNode=0;
	Node* myToNode=0;

	Length myLength=-1;
	int myNumLanes=0;
	// TODO - input file doesn't have the below info (speed limit)
	Speed mySpeedLimit=16.6; // static - 60km/h ->16.6m/s

	map<Link*, list<Connection*>> myMapNextLink2Connection;
	map<Link*, list<int>> myMapNextLink2Lane;
	int myNumSections = 0;
	// too short links are exceptional links
	bool myExceptionFlag = false;

	// @usage: myCellMap[section][lane]
	// lane : rightmost->leftmost / section : upstream->downstream

	map<int,map<int,CellInterface*>> myCellMap;


	list<VehicleInterface*> myOnVehicleList;
public:
	string myShape="";
	string myInfo="";


};
}

#endif /* OBJECTT_EDGE_H_ */
