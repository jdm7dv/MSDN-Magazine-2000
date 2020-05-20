function GetChildElem(eSrc,sTagName)
{
  var cKids = eSrc.children;
  for (var i=0;i<cKids.length;i++)
  {
    if (sTagName == cKids[i].tagName) return cKids[i];
  }
  return false;
}

function document.onclick()
{
  var eSrc = window.event.srcElement;
  
  if ("roundrect" == eSrc.tagName) 
  {
    	var eParent = eSrc.parentElement;
    	if( eParent = GetChildElem(eParent, "TABLE") )
    		eParent.style.display = ("block" == eParent.style.display ? "none" : "block");
  }
  else if ("clsOneDeep" == eSrc.className && (eChild = GetChildElem(eSrc,"DIV")))
    eChild.style.display = ("block" == eChild.style.display ? "none" : "block");
}

function fnSetInfo( ele ) 
{                                                             // Sets data format in first parameter
	event.dataTransfer.setData("Text", ele.id )
	event.dataTransfer.effectAllowed = "move";
}

// This function is called by the target object in the ondrop event.
function fnGetInfo( ele )
{
  event.returnValue = false;                           // Cancels default action.
  event.dataTransfer.dropEffect = "move";             // Sets cursor to system move icon.
  MovePerson( event.dataTransfer.getData("Text"), ele.id );
}
function fnCancelDefault()
{                                           // Cancel default action in ondragenter
  event.returnValue = false;                // and ondragover so that move cursor will  
  event.dataTransfer.dropEffect = "move";  // display until selection is dropped.
}

var strSitename
var strCompany
  
function window_onload() 
{
  var oXML
  var oXSL
  var xslHTML
	  
  oXML = new ActiveXObject("Microsoft.XMLDOM");
  oXML.async = false;
  oXSL = new ActiveXObject("Microsoft.XMLDOM");
  oXSL.async = false;
      
  strSitename = "/VMLArticle"
  strCompany = "WidgetCorp"
      
  strPath = strSitename + "/sales/" + strCompany; 
      		
  //load the xml document
  oXML.load(strPath + "/" + "info.xml");
      
  //fill the xml data island	
  infoxml.loadXML(oXML.xml);
	        
  //load xsl and transform the node
  oXSL.load(strSitename + "/xsl/header.xsl");	
  xslHTML = infoxml.transformNode(oXSL);
  document.all.item("header").innerHTML = xslHTML;

  //load orgchart xsl
  oXSL.load(strSitename + "/xsl/orgchart.xsl");
  orgchartxsl.loadXML(oXSL.xml);
  
  //load companyinfo xsl
  oXSL.load(strSitename + "/xsl/edit.xsl");
  companyinfoxsl.loadXML(oXSL.xml);
  
  ReloadEdit();
  ReloadOrgChart();
}
    
function ReloadOrgChart() 
{
	// OrgChart
	document.all.item("orgchart").innerHTML = infoxml.transformNode(orgchartxsl.XMLDocument);
}

function ReloadEdit() 
{
	// reindex the xml
	indexXML(infoxml);

	document.all.item("companyinfo").innerHTML = infoxml.transformNode(companyinfoxsl.XMLDocument);
 }
	     
function SaveXML() 
{  
	var objhttp = new ActiveXObject("Microsoft.XMLHTTP");

	objhttp.Open("POST",strSitename + "/Sales/savexml.asp?company=" + strCompany, false);
	// strip off ID attribute
	removeIndexXML(infoxml);
	
	objhttp.send(infoxml.XMLDocument);
	
	if (objhttp.responseText!="")
		alert(objhttp.responseText);
	else
		alert("Save successful.");
}

function indexXML(XML)
    {
		var objCol = XML.getElementsByTagName("*");
  		for (var i=0; i< objCol.length; i++)	
  		{
  			var att = XML.createAttribute("ID");
  			att.value = i;
  			objCol(i).attributes.setNamedItem(att);
  		}
    }
	    
function removeIndexXML(XML)
{
	var objCol = XML.getElementsByTagName("*");
	for (var i=0; i< objCol.length; i++)	
		objCol(i).attributes.removeNamedItem("ID");
}

function AddPersonToPeople(objPerson, objNewNode)
{
	try
	{
		// add to the people collection
		objPerson.selectNodes("PEOPLE")(0).appendChild(objNewNode);
	}
	catch (e)
	{
		// if that failed, then there is no people collection, so create one
		var newPeople;
		var newtree;

		newPeople = objPerson.ownerDocument.createNode(1,"PEOPLE","");
		newtree = objPerson.appendChild(newPeople);
		newtree.appendChild(objNewNode);
	}
}
		     		
