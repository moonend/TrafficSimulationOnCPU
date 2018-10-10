#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <assert.h>

#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include <libxml/tree.h>

#include "TrafficSim.h"
#include "log/logger.h"

Logger *lggr;
roadlink *mylink;
vehicle *myveh;
source_cell *mysource;
sink_cell *mysink;
connection_cell *mycon;

char *edgelink_loc = "/home/moonend/Downloads/toy-data-defined-by-ETRI/toy4.edge.xml";
int **edges_temp, **veh_temp, **nodes_temp, **cc_temp;
int edge_a, edge_b, node_a, node_b, veh_a, veh_b, cc_a, cc_b;

/*--------------------------------------------------------------------*/
/// RECENT UPDATES
/// 1. Update header file
/// 2. Update "Setup_Connectioncell"
/// 3. Add "Update_Source, Start_Path"
/// TODO
/// 4. Update "Relay_numVeh", "Relay_numCF", "Update_nextLink"
/// 5. Add debug functions
/// 5-1. Compare tempArr with CC
/// 6. Source overflow detection
/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/// @fn      void Setup_Veh(vehicle*, int)
/// @brief   Function that setup the values of struct vehicle.
/// @param   vehicle* v, int numVeh
/// @return  None
/*--------------------------------------------------------------------*/
void Setup_Veh(vehicle* v, int numVeh) {
	log_debug(lggr, "Setup_Veh");

	/// (1) Set vehicle ID, type.
	for (int i = 0; i < numVeh; i++) {
		v[i].vehID = i;
		v[i].vehType = 0;

		for (int j = 0; j < MAX_PATH; j++) {
			v[i].path[j] = -1;
		}
		v[i].lenPath = 0;

		for (int j = 0; j < MAX_PATH; j++) {
			v[i].minTargetLane[j] = -1;
			v[i].maxTargetLane[j] = -1;
		}

		v[i].initLink = -1;
		v[i].departTime = i;
	}

	/// vPath[] = list of linkID
	int vPath[100][4] =
			{ { 0, 1, 6, -2 }, { 0, 1, 6, -2 }, { 0, 1, 6, -2 },
					{ 0, 1, 4, -2 }, { 0, 1, 4, -2 }, { 0, 1, 4, -2 }, { 0, 1,
							4, -2 }, { 0, 1, 2, -2 }, { 0, 1, 2, -2 }, { 0, 1,
							2, -2 }, { 1, 6, -2, -1 }, { 1, 6, -2, -1 }, { 1, 6,
							-2, -1 }, { 1, 4, -2, -1 }, { 1, 4, -2, -1 }, { 1,
							4, -2, -1 }, { 1, 4, -2, -1 }, { 1, 2, -2, -1 }, {
							1, 2, -2, -1 }, { 1, 2, -2, -1 }, { 3, 8, 9, -2 }, {
							3, 8, 9, -2 }, { 3, 8, 9, -2 }, { 3, 6, -2, -1 }, {
							3, 6, -2, -1 }, { 3, 6, -2, -1 }, { 3, 6, -2, -1 },
					{ 3, 4, -2, -1 }, { 3, 4, -2, -1 }, { 3, 4, -2, -1 }, { 5,
							2, -2, -1 }, { 5, 2, -2, -1 }, { 5, 2, -2, -1 }, {
							5, 8, 9, -2 }, { 5, 8, 9, -2 }, { 5, 8, 9, -2 }, {
							5, 8, 9, -2 }, { 5, 6, -2, -1 }, { 5, 6, -2, -1 }, {
							5, 6, -2, -1 }, { 7, 4, -2, -1 }, { 7, 4, -2, -1 },
					{ 7, 4, -2, -1 }, { 7, 2, -2, -1 }, { 7, 2, -2, -1 }, { 7,
							2, -2, -1 }, { 7, 2, -2, -1 }, { 7, 8, 3, -2 }, { 7,
							8, 3, -2 }, { 7, 8, 3, -2 }, { 0, 1, 6, -2 }, { 0,
							1, 6, -2 }, { 0, 1, 6, -2 }, { 0, 1, 4, -2 }, { 0,
							1, 4, -2 }, { 0, 1, 4, -2 }, { 0, 1, 4, -2 }, { 0,
							1, 2, -2 }, { 0, 1, 2, -2 }, { 0, 1, 2, -2 }, { 1,
							6, -2, -1 }, { 1, 6, -2, -1 }, { 1, 6, -2, -1 }, {
							1, 4, -2, -1 }, { 1, 4, -2, -1 }, { 1, 4, -2, -1 },
					{ 1, 4, -2, -1 }, { 1, 2, -2, -1 }, { 1, 2, -2, -1 }, { 1,
							2, -2, -1 }, { 3, 8, 9, -2 }, { 3, 8, 9, -2 }, { 3,
							8, 9, -2 }, { 3, 6, -2, -1 }, { 3, 6, -2, -1 }, { 3,
							6, -2, -1 }, { 3, 6, -2, -1 }, { 3, 4, -2, -1 }, {
							3, 4, -2, -1 }, { 3, 4, -2, -1 }, { 5, 2, -2, -1 },
					{ 5, 2, -2, -1 }, { 5, 2, -2, -1 }, { 5, 8, 9, -2 }, { 5, 8,
							9, -2 }, { 5, 8, 9, -2 }, { 5, 8, 9, -2 }, { 5, 6,
							-2, -1 }, { 5, 6, -2, -1 }, { 5, 6, -2, -1 }, { 7,
							4, -2, -1 }, { 7, 4, -2, -1 }, { 7, 4, -2, -1 }, {
							7, 2, -2, -1 }, { 7, 2, -2, -1 }, { 7, 2, -2, -1 },
					{ 7, 2, -2, -1 }, { 7, 8, 3, -2 }, { 7, 8, 3, -2 }, { 7, 8,
							3, -2 } };

	/// (2) Set vehicle path, path length.
	for (int i = 0; i < numVeh; i++) {
		for (int j = 0; j < 4; j++) {
			v[i].path[j] = vPath[i][j];

			if (v[i].path[j] == -2)
				v[i].lenPath = j;
		}
	}

	/// vMinTL[] = list of minTargetLane
	int vMinTL[100][4] = { { 0, 0, 0, -1 }, { 0, 0, 0, -1 }, { 0, 0, 0, -1 }, {
			0, 1, 0, -1 }, { 0, 1, 0, -1 }, { 0, 1, 0, -1 }, { 0, 1, 0, -1 }, {
			0, 3, 0, -1 }, { 0, 3, 0, -1 }, { 0, 3, 0, -1 }, { 0, 0, -1, -1 }, {
			0, 0, -1, -1 }, { 0, 0, -1, -1 }, { 1, 0, -1, -1 },
			{ 1, 0, -1, -1 }, { 1, 0, -1, -1 }, { 1, 0, -1, -1 },
			{ 3, 0, -1, -1 }, { 3, 0, -1, -1 }, { 3, 0, -1, -1 },
			{ 0, 0, 0, -1 }, { 0, 0, 0, -1 }, { 0, 0, 0, -1 }, { 1, 0, -1, -1 },
			{ 1, 0, -1, -1 }, { 1, 0, -1, -1 }, { 1, 0, -1, -1 },
			{ 3, 0, -1, -1 }, { 3, 0, -1, -1 }, { 3, 0, -1, -1 },
			{ 0, 0, -1, -1 }, { 0, 0, -1, -1 }, { 0, 0, -1, -1 },
			{ 1, 0, 0, -1 }, { 1, 0, 0, -1 }, { 1, 0, 0, -1 }, { 1, 0, 0, -1 },
			{ 3, 0, -1, -1 }, { 3, 0, -1, -1 }, { 3, 0, -1, -1 },
			{ 0, 0, -1, -1 }, { 0, 0, -1, -1 }, { 0, 0, -1, -1 },
			{ 1, 0, -1, -1 }, { 1, 0, -1, -1 }, { 1, 0, -1, -1 },
			{ 1, 0, -1, -1 }, { 3, 0, 0, -1 }, { 3, 0, 0, -1 }, { 3, 0, 0, -1 },
			{ 0, 0, 0, -1 }, { 0, 0, 0, -1 }, { 0, 0, 0, -1 }, { 0, 1, 0, -1 },
			{ 0, 1, 0, -1 }, { 0, 1, 0, -1 }, { 0, 1, 0, -1 }, { 0, 3, 0, -1 },
			{ 0, 3, 0, -1 }, { 0, 3, 0, -1 }, { 0, 0, 0, -1 }, { 0, 0, 0, -1 },
			{ 0, 0, 0, -1 }, { 1, 0, -1, -1 }, { 1, 0, -1, -1 },
			{ 1, 0, -1, -1 }, { 1, 0, -1, -1 }, { 3, 0, -1, -1 },
			{ 3, 0, -1, -1 }, { 3, 0, -1, -1 }, { 0, 0, 0, -1 },
			{ 0, 0, 0, -1 }, { 0, 0, 0, -1 }, { 1, 0, -1, -1 },
			{ 1, 0, -1, -1 }, { 1, 0, -1, -1 }, { 1, 0, -1, -1 },
			{ 3, 0, -1, -1 }, { 3, 0, -1, -1 }, { 3, 0, -1, -1 },
			{ 0, 0, 0, -1 }, { 0, 0, 0, -1 }, { 0, 0, 0, -1 }, { 1, 0, 0, -1 },
			{ 1, 0, 0, -1 }, { 1, 0, 0, -1 }, { 1, 0, 0, -1 }, { 3, 0, -1, -1 },
			{ 3, 0, -1, -1 }, { 3, 0, -1, -1 }, { 0, 0, -1, -1 },
			{ 0, 0, -1, -1 }, { 0, 0, -1, -1 }, { 1, 0, -1, -1 },
			{ 1, 0, -1, -1 }, { 1, 0, -1, -1 }, { 1, 0, -1, -1 },
			{ 3, 0, 0, -1 }, { 3, 0, 0, -1 }, { 3, 0, 0, -1 }, };

	/// vMaxTL[] = list of maxTargetLane
	int vMaxTL[100][4] =
			{ { 3, 0, 3, -1 }, { 3, 0, 3, -1 }, { 3, 0, 3, -1 },
					{ 3, 3, 3, -1 }, { 3, 3, 3, -1 }, { 3, 3, 3, -1 }, { 3, 3,
							3, -1 }, { 3, 3, 3, -1 }, { 3, 3, 3, -1 }, { 3, 3,
							3, -1 }, { 0, 3, -1, -1 }, { 0, 3, -1, -1 }, { 0, 3,
							-1, -1 }, { 3, 3, -1, -1 }, { 3, 3, -1, -1 }, { 3,
							3, -1, -1 }, { 3, 3, -1, -1 }, { 3, 3, -1, -1 }, {
							3, 3, -1, -1 }, { 3, 3, -1, -1 }, { 0, 3, 3, -1 }, {
							0, 3, 3, -1 }, { 0, 3, 3, -1 }, { 3, 3, -1, -1 }, {
							3, 3, -1, -1 }, { 3, 3, -1, -1 }, { 3, 3, -1, -1 },
					{ 3, 3, -1, -1 }, { 3, 3, -1, -1 }, { 3, 3, -1, -1 }, { 0,
							3, -1, -1 }, { 0, 3, -1, -1 }, { 0, 3, -1, -1 }, {
							3, 3, 3, -1 }, { 3, 3, 3, -1 }, { 3, 3, 3, -1 }, {
							3, 3, 3, -1 }, { 3, 3, -1, -1 }, { 3, 3, -1, -1 }, {
							3, 3, -1, -1 }, { 0, 3, -1, -1 }, { 0, 3, -1, -1 },
					{ 0, 3, -1, -1 }, { 3, 3, -1, -1 }, { 3, 3, -1, -1 }, { 3,
							3, -1, -1 }, { 3, 3, -1, -1 }, { 3, 0, 3, -1 }, { 3,
							0, 3, -1 }, { 3, 0, 3, -1 }, { 3, 0, 3, -1 }, { 3,
							0, 3, -1 }, { 3, 0, 3, -1 }, { 3, 3, 3, -1 }, { 3,
							3, 3, -1 }, { 3, 3, 3, -1 }, { 3, 3, 3, -1 }, { 3,
							3, 3, -1 }, { 3, 3, 3, -1 }, { 3, 3, 3, -1 }, { 0,
							3, -1, -1 }, { 0, 3, -1, -1 }, { 0, 3, -1, -1 }, {
							3, 3, -1, -1 }, { 3, 3, -1, -1 }, { 3, 3, -1, -1 },
					{ 3, 3, -1, -1 }, { 3, 3, -1, -1 }, { 3, 3, -1, -1 }, { 3,
							3, -1, -1 }, { 0, 3, 3, -1 }, { 0, 3, 3, -1 }, { 0,
							3, 3, -1 }, { 3, 3, -1, -1 }, { 3, 3, -1, -1 }, { 3,
							3, -1, -1 }, { 3, 3, -1, -1 }, { 3, 3, -1, -1 }, {
							3, 3, -1, -1 }, { 3, 3, -1, -1 }, { 0, 3, -1, -1 },
					{ 0, 3, -1, -1 }, { 0, 3, -1, -1 }, { 3, 3, 3, -1 }, { 3, 3,
							3, -1 }, { 3, 3, 3, -1 }, { 3, 3, 3, -1 }, { 3, 3,
							-1, -1 }, { 3, 3, -1, -1 }, { 3, 3, -1, -1 }, { 0,
							3, -1, -1 }, { 0, 3, -1, -1 }, { 0, 3, -1, -1 }, {
							3, 3, -1, -1 }, { 3, 3, -1, -1 }, { 3, 3, -1, -1 },
					{ 3, 3, -1, -1 }, { 3, 0, 3, -1 }, { 3, 0, 3, -1 }, { 3, 0,
							3, -1 }, };

	/// (3) Set vehicle minimum and maximum target lane.
	for (int i = 0; i < numVeh; i++) {
		for (int j = 0; j < v[i].lenPath; j++) {
			v[i].minTargetLane[j] = vMinTL[i][j];
			v[i].maxTargetLane[j] = vMaxTL[i][j];
		}
	}

	/// vPos[] = initLink, departTime
	int vPos[100][2] = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 }, { 0, 4 }, { 0,
			5 }, { 0, 6 }, { 0, 7 }, { 0, 8 }, { 0, 9 }, { 1, 10 }, { 1, 11 }, {
			1, 12 }, { 1, 13 }, { 1, 14 }, { 1, 15 }, { 1, 16 }, { 1, 17 }, { 1,
			18 }, { 1, 19 }, { 3, 20 }, { 3, 21 }, { 3, 22 }, { 3, 23 },
			{ 3, 24 }, { 3, 25 }, { 3, 26 }, { 3, 27 }, { 3, 28 }, { 3, 29 }, {
					5, 30 }, { 5, 31 }, { 5, 32 }, { 5, 33 }, { 5, 34 },
			{ 5, 35 }, { 5, 36 }, { 5, 37 }, { 5, 38 }, { 5, 39 }, { 7, 40 }, {
					7, 41 }, { 7, 42 }, { 7, 43 }, { 7, 44 }, { 7, 45 },
			{ 7, 46 }, { 7, 47 }, { 7, 48 }, { 7, 49 }, { 0, 50 }, { 0, 51 }, {
					0, 52 }, { 0, 53 }, { 0, 54 }, { 0, 55 }, { 0, 56 },
			{ 0, 57 }, { 0, 58 }, { 0, 59 }, { 1, 60 }, { 1, 61 }, { 1, 62 }, {
					1, 63 }, { 1, 64 }, { 1, 65 }, { 1, 66 }, { 1, 67 },
			{ 1, 68 }, { 1, 69 }, { 3, 70 }, { 3, 71 }, { 3, 72 }, { 3, 73 }, {
					3, 74 }, { 3, 75 }, { 3, 76 }, { 3, 77 }, { 3, 78 },
			{ 3, 79 }, { 5, 80 }, { 5, 81 }, { 5, 82 }, { 5, 83 }, { 5, 84 }, {
					5, 85 }, { 5, 86 }, { 5, 87 }, { 5, 88 }, { 5, 89 },
			{ 7, 90 }, { 7, 91 }, { 7, 92 }, { 7, 93 }, { 7, 94 }, { 7, 95 }, {
					7, 96 }, { 7, 97 }, { 7, 98 }, { 7, 99 }, };

	/// (4) Set vehicle initial position.
	for (int i = 0; i < numVeh; i++) {
		v[i].initLink = vPos[i][0];
		v[i].departTime = vPos[i][1];
	}
}


