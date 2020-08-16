<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:transform version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
			     xmlns:vty="urn:osmocom:xml:libosmocore:vty:doc:1.0" >
  <xsl:output method="xml" version="1.0" encoding="UTF-8" indent="yes" />

  <!-- tick off the filtering -->
  <xsl:template match="@*|node()">
    <xsl:apply-templates select="@*|node()" />
  </xsl:template>

  <!-- every node into a new file -->
  <xsl:template match="vty:node">
    <xsl:variable name="filename" select="concat('generated/docbook_vty_', @id, '.xml')" />
<!-- create a new section -->
<section>
    <title><xsl:value-of select="./vty:name" /></title>
    <para><xsl:value-of select="./vty:description" /></para>

    <!-- each command into a subsection now -->
    <xsl:for-each select="./vty:command">
      <xsl:sort select="@id" />
      <section>
        <xsl:choose>
          <xsl:when test="string-length(@id) &gt; 80">
            <title><xsl:value-of select="substring(@id, 1, 80)"/>...</title>
          </xsl:when>
          <xsl:otherwise>
            <title><xsl:value-of select="@id"/></title>
          </xsl:otherwise>
        </xsl:choose>

        <xsl:if test="./vty:description">
          <para><xsl:value-of select="./vty:description" /></para>
        </xsl:if>

        <variablelist><varlistentry>
            <listitem>
              <para>Command</para>
              <screen><xsl:value-of select="@id" /></screen>
            </listitem>
        </varlistentry></variablelist>

      <xsl:if test="./vty:attributes[@scope='application']">
        <variablelist>
          <varlistentry>
            <listitem>
              <para>Attributes</para>
            </listitem>
          </varlistentry>
        <xsl:for-each select="./vty:attributes[@scope='application']/*">
          <varlistentry>
            <listitem>
              <xsl:choose>
                <xsl:when test="@flag">
                  <para>Flag: <xsl:value-of select="@flag" /></para>
                </xsl:when>
                <xsl:otherwise>
                  <para>Flag: (not assigned)</para>
                </xsl:otherwise>
              </xsl:choose>
              <para><xsl:value-of select="@doc" /></para>
            </listitem>
          </varlistentry>
        </xsl:for-each>
        </variablelist>
      </xsl:if>

        <variablelist>
          <varlistentry>
            <listitem>
              <para>Parameters</para>
            </listitem>
          </varlistentry>
        <xsl:for-each select="./vty:params/*">
          <varlistentry>
            <listitem>
              <para><xsl:value-of select="@name" /></para>
              <para><xsl:value-of select="@doc" /></para>
            </listitem>
          </varlistentry>
        </xsl:for-each>
        </variablelist>

      </section>
    </xsl:for-each>
</section>
  </xsl:template>
</xsl:transform>
