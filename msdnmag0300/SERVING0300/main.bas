Option Explicit
Dim catalog As Object
Dim packages As Object
Dim PackageUtil As PackageUtil
Dim CommandArguments()

Sub Main()
Dim vObjKey As Variant
    Set catalog = CreateObject("MTSAdmin.Catalog.1")
    Set packages = catalog.GetCollection("Packages")
       
    If Command$ = "Show" Or Command$ = "" Then
        frmMTSUTilInferface.Show
        frmMTSUTilInferface.cmdShutdownpackage.Visible = False
        frmMTSUTilInferface.ListPackages
    End If
    
    ProcessCommandLine
    
End Sub
Function FindPackage(PackageName As String) As String
Dim n As Integer, i As Integer
    packages.Populate
    
    n = packages.Count
    For i = n - 1 To 0 Step -1
        If packages.Item(i).Value("Name") = PackageName Then
            FindPackage = packages.Item(i).Value("ID")
            Exit Function
    End If
    Next

End Function

Sub ShutDownPackage(PackageName As String)
Dim PackageID As String, PackUtil As Object
    PackageID = FindPackage(PackageName)
    If PackageID > "" Then
        Set PackUtil = packages.GetUtilInterface
        PackUtil.ShutDownPackage (PackageID)
    End If
End Sub

Function GetAllPackages() As Variant
Dim PackageName As String, n As Integer
Dim i As Integer, j As Integer

    packages.Populate
    n = packages.Count
    ReDim PackageArray(n)
    j = 0
    For i = n - 1 To 0 Step -1
        
        PackageName = packages.Item(i).Name
        If PackageName > "" Then
            j = j + 1
            PackageArray(j) = PackageName
        End If
    Next
    
    GetAllPackages = PackageArray
End Function

Sub ProcessCommandLine()
Dim CmdLine, CmdLnLen, i
Dim sCommand As String, sCommandParam As String
Dim iStart, iEnd
    CmdLine = Command()
    CmdLnLen = Len(CmdLine)
          
    iStart = InStr(CmdLine, " ")
    If iStart = 0 Then Exit Sub
    
    iEnd = Len(CmdLine)
    
    sCommand = Trim$(Mid$(CmdLine, 1, iStart))
    sCommandParam = Trim$(Mid$(CmdLine, iStart, iEnd))
    
    Select Case LCase(sCommand)
         Case "\shutdown"
             ShutDownPackage (sCommandParam)
     End Select
End Sub
