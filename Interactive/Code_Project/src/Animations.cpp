
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

void ToastPop::Start(ModelObject &toast)
{
    // If the animation isn't running, start it
    if (!animationRunning) 
    {
        this->animationRunning = true;
        this->currentPosition = startPosition;
        this->currentRotation = startRotation;
    }
}

bool ToastPop::Tick(ModelObject &toast, float deltaTime)
{   
    if (!animationRunning) {
        return animationRunning;
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
    vec3 topPos = vec3(startPosition.x, startPosition.y + 1.12, startPosition.z);
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


/**
 * Storage jar wobble animation
*/
StorageJarMov::StorageJarMov() {}

void StorageJarMov::Initialise(glm::vec3 startPosition_SJ, glm::vec3 startRotation_SJ, glm::vec3 startPosition_Lid, glm::vec3 startRotation_Lid)
{
    this->startPosition_SJ = startPosition_SJ;
    this->startRotation_SJ = startRotation_SJ;

    this->startPosition_Lid = startPosition_Lid;
    this->startRotation_Lid = startRotation_Lid;
}

bool StorageJarMov::isRunning()
{
    return animationRunning;
}

void StorageJarMov::Start(ModelObject &storageJar, ModelObject &storageJarLid)
{
    if (!animationRunning) {
        this->animationRunning = true;

        this->currentPosition_SJ = this->startPosition_SJ;
        this->currentRotation_SJ = this->startRotation_SJ;

        this->currentPosition_Lid = this->startPosition_Lid;
        this->currentRotation_Lid = this->startRotation_Lid;
    }
}

bool StorageJarMov::Tick(ModelObject &storageJar, ModelObject &storageJarLid, float deltaTime)
{
    if(!animationRunning) {
        return animationRunning;
    }

    t += animationSpeed * deltaTime;

    bool aniRunSJ = this->JarMov(t);
    storageJar.Position = this->currentPosition_SJ;
    storageJar.Rotation = this->currentRotation_SJ;

    bool aniRunLid = this->LidMov(t);
    storageJarLid.Position = this->currentPosition_Lid;
    storageJarLid.Rotation = this->currentRotation_Lid;
    
    if (aniRunSJ == false && aniRunLid == false) {
        this->animationRunning = false;
        this->t = 0.0;
    }

    return animationRunning;

}

bool StorageJarMov::JarMov(float t)
{   
    // Movements.. should put this in an array or something
    // Wobble
    vec3 p1 = startPosition_SJ + vec3{0.0, 0.03, 0.0};
    vec3 r1 = startRotation_SJ + vec3{0.250, 0.0, 0.0};

    vec3 p2 = startPosition_SJ;
    vec3 r2 = startRotation_SJ;

    vec3 p3 = startPosition_SJ + vec3{0.0, 0.03, 0.0};
    vec3 r3 = startRotation_SJ + vec3{-0.167, 0.0, -0.167};

    vec3 p4 = startPosition_SJ;
    vec3 r4 = startRotation_SJ;

    vec3 p5 = startPosition_SJ + vec3{0.0, 0.03, 0.0};
    vec3 r5 = startRotation_SJ + vec3{0.0, 0.25, -0.167};

    vec3 p6 = startPosition_SJ;
    vec3 r6 = startRotation_SJ;

    vec3 p7 = startPosition_SJ + vec3{0.0, 0.03, 0.0};
    vec3 r7 = startRotation_SJ + vec3{0.167, 0.0, 0.167};

    vec3 p8 = startPosition_SJ;
    vec3 r8 = startRotation_SJ;

    // Move back forth
    vec3 p9 = startPosition_SJ + vec3{0.0, 0.0, 0.005};

    vec3 p10 = startPosition_SJ + vec3{0.0, 0.0, 0.02};

    vec3 p11 = startPosition_SJ + vec3{0.070, 0.000, 0.080};

    vec3 p12 = startPosition_SJ + vec3{0.110, 0.000, -0.040};

    vec3 p13 = startPosition_SJ + vec3{0.010, 0.000, 0.130};

    vec3 p14 = startPosition_SJ;
    vec3 r14 = startRotation_SJ;

    // Upward
    vec3 p15 = startPosition_SJ + vec3{0.000, 0.400, 0.000};
    vec3 r15 = startRotation_SJ + vec3{0.000, -0.667, 0.000};

    vec3 p16 = startPosition_SJ;
    vec3 r16 = startRotation_SJ;

    vec3 p17 = startPosition_SJ + vec3{0.000, 0.05, 0.000};

    vec3 p18 = startPosition_SJ;

    // Times, monotonic
    float ts[19] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 
                    2.8, 3.2, 3.8, 4.0, 4.2};

    // Giant if
    if (t < ts[0]) {
        currentPosition_SJ = startPosition_SJ;
        currentRotation_SJ = startRotation_SJ;
    }
        else if (t <= ts[1]) {
        currentPosition_SJ = BasicMovement::lerp(startPosition_SJ, p1, BasicMovement::normalise(t, ts[0], ts[1]));
        currentRotation_SJ = BasicMovement::lerp(startRotation_SJ, r1, BasicMovement::normalise(t, ts[0], ts[1]));
    }
    else if (t <= ts[2]) {
        currentPosition_SJ = BasicMovement::lerp(p1, p2, BasicMovement::normalise(t, ts[1], ts[2]));
        currentRotation_SJ = BasicMovement::lerp(r1, r2, BasicMovement::normalise(t, ts[1], ts[2]));
    }
    else if (t <= ts[3]) {
        currentPosition_SJ = BasicMovement::lerp(p2, p3, BasicMovement::normalise(t, ts[2], ts[3]));
        currentRotation_SJ = BasicMovement::lerp(r2, r3, BasicMovement::normalise(t, ts[2], ts[3]));
    }
    else if (t <= ts[4]) {
        currentPosition_SJ = BasicMovement::lerp(p3, p4, BasicMovement::normalise(t, ts[3], ts[4]));
        currentRotation_SJ = BasicMovement::lerp(r3, r4, BasicMovement::normalise(t, ts[3], ts[4]));
    }
    else if (t <= ts[5]) {
        currentPosition_SJ = BasicMovement::lerp(p4, p5, BasicMovement::normalise(t, ts[4], ts[5]));
        currentRotation_SJ = BasicMovement::lerp(r4, r5, BasicMovement::normalise(t, ts[4], ts[5]));
    }
    else if (t <= ts[6]) {
        currentPosition_SJ = BasicMovement::lerp(p5, p6, BasicMovement::normalise(t, ts[5], ts[6]));
        currentRotation_SJ = BasicMovement::lerp(r5, r6, BasicMovement::normalise(t, ts[5], ts[6]));
    }
    else if (t <= ts[7]) {
        currentPosition_SJ = BasicMovement::lerp(p6, p7, BasicMovement::normalise(t, ts[6], ts[7]));
        currentRotation_SJ = BasicMovement::lerp(r6, r7, BasicMovement::normalise(t, ts[6], ts[7]));
    }
    else if (t <= ts[8]) {
        currentPosition_SJ = BasicMovement::lerp(p7, p8, BasicMovement::normalise(t, ts[7], ts[8]));
        currentRotation_SJ = BasicMovement::lerp(r7, r8, BasicMovement::normalise(t, ts[7], ts[8]));
    }
    else if (t <= ts[9]) {
        currentPosition_SJ = BasicMovement::lerp(p8, p9, BasicMovement::normalise(t, ts[8], ts[9]));
    }
    else if (t <= ts[10]) {
        currentPosition_SJ = BasicMovement::lerp(p9, p10, BasicMovement::normalise(t, ts[9], ts[10]));
    }
    else if (t <= ts[11]) {
        currentPosition_SJ = BasicMovement::lerp(p10, p11, BasicMovement::normalise(t, ts[10], ts[11]));
    }
    else if (t <= ts[12]) {
        currentPosition_SJ = BasicMovement::lerp(p11, p12, BasicMovement::normalise(t, ts[11], ts[12]));
    }
    else if (t <= ts[13]) {
        currentPosition_SJ = BasicMovement::lerp(p12, p13, BasicMovement::normalise(t, ts[12], ts[13]));
    }
    else if (t <= ts[14]) {
        currentPosition_SJ = BasicMovement::lerp(p13, p14, BasicMovement::normalise(t, ts[13], ts[14]));
    }
    else if (t <= ts[15]) {
        currentPosition_SJ = BasicMovement::lerp(p14, p15, BasicMovement::normalise(t, ts[14], ts[15]));
        currentRotation_SJ = BasicMovement::lerp(r14, r15, BasicMovement::normalise(t, ts[15], ts[16]));
    }
    else if (t <= ts[16]) {
        currentPosition_SJ = BasicMovement::lerp(p15, p16, BasicMovement::normalise(t, ts[15], ts[16]));
        currentRotation_SJ = BasicMovement::lerp(r15, r16, BasicMovement::normalise(t, ts[15], ts[16]));
    }
    else if (t <= ts[17]) {
        currentPosition_SJ = BasicMovement::lerp(p16, p17, BasicMovement::normalise(t, ts[16], ts[17]));
    }
    else if (t <= ts[18]) {
        currentPosition_SJ = BasicMovement::lerp(p17, p18, BasicMovement::normalise(t, ts[17], ts[18]));
    }
    else {
        currentPosition_SJ = p18;
        currentRotation_SJ = r16;
        return false;
    }

    return true;
}

bool StorageJarMov::LidMov(float t)
{
    // Movements.. should put this in an array or something
    // Wobble
    vec3 p1 = startPosition_Lid + vec3{0.003, -0.010, 0.124};
    vec3 r1 = startRotation_Lid + vec3{0.250, 0.0, 0.0};

    vec3 p2 = startPosition_Lid;
    vec3 r2 = startRotation_Lid;

    vec3 p3 = startPosition_Lid + vec3{0.077, 0.000, -0.045};
    vec3 r3 = startRotation_Lid + vec3{-0.167, 0.0, -0.167};

    vec3 p4 = startPosition_Lid;
    vec3 r4 = startRotation_Lid;

    vec3 p5 = startPosition_Lid + vec3{0.075, 0.000, 0.037};
    vec3 r5 = startRotation_Lid + vec3{0.0, 0.25, -0.167};

    vec3 p6 = startPosition_Lid;
    vec3 r6 = startRotation_Lid;

    vec3 p7 = startPosition_Lid + vec3{-0.073, 0.000, 0.047};
    vec3 r7 = startRotation_Lid + vec3{0.167, 0.0, 0.167};

    vec3 p8 = startPosition_Lid;
    vec3 r8 = startRotation_Lid;

    // Move back forth
    vec3 p9 = startPosition_Lid + vec3{0.0, 0.0, 0.005};

    vec3 p10 = startPosition_Lid + vec3{0.0, 0.0, 0.02};

    vec3 p11 = startPosition_Lid + vec3{0.070, 0.000, 0.080};

    vec3 p12 = startPosition_Lid + vec3{0.110, 0.000, -0.040};

    vec3 p13 = startPosition_Lid + vec3{0.010, 0.000, 0.130};

    vec3 p14 = startPosition_Lid;
    vec3 r14 = startRotation_Lid;

    // Upward
    vec3 p15 = startPosition_Lid + vec3{0.000, 0.5, 0.000};
    vec3 r15 = startRotation_Lid + vec3{0, 0.0, 0.000};

    vec3 p16 = startPosition_Lid + vec3{0.236, 1.095, -0.048};
    vec3 r16 = startRotation_Lid + vec3{3.5, 0.0, 0.000};

    // vec3 p17 = startPosition_Lid + vec3{0.658, -0.307, -0.133};
    //vec3 r17 = startRotation_Lid + vec3{11.001, 0.010, 0.000};

    vec3 p17 = vec3{-2.869, 1.820, 2.040};
    vec3 r17 = vec3{10.974, -0.465, 0.0};

    vec3 p18 = vec3{-2.868, 1.661, 2.106};
    vec3 r18 = vec3{12.568, -0.324, 0};


    // Times, monotonic
    float ts[19] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 
                    2.8, 3.3, 3.6, 4.3, 5.0};

    // Giant if
    if (t < ts[0]) {
        currentPosition_Lid = startPosition_Lid;
        currentRotation_Lid = startRotation_Lid;
    }
    else if (t <= ts[1]) {
        currentPosition_Lid = BasicMovement::lerp(startPosition_Lid, p1, BasicMovement::normalise(t, ts[0], ts[1]));
        currentRotation_Lid = BasicMovement::lerp(startRotation_Lid, r1, BasicMovement::normalise(t, ts[0], ts[1]));
    }
    else if (t <= ts[2]) {
        currentPosition_Lid = BasicMovement::lerp(p1, p2, BasicMovement::normalise(t, ts[1], ts[2]));
        currentRotation_Lid = BasicMovement::lerp(r1, r2, BasicMovement::normalise(t, ts[1], ts[2]));
    }
    else if (t <= ts[3]) {
        currentPosition_Lid = BasicMovement::lerp(p2, p3, BasicMovement::normalise(t, ts[2], ts[3]));
        currentRotation_Lid = BasicMovement::lerp(r2, r3, BasicMovement::normalise(t, ts[2], ts[3]));
    }
    else if (t <= ts[4]) {
        currentPosition_Lid = BasicMovement::lerp(p3, p4, BasicMovement::normalise(t, ts[3], ts[4]));
        currentRotation_Lid = BasicMovement::lerp(r3, r4, BasicMovement::normalise(t, ts[3], ts[4]));
    }
    else if (t <= ts[5]) {
        currentPosition_Lid = BasicMovement::lerp(p4, p5, BasicMovement::normalise(t, ts[4], ts[5]));
        currentRotation_Lid = BasicMovement::lerp(r4, r5, BasicMovement::normalise(t, ts[4], ts[5]));
    }
    else if (t <= ts[6]) {
        currentPosition_Lid = BasicMovement::lerp(p5, p6, BasicMovement::normalise(t, ts[5], ts[6]));
        currentRotation_Lid = BasicMovement::lerp(r5, r6, BasicMovement::normalise(t, ts[5], ts[6]));
    }
    else if (t <= ts[7]) {
        currentPosition_Lid = BasicMovement::lerp(p6, p7, BasicMovement::normalise(t, ts[6], ts[7]));
        currentRotation_Lid = BasicMovement::lerp(r6, r7, BasicMovement::normalise(t, ts[6], ts[7]));
    }
    else if (t <= ts[8]) {
        currentPosition_Lid = BasicMovement::lerp(p7, p8, BasicMovement::normalise(t, ts[7], ts[8]));
        currentRotation_Lid = BasicMovement::lerp(r7, r8, BasicMovement::normalise(t, ts[7], ts[8]));
    }
    else if (t <= ts[9]) {
        currentPosition_Lid = BasicMovement::lerp(p8, p9, BasicMovement::normalise(t, ts[8], ts[9]));
    }
    else if (t <= ts[10]) {
        currentPosition_Lid = BasicMovement::lerp(p9, p10, BasicMovement::normalise(t, ts[9], ts[10]));
    }
    else if (t <= ts[11]) {
        currentPosition_Lid = BasicMovement::lerp(p10, p11, BasicMovement::normalise(t, ts[10], ts[11]));
    }
    else if (t <= ts[12]) {
        currentPosition_Lid = BasicMovement::lerp(p11, p12, BasicMovement::normalise(t, ts[11], ts[12]));
    }
    else if (t <= ts[13]) {
        currentPosition_Lid = BasicMovement::lerp(p12, p13, BasicMovement::normalise(t, ts[12], ts[13]));
    }
    else if (t <= ts[14]) {
        currentPosition_Lid = BasicMovement::lerp(p13, p14, BasicMovement::normalise(t, ts[13], ts[14]));
    }
    else if (t <= ts[15]) { // Upward
        currentPosition_Lid = BasicMovement::lerp(p14, p15, BasicMovement::normalise(t, ts[14], ts[15]));
        currentRotation_Lid = BasicMovement::lerp(r14, r15, BasicMovement::normalise(t, ts[14], ts[15]));
    }
    //
    else if (t <= ts[16]) { // Upward
        currentPosition_Lid = BasicMovement::lerp(p15, p16, BasicMovement::normalise(t, ts[15], ts[16]));
        currentRotation_Lid = BasicMovement::lerp(r15, r16, BasicMovement::normalise(t, ts[15], ts[16]));
    }
    else if (t <= ts[17]) { // Upward
        currentPosition_Lid = BasicMovement::lerp(p16, p17, BasicMovement::normalise(t, ts[16], ts[17]));
        currentRotation_Lid = BasicMovement::lerp(r16, r17, BasicMovement::normalise(t, ts[16], ts[17]));
    }
    else if (t <= ts[18]) { // Upward
        currentPosition_Lid = BasicMovement::lerp(p17, p18, BasicMovement::normalise(t, ts[17], ts[18]));
        currentRotation_Lid = BasicMovement::lerp(r17, r18, BasicMovement::normalise(t, ts[17], ts[18]));
    }
    else {
        //currentPosition_Lid = currentPosition_Lid;
        //currentRotation_Lid = currentRotation_Lid;
        return false;
    }
    return true;
}


