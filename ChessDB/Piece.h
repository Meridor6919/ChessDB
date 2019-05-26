#pragma once
#include "Object.h"
#include "Piece_type.h"

struct Piece
{
	Object* object;
	Piece_type *piece_type;
	int x;
	int y;
	bool white;

	Piece(Object* object, Piece_type* piece_type, bool white, int x, int y)
	{
		this->object = object;
		this->piece_type = piece_type;
		this->white = white;
		this->x = x;
		this->y = y;
	}
};

