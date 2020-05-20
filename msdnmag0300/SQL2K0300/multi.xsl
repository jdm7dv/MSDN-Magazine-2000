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
<!--
<v:rect fillcolor="white" strokecolor="blue">
<xsl:attribute name="style">
    position:absolute;
    top: <xsl:eval>(parseInt(this.selectSingleNode("//measure/row/@ComputedColumn1").text)-
                    parseInt(this.selectSingleNode("//measure/row/@ComputedColumn2").text))
         </xsl:eval>;
    left:<xsl:value-of select='//measure/row/@ComputedColumn0' />;
    width:<xsl:value-of select='//measure/row/@ComputedColumn2' />;
    height:<xsl:value-of select='//measure/row/@ComputedColumn2' />;
</xsl:attribute>
</v:rect>
-->

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
                <xsl:attribute name="strokecolor"><xsl:eval>QCFCC(this)</xsl:eval></xsl:attribute>
        <xsl:attribute name="from"><xsl:value-of select="@frlong"/>,<xsl:value-of select="@frlat"/></xsl:attribute>
        <xsl:attribute name="to"><xsl:value-of select="@tolong"/>,<xsl:value-of select="@tolat"/></xsl:attribute>
    </xsl:element>
</xsl:template>

<xsl:script>
<![CDATA[
function CFCC(q)
{
    if ((q.attributes.getNamedItem("cfcc").nodeValue).indexOf("A") == 0) return true;
    return false;
}

function QCFCC(q)
{
    if ((q.attributes.getNamedItem("cfcc").nodeValue).indexOf("A") == 0) return "#008000";
    if ((q.attributes.getNamedItem("cfcc").nodeValue).indexOf("H") == 0) return "#0000FF";
    if ((q.attributes.getNamedItem("cfcc").nodeValue).indexOf("B") == 0) return "#A0522D";
    return "black";
}

function Coord(a,b)
{
    a = a + 0;
    b = b + 0;
   
    return a-b;
}
]]>
</xsl:script>

</xsl:stylesheet> 
