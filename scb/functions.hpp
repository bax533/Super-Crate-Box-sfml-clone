#pragma once
#include"bits/stdc++.h"
#include"SFML/Graphics.hpp"
#include"player.hpp"
#include"weapons.hpp"
#include"enemys.hpp"
using namespace sf;
///////PARAMETRY///////////////////

const Vector2f granat_speed=Vector2f(8.0f, -7.0f);
const int spid=7, vert=17, ts=45;
const float gravity=0.677;
//////////////////////////////////
std::vector<Small> mali;
std::vector<Big>   duzi;
std::vector<std::pair<Sprite, int> > tiles;
std::vector<Texture> textures;
std::vector<Vector2f> points;

Rocket rocket;
Granade granat;
std::vector<Bullet> bullets;

enum bronie
{
PISTOL, 	  
DUAL  , 	  
MINIGUN	  ,
BAZOOKA   ,
REVOLVER  ,
GRANAT    
};

int pre(int mapa[100][100])
{
	Texture floortex, walltex, trzytex; Sprite floor, wall, trzy;
	floortex.loadFromFile("images/floor.png");walltex.loadFromFile("images/wall.png"); trzytex.loadFromFile("images/trzy.png");
	wall.setTexture(walltex); floor.setTexture(floortex); trzy.setTexture(trzytex);
	textures.push_back(floortex);textures.push_back(walltex);textures.push_back(trzytex);textures.push_back(trzytex);
	int skrzynie = 0;

	for(int i=0;i<15; i++)
	{
		for(int j=0; j<25; j++)
		{
			if(mapa[i][j]==1)
			{
				floor.setPosition(j*ts, i*ts);
				tiles.push_back(std::make_pair(floor, 1));
			}
			else if(mapa[i][j]==2)
			{
				wall.setPosition(j*ts, i*ts);
				tiles.push_back(std::make_pair(wall, 2));	
			}
			else if(mapa[i][j]!=0)
			{
				if(mapa[i][j]==3)
				{
					trzy.setPosition(j*ts, i*ts);
					tiles.push_back(std::make_pair(trzy, 3));
				}
				else if(mapa[i][j]==4)
				{
					trzy.setPosition(j*ts+35, i*ts);
					tiles.push_back(std::make_pair(trzy, 4));
				}
				else if(mapa[i][j]==5)
				{
					skrzynie+=1;
					points.push_back(Vector2f(j*ts, i*ts)); 
				}
			}
		}
	}	
	return skrzynie;
}

void FlipLeft(Sprite &sprite, float width, float height)
{
	sprite.setTextureRect(IntRect(width, 0, -width, height));
}
void FlipRight(Sprite &sprite, float width, float height)
{
	sprite.setTextureRect(IntRect(0, 0, width, height));
}

Vector2f getPointToSpawn(int nr)
{
	return points[nr];
}

void podloga(Sprite tile, play &player)
{
	FloatRect rect=tile.getGlobalBounds(), bob=player.getBounds();
	Vector2f pos=player.getPos();	
	player.obraz.setOrigin(0, 37);
	if(bob.intersects(rect))
	{
		if(player.speed.y<0){player.obraz.setPosition(player.getPos().x, tile.getPosition().y+ts+37); player.speed.y=0.5f;}
		else {player.obraz.setPosition(player.getPos().x, tile.getPosition().y); player.speed.y=0;}
	}
}

void sciana(Sprite tile, play &player, int dir)
{
	FloatRect rect=tile.getGlobalBounds(), bob=player.getBounds();
	Vector2f pos=player.getPos();	
	player.obraz.setOrigin(0, 37);
	if(bob.intersects(rect))
	{
		if(dir==1)player.obraz.setPosition(tile.getPosition().x+ts, player.getPos().y);
		else player.obraz.setPosition(tile.getPosition().x-37, player.getPos().y);

		player.speed.x=0;
	}
}
void cienkasciana(Sprite tile, play &player, int dir,int nr)
{
	FloatRect rect=tile.getGlobalBounds(), bob=player.getBounds();
	Vector2f pos=player.getPos();	
	player.obraz.setOrigin(0, 37);
	if(bob.intersects(rect))
	{
		if(nr==4 and dir==2)
			player.obraz.setPosition(tile.getPosition().x-37, player.getPos().y);
		else if(nr==3 and dir==1)
			 player.obraz.setPosition(tile.getPosition().x+10, player.getPos().y);

		player.speed.x=0;
	}
}
// ^^^^^^^^^ KOLIZJE ^^^^^^^^^^
// |||||||||         ||||||||||


