OSMO_GSM_MANUALS_DIR = ..

ASCIIDOC = osmopcu-usermanual.adoc osmopcu-gb.adoc
include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.asciidoc.inc
osmopcu-gb.pdf: gb/*.adoc gb/*.msc
osmopcu-usermanual.pdf: chapters/*.adoc

VTY_REFERENCE = osmopcu-vty-reference.xml
include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.vty-reference.inc

include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.common.inc
