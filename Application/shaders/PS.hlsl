struct PS_INPUT //from the VS_OUTPUT
{
	
    float4 position : SV_POSITION;
    float4 color : COLOR;
	
};


struct MaterialData
{
    float4 diffuseAlbedo;
};

ConstantBuffer<MaterialData> gMaterialData : register(b1);


float4 main(PS_INPUT input) : SV_TARGET
{
    return gMaterialData.diffuseAlbedo;
    //return input.color;

}