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

varying  vec4  cam_colour;


// The main entry point for the vertex shader.
void  main()
{
	// Create the vertex in object space, and then trasnform it into camera then projection space.
        float ratetime = rate*time;
	float sintime = sin(ratetime);
	float costime = cos(ratetime);
	vec4  vertex_obj = vec4( position.xy, position.z*sintime+position.w*costime, 1.0 );
        vec4  cam_normal  = vec4 (normalize(modelview_invtrans*vec3(normal.xy*sintime + normal.zw*costime,1.0)),0.0);
	vec4  vertex_cmr = modelview * vertex_obj + cam_normal;
	vec4  vertex_prj = projection * vertex_cmr;

	

	
	cam_colour    = colour;
	

        // Send OpenGL the vertex we have calculated.
	gl_Position = vertex_prj;
}
