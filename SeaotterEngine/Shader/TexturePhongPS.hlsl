#include "Common/light.hlsli"

cbuffer camera : register(b1) {
    float4 cameraPosition;
}

cbuffer attributes : register(b4) {
    float shiness;
    float3 padding[3];
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
    output.color = float4(0.0f, 0.0f, 0.0f, 1.0f);
    for (int i = 0; i < sizeDir; i++) {
        output.color.rgb += intensityDir[i].x * (ambientDir[i].rgb * inputColor +
            DiffuseLight(inputColor, input.normal, -directionDir[i], diffuseDir[i].rgb) +
            SpecularLight(inputColor, input.worldPosition, cameraPosition, input.normal, -directionDir[i], specularDir[i].rgb, 10.0f));
    }
    
    // point lights
    for (int i = 0; i < sizePoint; i++) {
        const float3 lightVector = (positionPoint[i] - input.worldPosition).xyz;
        const float distance = length(lightVector);
        const float3 lightUnitVector = lightVector / distance;
        output.color.rgb += Attenuation(distance, attenConstantPoint, attenLinearPoint, attenQuadraticPoint) *
            intensityPoint[i].x * (ambientPoint[i].rgb * inputColor +
            DiffuseLight(inputColor, input.normal, lightUnitVector, diffusePoint[i].rgb) +
            SpecularLight(inputColor, input.worldPosition, cameraPosition, input.normal, lightUnitVector, specularPoint[i].rgb, 10.0f));
    }
    
    output.color = saturate(float4(output.color.rgb, 1.0f));
    
    return output;
}