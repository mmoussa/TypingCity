#ifndef GAME_H_
#define GAME_H_

#include "GLSH.h"
#include <memory>

/*
Midterm (Option A - Pickups)
Name: Mohammad Moussa
ID: 991407852
*/

class Game : public glsh::App
{
    // shaders
    GLuint                  mUColorProgram;
    GLuint                  mVColorProgram;
    GLuint                  mUColorDirLightProgram;
    GLuint                  mVColorDirLightProgram;

    // meshes
    glsh::Mesh*             mCubeMesh;
	glsh::Mesh*				mTrackMesh;
	std::list<std::shared_ptr<glsh::Mesh>>	mTrackMeshes;
	std::list<std::shared_ptr<glsh::Mesh>> mPickupMeshes;
	float					mCubeWidth;

    // projection stuff
    float                   mCamFOV;            // field of view (in radians)
    float                   mCamAspect;         // screen aspect ratio (width/height)
    float                   mCamNear;           // distance from camera to near clipping plane
    float                   mCamFar;            // distance from camera to far clipping plane

    // camera stuff
    glm::vec3               mCamPos;
    float                   mCamYaw;
    float                   mCamPitch;

    // camera local axes
    glm::vec3               mCamForward;
    glm::vec3               mCamUp;
    glm::vec3               mCamRight;

    void                    updateCameraAxes();


    // graphics config
    bool                    mUseLighting        = false;
    bool                    mUseVertexColors    = true;
    bool                    mUseDepthTest       = true;
    bool                    mUseCulling         = true;

    enum AxesMode { AXES_NONE, AXES_GRID, AXES_PLANE };

    AxesMode                mAxesMode           = AXES_GRID;

    glsh::Mesh*             mActiveMesh         = NULL;

public:
                            Game();
                            ~Game();

    bool                    initialize(int w, int h)    override;
    void                    shutdown()                  override;
    void                    resize(int w, int h)        override;
    void                    draw()                      override;
    void                    update(float dt)            override;
	/*int						collision();
	void					resetGame();
	void					generateTrack();*/
};


#endif
