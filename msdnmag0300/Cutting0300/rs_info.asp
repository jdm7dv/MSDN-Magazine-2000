<%@ LANGUAGE="JavaScript" %>
<!--#INCLUDE VIRTUAL="/_ScriptLibrary/JsRecordset.ASP"-->

<HTML>
<BODY bgcolor="yellow">

<%
	// Attempt to get the passed data
	strText = Request.QueryString("info");
	if (strText == "")	Response.End();

	oRS = EvalRS(strText);
	if (typeof(oRS) == "undefined") {
		Response.Write ("No information available.");
		Response.End();
	}
	if (oRS.length == 0) {
		Response.Write ("No information available.");
		Response.End();
	}
%>

<table border=0>

<% 
	Response.Write ("<tr>");
	Response.Write ("<td><b>Employee:&nbsp&nbsp</b></td>");
	buf = oRS.Items[0].EmployeeID + " - " + 
		  oRS.Items[0].TitleOfCourtesy + " " + 
		  oRS.Items[0].FirstName + " " + 
		  oRS.Items[0].LastName;
	Response.Write ("<td>" + buf + "</td>");
	Response.Write ("</tr>");

	Response.Write ("<tr>");
	Response.Write ("<td><b>Title:</b></td>");
	Response.Write ("<td>" + oRS.Items[0].Title + "</td>");
	Response.Write ("</tr>");

	Response.Write ("<tr>");
	Response.Write ("<td><b>City:</b></td>");
	buf = oRS.Items[0].City + " " + 
		  oRS.Items[0].Region + ", " + 
		  oRS.Items[0].Country; 
	Response.Write ("<td>" + buf + "</td>");
	Response.Write ("</tr>");
	
	Response.Write ("<tr>");
	Response.Write ("<td><b>Hired on:</b></td>");
	d = new Date(oRS.Items[0].HireDate);
	if (isNaN(d))	{
		var str = oRS.Items[0].HireDate;
		re = /UTC /g;
		s = str.replace(re, "UTC+");
		d = new Date(s);
	}
	
	buf = (1+d.getMonth()) + "/" + d.getDate() + "/" + d.getYear(); 
	Response.Write ("<td>" + buf + "</td>");
	Response.Write ("</tr>");
%>

</table>
</BODY>
</HTML>
