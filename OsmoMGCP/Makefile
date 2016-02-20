# XSL stylesheets downloaded from http://docbook.sourceforge.net/release/xsl/current/html/
# Makefile from BitBake/OpenEmbedded manuals

EXTRA_DEPS = gen-mgcp-vty-docbook

topdir = .
mgcp_reference = $(topdir)/osmomgcp-vty-reference.xml
manuals = $(mgcp_reference)
# types = pdf txt rtf ps xhtml html man tex texi dvi
# types = pdf txt
types = $(docbooktotypes)
docbooktotypes = pdf
# htmlcssfile =
# htmlcss =

include ../build/Makefile.inc

clean:
	rm -rf $(cleanfiles)

gen-mgcp-vty-docbook: FORCE
	$(call command,xsltproc -o generated/combined1.xml \
		--stringparam with $(PWD)/../common/vty_additions.xml \
		$(MERGE_DOC) vty/mgcp_vty_reference.xml, \
		XSLTPROC,Merging Common VTY)
	$(call command,xsltproc -o generated/combined2.xml \
		--stringparam with $(PWD)/vty/mgcp_vty_additions.xml \
		$(MERGE_DOC) generated/combined1.xml, \
		XSLTPROC,Merging MGCP VTY)
	$(call command,xsltproc ../vty_reference.xsl generated/combined2.xml > generated/docbook_vty.xml, \
		XSLTPROC,Converting MGCP VTY to DocBook)
