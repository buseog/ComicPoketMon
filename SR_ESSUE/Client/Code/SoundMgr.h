#pragma once

class CSoundMgr
{
private:
	FMOD_SYSTEM*	m_pSystem;	//fmod �ý��� ����� ������
	FMOD_CHANNEL*	m_pEffect;	//fmod ä�� ����� ������
	FMOD_CHANNEL*	m_pBgm;		//fmod ä�� ����� ������
	
	unsigned int	m_iVersion;

	//������� ������ map �����̳�...
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
