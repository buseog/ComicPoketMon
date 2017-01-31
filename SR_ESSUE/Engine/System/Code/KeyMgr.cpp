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

bool	Engine::CKeyMgr::StayKeyDown(int nKey)	// 쭉 누르고있을때
{
	if (GetAsyncKeyState(nKey) & 0x8000)	// 함수가 계속 반복되면서 키가 입력된걸 확인하고 트루를 반홤함
		return true;

	return false;	// if문에서 입력된걸 감지하지 않았음으로 눌리지 않았음. 펄스를 반환
}

bool	Engine::CKeyMgr::KeyDown(int nKey, int iIndex)	// 한번만 딱 눌렀을때
{
	if (GetAsyncKeyState(nKey) & 0x8000)	// 키가 입력됬는지 확인하고
	{
		if (m_bKeyDown[iIndex][nKey] == false)	// 다운 배열에서 입력된 키값이 폴스인지 확인(이전에 눌렸는지)
		{
			m_bKeyDown[iIndex][nKey] = true;	//	이전에 눌린적이 없으면 트루로 바꿔줌

			return true;				//	트루로 반환
		}
	}
	else
	{
		m_bKeyDown[iIndex][nKey] = false;		//	키가 입력되지 않았으므로 폴스 반환
	}

	return false;						//	그냥 실패로간주
}

bool	Engine::CKeyMgr::KeyUp(int nKey, int iIndex)	// 눌렀다가 똇을때
{
	if (GetAsyncKeyState(nKey) & 0x8000)		// 눌렸는지 확인
	{
		m_bKeyUp[iIndex][nKey] = true;			//	눌렸으면 업배열 해당키값을 트루로 바꿈
	}
	else if (m_bKeyUp[iIndex][nKey] == true)	//	다시 함수가 시작됬을떄 입력된 키값이 눌리지 않았고, 해당 업배열이 트루라면
	{
		m_bKeyUp[iIndex][nKey] = false;			//	배열을 펄스로 초기화하고

		return true;							//	트루를 반환함
	}

	return false;								//	걍실패
}
