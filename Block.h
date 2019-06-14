#pragma once
#include <SFML\Graphics.hpp>
#ifndef _BLOCK_H_

#define _BLOCK_H_

class Block
{
public:
	Block();
	sf::Sprite spr1;
	sf::Sprite spr2;
	void put(sf::Texture* &image, int X, int Y, short int length);

	int x;
	int y;

	short int part;
	short int length;
};

#endif