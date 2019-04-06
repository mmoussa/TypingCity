#include "MainGame.h"

/*
Author: Mohammad Moussa - 991407852
3D Graphics & Gamification
Final Gamification Project

Project Description:
The game is called Typing City. It is a city building game using typing.
A random word is generated, and the user can start typing. If the user types the
word correctly, they gain a point, and are able to start building.

There are different building components that the user can choose from e.g. roof,
door, window, etc.

The project demonstrates gamification by:
	- encouraging the user to improve their typing skills
	- visually showing progress through progress bar and the building components
	- adjusting challenge difficulty with improving skills


*/


MainGame::MainGame()
{

}


MainGame::~MainGame()
{
}

bool MainGame::initialize(int w, int h)
{

	mInputText = "";

	//load word list and get a word
	initWordList();
	getNextWord();

	//setup game
	mCurrentPoints = 0;
	mMaxPoints = 5;
	mLevel = 1;
	mLevelText = "Level: " + std::to_string(mLevel);
	mLevelUpText = "";

	mNumBoxes = 0;
	mBoxDim = 10.f;
	mDoorWidth = 1.f;
	mDoorHeight = 5.f;

	createWorld();

	//background color
	glClearColor(0.713, 0.988, 0.988, 1);

	return true;
}

void MainGame::shutdown()
{
}

void MainGame::resize(int w, int h)
{
}

void MainGame::draw()
{

	//Clear
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_ACCUM_BUFFER_BIT);
	glClear(GL_STENCIL_BUFFER_BIT);



	//draw text
	//draw word
	glColor3f(1, 1, 1);
	drawText(mWord, 25, 50);
	//draw input text
	glColor3f(1, 1, 1);
	drawText(mInputText, 25, 100);
	//draw level
	glColor3f(1, 1, 1);
	drawText(mLevelText, 25, 550);
	//draw level up text
	drawText(mLevelUpText, 275, 550);


	//draw huds
	//draw level hud
	glColor4f(0.349, 0.019, 1, 0.5f);
	drawHudElement(20, 540, 125, 35);
	//draw word hud
	glColor4f(0.349, 0.019, 1, 0.5f);
	drawHudElement(20, 40, 200, 35);
	//draw input hud
	glColor4f(0.019, 0.247, 1, 0.5f);
	drawHudElement(20, 90, 200, 35);
	//draw message hud
	glColor4f(0.349, 0.019, 1, 0.5f);
	drawHudElement(270, 500, 250, 70);

	//glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	gluPerspective(60, w / h, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	gluLookAt
	(
		10, 10, 20,
		0, 0, 0,
		0, 1, 0
	);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glColorMaterial(GL_FRONT, GL_SPECULAR);


	/*glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glColorMaterial(GL_AMBIENT_AND_DIFFUSE, GL_FRONT);
	glColorMaterial(GL_SPECULAR, GL_FRONT);*/


	// enable back face culling for efficiency
	//glEnable(GL_CULL_FACE);

	////draw meshes
	drawMeshes();



	//glutSwapBuffers();



}

void MainGame::update(float dt)
{
	detectKeyPresses();
}

void MainGame::drawText(std::string s, float x, float y)
{
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 800, 0.0, 600);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);

	void * font = GLUT_BITMAP_HELVETICA_18;

	//renderBitmapString(100, 100, 100, GLUT_BITMAP_HELVETICA_18, s.c_str());

	for (std::string::iterator i = s.begin(); i != s.end(); ++i) {

		char c = *i;
		if (c == '\n') {
			glRasterPos2i(x, y - 20);
		}
		glColor3f(1.0, 1.0, 1.0);
		glutBitmapCharacter(font, c);
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void MainGame::createWorld()
{
	glm::mat4 transformation = glm::mat4(1.f);
	//transformation = glm::translate(transformation, glm::vec3(0.f, -mBoxDim*2, 0.f));
	mWorldMeshes.push_back(std::shared_ptr<glsh::Mesh>(glsh::CreateSolidPlane(100, 100, 5, 5, transformation)));
}

void MainGame::drawHudElement(float x, float y, float w, float h)
{

	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 800, 0.0, 600);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//glRasterPos2i(x, y);

	//draw stuff
	glRectf(x, y, x + w, y + h);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);

}

