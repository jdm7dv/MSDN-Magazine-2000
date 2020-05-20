<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl"   xmlns:v="urn:schemas-microsoft-com:vml" >

<xsl:template match="/">
<HTML xmlns:v="urn:schemas-microsoft-com:vml" >
<HEAD bgcolor="gray">
    <TITLE>VML Line Sample</TITLE>

<STYLE>
v\:* { behavior: url(#default#VML); }
</STYLE> 

</HEAD>

<BODY TOPMARGIN="0" LEFTMARGIN="0" MARGINHEIGHT="0" MARGINWIDTH="0" BGCOLOR="#9DFE81">

<table border="0" cellpadding="0" cellspacing="0">
    <tr>
        <td><H1><font face="Arial"><strong>NYC in VML Sample 1.005</strong></font></H1></td>
    </tr>
    <tr>
        <td><font size="1" face="Arial">(c) 1999 Microsoft Internet Developer - Written by <a
        href="mailto:joshuat">Joshua Trupin</a></font></td>
    </tr>
</table>

<HR />

<v:group coordsize="150000,-150000" 
         coordorigin="-74100000,40900000"
         style='position:relative;left:2pt;top:2pt;width:3.5in; height:3.5in;'
         >
<v:rect style='width:300000;height:300000;' fillcolor="white" strokecolor="blue"/>
<xsl:apply-templates select="root/row" />
</v:group>

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

]]>
</xsl:script>

</xsl:stylesheet> 
