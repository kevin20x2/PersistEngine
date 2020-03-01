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
    //matrix mvp =mul ( projectionMat ,  mul( viewMat , worldMat ) );  
    matrix mvp = mul ( mul ( worldMat , viewMat) , projectionMat);  
    //matrix mvp =  mul( viewMat , worldMat ) ;
    output.position = mul(float4(input.position,1.0) , mvp);//mul(mvp , float4(input.position , 1.0) );
    output.position /= output.position.w;
    output.color = input.color;


    return output;
}