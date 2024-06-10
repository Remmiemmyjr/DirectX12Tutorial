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
    return gMaterialData.diffuseAlbedo;
    //return input.color;

}