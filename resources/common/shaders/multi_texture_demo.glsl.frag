#ifdef GL_ES
precision mediump float;
#endif

uniform	sampler2D	texture0;
uniform	sampler2D	texture1;
varying	vec2		my_texcoord0;

void main(void) {
	vec4 color0 = texture2D(texture0, my_texcoord0);
	vec4 color1 = texture2D(texture1, my_texcoord0 / 1.35);

	gl_FragColor = vec4(mix(color0.rgb, vec3(0.15, 0.0, 0.0), color1.r), 1.0);
}
