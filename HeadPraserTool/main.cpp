#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>
const std::filesystem::path rootPath = std::filesystem::current_path().parent_path();
//using fs = std::filesystem;
std::vector <std::string > classNames ;

std::string out_put_path =  std::filesystem::current_path().parent_path().string() + "\\" + "dynamicObjectInit.inc";


void parseHeadFile(std::string & content)
{
    //std::cout << "file content begin " <<std::endl;

    //std::cout <<content;
    std::regex persist_object ("[\\s\\S]*(PERSIST_OBJECT\\(\\))\\s+(class|interface)\\s+(\\S+)\\s+:[\\s\\S]*$");
    std::smatch object_match;
    if(std::regex_match (content , object_match , persist_object ))
    {
        //std::cout <<" find match" ;
        for(int i = 1 ; i < object_match.size(); ++ i)
        {
            std::string piece = object_match[i].str();
            //std::cout << "subMatch" << piece << std::endl;
        }
        if(object_match.size() ==  4)
        {
            std::cout <<"find class Name :" << object_match[3] <<std::endl;
            classNames.push_back(object_match[3]);
        }
    }
    //std::cout << "file content end" <<std::endl;

}


int main()
{

    
    std::vector<std::filesystem ::path > paths;
    if(std::filesystem::exists(rootPath) && std::filesystem::is_directory(rootPath))
    {
        std::filesystem::recursive_directory_iterator iter (rootPath);
        std::copy_if(begin(iter),end(iter),std::back_inserter(paths), [](const std::filesystem::directory_entry & entry){
            return entry.is_regular_file();
        });
    }
    for(auto & path : paths) if(path.extension().string() == ".hpp")
    {
        std::ifstream ifs(path.string());
        if(ifs.is_open())
        {
            std::string content((std::istreambuf_iterator<char >(ifs)) , 
                                std::istreambuf_iterator<char>());
            parseHeadFile(content);
            ifs.close();
        }
    }
    std::ofstream ofs(out_put_path) ;
    if(ofs.is_open())
    {
        for(int i = 0 ; i < classNames.size();++i)
        {
            ofs << "DYNAMIC_REGISTER_CLASS(" << classNames[i] <<");" << std::endl;
        }

    }
    ofs.close();





    //const std::regex reg("*.hpp");

    return 0;
}