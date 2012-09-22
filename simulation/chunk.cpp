
///
///
///
///
///



#include "chunk.h"



///
///
cx::simulation::chunk::global_parameters  cx::simulation::chunk::specification;



///
///
cx::simulation::chunk::chunk( chunk::local_parameters  configuration, cx::engine::base::scene*  domain ) : cx::engine::base::renderable( domain )
{
	// Set up the parameters for this chunk.
	this->configuration = configuration;
        this->real_partialy.function = &specification.function;
        this->real_partialx.function = &specification.function;
         this->imag_partialy.function = &specification.function;
        this->imag_partialx.function = &specification.function;
	// Create the vertices arrays in which to store vertices objects of varying levels of detail.
	vertices = new std::vector<cx::simulation::chunk::vertex>[chunk::specification.levels_of_detail + 1];

	// Create this chunk's geometry, then generate mipmaps down to the specified level.
	create();
	for (int i = 0; i <= chunk::specification.levels_of_detail; i++)
		generate( i );
}



///
///
cx::simulation::chunk::~chunk()
{
	// Run garbage collection on our properties.
	delete [] vertices;
}



///
///
void cx::simulation::chunk::create()
{
	// For clarity of code, we store the number of vertices in a row at this resolution.
	int N = std::pow( 2.0, chunk::specification.resolution ) + 1;

	// Iterate over every vertex position in the grid and generate appropriate complex z-values.
	for (int  x = -(N - 1) / 2; x <= (N - 1) / 2; x++)
		for (int  y = -(N - 1) / 2; y <= (N - 1) / 2; y++)
		{
			// Create a four-dimensional vertex and compute its complex z-value.
			chunk::vertex        sample;
                        float xp = (x + this->configuration.center.x / chunk::specification.scale_world)*chunk::specification.scale_data;
                        float yp = (y + this->configuration.center.y / chunk::specification.scale_world)*chunk::specification.scale_data;
			complexf  z = chunk::specification.function( complexf(xp,yp));
                        
                        real_partialx.helpery = yp;
                        sample.normal.x = differentiate (real_partialx, xp,1.0f);
                        real_partialy.helperx = xp;
                        sample.normal.y = differentiate (real_partialy, yp,1.0f);
                        imag_partialx.helpery = yp;
                        sample.normal.z = differentiate (imag_partialx, xp,1.0f);
                        imag_partialy.helperx = xp;
                        sample.normal.w = differentiate (imag_partialy, yp,1.0f);

			// Set the values of the four-dimensional vertex.
			sample.position.x = x;
			sample.position.y = y;
			sample.position.z = z.real() / chunk::specification.scale_data;
			sample.position.w = z.imag() / chunk::specification.scale_data;

			// Set the colour of the vertex.
			sample.colour = cx::utilities::maths::angle_to_hue( glm::atan2( sample.position.w, sample.position.z ) );

			//std::cout << "(" << sample.position.x << ", " << sample.position.y << ", " << sample.position.z << ", " << sample.position.w << ") ~ (" << sample.color.x << ", " << sample.color.y << ", " << sample.color.z << ", " << sample.color.w << ")" << std::endl;

			// Push the vertex onto the array.
			vertices[0].push_back( sample );
		}
}



