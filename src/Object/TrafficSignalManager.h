/*
 * TrafficSignalManager.h
 *
 *  Created on: 2018. 1. 30.
 *      Author: SDJ
 */

#ifndef TRAFFICSIGNALMANAGER_H_
#define TRAFFICSIGNALMANAGER_H_

#include <Object/TrafficSignal/TrafficSignal.h>
#include <utils/config.h>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
namespace SALT{

class SimScenarioInfo;

class TrafficSignalManager {
private:
	static TrafficSignalManager* instance;

	TrafficSignalManager(){};
public:
	static TrafficSignalManager* getInstance();

public:
	virtual ~TrafficSignalManager();
	Result build(SimScenarioInfo* scenario);
	Result build(string const& _signal_file, const string& _input_type);
	Result initTrafficSignalList(const string& _signal_file);
	Result registerTrafficSignalToNode();
	void registerTrafficSignalToManager(const string& _nodeID, TrafficSignal* _ts);
	TrafficSignal* getTrafficSignalByNodeID(const string& _nodeID);


	//void insertSchedule(string _nodeID, string _scheduleID, TrafficSignalSchedule* _schedule);
	void update(SALTTime currentTime);
	void printStatus(SCOPE _scope=MACRO);


	string print(void);
private:
	list<TrafficSignal*> myTrafficSignalList;
	map<string, TrafficSignal*> myTrafficSignalMap;
	map<string, set<TrafficSignal*>> myTrafficSignalGroupMap;
};

ostream& operator << (ostream& strm, TrafficSignalManager& obj);
}

#endif /* TRAFFICSIGNALMANAGER_H_ */
