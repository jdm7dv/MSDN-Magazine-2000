<%@ LANGUAGE=VBSCRIPT %>
<% RSDispatch %>

<SCRIPT RUNAT=SERVER Language=javascript>
<!--#INCLUDE VIRTUAL="/_ScriptLibrary/RS.ASP"-->

	function Description()
	{ 
   	    this.GetEmployeeInfo = DoGetData;
	}
	public_description = new Description();


	function DoGetData(empName)
	{
            sql = "select * from Employees where [LastName]='" + empName + "'";
            rst = new ActiveXObject("ADODB.Recordset");
            rst.CursorLocation = 3; 	// adUseClient

            rst.Open(sql, "NW");
            i = 0;
	    	strText = "";

            if (rst.RecordCount == 1)  {
               strText += rst.Fields("EmployeeID").Value + " - " +
                          rst.Fields("TitleOfCourtesy").Value + " " + 
                          rst.Fields("FirstName").Value + " " + 
                          rst.Fields("LastName").Value;
               strText += "|";
               strText += rst.Fields("Title").Value;
               strText += "|";
               strText += rst.Fields("City").Value + " " + 
                          rst.Fields("Region").Value + ", " +
                          rst.Fields("Country").Value;
               strText += "|";
               d = new Date(rst.Fields("HireDate").Value);
               strText += (1+d.getMonth()) + "/" + d.getDate() + "/" + d.getYear();
            }

            return strText;
    	}
</SCRIPT>


