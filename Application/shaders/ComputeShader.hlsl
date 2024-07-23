
Texture2D<float4> input : register(t0);
RWTexture2D<float4> output : register(u0);

// most optimal config, defining thread group. 
[numthreads(8, 8, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    // assigns a slightly different color to each vertex, creating a "rainbow-like" effect
    //vertices[DTid.x].color = float4(sin(DTid.x), cos(DTid.x), sin(DTid.x + 1), 1.0f);
    float4 color = input.Load(DTid);
    color.b += .5f;
    
    output[DTid.xy] = color;
    
    // read render target, make things slightly bluer
}
