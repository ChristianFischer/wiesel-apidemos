#ifdef GL_ES
precision mediump float;
#endif

varying		vec4		mandelbrot_arg;

const float scale = 1.0;
const int   iter  = 100;


vec4 hsv2rgb(float hue, float sat, float val) {
	vec4 result;

	int   i = int(hue * 6.0);
	float f = hue * 6.0 - float(i);
	float p = val * (1.0 - sat);
	float q = val * (1.0 - f * sat);
	float t = val * (1.0 - (1.0 - f) * sat);

	switch(i) {
		case 0: result = vec4(val, t,   p,   1.0); break;
		case 1: result = vec4(q,   val, p,   1.0); break;
		case 2: result = vec4(p,   val, t,   1.0); break;
		case 3: result = vec4(p,   q,   val, 1.0); break;
		case 4: result = vec4(t,   p,   val, 1.0); break;
		case 5: result = vec4(val, p,   q,   1.0); break;
	}

	return result;
}


void main(void) {
	vec2 z, c;

	c.x = mandelbrot_arg.x;
	c.y = mandelbrot_arg.y;

	int i;
	z = c;
	for(i=0; i<iter; i++) {
		float x = (z.x * z.x - z.y * z.y) + c.x;
		float y = (z.y * z.x + z.x * z.y) + c.y;

		if ((x * x + y * y) > 4.0) {
			break;
		}

		z.x = x;
		z.y = y;
	}

	if (i == iter) {
		gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
	else {
		float hue = float(i) / 100.0;
		float sat = 1.0;
		float val = 1.0;

		gl_FragColor = hsv2rgb(hue, sat, val);
	}
}
