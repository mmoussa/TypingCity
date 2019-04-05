#include "Game.h"
#include <glm/gtx/perpendicular.hpp>
#include <GLSH_Util.h>
#include <GLSH_Prefabs.h>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>


const int font = (int)GLUT_BITMAP_9_BY_15;
std::string mText = "Hello, World!";


/*
Final
Name: Mohammad Moussa
ID: 991407852
*/


void renderBitmapString(float x, float y, float z, void *font, const char *string) {
	const char *c;
	//glRasterPos3d(x, y, z);
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}


Game::Game() 
    : mUColorProgram(0)
    , mVColorProgram(0)
    , mCubeMesh(NULL)
	, mTrackMesh(NULL)
    , mCamFOV(0)
    , mCamAspect(0)
    , mCamNear(0)
    , mCamFar(0)
    , mCamYaw(0)
    , mCamPitch(0)
{
}

Game::~Game()
{
}

bool Game::initialize(int w, int h)
{
	// build shader programs
	mUColorProgram = glsh::BuildShaderProgram("shaders/ucolor-vs.glsl", "shaders/ucolor-fs.glsl");
    mVColorProgram = glsh::BuildShaderProgram("shaders/vcolor-vs.glsl", "shaders/vcolor-fs.glsl");
    mUColorDirLightProgram = glsh::BuildShaderProgram("shaders/ucolor-DirLight-vs.glsl", "shaders/ucolor-DirLight-fs.glsl");
    mVColorDirLightProgram = glsh::BuildShaderProgram("shaders/vcolor-DirLight-vs.glsl", "shaders/vcolor-DirLight-fs.glsl");

	// set clear color
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //
    // create cube mesh
    //

	glm::mat4 cubeMatrix = glm::mat4(1.f);
	cubeMatrix = glm::scale(cubeMatrix, glm::vec3(1.f, 1.f, 1.f));
	mCubeMesh = glsh::CreateSolidCube(mCubeWidth, cubeMatrix);

	//draw track
	//generateTrack();



    //
    // set active mesh
    //

    mActiveMesh = mCubeMesh;

    //
    // initialize camera
    //

    mCamPos = glm::vec3(0.0f, 3.f, 5.f);
    mCamFOV = glm::radians(90.0f);
    mCamYaw = 0.f;
    mCamPitch = 0.f;

    updateCameraAxes();

    //
    // dump initial graphics config
    //
    std::cout << "========================================" << std::endl;
    std::cout << "Vertex colors:  " << (mUseVertexColors ? "on " : "off") << " (press V to toggle)" << std::endl;
    std::cout << "3D lighting:    " << (mUseLighting ? "on " : "off") << " (press L to toggle)" << std::endl;
    std::cout << "Depth test:     " << (mUseDepthTest ? "on " : "off") << " (press T to toggle)" << std::endl;
    std::cout << "Culling:        " << (mUseCulling ? "on " : "off") << " (press U to toggle)" << std::endl;

	

    return true;
}

void Game::shutdown()
{
    delete mCubeMesh;
	delete mTrackMesh;
	mTrackMeshes.clear();
	mPickupMeshes.clear();

	glUseProgram(0);
	glDeleteProgram(mUColorProgram);
    glDeleteProgram(mVColorProgram);
	glDeleteProgram(mUColorDirLightProgram);
    glDeleteProgram(mVColorDirLightProgram);
}

void Game::resize(int w, int h)
{
    // tell OpenGL to use entire window
    glViewport(0, 0, w, h);
}

