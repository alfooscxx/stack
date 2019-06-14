#include <SFML\Graphics.hpp>
#include <vector>
#include "view.h"
#include <sstream>

using namespace sf;

#include"Block.h"
std::vector <Block> b(1);

inline void update()
{
	static bool right;
	if (b.back().x >= 591 - b.back().length)
		right = false;
	if (b.back().x <= 9)
		right = true;
	if (right)
		b.back().x += 1;
	else
		b.back().x -= 1;
	b.back().spr1.setPosition(b.back().x, b.back().y);
	b.back().spr2.setPosition(b.back().x, b.back().y);
}

unsigned short int color = 2;

Texture* atlas;

inline void newBlock()
{
	b.push_back(Block());
	b.back().spr1.setTextureRect(IntRect((color - 1) * 200, 0, b[b.size() - 2].length, 100 ));
	if (b.size() % 2)
	{
		b.back().put(atlas, 0, b[b.size() - 2].y - 170, b[b.size() - 2].length);
	}
	else
	{
		b.back().put(atlas, 600 - b[b.size() - 2].length, b[b.size() - 2].y - 170, b[b.size() - 2].length);
	}
	b.back().spr1.setPosition(b.back().x, b.back().y);
	if (b.size() > 5)
		view.setCenter(300, b[b.size() - 2].y + 50);
	color++;
	if (color > 7)
		color = 1;
	b.back().length = b[b.size() - 2].length;
	
}
int main()
{
	atlas = new Texture;
	atlas->loadFromFile("resourses/blocks.png");
	RenderWindow window(VideoMode(600, 900), "Stack");
	view.reset(sf::FloatRect(0, 0, 600, 900));
	Event event;
	Font font;
	font.loadFromFile("resourses/11763.ttf");
	Text text("Score 0", font, 55);
	text.setColor(Color::White);
	text.setStyle(sf::Text::Bold);
	text.setPosition(420, 40);
	std::ostringstream score_stream;
	b[0].put(atlas, 200, 800, 200);
	b[0].spr1.setTextureRect(IntRect(0, 0, 200, 100));
	b[0].spr1.setPosition(200, 800);
	newBlock();
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				window.close();
			}
		}
		update();
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			if (b.back().x <= b[b.size() - 2].x - b.back().length|| b.back().x >= b[b.size() - 2].x + b.back().length)
			{
				while (b.back().y < 800)
				{
					b.back().y += 1;
					b.back().spr1.setPosition(b.back().x, b.back().y);
					window.clear();
					 for (int i = 0; i < b.size(); i++)
					{
						window.draw(b[i].spr1);
						window.draw(b[i].spr2);
					}
					window.draw(text);
					window.display();
				}
				window.close();
				exit(NULL);
			} 
			while (b.back().y < b[b.size() - 2].y - 100)
			{
				b.back().y += 1;      
				b.back().spr1.setPosition(b.back().x, b.back().y);
				window.clear();
				for (int i = 0; i < b.size(); i++)
				{
					window.draw(b[i].spr1);
					window.draw(b[i].spr2);
				}
				window.draw(text);
				window.display();
			}
			short int color2;
			if (color > 1)
				color2 = color - 2;
			else
				color2 = 6;

			if (b.back().x <= b[b.size() - 2].x)
			{
				b.back().part = b.back().length + b.back().x - b[b.size() - 2].x;
				b.back().spr1.setTextureRect(IntRect(color2 * 200 + b.back().length - b.back().part, 0, b.back().part, 100));
				b.back().spr2.setTextureRect(IntRect(color2 * 200, 0, b.back().length - b.back().part, 100));
				b.back().x = b[b.size() - 2].x;
				b.back().spr1.setPosition(b.back().x, b[b.size() - 2].y - 100);
				b.back().spr2.setPosition(b.back().x - b.back().length + b.back().part, b[b.size() - 2].y - 100);
				sleep(milliseconds(300));
				for (int i = b.size() - 3; i >= 0; i--)
				{
					if (b[i].x < b.back().x)
					{
						while (b.back().y < b[i].y - 100)
						{
							b.back().y += 1;
							b.back().spr2.setPosition(b.back().x - b.back().length + b.back().part, b.back().y);
							window.clear();
							for (int i = 0; i < b.size(); i++)
							{
								window.draw(b[i].spr1);
								window.draw(b[i].spr2);
							}
							window.draw(text);
							window.display();
						}
						break;
					}
				}
				if (b.back().y == b[b.size() - 2].y - 100)
				{
					while (b.back().y < 800)
					{
						b.back().y += 1;
						b.back().spr2.setPosition(b.back().x - b.back().length + b.back().part, b.back().y);
						window.clear();
						for (int i = 0; i < b.size(); i++)
						{
							window.draw(b[i].spr1);
							window.draw(b[i].spr2);
						}
						window.draw(text);
						window.display();
					}
				}
			}
			else
			{
				b.back().part = b.back().length - b.back().x + b[b.size() - 2].x;
				b.back().spr1.setTextureRect(IntRect(color2 * 200, 0, b.back().part, 100));
				b.back().spr2.setTextureRect(IntRect(color2 * 200 + b.back().part, 0, b.back().length - b.back().part, 100));
				b.back().spr1.setPosition(b.back().x, b[b.size() - 2].y - 100);
				b.back().spr2.setPosition(b[b.size() - 2].x + b.back().length, b[b.size() - 2].y - 100);
				sleep(milliseconds(300));
				for (int i = b.size() - 3; i >= 0; i--)
				{
					if (b[i].x + b[i].length > b.back().x + b.back().length)
					{
						while (b.back().y < b[i].y - 100)
						{
							b.back().y += 1;
							b.back().spr2.setPosition(b.back().x + b.back().part, b.back().y);
							window.clear();
							for (int i = 0; i < b.size(); i++)
							{
								window.draw(b[i].spr1);
								window.draw(b[i].spr2);
							}
							window.draw(text);
							window.display();
						}
						break;
					}
				}
				if (b.back().y == b[b.size() - 2].y - 100)
				{
					while (b.back().y < 800)
					{
						b.back().y += 1;
						b.back().spr2.setPosition(b.back().x + b.back().part, b.back().y);
						window.clear();
						for (int i = 0; i < b.size(); i++)
						{
							window.draw(b[i].spr1);
							window.draw(b[i].spr2);
						}
						window.draw(text);
						window.display();
					}
				}
			}
			b.back().y = b[b.size() - 2].y - 100;
			b.back().length = b.back().part;
			newBlock();
			text.setPosition(view.getCenter().x + 120, view.getCenter().y - 410);
			score_stream << b.size() - 2;
			text.setString("Score " + score_stream.str());
			score_stream.str("");
			sleep(milliseconds(500));
		}
		window.setView(view);
		window.clear();
		for (int i = 0; i < b.size(); i++)
		{
			window.draw(b[i].spr1);
			window.draw(b[i].spr2);
		}
		window.draw(text);
		window.display();
		sleep(milliseconds(2.8));
	}
	return 0;
}
