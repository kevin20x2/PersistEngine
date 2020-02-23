#pragma once


namespace Persist
{
class SubShader;
struct SerializedGpuProgram;

class GpuProgram 
{
public:
    enum ProgramType
    {
        PT_Vertex = 0,
        PT_Pixel = 1
    };

    ProgramType type() { return type_; }
    virtual ~GpuProgram() {}

protected:
    ProgramType type_;

    //    static GpuProgram createFromSerailizedProgram(const SerialiedGpuProgram & program);

};

}