void GetEdgeValue(xmlNode * a_node, struct _xmlAttr * pAtt) {
	xmlChar *key = xmlGetProp(a_node, pAtt->name);
	printf("edge_value: %s\t\t", (char*) key);

	// 스트링이면 -404 대입
	if ((int) atoi((char*) key) < 0) {
		edges_temp[edge_a][edge_b] = (int) atoi((char*) key);
	} else {
		edges_temp[edge_a][edge_b] = (int) atoi((char*) key);
	}
	printf("edge_id: %d, prop: %d\t", edge_a, edge_b);
	printf("value: %d\n", edges_temp[edge_a][edge_b]);
	edge_b++;

	if (pAtt->next != NULL) {
		GetEdgeValue(a_node, pAtt->next);
	}


	free(key);
}

static void parseEdgeDoc(char *docname) {
	xmlDocPtr doc;
	xmlNodePtr cur;
	doc = xmlParseFile(docname);

	if (doc == NULL) {
		fprintf(stderr, "Document is not allocated.\n");
		return;
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		fprintf(stderr, "empty document\n");
		xmlFreeDoc(doc);
		return;
	}

	int elementCnt = 0;
	int propertyCnt = 1;

	// 1. 프로퍼티 개수와 엘리먼트 개수 파악
	cur = cur->children;
	cur = cur->next;
	if (!xmlStrcmp(cur->name, (const xmlChar *) "location")) {
		cur = cur->next->next;
	}

	while (cur->properties->next != NULL) {
		propertyCnt++;
		cur->properties = cur->properties->next;
	}

	while (cur->properties->prev != NULL)
		cur->properties = cur->properties->prev;

	while (cur != NULL) {
		if (!xmlStrcmp(cur->name, (const xmlChar *) "edge")
				|| !xmlStrcmp(cur->name, (const xmlChar *) "vehicle")
				|| !xmlStrcmp(cur->name, (const xmlChar *) "node")
				|| !xmlStrcmp(cur->name, (const xmlChar *) "connection")) {
			cur = cur->next;
			elementCnt++;
		}
		cur = cur->next;
	}

	// 2. 커서 초기화
	cur = xmlDocGetRootElement(doc);
	cur = cur->children;
	cur = cur->next;

	if (!xmlStrcmp(cur->name, (const xmlChar *) "location"))
		cur = cur->next->next;

	edges_temp = (int**) malloc(sizeof(int*) * elementCnt);
	for (int i = 0; i < elementCnt; i++) {
		edges_temp[i] = (int*) malloc(sizeof(int) * propertyCnt);
	}

	for (int i = 0; i < elementCnt; i++) {
		GetEdgeValue(cur, cur->properties);
		edge_a++;
		edge_b = 0;
		if (!xmlStrcmp(cur->name, (const xmlChar *) "vehicle")) {
			cur = cur->children;
			GetEdgeValue(cur, cur->properties);
			cur = cur->parent;
		}
		cur = cur->next->next;
	}

	xmlFreeDoc(doc);
	return;
}


