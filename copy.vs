#include "vsoutput.hs"

cbuffer MatrixBuffer
{
    //float4 color ;
    matrix worldMat;
    matrix viewMat;
    matrix projectionMat;
};


//中文测试

v2p main(a2v input )
{
    v2p output ;
    //matrix mvp =mul ( projectionMat ,  mul( viewMat , worldMat ) );  
    //matrix mvp = mul ( mul ( worldMat , viewMat) , projectionMat);  
    //matrix mvp =  mul( viewMat , worldMat ) ;
    float4 worldPos = mul(worldMat ,float4(input.position ,1.0));
    float4 viewPos = mul(viewMat,worldPos  );
    output.position= mul(projectionMat , viewPos);
    //output.position = mul(float4(input.position,1.0) , mvp);//mul(mvp , float4(input.position , 1.0) );
    //output.position = float4(input.position,1.0);
    //output.position /= output.position.w;
    output.color = input.color;


    return output;
}