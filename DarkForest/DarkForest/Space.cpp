#include "Space.h"
#include "SolarSystem.h"

void Space::getIn(SolarSystem * in){

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