void ruszaj(play &player, int dir, bool jump)
{
	if(dir==1) 		player.speed.x=-spid;
	else if(dir==2)	player.speed.x=spid;
	else  			player.speed.x=0;

	if(jump and player.speed.y==0)	player.speed.y=-vert;
	player.speed.y+=gravity;
}



void wczytaj(RenderWindow &window, int mapa[100][100])
{
	std::ifstream openfile("levels/1.txt");

	int countx=0, county=0;

	if(openfile.is_open())
	{
		while(!openfile.eof())
		{
			std::string str;
			openfile>>str;
			char x=str[0];

			if(!isdigit(x))	mapa[county][countx]=0;
			else			mapa[county][countx]=x-'0';

			if(openfile.peek()=='\n')
			{
				county++;
				countx=0;
			}
			else countx++;
		}	
	}
}

void drawcollide(RenderWindow &window, play &player, int dir, CircleShape &wybuch, int &dur)
{
	
	for(int i=0; i<tiles.size(); i++)
	{
		tiles[i].first.setTexture(textures[tiles[i].second-1]);
		window.draw(tiles[i].first);
		if(tiles[i].second==1)			podloga(tiles[i].first, player);
		else if(tiles[i].second==2)		sciana(tiles[i].first, player, dir);	
		else if(tiles[i].second==3)		cienkasciana(tiles[i].first, player, dir, 3);
		else if(tiles[i].second==4)		cienkasciana(tiles[i].first, player, dir, 4);

			FloatRect box=rocket.getBounds();
			if(box.intersects(tiles[i].first.getGlobalBounds()))
			{
				wybuch.setPosition(tiles[i].first.getPosition().x-140,tiles[i].first.getPosition().y-140);
				dur=15;
				//window.draw(wybuch);
				rocket.obraz.setPosition(9999, 9999);
			}
			FloatRect gran=granat.getBounds();
			if(gran.intersects(tiles[i].first.getGlobalBounds()) and granat.rzucony)
			{
				if(tiles[i].second==1)
				{
					granat.speed.y*=-1;
					if(granat.speed.y<=0)
						granat.obraz.setPosition(granat.getPos().x, tiles[i].first.getPosition().y-25);
					else
						granat.obraz.setPosition(granat.getPos().x, tiles[i].first.getPosition().y+65);
				}	
				else 
				{
					granat.speed.x*=-1;
					//granat.kierunek*=-1;
					if(granat.speed.x<=0)
						granat.obraz.setPosition(tiles[i].first.getPosition().x-15, granat.getPos().y);
					else
						granat.obraz.setPosition(tiles[i].first.getPosition().x+65, granat.getPos().y);
				}
				
				
			}
			if(std::abs(granat.speed.x)<0.3f)
			{
				wybuch.setPosition(granat.getPos().x-140, granat.getPos().y-140);
				dur=15;
				granat.reset();
				//granat.obraz.setPosition(player.getPos());
			}
	}	
}

