/*
 * Configuration.h
 *
 *  Created on: 2018. 5. 17.
 *      Author: dongjin
 */

#ifndef SRC_SCENARIO_H_
#define SRC_SCENARIO_H_

#include <utils/config.h>
#include <string>
namespace SALT{
class Scenario {
public:
	Scenario(string configFile);
	virtual ~Scenario();
	string dataDir;
	string nodeFile;
	string linkFile;
	string connectionFile;
	string routeFile;
	string tlsFile;

	Length minCellLength = 30.0;
	Length vehLength = 7.0;
};
}

#endif /* SRC_SCENARIO_H_ */
