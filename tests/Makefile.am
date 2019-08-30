OSMO_GSM_MANUALS_DIR = $(top_srcdir)
EXTRA_DIST = test-usermanual-docinfo.xml \
	test-vty-reference.xml \
	vty

# Do not install any of the test pdfs
OSMO_GSM_MANUALS_NO_INSTALL = 1

# Generate adoc file that includes all chapters (OS#4183: glossary.adoc must be the last file)
ASCIIDOC = test-usermanual.adoc
ASCIIDOC_DEPS =
COMMON_CHAPTERS = $(shell find $(OSMO_GSM_MANUALS_DIR)/common/chapters -name '*.adoc' | grep -v glossary\.adoc) \
		  $(OSMO_GSM_MANUALS_DIR)/common/chapters/glossary.adoc
$(ASCIIDOC): $(COMMON_CHAPTERS)
	echo ":gfdl-enabled:" > $@
	echo ":program-name: Test" >> $@
	echo "" >> $@
	echo "Osmo GSM Manuals Shared Content Test" >> $@
	echo "====================================" >> $@
	echo "Oliver Smith <osmith@sysmocom.de>" >> $@
	echo "" >> $@
	for chapter in $(COMMON_CHAPTERS); do \
		echo "include::$${chapter}[]" >> $@; \
	done;
CLEAN_FILES = $(ASCIIDOC)

include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.asciidoc.inc

VTY_REFERENCE = test-vty-reference.xml
include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.vty-reference.inc
include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.common.inc


default: all check


.DEFAULT_GOAL := default
.PHONY: default
