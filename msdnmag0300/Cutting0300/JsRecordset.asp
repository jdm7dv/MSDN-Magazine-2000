<SCRIPT RUNAT="SERVER" LANGUAGE="JavaScript">

// **************************************************************
//  JsRecordset.js 
//  Provides a Javascript implementation of ADO recordsets
//  
//  Dino Esposito (October 1999)
// **************************************************************


// ----------------------------------------------------------- 
// Creates a new object with as many fields as specified
// INPUT: <fields> it's a reference to an ADO Fields object
// ----------------------------------------------------------- 
function Record(fields)
{
	var i;
	
	// Add a new named property for each field in the recordset
	for (i=0; i<fields.Count; i++) {
		cmd = "this." + fields.Item(i).Name + " = \"" + fields.Item(i).Name + "\"";
		eval(cmd);
	}
}


// -----------------------------------------------------------
// Creates and fills a new array with as many records as the  
// specified ADO recordset 
// INPUT: <rst> it's a reference to an ADO recordset object
// -----------------------------------------------------------
function Recordset(rst)
{
	// Define the Items property being the collection of records
	this.Items = new Array();
	
	var i=0;
	var cmd = "";
	
	// For each record in the recordset creates a Record object
	// and populates its properties with the values
	numOfFields = rst.Fields.Count;
	while (!rst.EOF) {
		this.Items[i] = new Record(rst.Fields);
		
		for (j=0; j<numOfFields; j++) 
		{
			cmd = "this.Items[i]." + rst.Fields.Item(j).Name + " = String(rst.Fields.Item(j).Value)"; 
			eval(cmd);  
		}		

		rst.MoveNext();
		i++;
	}
	
	// Define the length property counting the records
	this.length = i;
}

// -----------------------------------------------------------
// Rebuilds the Javascript Recordset object from a 
// serialized version of it. 
// INPUT: <string representing a serialized RS> 
// -----------------------------------------------------------
function EvalRS(strRS)
{
	// The original string is in the form:
	//   <RETURN_VALUE...><METHOD...>
	//    var undefined; ...
	//   </RETURN_VALUE></METHOD>

	// Unescapes the original string
	strOriginal = unescape(strRS);
	
	// The string we're interested in begins with 'var undefined;'
	pos = strOriginal.indexOf("var");
	strRawData = strOriginal.substr(pos);
	
	// Removes the closing tags
	pos = strRawData.indexOf("</RETURN_VALUE></METHOD>");
	strRawData = strRawData.substring(0,pos);
	
	// Rebuilds the object and returns
	return eval(strRawData);
}
</SCRIPT>