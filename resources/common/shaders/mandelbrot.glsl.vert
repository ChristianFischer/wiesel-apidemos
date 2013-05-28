uniform		mat4		mProjection;
uniform		mat4		mModelview;
attribute	vec4		vPosition;
attribute	vec4		vColor;
varying		vec4		mandelbrot_arg;

void main() {
	gl_Position    = vPosition * mModelview * mProjection;
	mandelbrot_arg = vColor;
}
