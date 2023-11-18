#include "LightObject.hpp"


LightObject::LightObject() { }

LightObject::LightObject(glm::vec3 lightPosition, glm::vec3 lightColor)
{
    this->lightPosition = lightPosition;
    this->lightColor = lightColor;

    this->switched_on = true;
}

LightObject::LightObject(glm::vec3 lightPosition, glm::vec3 lightDirection, glm::vec3 lightUp, 
            float near_plane, float far_plane, bool directionalLight,
            glm::vec3 lightColor, GLfloat k_ambient )
{
    this->lightPosition = lightPosition;
    this->lightDirection = lightDirection;
    this->lightUp = lightUp;
    this->near_plane = near_plane;
    this->far_plane = far_plane;
    this->DirectionalLight = directionalLight;
    this->lightColor = lightColor;
    this->k_ambient = k_ambient;

    this->switched_on = true;
}

LightObject::LightObject(glm::vec3 lightPosition, glm::vec3 lightDirection, glm::vec3 lightUp, 
            float near_plane, float far_plane, bool directionalLight,
            glm::vec3 lightColor, GLfloat k_ambient,
            GLfloat atten_constant, GLfloat atten_linear, GLfloat atten_quadratic)
{
    this->lightPosition = lightPosition;
    this->lightDirection = lightDirection;
    this->lightUp = lightUp;
    this->near_plane = near_plane;
    this->far_plane = far_plane;
    this->DirectionalLight = directionalLight;
    this->lightColor = lightColor;
    this->k_ambient = k_ambient;

    this->switched_on = true;

    this->atten_constant = atten_constant;
    this->atten_linear = atten_linear;
    this->atten_quadratic = atten_quadratic;
}

glm::mat4 LightObject::GetLightViewMatrix()
{
    return glm::lookAt(lightPosition, lightDirection, lightUp);
}

glm::mat4 LightObject::GetLightProjectionMatrix(GLfloat shadowWidth, GLfloat shadowHeight)
{   
    
    if (DirectionalLight) {
        // Use orthographic projection for directional lights
        return glm::ortho(orth_left, orth_right, orth_bottom, orth_top, near_plane, far_plane);
    }
    else {
        return glm::perspective(glm::radians(45.0f), (GLfloat) shadowWidth / (GLfloat) shadowHeight, near_plane, far_plane);
    }
}

void LightObject::On()
{
    this->switched_on = true;
}

void LightObject::Off()
{
    this->switched_on = false;
}

bool LightObject::isOn()
{
    return this->switched_on;
}