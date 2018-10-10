/*
 * ModelSimpleMeso.h
 *
 *  Created on: 2018. 4. 24.
 *      Author: SDJ
 */

#ifndef MODELMESOVERSION2_H_
#define MODELMESOVERSION2_H_

#include <Controller/ModelInterface.h>
#include <utils/config.h>
namespace SALT{
namespace version2{

class Model : public SALT::ModelInterface{
public:
	Model(NetworkManager* _nm, VehicleManager* _vm, TrafficSignalManager* _tsm,  Analyzer* _az) : ModelInterface(_nm,_vm,_tsm,_az){};
	virtual ~Model();
	virtual void update(SALTTime _step);
	virtual void print(SALTTime _step, SCOPE _scope);
	virtual OutputStepSet* getOutputStepSet(SALTTime _step);
	virtual OutputPeriodicRoadSet* getOutputPeriodicRoad(SALTTime _step);


	void planVehicleInsertion(SALTTime _step);

};
}

}
#endif /* MODELMESOVERSION2_H_ */
