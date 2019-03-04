#include "SFML/Graphics.hpp"
#include "bits/stdc++.h"

using namespace sf;
const int W=1024, H=640, ts=32;

struct Mapa
{
	Sprite obraz;
	int blok;
};

Mapa mapa[40][40];

enum bloki
{
	EMPTY,
	WALL,
	FLOOR,
	LEFT,
	RIGHT,
	CRATE
};

int main()
{
	
	RenderWindow Window( VideoMode( W+64, H ), "app!" );

	Texture tileTex, floorTex, wallTex, kursorTex, leftTex, rightTex, crateTex;
	Sprite kursor, tile, floor, wall,left, right, crate;

	Color color(0, 0, 200, 100);

	if(!tileTex.loadFromFile("resources/tile.png") || !floorTex.loadFromFile("resources/floor.png") || !wallTex.loadFromFile("resources/wall.png") || !kursorTex.loadFromFile("resources/kursor.png")  || !rightTex.loadFromFile("resources/smallR.png") || 
	!leftTex.loadFromFile("resources/smallL.png") || !crateTex.loadFromFile("resources/crate.png"))
		return 0;

	crate.setTexture(crateTex);
	tile.setTexture(tileTex);
	floor.setTexture(floorTex);
	wall.setTexture(wallTex);	
	left.setTexture(leftTex);
	right.setTexture(rightTex);
	kursor.setTexture(kursorTex);
	kursor.setOrigin(3, 3);
    Window.setVerticalSyncEnabled(1); 
    Window.setFramerateLimit(60); 

//////DEKLARACJE//////


	for(int i=0; i<20; i++)
	{
		for(int j=0; j<25; j++)
		{
			mapa[i][j].obraz.setTexture(tileTex);
			mapa[i][j].obraz.setPosition(j*ts, i*ts);
		}
	}	
	
	Window.setMouseCursorVisible(0);
	int blok=0;
	floor.setPosition(W+20, 0);
	wall.setPosition(W+20, ts);
	left.setPosition(W+20, 2*ts);
	right.setPosition(W+20, 3*ts);
	crate.setPosition(W+20, 4*ts);

	FloatRect wallbox=wall.getGlobalBounds();
	FloatRect floorbox=floor.getGlobalBounds();	
	FloatRect leftbox = left.getGlobalBounds();
	FloatRect rightbox = right.getGlobalBounds();
	FloatRect cratebox = crate.getGlobalBounds();

	while(Window.isOpen())/////////////////////////////////////////////////////
	{

		kursor.setPosition((float)Mouse::getPosition(Window).x, (float)Mouse::getPosition(Window).y-ts);
	
		Event Event;
		while(Window.pollEvent(Event))
		{
			switch(Event.type)
			{
				case Event::Closed:
					Window.close();
					break;
			}

		}
///DeklaracjeWPętli///
		Vector2f pointPos=kursor.getPosition();


		for(int i=0; i<15; i++)
			for(int j=0; j<25; j++)
			{	
				FloatRect mapix=mapa[i][j].obraz.getGlobalBounds();
				if(Mouse::isButtonPressed(Mouse::Left))
				{				
					if(mapix.contains(kursor.getPosition()))
					{
						if(blok==WALL)
						{
							mapa[i][j].obraz.setTexture(wallTex);
							mapa[i][j].blok=blok;
						}
						if(blok==FLOOR)
						{
							mapa[i][j].obraz.setTexture(floorTex);
							mapa[i][j].blok=blok;
						}	
						if(blok==LEFT)
						{
							mapa[i][j].obraz.setTexture(leftTex);
							mapa[i][j].blok=blok;
						}	
						if(blok==RIGHT)
						{
							mapa[i][j].obraz.setTexture(rightTex);
							mapa[i][j].blok = blok;
						}
						if(blok==CRATE)
						{
							mapa[i][j].obraz.setTexture(crateTex);
							mapa[i][j].blok = blok;
						}
					}
				}
				if(Mouse::isButtonPressed(Mouse::Right) and mapix.contains(kursor.getPosition()))
				{
					mapa[i][j].obraz.setTexture(tileTex);
					mapa[i][j].blok=EMPTY;
				}
				Window.draw(mapa[i][j].obraz);
			}
	
			if(Mouse::isButtonPressed(Mouse::Left))
			{
				if(wallbox.contains(kursor.getPosition()))
					blok=WALL;				
				if(floorbox.contains(kursor.getPosition()))
					blok=FLOOR;
				if(leftbox.contains(kursor.getPosition()))
					blok=LEFT;
				if(rightbox.contains(kursor.getPosition()))
					blok=RIGHT;
				if(cratebox.contains(kursor.getPosition()))
					blok=CRATE;
			}	

		if(Keyboard::isKeyPressed(Keyboard::LControl) and Keyboard::isKeyPressed(Keyboard::S))
		{
			for(int i=0; i<15; i++)
			{
				for(int j=0; j<25; j++)
				{
					std::cout<<mapa[i][j].blok;
					if(j!=24)std::cout<<" ";
				}
				if(i!=14)std::cout<<"\n";
			}
			break;
		}

		Window.draw(floor);
		Window.draw(wall);
		Window.draw(left);
		Window.draw(right);
		Window.draw(crate);
		Window.draw(kursor);

		Window.display();
		Window.clear();
	
	}
	
}