CabinDoorMove::CabinDoorMove()
{

}

void CabinDoorMove::Initialise(glm::vec3 startPosition, glm::vec3 startRotation)
{
    this->startPosition = startPosition;
    this->startRotation = startRotation;
    this->currentPosition = startPosition;
    this->currentRotation = startRotation;
}
bool CabinDoorMove::isRunning()
{
    return animationRunning;
}

void CabinDoorMove::Start(ModelObject &door)
{
    // If the animation isn't running, start it
    if (!animationRunning) 
    {
        this->animationRunning = true;
        this->startPosition = currentPosition;
        this->startRotation = currentRotation;
    }
}

bool CabinDoorMove::Tick(ModelObject &door, float deltaTime)
{   
    if (!animationRunning) {
        return animationRunning;
    }
    
    // Move the door
    t += animationSpeed * deltaTime;

    bool aniRun = this->DoorMov(door, t);
    door.Position = this->currentPosition;
    door.Rotation = this->currentRotation;

    // Stop animation! 
    if (aniRun == false) {
        this->animationRunning = false;
        this->t = 0.0;
    }

    return animationRunning;
}

bool CabinDoorMove::DoorMov(ModelObject &door, float t)
{   
    vec3 targetRot1 = vec3(startRotation.x, isOpen ? startRotation.y + 0.5 : startRotation.y - 0.5, startRotation.z);

    vec3 targetRot2 = vec3(startRotation.x, isOpen ? startRotation.y + 1 : startRotation.y - 1, startRotation.z);

    vec3 targetRot3 = vec3(startRotation.x, isOpen ? startRotation.y + 1.5 : startRotation.y - 1.5, startRotation.z);

    vec3 targetRot4 = vec3(startRotation.x, isOpen ? door.DefaultRotation.y : startRotation.y - 2, startRotation.z);

    float ts[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};

    if (t < ts[0]) {
        this->currentRotation = startRotation;
    }
    else if (t <= ts[1]) {
        this->currentRotation = BasicMovement::lerp(startRotation, targetRot1, BasicMovement::normalise(t, ts[0], ts[1]));
    }
    else if (t <= ts[2]) {
        this->currentRotation = BasicMovement::lerp(targetRot1, targetRot2, BasicMovement::normalise(t, ts[1], ts[2]));
    }
    else if (t <= ts[3]) {
        this->currentRotation = BasicMovement::lerp(targetRot2, targetRot3, BasicMovement::normalise(t, ts[2], ts[3]));
    }
    else if (t <= ts[4]) {
        this->currentRotation = BasicMovement::lerp(targetRot3, targetRot4, BasicMovement::normalise(t, ts[3], ts[4]));
    } else {
        isOpen = isOpen ? false : true;
        return false;
    }
    
    return true;
}