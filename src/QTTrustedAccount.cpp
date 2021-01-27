#include "stdafx.h"
//#include "TrustedAccount.h"

BOOLEAN QTIsRunByTrustedAccount()
{
	//if (!IsCurrentProcessRunByTrustedAccount(TRUE))
	//{
	//	DWORD dwLastError;
	//	dwLastError = ERROR_ACCESS_DENIED;
	//	if (dwLastError != 0)
	//	{
	//		//QTMessageBox(QApplication::activeWindow(), QApplication::tr("You have to be in the trusted account list to be able to modify this. Trusted account list can be managed in the Manage User Rights by a trusted user."), get_secureaplus_title(), QMessageBox::Ok, QMessageBox::Information);
	//		return FALSE;
	//	}
	//}
	return TRUE;
}