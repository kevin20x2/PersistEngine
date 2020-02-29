#include "vsoutput.hs"

cbuffer MatrixBuffer
{
    //float4 color ;
    matrix worldMat;
    matrix viewMat;
    matrix projectionMat;
};



v2p main(a2v input )
{
    v2p output ;
    matrix mvp = projectionMat * viewMat * worldMat;  
    output.position = mul(mvp , float4(input.position , 1.0) );
    output.color = input.color;


    return output;
}