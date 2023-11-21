
#include "Animations.hpp"

/**
 * Some basic useful functions
*/

// This function is from https://graphicscompendium.com/opengl/22-interpolation
glm::vec3 BasicMovement::lerp(glm::vec3 x, glm::vec3 y, float t) {
    return x * (1.f - t) + y * t;
}

float BasicMovement::lerp(float x, float y, float t)
{
    return x * (1.f - t) + y * t;
}

float BasicMovement::normalise(float n, float min, float max)
{
    // Assume max > min
    return (n - min) / (max - min);
}


/**
 * Toaster toast popping animation
 * 
 * TODO: Can probably make this nicer without a bunch of terrible ifs 
 * (some sorta index and move that along each time we pass a timestamp maybe?)
*/
ToastPop::ToastPop()
{

}

void ToastPop::Initialise(glm::vec3 startPosition, glm::vec3 startRotation)
{
    this->startPosition = startPosition;
    this->startRotation = startRotation;
}


bool ToastPop::isRunning()
{
    return animationRunning;
}


bool ToastPop::Tick(ModelObject &toast, float deltaTime)
{   
    // If the animation isn't running, start it
    if (!animationRunning) 
    {
        animationRunning = true;
        this->currentPosition = startPosition;
        this->currentRotation = startRotation;
    }

    // Move the toast
    t += animationSpeed * deltaTime;

    bool aniRun = this->ToastMov(t);
    toast.Position = this->currentPosition;
    toast.Rotation = this->currentRotation;

    // Stop animation! 
    if (aniRun == false) {
        this->animationRunning = false;
        this->t = 0.0;
    }

    return animationRunning;
}

bool ToastPop::ToastMov(float t)
{   
    vec3 downPos = vec3(startPosition.x, startPosition.y - 0.15, startPosition.z);
    vec3 topPos = vec3(startPosition.x, startPosition.y + 1.3, startPosition.z);
    vec3 bouncePos = vec3(startPosition.x, startPosition.y - 0.08, startPosition.z);

    vec3 endPos = vec3(-3.470, 2.20, -3.055);
    vec3 endPosRev = vec3(-3.328, 2.20, -3.055);

    vec3 endRot = vec3(startRotation.x + 3.275, startRotation.y - 0.192, startRotation.z);
    vec3 endRotRev = vec3(startRotation.x -3.103, startRotation.y - 0.2, startRotation.z);

    // These values should be monotonic
    float ts[7] = {0.0, 1.0, 3, 3.4, 3.8, 4.2, 4.45};

    if (t < ts[0]) {
        this->currentPosition = startPosition;
    }
    else if (t < ts[1]) {
        this->currentPosition = BasicMovement::lerp(startPosition, downPos, t);
    }
    else if (t < ts[2]) {
        this->currentPosition = downPos;
    }
    else if (t <= ts[3]) {
        this->currentPosition = BasicMovement::lerp(downPos, topPos, BasicMovement::normalise(t, ts[2], ts[3]));
    }
    else if (t <= ts[4]) {
        // Two different ways of spinning toast
        if(this->reverseSpin) {
            this->currentRotation = BasicMovement::lerp(startRotation, endRotRev, BasicMovement::normalise(t, ts[3], ts[4]));
        } else {
            this->currentRotation = BasicMovement::lerp(startRotation, endRot, BasicMovement::normalise(t, ts[3], ts[4]));
        }  
    }
    else if (t <= ts[5]) {
        this->currentPosition = BasicMovement::lerp(topPos, bouncePos, BasicMovement::normalise(t, ts[4], ts[5]));
    }
    else if (t <= ts[6]) {
        if(this->reverseSpin) {
            this->currentPosition = BasicMovement::lerp(bouncePos, endPosRev, BasicMovement::normalise(t, ts[5], ts[6]));
        } else {
            this->currentPosition = BasicMovement::lerp(bouncePos, endPos, BasicMovement::normalise(t, ts[5], ts[6]));
        }
    }
    else {
        if(this->reverseSpin) {
            this->currentPosition = endPosRev;
        } else {
            this->currentPosition = endPos;
        }
        return false; // Now done with the animation
    }
    return true;
}


