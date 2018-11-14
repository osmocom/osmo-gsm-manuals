OSMO_GSM_MANUALS_DIR = $(top_srcdir)

ASCIIDOC = osmobts-usermanual.adoc osmobts-abis.adoc rtp-amr.adoc
include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.asciidoc.inc
osmobts-usermanual.pdf: $(srcdir)/chapters/*.adoc
osmobts-abis.pdf: $(srcdir)/abis/*.adoc $(srcdir)/abis/*.msc
rtp-amr.pdf: $(srcdir)/dtx.dot

VTY_REFERENCE = osmobts-vty-reference.xml
include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.vty-reference.inc

include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.common.inc
