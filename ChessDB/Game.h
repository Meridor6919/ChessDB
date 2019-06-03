#pragma once
#include "Piece.h"
#include <vector>
#include <Windows.h>
#include <fstream>
#include <tuple>

class Game
{
	std::vector<Piece*> pieces;
	RECT grid_rect;
	int cells_in_row;
	int cells_in_column;

	int turn = 0;

	void OnMove(int piece_id);
	void MovePiece(int piece_id);
	bool ValidateMove(std::string move_formula, int piece_id);
	bool CollisionDetected(int src_x, int src_y, int dst_x, int dst_y);
	void ChangePlayer();
	int GetCellId_X(int x);
	int GetCellId_Y(int y);
	std::tuple<bool, bool, bool, bool> GetRelativeDirection(int binary_direction, double rotation);

public:

	Game();
	void AddPiece(Piece* piece);
	void Update(DirectX::Mouse::ButtonStateTracker* mouse_info, DirectX::Mouse * mouse);
	void Draw();

	RECT GetGridRect() { return grid_rect; }
	int GetCellsInRow() { return cells_in_row; }
	int GetCellsInColumn() { return cells_in_column; }
};

