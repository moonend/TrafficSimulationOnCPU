/*
 * ParserSALT.h
 *
 *  Created on: 2018. 7. 26.
 *      Author: SDJ
 */

#ifndef SRC_UTILS_PARSERSALT_H_
#define SRC_UTILS_PARSERSALT_H_

#include <utils/config.h>
#include <utils/ParserInterface.h>
#include <string>


namespace SALT{

class NetworkManager;
class VehicleManager;
class TrafficSignalManager;

class ParserSALT : public ParserInterface{
public:
	ParserSALT(){};
	//ParserSALT(NetworkManager* _NM, VehicleManager* _VM, TrafficSignalManager* _TM): myNM(_NM), myVM(_VM), myTM(_TM){};
	virtual ~ParserSALT(){};
	virtual Result buildNode(string const& _node_json, NetworkManager* networkManagerToFill);
	virtual Result buildLink(string const& _link_json, NetworkManager* networkManagerToFill);
	virtual Result buildConnection(string const& _connection_json, NetworkManager* networkManagerToFill);

	virtual Result buildRoute(string const& _route_json, VehicleManager* vehicleManagerToFill, NetworkManager* networkManagerToRef);

	virtual Result buildTLS(string const& _tls_json, TrafficSignalManager* trafficSignalManagerToFill, NetworkManager* networkManagerToRef);

	Result parseTLS(string const& _tls_json, TrafficSignalManager* trafficSignalManagerToFill, NetworkManager* networkManagerToRef);

};
}
#endif /* SRC_UTILS_PARSERSALT_H_ */
