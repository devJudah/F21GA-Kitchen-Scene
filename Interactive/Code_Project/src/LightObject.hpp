#pragma once


#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"


class LightObject
{  
    public: 

        // Light position
        glm::vec3 lightPosition;

        // What the light is looking at
        glm::vec3 lightDirection;
        // Up direction for the light
        glm::vec3 lightUp;

        // How close to process any shadows / how close the light has an effect
        float near_plane;
        // How far to process any shadows / how far the light has an effect
        float far_plane;

        // If the light is directional (and thus should use orthographic projection)
        bool DirectionalLight;

        // Light color
        glm::vec3 lightColor;

        // Light ambient constant
        GLfloat k_ambient;

        // Attenuation constants - https://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
        GLfloat atten_constant = 1.0f;
        GLfloat atten_linear = 0.045f;
        GLfloat atten_quadratic = 0.0075f;

        bool switched_on;

        float orth_left = -10.0f;
        float orth_right = 10.0f;
        float orth_bottom = -10.0f;
        float orth_top = 10.0f;

        LightObject();

        LightObject(glm::vec3 lightPosition, glm::vec3 lightColor);

        LightObject(
                glm::vec3 lightPosition, 
                glm::vec3 lightDirection, 
                glm::vec3 lightUp, 
                float near_plane,
                float far_plane,
                bool directionalLight,
                glm::vec3 lightColor,
                GLfloat k_ambient
            );

        LightObject(
            glm::vec3 lightPosition, 
            glm::vec3 lightDirection, 
            glm::vec3 lightUp, 
            float near_plane,
            float far_plane,
            bool directionalLight,
            glm::vec3 lightColor,
            GLfloat k_ambient,
            GLfloat atten_constant,
            GLfloat atten_linear,
            GLfloat atten_quadratic
        );

        // Returns the light view matrix glm::lookAt()
        glm::mat4 GetLightViewMatrix();

        // Returns the light projection matrix. Orthographic if the light is directional, perspective if it is not
        glm::mat4 GetLightProjectionMatrix(GLfloat shadowWidth, GLfloat shadowHeight);

        void Off();

        void On();

        bool isOn();

};
