<?xml version="1.0" encoding="utf-8"?>

<!--
//	Copyright (C) 2010, 2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
 *
 *	This file is part of Display Enumeration.
 *
 *	Display Enumeration is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Display Enumeration is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Display Enumeration.  If not, see <http://www.gnu.org/licenses/>.
-->

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
