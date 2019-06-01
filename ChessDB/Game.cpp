#include "Game.h"



Game::Game()
{
	std::fstream fvar;
	std::string line;
	fvar.open("settings\\general.txt", std::ios::in);

	for (int i = 0; std::getline(fvar, line); i++)
	{
		switch (i)
		{
			case 0:
			{
				grid_rect.left = atoi(line.c_str());
			}
			case 1:
			{
				grid_rect.top = atoi(line.c_str());
			}
			case 2:
			{
				grid_rect.right = atoi(line.c_str());
			}
			case 3:
			{
				grid_rect.bottom = atoi(line.c_str());
			}
			case 4:
			{
				cells_in_row = atoi(line.c_str());
			}
			case 5:
			{
				cells_in_column = atoi(line.c_str());
			}
		}
	}
	std::vector<Piece*> pieces;
	pieces;
	this->pieces;
}

void Game::AddPiece(Piece * piece)
{
	
	pieces.push_back(piece);
}


void Game::Update(DirectX::Mouse::ButtonStateTracker * mouse_info, DirectX::Mouse * mouse)
{
	for (int i = 0; i < pieces.size(); i++)
	{
		if (pieces[i]->object->Update(mouse_info, mouse))
			OnMove(i);
	}
}

void Game::Draw()
{
	for (int i = 0; i < pieces.size(); i++)
	{
		pieces[i]->object->Draw();
	}
}

void Game::OnMove(int piece_id)
{
	int x = GetCellId_X(pieces[piece_id]->object->GetX());
	int y = GetCellId_Y(pieces[piece_id]->object->GetY());
	bool attacking = false;
	int target;
	std::string move_formula;

	//checking if attack performed
	for (int i = pieces.size() - 1; i >= 0; i--)
	{
		if (pieces[i]->x == grid_rect.left + x * grid_rect.right && pieces[i]->y == grid_rect.top + y * grid_rect.bottom)
		{
			if (pieces[i]->white == pieces[piece_id]->white)
			{
				pieces[piece_id]->object->SetX(pieces[piece_id]->x);
				pieces[piece_id]->object->SetY(pieces[piece_id]->y);
				return;
			}
			else
			{
				attacking = true;
				target = i;
			}
		}
	}
	if (attacking)
	{
		move_formula = pieces[piece_id]->piece_type->attack_formula;
	}
	else
	{
		move_formula = pieces[piece_id]->piece_type->move_formula;
	}

	if (ValidateMove(move_formula, piece_id))
	{
		MovePiece(piece_id);
		if (attacking)
		{
			if (target < piece_id)
				piece_id--;
			pieces.erase(pieces.begin() + target);
		}
	}
	else
	{
		pieces[piece_id]->object->SetX(pieces[piece_id]->x);
		pieces[piece_id]->object->SetY(pieces[piece_id]->y);
	}
}

void Game::MovePiece(int piece_id)
{
	int x = GetCellId_X(pieces[piece_id]->object->GetX());
	int y = GetCellId_Y(pieces[piece_id]->object->GetY());

	pieces[piece_id]->object->SetX(grid_rect.left + x * grid_rect.right);
	pieces[piece_id]->object->SetY(grid_rect.top + y * grid_rect.bottom);

	pieces[piece_id]->x = pieces[piece_id]->object->GetX();
	pieces[piece_id]->y = pieces[piece_id]->object->GetY();
	ChangePlayer();
}

bool Game::ValidateMove(std::string move_formula, int piece_id)
{
	int dst_x = GetCellId_X(pieces[piece_id]->object->GetX());
	int dst_y = GetCellId_Y(pieces[piece_id]->object->GetY());
	int src_x = GetCellId_X(pieces[piece_id]->x);
	int src_y = GetCellId_Y(pieces[piece_id]->y);
	int x_shift = GetCellId_X(pieces[piece_id]->object->GetX()) - src_x;
	int y_shift = GetCellId_Y(pieces[piece_id]->object->GetY()) - src_y;

	bool ret = false;

	if (dst_x == src_x && dst_y == src_y)
	{
		return false;
	}
	else if(dst_x < 0 || dst_y < 0 || dst_x >= cells_in_row || dst_y >= cells_in_column)
	{
		return false;
	}
	for (int i = 0; i < move_formula.size(); i+=5)
	{
		bool str_dgn = atoi(((std::string)"" + move_formula[i]).c_str());
		int direction = strtoul(((std::string)""+ move_formula[i+1]).c_str(),NULL, 16);
		int distance = atoi(((std::string)"" + move_formula[i+2] + move_formula[i+3]).c_str());
		if (distance == 0)
			distance = INT_MAX;
		bool n, e, w, s;
		if (pieces[piece_id]->white)
		{
			w = direction - 8 >= 0;
			s = direction - (8 * w) - 4 >= 0;
			e = direction - (8 * w) - (4 * s) - 2 >= 0;
			n = direction % 2 == 1;
		}
		else
		{
			e = direction - 8 >= 0;
			n = direction - (8 * e) - 4 >= 0;
			w = direction - (8 * e) - (4 * n) - 2 >= 0;
			s = direction % 2 == 1;
		}
		if (move_formula[i + 4] == ';')
		{
			if ((bool)(x_shift*y_shift) == (bool)str_dgn)
				continue;
			else if (!str_dgn && abs(x_shift) != abs(y_shift))
				continue;
			else if (x_shift >= 0 && y_shift > 0 && !n)
				continue;
			else if (x_shift > 0 && y_shift <= 0 && !e)
				continue;
			else if (x_shift <= 0 && y_shift < 0 && !s)
				continue;
			else if (x_shift < 0 && y_shift >= 0 && !w)
				continue;
			else if (x_shift >= 0 && y_shift > 0 && !n)
				continue;
			else if (abs(x_shift - y_shift)*str_dgn+abs(x_shift)*!str_dgn > distance)
				continue;
			else
				ret = true;
		}
	}
	return ret;
}

void Game::ChangePlayer()
{
	turn++;
	for (int i = 0; i < pieces.size(); i++)
	{
		pieces[i]->object->SetDragable(!pieces[i]->object->GetDragable());
	}
}

int Game::GetCellId_X(int x)
{
	return (x - (grid_rect.left - grid_rect.right/2)) / 90;
}

int Game::GetCellId_Y(int y)
{
	return (y - (grid_rect.top - grid_rect.bottom/ 2)) / 90;
}

