uniform		mat4		mProjection;
uniform		mat4		mModelview;
uniform		sampler2D	texture0;
attribute	vec4		vPosition;
attribute	vec2		vTexCoord0;
attribute	vec2		vTexCoord1;
varying		vec2		my_texcoord0;

void main() {
	gl_Position  = vPosition * mModelview * mProjection;
	my_texcoord0 = vTexCoord0;
}
