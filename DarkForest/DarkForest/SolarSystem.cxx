#pragma once
#include "SolarSystem.h"
#include "SystemTool.h"

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

SolarSystem::SolarSystem(){
  m_name = "Undeveloped";
  m_is_player = false;
  init();
}

void SolarSystem::init(){
  SystemTool::systemSleep(1);
  std::srand(std::time(0));

  m_position = double(std::rand()%1000) / (1.0+double(std::rand()%10));
  m_tech = std::rand() % 10;
  m_resource = std::rand() % 100;
  m_develop_speed =  double(std::rand()%10) / 5 + 1;
  m_explore_range = 0.0;

  SystemTool::log("["+m_name+"] is created...");
  SystemTool::log("-------------------------------------------");

  if(m_is_player)
    report();
}

void SolarSystem::takeAction(SolarSystem & other){
  if(!m_is_player){
    act(other); return;
  }

  SystemTool::log("["+m_name+"] decide to:");
  SystemTool::log("("+SystemTool::toString(SolarSystemAction::DEVELOP)+") develop tech");
  SystemTool::log("("+SystemTool::toString(SolarSystemAction::EXPLORE)+") explore the space");
  SystemTool::log("(other) random");
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

void SolarSystem::explore(SolarSystem & other){
  m_explore_range += m_develop_speed;

  report("Exploring...");
  //TODO: have chance to find resources

  double distance = other.getPosition()-m_position;

  if( (m_explore_range*m_explore_range) > (distance*distance) ){
    if(m_tech > other.m_tech){
      SystemTool::log("["+m_name+"] distroyed ["+other.m_name+"]");
      m_resource += other.m_resource;
      other.m_resource = 0;
    } else {
      SystemTool::log("["+other.m_name+"] distroyed ["+m_name+"]");
    }
  }
}

void SolarSystem::report(std::string new_report){
  SystemTool::log();
  new_report = "["+m_name+"] "+new_report;
  reportDetail();
  SystemTool::log(new_report);
  SystemTool::log();
}

void SolarSystem::report(){
  reportDetail();
  SystemTool::log();
}

void SolarSystem::reportDetail(){
  SystemTool::log("Name:        ["+m_name+"]");
  SystemTool::log("Player:      ["+(m_is_player? std::string("Yes"):std::string("No"))+"]");
  SystemTool::log("Position:    ["+SystemTool::toString(m_position)+"]");
  SystemTool::log("Tech:        ["+SystemTool::toString(m_tech)+"]");
  SystemTool::log("Resource:    ["+SystemTool::toString(m_resource)+"]");
  SystemTool::log("DevelopSpeed:["+SystemTool::toString(m_develop_speed)+"]");
  SystemTool::log("ExploreRange:["+SystemTool::toString(m_explore_range)+"]");
}

bool SolarSystem::dead(){
  if(m_resource<=0){
    SystemTool::log("["+m_name+"] is destroyed.");
    return true;
  }
  return false;
}