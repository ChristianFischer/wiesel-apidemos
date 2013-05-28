#ifdef GL_ES
precision mediump float;
#endif

uniform	sampler2D	texture0;
varying	vec2		my_texcoord0;


void main(void) {
	vec4 texel = texture2D(texture0, my_texcoord0);
	float gray = dot(texel.rgb, vec3(0.299, 0.587, 0.114));
	
	gl_FragColor = vec4(vec3(gray), 1.0);
}