///
///
void  cx::simulation::chunk::generate( unsigned int n )
{
	// Check that the preceding geomipmap has been generated.
	if ((n > 0) and (vertices[n - 1].size() == 0))
		throw std::string( "The generate( i ) method must be called in order, from i = 0 .. specifaction.levels_of_detail." );

	// For clarity of code, we store the number of vertices in a row at this resolution.
	int N = std::pow( 2.0, chunk::specification.resolution - n ) + 1;

	// If n is not the base mipmap, we will need to generate it.
	if (n > 0)
	{
		// We iterate over every other x-value and every other y-value in the M-squared grid of vertices comprising the baser mipmap.
		int  M = std::pow( 2.0, chunk::specification.resolution - (n - 1) ) + 1;
		for (int  x = 0; x < M; x += 2)
			for (int  y = 0; y < M; y += 2)
			{
				// Generate the vertex for this grid coordinate.
				chunk::vertex  sample;
				sample.position = vertices[n - 1][M * x + y].position;
				sample.colour    = vertices[n - 1][M * x + y].colour;
                                sample.normal    = vertices[n - 1][M * x + y].normal;

				// Push it onto the new grid.
				vertices[n].push_back( sample );
			}
	}

	// To ensure that this chunk matches up with adjacent chunks of lower LOD, interpolate along the outer edges.
	for (int  i = 1; i < N; i += 2)
	{
		int  j[4] = { i,  N * i,  N * N - i - 1,  N * N - N * i - 1 };        // These formulae represent a transition along the first row, the first column, the last row, and the last column.
		int  k[4] = { 1,  N,      1,              N };
		for (int  l = 0; l < 4; l++)
		{
			vertices[n][j[l]].position.z = (vertices[n][j[l] - k[l]].position.z + vertices[n][j[l] + k[l]].position.z) / 2.0f;
			vertices[n][j[l]].position.w = (vertices[n][j[l] - k[l]].position.w + vertices[n][j[l] + k[l]].position.w) / 2.0f;
                        
                        vertices[n][j[l]].normal = (vertices[n][j[l] - k[l]].normal + vertices[n][j[l] + k[l]].normal) / 2.0f;
                        
			vertices[n][j[l]].colour = glm::mix( vertices[n][j[l] - k[l]].colour, vertices[n][j[l] + k[l]].colour, 0.5 );
                        
                     
		}
	}

	// Create an array to store the indices of vertices, making triangles.
	unsigned int*  indices = new unsigned int[(N - 1) * (N - 1) * 6];

	// Iterate over every triangle, adding to the indices array.
	int  i = 0;
	for (int  x = 0; x < N - 1; x++)
		for (int  y = 0; y < N - 1; y++)
		{
			// First triangle in this quad.
            indices[i++] = y * N + x;
            indices[i++] = y * N + x + 1;
            indices[i++] = (y + 1) * N + x + 1;

			// Second triangle in this quad.
            indices[i++] = y * N + x;
            indices[i++] = (y + 1) * N + x + 1;
            indices[i++] = (y + 1) * N + x;
		}

	// Load both the indices and the vertices into buffer objects.
	buffers_index.push_back(  new cx::engine::pipeline::buffer( GL_ELEMENT_ARRAY_BUFFER, (void*)indices,              sizeof( unsigned int )                  * ((N - 1) * (N - 1) * 6), GL_STATIC_DRAW ) );
	buffers_vertex.push_back( new cx::engine::pipeline::buffer( GL_ARRAY_BUFFER,         (void*)&vertices[n].front(), sizeof( cx::simulation::chunk::vertex ) * (N * N),                 GL_STATIC_DRAW ) );

	// Garbage collect the now not-neccessary indices array.
	delete [] indices;
}



///
///
glm::mat4  cx::simulation::chunk::get_transformation()
{
	// Create the model matrix from individual scale, orientation and translation transformations.
	glm::mat4  scale       = glm::scale( glm::vec3( chunk::specification.scale_world, chunk::specification.scale_world, chunk::specification.scale_world ) );
	glm::mat4  orientation = glm::mat4();
	glm::mat4  translate   = glm::translate( glm::vec3( this->configuration.center.x, this->configuration.center.y, 0.0 ) );

	// Return the model matrix.
	return translate * orientation * scale;
}



///
///
void  cx::simulation::chunk::render( void*  parameters )
{
	// Access the OpenGL attributes list supplied to this rendering routine.
	cx::simulation::graph::attribute_list  attributes = *(cx::simulation::graph::attribute_list*)parameters;

	// Calculate the distance from this chunk's center to the camera, and therefore the level of detail to apply.
	float  distance = glm::distance( this->configuration.center, glm::vec2( this->domain->get_camera()->get_position().x, this->domain->get_camera()->get_position().y ) );
	int    n        = glm::floor( distance / (std::pow( 2.0, chunk::specification.resolution ) * chunk::specification.scale_world) );

	// Clamp the level of detail to valid values.
	if (n > chunk::specification.levels_of_detail)
		n = chunk::specification.levels_of_detail;

	// Send the correct vertex information based on the level of detail.
	glBindBuffer( GL_ARRAY_BUFFER, buffers_vertex[n]->get_id() );
	glEnableVertexAttribArray( attributes.vec4_position );
	glEnableVertexAttribArray( attributes.vec4_colour );
        glEnableVertexAttribArray( attributes.vec4_normal );
	glVertexAttribPointer( attributes.vec4_position, 4, GL_FLOAT, GL_FALSE, sizeof( cx::simulation::chunk::vertex ), (void*)offsetof( cx::simulation::chunk::vertex, position ) );
	glVertexAttribPointer( attributes.vec4_colour,    4, GL_FLOAT, GL_FALSE, sizeof( cx::simulation::chunk::vertex ), (void*)offsetof( cx::simulation::chunk::vertex, colour ) );
        glVertexAttribPointer( attributes.vec4_normal,    4, GL_FLOAT, GL_FALSE, sizeof( cx::simulation::chunk::vertex ), (void*)offsetof( cx::simulation::chunk::vertex, normal ) );

	// Draw the vertices.
	int N  = std::pow( 2.0, chunk::specification.resolution - n ) + 1;
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, buffers_index[n]->get_id() );
	glDrawElements( GL_TRIANGLES, (N - 1) * (N - 1) * 6, GL_UNSIGNED_INT, 0 );

    // Unbind the vertex attribute patterns used.
    glDisableVertexAttribArray( attributes.vec4_position );
    glDisableVertexAttribArray( attributes.vec4_colour );
    glDisableVertexAttribArray( attributes.vec4_normal );
}
