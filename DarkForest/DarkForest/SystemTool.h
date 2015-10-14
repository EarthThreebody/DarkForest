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

	template <typename T> std::string numToBars(T value){
		//TODO: kind of risky here
		int bar_num = int(value);	
		std::string bars("[");
		for(int i=0; i<bar_num; ++i)
			bars += "+";
		bars += "]";

		return bars;
	};

	inline int genRandom(const int & max){
		//boost::this_thread::sleep(boost::posix_time::milliseconds(100));
		//std::cout<<std::time(0)<<std::endl;
		return 1 + std::rand() % max;
	};
}

#endif /* SYSTEM_TOOL_H_INCLUDED */