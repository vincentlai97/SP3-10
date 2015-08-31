#include "NDLvl.h"

NDlvl::NDlvl()
{
}


NDlvl::~NDlvl()
{
}

void NDlvl::Init()
{
	GameModel::Init();

	m_tileMap = new TileMap();
	m_tileMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_tileMap->LoadMap("Image//Tutorial1.csv");

	m_itemMap = new TileMap();
	m_itemMap->Init(25, 32, 24, worldWidth, worldHeight);
	m_itemMap->LoadMap("Image//BlankItem.csv");

	GameModel::getKeys();
	GameModel::setLaser();

	player = new PlayerCharacter(Vector3(11, 12 , 0));

	cout << "check";
	InstructFile = "SpeechText//Instruction//MoveCharacter.txt";
	InstructText = true;

	RenderSpeech();
}

void NDlvl::RenderSpeech()
{
	if (!speech.talking && InstructText)
	{
		for (int n = 0; n < speech.InstructionText.size(); n++)
		{
			if (speech.InstructionText[n] == InstructFile)
			{
				speech.talking = true;
				const char* temp = speech.InstructionText[n].c_str();
				speech.Dialogue(temp);
				speech.InstructionText[n] = " ";
			}
		}
		InstructFile = "";
		if (temp_InstructFile != "")
		{
			InstructFile = temp_InstructFile;
		}
		else
		{
			InstructText = false;
		}
	}
	if (commands[SPEECH_NEXTLINE] && speech.talking)
	{
		speech.KeyPressed = true;
	}
}

void NDlvl::Update(double dt)
{
	GameModel::Update(dt);
	if (GameModel::getwin())
		if (GameModel::getNext())
		{
			if (GameModel::getDead())
				throw 0;
			else
				throw 1;
		}

		if (speech.talking)
		{
			speech.Update(dt);
		}
}

