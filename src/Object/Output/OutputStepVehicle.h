//
// Created by hwonsong on 2018. 3. 28..
//

#ifndef SIMULATIONOBJECT_OUTPUTSTEPVEHICLE_H
#define SIMULATIONOBJECT_OUTPUTSTEPVEHICLE_H

#include <string>
#include <array>
#include <utils/config.h>

using namespace std;
namespace SALT{
class OutputStepVehicle {
public:
    OutputStepVehicle();
//    __attribute__((deprecated)) OutputStepVehicle(long myTstep, string myCurvid, string myCurvtype, string myCurlink, int myCurlane,
//                      float myCurvspeed, float myCurlanepos, array<float, 2> myCurvpos);
    OutputStepVehicle(SALTTime myTstep, ID myCurvid, string myCurvtype, ID myCurlink, int myCurSection, int myCurlane,
                      SALTTime myCurEnteredTime, SALTTime myCurLeftTime, string myCurOutLevelId, Length myCurRoadLength);

    virtual ~OutputStepVehicle();

   // void setOutputStepVehicle(long tstep, std::string curvid, std::string curvtype, std::string curlink, std::string curlane, float curvspeed, float lanepos, std::array<float, 2> vpos);

//    OutputStepVehicle* getOutputStepVehicle();
    SALTTime getCurTimeStep();
    ID getCurVehicleId();
    string getCurVehicleType();
    ID getCurLink();
    int getCurSection();
    int getCurLane();
    SALTTime getCurEnteredTime();
    SALTTime getCurLeftTime();
    string getCurOutLevelId();
    Length getCurRoadLength();
    void setCurLeftTime(SALTTime myCurLeftTime);
//    __attribute__((deprecated)) float getCurVehicleSpeed();
//    __attribute__((deprecated)) float getCurLanePosition();
//    __attribute__((deprecated)) array<float, 2> getCurVehiclePosition();

private:
    SALTTime tstep;
    ID curvid;
    string curvtype;
    ID curlink;
    int cursection;
    int curlane;
    SALTTime curenteredtime;
    SALTTime curlefttime;
    string curoutlevelid;
    Length curroadlength;
//    __attribute__((deprecated)) float curvspeed;
//    __attribute__((deprecated)) float curlanepos;
//    __attribute__((deprecated)) array <float, 2> curvpos;
};

}
#endif //SIMULATIONOBJECT_OUTPUTSTEPVEHICLE_H
