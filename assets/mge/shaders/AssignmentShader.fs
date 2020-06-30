#version 330

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D diffuseTexture;

uniform vec3 lightColor;
uniform float specularStrength;
uniform float shininess;
uniform float ambientStrength;

in vec3 fNormal;
in vec3 fragPos;
in vec2 texCoord;

out vec4 sColor;

vec4 fragment_color;

void main (void) {
	fragment_color = texture(diffuseTexture,texCoord);

	//AMBIENT
	vec3 ambient = ambientStrength * lightColor;

	//DIFFUSE
	vec3 norm = normalize(fNormal);
	vec3 lightDir = lightPos - fragPos;
	vec3 lightDirNorm = normalize(lightDir);//normalizing is required for directional calculations
	float diffIntensity = max(dot(norm,lightDirNorm), 0.0);//max prevents it from going below 0, the greater the angle the smaller the value will be

	//ATTENUATION
	float lightDistance = length(lightDir);
	diffIntensity /=  1 + lightDistance; //linear attenuetion, when lightdistance is 0 the object is divided by 1 which is the brightest
	vec3 diffuse = diffIntensity * lightColor;
	
	//SPECULAR
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDirNorm, norm);//reflect lightdir in relation to norm, negate lightdirnorm because it points from object to light instead of the other way
	float spec = 
		pow( max( dot(
		viewDir, reflectDir) //power		
		, 0.0)//max: keep it above 0		
		,shininess);//dot: higher shininess is less scattering
	vec3 specular = specularStrength * spec * lightColor;
	
	vec3 result = (ambient + diffuse + specular) * fragment_color.rgb;//dont use alpha from texture, lighting takes care of it
	sColor = vec4(result, fragment_color.a);
}
