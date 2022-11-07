#include "BasicShaderHeader.hlsli"

//struct GSOutput
//{
//	float4 pos : SV_POSITION;
//};

[maxvertexcount(3)]
void main(
	point VSOutput input[1] : SV_POSITION, 
	inout TriangleStream< GSOutput > output
)
{

	GSOutput element;
	element.normal = input[0].normal;
	element.uv = input[0].uv;

	element.svpos = input[0].svpos;
	output.Append(element);

	element.svpos = input[0].svpos + float4(10.0f, 10.0f, 0.0f, 0.0f);
	output.Append(element);

	element.svpos = input[0].svpos + float4(10.0f, 0.0f, 0.0f, 0.0f);
	output.Append(element);

	//for (uint i = 0; i < 3; i++)
	//{
	//	GSOutput element;
	//	element.svpos = input[i].svpos;
	//	element.normal = input[i].normal;
	//	element.uv = input[i].uv;
	//	output.Append(element);
	//}
	//output.RestartStrip();
	//for (uint i = 0; i < 3; i++)
	//{
	//	GSOutput element;
	//	element.svpos = input[i].svpos + float4(20.0f, 0.0f, 0.0f, 0.0f);
	//	element.normal = input[i].normal;
	//	element.uv = input[i].uv * 5.0f;
	//	output.Append(element);
	//}

}