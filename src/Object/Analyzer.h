//
// Created by hwonsong on 2018. 3. 29..
//

#ifndef SIMULATIONOBJECT_ANALYZER_H
#define SIMULATIONOBJECT_ANALYZER_H


#include <Object/Network/CellInterface.h>
#include <Object/Output/OutputPeriodicRoadSet.h>
#include <Object/Output/OutputStepRoad.h>
#include <Object/Output/OutputStepSet.h>
#include <list>
#include <map>
#include <set>
#include <string>

namespace SALT{

class SimScenarioInfo;



class Analyzer {
public:
    static Analyzer* getInstance();

    virtual ~Analyzer();

//    void updateOutputStatus(SALTTime myTstep);
    OutputStepSet* updateOutputStatus(SALTTime myTstep);

    void setOutputParameters(SimScenarioInfo* scenario);

    SALTTime getSALTTimeStep();
    SALTTime getSALTTimePeriod();
    SALTTime getSALTStartTime();
    SALTTime getSALTEndTime();

//    map<SALTTime,OutputStepSet*> getOutputStepSetStatus();
    OutputStepSet* getOutputStepSetStatus();
    map<SALTTime,OutputPeriodicRoadSet*> getOutputPeriodicRoadSetStatus();

//    void printStatus(SALTTime myTstep);
    void printStatus(SALTTime myTstep);
    void printPeriodicStatus();
    string print();



private:
    Analyzer();
//    static bool myAnalyzerFlag;
    static Analyzer* instance;
    int myOuttype;          //0: default(only output according simulation time step), 1: additionally include output for periodic time interval
    int myOutlevel;          //0: default(cell level), 1: segment level, 2: link level
    int myOutSave;          //0: default(not save the OutputStepSet), 1: save the OutputStepSet
    SALTTime myTimestep;
    SALTTime myPeriod;
    SALTTime mySimStarttime;
    SALTTime mySimEndtime;
    int myCurPeriodState;      // 0: start (including period start and sim start), 1: end (including period end and sim end), 2: intermediate, 3: special case (Sim end & period start)
    SALTTime myCurPeriodDist;       // id for seperated time sections
    OutputPeriodicRoadSet* myPendingOutStatus;
    OutputPeriodicRoad* myPeriodicUpdator;
    set<ID> myPendingRoad;
    OutputStepSet* myCurOutstepStatus;
    OutputStepSet* myPreviousOutstepStatus;


//    map<SALTTime, list<OutputStepRoad*>>  myOutStepRoadSave;
//    map<SALTTime, map<string, list<OutputStepVehicle*>>> myOutStepVehiclePerRoadIDSave;
//    map<SALTTime, map<string, OutputStepVehicle*>> myOutStepVehiclePerVehIDSave;
    map<SALTTime, list<RoadStepOutput>>  myOutStepRoadSave;
    map<SALTTime, map<string, list<VehicleStepOutput>>> myOutStepVehiclePerRoadIDSave;
    map<SALTTime, map<string, VehicleStepOutput>> myOutStepVehiclePerVehIDSave;
    map<SALTTime, OutputPeriodicRoadSet*> myOutperiodicStatus;
    map<ID, OutputStepRoad*>  myStepPendingOut;
    map<ID, RoadStepOutput> myPendingStepOutput;

    std::set<CellInterface*> myPrevAC;
    list<ID> myPrevUpdated;


    void setOutputStepLevel(string myOutlevel);
    void setOutputSaveOption(int mySaveOption);
    void setPeriodicAttributes(int myOuttype, SALTTime myPeriod, SALTTime myStarttime, SALTTime myEndtime);

//    void setOutputByStep(SALTTime myTstep, OutputStepSet* OSS);
    OutputStepSet* setOutputByStep(SALTTime myTstep);
    void setOutputByPeriodic (SALTTime myTstep, OutputStepSet* OSS);
    void updateCurPeriodInfo(SALTTime myTstep);

    string cookCellId(ID link, int section, int lane);
    string cookSectionId(ID link, int section);

    string getOutputLevel();

    OutputStepRoad* setOutputStepByOutlevel(OutputStepRoad* curOSR, int basenumber, int curVnum, int curWaitVnum, Length curLength);
    RoadStepOutput setOutputStepByOutlevel(SALTTime tstep, ID myCurid, int myCurvnum, int myCurWaitvnum, string myCurtls, Speed myCurSpeedLimit, int basenumber, int curVnum, int curWaitVnum, Length curLength);

    RoadPeriodicOutput updateProcessByOPR(RoadPeriodicOutput myRPO);
    RoadPeriodicOutput updateProcessByOPR(RoadPeriodicOutput myRPO, SALTTime myTstep, Speed mySpeedSum, long myPassingVehs);
    RoadPeriodicOutput updateProcessByOPR(RoadPeriodicOutput myRPO, SALTTime myTstep, int myCurVehNum, int myCurWaitVehNum, Speed mySpeedSum, float myDensity, long myPassingVehs);
    RoadPeriodicOutput updateProcessByOPR(RoadPeriodicOutput myRPO, SALTTime myTstep);

};

}
#endif //SIMULATIONOBJECT_ANALYZER_H
