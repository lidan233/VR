//
// Created by lidan on 1/3/2021.
//

#ifndef VR_LOG_H
#define VR_LOG_H

#include <iostream>
#include <string>

enum INFO {
    ERROR1 = 1 << 1,
    WARNNING1 = 1 << 2,
    IF1 =  1 << 3 ,
    NOTE1 = 1 << 4
} ;


inline void llog( INFO level,std::string str)
{

    if(level == INFO::ERROR1)
    {
        std::cout<<"ERROR: "<<str<<std::endl ;
    } else if ( level == INFO::WARNNING1 )
    {
        std::cout<<"WARNNING: "<<str<<std::endl ;
    } else if ( level == INFO::NOTE1 )
    {
        std::cout<<"NOTE: "<<str<<std::endl ;
    } else if ( level == INFO::IF1)
    {
        std::cout<<"INFO: "<<str<<std::endl ;
    }


//    switch(level)
//    {
//        case INFO::ERROR:
//            std::cout<<"ERROR: "<<str<<std::endl ;
//            break ;
//        case INFO::WARNNING:
//            std::cout<<"WARNNING: "<<str<<std::endl ;
//            break ;
//        case INFO::NOTE:
//            std::cout<<"NOTE: "<<str<<std::endl ;
//            break ;
//        case INFO::IF:
//            std::cout<<"INFO: "<<str<<std::endl ;
//            break ;
//    }
    std::cout<<str<<std::endl;
}


#endif //VR_LOG_H
