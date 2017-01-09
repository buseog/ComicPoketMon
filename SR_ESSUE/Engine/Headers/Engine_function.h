/*!
 * \file Engine_function.h
 * \date 2016/12/21 16:03
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Engine_function_h__
#define Engine_function_h__


namespace Engine
{
	template<typename T>
	void Safe_Delete(T& Temp)
	{
		if(NULL != Temp)
		{
			delete Temp;
			Temp = NULL;
		}
	}

	template <typename T> 
	void Safe_Delete_Array (T& pointer)
	{
		if(NULL != pointer)
		{
			delete [] pointer;
			pointer = NULL;
		}
	}


	template <typename T> 
	DWORD Safe_Release (T& pointer)
	{
		DWORD		dwRefCnt = 0;
		if(NULL != pointer)
		{
			dwRefCnt = pointer->Release();
			if(dwRefCnt == 0)
				pointer = NULL;
		}

		return dwRefCnt;
	}


	template <typename T> 
	void Safe_Single_Destory(T& pointer)
	{
		if(NULL != pointer)
		{
			pointer->DestroyInstance();
			pointer = NULL;
		}
	}
}

#endif // Engine_function_h__