void RenderText() {

	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	//glLoadIdentity();
	gluOrtho2D(0.0, 800, 0.0, 600);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//glLoadIdentity();
	glRasterPos2i(100, 100);

	std::string s = mText;
	void * font = GLUT_BITMAP_TIMES_ROMAN_24;

	//renderBitmapString(100, 100, 100, GLUT_BITMAP_HELVETICA_18, s.c_str());

	for (std::string::iterator i = s.begin(); i != s.end(); ++i) {

		char c = *i;
		glColor3f(1.0, 1.0, 1.0);
		glutBitmapCharacter(font, c);
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

//const char* mText = "FUCK!";

void Game::draw()
{
    // clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//drawText();
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	//glClear(GL_DEPTH_BUFFER_BIT);

	/*glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();*/

	
	//gluOrtho2D(0.0, 800, 0.0, 600);
	////glPushMatrix();
	//
	//glColor3d(1.0, 0.0, 0.0);
	//renderBitmapString(100, 100, 100, GLUT_BITMAP_HELVETICA_18, mText);
	//glPopMatrix();
	
	/*glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();*/

	
	/*glPushMatrix();

	gluOrtho2D(0.0, 800, 0.0, 600);
	glColor3d(1.0, 0.0, 0.0);
	renderBitmapString(100, 100, 100, GLUT_BITMAP_HELVETICA_18, mText.c_str());

	glPopMatrix();*/

	RenderText();

    // should usually enable depth test when drawing 3D stuff
    //if (mUseDepthTest) {
    //    glEnable(GL_DEPTH_TEST);
    //} else {
    //    glDisable(GL_DEPTH_TEST);
    //}

    //// enable back face culling for efficiency
    //if (mUseCulling) {
    //    glEnable(GL_CULL_FACE);
    //} else {
    //    glDisable(GL_CULL_FACE);
    //}

    //
    // compute perspective projection matrix
    //

    float camFOV = mCamFOV;
    float camAspect = getWindow()->getWidth() / (float)getWindow()->getHeight();
    float camNear = 0.1f;
    float camFar = 100.0f;

    glm::mat4 projMatrix = glm::perspective(camFOV, camAspect, camNear, camFar);

    //
    // compute viewing matrix
    //

    glm::vec3 camPos = mCamPos;
    glm::vec3 camTarget = camPos + mCamForward;
    glm::vec3 camUp = mCamUp;

    glm::mat4 viewMatrix = glm::lookAt(camPos, camTarget, camUp);

    //
    // draw active entity mesh
    //

    // compute transform
	glm::mat4 modelMatrix = glm::mat4(1.f);
	/*glm::quat orientation = glsh::CreateQuaternion(mObjYaw, glm::vec3(0.f, 1.f, 0.f));
	mObjForward = orientation * glm::vec3(0.f, 0.f, -1.f);
	modelMatrix = glm::translate(modelMatrix, mObjPos);
	modelMatrix = glm::rotate(modelMatrix, mObjYaw, glm::vec3(0.f, 1.f, 0.f))*/;
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.25f, 1.f));

	//if (mObjPos.x > 6.f || mObjPos.x < -6.f) {//TODO: store values in variables
	//	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.f, 0.f, 0.f));
	//	mControlsEnabled = false;
	//}
	
    glm::mat4 modelviewMatrix = viewMatrix * modelMatrix;

    // choose shader and parameters depending on graphics settings
    if (mUseLighting) {

        // light info
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
        glm::vec3 lightDir(1.0f, 2.0f, 3.0f);           // direction to light in world space
        lightDir = glm::mat3(viewMatrix) * lightDir;    // direction to light in camera space
        lightDir = glm::normalize(lightDir);            // normalized for sanity

        // normal matrix
        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelviewMatrix)));

        if (mUseVertexColors) {
            glUseProgram(mVColorDirLightProgram);
            glsh::SetShaderUniform("u_ProjectionMatrix", projMatrix);
            glsh::SetShaderUniform("u_ModelviewMatrix", modelviewMatrix);
            glsh::SetShaderUniform("u_NormalMatrix", normalMatrix);
            glsh::SetShaderUniform("u_LightColor", lightColor);
            glsh::SetShaderUniform("u_DirToLight", lightDir);
        } else {
            glUseProgram(mUColorDirLightProgram);
            glsh::SetShaderUniform("u_ProjectionMatrix", projMatrix);
            glsh::SetShaderUniform("u_ModelviewMatrix", modelviewMatrix);
            glsh::SetShaderUniform("u_NormalMatrix", normalMatrix);
            glsh::SetShaderUniform("u_LightColor", lightColor);
            glsh::SetShaderUniform("u_DirToLight", lightDir);
            glsh::SetShaderUniform("u_Color", glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
        }

    } else {

        // not using 3D lighting

        if (mUseVertexColors) {
            glUseProgram(mVColorProgram);
            glsh::SetShaderUniform("u_ProjectionMatrix", projMatrix);
            glsh::SetShaderUniform("u_ModelviewMatrix", viewMatrix * modelMatrix);
        } else {
            glUseProgram(mUColorProgram);
            glsh::SetShaderUniform("u_ProjectionMatrix", projMatrix);
            glsh::SetShaderUniform("u_ModelviewMatrix", viewMatrix * modelMatrix);
            glsh::SetShaderUniform("u_Color", glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
        }
    }

	
    mActiveMesh->draw();



	////draw pickups when player approaches some location
	//if (mObjPos.z < (-mTrackLength)*mNumTrackBlocks+mTrackLength/8) {
	//	mNumTrackBlocks = mNumTrackBlocks + 1.f;
	//	
	//	//draw pickups
	//	//pickups
	//	glm::mat4 pickupTransform = glm::mat4(1.f);
	//	float randX = glsh::Random(-4.f, 4.f);
	//	mPickupPos = glm::vec3(randX, mObjPos.y, mObjPos.z - (mTrackLength*0.8));
	//	mPickupLocs.push_back(mPickupPos);
	//	pickupTransform = glm::translate(pickupTransform, mPickupPos);
	//	pickupTransform = glm::scale(pickupTransform, glm::vec3(.25f, .25f, .25f));
	//	mPickupMeshes.push_back(std::shared_ptr<glsh::Mesh>(glsh::CreateSolidCube(5.f, pickupTransform)));
	//	
	//}
	

	//draw stuff
	//glUseProgram(mUColorProgram);
	glsh::SetShaderUniform("u_ProjectionMatrix", projMatrix);
	glsh::SetShaderUniform("u_ModelviewMatrix", viewMatrix);
	//glsh::SetShaderUniform("u_Color", glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

	for (std::shared_ptr<glsh::Mesh> trackMesh : mTrackMeshes) {
		trackMesh->draw();
	}
	for (std::shared_ptr<glsh::Mesh> pickup : mPickupMeshes) {
		pickup->draw();
	}

	


}

