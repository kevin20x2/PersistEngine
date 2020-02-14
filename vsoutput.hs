struct a2v {
    float3 position : POSITION;
    float4 color :COLOR;
};

struct v2p {
    float4 position : SV_POSITION;
    float4 color : COLOR;
};