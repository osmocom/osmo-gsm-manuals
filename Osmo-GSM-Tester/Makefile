TOPDIR := ..
ASCIIDOCS := osmo-gsm-tester-manual

include $(TOPDIR)/build/Makefile.asciidoc.inc
include $(TOPDIR)/build/Makefile.inc

osmo-gsm-tester-manual.pdf: chapters/*.adoc

clean:
	-rm -rf $(cleanfiles)
	-rm osmo-gsm-tester-manual__*.svg
	-rm osmo-gsm-tester-manual__*.png
