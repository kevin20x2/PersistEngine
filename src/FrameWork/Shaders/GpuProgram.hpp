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
    static GpuProgram *  createFromSerializedProgram(const SerializedGpuProgram & program,GpuProgram ::ProgramType type);

protected:
    ProgramType type_;


};

}