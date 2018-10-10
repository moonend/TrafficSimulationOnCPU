//
// Created by hwonsong on 2018. 3. 29..
//

#ifndef SIMULATIONOBJECT_OUTPUTLINK_H
#define SIMULATIONOBJECT_OUTPUTLINK_H

#include <string>
#include <utils/config.h>
#include "OutputData.h"


using namespace std;

namespace SALT{

class OutputStepRoad;

class OutputPeriodicRoad {
public:
    OutputPeriodicRoad();
//    __attribute__((deprecated)) OutputPeriodicRoad(long myStime, long myEtime, string myLinkid, int myEnteredVnum, int myLeftVnum, float myAvgspeed,
//                       float myAvgdensity, float myAvgwaitingtime, long myMaxwaitingtime);
//    OutputPeriodicRoad(SALTTime myStime, SALTTime myEtime, ID myRoadid, float myVnum, Speed mySpeedLimit, Speed mySpeedSum, float myDensity, long myPassingVehs);
    virtual ~OutputPeriodicRoad();

//    SALTTime getStartTime();
//    SALTTime getEndTime();
//    ID getRoadId();
//    float getAvgVehicleNum();
//    __attribute__((deprecated)) int getEnteredVehicleNum();
//    __attribute__((deprecated)) int getLeftVehicleNum();
//    Speed getAvgSpeed();
//    float getAvgDensity();
//    float getAvgWaitingTime();
//    SALTTime getMaxWaitingTime();

    RoadPeriodicOutput getRoadPeriodicOutput();

//    void setRoadPeriodicOutput(SALTTime myStime, SALTTime myEtime, ID myRoadid, float myVnum, Speed mySpeedLimit, Speed mySpeedSum, float myDensity, long myPassingVehs);
    void setRoadPeriodicOutput(RoadPeriodicOutput myRPO);
//    OutputPeriodicRoad* getOutputPeriodicRoad();

    void updateByOutputStep(SALTTime myTstep, OutputStepRoad* myOSR, Speed mySpeedSum, float myDensity, long myPassingVehs);
    void updateByOutputStep(SALTTime myTstep, int myCurVehNum, int myCurWaitVehNum, Speed mySpeedSum, float myDensity, long myPassingVehs);
    void updateByOutputStepOnly(SALTTime myTstep);
    void setAvgSpeed(SALTTime myTstep, Speed mySpeedSum, long myPassingVehs);
//    void setAvgDensity(float myDensity);
//    void setAvgWaitingTime(float myAvgWaitingTime);
//    void setMaxWaitingTime(SALTTime myMaxWaitingTime);
    string getAttributeString();


private:
    RoadPeriodicOutput periodicout;
//    SALTTime stime;
//    SALTTime etime;
//    ID roadid;
//    float avgvnum;
////    __attribute__((deprecated)) int enteredvnum;
////    __attribute__((deprecated)) int leftvnum;
//    Speed avgspeed;
//    float avgdensity;
//    float avgwaitingtime;
//    SALTTime maxwaitingtime;
//    Speed speedsum;
//    long passingvehs;

//    __attribute__((deprecated)) void calculatePeriodicEnteredvnum(int myEnteredvnum);
//    __attribute__((deprecated)) void calculatePeriodicLeftvnum(int myLeftvnum);
    void calculatePeriodicVehicleNum(SALTTime myTstep, int myVnum, int myWaitVnum);
    void calculatePeriodicAvgSpeed(SALTTime myTstep, Speed mySpeed);
    void calculatePeriodicAvgDensity(SALTTime myTstep, float myDensity);
//    void calculatePeriodicWaitingtime(SALTTime myTstep, SALTTime myWaitingtime);

};

}
#endif //SIMULATIONOBJECT_OUTPUTLINK_H
