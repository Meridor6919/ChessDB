#pragma once
#include "Object.h"
#include "Piece_type.h"

struct Piece
{
	std::shared_ptr<Object> object;
	std::shared_ptr <Piece_type> piece_type;
	int x;
	int y;
	bool white;

	Piece(std::shared_ptr<Object> object, std::shared_ptr <Piece_type> piece_type, bool white)
	{
		this->object = object;
		this->piece_type = piece_type;
		this->white = white;
		this->x = object->GetX();
		this->y = object->GetY();
	}
};

