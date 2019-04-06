#pragma once
#include "GLSH.h"
#include "GLSH_Prefabs.h"
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
#include <chrono>

class MainGame : public glsh::App
{

private:


	//ui
	std::string mInputText;
	std::string mWord;
	std::string mLevelText;
	std::string mLevelUpText;

	std::vector<std::string> lines;
	std::ifstream infile;

	//game variables
	int mCurrentPoints;
	int mMaxPoints;
	int mLevel;

	//game mesh variables
	float mBoxDim;
	float mDoorWidth;
	float mDoorHeight;
	float mWindowWidth;
	float mWindowHeight;

	int mNumBoxes;

	//meshes
	std::list<std::shared_ptr<glsh::Mesh>> mBoxes;
	std::list<std::shared_ptr<glsh::Mesh>> mDoors;
	std::list<std::shared_ptr<glsh::Mesh>> mWindows;
	std::list<std::shared_ptr<glsh::Mesh>> mWorldMeshes;

public:
	MainGame();
	~MainGame();
	bool initialize(int w, int h) override;
	void shutdown() override;
	void resize(int w, int h) override;
	void draw() override;
	void update(float dt) override;

	//drawing methods
	void drawText(std::string s, float x, float y);
	void createWorld();
	void drawHudElement(float x, float y, float w, float h);

	//keyboard
	void detectKeyPresses();
	void typeLetter(std::string lowercase, std::string uppercase);

	//io
	void initWordList();
	void getNextWord();
	void inputWord();

	//utils
	int genRandNum(int max);

	//game methods
	bool isLeveledUp();
	void drawMeshes();
	void addBox();
	void drawRoof();
	void addDoor();
	void addWindow();

};

