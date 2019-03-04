#include "SFML/Graphics.hpp"
#include "bits/stdc++.h"
#include "functions.hpp"
#include "player.hpp"
#include "weapons.hpp"
#include "crates.hpp"
using namespace sf;
const int tsize=45;

const float PI=3.141592654;
float DEGTORAD = 0.017453f;

const int W=25*tsize, H=tsize*15;
int mapa[100][100], dur, wyn, poprz_pos, ilosc_skrzyn;

play player;

void dbg()
{
	for(int i=0; i<15; i++)
	{
		for(int j=0; j<25; j++)
			std::cout<<mapa[i][j]<<" ";
		std::cout<<"\n";
	}
}

int main()
{
	srand(time(0));
	RenderWindow Window( VideoMode( W, H), "scb" );

	Font font;
	font.loadFromFile("Blockletter.otf");
	Text score;
	score.setFont(font);
	score.setPosition(600, 200);

	CircleShape wybuch;
	wybuch.setRadius(140);
	wybuch.setFillColor(Color::Red);
	wybuch.setOutlineColor(Color::Red);

	FloatRect okno=FloatRect(0, 0, W+1000, H);   
    Window.setVerticalSyncEnabled(1); 
    Window.setFramerateLimit(59); 
	player.obraz.setPosition(400, 101);
	wczytaj(Window, mapa);

	ilosc_skrzyn = pre(mapa);
	std::cout<<ilosc_skrzyn;

//////DEKLARACJE//////
	Sprite bck; Texture bcktex;
	if(bcktex.loadFromFile("images/bck.png"))bck.setTexture(bcktex);

	//dodaj_punkty_default();

	Clock clock;
	Time time;

	Crate crate;
	Vector2f poprz=player.getPos();
	bool LP=1, allowjump=1, allowshot=1, spawn=1;
	int bron_id=0;
	przypisz_bron(Window, player, 1, 0, 0);
	//dbg(mapa);

	
	while(Window.isOpen())/////////////////////////////////////////////////////
	{
		//if(player.ragdoll)return 0;
		Window.draw(bck);
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
		int dir=0;
		bool jump=0, shot=0;
		if(player.speed.y==0)allowjump=1;
		else allowjump=0;

	//////KLAWIATURA//////////
		if(!player.ragdoll){
		if(Keyboard::isKeyPressed(Keyboard::Numpad4) or Keyboard::isKeyPressed(Keyboard::Left))
			{FlipLeft(player.obraz, player.getBounds().width, player.getBounds().height); dir=1; LP=0;}

		if(Keyboard::isKeyPressed(Keyboard::Numpad6) or Keyboard::isKeyPressed(Keyboard::Right))
			{FlipRight(player.obraz, player.getBounds().width, player.getBounds().height);dir=2;LP=1;}

		if((Keyboard::isKeyPressed(Keyboard::Numpad8) or Keyboard::isKeyPressed(Keyboard::Up)) and allowjump)  
			jump=1;
	
		if(Keyboard::isKeyPressed(Keyboard::Space) and allowshot)
			{ shot=1;allowshot=0;}

		if(!Keyboard::isKeyPressed(Keyboard::Space))
			allowshot=1;
		}

	//////////RUCH KOLIZJE
		if(!player.ragdoll)
		{
			ruszaj(player, dir, jump);
			player.obraz.move(player.speed);
			drawcollide(Window, player, dir, wybuch, dur);

				/////////STRZAŁY BRONIE SKRZYNKI
			if(wyn==0)	przypisz_bron(Window, player, LP, 0, shot);
			else		przypisz_bron(Window, player, LP, bron_id, shot);
			przeciwniki((int)rand()%180,(int)rand()%770, Window, (int)time.asMilliseconds());		
			std::ostringstream ss;	
			ss<<wyn;
			score.setString(ss.str());
			rakiety_bulety(okno, LP, Window, bron_id);
			Window.draw(crate.obraz);		
		}		
		if(dur>0)dur--;



		if(crate.getBounds().intersects(player.getBounds()))
		{
			if(!player.ragdoll)
				wyn++;
			spawn=1;
		}

		if(spawn && !player.ragdoll)
		{
			int randzik=rand()%ilosc_skrzyn;
			while(randzik==poprz_pos)
				randzik=rand()%ilosc_skrzyn;
			poprz_pos=randzik;
			
			

			crate.spawn(getPointToSpawn(randzik));
			int c=bron_id;
			while(bron_id==c)
				bron_id=((int)rand()%5)+1;
			spawn=0;
		}			

		if(dur>0)
			Window.draw(wybuch);
	

		if(koniec(player))
		{
			player.ragdoll=1;
			player.speed.y=-10;
			std::ostringstream ss;	
			ss<<wyn;
			score.setString("Twoj wynik to: " + ss.str() + "\nwcisnij klawisz R aby zrestartowac gre");
		}

		kolizje_dmg(wybuch, dur);

		if(player.ragdoll){
			player.obraz.setRotation(player.obraz.getRotation()+5);
			player.speed.y+=gravity;
			player.obraz.move(0, player.speed.y);	
		}

		Window.draw(score);

		player.drawTo(Window);

		Window.display();
		Window.clear();
	
		if(Keyboard::isKeyPressed(Keyboard::R) && player.ragdoll)
		{
			bron_id = 0;
			wyn = 0;
			przypisz_bron(Window, player, 1, 0, 0);
			player.reset();
			player.ragdoll = 0;
		}
	}
}
