OSMO_GSM_MANUALS_DIR = ..

ASCIIDOC = osmobsc-usermanual.adoc osmux-reference.adoc aoip-mgw-options.adoc
include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.asciidoc.inc
osmobsc-usermanual.pdf: chapters/*.adoc chapters/*.dot
aoip-mgw-options.pdf: aoip-mgw-options.adoc mgw/*.msc

VTY_REFERENCE = osmobsc-vty-reference.xml
include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.vty-reference.inc

include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.common.inc
