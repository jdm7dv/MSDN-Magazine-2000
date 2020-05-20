<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">

<xsl:template match="/">
  <UL>
     <xsl:apply-templates select="CLIENT/PEOPLE" />
  </UL>
</xsl:template>

<xsl:template match="PEOPLE">
	<LI CLASS="clsZeroDeep">People
		<UL style="display:block">
			<xsl:apply-templates select=".//PERSON" />
		</UL>
	</LI>
</xsl:template>

<xsl:script language="javascript">
<![CDATA[
  function GetNodeName() {
      return this.nodeName;
    }
    function GetNodeNameProper() {
      return (this.nodeName.charAt(0) + this.nodeName.substr(1).toLowerCase());
    }
]]>	
</xsl:script>
		
<xsl:template match="PERSON">
	<LI CLASS="clsOneDeep" >
		<xsl:value-of select="NAME" /> (<xsl:value-of select="TITLE"/>) 
		(
		<xsl:element name="A">
		    <xsl:attribute name="CLASS">clsOperation</xsl:attribute>
			<xsl:attribute name="ONCLICK">AddPerson("<xsl:value-of select="@ID" />")</xsl:attribute>
			Add
		</xsl:element>
		/
		<xsl:element name="A">
		    <xsl:attribute name="CLASS">clsOperation</xsl:attribute>
			<xsl:attribute name="ONCLICK">DeletePerson("<xsl:value-of select="@ID" />")</xsl:attribute>
			Delete
		</xsl:element>
		)
		<DIV CLASS="clsSummary" style="DISPLAY:none">
			<TABLE CLASS="clsSummaryTable">
				<xsl:apply-templates select="NAME | TITLE" />
			</TABLE>
		</DIV>
	</LI>
</xsl:template>

<xsl:template match="PERSON/(NAME | TITLE)">
	<TR>
		<TD CLASS="clsColumn1"><xsl:eval>GetNodeNameProper()</xsl:eval></TD>
		<TD CLASS="clsColumn2">
			<xsl:element name="INPUT">
				<xsl:attribute name="ID"><xsl:eval>GetNodeName()</xsl:eval><xsl:value-of select="@ID"/></xsl:attribute>
				<xsl:attribute name="VALUE"><xsl:value-of select="."/></xsl:attribute>
				<xsl:attribute name="ONCHANGE">infoxml.selectSingleNode(".//*[@ID ='<xsl:value-of select="@ID"/>']").text = <xsl:eval>GetNodeName()</xsl:eval><xsl:value-of select="@ID"/>.value;</xsl:attribute>	
			</xsl:element>
		</TD>
	</TR>			
</xsl:template>

</xsl:stylesheet>