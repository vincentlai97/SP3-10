#include "ReadFromText.h"

ReadFromText::ReadFromText() :KeyPressed(false), talking(false)
{
	LineParagraph = 0;
	changetext = false;
	speechspeed = 0;
	letterofspeech = 0;
	vectorspeech = 0;
	
	copyspeech = "";
	speedup = false;
}

ReadFromText::~ReadFromText()
{
}

void ReadFromText::Textfile(const char* filename, bool Character)
{
	ifstream file;
	string data;

	file.open(filename);

	if (file.is_open())
	{
		if (Character)
		{
			CharacterText.clear();
			CharacterText.shrink_to_fit();
		}
		else
		{
			InstructionText.clear();
			InstructionText.shrink_to_fit();
		}
		file.clear();
		file.seekg(0, file.beg);

		while (file.good()) {
			getline(file, data, '\n');

			if (Character)
				CharacterText.push_back(data);
			else
				InstructionText.push_back(data);
		}
	}
	file.close();
}

void ReadFromText::Dialogue(const char* filename)
{
	ifstream file;
	string data;

	file.open(filename);

	if (file.is_open())
	{
		line.clear();
		line.shrink_to_fit();

		file.clear();
		file.seekg(0, file.beg);

		while (file.good()) {
			getline(file, data, '\n');

			line.push_back(data);
		}
	}
	file.close();

	changetext = false;
	speechspeed = 0;
	letterofspeech = 0;

	copyspeech = "";
	speedup = false;
	vectorspeech = 0;
	filespeech = line[vectorspeech];
	LineParagraph = 1;
}

void ReadFromText::Obtain(const char* filename, bool loot, string ItemName)
{
	ifstream file;
	string data;

	file.open(filename);

	if (file.is_open())
	{
		line.clear();
		line.shrink_to_fit();

		file.clear();
		file.seekg(0, file.beg);

		if (loot)
		{
			if (file.good())
			{
				getline(file, data, '\n');
				line.push_back(data);
			}
		}
		else
		{
			while (file.good()) {
				getline(file, data, '\n');
			}
			line.push_back(data);
		}
	}
	file.close();

	changetext = false;
	speechspeed = 0;
	letterofspeech = 0;

	copyspeech = "";
	speedup = false;
	vectorspeech = 0;
	filespeech = line[vectorspeech] + ItemName + ".";
	LineParagraph = 1;
}

void ReadFromText::Update(double dt)
{
	if (speedup)
	{
		if (letterofspeech < filespeech.size())
		{
			while (letterofspeech < filespeech.size())
			{
				copyspeech += filespeech[letterofspeech];
				letterofspeech += 1;
			}
		}
		else if (vectorspeech < line.size() - 1)
		{
			if (line[vectorspeech + 1] != "")
			{
				if (vectorspeech < line.size() - 1)
				{
					letterofspeech = 0;
					vectorspeech = vectorspeech + 1;
					filespeech = line[vectorspeech];
					copyspeech = "";

					LineParagraph++;
				}
			}
			else
			{
				changetext = true;
				speedup = false;
			}
		}
	}

	speechspeed -= (float)dt;

	if (speechspeed < 0 && vectorspeech < line.size() && !speedup)
	{
		if (letterofspeech < filespeech.size())
		{
			copyspeech += filespeech[letterofspeech];
			letterofspeech += 1;
			if (letterofspeech < filespeech.size())
			{
				if (filespeech[letterofspeech] == ' ')
				{
					copyspeech += filespeech[letterofspeech];
					letterofspeech += 1;
				}
			}
			speechspeed = 0.1;
		}
		else if (vectorspeech < line.size() - 1)
		{
			if (line[vectorspeech + 1] != "")
			{
				if (vectorspeech < line.size() - 1)
				{
					letterofspeech = 0;
					vectorspeech = vectorspeech + 1;
					filespeech = line[vectorspeech];
					copyspeech = "";

					LineParagraph++;
				}
			}
			else
				changetext = true;
		}
	}

	if (KeyPressed && changetext && !speedup)
	{
		KeyPressed = false;

		changetext = false;
		letterofspeech = 0;
		vectorspeech = vectorspeech + 2;
		filespeech = line[vectorspeech];
		copyspeech = "";

		LineParagraph = 1;
	}
	else if (KeyPressed && !changetext && !speedup)
	{
		KeyPressed = false;

		speedup = true;
	}
	if (KeyPressed && vectorspeech >= line.size() - 1)
	{
		KeyPressed = false;
		talking = false;

		filespeech = "";
		copyspeech = "";

		LineParagraph = 0;
	}
}

string ReadFromText::GetText()
{
	return copyspeech;
}

int ReadFromText::GetParagraphLine()
{
	return LineParagraph;
}