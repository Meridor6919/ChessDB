#pragma once
#include "Piece.h"
#include <vector>
#include <Windows.h>
#include <fstream>

class Game
{
	std::vector<Piece*> pieces;
	RECT grid_rect;
	int cells_in_row;
	int cells_in_column;

	int turn = 0;

public:

	Game();
	void AddPiece(Piece* piece);
	void Update(DirectX::Mouse::ButtonStateTracker* mouse_info, DirectX::Mouse * mouse);
	void Draw();
	void ValidateMove(int piece_id);
	void MovePiece(int piece_id);
	void ChangePlayer();
	int GetCellId_X(int piece_id);
	int GetCellId_Y(int piece_id);

	RECT GetGridRect() { return grid_rect; }
	int GetCellsInRow() { return cells_in_row; }
	int GetCellsInColumn() { return cells_in_column; }
};

