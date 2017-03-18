//**********************************************虽然并不知道有什么用，但是还是加上吧
#ifndef MYFUNCTION_CPP
#define MYFUNCTION_CPP

#include <ctime>

 inline void init(){
    srand(unsigned(time(0)));
 }
 inline double random(double Start=0, double End=1){
    return Start+(End-Start)*rand()/(RAND_MAX + 1.0);
 }
 inline double random(double Start, int End){
    return Start+(End-Start)*rand()/(RAND_MAX + 1.0);
 }
 inline double random(int Start, double End){
    return Start+(End-Start)*rand()/(RAND_MAX + 1.0);
 }
 inline int random(int Start ,int End){
    return Start + int(rand())%(End-Start);
 }

template<class T>
void realese(T t)
{
	if(t!=NULL)
		delete t;
}


#endif // MYFUNCTION_CPP


