#include "AnimationController.h"

#include <windows.h>
#include <gdiplus.h>

#include "Sprite.h"
#include "Input.h"
#include "GDIRenderer.h"

static Sprite* sprites[(int)AnimationController::SpriteName::MAX];

static AnimationController::AnimationState current_state;
static AnimationController::AnimationState next_state;

static Sprite* current_sprite;

void AnimationController::Initialize()
{
	sprites[(int)AnimationController::SpriteName::Sprite_Idle] = new Sprite(L"Resource/Idle.png", 7, true, true);
	sprites[(int)AnimationController::SpriteName::Sprite_Walk] = new Sprite(L"Resource/Walk.png", 12, true, true);
	sprites[(int)AnimationController::SpriteName::Sprite_Attack] = new Sprite(L"Resource/Attack.png", 9, false, false);

	current_state = AnimationState::State_Idle;
	next_state = AnimationState::State_Idle;

	current_sprite = sprites[(int)AnimationController::SpriteName::Sprite_Idle];
	current_sprite->Play();
}

void AnimationController::Update()
{
	if (Input::IsKeyUp('2'))
	{
		next_state = AnimationState::State_Attack;
	}
	else if (Input::IsKeyPressing('1'))
	{
		next_state = AnimationState::State_Walk;
	}
	else
	{
		next_state = AnimationState::State_Idle;
	}
	
	if (current_state != next_state)
	{
		switch (next_state)
		{
		case AnimationState::State_Attack:
			if (current_sprite->is_stoppable)
			{
				current_sprite->Reset();
				current_sprite = sprites[(int)AnimationController::SpriteName::Sprite_Attack];
				current_sprite->Play();

				current_state = AnimationState::State_Attack;
			}
			break;

		case AnimationState::State_Idle:
			if (current_sprite->is_stoppable)
			{
				current_sprite->Reset();
				current_sprite = sprites[(int)AnimationController::SpriteName::Sprite_Idle];
				current_sprite->Play();

				current_state = AnimationState::State_Idle;
			}
			else if (current_sprite->is_end)
			{
				current_sprite->Reset();
				current_sprite = sprites[(int)AnimationController::SpriteName::Sprite_Idle];
				current_sprite->Play();

				current_state = AnimationState::State_Idle;
			}
			break;

		case AnimationState::State_Walk:
			if (current_sprite->is_stoppable)
			{
				current_sprite->Reset();
				current_sprite = sprites[(int)AnimationController::SpriteName::Sprite_Walk];
				current_sprite->Play();

				current_state = AnimationState::State_Walk;
			}
			else if (current_sprite->is_end)
			{
				current_sprite->Reset();
				current_sprite = sprites[(int)AnimationController::SpriteName::Sprite_Walk];
				current_sprite->Play();

				current_state = AnimationState::State_Walk;
			}
			break;
		}
	}

	current_sprite->Update();
}

void AnimationController::Render()
{
	Gdiplus::Rect src_rect = {};
	Gdiplus::Rect dst_rect = {};
	dst_rect.X = 0;
	dst_rect.Y = 0;

	current_sprite->GetFrameInfo(&dst_rect, &src_rect);

	GDIRenderer::Render(current_sprite->image, dst_rect, src_rect);
}

void AnimationController::Release()
{
	for (int i = 0; i < (int)AnimationController::SpriteName::MAX; ++i)
	{
		if (sprites[i] != nullptr)
		{
			delete sprites[i];
		}
	}
}