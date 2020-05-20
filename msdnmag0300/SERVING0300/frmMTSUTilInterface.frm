Option Explicit

Private Sub cmdListPackages_Click()
    ListPackages
End Sub

Private Sub cmdShutdownpackage_Click()
    ShutDownPackage (lstPackages.List(lstPackages.ListIndex))
End Sub

Private Sub lstPackages_Click()
    cmdShutdownpackage.Visible = True
End Sub

Sub ListPackages()
Dim sPackages As Variant, sTemp As String
Dim i As Integer
    sPackages = GetAllPackages()
    lstPackages.Clear
    For i = 0 To UBound(sPackages)
        If sPackages(i) > "" Then
            lstPackages.AddItem sPackages(i)
        End If
    Next
End Sub
