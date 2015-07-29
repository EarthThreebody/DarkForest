#ifndef SOLAR_SYSTEM_H_INCLUDED
#define SOLAR_SYSTEM_H_INCLUDED  

#include <string>
#include <map>

namespace SolarSystemAction{
  const int DEVELOP = 1;
  const int EXPLORE = 2;
  const int NUM_OF_ACT = 2;
}

class SolarSystem{
public:
  SolarSystem(const std::string & name, const bool & is_player);
  SolarSystem(const std::string & name);
  SolarSystem();
  void develop();
  void explore(SolarSystem & other);
  void takeAction(SolarSystem & other);
  void act(SolarSystem & other,const int & i);
  void act(SolarSystem & other);
  double getPosition(){return m_position;};
  std::string getName(){return m_name;};
  bool dead();

protected:
  double m_position;
  double m_tech;
  double m_resource;
  std::string m_name;

private:
  double m_develop_speed;
  double m_explore_range;
  bool m_is_player;


  void init();
  void report();
  void report(std::string new_report);
  void reportDetail();
};

#endif /* SOLAR_SYSTEM_H_INCLUDED */