/*--------------------------------------------------------------------*/
/// @fn      void Setup_Link(link*, int, vehicle*, int)
/// @brief   Function that setup the values of struct link,
///          source_cell, sink_cell.
/// @param   vehicle* v, int numVeh, link* l, int numLink
/// @return  None
/*--------------------------------------------------------------------*/
void Setup_Link(vehicle* v, int numVeh, roadlink* l, source_cell* sc,
		sink_cell* sk, int numLink) {
	log_debug(lggr, "Setup_Link");
	parseEdgeDoc(edgelink_loc);

	/// (1) Setup link ID, characteristics and initialize values.
	for (int i = 0; i < numLink; i++) {
//		l[i].linkID = i;
//		l[i].ffSpeed = 16;

		l[i].linkID = i;
		l[i].ffSpeed = 16;

		for (int sect = 0; sect < NUM_SECTION + 2; sect++) {
			l[i].lenSection[sect] = 100;

			for (int lane = 0; lane < NUM_LANE; lane++) {
				l[i].maxNumVeh[sect][lane] = 20;
				l[i].maxNumCF[sect][lane] = 3;

				l[i].numVehArr[sect][lane] = 0;

				for (int j = 0; j < MAX_VEC; j++) {
					l[i].vehIDArr[sect][lane][j] = -1;
					l[i].currLinkOrderArr[sect][lane][j] = -1;
					l[i].nextLinkIDArr[sect][lane][j] = -1;
					l[i].minTargetLaneArr[sect][lane][j] = -1;
					l[i].maxTargetLaneArr[sect][lane][j] = -1;
				}

				l[i].speed[sect][lane] = l[i].ffSpeed;

				l[i].numMLCL[sect][lane] = 0;
				l[i].numMLCR[sect][lane] = 0;
				l[i].numCF[sect][lane] = 0;

				for (int j = 0; j < MAX_VEC; j++) {
					l[i].vehMLC[sect][lane][j] = 0;
					l[i].vehOLC[sect][lane][j] = 0;
					l[i].vehCF[sect][lane][j] = 0;
				}
			}
		}

		for (int lane = 0; lane < NUM_LANE; lane++) {
			for (int j = 0; j < MAX_LEG; j++) {
				l[i].tempIDArr[lane][j] = -1;
				l[i].tempNumArr[lane][j] = 0;
			}
		}
	}

	/// (2) Setup source/sink cell ID, and initialize values.
	for (int i = 0; i < numLink; i++) {
		sc[i].sourceID = i;

		sc[i].numVeh = 0;
		for (int j = 0; j < MAX_SOURCE_VEC; j++) {
			sc[i].vehIDArr[j] = -1;
		}

		sk[i].sinkID = i;

		sk[i].numVeh = 0;
		for (int j = 0; j < MAX_SINK_VEC; j++) {
			sk[i].vehIDArr[j] = -1;
			sk[i].arrivalTime[j] = -1;
		}
	}
}

