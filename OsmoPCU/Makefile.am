OSMO_GSM_MANUALS_DIR = $(top_srcdir)

ASCIIDOC = osmopcu-usermanual.adoc osmopcu-gb.adoc
include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.asciidoc.inc
osmopcu-gb.pdf: $(srcdir)/gb/*.adoc $(srcdir)/gb/*.msc
osmopcu-usermanual.pdf: $(srcdir)/chapters/*.adoc

VTY_REFERENCE = osmopcu-vty-reference.xml
include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.vty-reference.inc

include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.common.inc
