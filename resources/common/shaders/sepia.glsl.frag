#ifdef GL_ES
precision mediump float;
#endif

uniform	sampler2D	texture0;
varying	vec2		my_texcoord0;


void main(void) {
	vec4 texel  = texture2D(texture0, my_texcoord0);
	float gray  = dot(texel.rgb, vec3(0.299, 0.587, 0.114));
	vec4 sepia1 = vec4(0.15, 0.05, 0.00, 1.0);
	vec4 sepia2 = vec4(1.00, 0.90, 0.60, 1.0);

	gl_FragColor = mix(
					mix(sepia1, sepia2, gray),
					texel,
					0.2
	);
}
