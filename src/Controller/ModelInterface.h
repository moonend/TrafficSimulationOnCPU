/*
 * ModelInterface.h
 *
 *  Created on: 2018. 3. 29.
 *      Author: SDJ
 */

#ifndef MODELINTERFACE_H_
#define MODELINTERFACE_H_

#include <utils/config.h>

namespace SALT{
class Analyzer;
class OutputPeriodicRoadSet;
class OutputStepSet;

class NetworkManager;
class TrafficSignalManager;
class VehicleManager;

//#include "../Object/NetworkManager.h"
//#include "../Object/VehicleManager.h"
//#include "../Object/TrafficSignalManager.h"
//#include "../Object/Analyzer.h"


class ModelInterface {
public:
	ModelInterface(NetworkManager* _nm, VehicleManager* _vm, TrafficSignalManager* _tsm, Analyzer* _az) : myNetworkManager(_nm), myVehicleManager(_vm), myTrafficSignalManager(_tsm),  myAnalyzer(_az){};
	virtual ~ModelInterface()=0;
	virtual void update(SALTTime _step)=0;
	virtual void print(SALTTime _step,SCOPE _scope=MACRO)=0;
	virtual OutputStepSet* getOutputStepSet(SALTTime _step)=0;
	virtual OutputPeriodicRoadSet* getOutputPeriodicRoad(SALTTime _step)=0;
protected:
	NetworkManager* myNetworkManager;
	VehicleManager* myVehicleManager;
	TrafficSignalManager* myTrafficSignalManager;
	Analyzer* myAnalyzer;
};
}
#endif /* MODELINTERFACE_H_ */
