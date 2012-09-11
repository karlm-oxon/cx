
///
/// Summary:  Prototypes for the cx::simulation::chunk class.
/// Remarks:  The chunk class describes a self-managing renderable section of the terrain of a graph.
/// Authors:  Jack K., Karl M.
///



#ifndef cx_simulation_chunk
#define cx_simulation_chunk



#include <SDL.h>
#include <glew.h>
#include <glm.hpp>
#include <ext.hpp>

#include <cmath>
#include <complex>
#include <vector>

#include "graph.h"
#include "../engine/base/renderable.h"
#include "../engine/pipeline/buffer.h"
#include "../utilities/maths.h"



#include <iostream>



namespace cx
{
	namespace simulation
	{

		/// Summary:  Defines a chunk of the graph terrain.
		/// Remarks:  Automatically generates the geometry based on an input parameter; implements geomipmapping to
		///           reduce GPU load.
		class chunk : public cx::engine::base::renderable
		{
			protected:

				/// Summary:  Defines a vertex within the chunk.
				/// Remarks:  The position vec4 should be interpreted as (x, y, u(x, y), v(x, y)).
				struct vertex
				{
					glm::vec4  position;
					glm::vec4  color;
				};

			public:

				/// Summary:  Defines the settings for a specific chunk instance.
				/// Remarks:  The glm::vec2 center specifies the center of the chunk in world coordinates.
				struct local_parameters
				{
					glm::vec2  center;
				};

				/// Summary:  Defines the settings for the static, class-wide chunk generation system.
				/// Remarks:  A complex function is necessary to get data from which to create the chunk geometry;
				///           The resolution is some value n, where (2^n)^2 is the maximum number of quads per chunk;
				///           Minimum value of n is defined by resolution - levels_of_detail;
				///           To transform from object to world coordinates, use [object] (x, y) * scale_world = [world] (x, y).
				///           Similarly, from object to data coordinates, [object] (x, y) * scale_data = [data] (x, y).
				struct global_parameters
				{
					std::complex<float>  (*function)( std::complex<float> );

					int    levels_of_detail;
					int    resolution;
					float  scale_world;
					float  scale_data;
				};



			protected:
				cx::simulation::chunk::local_parameters      configuration;
				std::vector<int>                             indices;
				std::vector<cx::simulation::chunk::vertex>*  vertices;

				std::vector<cx::engine::pipeline::buffer*>  buffers_index;
				std::vector<cx::engine::pipeline::buffer*>  buffers_vertex;

			public:
				static cx::simulation::chunk::global_parameters  specification;

				chunk( cx::simulation::chunk::local_parameters, cx::engine::base::scene* );
				~chunk();
				void  create();
				void  generate( unsigned int );

				virtual glm::mat4  get_transformation();
				virtual void       render( void* );
		};
	}
}



#endif
