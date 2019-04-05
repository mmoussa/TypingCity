#version 330

// vertex attributes
layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Color;
layout(location=2) in vec3 in_Normal;

// transform
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ModelviewMatrix;
uniform mat3 u_NormalMatrix;

// directional light info
uniform vec3 u_LightColor;
uniform vec3 u_DirToLight;    // direction to light (in camera space!)

// outputs to rasterizer
out vec4 var_Color;

void main(void)
{
	// output transformed vertex position
	gl_Position = u_ProjectionMatrix * u_ModelviewMatrix * in_Position;

	vec3 N = normalize(u_NormalMatrix * in_Normal);		// transform and normalize surface normal
	vec3 L = normalize(u_DirToLight);					// normalize direction to light

	// compute diffuse lighting intensity
	float lightIntensity = dot(N, L);

	if (lightIntensity < 0.1) {
		lightIntensity = 0.1;
	}

	vec3 lightColor = lightIntensity * u_LightColor;

	// apply lighting to this vertex and pass result to rasterizer
	var_Color.rgb = lightColor * in_Color.rgb;
	var_Color.a = in_Color.a;
}