void przypisz_bron(RenderWindow &window,play &player, bool LP, int bron_id, bool shot)//////////////////////////////////////////////////////////
{////////////////////PRZYPISYWANIE BRONI//////////////////////////////////
	switch(bron_id)
	{
		case PISTOL:
		{
			Pistol pistol;
			if(!LP)
			{
				pistol.obraz.setPosition(player.getPos().x-14, player.getPos().y-22);
				FlipLeft(pistol.obraz, pistol.getBounds().width, pistol.getBounds().height);
			}
			else
			{
				pistol.obraz.setPosition(player.getPos().x+30, player.getPos().y-22);
				FlipRight(pistol.obraz, pistol.getBounds().width, pistol.getBounds().height);
			}
			window.draw(pistol.obraz);
			if(shot)
			{
				Bullet bullet;
				bullet.obraz.setPosition(pistol.getPos());
				if(!LP)bullet.speed.x*=-1;
				bullets.push_back(bullet);
			}
		}
			break;
		case DUAL:
		{
			Dual dual;
			dual.obraz.setPosition(player.getPos().x-25, player.getPos().y-22);
			window.draw(dual.obraz);
			if(shot)
			{
				Bullet bullet1, bullet2;
				bullet1.obraz.setPosition(player.getPos().x-10, player.getPos().y-22);
				bullet2.obraz.setPosition(player.getPos().x+20, player.getPos().y-22);
				bullet1.speed.x*=-1;
				bullets.push_back(bullet1);bullets.push_back(bullet2);
			}
		}			
			break;
		case MINIGUN:
		{
			Minigun mini;
			if(!LP)
			{
				mini.obraz.setPosition(player.getPos().x-33, player.getPos().y-32);
				FlipLeft(mini.obraz, mini.getBounds().width, mini.getBounds().height);
			}
			else
			{
				mini.obraz.setPosition(player.getPos().x+30, player.getPos().y-32);
				FlipRight(mini.obraz, mini.getBounds().width, mini.getBounds().height);
			}
			window.draw(mini.obraz);
			if(Keyboard::isKeyPressed(Keyboard::Space))
			{
				Bullet bullet;
				bullet.dmg=0.25;bullet.speed.y=rand()%5-2;
				bullet.obraz.setPosition(mini.getPos().x, mini.getPos().y+20);
				if(!LP){bullet.speed.x*=-1;player.obraz.move(3, 0);}
				else {player.obraz.move(-3, 0);bullet.obraz.setPosition(bullet.getPos().x+45, bullet.getPos().y);}

				bullets.push_back(bullet);
			}
		}
			break;
		case BAZOOKA:
		{
			Bazooka bazooka;
			if(!LP)
			{
				bazooka.obraz.setPosition(player.getPos().x-33, player.getPos().y-32);
				FlipLeft(bazooka.obraz, bazooka.getBounds().width, bazooka.getBounds().height);
			}
			else
			{
				bazooka.obraz.setPosition(player.getPos().x+30, player.getPos().y-32);
				FlipRight(bazooka.obraz, bazooka.getBounds().width, bazooka.getBounds().height);
			}
			window.draw(bazooka.obraz);
			FloatRect okno=FloatRect(0, 0, 990, 675);
			if(shot and !okno.contains(rocket.getPos()))
			{
				rocket.reset();
				rocket.obraz.setPosition(bazooka.getPos());
				if(!LP) {rocket.speed.x*=-1;FlipLeft(rocket.obraz, rocket.getBounds().width, rocket.getBounds().height);}
				else 	{rocket.speed.x=0.5;FlipRight(rocket.obraz, rocket.getBounds().width, rocket.getBounds().height);}
			}
		}
			break;
		case REVOLVER:
		{
			Revolver rev;
			if(!LP)
			{
				rev.obraz.setPosition(player.getPos().x-25, player.getPos().y-30);
				FlipLeft(rev.obraz, rev.getBounds().width, rev.getBounds().height);
			}
			else
			{
				rev.obraz.setPosition(player.getPos().x+35, player.getPos().y-30);
				FlipRight(rev.obraz, rev.getBounds().width, rev.getBounds().height);
			}
			window.draw(rev.obraz);
			if(shot)
			{
				Bullet bullet;
				bullet.obraz.setPosition(rev.getPos());
				bullet.obraz.setScale(1.5, 1.5);
				bullet.dmg=2;
				if(!LP)bullet.speed.x*=-1;
				bullets.push_back(bullet);
			}
		}
			break;
		case GRANAT:
		{
			//Granade granat;
			if(!granat.rzucony)
			{
				if(!LP)
				{
					granat.obraz.setPosition(player.getPos().x, player.getPos().y-30);
					FlipLeft(granat.obraz, granat.getBounds().width, granat.getBounds().height);
					granat.speed.x=-8.0f;
				}
				else
				{
					granat.obraz.setPosition(player.getPos().x+35, player.getPos().y-30);
					FlipRight(granat.obraz, granat.getBounds().width, granat.getBounds().height);
					granat.speed.x=8.0f;
				}
				
				if(shot)
				{	granat.rzucony=1;// granat.speed=granat_speed;
				}	
			}
			window.draw(granat.obraz);
		}
			break;
	};
}//////////////////KONIEC PRZYPISYWANIA BRONI//////////////////////

