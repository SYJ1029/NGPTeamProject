#pragma once


enum Game_State : long long
{
	GAME_STATE_WAITING = 0, // ��� Ŭ���̾�Ʈ ���� ��� & �ʱ�ȭ ���� �۽� �ܰ�
	GAME_STATE_RUNNING = 1, // ���� ��� ��
	GAME_STATE_FINISHED = 2, // ����ڰ� ������
	GAME_STATE_RESETTING = 3 // ����/�÷��̾� ���� ��
};


