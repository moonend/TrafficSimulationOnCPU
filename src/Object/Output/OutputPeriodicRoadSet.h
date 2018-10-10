//
// Created by hwonsong on 2018. 3. 29..
//

#ifndef SIMULATIONOBJECT_OUTPUTPERIODICLINK_H
#define SIMULATIONOBJECT_OUTPUTPERIODICLINK_H

#include <Object/Output/OutputPeriodicRoad.h>
#include <list>
#include <map>
#include <string>
#include <utils/config.h>

using namespace std;

namespace SALT{
class OutputPeriodicRoadSet {
public:
    OutputPeriodicRoadSet();
    OutputPeriodicRoadSet(SALTTime myStime, SALTTime myEtime);

    virtual ~OutputPeriodicRoadSet();

    SALTTime getPeriodicStartTime();
    SALTTime getPeriodicEndTime();

    void setPeriodStartTime(SALTTime myStime);
    void setPeriodEndTime(SALTTime myEtime);

    list<OutputPeriodicRoad*> getOutputPeriodicRoad();
    map<ID, OutputPeriodicRoad*> getOutputPeriodicRoadMap();
    list<RoadPeriodicOutput> getRoadPeriodicOutput();
    map<ID, RoadPeriodicOutput> getRoadPeriodicOutputByRoadID();

    void addOutputPeriodicRoad(OutputPeriodicRoad* myOPL);
    void clearOuputPeriodicRoad();

    void addOutputPeriodicRoadMap(ID myRoadid, OutputPeriodicRoad* myOPL);
    void clearOutputPeriodicRoadMap();

    void addRoadPeriodicOutputByRoadID(ID myRoadid, RoadPeriodicOutput myRPO);
    void clearPeriodicOutputSet();

private:
    SALTTime stime;
    SALTTime etime;
    list<OutputPeriodicRoad*> outperiodic;
    map<ID, OutputPeriodicRoad*> outperiodicMap;
    list<RoadPeriodicOutput> pOut;
    map<ID, RoadPeriodicOutput> pOutPerRoad;
};

}
#endif //SIMULATIONOBJECT_OUTPUTPERIODICLINK_H
