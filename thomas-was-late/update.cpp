#include "Engine.h"
#include <sstream>

#include <iostream>

using namespace std;

void Engine::update(float dtAsSeconds)
{
	if (m_NewLevelRequired)
	{
		// Load the level
		loadLevel();
	}

	if (m_IsPlaying)
	{
		m_Thomas.update(dtAsSeconds);
		m_Bob.update(dtAsSeconds);

		// Detect collisions
		if (detectCollisions(m_Thomas) && detectCollisions(m_Bob))
		{
			// New level required
			m_NewLevelRequired = true;

			// play a victory sound
			m_SM.PlayReachGoal();
		}
		else
		{
			detectCollisions(m_Bob);
		}

		// Let Thomas and Bob jump on each others heads
		if (m_Bob.getFeet().intersects(m_Thomas.getHead()))
		{
			m_Bob.stopFalling(m_Thomas.getHead().top);
		}
		else if (m_Thomas.getFeet().intersects(m_Bob.getHead()))
		{
			m_Thomas.stopFalling(m_Bob.getHead().top);
		}

		m_TimeRemaining -= dtAsSeconds;

		if (m_TimeRemaining <= 0)
		{
			m_NewLevelRequired = true;
		}
	}

	if (m_IsSplitScreen)
	{
		m_LeftView.setCenter(m_Thomas.getCenter());
		m_RightView.setCenter(m_Bob.getCenter());
	}
	else
	{
		if (m_Character1)
		{
			m_MainView.setCenter(m_Thomas.getCenter());
		}
		else
		{
			m_MainView.setCenter(m_Bob.getCenter());
		}
	}

	vector<Vector2f>::iterator it;

	for (it = m_FireEmitters.begin(); it != m_FireEmitters.end(); it++)
	{
		float posX = (*it).x;
		float posY = (*it).y;

		FloatRect localRect(posX - 250, posY - 250, 500, 500);

		if (m_Thomas.getPosition().intersects(localRect))
		{
			m_SM.PlayFire(Vector2f(posX, posY), m_Thomas.getCenter());
		}
	}
}