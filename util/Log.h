//
// Created by lidan on 1/3/2021.
//

#ifndef VR_LOG_H
#define VR_LOG_H

#include <iostream>
#include <string>

enum INFO{ERROR,WARNNING,INFO,NOTE} info ;


void llog(enum INFO level,std::string str)
{
    switch(level)
    {
        case ERROR:
            std::cout<<"ERROR: "<<str<<std::endl ;
        case WARNNING:
            std::cout<<"WARNNING: "<<str<<std::endl ;

        case NOTE:
            std::cout<<"NOTE: "<<str<<std::endl ;

        case INFO:
            std::cout<<"INFO: "<<str<<std::endl ;
    }
    std::cout<<str<<std::endl;
}


#endif //VR_LOG_H
