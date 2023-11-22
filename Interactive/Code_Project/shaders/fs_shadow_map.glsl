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

// This sets the make number of possible lights - should ideally match this to how many lights there are
const int NUM_LIGHTS = 4;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace[NUM_LIGHTS];
} fs_in;

uniform sampler2D tex;
uniform sampler2D shadowMap[NUM_LIGHTS];


uniform vec3 viewPosition;

// Not sure if this will work - can we have dynamic loops?
uniform int num_lights;

struct LightStruct {
    vec3 lightPosition;
    
    // Light properties
    vec3 lightColor;
    // For simplified model we just use light colour for all of these
    // vec3 diffuse_color;
    // vec3 specular_color;

    float k_ambient;  // Ambient constant

    // See Table in Lecture 14 - Advanced lightning for possible values
    float atten_constant;   // Attenuation constant
    float atten_linear;     // Attenuation linear term
    float atten_quadratic;  // Attenuation quadratic term

    bool turnedOn; // If this light is on or off
};

uniform LightStruct lights[NUM_LIGHTS];

// TODO: Figure out where these live
uniform float k_diffuse;  // Diffuse constant
uniform float k_specular; // specular constant

// Material specific
uniform float shininess;

// PCF settings
uniform int PCF_FilterSize = 3; // How many samples to take for the PCF. 
                                // Samples taken: PCF_FilterSize^2 (since this is 3 samples in x and 3 samples in y directions)
                                // Possibly should also be odd?


float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightPos, int shadowMapIndex)
{   
    // See https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping for code source

    // Perform perspective divide (note: not required for orthographic projection, but keep it for perspective)
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;

    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap[shadowMapIndex], projCoords.xy).x;

    // Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

    // Fix for "Shadow Acne" - Calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

    // PCF (percentage-closer filtering) - Help smooth shadow edges
    float shadowTotal = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap[shadowMapIndex], 0);

    // Find the half filter size so we can go from -half to +half (including 0)
    int PCF_FilterSizeMin = PCF_FilterSize / 2;
    int PCF_FilterSizeMax = - PCF_FilterSizeMin + PCF_FilterSize;
    for(int x = -PCF_FilterSizeMin; x < PCF_FilterSizeMax; x++)
    {
        for(int y = -PCF_FilterSizeMin; y < PCF_FilterSizeMax; y++)
        {
            float pcfDepth = texture(shadowMap[shadowMapIndex], projCoords.xy + vec2(x, y) * texelSize).x; 
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

vec3 CalculateLight(LightStruct light) 
{
    return vec3(0.0);
}

void main()
{
    // Store total lighting contribution
    vec3 totalLighting = vec3(0.0);

    // Set colour based on the texture
    vec3 color = texture(tex, fs_in.TexCoords).rgb;

    // Calculate normal - will be used a few times
    vec3 normal = normalize(fs_in.Normal);

    for(int i=0; i < num_lights; i++) {
        
        if (!lights[i].turnedOn) continue;

        // Ambient
        vec3 ambient = lights[i].k_ambient * lights[i].lightColor;

        // Diffuse
        vec3 lightDir = normalize(lights[i].lightPosition - fs_in.FragPos);
        float diff = max(dot(lightDir, normal), 0.0);
        vec3 diffuse = k_diffuse * diff * lights[i].lightColor;

        // Test if we are on the right side of the object to do a specular highlight
        // See: https://stackoverflow.com/questions/61166762/opengl-phong-lighting-specular-highlight-is-wrong/61167359#61167359
        vec3 specular = vec3(0.0);
        float NormalDotLightDir = dot(normal, lightDir);
        if (NormalDotLightDir > 0.0) {
             // Specular - Use the Blinn-Phong method to improve specular effect - https://learnopengl.com/Advanced-Lighting/Advanced-Lighting
            vec3 viewDir = normalize(viewPosition - fs_in.FragPos);
            vec3 halfwayDir = normalize(lightDir + viewDir);  
            float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
            specular = k_specular * spec * lights[i].lightColor;
        }

        // Attenuation
        float distance = length(lights[i].lightPosition - fs_in.FragPos);
        float attenuation = 1.0f / (lights[i].atten_constant + lights[i].atten_linear * distance + lights[i].atten_quadratic * (distance * distance));

        // Adjust values based on attenuation
        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;

        // Calculate shadow
        float shadow = ShadowCalculation(fs_in.FragPosLightSpace[i], lights[i].lightPosition, i);                      
        vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));  
        //vec3 lighting = (ambient + diffuse + specular); // No shadows
        
       // vec3 lighting = (ambient + diffuse + specular); // No shadows
        //if(i == 1) {
        //    float shadow = ShadowCalculation(fs_in.FragPosLightSpace[i], lights[i].lightPosition, i);
        //    lighting = (ambient + (1.0 - shadow) * (diffuse + specular));
        //}

        totalLighting += lighting;
    }

    // Add total lighting together with colour
    totalLighting *= color;

    // Gamma correction. TODO: Move this into option
    float gamma = 2.2;
    totalLighting = pow(totalLighting, vec3(1.0/gamma));

    // Final result
    FragColor = vec4(totalLighting, 1.0);
}