<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">

<xsl:template match="/">
  <HTML>
  <HEAD>
  <TITLE>iMason.com Prospects</TITLE>
  <LINK REL="stylesheet" TYPE="text/css" HREF="/intranet/css/prospects.css" />
  <SCRIPT TYPE="text/javascript" LANGUAGE="javascript" SRC="/intranet/script/xsl.js"></SCRIPT>
  </HEAD>
  <BODY>
  <xsl:element name="A">
     <xsl:attribute name="href">http://www.imason.com</xsl:attribute>
     <xsl:element name="IMG">
       <xsl:attribute name="SRC">../images/imasonlogo.gif</xsl:attribute>
     </xsl:element>
  </xsl:element>
  <BR/>
  <H1>Prospects</H1><HR/>
  <TABLE>
	<TR>
		<TD VALIGN="top" STYLE="border-right:2px" >
			<B>Scott Howlett</B> (<xsl:eval>generateStats(this, 'Scott')</xsl:eval>)<BR/>
			<TABLE>
				<xsl:apply-templates select="PROSPECTS/PROSPECT[OWNER/FNAME='Scott']" order-by="+NAME"/>
			</TABLE>
		</TD>
		<TD VALIGN="top">
			<B>Jeff Dunmall</B> (<xsl:eval>generateStats(this, 'Jeff')</xsl:eval>)<BR/>
			<TABLE>
				<xsl:apply-templates select="PROSPECTS/PROSPECT[OWNER/FNAME='Jeff']" order-by="+NAME"/>
			</TABLE>
		</TD>
	</TR>
  </TABLE>
  <xsl:element name="IMG">
     <xsl:attribute name="SRC">../images/mcsp.gif</xsl:attribute>
     <xsl:attribute name="ALIGN">right</xsl:attribute>
  </xsl:element>
</BODY>
  </HTML>
</xsl:template>

<xsl:template match="PROSPECT">
	<TR>
		<TD>
			<A>
				<xsl:attribute name="HREF"><xsl:value-of select="INFOURL" /></xsl:attribute>
				<xsl:value-of select="NAME" />
			</A>
		</TD>
	</TR>
</xsl:template>

<xsl:script><![CDATA[
  function generateStats( e, fname ) {
	var strPattern = "PROSPECTS/PROSPECT[OWNER/FNAME='"
	strPattern += fname + "']"
	return(e.selectNodes( strPattern ).length);
	
  }
]]></xsl:script>

</xsl:stylesheet>
