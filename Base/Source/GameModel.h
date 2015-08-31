#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include "Model.h"
#include "PlayerCharacter.h"

#include "TileMap.h"

#include "InventoryMenu.h"

#include "AI.h"

#include "ReadFromText.h"


#include <vector>

#define worldWidth 32
#define worldHeight 24

class GameModel : public Model
{
public:
	enum COMMANDS {
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		INVENT,
		ACTION,
		MODEL_UP,
		MODEL_DOWN,
		IDLE_UP,
		IDLE_DOWN,
		IDLE_LEFT,
		IDLE_RIGHT,
		SPEECH_NEXTLINE,
		NUM_COMMANDS,
	};
protected:
	enum GAME_STATE {
		IDLE,
		PLAYER_TURN,
		AI_TURN,
		INVENTORY,
		PLACE_ITEM,
		SPEECH,
		NUM_STATES,
	};
	enum PLAYER_TYPE
	{
		PLAYERB,
		PLAYERG,
		BUTLER,
		CAT,
		CHARO,
		CLOWN,
		DARK,
		EYES,
		GLOW,
		HORN,
		MASK,
		NOEYES,
		SKELETON,
		TURBAN,
		WITCH,

		MAID,
		SHINIGAMI,
		NUM_PLAYER,
	};
	Mesh* meshPlayer[NUM_PLAYER];
	int ModelSwitch;

	enum ITEM_TYPE{
		GOLD_KEY,
		SILVER_KEY,
		RED_KEY,
		GREEN_KEY,
		BLUE_KEY,
		LEFT_KEY,
		RIGHT_KEY,
		LR_KEY,
		TRAP,
		NUM_ITEM,
	};
	Mesh* meshItem[NUM_ITEM];

	enum SPEECH_TYPE{
		PLAYERB_FACE,
		PLAYERG_FACE,
		BUTLER_FACE,
		CAT_FACE,
		CHARO_FACE,
		CLOWN_FACE,
		DARK_FACE,
		EYES_FACE,
		GLOW_FACE,
		HORN_FACE,
		MASK_FACE,
		NOEYES_FACE,
		SKELETON_FACE,
		TURBAN_FACE,
		WITCH_FACE,
		CHARACTER_FACE,
		TEXTBOX,
		NUM_SPEECH,
	};
	Mesh* meshSpeech[NUM_SPEECH];

	PlayerCharacter *player;
private:
	GAME_STATE m_gameState;

	Mesh *tile;
	
	Mesh *winMesh;
	Mesh *lose;

	float m_mapOffset_x;
	float m_mapOffset_y;

	bool PlaceItemState;

	int up, down, left, right;

	bool win;
	bool touchdoor;
	int numKey;
	bool Key;
	int totalKey;

	bool goNext;

	bool died;
	/*bool InstructText;
	string InstructFile;
	string temp_InstructFile;
*/
	Mesh *Text;
protected:
	TileMap* m_tileMap;
	TileMap* m_itemMap;
public:
	GameModel();
	~GameModel();

	virtual void Init();
	virtual void Update(double dt);
	virtual void setCommands(int command);

	bool isShowInventory() { return m_gameState == GAME_STATE::INVENTORY; }

	int getWorldWidth() { return worldWidth; }
	int getWorldHeight() { return worldHeight; }

	void MeshPlayer();
	string GetTextSpeech();
	int GetLineParagraph();

	PlayerCharacter* getPlayer();
	Mesh* getPlayerMesh();

	Mesh* getTileMesh();
	TileMap* getTileMap();
	TileMap* getItemMap();
	void getOffset(float& mapOffset_x, float& mapOffset_y);

	Mesh* getWinMesh();
	Mesh* getLoseMesh();

	Mesh* getTextMesh();
	InventoryMenu inventory;
	float InvenTime;

	std::vector<int> floorTiles;

	Mesh *shadow;

	AI *Aina;

	ReadFromText speech;
	void MeshSpeech();
	Mesh* getFaceMesh();
	Mesh* getSpeechMesh();

	Mesh* getAIMesh();

	int getKeys();
	bool getwin();

	void laserswitch(void);
	void setLaser(void);

	bool getNext();

	int getNumKeys();
	int getTotalKeys();

	bool getDead();

	std::vector<Vector3> mirror;
};

#endif