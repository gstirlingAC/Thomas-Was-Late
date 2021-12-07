#include "Engine.h"

bool Engine::detectCollisions(PlayableCharacter& character)
{
	bool reachedGoal = false;

	// Make a rect for all his parts
	FloatRect detectZone = character.getPosition();

	// Make a floatrect to test each block
	FloatRect block;
	block.width = TILE_SIZE;
	block.height = TILE_SIZE;

	// Build a zone around the character to detect collisions
	int startX = (int)(detectZone.left / TILE_SIZE) -1;
	int startY = (int)(detectZone.top / TILE_SIZE) -1;
	int endX = (int)(detectZone.left / TILE_SIZE) +2;
	int endY = (int)(detectZone.top / TILE_SIZE) +3;

	/*
	* Make sure we don't test positions lower than zero
	* or higher than the end of the array
	*/
	if (startX < 0) startX = 0;
	if (startY < 0) startY = 0;
	if (endX >= m_LM.getLevelSize().x)
		endX = m_LM.getLevelSize().x;
	if (endY >= m_LM.getLevelSize().y)
		endY = m_LM.getLevelSize().y;
	
	// Has the character fallen out of the map?
	FloatRect level(0, 0,
		m_LM.getLevelSize().x * TILE_SIZE,
		m_LM.getLevelSize().y * TILE_SIZE);

	if (!character.getPosition().intersects(level))
	{
		// Respawn the character
		character.spawn(m_LM.getStartPosition(), GRAVITY);
	}

	// Loop through all the local blocks
	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			// Initialise the starting position of the current block
			block.left = x * TILE_SIZE;
			block.top = y * TILE_SIZE;

			// Has the character been burned or drowned?
			if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
			{
				if (character.getHead().intersects(block))
				{
					character.spawn(m_LM.getStartPosition(), GRAVITY);

					// Which sound should be played?
					if (m_ArrayLevel[y][x] == 2) // Fire, buuuurrnn!
					{
						// Play a sound
					}
					else // water gurgle!
					{
						// Play a sound
					}
				}
			}

			// Is character colliding with regular blocks
			if (m_ArrayLevel[y][x] == 1)
			{
				if (character.getRight().intersects(block))
				{
					character.stopRight(block.left);
				}
				else if (character.getLeft().intersects(block))
				{
					character.stopLeft(block.left);
				}
				if (character.getFeet().intersects(block))
				{
					character.stopFalling(block.top);
				}
				else if (character.getHead().intersects(block))
				{
					character.stopJump();
				}
			}

			// Is the character colliding with the goal block
			if (m_ArrayLevel[y][x] == 4)
			{
				// Particles ooooo-sparkly
				
				// Audio cheers yaaaay!!!

				// Character has reached the goal
				reachedGoal = true;
			}
		}
	}

	return reachedGoal;
}