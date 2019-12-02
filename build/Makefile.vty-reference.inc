# Usage:
# Have files:
# - osmoyada-vty-reference.xml
#   A docbook root XML including a &chapter-vty; reference.
# - vty/*additions*.xml
#   Manual additions to specific VTY nodes, any number of files.
# - vty/*_reference.xml
#   Export from VTY 'show online-help', exactly one file.
#
# In your Makefile.am,
# - define 'OSMO_GSM_MANUALS_DIR' to point at the osmo-gsm-manuals shared files
#   installation path as returned by "pkg-config osmo-gsm-manuals --variable=osmogsmmanualsdir"
#   (project specific repos set this with configure.ac),
# - define the (single) name of the vty-reference source in VTY_REFERENCE,
# - include this file.
#
# e.g.
#
#     OSMO_GSM_MANUALS_DIR = ..
#     VTY_REFERENCE = osmofoo-vty-reference.xml
#     include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.vty-reference.inc
#
# This uses the Makefile.docbook.inc, you should not mix uses of
# Makefile.vty-reference.inc and Makefile.docbook.inc.

DOCBOOKS = $(VTY_REFERENCE)
DOCBOOKS_DEPS = generated/docbook_vty.xml
include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.docbook.inc

MERGE_DOC = $(shell realpath $(OSMO_GSM_MANUALS_DIR)/merge_doc.xsl)

CLEAN_FILES += generated

generated/docbook_vty.xml: \
			   $(srcdir)/vty/*xml \
			   $(OSMO_GSM_MANUALS_DIR)/common/vty_additions.xml \
			   $(OSMO_GSM_MANUALS_DIR)/common/chapters/vty.xml \
			   $(OSMO_GSM_MANUALS_DIR)/vty_reference.xsl
	$(OSMO_GSM_MANUALS_DIR)/build/vty_reference_combine.sh "$(MERGE_DOC)" \
		$(srcdir)/vty/*reference.xml \
		$(OSMO_GSM_MANUALS_DIR)/common/vty_additions.xml \
		$(srcdir)/vty/*additions*.xml
	xsltproc $(OSMO_GSM_MANUALS_DIR)/vty_reference.xsl generated/combined.xml \
		> generated/docbook_vty.xml
