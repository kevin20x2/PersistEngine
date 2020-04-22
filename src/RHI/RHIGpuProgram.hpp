#pragma once


namespace Persist
{
class SubShader;
struct SerializedGpuProgram;

class RHIGpuProgram 
{
public:
    enum ProgramType
    {
        PT_Vertex = 0,
        PT_Pixel = 1
    };

    ProgramType type() { return type_; }
    virtual ~RHIGpuProgram() {}
    static RHIGpuProgram *  createFromSerializedProgram(const SerializedGpuProgram & program,RHIGpuProgram ::ProgramType type);

protected:
    ProgramType type_;


};

}