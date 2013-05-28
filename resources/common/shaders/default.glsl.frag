#ifdef GL_ES
precision mediump float;
#endif

uniform	sampler2D	texture0;
varying	vec2		my_texcoord0;

void main(void) {
	gl_FragColor = texture2D(texture0, my_texcoord0);
}
