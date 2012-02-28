struct Light
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 position;
	float constant_attenuation;
	float linear_attenuation;
	float quadratic_attenuation;
};

const int MAX_LIGHTS = 32;

uniform int nlights;
uniform Light lights[MAX_LIGHTS];

void main()
{
	vec4 obj_pos = gl_ModelViewProjectionMatrix * gl_Vertex;	//ftransform();
//	vec4 obj_pos = ftransform();
	vec3 N = -normalize(gl_NormalMatrix * gl_Normal);

	vec4 color = vec4(0, 0, 0, 1);

	int i;
	
	for (i = 0; i < nlights; i++)
	{
	//	vec4 light = normalize(lights[i].position.xyz - P.xyz);
	
		vec3 light_pos	= lights[i].position.xyz;
		
		vec3 L = normalize(light_pos - obj_pos.xyz);

		vec4 diffuseColor = max(0.0, dot(N, L)) * lights[i].diffuse;
	
		color += diffuseColor;
	}

	gl_Position = obj_pos;

	gl_FrontColor = color;
	gl_BackColor = vec4(1, 0, 0, 1);

//	gl_FrontColor = vec4(0, 1, 0, 1);
}
