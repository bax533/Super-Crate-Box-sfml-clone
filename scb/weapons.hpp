#pragma once
#include"bits/stdc++.h"
#include"SFML/Graphics.hpp"
#define col getColor()
using namespace sf;

class Rocket
{public:
	Texture tex, dymraztex, dymdwatex;
	Sprite obraz, dymraz, dymdwa;
	Vector2f speed;
	std::vector<Sprite>dymy;	
	bool drawable;
	
	Rocket()
	{
		if(tex.loadFromFile("images/rocket.png") and dymraztex.loadFromFile("images/dym1.png") and dymdwatex.loadFromFile("images/dym2.png"))
		{	obraz.setTexture(tex); dymraz.setTexture(dymraztex); dymdwa.setTexture(dymdwatex);}
		obraz.setOrigin(5, 5);
		speed.x=0.5;speed.y=0;
		dymraz.setOrigin(10, 10);
		dymdwa.setOrigin(10, 10);
		drawable=1;
	}

	void reset()
	{
		speed.x=0.5;speed.y=0;
		dymraz.setOrigin(10, 10);
		dymdwa.setOrigin(10, 10);
		drawable=1;
	}

	void zadyma(bool in,RenderWindow &window)
	{
		//bool ret=0;
		if(in)
		{
			if(rand()%2)
			{
				dymraz.setPosition(obraz.getPosition()); 	 
				dymy.push_back(dymraz);	 
			}			
			else
			{
				dymdwa.setPosition(obraz.getPosition());
				dymy.push_back(dymdwa);
			}
		}
		
		for(int i=0; i<dymy.size(); i++)
		{
			if(dymy[i].col.a>0)
			{
				dymy[i].setColor(Color(dymy[i].col.r, dymy[i].col.g, dymy[i].col.b, dymy[i].col.a-5));
				dymy[i].setScale(dymy[i].getScale().x+0.1, dymy[i].getScale().y+0.1);
				dymy[i].setRotation(dymy[i].getRotation()+1);
				window.draw(dymy[i]);
			}
			else
			{
				//std::swap(dymy[i], dymy[dymy.size()-1]);
				//dymy.pop_back();
				//i--;
			}

		}
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

class Bullet
{public:
	Texture tex;
	Sprite obraz;
	Vector2f speed;
	double dmg;

	Bullet()
	{
		if(tex.loadFromFile("images/bullet.png"))
			obraz.setTexture(tex);
		obraz.setOrigin(5, 5);
		speed.x=15;speed.y=0;
		dmg=1;
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

class Pistol
{public:
	Sprite obraz;
	Texture tex;

	Pistol()
	{
		tex.loadFromFile("images/pistol.png");
		obraz.setTexture(tex);
	}

	FloatRect getBounds()
	{
		return obraz.getGlobalBounds();
	}

	Vector2f getPos()
	{
		return obraz.getPosition();
	}
};

class Dual
{public:
	Sprite obraz;
	Texture tex;

	Dual()
	{
		tex.loadFromFile("images/dual.png");
		obraz.setTexture(tex);
	}
	FloatRect getBounds()
	{
		return obraz.getGlobalBounds();
	}

	Vector2f getPos()
	{
		return obraz.getPosition();
	}

};

class Minigun
{public:
	Sprite obraz;
	Texture tex;

	Minigun()
	{
		tex.loadFromFile("images/mini.png");
		obraz.setTexture(tex);
	}

	FloatRect getBounds()
	{
		return obraz.getGlobalBounds();
	}

	Vector2f getPos()
	{
		return obraz.getPosition();
	}
};

class Bazooka
{public:
	Sprite obraz;
	Texture tex;

	Bazooka()
	{
		tex.loadFromFile("images/bazooka.png");
		obraz.setTexture(tex);
	}

	FloatRect getBounds()
	{
		return obraz.getGlobalBounds();
	}

	Vector2f getPos()
	{
		return obraz.getPosition();
	}

};

class Revolver
{public:
	Sprite obraz;
	Texture tex;

	Revolver()
	{
		tex.loadFromFile("images/revolver.png");
		obraz.setTexture(tex);
	}

	FloatRect getBounds()
	{
		return obraz.getGlobalBounds();
	}

	Vector2f getPos()
	{
		return obraz.getPosition();
	}
};

class Granade
{public:
	Sprite obraz;
	Texture tex;
	Vector2f speed;	
	bool rzucony;

	Granade()
	{
		tex.loadFromFile("images/granade.png");
		obraz.setTexture(tex);
		speed=Vector2f(8.0f, 7.0f);
		rzucony=0;
		obraz.setOrigin(5, 10);
	}

	void reset()
	{
		speed=Vector2f(8.0f, -7.0f);
		rzucony=0;
		obraz.setRotation(0);
	}

	FloatRect getBounds()
	{
		return obraz.getGlobalBounds();
	}

	Vector2f getPos()
	{
		return obraz.getPosition();
	}
};
