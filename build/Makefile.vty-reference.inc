# Usage:
# Have files:
# - osmoyada-vty-reference.xml
#   A docbook root XML including a &chapter-vty; reference.
# - vty/*additions*.xml
#   Manual additions to specific VTY nodes, any number of files.
# - vty/*_reference.xml
#   Export from VTY 'show online-help', exactly one file.
#
# In your Makefile,
# - define 'TOPDIR' to point at the git root,
# - define the (single) name of the vty-reference source in VTY_REFERENCE,
# - include this file.
#
# e.g.
#
#     TOPDIR = ..
#     VTY_REFERENCE = osmofoo-vty-reference
#     include $(TOPDIR)/build/Makefile.vty-reference.inc
#
# This uses the Makefile.docbook.inc, you should not mix uses of
# Makefile.vty-reference.inc and Makefile.docbook.inc.

DOCBOOKS = $(VTY_REFERENCE)
DOCBOOKS_DEPS = generated/docbook_vty.xml
include $(TOPDIR)/build/Makefile.docbook.inc

LIBOSMO_DIR ?= ~/source/gsm/libosmocore
MERGE_DOC = $(shell realpath $(LIBOSMO_DIR)/doc/vty/merge_doc.xsl)

CLEAN_FILES += generated

generated/docbook_vty.xml: \
			   vty/*xml \
			   $(TOPDIR)/common/vty_additions.xml \
			   $(TOPDIR)/common/chapters/vty.xml \
			   $(TOPDIR)/vty_reference.xsl
	$(TOPDIR)/build/vty_reference_combine.sh "$(MERGE_DOC)" \
		$(TOPDIR)/common/vty_additions.xml \
		vty/*additions*.xml
	xsltproc $(TOPDIR)/vty_reference.xsl generated/combined.xml \
		> generated/docbook_vty.xml
