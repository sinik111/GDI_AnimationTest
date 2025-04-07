#include "Game.h"

#include "GDIRenderer.h"
#include "AnimationController.h"
#include "Input.h"

void Game::Initialize()
{
	GDIRenderer::Initialize();
	AnimationController::Initialize();
}

void Game::Update()
{
	AnimationController::Update();
	Input::Update();
}

void Game::Render()
{
	// Begin Draw
	GDIRenderer::BeginDraw();

	// Render
	AnimationController::Render();

	// End Draw
	GDIRenderer::EndDraw();
}

void Game::Release()
{
	AnimationController::Release();
	GDIRenderer::Release();
}