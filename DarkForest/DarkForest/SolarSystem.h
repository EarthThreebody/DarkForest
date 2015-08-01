#ifndef SOLAR_SYSTEM_H_INCLUDED
#define SOLAR_SYSTEM_H_INCLUDED  

#include <string>
#include <map>

namespace SolarSystemAction{
	const int AWAIT = 0;
	const int DEVELOP = 1;
	const int EXPLORE = 2;

	const int NUM_OF_ACT = 3;
}

namespace SolarSystemState{
	const int PLAYER = 1;
	const int ENEMY = 2;
	const int UNDEVELOPED = 3;
}


class Space;

class SolarSystem{
public:
	SolarSystem(Space * space_ptr=NULL,const std::string & name="Undeveloped",const int state=SolarSystemState::UNDEVELOPED);

	void takeAction();
	void develop();
	void explore();
	void await();
	void act(const int & i);
	void act();
	void joinSpace(Space * space_ptr);

	void setPosition(const double position){m_position = position;};
	double getPosition(){return m_position;};
	double getExploreRange(){return m_explore_range;};
	std::string getName(){return m_name;};
	bool dead();

protected:
	double m_position;
	double m_tech;
	double m_resource;
	std::string m_name;

private:
	Space * m_space_ptr;
	double m_develop_speed;
	double m_explore_range;
	int m_state;

	void init();
	void report();
	void report(std::string new_report);
	void reportDetail();
};

#endif /* SOLAR_SYSTEM_H_INCLUDED */
