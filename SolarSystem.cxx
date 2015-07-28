#include "SolarSystem.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

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

  log("["+m_name+"] is in the Dark Forest...");
  log("-------------------------------------------");
  report();
}

void SolarSystem::takeAction(SolarSystem & other){
  if(!m_is_player){
    act(other); return;
  }

  log("["+m_name+"] decide to:");
  log("("+to_string(SolarSystemAction::DEVELOP)+") develop tech");
  log("("+to_string(SolarSystemAction::EXPLORE)+") explore the space");
  log("(other) random");
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

int SolarSystem::genRandom(const int & min, const int & max){
  return 1;//TODO
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
      log("["+m_name+"] distroyed ["+other.m_name+"]");
      m_resource += other.m_resource;
      other.m_resource = 0;
    } else {
      log("["+other.m_name+"] distroyed ["+m_name+"]");
    }
  }
}

void SolarSystem::report(std::string new_report){
  log();
  new_report = "["+m_name+"] "+new_report;
  reportDetail();
  log(new_report);
  log();
}

void SolarSystem::report(){
  reportDetail();
  log();
}

void SolarSystem::reportDetail(){
  log("Name:        ["+m_name+"]");
  log("Player:      ["+(m_is_player? std::string("Yes"):std::string("No"))+"]");
  log("Position:    ["+to_string(m_position.x)+","+to_string(m_position.y)+"]");
  log("Tech:        ["+to_string(m_tech)+"]");
  log("Resource:    ["+to_string(m_resource)+"]");
  log("DevelopSpeed:["+to_string(m_develop_speed)+"]");
  log("ExploreRange:["+to_string(m_explore_range)+"]");
}

void SolarSystem::log(std::string out){
  std::cout<<out<<std::endl;
}

void SolarSystem::log(){
  std::cout<<std::endl;
}


template <typename T> std::string SolarSystem::to_string(T value){
  std::ostringstream os ;
  os << value ;
  return os.str() ;
}


bool SolarSystem::dead(){
  if(m_resource<=0){
    log("["+m_name+"] is destroyed.");
    return true;
  }
  return false;
}

