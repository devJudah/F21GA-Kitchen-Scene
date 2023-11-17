/**
 * Create a depth buffer to render the shadows for a light source
 * 
 * Sources used:
 *      LearnOpenGL by Joey de Vries - https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping
 *      ogldev.org by Etay Meiri - https://www.youtube.com/watch?v=kCCsko29pv0
 *      
*/

#include "ShadowMap.hpp"


ShadowMap::ShadowMap()
{

}

void ShadowMap::Initialise(unsigned int shadowWidth, unsigned int shadowHeight)
{
    // Save the width/height for later
    ShadowWidth = shadowWidth;
    ShadowHeight = shadowHeight;

    // Create new framebuffer - to render the the scene to create the depth map
    glGenFramebuffers(1, &DepthMapFBO);

    // Create a 2D texture that will be for the depth buffer
    glGenTextures(1, &DepthMap);
    glBindTexture(GL_TEXTURE_2D, DepthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, ShadowWidth, ShadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    
    // Set some parameters for the texture

    // TODO: Can this be something other than nearest? E.g. GL_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Clamp to remove the sharp cutoff when moving out of the shadow
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    // Now set the texture to the framebuffer object's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, DepthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthMap, 0);

    // Don't need to use colour
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void ShadowMap::SetActive()
{
    // Set this ready to render the depth scene
    glViewport(0, 0, ShadowWidth, ShadowHeight);
    glBindFramebuffer(GL_FRAMEBUFFER, DepthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
}
