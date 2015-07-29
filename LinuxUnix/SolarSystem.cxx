#include "SolarSystem.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

namespace SolarSystemTool{
  void log(std::string out){
    std::cout<<out<<std::endl;
  };

  void log(){
    std::cout<<std::endl;
  };

  template <typename T> std::string toString(T value){
    std::ostringstream os ;
    os << value ;
    return os.str() ;
  };

  int genRandom(const int & min, const int & max){
    return 1;//TODO
  };
}

namespace SolarSystemAction{
  const int DEVELOP = 1;
  const int EXPLORE = 2;
  const int NUM_OF_ACT = 2;
}


SolarSystem::SolarSystem(const std::string & name, const bool & is_player){
  m_name = name;
  m_is_player = is_player;
  init();
}

SolarSystem::SolarSystem(const std::string & name){
  m_name = name;
  m_is_player = false;
  init();
}

void SolarSystem::init(){
  sleep(1);
  std::srand(std::time(0));

  m_position.x = std::rand() % 100;
  m_position.y = std::rand() % 100;
  m_tech = std::rand() % 10;
  m_resource = std::rand() % 100;
  m_develop_speed =  double(std::rand()%10) / 5 + 1;
  m_explore_range = 0.0;

  SolarSystemTool::log("["+m_name+"] is in the Dark Forest...");
  SolarSystemTool::log("-------------------------------------------");

  if(m_is_player)
    report();
}

void SolarSystem::takeAction(SolarSystem & other){
  if(!m_is_player){
    act(other); return;
  }

  SolarSystemTool::log("["+m_name+"] decide to:");
  SolarSystemTool::log("("+SolarSystemTool::toString(SolarSystemAction::DEVELOP)+") develop tech");
  SolarSystemTool::log("("+SolarSystemTool::toString(SolarSystemAction::EXPLORE)+") explore the space");
  SolarSystemTool::log("(other) random");
  int act_num;
  std::cin>>act_num;
  act(other,act_num);
}

void SolarSystem::act(SolarSystem & other,const int & i){
  switch (i){
  case SolarSystemAction::DEVELOP :
    develop(); break;
  case SolarSystemAction::EXPLORE :
    explore(other); break;
  default:
    act(other);
  }
}

void SolarSystem::act(SolarSystem & other){
  sleep(1);
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

void SolarSystem::explore(SolarSystem & other){
  m_explore_range += m_develop_speed;

  report("Exploring...");
  //TODO: have chance to find resources

  double distance_x = (m_position.x - other.m_position.x);
  double distance_y = (m_position.y - other.m_position.y);
  double distance = distance_x*distance_x + distance_y*distance_y;

  if((m_explore_range*m_explore_range)>distance){
    if(m_tech > other.m_tech){
      SolarSystemTool::log("["+m_name+"] distroyed ["+other.m_name+"]");
      m_resource += other.m_resource;
      other.m_resource = 0;
    } else {
      SolarSystemTool::log("["+other.m_name+"] distroyed ["+m_name+"]");
    }
  }
}

void SolarSystem::report(std::string new_report){
  SolarSystemTool::log();
  new_report = "["+m_name+"] "+new_report;
  reportDetail();
  SolarSystemTool::log(new_report);
  SolarSystemTool::log();
}

void SolarSystem::report(){
  reportDetail();
  SolarSystemTool::log();
}

void SolarSystem::reportDetail(){
  SolarSystemTool::log("Name:        ["+m_name+"]");
  SolarSystemTool::log("Player:      ["+(m_is_player? std::string("Yes"):std::string("No"))+"]");
  SolarSystemTool::log("Position:    ["+SolarSystemTool::toString(m_position.x)+","+SolarSystemTool::toString(m_position.y)+"]");
  SolarSystemTool::log("Tech:        ["+SolarSystemTool::toString(m_tech)+"]");
  SolarSystemTool::log("Resource:    ["+SolarSystemTool::toString(m_resource)+"]");
  SolarSystemTool::log("DevelopSpeed:["+SolarSystemTool::toString(m_develop_speed)+"]");
  SolarSystemTool::log("ExploreRange:["+SolarSystemTool::toString(m_explore_range)+"]");
}

bool SolarSystem::dead(){
  if(m_resource<=0){
    SolarSystemTool::log("["+m_name+"] is destroyed.");
    return true;
  }
  return false;
}
