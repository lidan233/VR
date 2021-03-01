//
// Created by lidan on 2021/2/28.
//

#ifndef VR_FILEREADER_H
#define VR_FILEREADER_H
#include <string>
#include <stdlib.h>
#include <memory.h>
#include <fstream>
#include <iostream>
#include <sstream>


class FileReader{
public:
    static std::string fileExtName(std::string& filename  )
    {
        if(filename == "")
        {
            return nullptr ;
        }

        size_t len = filename.size() ;
        for(int i = len -1 ; i >=0 ;i--)
        {
            if(filename[i] == '.' && i+1 < len)
            {
                return filename.substr(i+1,len-i-1) ;
            }
        }

        return "" ;
    }

    static std::string readAll(std::string& filename )
    {
        if(filename == "" )
        {
            return "" ;
        }
        std::ifstream infile ;
        infile.open(filename,std::ios::in) ;
        if(!infile) return "" ;
        std::stringstream  buffer ;

        buffer<<infile.rdbuf() ;
        std::string contents(buffer.str()) ;
        return contents ;
    }

    static std::string readline(std::ifstream& infile)
    {
        if(infile.eof()){
            char buffer[1024] ;
            infile.getline(buffer,sizeof(buffer)) ;
            return std::string(buffer) ;
        }
        return "" ;
    }
};

#endif //VR_FILEREADER_H
