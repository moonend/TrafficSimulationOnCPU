//
// Created by hwonsong on 2018. 8. 17..
//

#ifndef SALT_OUTPUTSTEP_H
#define SALT_OUTPUTSTEP_H

#include <utils/config.h>

using namespace std;

namespace SALT{
    struct RoadStepOutput {
        SALTTime tstep;
        ID curid;
        int curvnum;
        int curwaitvnum;
        Speed curspeedlimit;
        Length curlength;
        string curtls;
    };

    struct VehicleStepOutput {
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
    };

    struct RoadPeriodicOutput {
        SALTTime stime;
        SALTTime etime;
        ID roadid;
        float avgvnum;
        Speed avgspeed;
        float avgdensity;
        Speed speedsum;
        long passingvehs;
//        float avgwaitingtime;
//        SALTTime maxwaitingtime;
    };
}

#endif //SALT_OUTPUTSTEP_H