//int Game::collision() {
//	int i = 0;
//	int collision = 0;
//	auto iter = mPickupMeshes.begin();
//	for (glm::vec3 pos : mPickupLocs) {
//		
//		if (mObjPos.z + mCubeWidth / 2 < pos.z - 1.5f);
//		else if (mObjPos.z + mCubeWidth / 2 > pos.z + 1.5f);
//		else if (mObjPos.x + mCubeWidth / 2 < pos.x - 1.5f);
//		else if (mObjPos.x + mCubeWidth / 2 > pos.x + 1.5f);
//		else {
//			collision = 1;
//			mPickupLocs.remove(pos);
//			mPickupMeshes.erase(iter);
//			return collision;
//		}
//		i++;
//		std::advance(iter, 1);
//		
//	}
//	return collision;
//
//}

//void Game::generateTrack() {
//	//generate track vertices
//	mTrackLeft = glsh::Random(-5.f, -3.f);
//	mTrackRight = glsh::Random(3.f, 5.f);
//
//	//generate track
//	glsh::VPNC frontRight;
//	glsh::VPNC frontLeft;
//	float currSegment = 1.f;
//	//first segment
//	std::vector<glsh::VPNC> trackVerts;
//	std::vector<unsigned short> trackIndices;
//	frontRight = glsh::VPNC(mTrackRight, -1.f, -mTrackLength * currSegment, 0.f, 1.f, 0.f, 0.5f, 0.5f, 0.5f, 1.f);//front-right
//	trackVerts.push_back(frontRight);
//	frontLeft = (glsh::VPNC(mTrackLeft, -1.0f, -mTrackLength * currSegment, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f));//front-left
//	trackVerts.push_back(frontLeft);//front-left
//	trackVerts.push_back(glsh::VPNC(mTrackRight, -1.0f, (-mTrackLength * currSegment) + mTrackLength, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f));
//	trackVerts.push_back(glsh::VPNC(mTrackLeft, -1.0f, (-mTrackLength * currSegment) + mTrackLength, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f));
//	trackIndices.push_back(0);  trackIndices.push_back(1);  trackIndices.push_back(2);
//	trackIndices.push_back(1);  trackIndices.push_back(3);  trackIndices.push_back(2);
//	mTrackMeshes.push_back(std::shared_ptr<glsh::Mesh>(glsh::CreateMesh(GL_TRIANGLES, trackVerts, trackIndices)));
//	currSegment++;
//
//	for (int i = 0; i < 500; i++) {
//
//		float prevRight = mTrackRight;
//		float prevLeft = mTrackLeft;
//		mTrackLeft = glsh::Random(-8.f, -3.f);
//		mTrackRight = glsh::Random(3.f, 8.f);
//
//		std::vector<glsh::VPNC> trackVerts;
//		std::vector<unsigned short> trackIndices;
//		frontRight = glsh::VPNC(mTrackRight, -1.f, -mTrackLength * currSegment, 0.f, 1.f, 0.f, 0.5f, 0.5f, 0.5f, 1.f);//front-right
//		trackVerts.push_back(frontRight);
//		frontLeft = (glsh::VPNC(mTrackLeft, -1.0f, -mTrackLength * currSegment, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f));//front-left
//		trackVerts.push_back(frontLeft);//front-left
//		trackVerts.push_back(glsh::VPNC(prevRight, -1.0f, (-mTrackLength * currSegment) + mTrackLength, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f));
//		trackVerts.push_back(glsh::VPNC(prevLeft, -1.0f, (-mTrackLength * currSegment) + mTrackLength, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f));
//		trackIndices.push_back(0);  trackIndices.push_back(1);  trackIndices.push_back(2);
//		trackIndices.push_back(1);  trackIndices.push_back(3);  trackIndices.push_back(2);
//		mTrackMeshes.push_back(std::shared_ptr<glsh::Mesh>(glsh::CreateMesh(GL_TRIANGLES, trackVerts, trackIndices)));
//		currSegment++;
//	}
//}
//void Game::resetGame() {
//	// reset object transform
//	mScore = 0.f;
//	mNumTrackBlocks = 1.f;
//	mTrackMeshes.clear();
//	mPickupMeshes.clear();
//	mPickupLocs.clear();
//	mObjYaw = 0;
//	mObjPos = glm::vec3(0.f, 0.f, 0.f);
//	mCamPos = glm::vec3(0.0f, 3.f, 5.f); //TODO: store default values in a variable
//	mControlsEnabled = true;
//	generateTrack();
//}

