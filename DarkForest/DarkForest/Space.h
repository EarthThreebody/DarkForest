#ifndef SPACE_H_INCLUDED
#define SPACE_H_INCLUDED

#include <iostream>
#include <vector>
#include <map>

#include "SystemTool.h"

class SolarSystem;

namespace{
	typedef SolarSystem * SolarSystemPtr;
	typedef std::map<double,SolarSystemPtr> SpaceMap;
	typedef std::map<double,SolarSystemPtr>::value_type SpaceMapValue;
}

class Space{
private:
	SpaceMap m_space_map;

public:
	void SPaceMap();
	void getIn(SolarSystemPtr in);
	bool searchAround(SolarSystemPtr self,std::vector<SolarSystemPtr> & neighbours);
};


#endif /* SPACE_H_INCLUDED */