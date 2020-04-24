
#pragma once
#include "Array.hpp"
//#include "Logger.hpp"
#include "Memory.hpp"
#include <iostream>
#include <string>
//#include <string>
namespace Persist
{

using StdOutStream = std::basic_ostream<char , std::char_traits<char> > ;
    //using String = std:: string ;
    class String 
    {
        private : 

        Array <char> data_;

        public :
        using value_type = char;
        String(const char * str )
        {
            uint32_t len = String::Length(str);

            //for(int i = 0 ; i < len ; ++i)
            //{
             //   data_.push_back(str[i]);
            //}
            //data_.push_back('\0');
            //data_.reserve(len + 1);
            std::copy(str , str+len +1 , std::back_inserter(data_));
            //Memory::Memcpy(data_.data(),str,len );
        }
        String()
        {
            data_.push_back('\0');
        }

        const char * toCharArray() const
        {
            return data_.data();
            
        }
        std::string toStdString() const
        {
            return std::string(data_.begin(),data_.end() - 1);
        }
        /*
        const char * toCharArray()
        {

            return std::string(data_.data(),data_.size()).c_str();
            //return data_.data();
        }

*/
        void push_back(char  ch)
        {
            //data_.push_back(ch);
            data_[length()] = ch;
            data_.push_back('\0');

        }

        uint32_t length() const
        {
            return data_.size() ? data_.size( ) - 1 : 0 ;
        }

        const char & operator[] (int index) const
        {
            return * (data_.data() + index);
        }

        friend StdOutStream & operator<<( StdOutStream & stream, const String & str)
        {
            std::cout << str.data_.size();
            return stream <<str.toStdString() ;
        }



        // static methods
        public : 
        static uint32_t Length(const char * str )
        {
            return strlen(str);
        }




    };

}