<%@ LANGUAGE=VBSCRIPT %>
<% RSDispatch %>

<SCRIPT RUNAT=SERVER Language="JScript">
<!--#INCLUDE VIRTUAL="/_ScriptLibrary/RS.ASP"-->
<!--#INCLUDE VIRTUAL="/_ScriptLibrary/JSRECORDSET.ASP"-->

	function Description()
	{ 
   	    this.GetEmployeeInfo = DoGetEmployeeInfoAsRecordset;
	}
	public_description = new Description();


	function DoGetEmployeeInfoAsRecordset(empName)
	{
            sql = "select EmployeeID, FirstName, LastName, TitleOfCourtesy, City, HireDate, " +
                  "        Region, Country, Title from Employees" + 
                  "        where LastName='" + empName + "'";
            rst = new ActiveXObject("ADODB.Recordset");
            rst.CursorLocation = 3; 	// adUseClient

            rst.Open(sql, "NW");
            oRS = new Recordset(rst);
	    rst.Close();
	    return oRS; 
        }
</SCRIPT>

