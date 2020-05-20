/******************************************************************************
Module:  FilterOpLock.cpp
Notices: Written by Jeffrey Richter
******************************************************************************/


#define UNICODE
#define _UNICODE
#include <Windows.h>
#include <tchar.h>


///////////////////////////////////////////////////////////////////////////////


// Helper function to make setting an OpLock easier
inline RequestOpLock(DWORD dwCode, HANDLE hfile, OVERLAPPED* po) {
   DWORD dw;
   return(DeviceIoControl(hfile, dwCode, NULL, 0, NULL, 0, &dw, po));
}


///////////////////////////////////////////////////////////////////////////////


int WINAPI _tWinMain(HINSTANCE hinstExe, HINSTANCE, LPTSTR pszCmdLine, int) {

   TCHAR szFilename[] = TEXT("FilterOpLock.dat");
   HANDLE hfileLocking = INVALID_HANDLE_VALUE;
   HANDLE hfileReading = INVALID_HANDLE_VALUE;
   HMODULE hmod = NULL;
   OVERLAPPED o = { 0 };
   PCTSTR pszReport = NULL;

   __try {
      // Attempt to open the file for processing (must be asynchronous)
      MessageBox(NULL, TEXT("Open file's locking handle?"), NULL, MB_OK);

      // Open the file without requesting GENERIC_READ or GENERIC_WRITE
      // so that this call NEVER fails.
      hfileLocking = CreateFile(szFilename, 0, FILE_SHARE_READ, NULL, 
         OPEN_ALWAYS, FILE_FLAG_OVERLAPPED, NULL);
      if (hfileLocking == INVALID_HANDLE_VALUE) {
         pszReport = TEXT("Can't open file for locking.");
         __leave;
      }

      // After opening the file (above) and before requesting the 
      // OpLock (below), another process can sucessfully access the file
      // including delete the file.

      // Request the Filter OpLock on the file.
      // When another process attempts to access the file, the system will 
      // signal the event and block the other process until we close the file
      MessageBox(NULL, TEXT("Request filter oplock?"), NULL, MB_OK);
      o.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
      if (RequestOpLock(FSCTL_REQUEST_FILTER_OPLOCK, hfileLocking, &o) ||
         (GetLastError() != ERROR_IO_PENDING)) {
         pszReport = TEXT("Failed to set opportunistic lock.");
         __leave;
      }

#if 1
      // Attempt to open the file again to perform our own processing
      MessageBox(NULL, TEXT("Open file for processing?"), NULL, MB_OK);
      hfileReading = CreateFile(szFilename, GENERIC_READ, 
         FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, 
         OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
      if (hfileReading == INVALID_HANDLE_VALUE) {
         // The file was deleted or opened exclusively by another process.
         pszReport = TEXT("Can't open file for reading.");
         __leave;
      }
#else
      // NOTE: To experiment with a DLL change szFilename to a DLL file, 
      //       comment out the code above, uncomment this code and rebuild 
      //       this sample application.
      // Attempt to load the DLL to use it (Example: Explorer Shell Extension)
      MessageBox(NULL, TEXT("Load DLL?"), NULL, MB_OK);
      hmod = LoadLibrary(szFilename);
      if (hmod == NULL) {
         // The DLL was deleted or opened exclusively by another process.
         pszReport = TEXT("Can't load DLL.");
         __leave;
      }
#endif

      // Work with the file for 15 seconds (simulated)
      // Wait for lock to be broken
      MessageBox(NULL, TEXT("Access file/DLL for 15 seconds?"), NULL, MB_OK);
      if (WaitForSingleObject(o.hEvent, 15000) == WAIT_OBJECT_0) {
         // Event is signaled: Another process is trying to access the file
         // The other process is suspended until we close the file
         MessageBox (NULL, 
            TEXT("Another process is attempting to access the file.\n")
            TEXT("Close file/DLL and allow the other process access?"),
            NULL, MB_OK);
         pszReport = TEXT("The file/DLL is closed.");
      } else {
         // Another process did NOT attempt to access the file at the same 
         // time, we'll just close the file.
         pszReport = TEXT("We're finished accessing the file/DLL.");
      }
   }
   __finally {
      // Cleanup everything we did sucessfully.
      if (hfileLocking != INVALID_HANDLE_VALUE)
         CloseHandle(hfileLocking);

      if (hfileReading != INVALID_HANDLE_VALUE)
         CloseHandle(hfileReading);

      if (hmod != NULL)
         FreeLibrary(hmod);

      if (o.hEvent != NULL)
         CloseHandle(o.hEvent);

      if (pszReport != NULL)
         MessageBox(NULL, pszReport, TEXT("Final report"), MB_OK);
   }
   return(0);
}


//////////////////////////////// End of File //////////////////////////////////

#if 0
What File System does to open a file:
Open
   Break batch/filter op lock (blocked til close pending)
Sharing mode check
ACL check
	Break exclusive lock
Opened

NOTE: Filter lock: open w/read attributes only
#endif
