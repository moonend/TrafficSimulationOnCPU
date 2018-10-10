/*
 * TrafficSignal.h
 *
 *  Created on: 2018. 1. 29.
 *      Author: SDJ
 */

#ifndef OBJECTT_TRAFFICSIGNAL_H_
#define OBJECTT_TRAFFICSIGNAL_H_

#include <utils/config.h>
#include <map>
#include <string>


namespace SALT{
class Link;
class Node;
class Connection;
class TrafficSignalSchedule;

class TrafficSignal {
public:
	TrafficSignal();
	virtual ~TrafficSignal();

	//// functions to set member variables
	void setMyNode(Node* myNode = NULL) {
		this->myNode = myNode;
	}
	void insertSchedule(std::string id, TrafficSignalSchedule* schedule);
	// plan := (startingTime, schedule)
	void insertPlan(std::string _startTime, std::string scheduleID);
	void insertPlan(SALTTime startTime, TrafficSignalSchedule* schedule);

	void insertLinkLinkIndex(Link* from, Link* to, int index);

	void initTrafficSignalStatus(std::string defaultScheduleID);

	void setScheduleState(SALTTime setTime);

	// TODO - @brief  finishConstruct
	// set myNode to the node found from id
	// set myGroup, currentPhase, myNext~~~
	void finishConstruct();

	//// functions to get info
	Node* getMyNode()  {	return myNode;	}
	int getLinkLinkIndex(Link* from, Link* to);
	std::string getStatusString();
	// @brief return min(switchTime | switchTime>givenTime)
	SALTTime extractNextScheduleSwitchTime(SALTTime givenTime);

	//// functions to get current status
	TrafficSignalState getTrafficSignalState(Link* fromLink, Link* toLink);

	//// functions to update traffic signal
	// @brief determine update based on nextSwitchTime and currentTime
	void tryUpdate(SALTTime currentTime);
	void executeUpdateSchedule(SALTTime updateTime);
	void executeUpdatePhase(SALTTime updateTime);

	//[test][Analyzer] temporary
	std::string getCurTrafficSignalState(){
		return myCurrentSignalState;
	}





private:
	Node* myNode=NULL;
	// TODO - group....
//	std::set<TrafficSignal*>* myGroup=NULL;

	// Time of Day Plan
	std::map<std::string, TrafficSignalSchedule*> myScheduleMap; // (schedule name, schedule itself)
	std::map<SALTTime, TrafficSignalSchedule*> myTODPlan; //ToD Plan (schedule starting time, schedule itself)

	// Connection Control
	std::map<Connection*, int> myMapConnectionIndex;
	std::map<Link*,std::map<Link*,int>> myLinkLinkIndex;

	// schedule - cur/nextSwitchTime
	TrafficSignalSchedule* myCurrentSchedule=NULL; //
	SALTTime myNextScheduleTime=-1;

	// phase - last/cur/nextSwitchTime
	SALTTime myLastPhaseSwitchTime=-1;
	int myCurrentPhaseIndex = -1;
	SALTTime myNextPhaseTime=-1;

	// determined signal state
	int myCurrentPhaseNum = 0;
	std::string myCurrentSignalState="";
};
}
#endif /* OBJECTT_TRAFFICSIGNAL_H_ */
