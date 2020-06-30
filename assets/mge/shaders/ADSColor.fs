#version 330

//uniform vec3 ambientLightColor;
//uniform vec3 diffuseColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 fragment_color;
uniform vec3 lightColor;
uniform float specularStrength;
uniform float shininess;
uniform float ambientStrength;

in vec3 fNormal;
in vec3 fragPos;
in vec2 texCoord;

out vec4 sColor;


void main (void) {

	//AMBIENT
	vec3 ambient = ambientStrength * lightColor;

	//DIFFUSE
	vec3 norm = normalize(fNormal);
	vec3 lightDir = lightPos - fragPos;
	vec3 lightDirNorm = normalize(lightDir);
	float lightDistance = length(lightDir);
	float diffIntensity = max(dot(norm,lightDirNorm), 0.0);//max prevents it from going below 0, the greater the angle the smaller the value will be
	//ATTENUATION
	diffIntensity /=  1 + lightDistance; // i liked this better than the quadratic one
	vec3 diffuse = diffIntensity * lightColor;

	//SPECULAR
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDirNorm, norm);//reflect lightdir in relation to norm, points everything the wrong way so: negate
	float spec;
	spec = 
		pow( max( dot(
		viewDir, reflectDir) 		
		, 0.0)// keep it above 0		
		,shininess);//higher shininess is less scattering

	vec3 specular = specularStrength * spec * lightColor;
	
	vec3 result = (ambient + diffuse +specular) * fragment_color;//dont use alpha from texture, lighting takes care of it

	//DEBUG:
	//result = vec3(0,0,1);
	//result.x = (dot(lightDirNorm, norm) + 1) / 2 ;
	
	sColor = vec4(result, 1);
}