/*--------------------------------------------------------------------*/
/// @fn      void Setup_ConnectionCell(connection_cell*)
/// @brief   Function that setup the values of struct connection_cell.
/// @param   connection_cell* cc
/// @return  None
/*--------------------------------------------------------------------*/
void Setup_ConnectionCell(connection_cell* cc, int numCC) {
	log_debug(lggr, "Setup_ConnectionCell");

	/// (1) Set connection cell ID and previous, next link, and initialize flags.
	for (int i = 0; i < numCC; i++) {
		cc[i].ccID = i;

		cc[i].prevLinkID = i;
		for (int lane = 0; lane < NUM_LANE; lane++) {
			for (int j = 0; j < MAX_LEG; j++) {
				cc[i].nextLinkID[lane][j] = -1;
				cc[i].nextLane[lane][j] = -1;

				cc[i].numVehArr[lane][j] = 0;
				cc[i].numCFArr[lane][j] = 0;
			}

			for (int j = 0; j < MAX_VEC; j++) {
				cc[i].currLinkOrderArr[lane][j] = 0;
				cc[i].nextLinkIDArr[lane][j] = -1;
				cc[i].vehIDArr[lane][j] = 0;
			}
		}
	}

	cc[0].nextLinkID[0][0] = 1;
	cc[0].nextLane[0][0] = 0;
	cc[0].nextLinkID[1][0] = 1;
	cc[0].nextLane[1][0] = 1;
	cc[0].nextLinkID[2][0] = 1;
	cc[0].nextLane[2][0] = 2;
	cc[0].nextLinkID[3][0] = 1;
	cc[0].nextLane[3][0] = 3;

	cc[1].nextLinkID[0][0] = 6;
	cc[1].nextLane[0][0] = 0;
	cc[1].nextLinkID[1][0] = 4;
	cc[1].nextLane[1][0] = 1;
	cc[1].nextLinkID[2][0] = 4;
	cc[1].nextLane[2][0] = 2;
	cc[1].nextLinkID[3][0] = 4;
	cc[1].nextLane[3][0] = 3;
	cc[1].nextLinkID[3][1] = 2;
	cc[1].nextLane[3][1] = 3;

	cc[2].nextLinkID[0][0] = -2;
	cc[2].nextLinkID[1][0] = -2;
	cc[2].nextLinkID[2][0] = -2;
	cc[2].nextLinkID[3][0] = -2;

	cc[3].nextLinkID[0][0] = 8;
	cc[3].nextLane[0][0] = 0;
	cc[3].nextLinkID[1][0] = 6;
	cc[3].nextLane[1][0] = 1;
	cc[3].nextLinkID[2][0] = 6;
	cc[3].nextLane[2][0] = 2;
	cc[3].nextLinkID[3][0] = 6;
	cc[3].nextLane[3][0] = 3;
	cc[3].nextLinkID[3][1] = 4;
	cc[3].nextLane[3][1] = 3;

	cc[4].nextLinkID[0][0] = -2;
	cc[4].nextLinkID[1][0] = -2;
	cc[4].nextLinkID[2][0] = -2;
	cc[4].nextLinkID[3][0] = -2;

	cc[5].nextLinkID[0][0] = 2;
	cc[5].nextLane[0][0] = 0;
	cc[5].nextLinkID[1][0] = 8;
	cc[5].nextLane[1][0] = 1;
	cc[5].nextLinkID[2][0] = 8;
	cc[5].nextLane[2][0] = 2;
	cc[5].nextLinkID[3][0] = 8;
	cc[5].nextLane[3][0] = 3;
	cc[5].nextLinkID[3][1] = 6;
	cc[5].nextLane[3][1] = 3;

	cc[6].nextLinkID[0][0] = -2;
	cc[6].nextLinkID[1][0] = -2;
	cc[6].nextLinkID[2][0] = -2;
	cc[6].nextLinkID[3][0] = -2;

	cc[7].nextLinkID[0][0] = 4;
	cc[7].nextLane[0][0] = 0;
	cc[7].nextLinkID[1][0] = 2;
	cc[7].nextLane[1][0] = 1;
	cc[7].nextLinkID[2][0] = 2;
	cc[7].nextLane[2][0] = 2;
	cc[7].nextLinkID[3][0] = 2;
	cc[7].nextLane[3][0] = 3;
	cc[7].nextLinkID[3][1] = 8;
	cc[7].nextLane[3][1] = 3;

	cc[8].nextLinkID[0][0] = 9;
	cc[8].nextLane[0][0] = 0;
	cc[8].nextLinkID[1][0] = 9;
	cc[8].nextLane[1][0] = 1;
	cc[8].nextLinkID[2][0] = 9;
	cc[8].nextLane[2][0] = 2;
	cc[8].nextLinkID[3][0] = 9;
	cc[8].nextLane[3][0] = 3;

	cc[9].nextLinkID[0][0] = -2;
	cc[9].nextLinkID[1][0] = -2;
	cc[9].nextLinkID[2][0] = -2;
	cc[9].nextLinkID[3][0] = -2;

	/// (2) Set traffic signals.
	for (int i = 0; i < numCC; i++) {
		for (int lane = 0; lane < NUM_LANE; lane++) {
			for (int count = 0; count < MAX_CYCLE_DURATION; count++) {
				cc[i].trafficSignal[lane][count] = 0;
			}
		}
		cc[i].cycleDuration = 16;
	}

	for (int i = 0; i < numCC; i++) {
		for (int count = 0; count < MAX_LOOP; count++) {
			int trafficCycle = cc[i].cycleDuration;
			int trafficStep = count % trafficCycle;

			if (trafficStep < 5) {
				cc[1].trafficSignal[1][count] = 1;
				cc[1].trafficSignal[2][count] = 1;
				cc[1].trafficSignal[3][count] = 1;
				cc[5].trafficSignal[1][count] = 1;
				cc[5].trafficSignal[2][count] = 1;
				cc[5].trafficSignal[3][count] = 1;
			} else if (trafficStep < 8) {
				cc[1].trafficSignal[0][count] = 1;
				cc[5].trafficSignal[0][count] = 1;
			} else if (trafficStep < 13) {
				cc[3].trafficSignal[1][count] = 1;
				cc[3].trafficSignal[2][count] = 1;
				cc[3].trafficSignal[3][count] = 1;
				cc[7].trafficSignal[1][count] = 1;
				cc[7].trafficSignal[2][count] = 1;
				cc[7].trafficSignal[3][count] = 1;
			} else if (trafficStep < 16) {
				cc[3].trafficSignal[0][count] = 1;
				cc[7].trafficSignal[0][count] = 1;
			}

			cc[0].trafficSignal[0][count] = 1;
			cc[0].trafficSignal[1][count] = 1;
			cc[0].trafficSignal[2][count] = 1;
			cc[0].trafficSignal[3][count] = 1;
			cc[2].trafficSignal[0][count] = 1;
			cc[2].trafficSignal[1][count] = 1;
			cc[2].trafficSignal[2][count] = 1;
			cc[2].trafficSignal[3][count] = 1;
			cc[4].trafficSignal[0][count] = 1;
			cc[4].trafficSignal[1][count] = 1;
			cc[4].trafficSignal[2][count] = 1;
			cc[4].trafficSignal[3][count] = 1;
			cc[6].trafficSignal[0][count] = 1;
			cc[6].trafficSignal[1][count] = 1;
			cc[6].trafficSignal[2][count] = 1;
			cc[6].trafficSignal[3][count] = 1;
			cc[8].trafficSignal[0][count] = 1;
			cc[8].trafficSignal[1][count] = 1;
			cc[8].trafficSignal[2][count] = 1;
			cc[8].trafficSignal[3][count] = 1;
			cc[9].trafficSignal[0][count] = 1;
			cc[9].trafficSignal[1][count] = 1;
			cc[9].trafficSignal[2][count] = 1;
			cc[9].trafficSignal[3][count] = 1;
		}
	}
}

/*--------------------------------------------------------------------*/
/// @fn      void Evaluate_MLC(link, int)
/// @brief   Function that evaluate Mandatory Lane Change of a vehicle
///          and updates vehMLC Flag.
/// @param   link *l, int numLink
/// @return  None
/*--------------------------------------------------------------------*/
void Evaluate_MLC(roadlink *l) {
	log_debug(lggr, "Evaluate_MLC");

	for (int sect = 0; sect < NUM_SECTION + 2; sect++) {
		for (int lane = 0; lane < NUM_LANE; lane++) {
			for (int i = 0; i < l->numVehArr[sect][lane]; i++) {
				int minTL = l->minTargetLaneArr[sect][lane][i];
				int maxTL = l->maxTargetLaneArr[sect][lane][i];

				/// (1) Compare current lane with target lane and determine
				///     and update the value of vehMLC Flag.
				/// If vehicle should move left, set vehMLC Flag to -1
				if (lane > maxTL) {
					l->vehMLC[sect][lane][i] = -1;
					l->numMLCL[sect][lane]++;
				}
				/// If vehicle should move left, set vehMLC Flag to +1
				else if (lane < minTL) {
					l->vehMLC[sect][lane][i] = 1;
					l->numMLCR[sect][lane]++;
				} else {
					l->vehMLC[sect][lane][i] = 0;
				}
			}
		}
	}
}

/*--------------------------------------------------------------------*/
/// @fn      int Evaluate_Prob(double)
/// @brief   Function that randomly returns integer part or
///          (integer part+1) of a rational number.
/// @param   double inputProb
/// @return  intPart+1 when random > probPart
///          intPart  when random <= probPart
/*--------------------------------------------------------------------*/
int Evaluate_Prob(double inputProb) {
	log_debug(lggr, "Evaluate_Prob");

	// int intPart = (int)inputProb;
	// double probPart = inputProb - (double)intPart;

	// double random = ((rand() % 10)/10.);

	// return random > probPart ? (intPart+1):intPart;

	int intPart = (int) inputProb;
	return intPart;
}

