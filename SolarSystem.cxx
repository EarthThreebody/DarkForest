#include "SolarSystem.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

SolarSystem::SolarSystem(const std::string & name){
  sleep(1);
  std::srand(std::time(0));
  m_name = name;
  m_position.x = std::rand() % 100;
  m_position.y = std::rand() % 100;
  m_tech = std::rand() % 10;
  m_resource = std::rand() % 1000;
  m_develop_speed =  double(std::rand()%10) / 5 + 1;
  m_explore_range = 0.0;

  std::cout<<"["<<m_name<<"]"<<" is in the Dark Forest..."<<std::endl;
  std::cout<<"-------------------------------------------"<<std::endl;
  report();
}


void SolarSystem::develop(){
  m_resource      -= m_develop_speed;
  m_tech          += m_develop_speed;
  m_explore_range += m_develop_speed;
  report();
}

void SolarSystem::explore(SolarSystem & other){
  double distance_x = (m_position.x - other.m_position.x);
  double distance_y = (m_position.y - other.m_position.y);
  double distance = distance_x*distance_x + distance_y*distance_y;

  if((m_explore_range*m_explore_range)>distance){
    if(m_tech > other.m_tech){
      std::cout<<"["<<m_name<<"] distroyed ["<<other.m_name<<"]"<<std::endl;
      m_resource += other.m_resource;
      other.m_resource = 0;
    } else {
      std::cout<<"["<<other.m_name<<"] distroyed ["<<m_name<<"]"<<std::endl;
    }
  }
}

bool SolarSystem::dead(){
  if(m_resource<=0){
    std::cout<<"["<<m_name<<"] is destroyed."<<std::endl;
    return true;
  }

  return false;
}

void SolarSystem::report(){
  std::cout<<"Name:        ["<<m_name<<"]"<<std::endl;
  std::cout<<"Position:    ["<<m_position.x<<","<<m_position.y<<"]"<<std::endl;
  std::cout<<"Tech:        ["<<m_tech<<"]"<<std::endl;
  std::cout<<"Resource:    ["<<m_resource<<"]"<<std::endl;
  std::cout<<"DevelopSpeed:["<<m_develop_speed<<"]"<<std::endl;
  std::cout<<"ExploreRange:["<<m_explore_range<<"]"<<std::endl;

  std::cout<<std::endl;
}
