#version 330

// vertex attributes
layout(location=0) in vec4 in_Position;
layout(location=2) in vec3 in_Normal;

// transform
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ModelviewMatrix;
uniform mat3 u_NormalMatrix;

// directional light info
uniform vec3 u_LightColor;
uniform vec3 u_DirToLight;    // direction to light (in camera space!)

// outputs to rasterizer
out vec3 var_LightColor;

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

	// pass light color to rasterizer
	var_LightColor = lightIntensity * u_LightColor;

    //var_LightColor = u_LightColor;
    //var_LightColor = u_LightDir;
    //var_LightColor = in_Normal;
    //var_LightColor = N;
}
