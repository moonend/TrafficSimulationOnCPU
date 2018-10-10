/*
 * CellInterface.h
 *
 *  Created on: 2018. 3. 14.
 *      Author: SDJ
 */

#ifndef CELLINTERFACE_H_
#define CELLINTERFACE_H_

#include <utils/config.h>
#include <list>
#include <map>
#include <string>
#include <tuple>


namespace SALT{

class Link;
class VehicleInterface;
class SectionInterface;

class CellInterface {
public:
	CellInterface(Link* _link,  int _len, int _row, int _col, bool _myExceptionFlag=false);
	virtual ~CellInterface();


	virtual void updateStatus()=0;
	virtual string getStatusString()=0;

	virtual void preprocess(SALTTime t)=0;
	virtual void process(SALTTime t)=0;
	virtual void postprocess(SALTTime t)=0;


	// @brief: insert a vehicle into simulation i.e. cell's pendingQ
	virtual void executeVehInsert(VehicleInterface* veh, SALTTime tDepart)=0;

	// @brief: let a vehicle from pendingQ run on cell
	virtual void executeVehDepart(SALTTime tDepart)=0;

	// @brief: pop a vehicle that ends its route
	virtual void executeVehPop(SALTTime t)=0;

	// @brief: move vehicle from runningQ to waitingQ
	virtual void executeVehMove(SALTTime tStartWaiting)=0;

	// @brief: send a vehicle to the next cell (high pendingQ)
	virtual void executeVehSend(SALTTime t)=0;
	// @brief: send back a vehicle to the prev cell (waitingQ)
	virtual void rollbackVehSend(SALTTime t)=0;
	// @brief: receive a vehicle that the previous cell sent (i.e. from this cell's high pendingQ)
	virtual void executeVehReceive(SALTTime tEnterTime)=0;


	// @brief: insert a vehicle into runningQ
	// v : the vehicle inserted in the simulation
	// t : the time when the vehicle departs
	virtual Result insertRunningQ(VehicleInterface* v, SALTTime t)=0;

	// @brief: insert a vehicle into pendingQ
	// v : the vehicle that try to run
	// t : the time when the vehicle plans to depart its route
	virtual Result insertPendingQ(VehicleInterface* v, SALTTime t)=0;

	// @brief: insert a vehicle into high priority pendingQ
	// v : the vehicle that should depart but cannot depart until conditions meet
	// tStartWaiting : the time when the vehicle .... TODO
	// fromCell : TODO
	virtual Result insertHighPendingQ(VehicleInterface* v, SALTTime tStartWaiting, CellInterface* fromCell)=0;

	// @brief: move a vehicle from runningQ to waitingQ
	// v : the vehicle whose expected time to leave is overdue
	// t : the time when the vehicle starts to wait
	virtual Result insertWaitingQ(VehicleInterface* v, SALTTime t, bool insertToBack=true)=0;




	// @brief: traffic signal checking (called by wait2highpend)
	Result checkTrafficSignal(CellInterface* nextCell);
	Result checkTrafficSignal(Link* toLink);
	Result checkTrafficSignal(VehicleInterface* veh);

	Result decreaseVolume(int vol=1);
	Result increaseVolume(int vol=1);

	int getMyCurrentVolume() const {return myCurrentVolume;}
	bool checkInputRoom(int vol);

	int getMyActivationCount() const {	return myActivationCount;}
	bool isActive(){return myActivationCount > 0;}

	void increaseActivationCount(int val=1);
	void decreaseActivationCount(int val=1);

	// @brief: get the next cell "veh" of this cell should go
	// candidates - 1) same link's consecutive cell 2) next link's cell
	CellInterface* getNextCellOnInputRoute(VehicleInterface* veh);
	CellInterface* getNextValidCell(VehicleInterface* veh);

	// @brief: get traffic signal to go the next cell
	// intra-link -> always return "GREEN"
	// inter-link -> get trafficSignal(this link, next link)
	TrafficSignalState getTrafficSignalState(CellInterface* nextCell);

	Link* getMyLink(){return myLink;}
	// [Adding] used by class Analyzer (as identity info. of cell)
	int getMySection() {
	  return mySection;
	};
	int getMyLane() {
	  return myLane;
	};
	int getMyLength() {
		return myLength;
	};
	long getMyCurrentWaitingVolume() {
	    return myWaitingQ.size();
	}
	long getMyCurrentRunningVolume() {
	    return myRunningQ.size();
	}

	list<tuple<VehicleInterface*, SALTTime, SALTTime>> getVehiclePassingInfo(SALTTime t);
	void updateVehicelPassingInfo(VehicleInterface* veh);

    Speed getSpeedLimit();

	void determineCellSeries(VehicleInterface* veh);
	void recordVehicleEntering(VehicleInterface* veh,SALTTime tEnter);
	void recordVehicleLeaving(VehicleInterface* veh,SALTTime tLeave);

protected:
	//	(constant) cell fixed attriutes
	Link* myLink=0;
	int myLength=-1;
	int mySection=-1;
	int myLane=-1;
	bool myLastSectionFlag = false;
	bool myFirstSectionFlag = false;
	bool myExceptionFlag = false;
	string myInfo = "";


	int myPassRateCapacity = -1; // floor( speed_limit / veh_length)
	int myVolumeCapacity = -1; // floor( cell_length / veh_length)

	// (variable) link status summary
	int myCurrentVolume= 0;
	int myActivationCount = 0;

	// (variable) link queue
	//	list<VehicleInterface*> myVehicleQ;
	//	 tuple<veh, enterTime(:=the time when the vehicle has enters)
	//					,expectedLeavingTime(:=time when veh can leave)>
	// queue of vehicle that has entered and is passing this cell
	list<tuple<VehicleInterface*,SALTTime,SALTTime>> myRunningQ;

	// queue of vehicle that has passed this cell but waits to leave until condition meets
	// tuple <veh, the time when the vehicle has started waiting>
	list<tuple<VehicleInterface*,SALTTime>> myWaitingQ;

	// queue of vehicle that wants to enter this cell
	// tuple <veh, the time when the vehicle has started pening>
	list<tuple<VehicleInterface*,SALTTime>> myPendingQ;

	// queue of vehicle that wants to enter this cell
	// tuple <veh, the time when the vehicle has started pending, prevCell>
	list<tuple<VehicleInterface*,SALTTime,CellInterface*>> myReceivingQ;


	map<VehicleInterface*, tuple<SALTTime,SALTTime>> myVehiclePassingInfo;


};
}
#endif /* CELLINTERFACE_H_ */
