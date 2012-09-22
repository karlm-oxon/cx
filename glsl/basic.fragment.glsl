#version 120

// Declare programmable pipeline variables.
varying  vec3  cam_position; //position in camera space
varying  vec4  cam_colour; //colour
varying  vec3 cam_normal;
uniform mat4 modelview;
uniform mat4 p;
 
struct lightSource
{
  vec4 position;//In camera space
  vec4 diffuse;
  vec4 specular;
  float constantAttenuation, linearAttenuation, quadraticAttenuation;
  float spotCutoff, spotExponent;
  vec3 spotDirection;
};

uniform lightSource light0;

vec4 scene_ambient = vec4(0.4, 0.4, 0.4, 1.0);
 
struct material
{
  vec4 specular;
  float shininess;
};

material mat = material (vec4 (1.0,1.0,1.0,1.0), 0.3);
 
void main()
{
  
    
  vec3 normalDirection = (int (gl_FrontFacing)*2-1)* cam_normal;//If back-facing reverse direction
  vec3 viewDirection = normalize(vec3(-cam_position));//Camera at origin in camera space
  vec3 lightDirection;
  float attenuation;
 
  if (0.0 == light0.position.w) // directional light?
    {
      attenuation = 1.0; // no attenuation
      lightDirection = normalize(vec3(light0.position));
    } 
  else // point light or spotlight (or other kind of light) 
    {
      vec3 positionToLightSource = vec3(light0.position.xyz - cam_position);
      float distance = length(positionToLightSource);
      lightDirection = normalize(positionToLightSource);
      attenuation = 1.0 / (light0.constantAttenuation
                           + light0.linearAttenuation * distance
                           + light0.quadraticAttenuation * distance * distance);
 
      if (light0.spotCutoff <= 90.0) // spotlight?
        {
          float clampedCosine = max(0.0, dot(-lightDirection, light0.spotDirection));
          if (clampedCosine < cos(radians(light0.spotCutoff))) // outside of spotlight cone?
            {
              attenuation = 0.0;
            }
          else
            {
              attenuation = attenuation * pow(clampedCosine, light0.spotExponent); 
            }
        }
    }
 
  vec3 ambientLighting = vec3(scene_ambient) * vec3(cam_colour);
 
  vec3 diffuseReflection = attenuation 
    * vec3(light0.diffuse) * vec3(cam_colour)
    * max(0.0, dot(normalDirection, lightDirection));
 
  vec3 specularReflection;
  if (dot(normalDirection, lightDirection) < 0.0) // light source on the wrong side?
    {
      specularReflection = vec3(0.0, 0.0, 0.0); // no specular reflection
    }
  else // light source on the right side
    {
      specularReflection = attenuation * vec3(light0.specular) * vec3(mat.specular) 
        * pow(max(0.0, dot(reflect(-lightDirection, normalDirection), viewDirection)), mat.shininess);
    }
 
  gl_FragColor = vec4(ambientLighting + diffuseReflection + specularReflection, 1.0);
}
