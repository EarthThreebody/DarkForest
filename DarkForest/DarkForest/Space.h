#ifndef SPACE_H_INCLUDED
#define SPACE_H_INCLUDED

#include <map>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "SystemTool.h"

class SolarSystem;

namespace{
	typedef std::map<double,SolarSystem *> SpaceMap;
	typedef std::map<double,SolarSystem *>::value_type SpaceMapValue;
}

class Space{
private:
	SpaceMap m_space_map;

public:
	void SPaceMap();
	void getIn(SolarSystem * in);
};


#endif /* SPACE_H_INCLUDED */