/*--------------------------------------------------------------------*/
/// @fn      void Select_Veh()
/// @brief   Function that select vehicles of Optional Lane Change.
/// @param   link* l, int numOLC_L, int numOLC_R, int sect, int lane
/// @return  None
/*--------------------------------------------------------------------*/
void Select_Veh(roadlink* l, int numOLC_L, int numOLC_R, int sect, int lane) {
	log_debug(lggr, "Select_Veh");

	int numVeh = l->numVehArr[sect][lane];
	int possOLC[MAX_VEC] = { 0 };

	/// (1) Exclude vehMLC from candidates that can OLC.
	for (int i = 0; i < numVeh; i++) {
		if (l->vehMLC[sect][lane][i] != 0)
			possOLC[i] = 0;
		else
			possOLC[i] = 2;
	}

	/// (2) Consider when current lane is either maximum or minimum target lane.
	for (int i = 0; i < numVeh; i++) {
		int minTL = l->minTargetLaneArr[sect][lane][i];
		int maxTL = l->maxTargetLaneArr[sect][lane][i];

		if (lane == minTL) {
			if (possOLC[i] == 2)
				possOLC[i] = 1;
			else if (possOLC[i] == -1)
				possOLC[i] = 0;
		} else if (lane == maxTL) {
			if (possOLC[i] == 2)
				possOLC[i] = -1;
			else if (possOLC[i] == 1)
				possOLC[i] = 0;
		}
	}

	/// (3) Calculate number of vehicles that can go left, right, or both.
	int possBoth = 0;
	int possLeft = 0;
	int possRight = 0;
	int possLeftArr[MAX_VEC] = { 0 };
	int possRightArr[MAX_VEC] = { 0 };

	for (int i = 0; i < numVeh; i++) {
		if (possOLC[i] == 2) {
			possLeftArr[possLeft] = i;
			possRightArr[possRight] = i;
			possLeft++;
			possRight++;
			possBoth++;
		} else if (possOLC[i] == -1) {
			possLeftArr[possLeft] = i;
			possLeft++;
		} else if (possOLC[i] == 1) {
			possRightArr[possRight] = i;
			possRight++;
		}
	}

	/// (4) Consider when number of OLC is larger than possible vehicle of OLC
	if (possLeft < numOLC_L)
		numOLC_L = possLeft;
	if (possRight < numOLC_R)
		numOLC_R = possRight;

	int possTotal = possLeft + possRight - possBoth;
	while (possTotal < numOLC_L + numOLC_R) {
		numOLC_L--;
		if (possTotal >= numOLC_L + numOLC_R)
			break;
		numOLC_R--;
	}

	/// (5) Update values of vehOLC flags.
	int count_R = numOLC_R;
	int count_L = numOLC_L;
	if (numOLC_L == 0 && numOLC_R == 0)
		;

	else if (numOLC_L == 0) {
		while (count_R) {
			int randVeh = rand() % possRight;
			if (l->vehOLC[sect][lane][possRightArr[randVeh]] == 0) {
				l->vehOLC[sect][lane][possRightArr[randVeh]] = 1;
				count_R--;
			}
		}
	}

	else if (numOLC_R == 0) {
		while (count_L) {
			int randVeh = rand() % possLeft;
			if (l->vehOLC[sect][lane][possLeftArr[randVeh]] == 0) {
				l->vehOLC[sect][lane][possLeftArr[randVeh]] = -1;
				count_L--;
			}
		}
	}

	else if ((possLeft / numOLC_L) > (possRight / numOLC_R)) {
		while (count_R) {
			int randVeh = rand() % possRight;
			if (l->vehOLC[sect][lane][possRightArr[randVeh]] == 0) {
				l->vehOLC[sect][lane][possRightArr[randVeh]] = 1;
				count_R--;
			}
		}

		while (count_L) {
			int randVeh = rand() % possLeft;
			if (l->vehOLC[sect][lane][possLeftArr[randVeh]] == 0) {
				l->vehOLC[sect][lane][possLeftArr[randVeh]] = -1;
				count_L--;
			}
		}
	}

	else if ((possLeft / numOLC_L) <= (possRight / numOLC_R)) {
		while (count_L) {
			int randVeh = rand() % possLeft;
			if (l->vehOLC[sect][lane][possLeftArr[randVeh]] == 0) {
				l->vehOLC[sect][lane][possLeftArr[randVeh]] = -1;
				count_L--;
			}
		}

		while (count_R) {
			int randVeh = rand() % possRight;
			if (l->vehOLC[sect][lane][possRightArr[randVeh]] == 0) {
				l->vehOLC[sect][lane][possRightArr[randVeh]] = 1;
				count_R--;
			}
		}
	}
}

/*--------------------------------------------------------------------*/
/// @fn      void Evaluate_OLC(link*)
/// @brief   Function that evaluate Optional Lane Change of a vehicle
///          and updates vehOLC Flag.
/// @param   link *l
/// @return  None
/*--------------------------------------------------------------------*/
void Evaluate_OLC(roadlink *l) {
	log_debug(lggr, "Evaluate_OLC");

	for (int sect = 0; sect < NUM_SECTION + 2; sect++) {
		for (int lane = 0; lane < NUM_LANE; lane++) {
			int numMLC_L = l->numMLCL[sect][lane];
			int numMLC_R = l->numMLCR[sect][lane];
			double probLC_L, probLC_R;
			int diffSpeed_L = l->speed[sect][lane - 1] - l->speed[sect][lane];
			int diffSpeed_R = l->speed[sect][lane + 1] - l->speed[sect][lane];

			/// (1) Set probLC to zero in special cases.
			/// When current lane is leftmost, probLC_L = 0
			/// In other words, the vehicle cannot move left.
			if (lane == 0)
				probLC_L = 0;
			else
				probLC_L = (diffSpeed_L / l->ffSpeed)
						* l->numVehArr[sect][lane];

			/// When current lane is rightmost, probLC_R = 0
			/// In other words, the vehicle cannot move right.
			if (lane == NUM_LANE - 1)
				probLC_R = 0;
			else
				probLC_R = (diffSpeed_R / l->ffSpeed)
						* l->numVehArr[sect][lane];

			/// (2) Evaluate number of OLC by subtrating number of MLC
			///     from the total number of LC.
			int numOLC_L = Evaluate_Prob(probLC_L) - numMLC_L;
			int numOLC_R = Evaluate_Prob(probLC_R) - numMLC_R;

			/// numOLC cannot be smaller than zero.
			if (numOLC_L < 0)
				numOLC_L = 0;
			if (numOLC_R < 0)
				numOLC_R = 0;

			/// (3) Select vehicle to change lane.
			Select_Veh(l, numOLC_L, numOLC_R, sect, lane);
		}
	}
}

/*--------------------------------------------------------------------*/
/// @fn      void MoveLC()
/// @brief   Function that moves elements of one array to another array.
/// @param   int* fromArr, int fromArrSize, int* toArr, int toArrSize, int index
/// @return  None
/*--------------------------------------------------------------------*/
void MoveLC(int* fromArr, int fromArrSize, int* toArr, int toArrSize,
		int index) {
	log_debug(lggr, "MoveLC");

	double fromArrLoc = ((double) fromArrSize / (index + 1));
	int toArrLoc = Evaluate_Prob(toArrSize / fromArrLoc);

	for (int i = fromArrSize - 1; i > toArrLoc; i--) {
		toArr[i] = toArr[i - 1];
	}
	toArr[toArrLoc] = fromArr[index];

	for (int i = index; i < fromArrSize; i++) {
		fromArr[i] = fromArr[i + 1];
	}
}

/*--------------------------------------------------------------------*/
/// @fn      void LCSim()
/// @brief   Function to move vehicles that perform lane change.
/// @param   link* l
/// @return  None
/*--------------------------------------------------------------------*/
void LCSim(roadlink* l) {
	log_debug(lggr, "LCSim");

	for (int sect = 0; sect < NUM_SECTION + 2; sect++) {
		for (int lane = 0; lane < NUM_LANE; lane++) {
			for (int i = 0; i < MAX_VEC; i++) {
				if (l->vehMLC[sect][lane][i] == 1) {
					if (l->numVehArr[sect][lane + 1] < MAX_VEC) {
						MoveLC(l->vehIDArr[sect][lane],
								l->numVehArr[sect][lane],
								l->vehIDArr[sect][lane + 1],
								l->numVehArr[sect][lane + 1], i + 1);
						MoveLC(l->currLinkOrderArr[sect][lane],
								l->numVehArr[sect][lane],
								l->currLinkOrderArr[sect][lane + 1],
								l->numVehArr[sect][lane + 1], i);
						MoveLC(l->minTargetLaneArr[sect][lane],
								l->numVehArr[sect][lane],
								l->minTargetLaneArr[sect][lane + 1],
								l->numVehArr[sect][lane + 1], i);
						MoveLC(l->maxTargetLaneArr[sect][lane],
								l->numVehArr[sect][lane],
								l->maxTargetLaneArr[sect][lane + 1],
								l->numVehArr[sect][lane + 1], i);
						l->numVehArr[sect][lane + 1]++;
						l->numVehArr[sect][lane]--;
					}
				}

				else if (l->vehMLC[sect][lane][i] == -1) {
					if (l->numVehArr[sect][lane - 1] < MAX_VEC) {
						MoveLC(l->vehIDArr[sect][lane],
								l->numVehArr[sect][lane],
								l->vehIDArr[sect][lane - 1],
								l->numVehArr[sect][lane - 1], i);
						MoveLC(l->currLinkOrderArr[sect][lane],
								l->numVehArr[sect][lane],
								l->currLinkOrderArr[sect][lane - 1],
								l->numVehArr[sect][lane - 1], i);
						MoveLC(l->minTargetLaneArr[sect][lane],
								l->numVehArr[sect][lane],
								l->minTargetLaneArr[sect][lane - 1],
								l->numVehArr[sect][lane - 1], i);
						MoveLC(l->maxTargetLaneArr[sect][lane],
								l->numVehArr[sect][lane],
								l->maxTargetLaneArr[sect][lane - 1],
								l->numVehArr[sect][lane - 1], i);
						l->numVehArr[sect][lane - 1]++;
						l->numVehArr[sect][lane]--;
					}
				}
			}
		}
	}

	for (int sect = 0; sect < NUM_SECTION + 2; sect++) {
		for (int lane = 0; lane < NUM_LANE; lane++) {
			for (int i = 0; i < MAX_VEC; i++) {
				if (l->vehOLC[sect][lane][i]
						== 1&& l->numVehArr[sect][lane] < MAX_VEC) {
					MoveLC(l->vehIDArr[sect][lane], l->numVehArr[sect][lane],
							l->vehIDArr[sect][lane + 1],
							l->numVehArr[sect][lane + 1], i);
					MoveLC(l->currLinkOrderArr[sect][lane],
							l->numVehArr[sect][lane],
							l->currLinkOrderArr[sect][lane + 1],
							l->numVehArr[sect][lane + 1], i);
					MoveLC(l->minTargetLaneArr[sect][lane],
							l->numVehArr[sect][lane],
							l->minTargetLaneArr[sect][lane + 1],
							l->numVehArr[sect][lane + 1], i);
					MoveLC(l->maxTargetLaneArr[sect][lane],
							l->numVehArr[sect][lane],
							l->maxTargetLaneArr[sect][lane + 1],
							l->numVehArr[sect][lane + 1], i);
					l->numVehArr[sect][lane + 1]++;
					l->numVehArr[sect][lane]--;
				} else if (l->vehOLC[sect][lane][i]
						== -1&& l->numVehArr[sect][lane] < MAX_VEC) {
					MoveLC(l->vehIDArr[sect][lane], l->numVehArr[sect][lane],
							l->vehIDArr[sect][lane - 1],
							l->numVehArr[sect][lane - 1], i);
					MoveLC(l->currLinkOrderArr[sect][lane],
							l->numVehArr[sect][lane],
							l->currLinkOrderArr[sect][lane - 1],
							l->numVehArr[sect][lane - 1], i);
					MoveLC(l->minTargetLaneArr[sect][lane],
							l->numVehArr[sect][lane],
							l->minTargetLaneArr[sect][lane - 1],
							l->numVehArr[sect][lane - 1], i);
					MoveLC(l->maxTargetLaneArr[sect][lane],
							l->numVehArr[sect][lane],
							l->maxTargetLaneArr[sect][lane - 1],
							l->numVehArr[sect][lane - 1], i);
					l->numVehArr[sect][lane - 1]++;
					l->numVehArr[sect][lane]--;
				}
			}
		}
	}
}

