/*
 * CellVersion2.h
 *
 *  Created on: 2018. 4. 24.
 *      Author: dongjin
 */
#ifndef SRC_OBJECT_NETWORK_CELLVERSION2_H_
#define SRC_OBJECT_NETWORK_CELLVERSION2_H_

#include <Object/Network/CellInterface.h>
#include <utils/config.h>
#include <string>

namespace SALT{
namespace version2{

class Cell : public SALT::CellInterface {
public:
	Cell(Link* _link,  int _len, int _row, int _col, bool _myExceptionFlag=false);
	virtual ~Cell();

	virtual void executeVehInsert(VehicleInterface* veh, SALTTime tDepart);

	virtual void executeVehDepart(SALTTime tDepart);
	virtual void executeVehPop(SALTTime t);
	virtual void executeVehMove(SALTTime tStartWaiting);
	virtual void executeVehSend(SALTTime t);
	virtual void rollbackVehSend(SALTTime t);
	virtual void executeVehReceive(SALTTime tEnterTime);

	virtual Result insertRunningQ(VehicleInterface* v, SALTTime t);
	virtual Result insertPendingQ(VehicleInterface* v, SALTTime t);
	virtual Result insertHighPendingQ(VehicleInterface* v, SALTTime tStartWaiting, CellInterface* fromCell);
	virtual Result insertWaitingQ(VehicleInterface* v, SALTTime t,bool insertToBack=true);

	virtual void updateStatus();
	virtual string getStatusString();

	virtual void preprocess(SALTTime t);
	virtual void process(SALTTime t);
	virtual void postprocess(SALTTime t);

	void tryVehMove(SALTTime t);
	void tryVehSend(SALTTime t);
	void tryVehReceive(SALTTime tEnterTime);
	void tryVehDepart(SALTTime tStartRunning);
	Speed computeVehSpeed(VehicleInterface* veh);
	SALTTime computeLeavingTime(VehicleInterface* v, SALTTime currentTime);
private:
};

}
}
#endif /* SRC_OBJECT_NETWORK_CELLVERSION2_H_ */
