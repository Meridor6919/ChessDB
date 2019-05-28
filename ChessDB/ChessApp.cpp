#include "ChessApp.h"


ChessApp::ChessApp(HINSTANCE instance) : DirectXApplication(instance)
{

	Object::x_ratio = x_ratio;
	Object::y_ratio = y_ratio;
	m_states = new DirectX::CommonStates(device);
	m_effect = new DirectX::BasicEffect(device);
	m_effect->SetVertexColorEnabled(true);
	game = new Game();

	void const* shaderByteCode;
	size_t byteCodeLength;

	m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

		device->CreateInputLayout(DirectX::VertexPositionColor::InputElements,
			DirectX::VertexPositionColor::InputElementCount,
			shaderByteCode, byteCodeLength,
			&m_inputLayout);

		DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.f, float(window_width), float(window_height), 0.f, 0.f, 1.f);
		m_effect->SetProjection(proj);

	sprite_batch = new DirectX::SpriteBatch(device_context);
	primitive_batch = new DirectX::PrimitiveBatch<DirectX::VertexPositionColor>(device_context);
	sprite_font = new DirectX::SpriteFont(device, L"graphics\\myfile.spritefont", false);
	mouse = new DirectX::Mouse();
	mouse->SetWindow(hwnd);
	mouse_tracker = new DirectX::Mouse::ButtonStateTracker();
	LoadStartingPosition();
}

int ChessApp::Run()
{
	return DirectXApplication::Run();
}

void ChessApp::Update(float delta_time)
{
	mouse_tracker->Update(mouse->GetState());
	game->Update(mouse_tracker, mouse);
}

void ChessApp::Render(float delta_time)
{
	float f[4] = { 0.1,0.15,0.15,1.0f };
	device_context->ClearRenderTargetView(render_target_view, f);
	DrawGrid();
	sprite_batch->Begin(DirectX::SpriteSortMode_FrontToBack);
	game->Draw();
	sprite_batch->End();
	swap_chain->Present(0, 0);
	
	
}

void ChessApp::LoadStartingPosition()
{
	std::fstream fvar;
	std::map<int, Piece_type*> piece_types;
	std::string line;
	std::string buffer[13];
	int index = 0;
	fvar.open("settings\\types_of_pieces.csv", std::ios::in);
	std::getline(fvar, line);

	//getting types of pieces
	while (std::getline(fvar, line))
	{
		for (int j = 0; j < line.size(); j++)
		{
			if (line[j] == '\t')
				index++;
			else if (index >= 13)
				break;
			else
				buffer[index] += line[j];
		}

		piece_types.insert(std::make_pair(atoi(buffer[0].c_str()), new Piece_type(atoi(buffer[0].c_str()), buffer[2], buffer[3], buffer[4],
			{ atoi(buffer[5].c_str()),atoi(buffer[6].c_str()),atoi(buffer[7].c_str()),atoi(buffer[8].c_str()) },
			{ atoi(buffer[9].c_str()),atoi(buffer[10].c_str()),atoi(buffer[11].c_str()),atoi(buffer[12].c_str()) })));
		for (int j = 0; j < 13; j++)
			buffer[j] = "";
		index = 0;
	}
	fvar.close();

	//loading pieces
	fvar.open("settings\\starting_pos.csv", std::ios::in);
	std::getline(fvar, line);

	while (std::getline(fvar, line))
	{
		for (int j = 0; j < line.size(); j++)
		{
			if (line[j] == '\t')
				index++;
			else if (index >= 4)
				break;
			else
				buffer[index] += line[j];
		}

		RECT rect;
		if (atoi(buffer[3].c_str()))
		{
			rect = (*piece_types.at(atoi(buffer[2].c_str()))).white;
		}
		else
		{
			rect = (*piece_types.at(atoi(buffer[2].c_str()))).black;
		}

		a = new Graphics::Sprite(sprite_batch, { rect.left,rect.top,rect.left + rect.right,rect.top + rect.bottom },
			game->GetGridRect().left + (game->GetCellsInRow() - atoi(buffer[0].c_str())) * game->GetGridRect().right,
			game->GetGridRect().top + (atoi(buffer[1].c_str())-1) *  game->GetGridRect().bottom, game->GetGridRect().right,
			game->GetGridRect().bottom, 0.1);

		line = "graphics\\" + (*piece_types.at(atoi(buffer[2].c_str()))).image_path;
		a->AddTexture(std::wstring(line.begin(), line.end()).c_str(), device);
		game->AddPiece(new Piece(new Object(a, !atoi(buffer[3].c_str())), piece_types.at(atoi(buffer[2].c_str())), atoi(buffer[3].c_str())));

		for (int j = 0; j < 4; j++)
			buffer[j] = "";
		index = 0;
	}
	fvar.close();
}

void ChessApp::DrawGrid()
{
	device_context->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
	device_context->OMSetDepthStencilState(m_states->DepthNone(), 0);
	device_context->RSSetState(m_states->CullNone());
	m_effect->Apply(device_context);
	device_context->IASetInputLayout(m_inputLayout);

	DirectX::XMFLOAT4 colors[2] = { { 0.7529, 0.7529, 0.7529, 1 }, { 1, 0.9215, 0.8039, 1 } };
	bool current_color = false;

	DirectX::XMFLOAT3 v1(game->GetGridRect().left, game->GetGridRect().top, 1.0f);
	DirectX::XMFLOAT3 v2(game->GetGridRect().left + game->GetGridRect().right, game->GetGridRect().top, 1.0f);
	DirectX::XMFLOAT3 v3(game->GetGridRect().left + game->GetGridRect().right, game->GetGridRect().top + game->GetGridRect().bottom, 1.0f);
	DirectX::XMFLOAT3 v4(game->GetGridRect().left, game->GetGridRect().top + game->GetGridRect().bottom, 1.0f);

	primitive_batch->Begin();
	for (int i = 0; i < game->GetCellsInRow(); i++)
	{
		v1.x = game->GetGridRect().left;
		v2.x = game->GetGridRect().left + game->GetGridRect().right;
		v3.x = game->GetGridRect().left + game->GetGridRect().right;
		v4.x = game->GetGridRect().left;
		for (int j = 0; j < game->GetCellsInColumn(); j++)
		{
			current_color = !current_color;
			primitive_batch->DrawQuad(DirectX::VertexPositionColor(XMLoadFloat3(&v1), XMLoadFloat4(&colors[current_color])),
				DirectX::VertexPositionColor(XMLoadFloat3(&v2), XMLoadFloat4(&colors[current_color])),
				DirectX::VertexPositionColor(XMLoadFloat3(&v3), XMLoadFloat4(&colors[current_color])),
				DirectX::VertexPositionColor(XMLoadFloat3(&v4), XMLoadFloat4(&colors[current_color])));
			v1.x += game->GetGridRect().right;
			v2.x += game->GetGridRect().right;
			v3.x += game->GetGridRect().right;
			v4.x += game->GetGridRect().right;
		}
		v1.y += game->GetGridRect().bottom;
		v2.y += game->GetGridRect().bottom;
		v3.y += game->GetGridRect().bottom;
		v4.y += game->GetGridRect().bottom;
		current_color = !current_color;
	}
	primitive_batch->End();
}
