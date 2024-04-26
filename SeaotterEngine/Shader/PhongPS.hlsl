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
    float4 color : COLOR0;
    float3 normal : NORMAL0;
};

struct Pixel {
    float4 color : SV_Target;
};

Pixel main(Interpolant input) {
    
    Pixel output;
    
    input.normal = normalize(input.normal);

    // directional lights
    output.color.rgb = float3(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < sizeDir; i++) {
        const float3 lightUnitVector = normalize(-directionDir[i]);
        output.color.rgb += intensityDir[i] * ( ambientDir[i].rgb * input.color.rgb + 
            DiffuseLight(input.color.rgb, input.normal, lightUnitVector, diffuseDir[i].rgb) +
            SpecularLight(input.color.rgb, input.worldPosition, cameraPosition, input.normal, lightUnitVector, specularDir[i].rgb, 10.0f) );
        
            //SpecularLight(input.color.rgb, input.worldPosition, cameraPosition, input.normal, lightUnitVector, specularDir[i].rgb, shiness) );
    }
    
    // point lights
    for (int i = 0; i < sizePoint; i++) {
        const float3 lightVector = (positionPoint[i] - input.worldPosition).xyz;
        const float distance = length(lightVector);
        const float3 lightUnitVector = lightVector / distance;
        output.color.rgb += intensityPoint[i] * (ambientPoint[i].rgb * input.color.rgb +
            DiffuseLight(input.color.rgb, input.normal, lightUnitVector, diffusePoint[i].rgb) +
            SpecularLight(input.color.rgb, input.worldPosition, cameraPosition, input.normal, lightUnitVector, specularPoint[i].rgb, 10.0f));
    }
    
    output.color = saturate(float4(output.color.rgb, 1.0f));
    
    return output;
}