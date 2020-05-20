<%@LANGUAGE=VBScript%>

<%

Set newxml = Server.CreateObject("Microsoft.XMLDOM")

newxml.async=false
newxml.load(Request)

newxml.save(Server.MapPath(Request.QueryString("Company") & "/info.xml"))

%>