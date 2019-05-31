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
			ValidateMove(i);
	}
}

void Game::Draw()
{
	for (int i = 0; i < pieces.size(); i++)
	{
		pieces[i]->object->Draw();
	}
}

void Game::ValidateMove(int id)
{
	int x = GetCellId_X(id);
	int y = GetCellId_Y(id);
	bool attacking = false;
	int target;

	//if dragged outside grid
	if (x < 0 || y < 0 || x >= cells_in_row || y >= cells_in_column)
	{
		pieces[id]->object->SetX(pieces[id]->x);
		pieces[id]->object->SetY(pieces[id]->y);
		return;
	}

	//checking if attack performed
	for (int i = pieces.size() - 1; i >= 0; i--)
	{
		if (pieces[i]->x == grid_rect.left + x * grid_rect.right && pieces[i]->y == grid_rect.top + y * grid_rect.bottom)
		{
			if (pieces[i]->white == pieces[id]->white)
			{
				pieces[id]->object->SetX(pieces[id]->x);
				pieces[id]->object->SetY(pieces[id]->y);
				return;
			}
			else
			{
				attacking = true;
				target = i;
			}
		}
	}
	MovePiece(id);
	if (attacking)
	{
		if (target < id)
			id--;
		pieces.erase(pieces.begin() + target);
	}
}

void Game::MovePiece(int id)
{
	int x = GetCellId_X(id);
	int y = GetCellId_Y(id);

	pieces[id]->object->SetX(grid_rect.left + x * grid_rect.right);
	pieces[id]->object->SetY(grid_rect.top + y * grid_rect.bottom);

	if (pieces[id]->x != pieces[id]->object->GetX() || pieces[id]->y != pieces[id]->object->GetY())
	{
		pieces[id]->x = pieces[id]->object->GetX();
		pieces[id]->y = pieces[id]->object->GetY();
		ChangePlayer();
	}
}

void Game::ChangePlayer()
{
	turn++;
	for (int i = 0; i < pieces.size(); i++)
	{
		pieces[i]->object->SetDragable(!pieces[i]->object->GetDragable());
	}
}

int Game::GetCellId_X(int piece_id)
{
	return (pieces[piece_id]->object->GetX() - (grid_rect.left - grid_rect.right / 2)) / 90;
}

int Game::GetCellId_Y(int piece_id)
{
	return (pieces[piece_id]->object->GetY() - (grid_rect.top - grid_rect.bottom / 2)) / 90;
}

