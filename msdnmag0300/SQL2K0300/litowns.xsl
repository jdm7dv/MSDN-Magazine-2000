<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl"> 

<xsl:template match="/">

<HTML>

<HEAD><TITLE>Long Island towns and villages</TITLE>
</HEAD>

<script language="VBScript">
sub lstTowns_onchange()
    vall = frmTowns.lstTowns.value
    divValue.innerText = vall
    divName.innerText = frmTowns.lstTowns.item(frmTowns.lstTowns.selectedIndex).text
end sub

sub btnVal_onclick()
    dim xmlDoc, xslDoc

    set xmlDoc = CreateObject("microsoft.xmldom")
    set xslDoc = CreateObject("microsoft.xmldom")

    xmlDoc.async = false
    xslDoc.async = false

    xmlDoc.load("http://cordelia/tiger?sql=select+tlid,cfcc,fedirs,fename,fetype,fpll,fplr,frlat,frlong,tolat,tolong+from+tgr3610301+where+fpll=" + frmTowns.lstTowns.value + "+FOR+XML+RAW")
    xslDoc.load("http://cordelia/XSLFiles/borders.xsl")
    strout = xmlDoc.transformNode(xslDoc)
    divSegs.innerHTML = strout
    // divSegs.innerText = xmlDoc.xml
end sub

</script>


<BODY>
<p><FONT face="Arial" size="6"><STRONG>Long Island towns and 
villages</STRONG></FONT>    </p>
<p></p>
<form method="post" id="frmTowns">
  <table border="0">
    <tr>
      <td valign="top">
      <table>
         <tr> <td>
         <select size="8" id="lstTowns" name="lstTowns" onchange="lstTowns_onchange()">
         <xsl:apply-templates select="root" />
         </select>
         </td> </tr>
         <tr><td>
         <div>
         <FONT face="Arial">
             <input type="button" value="Get Segs" name="btnVal" id="btnVal" onclick="btnVal_onclick()" /> 
         </FONT>
         </div>
          Value: <div name="divValue" id="divValue"><FONT face="Arial">0</FONT></div>
          Name:  <div name="divValue" id="divName"><FONT face="Arial">(none)</FONT></div>
          </td></tr>
      </table>
      </td>
      <td><div id="divSegs"></div></td>
    </tr>

    <tr>
      <td></td>
    </tr>
  </table>  
</form>


</BODY>
</HTML>
</xsl:template>

<xsl:template match="root">
   <xsl:apply-templates select="//row" />
</xsl:template>

<xsl:template match="row">
   <OPTION>
       <xsl:attribute name="value"><xsl:value-of select="@fips"/></xsl:attribute>
       <xsl:value-of select="@name"/>
   </OPTION>
</xsl:template>

</xsl:stylesheet> 
