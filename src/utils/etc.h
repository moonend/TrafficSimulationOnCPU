/*
 * etc.h
 *
 *  Created on: 2018. 2. 2.
 *      Author: SDJ
 */

#ifndef ETC_H_
#define ETC_H_

#include <json/json.h>
#include <utils/config.h>
#include <string>


//parse json file using jsoncpp library
int testFunc(int a);
SALT::Result getJSONObject(std::string const& file_path, Json::Value& root);
std::string convertJSONObject2string(const Json::Value&  _obj);
std::string jv2string(Json::Value& _input);
int jv2int(Json::Value& _input);
float jv2float(Json::Value& _input);

//parse json file using boost


#endif /* ETC_H_ */
