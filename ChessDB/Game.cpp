#include "Game.h"



Game::Game()
{

	std::vector<Piece*> pieces;
	grid_rect = { 80, 30, 90, 90 };
	cells_in_row = 8;
	cells_in_column = 8;
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
	int x = (pieces[id]->object->GetX() - (grid_rect.left - grid_rect.right / 2)) / 90;
	int y = (pieces[id]->object->GetY() - (grid_rect.top - grid_rect.bottom / 2)) / 90;

	if (x < 0 || y < 0 || x>= cells_in_row || y >= cells_in_column)
	{
		pieces[id]->object->SetX(pieces[id]->x);
		pieces[id]->object->SetY(pieces[id]->y);
	}
	else
	{
		pieces[id]->object->SetX(grid_rect.left + x * grid_rect.right);
		pieces[id]->object->SetY(grid_rect.top + y * grid_rect.bottom);

		if (pieces[id]->x != pieces[id]->object->GetX() || pieces[id]->y != pieces[id]->object->GetY())
		{
			pieces[id]->x = pieces[id]->object->GetX();
			pieces[id]->y = pieces[id]->object->GetY();
			for (int i = 0; i < pieces.size(); i++)
			{
				if (pieces[i]->x == pieces[id]->x && pieces[i]->y == pieces[id]->y && i != id)
				{
					pieces.erase(pieces.begin() + i);
				}
			}
			ChangePlayer();
		}
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

