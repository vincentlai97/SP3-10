#include "TutLvl2.h"


TutLvl2::TutLvl2()
{
}


TutLvl2::~TutLvl2()
{
}

void TutLvl2::Init()
{
	GameModel::Init();

	m_tileMap = new TileMap();
	m_tileMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_tileMap->LoadMap("Image//Tutorial2.csv");

	m_itemMap = new TileMap();
	m_itemMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_itemMap->LoadMap("Image//Tutorial2Item.csv");

	GameModel::getKeys();
	GameModel::setLaser();

	GameModel::setLaser();

	player = new PlayerCharacter(Vector3(28, 18, 0));

	InstructFile2 = "SpeechText//Instruction//AI.txt";
	InstructText2 = true;

	RenderSpeech();
}

void TutLvl2::RenderSpeech()
{
	if (!speech.talking && InstructText2)
	{
		for (int n = 0; n < speech.InstructionText.size(); n++)
		{
			if (speech.InstructionText[n] == InstructFile2)
			{
				speech.talking = true;
				const char* temp = speech.InstructionText[n].c_str();
				speech.Dialogue(temp);
				speech.InstructionText[n] = " ";
			}
		}
		InstructFile2 = "";
		if (temp_InstructFile2 != "")
		{
			InstructFile2 = temp_InstructFile2;
		}
		else
		{
			InstructText2 = false;
		}
	}
	if (commands[SPEECH_NEXTLINE] && speech.talking)
	{
		speech.KeyPressed = true;
	}
}

void TutLvl2::Update(double dt)
{
	GameModel::Update(dt);
	if (GameModel::getwin())
		if (GameModel::getNext())
		{
			if (GameModel::getDead())
				throw 1;
			else
			{
				GameModel::updateHighscore(1);
				throw 2;
			}
		}

}