/*--------------------------------------------------------------------*/
/// @fn      void Evaluate_CF()
/// @brief   Function that evaluate CF of a vehicle and updates vehCF Flag.
/// @param   link* l
/// @return  None
/*--------------------------------------------------------------------*/
void Evaluate_CF(roadlink* l) {
	log_debug(lggr, "Evaluate_CF");

	double wSpeed = 4.2;

	for (int sect = 0; sect < NUM_SECTION; sect++) {
		for (int lane = 0; lane < NUM_LANE; lane++) {
			l->numCF[sect][lane] =
			//MIN(MIN((l->ffSpeed / 3.6 * SECONDS_PER_STEP) / l->lenSection[sect] * l->numVeh[sect][lane], l->maxNumCF[sect][lane]),
			//	MIN(l->maxNumCF[sect+1][lane], wSpeed * SECONDS_PER_STEP / length * (l->maxNumCF[sect][lane] - l->numVeh[sect][lane])));
					MIN(l->numVehArr[sect][lane],
							MIN(l->maxNumCF[sect][lane], wSpeed / l->ffSpeed * (l->maxNumVeh[sect+1][lane] - l->numVehArr[sect+1][lane])))
							* l->ffSpeed * SECONDS_PER_STEP
							/ l->lenSection[sect];

			for (int i = 0; i < l->numCF[sect][lane]; i++) {
				l->vehCF[sect][lane][i] = 1;
			}
		}
	}
}

/*--------------------------------------------------------------------*/
/// @fn      void MoveCF()
/// @brief   Function that moves elements of one array to another array.
/// @param   int* fromArr, int fromArrSize, int* toArr, int toArrSize, int index
/// @return  None
/*--------------------------------------------------------------------*/
void MoveCF(int* fromArr, int fromArrSize, int* toArr, int toArrSize,
		int index) {
	log_debug(lggr, "MoveCF");

	toArr[toArrSize] = fromArr[index];

	for (int i = index; i < fromArrSize; i++) {
		fromArr[i] = fromArr[i + 1];
	}
}

/*--------------------------------------------------------------------*/
/// @fn      void CFsim()
/// @brief   Function to move vehicles that perform CF.
/// @param   link *l
/// @return  None
/*--------------------------------------------------------------------*/
void CFsim(roadlink *l) {
	log_debug(lggr, "CFsim");

	for (int sect = NUM_SECTION; sect > 0; sect--) {
		for (int lane = 0; lane < NUM_LANE; lane++) {
			for (int i = 0; i < MAX_VEC; i++) {
				if (l->vehCF[sect][lane][i]
						== 1&& l->numVehArr[sect+1][lane] < MAX_VEC) {
					MoveCF(l->vehIDArr[sect][lane], l->numVehArr[sect][lane],
							l->vehIDArr[sect + 1][lane],
							l->numVehArr[sect + 1][lane], i);
					MoveCF(l->currLinkOrderArr[sect][lane],
							l->numVehArr[sect][lane],
							l->currLinkOrderArr[sect + 1][lane],
							l->numVehArr[sect + 1][lane], i);
					MoveCF(l->minTargetLaneArr[sect][lane],
							l->numVehArr[sect][lane],
							l->minTargetLaneArr[sect + 1][lane],
							l->numVehArr[sect + 1][lane], i);
					MoveCF(l->maxTargetLaneArr[sect][lane],
							l->numVehArr[sect][lane],
							l->maxTargetLaneArr[sect + 1][lane],
							l->numVehArr[sect + 1][lane], i);
					l->numVehArr[sect + 1][lane]++;
					l->numVehArr[sect][lane]--;
				}
			}
		}
	}
}

/*--------------------------------------------------------------------*/
/// @fn      int Find_Index()
/// @brief   Function that find the index of a value in an array.
/// @param   int* findArr, int findArrSize, int findValue,
/// @return  index if the given value exists in the given array.
///          -1 if the given value doesn't exist in the givne array.
/*--------------------------------------------------------------------*/
int Find_Index(int* findArr, int findArrSize, int findValue) {
	log_debug(lggr, "Find_Index");

	for (int i = 0; i < findArrSize; i++) {
		if (findArr[i] == findValue)
			return i;
	}

	return -1;
}

/*--------------------------------------------------------------------*/
/// @fn      void Update_Link_TempArr()
/// @brief   Function that update tempIDArr and tempNumArr.
/// @param   link* l
/// @return  None
/*--------------------------------------------------------------------*/
void Update_tempArr(roadlink* l) {
	log_debug(lggr, "Update_tempArr");

	for (int lane = 0; lane < NUM_LANE; lane++) {
		int tempArrSize = 0;

		for (int i = 0; i < l->numVehArr[NUM_SECTION][lane]; i++) {
			int tempArrIndex = Find_Index(l->tempIDArr[lane], MAX_LEG,
					l->nextLinkIDArr[NUM_SECTION][lane][i]);

			if (tempArrIndex == -1) {
				l->tempIDArr[lane][tempArrSize] =
						l->nextLinkIDArr[NUM_SECTION][lane][i];
				l->tempNumArr[lane][tempArrSize] += 1;
				tempArrSize += 1;
			}

			else
				l->tempNumArr[lane][tempArrIndex] += 1;
		}
	}
}

/*--------------------------------------------------------------------*/
/// @fn      void Relay_numVeh()
/// @brief   Function that relay numVeh of the last cell of a previous
///          link to the virtual cell of the next link.
/// @param   link* prevl, link* nextl, int nextLane, connection_cell* cc,
///          int currLane, int i
/// @return  None
/*--------------------------------------------------------------------*/
void Relay_numVeh(roadlink* prevl, roadlink* nextl, int nextLane,
		connection_cell* cc, int currLane, int leg, int currLink) {

	log_debug(lggr, "Relay_numVeh");

	/// (1) Relay numVeh from tempArr of previous link to next link
	int index = Find_Index(prevl->tempIDArr[currLane], MAX_LEG,
			cc->nextLinkID[currLane][leg]);

	if (index != -1) {
		/// (1-1) tempArr of previous link -> connection cell
		cc->numVehArr[currLane][leg] = prevl->tempNumArr[currLane][index];

		/// (1-2) connection cell -> virtual cell of next link
		nextl->numVehArr[0][nextLane] = cc->numVehArr[currLane][leg];
	}
}