void przeciwniki(int r_mali, int r_duzi, RenderWindow &window, int fr)
{
	Small maly;
	Big duzy;
	if(r_mali<2)
	{
		maly.spawn((int)rand()%2);
		mali.push_back(maly);
	}
	if(r_duzi<2)
	{
		duzy.spawn((int)rand()%2);
		duzi.push_back(duzy);
	}
	

	FloatRect okno=FloatRect(0, 0, 990, 675);

	for(int i=0; i<mali.size(); i++)
	{
		if(mali[i].angry)mali[i].obraz.setTexture(mali[i].redtex);
		else 			 mali[i].obraz.setTexture(mali[i].greentex);
		mali[i].move(tiles);
		mali[i].pocisk(bullets);
		//if(okno.contains(mali[i].getPos()))
			window.draw(mali[i].obraz);

		if(mali[i].life<=0 and !mali[i].ragdoll)
		{
			mali[i].ragdoll=1;
			mali[i].speed.y=-10;
		}	
		else if(mali[i].ragdoll)
			mali[i].obraz.setRotation(mali[i].obraz.getRotation()+5);
		
		if(mali[i].ragdoll && !okno.contains(mali[i].obraz.getPosition()))
		{
			std::swap(mali[i], mali[mali.size()-1]);
			mali.pop_back();		
		}

		if(mali[i].getPos().y>670)
		{
			mali[i].angry=1;
			mali[i].spawn(rand()%2);
		}
	}

	for(int i=0; i<duzi.size(); i++)
	{
		if(duzi[i].angry)duzi[i].obraz.setTexture(duzi[i].redtex);
		else			 duzi[i].obraz.setTexture(duzi[i].greentex);
	//	duzi[i].setTex(fr);
		duzi[i].move(tiles);
		duzi[i].pocisk(bullets);

		//if(okno.contains(duzi[i].getPos()))
			window.draw(duzi[i].obraz);

		if(duzi[i].life<=0 and !duzi[i].ragdoll)
		{
			duzi[i].ragdoll=1;
			duzi[i].speed.y=-10;
			duzi[i].gravity=0.667f;
		}	
		else if(duzi[i].ragdoll)
			duzi[i].obraz.setRotation(duzi[i].obraz.getRotation()+5);
	
		if(duzi[i].ragdoll && !okno.contains(duzi[i].obraz.getPosition()))
		{
			std::swap(duzi[i], duzi[duzi.size()-1]);
			duzi.pop_back();		
		}

		if(duzi[i].getPos().y>670)
		{	
			duzi[i].angry=1;
			duzi[i].spawn(rand()%2);
		}
	}
}

