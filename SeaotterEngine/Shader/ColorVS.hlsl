cbuffer ConstantBuffer {
    matrix transform;
};

struct Vertex {
    float4 position : SV_Position;
    float4 color : COLOR0;
};

struct Interpolant {
    float4 position : SV_Position;
    float4 color : COLOR0;
};

Interpolant main(Vertex input) {
    Interpolant output;
    output.position = mul(input.position, transform); // mul using right multiply
    output.color = input.color;
    return output;
}