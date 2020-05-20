Installing the Handle Security Test:

1: Build all projects (each has its own workspace):
   ./handles.dsw
   ./include/handlesps.dsw
   ./HandleTest/HandleTest.dsw
   ./surrogate/surrogate.dsw
   ./nullprocess/nullprocess.dsw

2: Verify that all the programs built and were sent to the bin directory:
   ./bin/handles.exe
   ./bin/handlesps.dll
   ./bin/handletest.dll
   ./bin/surrogate.exe
   ./bin/nullprocess.exe

3: Register the proxy/stub DLL:
   ./bin/handlesps.dll

Now you're ready to run the client: ./bin/handles.exe

Consider running the client from the SYSTEM logon session
to be able to use all of the features of the test harness.
The easiest way to do this is to download the cmdasuser utility
from http://www.develop.com/kbrown/security/samples.htm, and run

  cmdasuser localsystem

to get an interactive command prompt running in the SYSTEM
logon session. Be VERY CAREFUL what you do from here, you have
lots of privileges and you could hurt yourself if you're not careful.
From this logon session, you can run handles.exe and be able to use
all its features.

Notes on using the Handle Security Test Harness:

1: The token object assumes you've got a local account defined with
   the name of "Alice", and a password of "alice". The system calls
   LogonUser using these hardcoded credentials to create a token object.

Known bugs:
   None so far. Please send bug reports and other feedback to Keith Brown
   at kbrown@develop.com
