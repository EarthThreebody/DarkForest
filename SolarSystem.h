#ifndef SOLAR_SYSTEM_H_INCLUDED
#define SOLAR_SYSTEM_H_INCLUDED

#include <string>

namespace SolarSystemAction{
  const int DEVELOP = 1;
  const int EXPLORE = 2;
  const int NUM_OF_ACT = 2;
}

struct Position{double x,y;};

class SolarSystem{
public:
  SolarSystem(const std::string & name, const bool & is_player);
  SolarSystem(const std::string & name);
  void develop();
  void explore(SolarSystem & other);
  void takeAction(SolarSystem & other);
  void act(SolarSystem & other,const int & i);
  void act(SolarSystem & other);
  bool dead();

protected:
  Position m_position;
  double m_tech;
  double m_resource;
  std::string m_name;

private:
  double m_develop_speed;
  double m_explore_range;
  bool m_is_player;

  int genRandom(const int & min, const int & max);
  void init();
  void report();
  void report(std::string new_report);
  void reportDetail();
  void log(std::string out);
  void log();
  template <typename T> std::string to_string(T value);
};

#endif /* SOLAR_SYSTEM_H_INCLUDED */
