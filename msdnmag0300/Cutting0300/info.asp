<HTML>
<BODY bgcolor="yellow">

<%
	' Attempt to get the passed data
	strText = Request.QueryString("info")
	If strText = "" Then Response.End

	' Convert the data into an array
	arrData = split(strText, "|")

	' Set the array of labels
	arrLabels = split("Employee,Title,City,Hired on", ",")
%>

<table border=0>

<% 
	for i=0 to 3
		Response.Write "<tr>"
		Response.Write "<td><b>" & arrLabels(i) & "</b></td>" 
		Response.Write "<td><i>" & arrData(i) & "</i></td>" 
	next
%>

</table>

</BODY>
</HTML>
