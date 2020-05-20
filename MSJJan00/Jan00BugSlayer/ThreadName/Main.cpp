/*----------------------------------------------------------------------
 Feb '00 - Microsoft Systems Journal - Bugslayer Column - John Robbins

                From a great idea by Ziv Caspi - Tip 29!
----------------------------------------------------------------------*/

#include "stdafx.h"
#include "ThreadName.h"

// The event all threads will wait on to end.
const LPCTSTR k_EVENTNAME = _T ( "ThreadNameEvent" ) ;
// The format string for naming threads.
const LPCTSTR k_NAMEFMT = _T ( "Hello from thread %d!" ) ;
// The main thread name.
const LPCTSTR k_MAINTHREADNAME = _T ( "Hello from the main thread!" ) ;


// The simple thread routine.
DWORD WINAPI ThreadProc ( LPVOID lpParameter )
{
    HANDLE hEvent = OpenEvent ( EVENT_ALL_ACCESS ,
                                FALSE            ,
                                k_EVENTNAME       ) ;
    if ( NULL == hEvent )
    {
        OutputDebugString ( _T ( "Unable to open the event!\n" ) ) ;
        return ( 0 ) ;
    }

    // The event is active so set the thread name.  Since the threads
    // routine's local variables are guarenteed to be around for the
    // life of the thread, I can set the name using this string
    // buffer.
    TCHAR szThreadName [ MAX_PATH ] ;

    wsprintf ( szThreadName , k_NAMEFMT , lpParameter ) ;

    if ( FALSE == SetThreadName ( szThreadName ) )
    {
        OutputDebugString ( _T ( "Unable to set the TIB for :\n" ) ) ;
        OutputDebugString ( szThreadName ) ;
        return ( 0 ) ;
    }

    WaitForSingleObject ( hEvent , INFINITE ) ;

    CloseHandle ( hEvent ) ;

    return ( 1 ) ;
}

void main ( void )
{
    // Set the name for the main thread.
    if ( FALSE == SetThreadName ( k_MAINTHREADNAME ) )
    {
        OutputDebugString ( _T ( "Unable to set main thread name!\n" ));
        return ;
    }

    HANDLE hEvent = CreateEvent ( NULL , TRUE , FALSE , k_EVENTNAME ) ;
    if ( NULL == hEvent )
    {
        OutputDebugString ( _T ( "Unable to create the event!\n" ) ) ;
    }

    // Create five threads.
    DWORD dwTID ;
    for ( DWORD i = 1 ; i < 6 ; i++ )
    {
        HANDLE hThread = CreateThread ( NULL       ,
                                        0          ,
                                        ThreadProc ,
                                        (LPVOID)i  ,
                                        0          ,
                                        &dwTID       ) ;
        if ( NULL == hThread )
        {
            SetEvent ( hEvent ) ;
            CloseHandle ( hEvent ) ;
            return ;
        }
    }

    Sleep ( 5000 ) ;
    SetEvent ( hEvent ) ;
    Sleep ( 1000 ) ;
    CloseHandle ( hEvent ) ;

}

