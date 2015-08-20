#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include "Model.h"
#include "PlayerCharacter.h"

#include "TileMap.h"

#include "InventoryMenu.h"

#include "AI.h"

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
		NUM_COMMANDS,
	};
protected:
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
		MAID,
		MASK,
		NOEYES,
		SHINIGAMI,
		SKELETON,
		TURBAN,
		WITCH,
		NUM_PLAYER,
	};
	Mesh* meshPlayer[NUM_PLAYER];
	int ModelSwitch;

	enum BOX_TYPE{
		PLAYERB_BOX,
		PLAYERG_BOX,
		BUTLER_BOX,
		CAT_BOX,
		CHARO_BOX,
		CLOWN_BOX,
		DARK_BOX,
		EYES_BOX,
		GLOW_BOX,
		HORN_BOX,
		MAID_BOX,
		MASK_BOX,
		NOEYES_BOX,
		SHINIGAMI_BOX,
		SKELETON_BOX,
		TURBAN_BOX,
		WITCH_BOX,
		NUM_BOX,
	};
	Mesh* meshBox[NUM_BOX];

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

	PlayerCharacter *player;
private:
	Mesh *tile;

	TileMap* m_tileMap;
	float m_mapOffset_x;
	float m_mapOffset_y;

	Mesh *Text;
public:
	GameModel();
	~GameModel();

	virtual void Init();
	virtual void Update(double dt);

	virtual void setCommands(int command);

	int getWorldWidth() { return worldWidth; }
	int getWorldHeight() { return worldHeight; }

	void MeshPlayer();
	void MeshBox();
	void MeshItem();

	PlayerCharacter* getPlayer();
	Mesh* getPlayerMesh();

	Mesh* getTileMesh();
	TileMap* getTileMap();
	void getOffset(float& mapOffset_x, float& mapOffset_y);

	Mesh* getTextMesh();
	InventoryMenu inventory;


	AI Aina;

};

#endif