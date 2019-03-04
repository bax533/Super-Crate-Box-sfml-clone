#pragma once
#include"SFML/Graphics.hpp"
#include"bits/stdc++.h"
using namespace sf;

class Crate
{public:
	Sprite obraz;
	Texture tex;

	Crate()
	{
		tex.loadFromFile("images/crate.png");
		obraz.setTexture(tex);
	}

	void spawn(Vector2f pos)
	{
		obraz.setPosition(pos);
	}

	FloatRect getBounds()
	{
		return obraz.getGlobalBounds();
	}
};