void Game::update(float dt)
{
	// get pointers to input device states
	const glsh::Keyboard* kb = getKeyboard();
	const glsh::Mouse* mouse = getMouse();

	//check collision
	//if (Game::collision()) {
	//	//mControlsEnabled = false;
	//	//mScore++;
	//	
	//	//std::cout << "Score: " << mScore << std::endl;
	//	
	//}

	// quit if Escape key was pressed
	if (kb->keyPressed(glsh::KC_ESCAPE)) {
		quit();
	}

    //
    // object rotation controls
    //

   /* if (kb->keyPressed(glsh::KC_R)) {
		resetGame();
        
    }*/

    float objRotSpeed = glsh::PI;       // radians/second
	//float objTranslateSpeed = std::max(8.f, std::min(mScore, 50.f));

	if (true) {
		/*if (kb->isKeyDown(glsh::KC_RIGHT)) {
			mObjYaw -= objRotSpeed * dt;
		}
		if (kb->isKeyDown(glsh::KC_LEFT)) {
			mObjYaw += objRotSpeed * dt;
		}
		if (kb->isKeyDown(glsh::KC_DOWN)) {
			mObjPos -= objTranslateSpeed * dt * mObjForward;
			mCamPos -= objTranslateSpeed * dt * mObjForward;
		}
		if (kb->isKeyDown(glsh::KC_UP)) {
			mObjPos += objTranslateSpeed * dt * mObjForward;
			mCamPos += objTranslateSpeed * dt * mObjForward;

		}*/

		if (kb->keyPressed(glsh::KC_A)) {
			mText.append("A");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_B)) {
			mText.append("B");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_C)) {
			mText.append("C");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_D)) {
			mText.append("D");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_E)) {
			mText.append("E");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_F)) {
			mText.append("F");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_G)) {
			mText.append("G");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_H)) {
			mText.append("H");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_I)) {
			mText.append("I");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_J)) {
			mText.append("J");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_K)) {
			mText.append("K");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_L)) {
			mText.append("L");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_M)) {
			mText.append("M");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_N)) {
			mText.append("N");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_O)) {
			mText.append("O");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_P)) {
			mText.append("P");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_Q)) {
			mText.append("Q");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_R)) {
			mText.append("R");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_S)) {
			mText.append("S");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_T)) {
			mText.append("T");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_U)) {
			mText.append("U");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_V)) {
			mText.append("V");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_W)) {
			mText.append("W");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_X)) {
			mText.append("X");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_Y)) {
			mText.append("Y");
			std::cout << mText << std::endl;
		}
		else if (kb->keyPressed(glsh::KC_Z)) {
			mText.append("Z");
			std::cout << mText << std::endl;
		}

		

	}
    


    //
    // camera controls
    //

    float camMoveSpeed = 4;
    /*if (kb->isKeyDown(glsh::KC_SHIFT)) {
        camMoveSpeed *= 5;
    }

    if (kb->isKeyDown(glsh::KC_W)) {
        mCamPos += camMoveSpeed * dt * mCamForward;
    }
    if (kb->isKeyDown(glsh::KC_S)) {
        mCamPos -= camMoveSpeed * dt * mCamForward;
    }
    if (kb->isKeyDown(glsh::KC_D)) {
        mCamPos += camMoveSpeed * dt * mCamRight;
    }
    if (kb->isKeyDown(glsh::KC_A)) {
        mCamPos -= camMoveSpeed * dt * mCamRight;
    }
    if (kb->isKeyDown(glsh::KC_E)) {
        mCamPos += camMoveSpeed * dt * mCamUp;
    }
    if (kb->isKeyDown(glsh::KC_C)) {
        mCamPos -= camMoveSpeed * dt * mCamUp;
    }*/

    float mouseSensitivity = glsh::PI / 1000;        // rotation speed in radians/pixel

    if (mouse->isDragging(glsh::MOUSE_BUTTON_LEFT)) {

        int dx = mouse->getDeltaX();
        int dy = mouse->getDeltaY();

        mCamYaw -= dx * mouseSensitivity;
        mCamPitch -= dy * mouseSensitivity;
    }

    int wd = mouse->getWheelDelta();
    if (wd != 0) {
        mCamFOV -= wd * glm::radians(10.0f);
        float minFOV = glm::radians(20.0f);
        float maxFOV = glm::radians(120.0f);
        if (mCamFOV < minFOV) {
            mCamFOV = minFOV;
        } else if (mCamFOV > maxFOV) {
            mCamFOV = maxFOV;
        }
    }

    updateCameraAxes();

    //
    // graphics settings controls
    //

    bool dumpConfig = false;

    /*if (kb->keyPressed(glsh::KC_L)) {
        mUseLighting = !mUseLighting;
        dumpConfig = true;
    }
    if (kb->keyPressed(glsh::KC_V)) {
        mUseVertexColors = !mUseVertexColors;
        dumpConfig = true;
    }
    if (kb->keyPressed(glsh::KC_T)) {
        mUseDepthTest = !mUseDepthTest;
        dumpConfig = true;
    }
    if (kb->keyPressed(glsh::KC_U)) {
        mUseCulling = !mUseCulling;
        dumpConfig = true;
    }*/

    if (dumpConfig) {
        std::cout << "========================================" << std::endl;
        std::cout << "Vertex colors:  " << (mUseVertexColors ? "on " : "off") << " (press V to toggle)" << std::endl;
        std::cout << "3D lighting:    " << (mUseLighting ? "on " : "off") << " (press L to toggle)" << std::endl;
        std::cout << "Depth test:     " << (mUseDepthTest ? "on " : "off") << " (press T to toggle)" << std::endl;
        std::cout << "Culling:        " << (mUseCulling ? "on " : "off") << " (press U to toggle)" << std::endl;
    }

    // change active mesh
   

    // change axes mode
    if (kb->keyPressed(glsh::KC_X)) {
        if (mAxesMode == AXES_NONE) {
            mAxesMode = AXES_GRID;
        } else if (mAxesMode == AXES_GRID) {
            mAxesMode = AXES_PLANE;
        } else {
            mAxesMode = AXES_NONE;
        }
    }
}

