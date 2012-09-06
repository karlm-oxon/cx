
///
/// Summary:  Prototypes for the cx::engine::scene class.
/// Remarks:  The scene class is an abstract class designed to be inherited as a bolt-on interface for any class
///           needing to act as a rendering manager.
/// Authors:  Jack K., Karl M.
///



#ifndef cx_engine_base_scene
#define cx_engine_base_scene



#include <vector>

#include "renderable.h"
#include "../pipeline/program.h"



namespace cx
{
	namespace engine
	{
		namespace base
		{
			/// Summary:  Describes an object which can act as a rendering manager.
			/// Remarks:  Inheriting from this class adds a number of data structures to the child class, as well as
			///           adding the prerequisite that certain initialisation routines are called (by the base::scene
			///           constructor). All virtual void member functions must be overridden by the child class.
			class scene
			{
				protected:
					std::vector<cx::engine::pipeline::program*>  programs;
					std::vector<base::renderable*>               renderables;

				public:
					scene();
					virtual void  initialise_programs();
					virtual void  initialise_renderables();
					virtual void  render();

					std::vector<cx::engine::pipeline::program*>  get_programs()    { return programs; }
					std::vector<base::renderable*>               get_renderables() { return renderables; }
			};
		}
	}
}



#endif
