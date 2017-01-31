#pragma once

class CSoundMgr
{
private:
	FMOD_SYSTEM*	m_pSystem;	//fmod 시스템 저장용 포인터
	FMOD_CHANNEL*	m_pEffect;	//fmod 채널 저장용 포인터
	FMOD_CHANNEL*	m_pBgm;		//fmod 채널 저장용 포인터
	
	unsigned int	m_iVersion;

	//사운드들을 보관할 map 컨테이너...
	map<TCHAR*, FMOD_SOUND*>		m_mapSound;
public:
	map<TCHAR*, FMOD_SOUND*>*	GetSoundMap(void)
	{
		return &m_mapSound;
	}
public:
	void	Initialize(void);
	void	LoadSoundFile();
	void	PlaySound(TCHAR* pSoundKey);
	void	PlayBGM(TCHAR*	pSoundKey);
	void	StopBGM(TCHAR*	pSoundKey);
	void	StopSoundAll(void);
	void	Release(void);
private:
	static CSoundMgr*	m_pInstance;
public:
	static CSoundMgr*	GetInstance(void)
	{
		if(m_pInstance == NULL)
			m_pInstance = new CSoundMgr;

		return m_pInstance;
	}

	void	DestroyInstance(void)
	{
		if(m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}
private:
	CSoundMgr(void);
	~CSoundMgr(void);
};
