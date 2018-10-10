/*
 * ModelSimpleMeso.h
 *
 *  Created on: 2018. 3. 29.
 *      Author: SDJ
 */

#ifndef MODELSIMPLEMESO_H_
#define MODELSIMPLEMESO_H_

#include <Controller/ModelInterface.h>
#include <utils/config.h>
namespace SALT{
namespace version1{

class Model : public SALT::ModelInterface{
public:
	Model(NetworkManager* _nm, VehicleManager* _vm, TrafficSignalManager* _tsm, Analyzer* _az) : ModelInterface(_nm,_vm,_tsm,_az){};
	virtual ~Model();
	virtual void update(SALTTime _step);
	virtual void print(SALTTime _step,SCOPE _scope);
	virtual OutputStepSet* getOutputStepSet(SALTTime _step);
	virtual OutputPeriodicRoadSet* getOutputPeriodicRoad(SALTTime _step);
	void departVehicle(SALTTime _step);


	void planVehicleInsertion(SALTTime _step);
	void executeVehicleInsertion(SALTTime _step);
	void intraCellTransmission(SALTTime _step);
	void planInterCellAndIntraLinkTransmission(SALTTime _step);
	void executeInterCellAndIntraLinkTransmission(SALTTime _step);
	void planInterCellAndInterLinkTransmission(SALTTime _step);
	void executeInterCellAndInterLinkTransmission(SALTTime _step);
	void rollbackInterCellTransmission(SALTTime _step);
	void popVehicle(SALTTime _step);

};
}

}
#endif /* MODELSIMPLEMESO_H_ */
