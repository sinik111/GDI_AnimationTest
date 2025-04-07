#pragma once

namespace AnimationController
{
	enum class SpriteName
	{
		Sprite_Idle,
		Sprite_Walk,
		Sprite_Attack,
		MAX
	};

	enum class AnimationState
	{
		State_Idle,
		State_Walk,
		State_Attack
	};

	void Initialize();

	void Update();

	void Render();

	void Release();
}