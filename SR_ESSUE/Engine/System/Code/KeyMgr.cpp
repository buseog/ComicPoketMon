#include "KeyMgr.h"

IMPLEMENT_SINGLETON(Engine::CKeyMgr)

Engine::CKeyMgr::CKeyMgr(void)
{
	ZeroMemory(m_bKeyDown, sizeof(KEYMAX));
	ZeroMemory(m_bKeyUp, sizeof(KEYMAX));
}

Engine::CKeyMgr::~CKeyMgr(void)
{

}

bool	Engine::CKeyMgr::StayKeyDown(int nKey)	// �� ������������
{
	if (GetAsyncKeyState(nKey) & 0x8000)	// �Լ��� ��� �ݺ��Ǹ鼭 Ű�� �ԷµȰ� Ȯ���ϰ� Ʈ�縦 ���c��
		return true;

	return false;	// if������ �ԷµȰ� �������� �ʾ������� ������ �ʾ���. �޽��� ��ȯ
}

bool	Engine::CKeyMgr::KeyDown(int nKey, int iIndex)	// �ѹ��� �� ��������
{
	if (GetAsyncKeyState(nKey) & 0x8000)	// Ű�� �Է���� Ȯ���ϰ�
	{
		if (m_bKeyDown[iIndex][nKey] == false)	// �ٿ� �迭���� �Էµ� Ű���� �������� Ȯ��(������ ���ȴ���)
		{
			m_bKeyDown[iIndex][nKey] = true;	//	������ �������� ������ Ʈ��� �ٲ���

			return true;				//	Ʈ��� ��ȯ
		}
	}
	else
	{
		m_bKeyDown[iIndex][nKey] = false;		//	Ű�� �Էµ��� �ʾ����Ƿ� ���� ��ȯ
	}

	return false;						//	�׳� ���зΰ���
}

bool	Engine::CKeyMgr::KeyUp(int nKey, int iIndex)	// �����ٰ� �H����
{
	if (GetAsyncKeyState(nKey) & 0x8000)		// ���ȴ��� Ȯ��
	{
		m_bKeyUp[iIndex][nKey] = true;			//	�������� ���迭 �ش�Ű���� Ʈ��� �ٲ�
	}
	else if (m_bKeyUp[iIndex][nKey] == true)	//	�ٽ� �Լ��� ���ۉ����� �Էµ� Ű���� ������ �ʾҰ�, �ش� ���迭�� Ʈ����
	{
		m_bKeyUp[iIndex][nKey] = false;			//	�迭�� �޽��� �ʱ�ȭ�ϰ�

		return true;							//	Ʈ�縦 ��ȯ��
	}

	return false;								//	������
}
