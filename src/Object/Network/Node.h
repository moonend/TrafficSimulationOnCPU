/*
 * Node.h
 *
 *  Created on: 2018. 1. 29.
 *      Author: SDJ
 */

#ifndef OBJECTT_NODE_H_
#define OBJECTT_NODE_H_

#include <utils/config.h>


namespace SALT{
class TrafficSignal;
class Node {
public:
	Node() {};
	Node(ID _ID, TypeName _type="priority") : myID(_ID), myIntersectionType(_type){};
	Node(ID _ID, float x=0,float y=0, TypeName _type="priority");
	virtual ~Node();
	ID getID(){ return myID; };
	string getStatusString();
	float computeDistance(const Node & v) const;

	const Position& getMyLocation() const {
		return myLocation;
	}

	TrafficSignal* getMyTrafficSignal() {
		return myTrafficSignal;
	}

	void setMyTrafficSignal(TrafficSignal* ts) {
		myTrafficSignal=ts;
	}

	//@brief: return "x,y"
	string getShape();


private:

	ID myID;
	Position myLocation;
	TypeName myIntersectionType;
	TypeName myRole;
	TrafficSignal* myTrafficSignal=0;

};
}
#endif /* OBJECTT_NODE_H_ */
