#ifdef WIN32
#include <windows>
#include <stdlib.h>
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

	std::vector<SolarSystem> undeveloped_stars;
	//TODO: make these to be pointer...
	SolarSystem new_1(&this_space);
	SolarSystem new_2(&this_space);
	SolarSystem new_3(&this_space);
	SolarSystem new_4(&this_space);
	SolarSystem new_5(&this_space);
	SolarSystem new_6(&this_space);
	SolarSystem new_7(&this_space);
	SolarSystem new_8(&this_space);
	undeveloped_stars.push_back(new_1);
	undeveloped_stars.push_back(new_2);
	undeveloped_stars.push_back(new_3);
	undeveloped_stars.push_back(new_4);
	undeveloped_stars.push_back(new_5);
	undeveloped_stars.push_back(new_6);
	undeveloped_stars.push_back(new_7);
	undeveloped_stars.push_back(new_8);

	SolarSystem two_body(&this_space,"TwoBody",SolarSystemState::ENEMY);
	SolarSystem three_body(&this_space,"ThreeBody",SolarSystemState::ENEMY);
	SolarSystem sun(&this_space,"Sun",SolarSystemState::PLAYER);
	system("PAUSE");
	system("cls");

	while(true){
		std::cout<<"-----------------------New Report-----------------------------"<<std::endl;

		for(std::vector<SolarSystem>::iterator it=undeveloped_stars.begin();it!=undeveloped_stars.end();++it){
			it->takeAction();
		}

		three_body.takeAction();
		sun.takeAction();
		//Can choose explore, develop, hide, do nothing etc. Comsuming diff resources respectively
		//When exploring, have chance to find resources(higher tech, higher possibility)

		//TODO:Use absolute position rather than 2D position? random generate distance
		//TODO:static map/set to save all solar objects

		std::cout<<"--------------------------------------------------------------"<<std::endl;
		system("PAUSE");
		system("cls");
		if(sun.dead() || three_body.dead())
			break;
	}

	system("PAUSE");
}

#endif /* __MAIN__ */