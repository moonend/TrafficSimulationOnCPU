//
// Created by hwonsong on 2018. 3. 28..
//

#ifndef SIMULATIONOBJECT_OUTPUTSTEPLINK_H
#define SIMULATIONOBJECT_OUTPUTSTEPLINK_H

#include <string>
#include <utils/config.h>

using namespace std;

namespace SALT{

class OutputStepRoad {
public:
    OutputStepRoad();

//    __attribute__((deprecated)) OutputStepRoad(long myTstep, string myCurid, int myCurvnum, string myCurtls);
//    __attribute__((deprecated)) OutputStepRoad(long myTstep, string myCurid, int myCurvnum, float myCurspeed, float myCurdensity, string myCurtls);
    OutputStepRoad(SALTTime myTstep, ID myCurid, int myCurvnum, int myCurWaitvnum, Length myCurlength, string myCurtls, Speed myCurSpeedLimit);

    virtual ~OutputStepRoad();

//    void setOutputStepRoad(long myTstep, string myCurid, int myCurvnum, float myCurspeed, float myCurdensity, string myCurtls);

//    OutputStepRoad* getOutputStepRoad();

    SALTTime getCurTimeStep();
    ID getRoadId();
    int getCurVehicleNumber();
//    __attribute__((deprecated)) float getCurRoadSpeed();
//    __attribute__((deprecated)) float getCurRoadDensity();
    int getCurWaitVehicleNumber();
    Length getCurRoadLength();
    string getCurTls();
    Speed getCurSpeedLimit();

    void setCurVehicleNumber(int myCurvnum);
//    __attribute__((deprecated)) void setCurRoadSpeed(float myCurspeed);
//    __attribute__((deprecated)) void setCurRoadDensity(float myCurdensity);
    void setCurWaitingVehicleNumber(int myCurWaitvnum);
    void setCurRoadLength(Length myCurlength);
    void setCurSpeedLimit(Speed myCurSpeedLimit);

    string getAttributeString();

private:
    SALTTime tstep;
    ID curid;
    int curvnum;
//    __attribute__((deprecated)) float curspeed;
//    __attribute__((deprecated)) float curdensity;
    int curwaitvnum;
    Speed curspeedlimit;
    Length curlength;
    string curtls;

};

}
#endif //SIMULATIONOBJECT_OUTPUTSTEPLINK_H
