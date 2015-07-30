#include "Space.h"
#include "SolarSystem.h"

#include <stdlib.h>

void Space::getIn(SolarSystemPtr in){

	double position = double(SystemTool::genRandom(1000))/(1.0+double(SystemTool::genRandom(10)));

	if(m_space_map.insert(SpaceMapValue(position,in)).second){	 //second = insert success or not
		in->setPosition(position);
		SystemTool::logInfo("["+in->getName()+"] is in the space. With position ["+SystemTool::toString(in->getPosition())+"]");
	} else {
		//Join again
		SystemTool::systemSleep(1);
		SystemTool::logInfo("["+in->getName()+"] is lost. Trying to get into the space again.");
		getIn(in);
	}
}

bool Space::searchAround(SolarSystemPtr self,std::vector<SolarSystemPtr> & neighbours){
	double range = self->getExploreRange();
	double self_position = self->getPosition();

	SpaceMap::const_iterator iter = m_space_map.begin();
	for(;iter!=m_space_map.end();++iter){

		if(self == iter->second) continue;

		double neighbour_position = iter->first;
		if( range > abs(neighbour_position - self_position) )
			neighbours.push_back(iter->second);
	}

	return !neighbours.empty();
}