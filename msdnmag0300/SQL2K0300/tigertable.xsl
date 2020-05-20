<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl"> 

<xsl:template match="/">
<HTML>
<HEAD><TITLE>Simple XSL Output</TITLE></HEAD>

<BODY>
<H2>Boundary roads</H2>
<p/>

<table border="0" cellpadding="1" cellspacing="1">
   <tr><td bgcolor="#C4B179"><font size="2" face="Arial"><B>Feature ID</B></font></td>
       <td bgcolor="#CA95FF"><font size="2" face="Arial"><B>Left/Right ZIP</B></font></td>
       <td bgcolor="#66CC66"><font size="2" face="Arial"><B>Feature Name</B></font></td>
   </tr>
    <xsl:apply-templates select="root"/>
</table>

</BODY>
</HTML>
</xsl:template>

<xsl:template match="root">
   <xsl:apply-templates select="row"/>
</xsl:template>

<xsl:template match="row">
   <tr><td bgcolor="#C4B179"><font size="2" face="Arial">
           <xsl:value-of select="@tlid"/></font></td>
       <td bgcolor="#CA95FF"><font size="2" face="Arial">
           <xsl:value-of select="@zipl"/>/<xsl:value-of select="@zipr"/></font></td>
       <td bgcolor="#66CC66"><font size="2" face="Arial">
           <xsl:value-of select="@fedirs"/> <xsl:value-of select="@fename"/> <xsl:value-of select="@fetype"/></font></td>
   </tr>
</xsl:template>

</xsl:stylesheet> 
