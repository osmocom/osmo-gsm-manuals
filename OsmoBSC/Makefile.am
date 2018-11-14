OSMO_GSM_MANUALS_DIR = $(top_srcdir)

ASCIIDOC = osmobsc-usermanual.adoc osmux-reference.adoc aoip-mgw-options.adoc
include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.asciidoc.inc
osmobsc-usermanual.pdf: $(srcdir)/chapters/*.adoc $(srcdir)/chapters/*.dot
aoip-mgw-options.pdf: $(srcdir)/aoip-mgw-options.adoc $(srcdir)/mgw/*.msc

VTY_REFERENCE = osmobsc-vty-reference.xml
include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.vty-reference.inc

include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.common.inc