void MainGame::detectKeyPresses()
{
	const glsh::Keyboard* kb = getKeyboard();
	if (mWord != "" && mLevelUpText == "") {
		if (kb->keyPressed(glsh::KC_A)) {
			typeLetter("a", "A");
		}
		else if (kb->keyPressed(glsh::KC_B)) {
			typeLetter("b", "B");

		}
		else if (kb->keyPressed(glsh::KC_C)) {
			typeLetter("c", "C");

		}
		else if (kb->keyPressed(glsh::KC_D)) {
			typeLetter("d", "D");

		}
		else if (kb->keyPressed(glsh::KC_E)) {
			typeLetter("e", "E");

		}
		else if (kb->keyPressed(glsh::KC_F)) {
			typeLetter("f", "F");

		}
		else if (kb->keyPressed(glsh::KC_G)) {
			typeLetter("g", "G");

		}
		else if (kb->keyPressed(glsh::KC_H)) {
			typeLetter("h", "H");

		}
		else if (kb->keyPressed(glsh::KC_I)) {
			typeLetter("i", "I");

		}
		else if (kb->keyPressed(glsh::KC_J)) {
			typeLetter("j", "J");

		}
		else if (kb->keyPressed(glsh::KC_K)) {
			typeLetter("k", "K");

		}
		else if (kb->keyPressed(glsh::KC_L)) {
			typeLetter("l", "L");

		}
		else if (kb->keyPressed(glsh::KC_M)) {
			typeLetter("m", "M");

		}
		else if (kb->keyPressed(glsh::KC_N)) {
			typeLetter("n", "N");

		}
		else if (kb->keyPressed(glsh::KC_O)) {
			typeLetter("o", "O");

		}
		else if (kb->keyPressed(glsh::KC_P)) {
			typeLetter("p", "P");

		}
		else if (kb->keyPressed(glsh::KC_Q)) {
			typeLetter("q", "Q");

		}
		else if (kb->keyPressed(glsh::KC_R)) {
			typeLetter("r", "R");

		}
		else if (kb->keyPressed(glsh::KC_S)) {
			typeLetter("s", "S");

		}
		else if (kb->keyPressed(glsh::KC_T)) {
			typeLetter("t", "T");

		}
		else if (kb->keyPressed(glsh::KC_U)) {
			typeLetter("u", "U");

		}
		else if (kb->keyPressed(glsh::KC_V)) {
			typeLetter("v", "V");

		}
		else if (kb->keyPressed(glsh::KC_W)) {
			typeLetter("w", "W");

		}
		else if (kb->keyPressed(glsh::KC_X)) {
			typeLetter("x", "X");

		}
		else if (kb->keyPressed(glsh::KC_Y)) {
			typeLetter("y", "Y");

		}
		else if (kb->keyPressed(glsh::KC_Z)) {
			typeLetter("z", "Z");

		}
		else if (kb->keyPressed(glsh::KC_SPACE)) {
			mInputText.append(" ");

		}
		else if (kb->keyPressed(glsh::KC_BACKSPACE)) {
			if (mInputText.length() > 0) {
				mInputText.pop_back();
			}
		}
	}

	if (kb->keyPressed(glsh::KC_RETURN)) {
		if (mLevelUpText == "") {
			inputWord();
		}
		else {
			mLevelUpText = "";
		}

	}
}

void MainGame::typeLetter(std::string lowercase, std::string uppercase)
{
	const glsh::Keyboard* kb = getKeyboard();
	if (kb->isKeyDown(glsh::KC_SHIFT)) {
		mInputText.append(uppercase);
	}
	else {
		mInputText.append(lowercase);
	}
}

