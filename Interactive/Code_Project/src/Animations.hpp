/**
 * Some simple animations for objects
 * TODO: Think of a better way to organize this - Maybe an animation interface or something then we can call them in a standard way?
*/

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

#include "ModelObject.hpp"


class BasicMovement
{   
    // Some helpful functions for basic movements
    
    public:
        static glm::vec3 lerp(glm::vec3 x, glm::vec3 y, float t);

        static float lerp(float x, float y, float t);

        static float normalise(float n, float min, float max);
};


class ToastPop
{
    public:

        float animationSpeed = 1.0;
        
        bool reverseSpin = false;

        
        ToastPop();

        void Initialise(glm::vec3 startPosition, glm::vec3 startRotation);


        bool isRunning();

        bool Tick(ModelObject &toast, float deltaTime);


    private:
        glm::vec3 startPosition;
        glm::vec3 startRotation;

        glm::vec3 currentPosition;
        glm::vec3 currentRotation;

        bool animationRunning = false;

        float t = 0.0;

        bool ToastMov(float t);

};

