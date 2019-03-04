#pragma once
#include "bits/stdc++.h"
#include "SFML/Graphics.hpp"

using namespace sf;

class play
{
public:
	
	Texture tex;
	Sprite obraz;
	Vector2f speed;	
	//int count;
	bool ragdoll;

	play()
	{
		if(tex.loadFromFile("images/player.png"))	obraz.setTexture(tex);	
		speed=Vector2f(0,0);	
		ragdoll = 0;
		//count=0;
	}

	void reset()
	{
		ragdoll = 0;
		//count = 0;
		speed = Vector2f(0, 0);
		obraz.setPosition(400, 101);
		obraz.setRotation(0);
	}

/*	bool animation(float fr)
	{	
		if(speed.x!=0)
		{
			if(fr>200)
			{
				if(count<=3)count++;
				else count=0;
				obraz.setTextureRect(IntRect(count*50, 0, 50, 50));
				return 1;
			}
			else return 0;
		}
		else return 0;
	}*/


	void drawTo(RenderWindow &window)
	{
		window.draw(obraz);
	}

	Vector2f getPos()
	{
		return obraz.getPosition();
	}

	FloatRect getBounds()
	{
		return obraz.getGlobalBounds();
	}
	
};