/*--------------------------------------------------------------------*/
/// @fn      void Relay_numCF()
/// @brief   Function that relay numCF of the virtual cell of a next
///          link to the last cell of the previous link.
/// @param   link* prevl, link* nextl, int nextLane, connection_cell* cc, int currLoop, int currLane, int i
/// @return  None
/*--------------------------------------------------------------------*/
void Relay_numCF(roadlink* prevl, roadlink* nextl, int nextLane,
		connection_cell* cc, int currLoop, int currLane, int leg) {

	log_debug(lggr, "Relay_numCF");

	/// (1) virtual cell of next link -> connection cell
	if (cc->trafficSignal[currLane][currLoop] == 0) {
		cc->numCFArr[currLane][currLoop] = 0;
	} else
		cc->numCFArr[currLane][leg] = nextl->numCF[0][nextLane];

	/// (2) connection cell -> previous link
	int index = Find_Index(prevl->tempIDArr[currLane], MAX_LEG,
			cc->nextLinkID[currLane][leg]);

	prevl->tempNumArr[currLane][index] = cc->numVehArr[currLane][leg];
}

/*--------------------------------------------------------------------*/
/// @fn      void Evaluate_Eff_numCF()
/// @brief   Function that evaluates effective numCF.
/// @param   link* l, connection_cell* cc
/// @return  None
/*--------------------------------------------------------------------*/
void Evaluate_Eff_numCF(roadlink* l) {

	log_debug(lggr, "Evaluate_Eff_numCF");

	for (int lane = 0; lane < NUM_LANE; lane++) {
		int tempArrSize = 0;
		int totalNumCF = 0;

		for (int i = 0; i < 3; i++) {
			totalNumCF += l->tempNumArr[lane][i];

			if (l->tempIDArr[lane][i] == -1) {
				tempArrSize = i;
				break;
			}
		}

		int effNumCF = 0;
		for (int count = 0;
				count < MIN(totalNumCF, l->maxNumCF[NUM_SECTION][lane]);
				count++) {
			int currNextLinkID = l->nextLinkIDArr[NUM_SECTION][lane][count];
			int index = Find_Index(l->tempIDArr[lane], tempArrSize,
					currNextLinkID);

			if (l->tempNumArr[lane][index] == 0)
				break;
			l->tempNumArr[lane][index]--;

			effNumCF++;
		}

		l->numCF[NUM_SECTION][lane] = effNumCF;
	}

	for (int lane = 0; lane < NUM_LANE; lane++) {
		for (int i = 0; i < l->numCF[NUM_SECTION][lane]; i++) {
			l->vehCF[NUM_SECTION][lane][i] = 1;
		}
	}
}

/*--------------------------------------------------------------------*/
/// @fn      void Update_nextLink()
/// @brief   Function update variables of first cell of a link using
///          variables of connection cell.
/// @param   vehicle* v, link* prevl, link* nextl, int nextLane, connection_cell* cc, int currLoop, int currLane
/// @return  None
/*--------------------------------------------------------------------*/
void Update_nextLink(vehicle* v, roadlink* prevl, roadlink* nextl, int nextLane,
		connection_cell* cc, int currLane) {

	log_debug(lggr, "Update_nextLink");

	/// (1) previous link -> connection cell
	for (int i = 0; i < MAX_VEC; i++) {
		cc->currLinkOrderArr[currLane][i] = prevl->currLinkOrderArr[NUM_SECTION
				+ 1][currLane][i];
		cc->nextLinkIDArr[currLane][i] =
				prevl->nextLinkIDArr[NUM_SECTION + 1][currLane][i];
		cc->vehIDArr[currLane][i] =
				prevl->vehIDArr[NUM_SECTION + 1][currLane][i];
	}

	/// (2) connection cell -> first cell of next link
	int index = nextl->numVehArr[1][currLane];

	for (int i = 0; i < MAX_VEC; i++) {
		int currOrder = cc->currLinkOrderArr[currLane][i];
		int currVehID = cc->vehIDArr[currLane][i];

		if (cc->nextLinkIDArr[currLane][i] == nextl->linkID) {
			nextl->vehIDArr[1][nextLane][index] = cc->vehIDArr[currLane][i];
			nextl->currLinkOrderArr[1][nextLane][index] =
					cc->currLinkOrderArr[currLane][i] + 1;
			nextl->nextLinkIDArr[1][nextLane][index] =
					v[currVehID].path[currOrder + 1];
			nextl->minTargetLaneArr[1][nextLane][index] =
					v[currVehID].minTargetLane[currOrder + 1];
			nextl->maxTargetLaneArr[1][nextLane][index] =
					v[currVehID].maxTargetLane[currOrder + 1];

			index++;
		}
	}

	nextl->numVehArr[1][nextLane] = index;
}

/*--------------------------------------------------------------------*/
/// @fn      void Reset_ConnectionCell()
/// @brief   Function that resets variables of connection cell.
/// @param   connection_cell* cc
/// @return  None
/*--------------------------------------------------------------------*/
void Reset_ConnectionCell(connection_cell* cc) {

	log_debug(lggr, "Reset_ConnectionCell");

	for (int lane = 0; lane < NUM_LANE; lane++) {
		for (int i = 0; i < 3; i++) {
			cc->numVehArr[lane][i] = 0;
			cc->numCFArr[lane][i] = 0;
		}

		for (int i = 0; i < MAX_VEC; i++) {
			cc->nextLinkIDArr[lane][i] = 0;
			cc->vehIDArr[lane][i] = 0;
			cc->currLinkOrderArr[lane][i] = 0;
		}
	}
}

/*--------------------------------------------------------------------*/
/// @fn      void Reset_Link()
/// @brief   Function that resets flags and temp variables of link.
/// @param   link* l
/// @return  None
/*--------------------------------------------------------------------*/
void Reset_Link(roadlink* l) {

	log_debug(lggr, "Reset_Link");

	double wSpeed = 4.2;

	for (int sect = 0; sect < NUM_SECTION + 2; sect++) {
		for (int lane = 0; lane < NUM_LANE; lane++) {
			int jamdensity = l->maxNumVeh[sect][lane] / l->lenSection[sect]; //도로가 막히기 시작하는 density (veh/km), 링크 특성(고정값)
			int density = l->numVehArr[sect][lane] / l->lenSection[sect]; //도로의 현재 density (veh/km), 시뮬레이션 스텝마다 업데이트

			l->speed[sect][lane] =
					MAX(0,
							MIN(l->ffSpeed, (-wSpeed + (wSpeed * jamdensity / density))));
			l->numMLCL[sect][lane] = 0;
			l->numMLCR[sect][lane] = 0;
			l->numCF[sect][lane] = 0;

			l->numVehArr[0][lane] = 0;
			l->numVehArr[NUM_SECTION + 1][lane] = 0;

			for (int i = 0; i < MAX_VEC; i++) {
				l->vehMLC[sect][lane][i] = 0;
				l->vehOLC[sect][lane][i] = 0;
				l->vehCF[sect][lane][i] = 0;

				l->vehIDArr[NUM_SECTION + 1][lane][i] = -1;
				l->currLinkOrderArr[NUM_SECTION + 1][lane][i] = -1;
				l->nextLinkIDArr[NUM_SECTION + 1][lane][i] = -1;
				l->minTargetLaneArr[NUM_SECTION + 1][lane][i] = -1;
				l->maxTargetLaneArr[NUM_SECTION + 1][lane][i] = -1;
			}
		}
	}

	for (int lane = 0; lane < NUM_LANE; lane++) {
		for (int i = 0; i < 3; i++) {
			l->tempIDArr[lane][i] = -1;
			l->tempNumArr[lane][i] = 0;
		}
	}
}

/*--------------------------------------------------------------------*/
/// @fn      void Reset_Sink()
/// @brief   Function that resets flags and temp variables of sink.
/// @param   sink_cell* sk
/// @return  None
/*--------------------------------------------------------------------*/
void Reset_Sink(sink_cell* sk) {

	log_debug(lggr, "Reset_Sink");

	sk->numVeh = 0;

	for (int i = 0; i < MAX_SINK_VEC; i++) {
		sk->vehIDArr[i] = -1;
		sk->arrivalTime[i] = 0;
	}
}

