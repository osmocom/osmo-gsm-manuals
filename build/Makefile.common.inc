# Usage:
#
# Other makefiles like Makefile.asciidoc.inc and Makefile.vty-reference.inc add
# entries to UPLOAD_FILES and CLEAN_FILES.
#
# Include this file at the end to have the common targets (upload, clean etc.).

SSH_COMMAND = ssh -o 'UserKnownHostsFile=$(OSMO_GSM_MANUALS_DIR)/build/known_hosts' -p 48
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

publish: all
	mkdir -p out
	cp *.pdf out
	rsync -avz -e "$(SSH_COMMAND)" ./out/ docs@rita.osmocom.org:web-files/latest/
