#ifndef SYSTEM_TOOL_H_INCLUDED
#define SYSTEM_TOOL_H_INCLUDED

#include <iostream>
#include <sstream>
#include <boost/thread.hpp>
#include <cstdlib>
#include <ctime>

/*Header Only Library*/
//(1)Non-template function has to be inline
//(2)Longer compilation times ¨C the compilation unit must see the implementation of all components in the included files, rather than just their interfaces
//(3)For templates, including the definitions in header is the only way to compile, since the compiler needs to know the full definition of the templates in order to instantiate.


namespace SystemTool{
	inline void systemSleep(const int i){
		boost::this_thread::sleep(boost::posix_time::millisec(i*1000));
	}

	inline void logInfo(std::string out){
		std::cout<<out<<std::endl;
	};

	inline void logInfo(){
		std::cout<<std::endl;
	};

	template <typename T> std::string toString(T value){
		std::ostringstream os ;
		os << value ;
		return os.str() ;
	};

	inline int genRandom(const int & max){
		//std::srand(std::time(0));
		return 1 + std::rand() % max;
	};
}

#endif /* SYSTEM_TOOL_H_INCLUDED */