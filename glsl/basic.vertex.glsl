#version 120

// Declare program parameters.
attribute  vec4  position;
attribute  vec4  color;
uniform    mat4  modelview;
uniform    mat4  projection;
uniform    float time;
uniform    float rate; 

// Declare programmable pipeline variables.
varying  vec3  position_interpolated;
varying  vec4  color_interpolated;

// The main entry point for the vertex shader.
void  main()
{
	// Create the vertex in object space, and then trasnform it into camera then projection space.
        float ratetime = rate*time;
	vec4  vertex_obj = vec4( position.xy, position.z*sin(ratetime)+position.z*cos(ratetime), 1.0 );
	vec4  vertex_cmr = modelview * vertex_obj;
	vec4  vertex_prj = projection * vertex_cmr;

	// Send OpenGL the vertex we have calculated.
	gl_Position = vertex_prj;

	// Pass the fragment shader the calculated values.
	position_interpolated = vertex_prj.xyz;
	color_interpolated    = color;
}
