
///
///
///
///
///



#include "maths.h"



///
///
glm::vec4  cx::utilities::maths::angle_to_hue( float angle )
{
	// Create an output variable.
	glm::vec4  color = glm::vec4( 0.0, 0.0, 0.0, 1.0 );

	// Create mappings useful for treating the angle as a colour on a hue hexagon.
	float  angle_degrees    = (angle / glm::acos( -1.0 )) * 180.0 + 180.0;                         // Map the -pi..pi angle to a 0..360 one.
	float  angle_normalised = angle_degrees / 60.0;                                                // Then map the angle to the 0..6 range.
	float  sliding_hue      = (1.0 - glm::abs( std::fmod( angle_normalised, 2.0 ) - 1.0) );        // Depending on angle_normalised, one component is clamped to 0.0, one to 1.0, and the last slides to this value.

	// Find out what sector of the hue hexagon this lies in.
	int sector = glm::floor( angle_normalised );
	switch (sector)
	{
		case 0: color.x = 1.0;         color.y = sliding_hue; break;
		case 1: color.x = sliding_hue; color.y = 1.0;         break;
		case 2: color.y = 1.0;         color.z = sliding_hue; break;
		case 3: color.y = sliding_hue; color.z = 1.0;         break;
		case 4: color.z = 1.0;         color.x = sliding_hue; break;
		case 5: color.z = sliding_hue; color.x = 1.0;         break;

		default: color.x = 1.0; break;
	}

	// Return the output RGB colour.
	return color;
}
