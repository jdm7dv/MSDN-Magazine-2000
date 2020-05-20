<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl"
                xmlns:v="urn:schemas-microsoft-com:vml" >

<xsl:template match="/">
<HTML xmlns:v="urn:schemas-microsoft-com:vml" >
<HEAD bgcolor="gray">
    <TITLE>VML Line Sample</TITLE>

<STYLE>
v\:* { behavior: url(#default#VML); }
</STYLE> 

</HEAD>

<BODY TOPMARGIN="0" LEFTMARGIN="0" MARGINHEIGHT="0" MARGINWIDTH="0" BGCOLOR="#FFFFFF">

<H1><font face="Arial"><strong>Welcome to New York!</strong></font></H1>
<HR />

<v:group style="position:relative;left:2pt;top:2pt;width:3.5in;height:3.5in;">
<xsl:attribute name="coordorigin">
    <xsl:value-of select='//measure/row/@ComputedColumn0' />,
    <xsl:value-of select='//measure/row/@ComputedColumn1' />
</xsl:attribute>
<xsl:attribute name="coordsize">
    <xsl:value-of select='//measure/row/@ComputedColumn2' />,
    -<xsl:value-of select='//measure/row/@ComputedColumn2' />
</xsl:attribute>

<xsl:apply-templates select="root/linesegs/row" />
</v:group>

<HR />
<font size="1" face="Arial">(c) 2000 MSDN Magazine - Written by <a
href="mailto:joshuat@microsoft.com">Joshua Trupin</a></font>

</BODY>
</HTML>
</xsl:template>

<xsl:template match="row">
    <xsl:element name="v:line">
                <xsl:attribute name="strokecolor">red</xsl:attribute>
        <xsl:attribute name="from"><xsl:value-of select="@frlong"/>,<xsl:value-of select="@frlat"/></xsl:attribute>
        <xsl:attribute name="to"><xsl:value-of select="@tolong"/>,<xsl:value-of select="@tolat"/></xsl:attribute>
    </xsl:element>
</xsl:template>

</xsl:stylesheet> 
