<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">

<xsl:template match="/">
  <UL style="display:block">
     <xsl:apply-templates select=".//DOCUMENT" />
  </UL>
</xsl:template>

<xsl:script language="javascript">
    function GetNodeName() {
      return this.nodeName;
    }
    
    function GetNodeValue() {
      return this.text;
    } 
</xsl:script>

<xsl:template match="DOCUMENTS">
  <UL style="display:block">
     <xsl:apply-templates select="DOCUMENT" order-by="TITLE"/>
  </UL>
</xsl:template>

<xsl:template match="DOCUMENT">
	<LI CLASS="clsZeroDeep" >
	  <xsl:value-of select="TITLE" /> (<xsl:value-of select="AUTHORS/AUTHOR/AUTHOR_LNAME" />, <xsl:value-of select="AUTHORS/AUTHOR/AUTHOR_FNAME" />)
	  <DIV CLASS="clsSummary" style="DISPLAY:none">
	<TABLE CLASS="clsSummaryTable">
	<TR>
	  <TD CLASS="clsColumn1">Title</TD><TD CLASS="clsColumn2"><xsl:value-of select="TITLE"/></TD>
	</TR>
	<TR>
	  <TD CLASS="clsColumn1">Authors</TD>
	  <TD CLASS="clsColumn2">
	       <xsl:apply-templates select="AUTHORS/AUTHOR" />
	  </TD>
	</TR>
	<TR>
	  <TD CLASS="clsColumn1">Website</TD>
	  <TD CLASS="clsColumn2">
		<xsl:element name="A">
			<xsl:attribute name="HREF"><xsl:value-of select="URL" /></xsl:attribute>
			<xsl:value-of select="URL" />
		</xsl:element>
	  </TD>
	</TR>
	<TR>
	  <TD CLASS="clsColumn1">Publisher</TD><TD CLASS="clsColumn2"><xsl:value-of select="PUBLISHER"/></TD>
	</TR>
	<TR>
	  <TD CLASS="clsColumn1">Date</TD><TD CLASS="clsColumn2"><xsl:value-of select="DATE"/></TD>
	</TR>
	<TR>
	  <TD CLASS="clsColumn1">Pages</TD><TD CLASS="clsColumn2"><xsl:value-of select="PAGES"/></TD>
	</TR>
	<TR>
	  <TD CLASS="clsColumn1">Summary</TD><TD CLASS="clsColumn2"><xsl:value-of select="SUMMARY"/></TD>
	</TR>
	</TABLE>
	Comments:
	  </DIV>
	<UL>
	  <xsl:apply-templates select="NOTES/NOTE" order-by="-DATE" />
	</UL>
	</LI>
</xsl:template>

<xsl:template match="AUTHOR">
    <xsl:value-of select="AUTHOR_LNAME" />, <xsl:value-of select="AUTHOR_FNAME" />
    <BR/>
</xsl:template>

<xsl:template match="NOTE">
  <LI CLASS="clsNote">
    <xsl:value-of select="TITLE" />	
    (<xsl:value-of select="FNAME" /> <xsl:value-of select="LNAME" />, 
    <xsl:value-of select="DATE" />)
    <DIV CLASS="clsNoteText" style="DISPLAY:none"><xsl:value-of select="TEXT"/></DIV>
  </LI>
</xsl:template>


</xsl:stylesheet>
