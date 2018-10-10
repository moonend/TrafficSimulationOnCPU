/*
 * SimulationController.h
 *
 *  Created on: 2018. 3. 29.
 *      Author: SDJ
 */

#ifndef SIMULATIONCONTROLLER_H_
#define SIMULATIONCONTROLLER_H_


#include <utils/config.h>
#include <string>

#include "Object/Output/OutputStepSet.h"
#include "Object/Output/OutputPeriodicRoadSet.h"

#include "Object/NetworkManager.h"
#include "Object/VehicleManager.h"
#include "Object/TrafficSignalManager.h"

namespace SALT{



class SimScenarioInfo;
class ModelInterface;


class SimulationController {
public:
	SimulationController(){};
	virtual ~SimulationController();

	// @brief: read configuration file and load simulation env and agent
	Result configureSimulation(string configFile);


	//////////////////////////////////////////////////////////////////
	// @Functions that update the state of simulation env and agent //
	//////////////////////////////////////////////////////////////////

	// @brief: do actual update the state of agent, enviroment and etc (e.g. myCurrentStep)
	void doSimulationStep(SALTTime currentStep);

	// @brief: iterate simulationStep until _end
	void runSimulation(SALTTime _end);


	//////////////////////////////////////////////////
	// @Functions that control simulation execution //
	//////////////////////////////////////////////////

	// @brief: start simulation by calling runSimulation(endTime from scenario)
	void start();

	// @brief: pause simulation by changing simulation state to SIMULATION_PAUSED
	void pause();

	// @brief: resume (paused) simulation by calling runSimulation(endTime from scenario)
	void resume();

	// @brief: stop simulation by changing simulation state to SIMULATION_END
	void stop();


	///////////////////////////////////////////////////
	// @Functions that get the result of simulation. //
	///////////////////////////////////////////////////

	// @brief: get the snapshot result of current state of simulation agents and environments.
	// Refer to OutputStepSet class
	OutputStepSet* getStepResult(SALTTime currentStep);

	// @brief: get the periodic result (e.g. average speed for 5 mins) of simulation.
	// Refer to OutputPeriodicRoadSet class
	OutputPeriodicRoadSet* getPeriodicResult(SALTTime currentStep);


	/////////////////////////
	// @ Utility functions //
	/////////////////////////

	// for debug
	void printSimulationResult(SALTTime currentStep);

	// @brief: increase this simulation's current step (myCurrentStep++)
	// @NOTE THAT : increaseCurrentStep() is called in doSimulationStep() to progress next simulation step
	void increaseCurrentStep();
	// @brief: Check the condition breaks simulation loop
	bool checkEnd();
	// @brief: Check the current simulation state to run simulation
	bool isRunnable();
	void assertReady();

	SALTTime getSimulationEndTime();
	SALTTime getCurrentStep() const {return myCurrentStep;}
	SimulationState getSimulationState() const {return mySimulationState;}
	map<string, string> getNodeShapeList();
	map<string, string> getLinkShapeList();

	const std::vector<Node*>& getNodeList() const;
	const std::vector<Link*>& getLinkList() const;
	const std::vector<Connection*>& getConnectionList() const;

public:
	NetworkManager* myNetworkManager=0;
	VehicleManager* myVehicleManager=0;
	TrafficSignalManager* myTrafficSignalManager=0;
private:
	SimScenarioInfo* mySimulationScenario=0;
	SimulationState mySimulationState=SIMULATION_NOT_READY;
	SALTTime myCurrentStep=0;
	ModelInterface* myModel = 0;

};
}
#endif /* SIMULATIONCONTROLLER_H_ */
