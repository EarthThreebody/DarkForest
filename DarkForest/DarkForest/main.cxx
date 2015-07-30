#ifdef WIN32
#include <windows>
#endif

#ifndef __MAIN__
#define __MAIN__

#include <iostream>
#include <ctime>
#include "SolarSystem.h"
#include "Space.h"

int main(){
	//std::srand(std::time(0));

	Space this_space;

	SolarSystem three_body(&this_space,"ThreeBody",SolarSystemState::ENEMY);
	SolarSystem test(&this_space);
	SolarSystem sun(&this_space,"Sun",SolarSystemState::PLAYER);

	while(true){
		std::cout<<"-------New Report-------"<<std::endl;
		sun.takeAction(three_body);
		three_body.takeAction(sun);
		test.takeAction(sun);

		//Can choose explore, develop, hide, do nothing etc. Comsuming diff resources respectively
		//When exploring, have chance to find resources(higher tech, higher possibility)

		//TODO:Use absolute position rather than 2D position? random generate distance
		//TODO:static map/set to save all solar objects

		std::cout<<"------------------------"<<std::endl;

		if(sun.dead() || three_body.dead())
			break;
	}

	system("PAUSE");
}

#endif /* __MAIN__ */