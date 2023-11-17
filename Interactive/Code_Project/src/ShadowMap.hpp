/**
 * Create a depth buffer to render the shadows for a light source
 * 
 * Sources used:
 *      LearnOpenGL by Joey de Vries - https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping
 *      ogldev.org by Etay Meiri - https://www.youtube.com/watch?v=kCCsko29pv0
 *      
*/

#pragma once

#include <glad/glad.h>


class ShadowMap
{
    public:

        GLuint DepthMapFBO;
        GLuint DepthMap;

        ShadowMap();

        void Initialise(unsigned int shadowWidth, unsigned int shadowHeight);

        void SetActive();

    
    private:

        // Probably won't change the width and height again?

        unsigned int ShadowWidth;
        unsigned int ShadowHeight;


};
