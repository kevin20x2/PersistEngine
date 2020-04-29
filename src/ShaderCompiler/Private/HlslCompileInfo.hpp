#pragma once
#include <FrameWork/Common/Array.hpp>
#include <FrameWork/Common/String.hpp>
#include <FrameWork/Common/Logger.hpp>

namespace Persist
{
    struct HlslCompileMsg
    {
        public : 
        enum MsgType 
        {
            MT_Warning,
            MT_Error
        };
        String msg_; 
        int line_;
    };

    struct HlslCompileInfo
    {
        HlslCompileInfo() {};

        void sourceError(const String & info , int line  ){
            PLOG() <<"Source error : "<< info  << "line  :"  << line << PEND;
        };






    };

}