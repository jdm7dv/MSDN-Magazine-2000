/*----------------------------------------------------------------------
 Feb '00 - Microsoft Systems Journal - Bugslayer Column - John Robbins

                From a great idea by Ziv Caspi - Tip 29!
----------------------------------------------------------------------*/

#include "stdafx.h"
#include "ThreadName.h"
#include "TIB.h"

// A static function to get the TIB.
static PTIB GetTIB ( void )
{
    PTIB pTib ;

    __asm
    {
        MOV  EAX , FS:[18h]
        MOV  pTib , EAX
    }
    return ( pTib ) ;
}

// See ThreadName.h.
BOOL SetThreadName ( LPCTSTR szName )
{
    // Grab the TIB.
    PTIB pTib = GetTIB ( ) ;

    // If someone has already written to the arbitrary field, I don't
    // want to be overwriting it.
    if ( NULL != pTib->pvArbitrary )
    {
        return ( FALSE ) ;
    }

    // Nothing's there.  Set the name.
    pTib->pvArbitrary = (void*)szName ;
    return ( TRUE ) ;
}

LPCTSTR GetThreadName ( void )
{
    // Grab the TIB.
    PTIB pTib = GetTIB ( ) ;

    return ( (LPCTSTR)pTib->pvArbitrary ) ;
}

