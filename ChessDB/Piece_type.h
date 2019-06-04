#pragma once
#include <string>
#include <Windows.h>

struct Piece_type
{
	int id;
	std::string move_formula;
	std::string attack_formula;
	bool essential;
	bool double_move;
	bool promotion;
	bool immortal;
	std::string image_path;
	RECT white;
	RECT black;

	Piece_type(int id,	std::string move_formula, std::string attack_formula, std::string specials, std::string image_path, RECT white, RECT black)
	{
		this->id = id;
		this->move_formula = move_formula;
		this->attack_formula = attack_formula;
		this->image_path = image_path;
		this->white = white;
		this->black = black;

		int specials_int = strtoul(specials.c_str(), NULL, 16);
		immortal = specials_int - 8 >= 0;
		promotion = specials_int - (8 * immortal) - 4 >= 0;
		double_move = specials_int - (8 * immortal) - (promotion) - 2 >= 0;
		essential = specials_int % 2 == 1;
		
	}
};

