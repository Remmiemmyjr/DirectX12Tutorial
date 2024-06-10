struct VS_INPUT
{
    float3 position : POSITION;
    float4 normal : NORMAL;
};


struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

struct LightData
{
    float3 position;
    float strength;
    float3 direction;
    float padding; 
};

struct PassData
{
    float4x4 viewProj;
    LightData light;
};



ConstantBuffer<PassData> gPassData : register(b0); // gloabl


VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = mul(gPassData.viewProj, float4(input.position,1.f));
    output.color = float4(1.f,1.f,1.f,1.f);
    
    return output;
}
