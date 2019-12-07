#pragma once
#include "DirectXApplication.h"
#include "SimpleMath.h"
#include "PrimitiveBatch.h"
#include "VertexTypes.h"
#include "SpriteBatch.h"
#include "Piece.h"
#include <fstream>
#include <map>

class Game
{
	std::vector<std::unique_ptr<Piece>> pieces;
	std::vector<std::shared_ptr<MeridorGraphics::Sprite>> sprites;
	RECT grid_rect;
	int cells_in_row;
	int cells_in_column;

	int GetCellId_X(int x);
	int GetCellId_Y(int y);
	void LoadConfigFile();
	void LoadPieces(DirectX::SpriteBatch * sprite_batch, ID3D11Device * device);
	void DrawGrid(DirectX::PrimitiveBatch<DirectX::VertexPositionColor> *primitive_batch);
	std::tuple<bool, bool, bool, bool> GetRelativeDirection(int binary_direction, double rotation);
	void DrawPieces();

	void OnMove(int piece_id);
	void MovePiece(int piece_id);
	bool ValidateMove(std::string move_formula, int piece_id);
	bool CollisionDetected(int src_x, int src_y, int dst_x, int dst_y);
	void ChangePlayer();
public:
	Game(DirectX::SpriteBatch* sprite_batch, ID3D11Device *device);
	void DrawPrimitiveBatch(DirectX::PrimitiveBatch<DirectX::VertexPositionColor> *primitive_batch, float delta_time);
	void DrawSpriteBatch(DirectX::SpriteBatch *sprite_batch, float delta_time);
	void Update(DirectX::Mouse::ButtonStateTracker * button_tracker, DirectX::Mouse * mouse, DirectX::Keyboard::KeyboardStateTracker * keyboard_tracker, DirectX::Keyboard * keyboard, float delta_time);
};