void MainGame::initWordList()
{
	std::string line;
	infile.open("words_alpha.txt");
	if (infile.is_open()) {
		while (std::getline(infile, line)) {
			lines.push_back(line);
		}
		infile.close();
	}

}

void MainGame::getNextWord()
{


	if (lines.size() >= 4) {
		srand(time(NULL));
		int random_number = genRandNum(lines.size());
		std::cout << random_number << std::endl;
		std::cout << lines[random_number] << std::endl;
		mWord = lines[random_number];
	}

}

void MainGame::inputWord()
{
	//check if input matches word
	if (mInputText == mWord) {
		std::cout << "Correct!" << std::endl;
		mInputText = "";
		getNextWord();
		mCurrentPoints++;
		if (isLeveledUp()) {
			std::cout << "You leveled up!" << std::endl;
		}

	}
	else {
		std::cout << "Wrong! Try again." << std::endl;
		mInputText = "";
	}
}

int MainGame::genRandNum(int max)
{
	std::mt19937_64 rng;
	// initialize the random number generator with time-dependent seed
	uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
	rng.seed(ss);
	// initialize a uniform distribution between 0 and 1
	std::uniform_real_distribution<double> unif(0, max);
	// ready to generate random numbers
	int randnum = unif(rng);

	return randnum;

}

bool MainGame::isLeveledUp()
{
	if (mCurrentPoints >= mMaxPoints) {
		mLevel++;
		mLevelText = "Level: " + std::to_string(mLevel);
		mCurrentPoints = 0;

		//show text
		mLevelUpText = "Woohoo! You leveled up!\nPress Return Key...";
		switch (mLevel) {
		case 2:
			addBox();
			break;
		case 3:
			addDoor();
			break;
		default:
			break;
		}
		return true;
	}
	return false;
}

void MainGame::drawMeshes()
{
	drawRoof();
	for (std::shared_ptr<glsh::Mesh> box : mBoxes) {
		glColor3d(0.807, 0.792, 0.650);
		box->draw();
	}


	for (std::shared_ptr<glsh::Mesh> door : mDoors) {
		glColor3d(0.533, 0.384, 0.145);
		door->draw();
	}

	for (std::shared_ptr<glsh::Mesh> worldMesh : mWorldMeshes) {
		glColor3d(0, 0.619, 0.098);
		worldMesh->draw();
	}

	glColor3f(1, 1, 1);

}

void MainGame::addBox()
{
	glm::mat4 transform = glm::mat4(1.0f);
	if (mNumBoxes > 0) {
		//move next box up
		transform = glm::translate(transform, glm::vec3(0.f, 1.f, 0.f));
	}
	mBoxes.push_back(std::shared_ptr<glsh::Mesh>(glsh::CreateSolidBox(mBoxDim, mBoxDim, mBoxDim, transform)));
	mNumBoxes++;
}

void MainGame::drawRoof()
{

	glPushMatrix();
	glScalef(5, 1, 5);
	glTranslatef(0.f, 6.f, 0.f);

	
	

	glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
									 // Front
	glColor3f(0.474, 0.439, 0.388);     // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.474, 0.439, 0.388);     // Green
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.474, 0.439, 0.388);     // Blue
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Right
	glColor3f(0.329, 0.290, 0.231);     // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.329, 0.290, 0.231);     // Blue
	glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(0.329, 0.290, 0.231);     // Green
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Back
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);

	// Left
	glColor3f(1.0f, 0.0f, 0.0f);       // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);       // Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);       // Green
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();   // Done drawing the pyramid

	

	


	
	

	glPopMatrix();

}

void MainGame::addDoor()
{
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(0.f, 0.f, mBoxDim / 2));
	mDoors.push_back(std::shared_ptr<glsh::Mesh>(glsh::CreateSolidBox(mDoorWidth, mDoorHeight, 0.1, transform)));
}

void MainGame::addWindow()
{
}


