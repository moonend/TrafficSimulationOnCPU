/*
 * Route.h
 *
 *  Created on: 2018. 1. 29.
 *      Author: SDJ
 */

#ifndef OBJECTT_ROUTE_H_
#define OBJECTT_ROUTE_H_

#include <string>
#include <vector>

#include <utils/config.h>



//////////////////////////////////////////////////////////
// XXX - consideration
// Should Route class have departing position(link, lane, offset) of vehicle?
//////////////////////////////////////////////////////////
namespace SALT{

class NetworkManager;
class Link;

class Route {
public:
	Route();
	Route(string _linkList, NetworkManager* networkManagerToRef, string _departLane="");
	Route(vector<Link*> _linkList);
	virtual ~Route();

	Link* getLink(int index);

//	Link* getDepartingLink();
	Link* getNextLink(Link* link);
	Link* getNextLink(int from_index);

	//Link* getNextValidLink(Link* link);
	Link* getNextValidLink(int from_index);
	int getOffsetToNextValidLink(int from_index);
	bool isAllInvalidLink();
private:
	// TODO
	// FIXME
	// a sub-simulation doesn't have Link* belonging to other sub-simulation!!
	vector<Link*> myLinkList;

	vector<string> myLinkStringVector;


	// XXX - myStartingIndex is deprecated, because Vehicle has its current position

	// // index of the link where the vehicle starts its route
//	int myStartingIndex=0;

	// XXX - issue
	int myDepartLane=0;
	// startingOffset is deprecated. not gonna use the 'offset of a single link'
	//int myOffsetOnStartingLink=0;

};
}
#endif /* OBJECTT_ROUTE_H_ */
