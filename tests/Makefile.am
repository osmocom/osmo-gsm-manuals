OSMO_GSM_MANUALS_DIR = $(top_srcdir)

# Generate adoc file that includes all chapters
ASCIIDOC = test-usermanual.adoc
ASCIIDOC_DEPS =
$(ASCIIDOC): $(OSMO_GSM_MANUALS_DIR)/common/chapters/*.adoc
	echo ":gfdl-enabled:" > $@
	echo ":program-name: Test" >> $@
	echo "" >> $@
	echo "Osmo GSM Manuals Shared Content Test" >> $@
	echo "====================================" >> $@
	echo "Oliver Smith <osmith@sysmocom.de>" >> $@
	echo "" >> $@
	for chapter in $(OSMO_GSM_MANUALS_DIR)/common/chapters/*.adoc; do \
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
