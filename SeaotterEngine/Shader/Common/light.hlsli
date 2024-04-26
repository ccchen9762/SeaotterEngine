#define MAX_LIGHTS 4

cbuffer LightDirectional : register(b2) {
    float4 directionDir[MAX_LIGHTS];
    float4 ambientDir[MAX_LIGHTS];
    float4 diffuseDir[MAX_LIGHTS];
    float4 specularDir[MAX_LIGHTS];
    float4 intensityDir[MAX_LIGHTS];
    unsigned int sizeDir;
};

cbuffer LightPoint : register(b3) {
    float4 positionPoint[MAX_LIGHTS];
    float4 ambientPoint[MAX_LIGHTS];
    float4 diffusePoint[MAX_LIGHTS];
    float4 specularPoint[MAX_LIGHTS];
    float4 intensityPoint[MAX_LIGHTS];
    unsigned int sizePoint;
    float attenConstantPoint;
    float attenLinearPoint;
    float attenQuadraticPoint;
};

inline float3 DiffuseLight(const in float3 diffuseColor, const in float3 normalVector, const in float3 lightUnitVector, const in float3 lightDiffuse) {
    return diffuseColor * lightDiffuse * max(0.0f, dot(lightUnitVector, normalVector));
}

inline float3 SpecularLight(const in float3 specularColor, const in float4 worldPosition, uniform float4 cameraPosition, const in float3 normalVector,
    const in float3 lightUnitVector, const in float3 lightSpecular, uniform float shiness) {
    
    const float3 reflectVector = 2 * dot(lightUnitVector, normalVector) * normalVector - lightUnitVector;
    return specularColor * lightSpecular * pow(max(0.0f, dot(normalize(cameraPosition - worldPosition), reflectVector)), shiness);
}

inline float Attenuation(const in float distance, const in float attenConstant, const in float attenLinear, const in float attenQuadratic) {
    return 1.0f / (attenConstant + attenLinear * distance + attenQuadratic * (distance * distance));
}