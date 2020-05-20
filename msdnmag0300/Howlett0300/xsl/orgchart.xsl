<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl" >

<xsl:template match="/">
	<UL style="margin-bottom: 0px">
		<LI CLASS="clsZeroDeep" ID="TOP" ondrop="fnGetInfo( this )" 
			ondragenter="fnCancelDefault()"
			ondragover="fnCancelDefault()">Organization Chart
		</LI>
	    <DIV CLASS="clsSummary" style="DISPLAY:block" >
			<xsl:apply-templates select="CLIENT/PEOPLE" />
		</DIV>
	</UL>	
</xsl:template>

<xsl:template match="PEOPLE">
	<TABLE border="0" style="display: block">
	<TR>
    <xsl:apply-templates select="PERSON" />
    </TR>
    </TABLE>
</xsl:template>

<xsl:template match="PERSON">
	<TD align="center" valign="top" >
	<xsl:element name="v:roundrect" >
		<xsl:choose>
			<xsl:when test="PEOPLE/PERSON">
				<xsl:attribute name="style">width:110pt;height:33pt;cursor:hand</xsl:attribute>
			</xsl:when>
			<xsl:otherwise>
				<xsl:attribute name="style">width:110pt;height:33pt;cursor:default</xsl:attribute>
			</xsl:otherwise>
		</xsl:choose>
		<xsl:attribute name="fillcolor">#ecac04</xsl:attribute>
		<xsl:element name="v:fill">
			<xsl:attribute name="color2">#F4DC8C</xsl:attribute>
			<xsl:attribute name="type">gradient</xsl:attribute>
		</xsl:element>
		<xsl:element name="v:textbox">
			<xsl:attribute name="style">padding-left: 0px</xsl:attribute>
			<DIV style="font-size: 8pt" align="center">
				<xsl:attribute name="ondragstart">fnSetInfo( this )</xsl:attribute>
				<xsl:attribute name="ondragenter">fnCancelDefault()</xsl:attribute>
				<xsl:attribute name="ondrop">fnGetInfo( this )</xsl:attribute>
				<xsl:attribute name="ondragover">fnCancelDefault()</xsl:attribute>
			    <xsl:attribute name="id"><xsl:value-of select="@ID" /></xsl:attribute>
			    <xsl:attribute name="TITLE">Certifications: <xsl:apply-templates select="CERTIFICATION" />Degrees: <xsl:apply-templates select="DEGREE" />Publications: <xsl:apply-templates select="PUBLICATION" />
				</xsl:attribute>
				<b><xsl:value-of select="NAME" /></b><BR/> (<xsl:value-of select="TITLE"/>)
			</DIV>
		</xsl:element>
		<xsl:if test="PEOPLE/PERSON" >
			<xsl:element name="v:shadow">
				<xsl:attribute name="on">true</xsl:attribute>
				<xsl:attribute name="type">perspective</xsl:attribute>
				<xsl:attribute name="offset">4pt,4pt</xsl:attribute>
			</xsl:element>
		</xsl:if>
	</xsl:element>	
	<xsl:apply-templates select="PEOPLE" />
	</TD>
</xsl:template>

<xsl:template match="CERTIFICATION | PUBLICATION | DEGREE">
<xsl:value-of select="." /> | 
</xsl:template>

</xsl:stylesheet>

