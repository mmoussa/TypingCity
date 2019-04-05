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

	int mNumBoxes;

	//meshes
	std::list<std::shared_ptr<glsh::Mesh>> mBoxes;
	std::list<std::shared_ptr<glsh::Mesh>> mDoors;
	std::list<std::shared_ptr<glsh::Mesh>> mWindows;

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
	void addDoor();
	void addWindow();

};

