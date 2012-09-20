///
/// Summary:  Prototypes for the cx::engine::pipeline::texture class.
/// Remarks:  Describes a GPU-based texture stored in the OpenGL programmable pipeline.
///           
/// Authors:  Jack K., Karl M.
///

#ifndef TEXTURE_H
#define	TEXTURE_H

#include <SDL.h>
#include <glew.h>
#include <glm.hpp>


namespace cx
{
	namespace engine
	{
		namespace pipeline
		{
			/// Summary:  Describes a GPU-based texture stored in the OpenGL programmable pipeline.
			/// Remarks:  Texture must be 'filled' e.g with calls to glTexImage, in between bind and unbind
                        ///           calls
			class texture
			{
				protected:
					unsigned int  id;
					const unsigned int  type;
                                        const unsigned int  texture_unit;


				public:
					texture(const unsigned int dim = GL_TEXTURE_2D,const unsigned int texture_unit = GL_TEXTURE0 );
					~texture();

					unsigned int  get_id()     { return id; }
					unsigned int  get_type() { return type; }
                                        unsigned int  get_texture_unit() { return texture_unit; }
                                        void bind ();
                                        void unbind();
			};
		}
	}
}

#endif	/* TEXTURE_H */