/*--------------------------------------------------------------------*/
/// @fn      void Update_Source()
/// @brief   Function that update source in every UPDATE_INTERVAL.
/// @param   vehicle* v, int numVeh, source_cell* sc, int currLoop
/// @return  None
/*--------------------------------------------------------------------*/
void Update_Source(vehicle* v, int numVeh, source_cell* sc, int currLoop) {

	log_debug(lggr, "Update_Source");

	// once in 60 step
	// vehicle scan
	int j = 0;
	for (int i = 0; i < numVeh; i++) {
		if (currLoop <= v[i].departTime
				&& v[i].departTime < (currLoop + UPDATE_INTERVAL)) {
			sc[v[i].initLink].vehIDArr[j] = v[i].vehID;
			j++;
			sc[v[i].initLink].numVeh++;
		}
	}
}

/*--------------------------------------------------------------------*/
/// @fn      void Start_Path()
/// @brief   Function that moves vehicles from source cell to initial
///          link.
/// @param   link* l, source_cell* sc, int numLink
/// @return  None
/*--------------------------------------------------------------------*/
void Start_Path(roadlink* l, source_cell* sc, int numLink) {
	log_debug(lggr, "Start_Path");

	if (l->numVehArr[3][3] < MAX_VEC) {
		int numEnter = MIN(l->maxNumCF[2][3], (MAX_VEC - l->numVehArr[3][3]));

		for (int j = 0; j < numEnter; j++) {
			MoveCF(sc->vehIDArr, sc->numVeh, l->vehIDArr[3][3],
					l->numVehArr[3][3], 0);

			sc->numVeh--;
			l->numVehArr[3][3]++;
		}
	}
}

/*--------------------------------------------------------------------*/
/// @fn      void Remove_Value()
/// @brief   Function that removes elements of an array.
/// @param   int* fromArr, int fromArrSize, int index
/// @return  None
/*--------------------------------------------------------------------*/
void Remove_Value(int* fromArr, int fromArrSize, int index) {
	log_debug(lggr, "Remove_Value");

	for (int i = MAX_VEC - 1; i >= 0; i--) {
		fromArr[i] = fromArr[i - 1];
	}
}

/*--------------------------------------------------------------------*/
/// @fn      void End_Path()
/// @brief   Function that moves vehicles from the last link of their
///          path to sink cell.
/// @param   link* l, sink_cell* sk, int numLink
/// @return  None
/*--------------------------------------------------------------------*/
void End_Path(roadlink* l, sink_cell* sk, int numLink) {
	log_debug(lggr, "EndPath");
	for (int lane = 0; lane < NUM_LANE; lane++) {
		for (int i = 0; i < MAX_VEC; i++) {
			if (l->nextLinkIDArr[3][lane][i] == -2) {
				MoveCF(l->vehIDArr[3][lane], l->numVehArr[3][lane],
						sk->vehIDArr, sk->numVeh, i);
				Remove_Value(l->currLinkOrderArr[3][lane],
						l->numVehArr[3][lane], i);
				Remove_Value(l->nextLinkIDArr[3][lane], l->numVehArr[3][lane],
						i);
				Remove_Value(l->minTargetLaneArr[3][lane],
						l->numVehArr[3][lane], i);
				Remove_Value(l->maxTargetLaneArr[3][lane],
						l->numVehArr[3][lane], i);

				sk->numVeh++;
				l->numVehArr[3][lane]--;
			}
		}
	}
}

/*--------------------------------------------------------------------*/
/// @fn      void SimulationStep()
/// @brief   Function that manages the whole process of simulation.
/// @param   link l[], int numLink, connection_cell cc[], int numCC,
///          vehicle* v, int numVeh, int numLoop
/// @return  None
/*--------------------------------------------------------------------*/
void SimulationStep(vehicle* v, int numVeh, roadlink l[], source_cell sc[],
		sink_cell sk[], connection_cell cc[], int numLink, int numLoop) {

	log_debug(lggr, "SimulationStep");
	for (int count = 0; count < numLoop; count++) {

		printf("\nSALTTime: %d\n", count);
		PrintOutput(mylink, numLink);

		int updateCycle = UPDATE_INTERVAL;
		int updateStep = count % UPDATE_INTERVAL;

		if (updateStep == 0) {
			for (int link = 0; link < numLink; link++) {
				//PrintOutput();
				Reset_Sink(&sk[link]);
				Update_Source(v, numVeh, &sc[link], count);
			}
		}

		for (int link = 0; link < numLink; link++) {
			Reset_Link(&l[link]);

			End_Path(&l[link], &sk[link], numLink);
			Start_Path(&l[link], &sc[link], numLink);

			Evaluate_MLC(&l[link]);
			Evaluate_OLC(&l[link]);
			LCSim(&l[link]);

			Update_tempArr(&l[link]);
		}

		for (int i = 0; i < numLink; i++) {
			for (int lane = 0; lane < NUM_LANE; lane++) {
				for (int leg = 0; leg < MAX_LEG; leg++) {
					if (cc[i].nextLinkID[lane][leg] >= 0) {
						Relay_numVeh(&l[cc[i].prevLinkID],
								&l[cc[i].nextLinkID[lane][leg]],
								cc[i].nextLane[lane][leg], &cc[i], lane, leg,
								i);
					}
				}
			}
			Reset_ConnectionCell(&cc[i]);
		}

		for (int link = 0; link < numLink; link++) {
			Evaluate_CF(&l[link]);
		}

		for (int i = 0; i < numLink; i++) {
			for (int lane = 0; lane < NUM_LANE; lane++) {
				for (int leg = 0; leg < MAX_LEG; leg++) {
					if (cc[i].nextLinkID[lane][leg] >= 0) {
						Relay_numCF(&l[cc[i].prevLinkID],
								&l[cc[i].nextLinkID[lane][leg]],
								cc[i].nextLane[lane][leg], &cc[i], count, lane,
								leg);
					}
				}
			}
			Reset_ConnectionCell(&cc[i]);
		}

		for (int link = 0; link < numLink; link++) {
			Evaluate_Eff_numCF(&l[link]);
			CFsim(&l[link]);
		}

		for (int i = 0; i < numLink; i++) {
			for (int lane = 0; lane < NUM_LANE; lane++) {
				for (int leg = 0; leg < MAX_LEG; leg++) {
					if (cc[i].nextLinkID[lane][leg] >= 0) {
						Update_nextLink(v, &l[cc[i].prevLinkID],
								&l[cc[i].nextLinkID[lane][leg]],
								cc[i].nextLane[lane][leg], &cc[i], lane);
					}
				}
			}
			Reset_ConnectionCell(&cc[i]);
		}
	}
}

double get_time_ms() {
	struct timeval t;
	gettimeofday(&t, NULL);

	return (t.tv_sec + (t.tv_usec / 1000000.0)) * 1000.0;
}

void PrintOutput(roadlink l[], int numLink) {
	for (int link = 0; link < numLink; link++) {
		printf("link %2d:\t", link);

		for (int sect = 0; sect < NUM_SECTION + 2; sect++) {
			for (int lane = 0; lane < NUM_LANE; lane++) {
				printf("%2d ", l[link].numVehArr[sect][lane]);
			}
			printf(" | ");
		}
		printf("\n");
	}


}

int main(int argc, char *argv[]) {
	lggr= Logger_create();
	lggr->level = LOG_DEBUG;

//	log_debug(l, "%d", __LINE__);
//	log_info(l, "Hello world");
//	foo = "Information";
//	log_warn(l, "Foo[%-30s] Bar[%d]", foo, bar);
//	log_error(l, "Foo Bar");

	srand(time(NULL));

	int numVeh = (int) atoi(argv[1]);  /// number of vehicles
	int numLink = (int) atoi(argv[2]); /// number of links
	int numLoop = (int) atoi(argv[3]);   /// number of simulation steps

	log_info(lggr, "# of vehicles: %s", argv[1]);
	log_info(lggr, "# of links: %s", argv[2]);
	log_info(lggr, "# of simulation steps: %s", argv[3]);

	myveh = (vehicle*) calloc(numVeh, sizeof(vehicle));
	mylink = (roadlink*) calloc(numLink, sizeof(roadlink));
	mysource = (source_cell*) malloc(numLink * sizeof(source_cell));
	mysink = (sink_cell*) malloc(numLink * sizeof(sink_cell));
	mycon = (connection_cell*) malloc(numLink * sizeof(connection_cell));

	Setup_Veh(myveh, numVeh);
	Setup_Link(myveh, numVeh, mylink, mysource, mysink, numLink);
	Setup_ConnectionCell(mycon, numLink);

	double start, stop;
	start = get_time_ms();
	SimulationStep(myveh, numVeh, mylink, mysource, mysink, mycon, numLink,
			numLoop);
	stop = get_time_ms();

	double result = stop - start;
	log_info(lggr, "Elapsed Time: %f", result);
	//PrintOutput(mylink, numLink);
	Logger_free(lggr);
	return 0;
}
