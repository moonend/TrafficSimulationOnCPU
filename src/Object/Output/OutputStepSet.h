//
// Created by hwonsong on 2018. 3. 28..
//

#ifndef SIMULATIONOBJECT_OUTPUTSTEPSET_H
#define SIMULATIONOBJECT_OUTPUTSTEPSET_H


#include <Object/Output/OutputStepRoad.h>
#include <Object/Output/OutputStepVehicle.h>
#include <list>
#include <map>
#include <string>
#include "OutputData.h"

using namespace std;

namespace SALT{

class OutputStepSet {
public:
    OutputStepSet();

    explicit OutputStepSet(SALTTime myCurtstep);

    virtual ~OutputStepSet();

    void setCurTimeStep(SALTTime myCurtstep);

    void addOutputStepRoad(OutputStepRoad* myOSL);
    void addOutputStepVehicle(OutputStepVehicle* myOSV);
    void updateOutputStepVehicle(OutputStepVehicle* myOSV);
    void addRoadOutputStep(SALTTime tstep, ID myCurid, int myCurvnum, int myCurWaitvnum, Length myCurlength, string myCurtls, Speed myCurSpeedLimit);
    void addVehicleOutputStep(SALTTime myTstep, ID myCurvid, string myCurvtype, ID myCurlink, int myCurSection, int myCurlane,
                             SALTTime myCurEnteredTime, SALTTime myCurLeftTime, string myCurOutLevelId, Length myCurRoadLength);
    void updateVehicleOutputStep(SALTTime myTstep, ID myCurvid, string myCurvtype, ID myCurlink, int myCurSection, int myCurlane,
                                 SALTTime myCurEnteredTime, SALTTime myCurLeftTime, string myCurOutLevelId, Length myCurRoadLength);


    void clearCurOutputStepRoadSet();
    void clearCurOutputStepSet();
//    void clearCurOutputStepVehicleSet();

//    OutputStepRoad generateOutputStepRoad(long myCurtstep, std::string myCurlid, int myCurvnum, float myCurspeed, float myCurdensity, std::string myCurtls);
//    OutputStepVehicle generateOutputStepVehicle(long myCurtstep);
    SALTTime getCurTimeStep();
    list<OutputStepRoad*> getOutputStepRoad();
//    __attribute__((deprecated)) list<OutputStepVehicle*> getOutputStepVehicle();
    map<string, list<OutputStepVehicle*>> getVehiclePerRoadMap();
    map<string, OutputStepVehicle*> getOutputStepPerVehicle();
    list<OutputStepVehicle*> getVehicleListPerRoad(string myRoadId);

    list<RoadStepOutput> getRoadOutputStep();
    map<ID, list<VehicleStepOutput>> getVehicleOutputStep();
    map<ID, VehicleStepOutput> getVehicleOutputStepByVehID();
    list<VehicleStepOutput> getVehicleOutputStepByRoadID(ID myRoadId);




private:
    SALTTime curtstep;
//    int curlinknum;
//    int curruningvnum;
    list<OutputStepRoad*> outsetroad;
//    __attribute__((deprecated)) list<OutputStepVehicle*> outsetvehicle;
    map<ID,list<OutputStepVehicle*>> vehPerRoad;
    map<ID,OutputStepVehicle*> outPerVehicle;
    list<RoadStepOutput> roadout;
    map<ID, list<VehicleStepOutput>> vehout;
    map<ID, VehicleStepOutput> vehoutbyvid;



};

}
#endif //SIMULATIONOBJECT_OUTPUTSTEPSET_H
