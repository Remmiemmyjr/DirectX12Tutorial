struct Vertex
{
    float3 position : SV_POSITION;
    float4 color : SV_COLOR;
};

RWStructuredBuffer<Vertex> vertices : register(u0);


[numthreads(1, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    // assigns a slightly different color to each vertex, creating a "rainbow-like" effect
    vertices[DTid.x].color = float4(sin(DTid.x), cos(DTid.x), sin(DTid.x + 1), 1.0f);
}