function AddPerson(strID) 
{
	var objNew, objPerson, oXSL, strName, strSearchString			
	var strName = window.prompt("Name:","");
			
	// make sure the name  is unique
	objPerson = infoxml.selectSingleNode("CLIENT/PEOPLE//PERSON[NAME= '" + strName + "']");
			
	if (objPerson!=null) {
		alert("No two people can have the same name in a company!");
		return;
	}
			
	//find the parent node to attach the new person
	strSearchString = ".//PERSON[@ID = '" + strID + "']";
	objPerson = infoxml.selectSingleNode(strSearchString);
			
	// make a copy of the node (this will become the new person)
	objNew = objPerson.cloneNode(true);

	try
	{
		// remove a people node from the clone, if there is one
		objNew.removeChild(objNew.selectNodes("PEOPLE").item(0));
    }
	catch(e)
	{
	}
			
	// erase the contents of the clone
	for(var i=0;i<objNew.childNodes.length;i++) {
		objNew.childNodes(i).text = "";
	}
			
	// set the first and last name for the person
	objNew.selectNodes("NAME")(0).text = strName;

	AddPersonToPeople(objPerson, objNew);
					
	ReloadEdit();
	ReloadOrgChart();		
}
		
function DeletePerson(strID) {
 	var oXSL
 	var xslHTML
 	var objChildren
 	var strSearchString
			
 	oXSL = new ActiveXObject("Microsoft.XMLDOM");
					
 	// find the right node to delete
 	strSearchString = ".//PERSON[@ID = '" + strID + "']";
 	objPerson = infoxml.selectSingleNode(strSearchString);
			
 	// check if the person has children
 	objChildren = objPerson.selectNodes("PEOPLE")(0);
			
 	if (objChildren!=null) {
 		if (objChildren.childNodes.length>0) {
 			alert("You cannot delete a node with children.");
 			return;
 		}
 	}
			
 	objPerson.parentNode.removeChild(objPerson);
			
 	ReloadEdit();
 	ReloadOrgChart();
 }
		
function MovePerson(SourceID, DestinationID)
{
	var strSearchString
	var objSource, objDest
		
	if (SourceID == DestinationID) {
		alert("You cannot move a person onto themselves.");
		ReloadEdit();
		ReloadOrgChart();
		return;
	}
		
		
	// find the source node
	strSearchString = ".//PERSON[@ID = '" + SourceID + "']";
	objSource = infoxml.selectSingleNode(strSearchString);
			
	// find the destination node
	if (DestinationID=="TOP")
	{
		objDest = infoxml.selectSingleNode("CLIENT");		// top level reference
	}
	else
	{		
		strSearchString = ".//PERSON[@ID = '" + DestinationID + "']";
		objDest = infoxml.selectSingleNode(strSearchString);
	}

	// Remove the node from the source
	objSource.parentNode.removeChild(objSource);
		
	// And add it to the destination person
	AddPersonToPeople(objDest, objSource);
		
	// Reload
	ReloadEdit();
	ReloadOrgChart();
}
	
function cmdSearch_onclick() 
{
	var strPattern = "//PERSON";
	if (chkManual.checked)
		strPattern = txtManual.value;
	else
	{	
		if (chkCertification.checked)
			(txtCertification.value.length == 0) ? strPattern += "[CERTIFICATION]" : strPattern += "[CERTIFICATION = '" + txtCertification.value + "']";
		if (chkDegree.checked)
			(txtDegree.value.length == 0) ? strPattern += "[DEGREE]" : strPattern += "[DEGREE = '" + txtDegree.value + "']";
		if (chkPublication.checked)
			(txtPublication.value.length == 0) ? strPattern += "[PUBLICATION]" : strPattern += "[PUBLICATION = '" + txtPublication.value + "']";
		txtManual.value = strPattern;
	}			

	//Unhighlight all spans
	var objSpans = document.getElementsByTagName("DIV");
	for (var i=0; i< objSpans.length; i++)
		objSpans(i).style.color = "black";

	//Select matched nodes and highlight
	var objCol = infoxml.selectNodes(strPattern + "/@ID");
	for (var i=0; i< objCol.length; i++)	
		document.all(objCol(i).text).style.color = "blue";
}
