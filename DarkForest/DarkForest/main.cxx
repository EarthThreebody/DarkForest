#ifdef WIN32
#include <windows>

#endif

#ifndef __MAIN__
#define __MAIN__

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include "SolarSystem.h"
#include "Space.h"

int main(){
	//std::srand(std::time(0));

	Space this_space;

	std::vector<SolarSystem *> undeveloped_stars_ptr;
	for(int i=0;i<15;++i){
		SolarSystem * new_star_ptr = new SolarSystem;
		new_star_ptr->joinSpace(&this_space);
		undeveloped_stars_ptr.push_back(new_star_ptr);
	}

	SolarSystem two_body(&this_space,"TwoBody",SolarSystemState::ENEMY);
	SolarSystem three_body(&this_space,"ThreeBody",SolarSystemState::ENEMY);
	SolarSystem sun(&this_space,"Sun",SolarSystemState::PLAYER);
	system("PAUSE");
	system("cls");

	while(true){
		std::cout<<"-----------------------New Report-----------------------------"<<std::endl;

		for(std::vector<SolarSystem *>::iterator it=undeveloped_stars_ptr.begin();it!=undeveloped_stars_ptr.end();++it){
			(*it)->takeAction();
		}

		three_body.takeAction();
		sun.takeAction();
		//Can choose explore, develop, hide, do nothing etc. Comsuming diff resources respectively
		//When exploring, have chance to find resources(higher tech, higher possibility)

		std::cout<<"--------------------------------------------------------------"<<std::endl;
		system("PAUSE");
		system("cls");
		if(sun.dead() || (three_body.dead()&&two_body.dead()))
			break;
	}

	for(std::vector<SolarSystem *>::iterator it=undeveloped_stars_ptr.begin();it!=undeveloped_stars_ptr.end();++it){
		delete (*it);
	}
	system("PAUSE");
}

#endif /* __MAIN__ */