void Game::updateCameraAxes()
{
    // keep yaw angle in standard range
    if (mCamYaw < -glsh::PI) {
        mCamYaw += glsh::TWO_PI;
    } else if (mCamYaw >= glsh::PI) {
        mCamYaw -= glsh::TWO_PI;
    }

    // don't let pitch reach or exceed 90 degrees!
    float maxPitch = glm::radians(85.0f);
    float minPitch = -glm::radians(85.0f);
    if (mCamPitch < minPitch) {
        mCamPitch = minPitch;
    } else if (mCamPitch > maxPitch) {
        mCamPitch = maxPitch;
    }

    // express yaw as rotation about global y-axis
    glm::quat camYawQuat = glsh::CreateQuaternion(mCamYaw, glm::vec3(0.0f, 1.0f, 0.0f));

    // compute the rotated camera x-axis
    glm::vec3 camXAxis = camYawQuat * glm::vec3(1.0f, 0.0f, 0.0f);

    // express pitch as a rotation about local x-axis
    glm::quat camPitchQuat = glsh::CreateQuaternion(mCamPitch, camXAxis);


    // compute camera orientation (yaw about global y-axis followed by pitch about local x-axis)
    /*glm::quat camOrientation = camPitchQuat * camYawQuat;*/
	glm::quat camOrientation = camPitchQuat * camYawQuat;

    // compute camera local axes
    mCamForward = camOrientation * glm::vec3(0.0f, 0.0f, -1.0f);
	mCamUp = camOrientation * glm::vec3(0.0f, 1.0f, 0.0f);
    mCamRight = camOrientation * glm::vec3(1.0f, 0.0f, 0.0f);
}
