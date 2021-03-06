#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

#pragma once
class ReadFromText
{
private:
	string str, strcopy;
	string filespeech;
	string copyspeech;
	float speechspeed;
	int letterofspeech;
	int vectorspeech;
	bool changetext;
	int LineParagraph;
	bool speedup;

public:
	ReadFromText();
	~ReadFromText();

	bool KeyPressed;
	bool talking;
	void Textfile(const char* filename, bool Character);
	void Dialogue(const char* filename);
	void Obtain(const char* filename, bool loot, string ItemName);
	void Update(double dt);
	string GetText(void);
	int GetParagraphLine(void);

	vector<string> line;
	vector<string> CharacterText;
	vector<string> InstructionText;

	void ReadCharacterSet();
	void ReadCharacterGet();

	void ReadInstructionSet();
	void ReadInstructionGet();
};

