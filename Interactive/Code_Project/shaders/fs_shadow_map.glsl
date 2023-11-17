/**
 * Create a depth buffer to render the shadows for a light source
 * 
 * Sources used:
 *      LearnOpenGL by Joey de Vries - https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping
 *      ogldev.org by Etay Meiri - https://github.com/emeiri/ogldev/blob/master/Common/Shaders/lighting_new.fs
 *      
*/

#version 410 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D tex;
uniform sampler2D shadowMap;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

// Light properties
uniform vec3 lightColor;
// For simplified model we just use light colour for all of these
// uniform vec3 diffuse_color;
// uniform vec3 specular_color;

uniform float k_ambient;  // Ambient constant
uniform float k_diffuse;  // Diffuse constant
uniform float k_specular; // specular constant

// Material specific
uniform float shininess;

// See Table in Lecture 14 - Advanced lightning for possible values
uniform float atten_constant;   // Attenuation constant
uniform float atten_linear;     // Attenuation linear term
uniform float atten_quadratic;  // Attenuation quadratic term

// PCF settings
uniform int PCF_FilterSize = 3; // How many samples to take for the PCF. 
                                // Samples taken: PCF_FilterSize^2 (since this is 3 samples in x and 3 samples in y directions)
                                // Possibly should also be odd?


float ShadowCalculation(vec4 fragPosLightSpace)
{   
    // See https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping for code source

    // Perform perspective divide (note: not required for orthographic projection, but keep it for perspective)
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;

    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).x;

    // Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

    // Fix for "Shadow Acne" - Calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(lightPosition - fs_in.FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

    // PCF (percentage-closer filtering) - Help smooth shadow edges
    float shadowTotal = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);

    // Find the half filter size so we can go from -half to +half (including 0)
    int PCF_FilterSizeMin = PCF_FilterSize / 2;
    int PCF_FilterSizeMax = - PCF_FilterSizeMin + PCF_FilterSize;
    for(int x = -PCF_FilterSizeMin; x < PCF_FilterSizeMax; x++)
    {
        for(int y = -PCF_FilterSizeMin; y < PCF_FilterSizeMax; y++)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).x; 
            shadowTotal += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    // Average the result by how many samples were taken
    float shadow = shadowTotal / float(PCF_FilterSize * PCF_FilterSize);
    
    // Keep the shadow at 0.0 when outside the far_plane region of the light's frustum. "Over sampling" section - https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping
    if(projCoords.z > 1.0)
        shadow = 0.0;
    
        
    return shadow;
}

void main()
{
    // Set colour based on the texture
    vec3 color = texture(tex, fs_in.TexCoords).rgb;

    // Calculate normal - will be used a few times
    vec3 normal = normalize(fs_in.Normal);

    // Ambient
    vec3 ambient = k_ambient * lightColor;

    // Diffuse
    vec3 lightDir = normalize(lightPosition - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = k_diffuse * diff * lightColor;

    // Specular - Use the Blinn-Phong method to improve specular effect - https://learnopengl.com/Advanced-Lighting/Advanced-Lighting
    vec3 viewDir = normalize(viewPosition - fs_in.FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
    vec3 specular = k_specular * spec * lightColor;

    // Attenuation
    float distance = length(lightPosition - fs_in.FragPos);
    float attenuation = 1.0f / (atten_constant + atten_linear * distance + atten_quadratic * (distance * distance));

    // Adjust values based on attenuation
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    // Calculate shadow
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);                      
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    

    // Final result
    FragColor = vec4(lighting, 1.0);
}