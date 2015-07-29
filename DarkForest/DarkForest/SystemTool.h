#ifndef SYSTEM_TOOL_H_INCLUDED
#define SYSTEM_TOOL_H_INCLUDED

#include <iostream>
#include <sstream>
#include <boost/thread.hpp>
#include <cstdlib>
#include <ctime>

namespace SystemTool{
  void systemSleep(const int i){
   boost::this_thread::sleep(boost::posix_time::millisec(i*1000));
  }

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

  int genRandom(const int & max){
	std::srand(std::time(0));
    return std::rand() % max;
  };
}

#endif /* SYSTEM_TOOL_H_INCLUDED */