/*
 * VehicleManager.h
 *
 *  Created on: 2018. 1. 29.
 *      Author: SDJ
 */

#ifndef OBJECTT_VEHICLEMANAGER_H_
#define OBJECTT_VEHICLEMANAGER_H_

#include <Object/Agent/VehicleInterface.h>
#include <utils/config.h>
#include <iostream>
#include <list>
#include <string>


namespace SALT{
class Link;
class SimScenarioInfo;


class VehicleManager {
private:
	static VehicleManager* instance;

	VehicleManager(){};

public:
	static VehicleManager* getInstance();

public:
	Result build(SimScenarioInfo* scenario);
	Result build(string const& _route_file, const string& _input_type="SALT");
	virtual ~VehicleManager();
	Route* buildRoute(string _linkList, string _departLane,string _offsetOnStartingLink);

	string print(void);
	void printStatus(SCOPE _scope=MACRO);


	void fillDepartingVehicleList(SALTTime curStep, list<VehicleInterface*>& departingVehicleList);
	Link* getDepartingLink(VehicleInterface* veh);
	void addStandByVehicle(VehicleInterface* veh);
	void appendRunningVeh(VehicleInterface* veh);


	void appendArrivedVeh(VehicleInterface* veh);

private:
	list<VehicleInterface*> myStandByVehicleList;
//	list<VehicleInterface*> myPendingVehicleList;
//
	list<VehicleInterface*> myRunningList;
//
//	list<VehicleInterface*> myExceptionList;
	list<VehicleInterface*> myArrivedVehicleList;

};


ostream& operator << (ostream& strm, VehicleManager& obj);
}
#endif /* OBJECTT_VEHICLEMANAGER_H_ */
