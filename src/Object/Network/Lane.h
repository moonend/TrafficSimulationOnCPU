///*
// * Lane.h
// *
// *  Created on: 2018. 1. 29.
// *      Author: SDJ
// */
//
//#ifndef OBJECTT_LANE_H_
//#define OBJECTT_LANE_H_
//
//#include <list>
//#include <string>
//
//#include "../../utils/config.h"
//#include "../Agent/VehicleInterface.h"
//
//class Link;
//
//class Lane {
//public:
//	Lane();
//	Lane(Link* _link, int _index=0, int _allowedSpeed=DEFAULT_SPEED, int _myCapacity=NO_LIMIT);
//	void addNextLane(Lane* _lane);
//	void addPrevLane(Lane* _lane);
//	virtual ~Lane();
//	std::string getStatusString();
////private:
//	Link* myLink=0;
//	int myIndex=-1; //in ��������, from right to zero (the rightmost one is 0)
//	Speed myAllowedSpeed=-1;
//	int myCapacity=-1;
//
//
//	std::list<Lane*> myNextLaneList;
//	std::list<Lane*> myPrevLaneList;
//
//	std::list<VehicleInterface*> myVehicleList;
//
//
//};
//
//#endif /* OBJECTT_LANE_H_ */
