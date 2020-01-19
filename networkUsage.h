#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

// Need to link with Iphlpapi.lib and Ws2_32.lib
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))
/* Note: could also use malloc() and free() */

void activeNet(DWORD processID)
{

	// Declare and initialize variables
	PMIB_TCPTABLE2 pTcpTable;
	ULONG ulSize = 0;
	DWORD dwRetVal = 0;

	char szLocalAddr[128];
	char szRemoteAddr[128];

	struct in_addr IpAddr;

	int i;

	pTcpTable = (MIB_TCPTABLE2*)MALLOC(sizeof(MIB_TCPTABLE2));
	if (pTcpTable == NULL) {
		printf("Error allocating memory\n");
	
	}

	ulSize = sizeof(MIB_TCPTABLE);
	// Make an initial call to GetTcpTable2 to
	// get the necessary size into the ulSize variable
	if ((dwRetVal = GetTcpTable2(pTcpTable, &ulSize, TRUE)) ==
		ERROR_INSUFFICIENT_BUFFER) {
		FREE(pTcpTable);
		pTcpTable = (MIB_TCPTABLE2*)MALLOC(ulSize);
		if (pTcpTable == NULL) {
			printf("Error allocating memory\n");
			//return 1;
		}
	}
	// Make a second call to GetTcpTable2 to get
	// the actual data we require
	if ((dwRetVal = GetTcpTable2(pTcpTable, &ulSize, TRUE)) == NO_ERROR) {
		//printf("\tNumber of entries: %d\n", (int)pTcpTable->dwNumEntries);
		int flag = 0;
		for (i = 0; i < (int)pTcpTable->dwNumEntries; i++) {
			//printf("\n\tTCP[%d] State: %ld - ", i,pTcpTable->table[i].dwState);

			//IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwLocalAddr;
			//strcpy_s(szLocalAddr, sizeof(szLocalAddr), inet_ntoa(IpAddr));
			//printf("\tTCP[%d] Local Addr: %s\n", i, szLocalAddr);
			//printf("\tTCP[%d] Local Port: %d \n", i,ntohs((u_short)pTcpTable->table[i].dwLocalPort));

			//IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwRemoteAddr;
			//strcpy_s(szRemoteAddr, sizeof(szRemoteAddr), inet_ntoa(IpAddr));
			//printf("\tTCP[%d] Remote Addr: %s\n", i, szRemoteAddr);
			//printf("\tTCP[%d] Remote Port: %d\n", i,ntohs((u_short)pTcpTable->table[i].dwRemotePort));


			if ((DWORD)pTcpTable->table[i].dwOwningPid == processID) {
				cout << "Uses internet" << endl << endl;
				flag = 1;
			}
		}
		if(flag==0)
		{
			cout << "Doesn't use" << endl << endl;
		}

			//printf("\tTCP[%d] Owning PID: %d\n\n", i, pTcpTable->table[i].dwOwningPid);
			//printf("\tTCP[%d] Offload State: %ld - ", i,pTcpTable->table[i].dwOffloadState);
			

		
	}
	else {
		printf("\tGetTcpTable2 failed with %d\n", dwRetVal);
		FREE(pTcpTable);
	//return 1;
	}

	if (pTcpTable != NULL) {
		FREE(pTcpTable);
		pTcpTable = NULL;
	}

//return 0;
}