#pragma once

namespace Input
{
	// 매 루프마다 호출 필요
	void Update();

	// 키가 눌려진 상태인지 확인
	bool IsKeyPressing(int vKey);

	// 이번 루프에 키가 눌려졌는지 확인
	bool IsKeyDown(int vKey);

	// 이번 루프에 키가 놓아졌는지 확인
	bool IsKeyUp(int vKey);
}