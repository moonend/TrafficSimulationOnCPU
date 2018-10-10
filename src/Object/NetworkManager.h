/*
 * NetworkManager.h
 *
 *  Created on: 2018. 1. 30.
 *      Author: SDJ
 */

#ifndef NETWORKMANAGER_H_
#define NETWORKMANAGER_H_

//#include <iostream>

#include <Object/Network/CellInterface.h>
#include <Object/Network/Connection.h>
#include <Object/Network/Link.h>
#include <Object/Network/Node.h>
#include <utils/config.h>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace SALT{

class SimScenarioInfo;
class Scenario;

class NetworkManager {
private:
	static NetworkManager* instance;

	NetworkManager(){};

public:
	static NetworkManager* getInstance();

	Result build(Scenario* scenario);
	//	Result build(string const& _net_file);
	//	Result build(string const& _node_file, string const& _link_file);
	Result build(string const& _node_file, string const& _link_file, string const& _connection_file, string const& _input_type="SALT");
	// [Add] for using SimScenarioInfo
	Result build(SimScenarioInfo* scenario);
	virtual ~NetworkManager();

public:
	//	1. init node
	//	2. init link (from-node,to-node)
	//	3. init connection (belonging node, from-lane, to-lane)

	//	5. set link->prevLinkList, nextLinkList via connection
	Result registerNode( Node* _node);
	Result registerLink( Link* _link);
	Result registerConnection(Connection* _connection);


	//	assign link->prevLinkList, nextLinkList according to connection info
	Result buildLinkGraph(void);

	Result buildCellGraph(void);

	// status
	string print(void);
	// util
	Node* findNodeByID(string id);
	Link* findLinkByID(string id);


	void insertActiveCell(CellInterface* _cell);
	void insertActiveLink(Link* _link);
	bool checkVehicleInsertingCondition(Link* link, VehicleInterface* veh);
	Result insertVehicle(Link* link, VehicleInterface* veh, SALTTime t);
	Result pendVehicle(Link* link, VehicleInterface* veh, SALTTime t);
	void printStatus(SCOPE _scope=MACRO);

	const set<CellInterface*>& getMyActiveCellSet() const {
		return myActiveCellSet;
	}


	void refreshActiveCellSet();

	//void executeFuncOnActiveCell(void (*method)(SALTTime), SALTTime t);

	// @return sample value from uniform distribution [minCellLength, cellLength]
	int getRandomLength(int cellLength);
	bool getTrueWithProb(float prob);
	int getRandomNumber(int low,int high);

	// information needed for visualization
	string getNodeShape(string nodeID);
	string getNodeShape(Node* _node);
	string getLinkShape(string linkID);
	string getLinkShape(Link* _link);
	//	getLinkAttr(string LinkID);

	map<string, string> getNodeShapeList();
	map<string, string> getLinkShapeList();


	const std::vector<Node*>& getNodeList() const;
	const std::vector<Link*>& getLinkList() const;
	const std::vector<Connection*>& getConnectionList() const;

private:
	vector<Node*> myNodeList;
	vector<Link*> myLinkList;
	vector<Connection*> myConnectionList;

	map<string, Node*> myNodeMap;
	map<string, Link*> myLinkMap;


	//	set<Link*> myActiveLinkSet;
	set<CellInterface*> myActiveCellSet;

	Length minCellLength = -1; // initialized by scenario
	//	Length maxCellLength = 30.0;


	// FIXME - convert to global variable
	RandomGenerator* myRandomGenerator = NULL;
};

ostream& operator << (ostream& strm, NetworkManager& obj);
}
#endif /* NETWORKMANAGER_H_ */
