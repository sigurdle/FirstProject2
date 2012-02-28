// Copyright © 1998 the e-comm group, inc.
//
// CScopeSingleLock.h: This class implements a locking class that locks
// only for the scope of the class
//
// $Author: Graf $
// $Date: 6/17/98 3:14p $
// $Revision: 2 $
// $Archive: /e-comm group/ScriptFII/DataTag COM Objects/CScopeSingleLock.h $

#ifndef _SCOPE_SINGLE_LOCK_H
#define _SCOPE_SINGLE_LOCK_H

class CScopeSingleLock
{
protected:
	// Vars that hold the critical section
	CRITICAL_SECTION* m_pCritSect;
	HANDLE m_hMutex;

	// Helper to do redundant code
	void Init(CRITICAL_SECTION* pCritSect,bool bInitialLock)
	{
		_ASSERTE(pCritSect != NULL);
		m_hMutex = NULL;
		// Intialize the member var
		m_pCritSect = pCritSect;
		// Check for auto lock or not
		if( bInitialLock == true )
		{
			// Lock the CS
			Lock();
		}
	}

// Constructors
public:
	CScopeSingleLock(CComAutoCriticalSection* pCritSect,
		bool bInitialLock = true)
	{
		_ASSERTE(pCritSect != NULL);
		// Call the method that does the work
		Init(&pCritSect->m_sec,bInitialLock);
	}
	CScopeSingleLock(CComCriticalSection* pCritSect,
		bool bInitialLock = true)
	{
		_ASSERTE(pCritSect != NULL);
		// Call the method that does the work
		Init(&pCritSect->m_sec,bInitialLock);
	}
#ifdef _AFX
	CScopeSingleLock(CCriticalSection* pCritSect,
		bool bInitialLock = true)
	{
		_ASSERTE(pCritSect != NULL);
		// Call the method that does the work
		Init(&pCritSect->m_sect,bInitialLock);
	}
#endif
	CScopeSingleLock(HANDLE hMutex,bool bInitialLock = true)
	{
		m_pCritSect = NULL;
		_ASSERTE(hMutex != NULL);
		m_hMutex = hMutex;
		// Lock the mutex if requested
		if( bInitialLock == true )
		{
			// Lock the mutex handle
			WaitForSingleObject(hMutex,INFINITE);
		}
	}
	virtual ~CScopeSingleLock() { Unlock(); }

// Operations
public:
	void Lock(void)
	{
		_ASSERTE(m_hMutex != NULL || m_pCritSect != NULL);
		// Check for a critical section first
		if( m_pCritSect != NULL )
		{
			// Lock the critical section
			EnterCriticalSection(m_pCritSect);
		}
		else
		{
			// Lock the mutex handle
			WaitForSingleObject(m_hMutex,INFINITE);
		}
	}
	void Unlock()
	{
		// Check for a critical section first
		if( m_pCritSect != NULL )
		{
			// Release the critical section
			LeaveCriticalSection(m_pCritSect);
		}
		else
		{
			// Release the mutex handle
			ReleaseMutex(m_hMutex);
		}
	}
};

#endif