void kolizje_dmg(CircleShape &wybuch, int &dur)
{
	/*for(int i=0; i<mali.size(); i++)
	{
		for(int j=0; j<bullets.size(); j++)
		{
			FloatRect box=bullets[j].getBounds();
			if(box.intersects(mali[i].obraz.getGlobalBounds()))
			{
				mali[i].life-=bullets[j].dmg;
				bullets[j].obraz.setPosition(99999, 99999);
				std::swap(bullets[j], bullets[bullets.size()-1]);
				bullets.pop_back();
			}
		}*/
	for(int i=0; i<mali.size(); i++)
	{

		FloatRect box=rocket.getBounds();
		if(box.intersects(mali[i].obraz.getGlobalBounds()) and !mali[i].ragdoll and rocket.drawable)
		{
			wybuch.setPosition(mali[i].getPos().x-140, mali[i].getPos().y-140);
			dur=15;
			rocket.drawable=0;
		}

		if(granat.rzucony and granat.getBounds().intersects(mali[i].getBounds()))
		{
				wybuch.setPosition(granat.getPos().x-140, granat.getPos().y-140);
				dur=15;
				granat.reset();
		}

		if(wybuch.getGlobalBounds().intersects(mali[i].getBounds()) and dur>0)
			mali[i].life=0;
	}

	for(int i=0; i<duzi.size(); i++)
	{

		FloatRect box=rocket.getBounds();
		if(box.intersects(duzi[i].getBounds()) and !duzi[i].ragdoll and rocket.drawable)
		{
			wybuch.setPosition(duzi[i].getPos().x-140, duzi[i].getPos().y-140);
			dur=15;
			rocket.drawable=0;
		}
		
		if(granat.rzucony and granat.getBounds().intersects(duzi[i].getBounds()))
		{
				wybuch.setPosition(granat.getPos().x-140, granat.getPos().y-140);
				dur=15;
				granat.reset();
		}

		if(wybuch.getGlobalBounds().intersects(duzi[i].getBounds()) and dur>0)
			duzi[i].life=0;

	}
}

void rakiety_bulety(FloatRect okno, bool LP, RenderWindow &window, int bron_id)
{
		Bullet bullet;

		rocket.obraz.setTexture(rocket.tex);
		if(rocket.speed.x<25 and rocket.speed.x>-25)rocket.speed.x*=1.2f;
		if(rocket.drawable)	rocket.obraz.move(rocket.speed);
		if(okno.contains(rocket.getPos()) and rocket.drawable)
		{	
			window.draw(rocket.obraz);
			rocket.zadyma(1, window);
		}
		else if(rocket.dymy.size()>2)
		{
			rocket.zadyma(0, window);
			rocket.obraz.setPosition(99999, 99999);
		}
		else
		{
			//
		}

		for(int i=0; i<bullets.size(); i++)
		{
			bullets[i].obraz.setTexture(bullet.tex);
			bullets[i].obraz.move(bullets[i].speed);
			if(okno.contains(bullets[i].getPos()))
				window.draw(bullets[i].obraz);
			else
			{
				bullets[i].obraz.setPosition(99999, 99999);
				bullets[i].speed=Vector2f(0, 0);
				std::swap(bullets[i], bullets[bullets.size()-1]);
				bullets.pop_back();
			}
		}


		if(granat.rzucony)
		{
			granat.obraz.setRotation(granat.obraz.getRotation()+10);
			if(granat.speed.x<=0)granat.speed.x+=0.05f;
			else 				granat.speed.x-=0.05f;

			if(granat.speed.y<0)						
				granat.speed.y+=gravity;
			else
				granat.speed.y+=(gravity/2);

			granat.obraz.move(granat.speed);
		//	window.draw(granat.obraz);
		}

//		if()
}

bool koniec(play &player)
{
	bool c=0;
	for(int i=0; i<mali.size();i++)
		if(player.getBounds().intersects(mali[i].getBounds()) and !mali[i].ragdoll)
		{c=1; break;}

	if(!c)
	for(int i=0; i<duzi.size();i++)
		if(player.getBounds().intersects(duzi[i].getBounds()) and !duzi[i].ragdoll)
		{c=1; break;}

	if(c)
	{
		while(mali.size()>0)mali.pop_back();
		std::cout<<mali.size();
		/*for(int i=0;i<mali.size(); i++)
			free(&mali[i]);*/
	
		while(duzi.size()>0)duzi.pop_back();
		/*for(int i=0;i<duzi.size(); i++)
			free(&duzi[i]);*/
		return 1;
	}


	return 0;
}


