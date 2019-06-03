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
	for (int i = 0; i < cells_in_column * cells_in_row; i++)
	{
		pieces.push_back(nullptr);
	}
}

void Game::AddPiece(Piece * piece)
{
	pieces[GetCellId_X(piece->x)+ GetCellId_Y(piece->y)*cells_in_row] = piece;
}

void Game::Update(DirectX::Mouse::ButtonStateTracker * mouse_info, DirectX::Mouse * mouse)
{
	for (int i = 0; i < pieces.size(); i++)
	{
		if (pieces[i] != nullptr)
		{
			if (pieces[i]->object->Update(mouse_info, mouse))
				OnMove(i);
		}
	}
}

void Game::Draw()
{
	for (int i = 0; i < pieces.size(); i++)
	{
		if (pieces[i] != nullptr)
		{
			pieces[i]->object->Draw();
		}
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
		if (pieces[i] != nullptr)
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

	pieces[x + y * cells_in_row] = pieces[piece_id];
	pieces[piece_id] = nullptr;

	ChangePlayer();
}

bool Game::ValidateMove(std::string move_formula, int piece_id)
{
	int dst_x = GetCellId_X(pieces[piece_id]->object->GetX());
	int dst_y = GetCellId_Y(pieces[piece_id]->object->GetY());
	int src_x = GetCellId_X(pieces[piece_id]->x);
	int src_y = GetCellId_Y(pieces[piece_id]->y);
	int x_shift = dst_x - src_x;
	int y_shift = dst_y - src_y;

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
		std::tie(n, e, s, w) = GetRelativeDirection(direction, 180*!pieces[piece_id]->white);
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
			{
				if(!CollisionDetected(src_x, src_y, dst_x ,dst_y))
					ret = true;
			}
				
		}
	}
	return ret;
}

bool Game::CollisionDetected(int src_x, int src_y, int dst_x, int dst_y)
{
	bool str_dgn = true;
	int x_shift = dst_x - src_x;
	int y_shift = dst_y - src_y;
	if (abs(x_shift) == abs(y_shift))
		str_dgn = false;

	int distance = abs(x_shift - y_shift)*str_dgn + abs(x_shift) * !str_dgn;

	

	for (int i = 0; i < distance -1; i++)
	{
		x_shift = x_shift + 1*(x_shift != 0) -2*(x_shift > 0);
		y_shift = y_shift + 1 * (y_shift != 0) - 2 * (y_shift > 0);
		auto u = pieces[src_x + x_shift + (src_y + y_shift)*cells_in_row];
		if (pieces[src_x + x_shift + (src_y + y_shift)*cells_in_row] != nullptr)
			return true;
	}
	return false;
}


void Game::ChangePlayer()
{
	turn++;
	for (int i = 0; i < pieces.size(); i++)
	{
		if (pieces[i] != nullptr)
		{
			pieces[i]->object->SetDragable(!pieces[i]->object->GetDragable());
		}
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

std::tuple<bool, bool, bool, bool> Game::GetRelativeDirection(int binary_direction, double rotation)
{
	bool ret[4];

	int add = ((int)rotation+45)/90;
	add = abs(add);

		ret[(3+add)%4] = binary_direction - 8 >= 0;
		ret[(2 + add) % 4] = binary_direction - (8 * ret[(3 + add) % 4]) - 4 >= 0;
		ret[(1 + add) % 4] = binary_direction - (8 * ret[(3 + add) % 4]) - (4 * ret[(2 + add) % 4]) - 2 >= 0;
		ret[add % 4] = binary_direction % 2 == 1;

	return std::tuple<bool, bool, bool, bool>(ret[0], ret[1], ret[2], ret[3]);
}

