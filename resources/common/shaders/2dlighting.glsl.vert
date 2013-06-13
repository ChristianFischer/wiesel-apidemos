uniform		mat4		mProjection;
uniform		mat4		mModelview;
uniform		sampler2D	texture0;
attribute	vec4		vPosition;
attribute	vec2		vTexCoord0;
varying		vec2		my_texcoord0;
varying		vec3		my_worldpos;

void main() {
	vec4 worldpos = vPosition * mModelview;

	gl_Position  = worldpos * mProjection;
	my_worldpos  = worldpos.xyz;
	my_texcoord0 = vTexCoord0;
}
