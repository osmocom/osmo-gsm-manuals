# Usage:
# Have files:
# - osmoyada-vty-reference.xml
#   A docbook root XML including a &chapter-vty; reference.
# - vty/*additions*.xml
#   Manual additions to specific VTY nodes, any number of files.
# - vty/*_reference.xml
#   Export from VTY 'show online-help', exactly one file.
#   The vty/*_reference.xml file may also live in the $(builddir)/vty/,
#   in which case you need to add it to BUILT_REFERENCE_XML, and provide a build rule, like:
#      BUILT_REFERENCE_XML = $(builddir)/vty/osmoyada_reference.xml
#      $(builddir)/vty/osmoyada_reference.xml:
#              mkdir -p $(builddir)/vty
#              $(top_builddir)/src/osmoyada --vty-ref-xml > $@
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
#
# In order to add more than one VTY reference, do this for each additional one:
# - Extend VTY_REFERENCE with the new entry, make sure it ends in "-vty-reference.xml":
#	VTY_REFERENCE = osmofoo-vty-reference.xml osmobar-vty-reference.xml
# - Create a new osmobar-vty-reference.xml file, just like osmofoo-vty-reference.xml, but with
#   "generated/docbook_osmobar-vty-reference.xml" as sections-vty path instead of
#   "generated/docbook_vty.xml".
# - Create vty-osmobar/*_additions.xml and vty-osmobar/*_reference.xml. Pay attention to the
#   directory name, it must start with vty-* instead of "vty" and it must match the prefix of
#   your new VTY_REFERENCE entry ("vty-osmobar" in this example).
# - Add osmobar-vty-reference.xml and vty-osmobar to EXTRA_DIST in Makefile.am.
# - Full example: osmo-sgsn.git I24c3ca2fc2446673edceefb797c7d800c3a1a5d2
# - The vty-osmobar/*_reference.xml may also live in the builddir: add it to
#   BUILT_REFERENCE_XML and provide a build rule, like:
#      BUILT_REFERENCE_XML += $(builddir)/vty-osmobar/osmobar_reference.xml
#      $(builddir)/vty-osmobar/osmobar_reference.xml: $(top_builddir)/src/osmobar
#              mkdir -p $(builddir)/vty-osmobar
#              $(top_builddir)/src/osmobar --vty-ref-xml > $@

DOCBOOKS = $(VTY_REFERENCE)

# Directory for intermediate results
GEN_DIR = generated

# First VTY reference
DOCBOOKS_DEPS = $(GEN_DIR)/docbook_vty.xml

# Additional VTY references: prepend "$(GEN_DIR)/docbook_"
# For example:
# VTY_REFERENCE = osmosgsn-vty-reference.xml osmogbproxy-vty-reference.xml
# DOCBOOK_DEPS = $(GEN_DIR)/docbook_vty.xml $(GEN_DIR)/docbook_osmogbproxy-vty-reference.xml
DOCBOOKS_DEPS += $(patsubst %,$(GEN_DIR)/docbook_%,$(filter-out $(firstword $(VTY_REFERENCE)),$(VTY_REFERENCE)))

include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.docbook.inc

MERGE_DOC = $(shell realpath $(OSMO_GSM_MANUALS_DIR)/merge_doc.xsl)

CLEAN_FILES += $(GEN_DIR)
CLEAN_FILES += $(BUILT_REFERENCE_XML)

# First VTY reference
$(GEN_DIR)/docbook_vty.xml: \
			   $(srcdir)/vty/*xml \
			   $(BUILT_REFERENCE_XML) \
			   $(OSMO_GSM_MANUALS_DIR)/common/vty_additions.xml \
			   $(OSMO_GSM_MANUALS_DIR)/common/chapters/vty.xml \
			   $(OSMO_GSM_MANUALS_DIR)/vty_reference.xsl
	mkdir -p $(GEN_DIR)
	$(OSMO_GSM_MANUALS_DIR)/build/vty_reference_combine.sh "$(MERGE_DOC)" \
		$$($(OSMO_GSM_MANUALS_DIR)/build/find_existing_path.sh "vty/*reference.xml" $(builddir) $(srcdir)) \
		$(OSMO_GSM_MANUALS_DIR)/common/vty_additions.xml \
		$(srcdir)/vty/*additions*.xml
	xsltproc $(OSMO_GSM_MANUALS_DIR)/vty_reference.xsl $(GEN_DIR)/combined.xml \
		> $(GEN_DIR)/docbook_vty.xml

# Additional VTY references
$(GEN_DIR)/docbook_%-vty-reference.xml: \
			 $(srcdir)/vty-%/*xml \
			 $(BUILT_REFERENCE_XML) \
			 $(OSMO_GSM_MANUALS_DIR)/common/vty_additions.xml \
			 $(OSMO_GSM_MANUALS_DIR)/common/chapters/vty.xml \
			 $(OSMO_GSM_MANUALS_DIR)/vty_reference.xsl
	export VTYDIR_NAME="vty-$(patsubst $(GEN_DIR)/docbook_%-vty-reference.xml,%,$@)" && \
	export VTYDIR_SRC="$(srcdir)/$$VTYDIR_NAME" && \
	export VTYDIR_BUILD="$(builddir)/$$VTYDIR_NAME" && \
	export VTYGEN="$@_combine" && \
	mkdir -p $$VTYGEN && \
	$(OSMO_GSM_MANUALS_DIR)/build/vty_reference_combine.sh "$(MERGE_DOC)" \
		$$($(OSMO_GSM_MANUALS_DIR)/build/find_existing_path.sh "*reference.xml" $$VTYDIR_BUILD $$VTYDIR_SRC) \
		$(OSMO_GSM_MANUALS_DIR)/common/vty_additions.xml \
		$$VTYDIR_SRC/*additions*.xml && \
	xsltproc $(OSMO_GSM_MANUALS_DIR)/vty_reference.xsl $$VTYGEN/combined.xml > "$@"
