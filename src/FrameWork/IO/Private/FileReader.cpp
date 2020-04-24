#include "../Public/FileReader.hpp"
#include <fstream>
#include <iostream>

namespace Persist
{

struct FileReader::Rep
{
    Rep ()
    {

    }
    void readFile(const String & fileName , IOMode mode)
    {
        ifs_.open(fileName.toStdString(), 
        mode == IOMode::IOM_Binary ?
         (std::ios_base::in | std::ios_base::binary ) : std::ios_base::in);

    }

    Status read(String & buf)
    {
        std::copy(std::istreambuf_iterator<char>(ifs_), std::istreambuf_iterator<char>(), 
        std::back_inserter(buf));
        return Status::Ok();

    }

    ~Rep()
    {
        if(ifs_.is_open())
        {
            ifs_.close();
        }
    }

    std::ifstream ifs_;


};

FileReader::FileReader(const String & fileName ,IOMode mode  ) : 
    rep_(new FileReader::Rep())
{
    rep_->readFile(fileName ,mode);


}

FileReader::~FileReader()
{
    delete rep_;
}

Status FileReader::read(String & buf)
{
   return  rep_->read(buf);

}




}
