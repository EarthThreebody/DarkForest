#include "boost/shared_ptr.hpp"
#include <iostream>
#include "SolarSystem.h"

int main(){
  SolarSystem sun("Sun",1);
  SolarSystem three_body("ThreeBody");

  while(true){
    sleep(1);

    std::cout<<"-------New Report-------"<<std::endl;
    sun.takeAction(three_body);
    three_body.takeAction(sun);

    //Player can choose explore, develop, hide, do nothing etc. Comsuming diff resources respectively
    //When exploring, have chance to find resources(higher tech, higher possibility)

    std::cout<<"-----------------------"<<std::endl;

    if(sun.dead() || three_body.dead())
      break;
  }
}
