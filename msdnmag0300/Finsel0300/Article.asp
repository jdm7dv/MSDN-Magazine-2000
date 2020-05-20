<%@ Language=VBScript %>
<% option explicit %>


<HTML>
<HEAD>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
</HEAD>
<BODY>
<table width="100%" border=1>
<TR><TH width="25%">Title</TH><TH width="10%">Size</TH><TH width="10%">Date</TH><TH width="*">Description</TH>
<%
	dim objPropReader		' Property Reading object
	dim objFileProps		' Object that stores the file properties
	dim objFSO				' File System Object
	dim objFile				' File Object
	dim objFolder			' Folder Object
	dim sMapPath			' String to store the Real Path

	on error resume next	
	'
	' Create File System Object to get list of files
	'
	set objFSO = createobject("Scripting.FileSystemObject")
	
	'
	' Set the Property Reader to get the file properties
	'
	Set objPropReader = CreateObject("DSOLEFILE.PropertyReader") 	
	
	'
	' Get the NT path for the web page
	'
	sMapPath = Server.MapPath(".")
	
	'
	' Set the folder object to the Mapped Path
	'
	
	set objFolder = objFSO.GetFolder(sMapPath)
	
	'
	' For each file in the folder
	'
	for each objFile in objFolder.files 		
		
		'
		' Read the file properties so we have the Title and Description.
		' In order to do this we need to use the .PATH which contains the
		' path and the file name.  .NAME only contains the file name.
		'
		set objFileProps= objPropReader.GetDocumentProperties(objfile.path)
		if err.number = 0 then 
			%>
			 <TR><TD width="25%">
			 
			 <A HREF="<%=objFile.Name%>"><%
			 '
			 ' Having used the name of the file in the HREF above, now we need to
			 ' check to see if we have a title to use.  If we dont' have a title
			 ' then we'll use the file name.
			 '
			 if trim(objFileProps.Title) = "" then 
				Response.Write objFile.Name
			 else 
				Response.Write trim(objFileProps.Title)
			 end if%></a></TD>
			 
			 <TD width="10%" align="Right"> 
			 <%
			 
			 '
			 ' We'll format the file size so it looks pretty.
			 '
			if objFile.size < 10240 then 
				Response.Write objFile.size & " Bytes"
			elseif objFile.size < 1048576 then
				Response.Write round(objFile.size/1024,1) & "KB"
			else
				Response.Write round((objFile.size/1024)/1024,1) & "MB"
			end if
			 %></td>
			 <TD><%=objFile.DateLastModified %></TD>
			 <TD width="*">  <%=objFileProps.Comments%> </TD> </tr>
			<%
		end if
		err.clear
	next
%>
</table><BR><BR>

</BODY>
</HTML>

