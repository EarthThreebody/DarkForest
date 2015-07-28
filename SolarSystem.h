#ifndef SOLAR_SYSTEM_H_INCLUDED
#define SOLAR_SYSTEM_H_INCLUDED

#include <string>

struct Position{double x,y;};

class SolarSystem{
public:
  SolarSystem(const std::string & name);
  void develop();
  void explore(SolarSystem & other);
  bool dead();

protected:
  Position m_position;
  double m_tech;
  double m_resource;
  std::string m_name;

private:
  double m_develop_speed;
  double m_explore_range;

  void report();
};

#endif /* SOLAR_SYSTEM_H_INCLUDED */
