#include "TutLvl3.h"


TutLvl3::TutLvl3()
{
}


TutLvl3::~TutLvl3()
{
}

void TutLvl3::Init()
{
	GameModel::Init();

	m_tileMap = new TileMap();
	m_tileMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_tileMap->LoadMap("Image//Tutorial3.csv");

	m_itemMap = new TileMap();
	m_itemMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_itemMap->LoadMap("Image//Tutorial3Item.csv");

	GameModel::getKeys();
	GameModel::setLaser();

	player = new PlayerCharacter(Vector3(2, 16, 0));


	InstructFile3 = "SpeechText//Instruction//AI.txt";
	InstructText3 = true;

	RenderSpeech();
}

void TutLvl3::RenderSpeech()
{
	if (!speech.talking && InstructText3)
	{
		for (int n = 0; n < speech.InstructionText.size(); n++)
		{
			if (speech.InstructionText[n] == InstructFile3)
			{
				speech.talking = true;
				const char* temp = speech.InstructionText[n].c_str();
				speech.Dialogue(temp);
				speech.InstructionText[n] = " ";
			}
		}
		InstructFile3 = "";
		if (temp_InstructFile3 != "")
		{
			InstructFile3 = temp_InstructFile3;
		}
		else
		{
			InstructText3 = false;
		}
	}
	if (commands[SPEECH_NEXTLINE] && speech.talking)
	{
		speech.KeyPressed = true;
	}
}

void TutLvl3::Update(double dt)
{
	GameModel::Update(dt);
	if (GameModel::getwin())
		if (GameModel::getNext())
		{
			if (GameModel::getDead())
				throw 2;
			else
			{
				GameModel::updateHighscore(1);
				throw 3;
			}
		}

	if (speech.talking)
	{
		speech.Update(dt);
	}

}