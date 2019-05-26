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
		pieces[i]->object->Update(mouse_info, mouse);
	}
}

void Game::Draw()
{
	for (int i = 0; i < pieces.size(); i++)
	{
		pieces[i]->object->Draw();
	}
}

