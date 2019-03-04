#pragma once
#include"bits/stdc++.h"
#include"SFML/Graphics.hpp"
#include"weapons.hpp"
using namespace sf;

void flipleft(Sprite &sprite, float width, float height)
{
	sprite.setTextureRect(IntRect(width, 0, -width, height));
}
void flipright(Sprite &sprite, float width, float height)
{
	sprite.setTextureRect(IntRect(0, 0, width, height));
}

class Small
{public:
	Texture greentex, redtex;
	Sprite obraz;
	Vector2f speed;
	double life;
	float gravity;
	bool angry, ragdoll;
	Small()
	{
		greentex.loadFromFile("images/smallgreen.png");
		redtex.loadFromFile("images/smallred.png");
		obraz.setTexture(greentex);
		speed.x=6.5;angry=0;life=2;gravity=0.667f;ragdoll=0;
	}

	void move(std::vector<std::pair<Sprite, int> > tiles)
	{
		int kol=0;
		if(!ragdoll)
		{		
			for(int i=0; i<tiles.size(); i++)
			{
				FloatRect box=obraz.getGlobalBounds();
				if(box.intersects(tiles[i].first.getGlobalBounds()))
				{
					if(tiles[i].second==2)
					{
						if(speed.x<0)obraz.setPosition(tiles[i].first.getPosition().x+50, obraz.getPosition().y);
						else 		 obraz.setPosition(tiles[i].first.getPosition().x-35, obraz.getPosition().y);
						speed.x*=-1;
						if(speed.x<0)flipleft(obraz, box.width, box.height);
						if(speed.x>0)flipright(obraz, box.width,box.height);			
					}
					if(tiles[i].second==1)
					{
						kol=1;
						speed.y=0;
						obraz.setPosition(obraz.getPosition().x, tiles[i].first.getPosition().y-33);
					}
					if(tiles[i].second==3 and speed.x<0){obraz.setPosition(tiles[i].first.getPosition().x+10, obraz.getPosition().y+50);}
					if(tiles[i].second==4 and speed.x>0){obraz.setPosition(tiles[i].first.getPosition().x-35, obraz.getPosition().y+50);}
				}
			}
			if(!kol)speed.y+=gravity;
		}
		else speed.y+=gravity;		
		obraz.move(speed);
	}
	
	void spawn(int dynks)
	{
		if(angry)
		{
			obraz.setTexture(redtex);
			speed.x=10;
		}
		FloatRect box=obraz.getGlobalBounds();
		if(dynks){obraz.setPosition(100, -50);flipright(obraz, box.width, box.height);}
		else	 {obraz.setPosition(890, -50);speed.x*=-1;flipleft(obraz, box.width, box.height);}
	}

	void pocisk(std::vector<Bullet> &bullets)
	{
		for(int i=0; i<bullets.size(); i++)
		{
			FloatRect box=bullets[i].getBounds();
			if(box.intersects(obraz.getGlobalBounds()))
			{
				life-=bullets[i].dmg;
				std::swap(bullets[i], bullets[bullets.size()-1]);
				bullets.pop_back();
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

class Big
{public:
	Texture greentex, redtex;
	Sprite obraz;
	Vector2f speed;
	double life;
	float gravity;
	bool angry, ragdoll;
	int it;
	Big()
	{
		greentex.loadFromFile("images/biggreen.png");
		redtex.loadFromFile("images/bigred.png");
		obraz.setTexture(greentex);
		speed.x=4.5;angry=0;life=8;gravity=2.7f; ragdoll=0;
		it=0;
	}

	void setTex(int fr)
	{
		if(fr>300)
			it++;
		
		if(it>1)it=0;

		if(speed.x>0)
			obraz.setTextureRect(IntRect(it*55, 0, 55, 60));			
		else
			obraz.setTextureRect(IntRect(it*55, 0, -55, 60));	
	}

	void move(std::vector<std::pair<Sprite, int> > tiles)
	{
		int kol=0;
		if(!ragdoll)
		{
			for(int i=0; i<tiles.size(); i++)
			{
				FloatRect box=obraz.getGlobalBounds();
				if(box.intersects(tiles[i].first.getGlobalBounds()))
				{
					if(tiles[i].second==2)
					{
						if(speed.x<0)obraz.setPosition(tiles[i].first.getPosition().x+50, obraz.getPosition().y);
						else 		 obraz.setPosition(tiles[i].first.getPosition().x-60, obraz.getPosition().y);
						speed.x*=-1;
						if(speed.x<0)flipleft(obraz, box.width, box.height);
						if(speed.x>0)flipright(obraz, box.width,box.height);			
					}
					if(tiles[i].second==1)
					{
						kol=1;
						speed.y=0;
						obraz.setPosition(obraz.getPosition().x, tiles[i].first.getPosition().y-50);
					}
					if(tiles[i].second==3 and speed.x<0){obraz.setPosition(tiles[i].first.getPosition().x+40, obraz.getPosition().y+50);}
					if(tiles[i].second==4 and speed.x>0){obraz.setPosition(tiles[i].first.getPosition().x-60, obraz.getPosition().y+50);}
				}
			}
			if(!kol)speed.y+=gravity;
		}
		else speed.y+=gravity;
		obraz.move(speed);
	}
	
	void spawn(int dynks)
	{
		if(angry==1)
		{
			obraz.setTexture(redtex);
			speed.x=7;
		}
		FloatRect box=obraz.getGlobalBounds();
		if(dynks){obraz.setPosition(150, -60);flipright(obraz, box.width, box.height);}
		else	 {obraz.setPosition(790, -60);speed.x*=-1;flipleft(obraz, box.width, box.height);}
	}

	void pocisk(std::vector<Bullet> &bullets)
	{
		for(int i=0; i<bullets.size(); i++)
		{
			FloatRect box=bullets[i].getBounds();
			if(box.intersects(obraz.getGlobalBounds()))
			{
				life-=bullets[i].dmg;
				std::swap(bullets[i], bullets[bullets.size()-1]);
				bullets.pop_back();
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

