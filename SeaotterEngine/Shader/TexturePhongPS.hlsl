#include "Common/light.hlsli"

cbuffer camera : register(b1) {
    float4 cameraPosition;
}

cbuffer attributes : register(b4) {
    float shiness;
}

struct Interpolant {
    float4 position : SV_Position;
    float4 worldPosition : POSITION0;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
};

struct Pixel {
    float4 color : SV_Target;
};

Texture2D tex : register(t0);
SamplerState sam : register(s0);

Pixel main(Interpolant input) {
    /*Pixel output;

    output.color = tex.Sample(sam, input.texcoord);
	
    return output;*/
    
    
    Pixel output;
    
    const float3 inputColor = tex.Sample(sam, input.texcoord).rgb;
    
    input.normal = normalize(input.normal);

    // directional lights
    output.color.rgb = float3(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < sizeDir; i++) {
        const float3 lightUnitVector = normalize(-directionDir[i]);
        output.color.rgb += intensityDir[i] * (ambientDir[i].rgb * inputColor +
            DiffuseLight(inputColor, input.normal, lightUnitVector, diffuseDir[i].rgb) +
            SpecularLight(inputColor, input.worldPosition, cameraPosition, input.normal, lightUnitVector, specularDir[i].rgb, shiness));
    }
    
    // point lights
    for (int i = 0; i < sizePoint; i++) {
        const float3 lightVector = (positionPoint[i] - input.worldPosition).xyz;
        const float distance = length(lightVector);
        const float3 lightUnitVector = lightVector / distance;
        output.color.rgb += intensityPoint[i] * (ambientPoint[i].rgb * inputColor +
            DiffuseLight(inputColor, input.normal, lightUnitVector, diffusePoint[i].rgb) +
            SpecularLight(inputColor, input.worldPosition, cameraPosition, input.normal, lightUnitVector, specularPoint[i].rgb, shiness));
    }
    
    output.color = saturate(float4(output.color.rgb, 1.0f));
    
    return output;
}