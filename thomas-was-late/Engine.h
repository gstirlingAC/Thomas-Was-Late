#ifndef ENGINE_H
#define ENGINE_H
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Thomas.h"
#include "Bob.h"

class Engine 
{
private:
    // Texture Holder
	TextureHolder th;

	Thomas m_Thomas;
	Bob m_Bob;

	const int TILE_SIZE = 50;
	const int VERT_IN_QUAD = 4;

	// The force pushing the characters down
	const int GRAVITY = 300;

	sf::RenderWindow m_Window;

	//The main views
	sf::View m_MainView;
	sf::View m_LeftView;
	sf::View m_RightView;

	// Background views
	sf::View m_BGMainView;
	sf::View m_BGLeftView;
	sf::View m_BGRightView;
	sf::View m_HUDView;

	sf::Sprite m_BackgroundSprite;
	sf::Texture m_BackgroundTexture;

	bool m_IsPlaying = false;

	bool m_Character1 = true;

	bool m_IsSplitScreen = false;

	bool m_NewLevelRequired = true;

	float m_TimeRemaining = 10;
	sf::Time m_GameTimeTotal;

	void input();
	void update(float dtAsSeconds);
	void draw();

public:
	Engine();
	void run();
};


#endif ENGINE_H
