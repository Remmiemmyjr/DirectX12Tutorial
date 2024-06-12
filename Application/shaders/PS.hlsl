struct PS_INPUT //from the VS_OUTPUT
{
	
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
	
};


struct MaterialData
{
    float4 diffuseAlbedo;
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

ConstantBuffer<PassData> gPassData : register(b0); // global
ConstantBuffer<MaterialData> gMaterialData : register(b1);


float4 main(PS_INPUT input) : SV_TARGET
{
    float intensity;
    float4 color;
    
    intensity = dot(gPassData.light.direction, input.normal);
    
    if(intensity > 0.9)
    {
        color = float4(1.f, 0.5f, 0.5f, 1.f);
    }
    else if(intensity > 0.5f)
    {
        color = float4(0.8f, 0.3f, 0.3f, 1.f);
    }
    else if (intensity > 0.25f)
    {
        color = float4(0.6f, 0.1f, 0.1f, 1.f);
    }
    else
    {
        color = float4(0.2f, 0.f, 0.f, 1.f);
    }
    
    return color;
}