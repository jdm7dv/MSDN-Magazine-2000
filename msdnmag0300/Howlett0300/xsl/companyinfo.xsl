<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">

<xsl:template match="/">
     <xsl:apply-templates select="CLIENT/PEOPLE" />
</xsl:template>

<xsl:template match="PEOPLE">
  <DIV STYLE="margin-left: 1cm">
     <xsl:apply-templates select="PERSON"/>
  </DIV>
</xsl:template>

<xsl:template match="PERSON">
  <xsl:value-of select="NAME" /> (<U><xsl:value-of select="TITLE"/></U>)<BR/>
  <xsl:apply-templates select="PEOPLE" />
</xsl:template>

</xsl:stylesheet>
