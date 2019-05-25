#pragma once
#include <string>
#include <Windows.h>

struct Piece_type
{
	int id;
	std::string move_formula;
	std::string attack_formula;
	std::string image_path;
	RECT white;
	RECT black;

	Piece_type(int id,	std::string move_formula, std::string attack_formula, std::string image_path, RECT white, RECT black)
	{
		this->id = id;
		this->move_formula = move_formula;
		this->attack_formula = attack_formula;
		this->image_path = image_path;
		this->white = white;
		this->black = black;
	}
};

