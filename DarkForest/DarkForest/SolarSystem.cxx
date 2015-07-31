#include "SolarSystem.h"
#include "SystemTool.h"
#include "Space.h"

SolarSystem::SolarSystem(Space * space_ptr,const std::string & name,const int state){

	m_name = name;
	m_space_ptr = space_ptr;
	m_state = state;
	m_space_ptr->getIn(this);
	init();
}

void SolarSystem::init(){

	m_tech = SystemTool::genRandom(10);
	m_resource = double(SystemTool::genRandom(1000)) / (1.0+double(SystemTool::genRandom(10)));
	m_develop_speed =  double(SystemTool::genRandom(10)) / 5 + 1;
	m_explore_range = 0.0;

	SystemTool::logInfo("["+m_name+"] is activated...");
	SystemTool::logInfo("--------------------------------------------------------------");

	if(m_state==SolarSystemState::PLAYER)
		report();
}

void SolarSystem::takeAction(SolarSystem & other){
	if(m_state==SolarSystemState::UNDEVELOPED){
		await();
		return;
	}


	if(m_state==SolarSystemState::ENEMY){
		act(other); return;
	}

	SystemTool::logInfo("["+m_name+"] decide to:");
	SystemTool::logInfo("("+SystemTool::toString(SolarSystemAction::DEVELOP)+") develop tech");
	SystemTool::logInfo("("+SystemTool::toString(SolarSystemAction::EXPLORE)+") explore the space");
	SystemTool::logInfo("(other) random");
	int act_num;
	std::cin>>act_num; //TODO: have bug when cin is not a int
	act(other,act_num);
}

void SolarSystem::act(SolarSystem & other,const int & i){
	switch (i){
	case SolarSystemAction::DEVELOP :
		develop(); break;
	case SolarSystemAction::EXPLORE :
		explore(); break;
	default:
		act(other);
	}
}

void SolarSystem::act(SolarSystem & other){
	//TODO: update this function
	SystemTool::systemSleep(1);
	std::srand(std::time(0));
	int rand = std::rand();
	int i = 1 + rand % SolarSystemAction::NUM_OF_ACT;
	act(other,i);
}

void SolarSystem::develop(){
	m_resource      -= m_develop_speed;
	m_tech          += m_develop_speed;

	report("Developing...");
}

void SolarSystem::explore(){
	m_explore_range += m_develop_speed;

	report("Exploring...");
	//TODO: have chance to find resources


	//TODO find neighbours
	std::vector<SolarSystem *> neighbours;
	if(!m_space_ptr->searchAround(this,neighbours))	{
		SystemTool::logInfo("["+m_name+"] didn't find anything in the Space.");
		return;
	}

	for(std::vector<SolarSystem *>::iterator it=neighbours.begin();it!=neighbours.end();++it){
		if(m_tech > (*it)->m_tech){
			SystemTool::logInfo("["+m_name+"] distroyed ["+(*it)->m_name+"]");
			m_resource += (*it)->m_resource;
			(*it)->m_resource = 0;
		} else {
			SystemTool::logInfo("["+(*it)->m_name+"] distroyed ["+m_name+"]");
			(*it)->m_resource += m_resource;
			m_resource = 0;
		}
	}
}

void SolarSystem::await(){
	report("Awaiting...");
}

void SolarSystem::report(std::string new_report){
	SystemTool::logInfo();
	new_report = "["+m_name+"] "+new_report;
	reportDetail();
	SystemTool::logInfo(new_report);
	SystemTool::logInfo();
}

void SolarSystem::report(){
	reportDetail();
	SystemTool::logInfo();
}

void SolarSystem::reportDetail(){
	std::string state_report;
	switch (m_state)
	{
	case SolarSystemState::PLAYER :
		state_report = "Player";
		break;
	case SolarSystemState::ENEMY :
		state_report = "Enemy";
		break;
	case SolarSystemState::UNDEVELOPED :
		state_report = "Undeveloped";
		break;
	default:
		break;
	}

	SystemTool::logInfo("Name:        ["+m_name+"]");
	SystemTool::logInfo("State:       ["+state_report+"]");
	SystemTool::logInfo("Position:    ["+SystemTool::toString(m_position)+"]");
	SystemTool::logInfo("Tech:        ["+SystemTool::toString(m_tech)+"]");
	SystemTool::logInfo("Resource:    ["+SystemTool::toString(m_resource)+"]");
	SystemTool::logInfo("DevelopSpeed:["+SystemTool::toString(m_develop_speed)+"]");
	SystemTool::logInfo("ExploreRange:["+SystemTool::toString(m_explore_range)+"]");
}

bool SolarSystem::dead(){
	if(m_resource<=0){
		SystemTool::logInfo("["+m_name+"] is destroyed.");
		return true;
	}
	return false;
}