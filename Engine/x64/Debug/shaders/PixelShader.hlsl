#include "VertexShader.hlsl"
Texture2D ObjTexture;
SamplerState ObjSamplerState;

cbuffer PF_PixelBuffer
{
	float4 ambientColor;
	float4 diffuseColor;
	float4 specularColor;
	float3 lightDirection;
	float specularPower;
};

float4 main(VSOutput input) : SV_TARGET
{
	float4 textureColor;
    float3 lightDir;
    float lightIntensity;
    float4 color;
    float3 reflection;
    float4 specular;


	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
    textureColor = ObjTexture.Sample(ObjSamplerState, input.uv);

	// Set the default output color to the ambient light value for all pixels.
	color = ambientColor;
	
	// Initialize the specular color.
	specular = float4(0.0f, 0.0f, 0.0f, 0.0f);
	
	// Invert the light direction for calculations.
	lightDir = -lightDirection;
	
	// Calculate the amount of light on this pixel.
	lightIntensity = saturate(dot(input.normal, lightDir));
	
	if (lightIntensity > 0.0f)
	{
		// Determine the final diffuse color based on the diffuse color and the amount of light intensity.
		color += (diffuseColor * lightIntensity);

		// Saturate the ambient and diffuse color.
		color = saturate(color);
		//The reflection vector for specular lighting is calculated here in the pixel shader provided the light intensity is greater than zero.This is the same equation as listed at the beginning of the tutorial.

		// Calculate the reflection vector based on the light intensity, normal vector, and light direction.
		reflection = normalize(2 * lightIntensity * input.normal - lightDir);
		//The amount of specular light is then calculated using the reflection vector and the viewing direction.The smaller the angle between the viewer and the light source the greater the specular light reflection will be.The result is taken to the power of the specularPower value.The lower the specularPower value the greater the final effect is.

		// Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
		specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower);
	}

	// Multiply the texture pixel and the input color to get the textured result.
	color = color * textureColor;

	if (color.x <= 0.1f && color.y <= 0.1f && color.z <= 0.1f)
	{
		color = input.color;
	}

	// Add the specular component last to the output color.
	color = saturate(color + specular);

	return color;
}