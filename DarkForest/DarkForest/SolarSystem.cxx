#include "SolarSystem.h"
#include "SystemTool.h"
#include "Space.h"

SolarSystem::SolarSystem(Space * space_ptr,const std::string & name,const int state){
	m_name = name;
	m_state = state;
	if(space_ptr){ joinSpace(space_ptr); };
	init();
}

void SolarSystem::joinSpace(Space * space_ptr){
	m_space_ptr = space_ptr;
	m_space_ptr->getIn(this);
}

void SolarSystem::init(){
	SystemTool::logInfo("["+m_name+"] is activated...");
	SystemTool::logInfo("--------------------------------------------------------------");

	m_resource = double(SystemTool::genRandom(100)) / (1.0+double(SystemTool::genRandom(10)));
	m_explore_range = 0.0;
	m_tech = 0.0;
	m_develop_speed =  0.0;

	if(m_state == SolarSystemState::UNDEVELOPED) return;

	m_tech = SystemTool::genRandom(10);
	m_develop_speed =  double(SystemTool::genRandom(10)) / 5 + 1;

	if(m_state==SolarSystemState::PLAYER)
		report();
}

void SolarSystem::takeAction(){
	if(m_resource<=0) return;

	if(m_space_ptr == NULL){
		SystemTool::logInfo("WARNING! ["+m_name+"] is not in the space." );
		reportDetail();
		return;
	}

	if(m_state==SolarSystemState::UNDEVELOPED){
		/*await();*/ return;
	}

	if(m_state==SolarSystemState::ENEMY){
		act();   return;
	}

	reportDetail();
	SystemTool::logInfo("["+m_name+"] decide to:");
	SystemTool::logInfo("("+SystemTool::toString(SolarSystemAction::DEVELOP)+") develop Tech");
	SystemTool::logInfo("("+SystemTool::toString(SolarSystemAction::EXPLORE)+") explore the space");
	SystemTool::logInfo("(other) random");
	int act_num;
	std::cin>>act_num; //TODO: have bug when cin is not a int
	act(act_num);
}

void SolarSystem::act(const int & i){
	switch (i){
	case SolarSystemAction::DEVELOP :
		develop(); break;
	case SolarSystemAction::EXPLORE :
		explore(); break;
	default:
		act();
	}
}

void SolarSystem::act(){
	if(m_resource<10) act(SolarSystemAction::EXPLORE);
	if(m_resource>15) act(SolarSystemAction::DEVELOP);

	//TODO: update this function
	SystemTool::systemSleep(1);
	std::srand(std::time(0));
	int rand = std::rand();
	int i = 1 + rand % SolarSystemAction::NUM_OF_ACT;
	act(i);
}

void SolarSystem::develop(){
	m_resource      -= m_develop_speed;
	m_tech          += m_develop_speed;

	if(m_state == SolarSystemState::PLAYER)
		report("Developing... Tech reaches ["+SystemTool::toString(m_tech)+"]. ["+SystemTool::toString(m_develop_speed)+"] resources are consumed.");
}

void SolarSystem::explore(){
	m_explore_range += m_develop_speed;

	if(m_state == SolarSystemState::PLAYER)
		report("Exploring...to range ["+SystemTool::toString(m_explore_range)+"]. ["+SystemTool::toString(m_develop_speed)+"] range expanded.");

	std::vector<SolarSystem *> neighbours;
	if(!m_space_ptr->searchAround(this,neighbours))	{
		SystemTool::logInfo("["+m_name+"] didn't find anything in the Space.");
		return;
	}

	for(std::vector<SolarSystem *>::iterator it=neighbours.begin();it!=neighbours.end();++it){
		double other_resource(0.0);
		if(m_tech > (*it)->m_tech){
			other_resource = (*it)->m_resource;

			if(other_resource<=0) continue;

			SystemTool::logInfo("["+m_name+"] distroyed ["+(*it)->m_name+"], and got its resources ["+SystemTool::toString(other_resource)+"]");
			m_resource += other_resource;
			(*it)->m_resource = 0;
		} else {
			other_resource = m_resource;
			SystemTool::logInfo("["+(*it)->m_name+"] distroyed ["+m_name+"], and got its resources ["+SystemTool::toString(other_resource)+"]");
			(*it)->m_resource += other_resource;
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
	SystemTool::logInfo("Tech:        "+SystemTool::numToBars(m_tech)         +"["+SystemTool::toString(m_tech)+"]");
	SystemTool::logInfo("Resource:    "+SystemTool::numToBars(m_resource)     +"["+SystemTool::toString(m_resource)+"]");
	SystemTool::logInfo("DevelopSpeed:"+SystemTool::numToBars(m_develop_speed)+"["+SystemTool::toString(m_develop_speed)+"]");
	SystemTool::logInfo("ExploreRange:"+SystemTool::numToBars(m_explore_range)+"["+SystemTool::toString(m_explore_range)+"]");
}

bool SolarSystem::dead(){
	if(m_resource>0) return false;

	SystemTool::logInfo("["+m_name+"] is destroyed.");
	return true;
}