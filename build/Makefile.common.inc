# Usage:
#
# Other makefiles like Makefile.asciidoc.inc and Makefile.vty-reference.inc add
# entries to UPLOAD_FILES and CLEAN_FILES.
#
# Include this file at the end to have the common targets (upload, clean etc.).

UPLOAD_PATH ?= generic@sysmocom-downloads:documents
SYMLINKS = common build
CLEAN_FILES += $(SYMLINKS)

$(SYMLINKS):
	ln -s $(OSMO_GSM_MANUALS_DIR)/$@ $@

upload: $(UPLOAD_FILES)
	rsync -avz $(UPLOAD_FILES) $(UPLOAD_PATH)/

clean:
	-rm -rf $(CLEAN_FILES)

distclean: clean
