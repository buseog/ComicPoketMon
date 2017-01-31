#include "Status.h"

Engine::CStatus::CStatus( void )
{

}

Engine::CStatus::CStatus( float _fHp, float _fMp, float _fSpeed, float _fAttack )
: fHp(_fHp)
, fMp(_fMp)
, fSpeed(_fSpeed)
, fAttack(_fAttack)
{

}

Engine::CStatus::~CStatus( void )
{
}
Engine::CStatus* Engine::CStatus::Create( void )
{
	return new CStatus;
}

Engine::CStatus* Engine::CStatus::Create( float _fHp, float _fMp, float _fSpeed, float _fAttack )
{
	return new CStatus(_fHp, _fMp, _fSpeed, _fAttack);
}
