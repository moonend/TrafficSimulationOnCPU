//
// Created by hwonsong on 2018. 5. 18..
//

#ifndef SALT_SIMSCENARIO_H
#define SALT_SIMSCENARIO_H

#include <utils/config.h>
#include <string>
#include <tuple>

namespace SALT{

class SimScenarioInfo {
public:
    SimScenarioInfo();

    explicit SimScenarioInfo(string configFile);
    virtual ~SimScenarioInfo();

    //Simulation ID
    string simid;

    //Simulation Begin time & End time
    SALTTime simbegin;
    SALTTime simend;

    //PartitionInfo
    string partitionid;
    tuple<float,float,float,float> parea;

    //InputParameters
    string inputType;
    string nodeFile;
    string linkFile;
    string connectionFile;
    string tlsFile;
    string routeFile;

    string eventFile;
    string weatherFile;

    //ModelParameters
    Length minCellLength = 30.0;
    Length vehLength = 7.0;

    //OutputParameters
    string outputPrefix;
    string outputFile;
    string outputlevel = "cell";
    int outputperiod = 0;
    int outputsave = 0;
};

}
#endif //SALT_SIMSCENARIO_H
