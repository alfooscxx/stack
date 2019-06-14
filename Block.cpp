#include "Block.h"

Block::Block()
{
}

void Block::put(sf::Texture* &image, int X, int Y, short int length)
{
	spr1.setTexture(*image);
	spr2.setTexture(*image);
	spr2.setTextureRect(sf::IntRect(0, 0, 0, 0));
	this->x = X;
	this->y = Y;
	this->length = length;
}