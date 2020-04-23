
#pragma once
#include "Array.hpp"
#include "Logger.hpp"
#include "Memory.hpp"
//#include <string>
namespace Persist
{
    //using String = std:: string ;
    class String 
    {
        private : 

        Array <char> data_;

        public :
        String(const char * str )
        {
            uint32_t len = String::Length(str);

            //for(int i = 0 ; i < len ; ++i)
            //{
             //   data_.push_back(str[i]);
            //}
            //data_.push_back('\0');
            //data_.reserve(len + 1);
            std::copy(str , str+len+1 , std::back_inserter(data_));
            //Memory::Memcpy(data_.data(),str,len );
        }
        String() = default;

        const char * toCharArray() const
        {
            return data_.data();
        }
        char * toCharArray()
        {
            return data_.data();
        }
        friend StdOutStream & operator<<( StdOutStream & stream, const String & str)
        {
            return stream << str.toCharArray();
        }

        public : 
        static uint32_t Length(const char * str )
        {
            return strlen(str);
        }



    };

}