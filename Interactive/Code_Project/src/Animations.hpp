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

        void Start(ModelObject &toast);

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

class StorageJarMov
{

    public:

        float animationSpeed = 1.0;

        StorageJarMov();

        void Initialise(glm::vec3 startPosition_SJ, glm::vec3 startRotation_SJ, glm::vec3 startPosition_Lid, glm::vec3 startRotation_Lid);

        bool isRunning();

        void Start(ModelObject &storageJar, ModelObject &storageJarLid);

        bool Tick(ModelObject &storageJar, ModelObject &storageJarLid, float deltaTime);


    private:
        glm::vec3 startPosition_SJ;
        glm::vec3 startRotation_SJ;

        glm::vec3 startPosition_Lid;
        glm::vec3 startRotation_Lid;

        glm::vec3 currentPosition_SJ;
        glm::vec3 currentRotation_SJ;

        glm::vec3 currentPosition_Lid;
        glm::vec3 currentRotation_Lid;

        bool animationRunning = false;

        float t = 0.0;

        bool JarMov(float t);
        bool LidMov(float t);
};

class CabinDoorMove
{
    public:

        float animationSpeed = 1.0;
        
        bool reverseSpin = false;

        
        CabinDoorMove();

        void Initialise(glm::vec3 startPosition, glm::vec3 startRotation);


        bool isRunning();

        void Start(ModelObject &door);

        bool Tick(ModelObject &door, float deltaTime);


    private:
        glm::vec3 startPosition;
        glm::vec3 startRotation;

        glm::vec3 currentPosition;
        glm::vec3 currentRotation;

        bool animationRunning = false;
        bool isOpen = false;
        
        float t = 0.0;

        bool DoorMov(ModelObject &door, float t);
};

