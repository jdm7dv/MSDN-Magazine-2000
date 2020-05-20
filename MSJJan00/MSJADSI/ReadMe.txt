MSJADSI.EXE

MSJADSI is a MFC Dialog application that does all the examples shown in the
article "Active Directory: Not Just For Network Resource Management Anymore",
by Shawn Wildermuth

There are a couple of caveats before compiling:

1.  The ADSI 2.5 SDK paths to the lib and include directories have been 
hard coded into the project file.  Please change the paths the correct ones
for your system.

2.  Be aware that the LDAP path and name and password are defaults for 
my test system.  They are not expected to work without changing them to your
path and username/password. 

Thanks,

Please feel free to write me with any comments or suggestions:

Shawn Wildermuth
shawn.wildermuth@bigfoot.com