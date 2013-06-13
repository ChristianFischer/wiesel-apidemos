#ifdef GL_ES
precision mediump float;
#endif

uniform	sampler2D	texture0;
varying	vec2		my_texcoord0;
varying vec3		my_worldpos;


const int MAX_LIGHTS  = 4;
const vec3 AMBIENT    = vec3(0.1, 0.1, 0.1);
const vec3 NORMAL     = normalize(vec3(0.0, 0.0, 1.0));


struct LightInfo {
	vec3	position;
	vec3	diffuse_color;
	float	strength;
};

uniform	int			lights_count;
uniform	LightInfo	lights[MAX_LIGHTS];



vec3 computeLight(in LightInfo light) {
	vec3 dist = light.position - my_worldpos;
	float intensity = dot(NORMAL, normalize(dist));

	return light.diffuse_color * light.strength * intensity;
}



vec3 getLightFactor() {
	vec3 light = AMBIENT;

	if (lights_count == 0) {
		return light;
	}

	for(int i=0; i<MAX_LIGHTS; i++) {
		if (i < lights_count) {
			light += computeLight(lights[i]);
		}
	}

	return light;
}



void main(void) {
	vec4 texel = texture2D(texture0, my_texcoord0);

	vec3 light = getLightFactor();
	texel.rgb *= light;
	texel.rgb += light / 10.0;

	gl_FragColor = texel;
}
