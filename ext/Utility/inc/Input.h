#pragma once

namespace Input
{
	// �� �������� ȣ�� �ʿ�
	void Update();

	// Ű�� ������ �������� Ȯ��
	bool IsKeyPressing(int vKey);

	// �̹� ������ Ű�� ���������� Ȯ��
	bool IsKeyDown(int vKey);

	// �̹� ������ Ű�� ���������� Ȯ��
	bool IsKeyUp(int vKey);
}