#include "boost/shared_ptr.hpp"
#include <iostream>
#include "SolarSystem.h"

int main(){
  SolarSystem sun("Sun");
  SolarSystem three_body("ThreeBody");

  while(true){
    std::cout<<"-------New Round-------"<<std::endl;

    sleep(1);
    sun.develop();
    three_body.develop();

    sun.explore(three_body);
    three_body.explore(sun);


    //Player can choose explore, develop, hide, do nothing etc. Comsuming diff resources respectively

    std::cout<<"-----------------------"<<std::endl;

    if(sun.dead() || three_body.dead())
      break;
  }
}
