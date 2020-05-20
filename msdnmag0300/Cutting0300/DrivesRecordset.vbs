'==========================================================================
'
' NAME: DrivesRecordset.vbs
'
' AUTHOR: Dino Esposito, Expoware Soft
' DATE  : 10/29/99
'
' COMMENT: Exposes drive information through an ADO recordset
'
'==========================================================================

' Constants
Const adUseClient = 3
Const adCurrency = 6
Const adBSTR = 8

' Local variables
Dim fso, rst, drives

' Creates the main objects of the script
Set fso = CreateObject("Scripting.FileSystemObject")
Set rst = CreateObject("ADODB.Recordset")

' Gets the collection of available drives
Set drives = fso.Drives

' Prepares the recordset structure: Root, Volume, Type, FileSystem, FreeSpace
rst.CursorLocation = adUseClient
rst.Fields.Append "Root", adBSTR
rst.Fields.Append "Volume", adBSTR
rst.Fields.Append "Type", adBSTR
rst.Fields.Append "FileSystem", adBSTR
rst.Fields.Append "FreeSpace", adCurrency
rst.Open

' Fills the recordset out with drive information
for each drv in drives 
	rst.AddNew
	if drv.IsReady then
		rst.Fields("Root").Value = drv.DriveLetter
		rst.Fields("Volume").Value = drv.VolumeName
		rst.Fields("Type").Value = drv.DriveType
		rst.Fields("FileSystem").Value = drv.FileSystem
		rst.Fields("FreeSpace").Value = drv.FreeSpace /1024
	end if 
next 

' Displays the recordset
s = ""
rst.MoveFirst
while Not rst.EOF
	for each fld in rst.Fields 
		s = s & Pad(rst.Fields(fld.Name), 14) & vbTab 
	next
	s = s & vbCrLf
	rst.MoveNext
wend

MsgBox s



'==========================================================================
' Pad(str, numChars)
' Pads the specified string with the specified trailing blanks
'==========================================================================
Function Pad (str, numChars)
	str = str & Space(numChars)
	Pad = Left(str, numChars)
End Function