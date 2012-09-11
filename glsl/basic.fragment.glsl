#version 120

// Declare programmable pipeline variables.
varying  vec3  position_interpolated;
varying  vec4  color_interpolated;

// The main entry point for the fragment shader.
void  main()
{
	// Send the fragment colour to OpenGL.
	gl_FragColor = color_interpolated;
}
