#ifndef ENGINE_H
#define ENGINE_H
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "Thomas.h"
#include "Bob.h"
#include "HUD.h"

using namespace sf;

class Engine 
{
private:
    // Texture Holder
	TextureHolder th;

	Thomas m_Thomas;
	Bob m_Bob;

	// A class reference to manage all the levels
	LevelManager m_LM;

	// A class reference to manage sound
	SoundManager m_SM;

	// The hud
	Hud m_Hud;
	int m_FramesSinceLastHUDUpdate = 0;
	int m_TargetFramesPerHUDUpdate = 500;

	const int TILE_SIZE = 50;
	const int VERT_IN_QUAD = 4;

	// The force pushing the characters down
	const int GRAVITY = 300;

	RenderWindow m_Window;

	//The main views
	View m_MainView;
	View m_LeftView;
	View m_RightView;

	// Background views
	View m_BGMainView;
	View m_BGLeftView;
	View m_BGRightView;
	View m_HUDView;

	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;

	bool m_IsPlaying = false;

	bool m_Character1 = true;

	bool m_IsSplitScreen = false;

	bool m_NewLevelRequired = true;

	float m_TimeRemaining = 10;
	sf::Time m_GameTimeTotal;

	// The vertex array for the level tiles
	VertexArray m_VALevel;

	// The 2d array with the map for the level
	int** m_ArrayLevel = NULL;

	// Texture for the level tiles
	Texture m_TextureFiles;

	vector <Vector2f> m_FireEmitters;

	void input();
	void update(float dtAsSeconds);
	void draw();
	void loadLevel();
	void populateEmitters(vector<Vector2f>& vSoundEmitters, int** arrayLevel);
	bool detectCollisions(PlayableCharacter& character);



public:
	Engine();
	void run();
};


#endif ENGINE_H
