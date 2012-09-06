
///
/// Summary:  Contains static utility functions pertaining to the modification of the host filesystem.
/// Authors:  Jack K., Karl M.
///



#ifndef cx_utilities_files
#define cx_utilities_files



#include <fstream>
#include <sstream>
#include <string>



namespace cx
{
	namespace utilities
	{
		/// Summary:  Contains static member functions for interacting with files on the host system.
		/// Remarks:  The private constructor marks this class as static; it may not be initialised.
		class file
		{
			private:
				file();

			public:
				static std::string  contents( std::string );
		};
	}
}



#endif
