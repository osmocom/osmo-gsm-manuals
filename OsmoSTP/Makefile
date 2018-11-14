OSMO_GSM_MANUALS_DIR = ..

ASCIIDOC = osmostp-usermanual.adoc
include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.asciidoc.inc
osmostp-usermanual.pdf: chapters/*.adoc
aoip-mgw-options.pdf: aoip-mgw-options.adoc mgw/*.msc

VTY_REFERENCE = osmostp-vty-reference.xml
include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.vty-reference.inc

include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.common.inc
