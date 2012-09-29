#version 120

// Declare program parameters.
attribute  vec4  position;
attribute  vec4  colour;
attribute  vec4 normal;
uniform    mat4  modelview;
uniform    mat4  projection;
uniform    mat3  modelview_invtrans;
uniform    float time;
uniform    float rate; 

// Declare programmable pipeline variables.
varying  vec3  cam_position;
varying  vec4  cam_colour;
varying vec3 cam_normal;

// The main entry point for the vertex shader.
void  main()
{
	// Create the vertex in object space, and then trasnform it into camera then projection space.
        float ratetime = rate*time;
	float sintime = sin(ratetime);
	float costime = cos(ratetime);
	vec4  vertex_obj = vec4( position.xy, position.z*sintime+position.w*costime, 1.0 );
	vec4  vertex_cmr = modelview * vertex_obj;
	vec4  vertex_prj = projection * vertex_cmr;

	// Send OpenGL the vertex we have calculated.
	gl_Position = vertex_prj;

	// Pass the fragment shader the calculated values.
	cam_position = vertex_cmr.xyz;
	cam_colour    = colour;
	cam_normal  = normalize(modelview_invtrans*vec3(normal.xy*sintime + normal.zw*costime,1.0));
}
