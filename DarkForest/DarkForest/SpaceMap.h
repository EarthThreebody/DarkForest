#ifndef SPACE_MAP_H_INCLUDED
#define SPACE_MAP_H_INCLUDED

#include <map>
#include <iostream>
#include "SolarSystem.h"


namespace SpaceMap{
  typedef std::multimap<double,SolarSystem &> SpaceMap;
  typedef std::multimap<double,SolarSystem &>::value_type SpaceMapValue;
  
  //TODO: make this a class
  void joinSpace(SolarSystem & in,SpaceMap & space_map){
     space_map.insert(SpaceMapValue(in.getPosition(),in));
	 std::cout<<"["<<in.getName()<<"] is in the space, with absolute position ["<<in.getPosition()<<"]"<<std::endl;
  }
}

#endif /* SPACE_MAP_H_INCLUDED */