<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/">
		<html>
			<head>
				<title>Fields</title>
			</head>
			<body>
				<p>
					<xsl:for-each select="tbody/tr">
						if(mode.dmFields &amp; <xsl:value-of select="td[position()=1]"/>)<br/>
							tcout &lt;&lt; setw(indent) &lt;&lt; TEXT(' ') &lt;&lt; setw(w) &lt;&lt; TEXT("<xsl:value-of select="td/strong"/>: ") &lt;&lt; mode.<xsl:value-of select="td/strong"/> &lt;&lt; TEXT("\n");<br/>
					</xsl:for-each>
				</p>
			</body>
		</html>
	</xsl:template>

</xsl:stylesheet>
