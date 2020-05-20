/*----------------------------------------------------------------------
 Feb '00 - Microsoft Systems Journal - Bugslayer Column - John Robbins

                From a great idea by Ziv Caspi - Tip 29!
----------------------------------------------------------------------*/

#ifndef _THREADNAME_H
#define _THREADNAME_H

/*----------------------------------------------------------------------
FUNCTION    :   SetThreadName

DESCRIPTION :
    SetThreadName provides a way to "name" your threads so that you can
see at a glance which thread is active when you are in the debugger.
Calling SetThreadName sets the string pointer parameter into the Thread
Information Block (TIB) pvArbitrary field (offset 0x14).  Matt Pietrek
discussed the TIB structure in his May 1996 "Under the Hood" column.
I included Matt's TIB.h as part of this project if you want to see the
rest of the fields in the TIB.
    pvArbitrary is an unused spot in the TIB that applications can use
as they wish.  SetThreadName does the right thing and checks if the
pvArbitrary is not 0 and will not write the string pointer to avoid
tromping on any other data written there.
    To view which thread is active in the Watch window, use
"(char*)(DW(@TIB+0x14))"  As you swap threads, you can now tell at a
glance which thread you are in!

PARAMETERS  :
    szName - A pointer to the string which you would like to name the
             current thread.  You should make the string pointer a
             constant name.

RETURNS     :
    TRUE  - The thread name was set.
    FALSE - Something else overwrote the pvArbitrary field.
----------------------------------------------------------------------*/
BOOL SetThreadName ( LPCTSTR szName ) ;

/*----------------------------------------------------------------------
FUNCTION    :   GetThreadName

DESCRIPTION :
    Returns the string pointer to the name assigned to the current
thread.

PARAMETERS  :
    None.

RETURNS     :
    NULL  - No name was assigned.
    !NULL - The value at the TIB pvArbitrary offset.  Please note that
            the pointer could be invalid of if something other than
            SetThreadName used the pvArbitrary offset.
----------------------------------------------------------------------*/
LPCTSTR GetThreadName ( void ) ;


#endif  // _THREADNAME_H


