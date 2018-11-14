OSMO_GSM_MANUALS_DIR = ..

ASCIIDOC = osmobts-usermanual.adoc osmobts-abis.adoc rtp-amr.adoc
include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.asciidoc.inc
osmobts-usermanual.pdf: chapters/*.adoc
osmobts-abis.pdf: abis/*.adoc abis/*.msc
rtp-amr.pdf: dtx.dot

VTY_REFERENCE = osmobts-vty-reference.xml
include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.vty-reference.inc

include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.common.inc
