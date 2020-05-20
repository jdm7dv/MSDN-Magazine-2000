<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl"> 

<xsl:template match="/">
    <table>
   <tr>
   <td bgcolor="#C4B179"><font size="1" face="Arial">tlid</font></td>
   <td bgcolor="#CA95FF"><font size="1" face="Arial">Street</font></td>
   <td bgcolor="#CA95FF"><font size="1" face="Arial">Type</font></td>
   <td bgcolor="#CA95FF"><font size="1" face="Arial">frlat</font></td>
   <td bgcolor="#CA95FF"><font size="1" face="Arial">frlong</font></td>
   <td bgcolor="#CA95FF"><font size="1" face="Arial">tolat</font></td>
   <td bgcolor="#CA95FF"><font size="1" face="Arial">tolong</font></td>
    </tr>
        <xsl:apply-templates select="root"/>
    </table>
</xsl:template>

<xsl:template match="root">
   <xsl:apply-templates select="row"/>
</xsl:template>

<xsl:template match="row">
   <tr>
   <td bgcolor="#C4B179"><font size="1" face="Arial">
   <xsl:value-of select="@tlid"/>
   </font></td>
   <td bgcolor="#C4B179"><font size="1" face="Arial">
   <xsl:value-of select="@fedirs"/>  <xsl:value-of select="@fename"/>  <xsl:value-of select="@fetype"/> 
   </font></td>
   <td bgcolor="#CA95FF"><font size="1" face="Arial">
   <xsl:value-of select="@cfcc"/>
   </font></td>
   <td bgcolor="#CA95FF"><font size="1" face="Arial">
   <xsl:value-of select="@frlat"/>
   </font></td>
   <td bgcolor="#CA95FF"><font size="1" face="Arial">
   <xsl:value-of select="@frlong"/>
   </font></td>
   <td bgcolor="#CA95FF"><font size="1" face="Arial">
   <xsl:value-of select="@tolat"/>
   </font></td>
   <td bgcolor="#CA95FF"><font size="1" face="Arial">
   <xsl:value-of select="@tolong"/>
   </font></td>
</tr>
</xsl:template>

</xsl:stylesheet> 
