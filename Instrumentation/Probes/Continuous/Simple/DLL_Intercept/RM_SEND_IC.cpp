// RM_SEND_IC.cpp
// Author      : Shivakumar C. Patil (shivakumar.patil@stdc.com)
// Description : 
//

/*
 * Copyright (C) 2001 System/Technology Development Corporation
 * This file is part of QoS Metrics Services (QMS)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA
 *
 * You may contact System/Technology Development Corporation at
 *
 *     System/Technology Development Corporation
 *     Suite 500, Center for Innovative Technology,
 *     2214 Rock Hill Road,
 *     Herndon, VA 20170    
 *     (703) 476-0687
 */


#include "RM_SEND_IC.h"

BOOL WINAPI DllMain (HMODULE hInst,  ULONG reason, LPVOID lpReserved) {
	switch (reason) {
	case DLL_PROCESS_ATTACH:
        printf("Attaching to the process\n");
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		printf("Detach from the process\n");
		WrapperUnloading(hInst);
	}
	return TRUE;  
}

extern "C"{ 

DllExport
int
WINAPI
Med_send(void *icall,
    SOCKET s,
    const char FAR * buf,
    int len,
    int flags
    )
	
{
	DWORD dwbyteswrittenSend;
	BOOL bstatus;
	
	bstatus = WriteFile(hNamedPipe, buf, (DWORD) len, &dwbyteswrittenSend, NULL);
	return (int) InnerCall(icall);
}

DllExport void InitializeWrapper(void)
{
	if(WaitNamedPipe("\\\\.\\PIPE\\RMSEND", NMPWAIT_USE_DEFAULT_WAIT))
		printf("\n Connected to the Server Named pipe");
	else 
		printf("\n Not Connected to the Server Named pipe");	
	
	hNamedPipe = CreateFile ("\\\\.\\PIPE\\RMSEND", GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hNamedPipe == INVALID_HANDLE_VALUE)
		printf (_T ("Failure to locate server."), 3, TRUE);
	else
		printf("\n Got the handle for the Server Named pipe");
		 
}


DllExport void CloseWrapper()
{
	printf("\n Closing the handle for the Named pipe");
	CloseHandle(hNamedPipe);
}

} // end of extern "C"
