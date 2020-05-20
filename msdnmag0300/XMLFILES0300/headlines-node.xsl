<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">

  <xsl:template match="Headline">
    <DIV class="title"><xsl:value-of select="Title"/></DIV>
    <DIV class="subtitle"><xsl:value-of select="Subtitle"/></DIV>
    <DIV class="link"><a><xsl:attribute name="href"><xsl:value-of select="StoryLink"/></xsl:attribute><xsl:value-of select="StoryLink"/></a></DIV>
    <DIV class="abstract"><xsl:value-of select="Abstract"/></DIV>
    <DIV class="author"><xsl:value-of select="Author/Name"/>, <xsl:value-of select="Author/Affiliation"/></DIV>
    <DIV class="date"><xsl:value-of select="DateTimePosted/@Month"/>/<xsl:value-of select="DateTimePosted/@Day"/>/<xsl:value-of select="DateTimePosted/@Year"/> - <xsl:value-of select="DateTimePosted/@Hour"/>:<xsl:value-of select="DateTimePosted/@Minute"/>:<xsl:value-of select="DateTimePosted/@Second"/></DIV>
    <BR/>
  </xsl:template>

</xsl:stylesheet>
