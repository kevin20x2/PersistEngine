#include "vsoutput.hs"

cbuffer MatrixBuffer
{
    float4 color ;
    //matrix worldMat;
    //matrix viewMat;
    //matrix projectionMat;
};



v2p main(a2v input )
{
    v2p output ;
    output.position = float4(input.position ,1.0);
    output.color = color;


    return output;
}