# Usage:
#
# Other makefiles like Makefile.asciidoc.inc and Makefile.vty-reference.inc add
# entries to UPLOAD_FILES and CLEAN_FILES.
#
# Put the repository name (e.g. "osmo-bts") into OSMO_REPOSITORY and include
# this file at the end to have the common targets (upload, clean, install etc.).

SSH_COMMAND = ssh -o 'UserKnownHostsFile=$(OSMO_GSM_MANUALS_DIR)/build/known_hosts' -p 48
UPLOAD_PATH ?= generic@sysmocom-downloads:documents
SYMLINKS = common build
CLEAN_FILES += $(SYMLINKS)
PDF_FILES = $(patsubst %.adoc,%.pdf,$(ASCIIDOC)) $(patsubst %.xml,%.pdf,$(VTY_REFERENCE))
OSMO_REPOSITORY ?= osmo-gsm-manuals

# Prefix (Makefile.am sets this to configure's --prefix when including)
prefix ?= /usr/local

$(SYMLINKS):
	ln -s $(OSMO_GSM_MANUALS_DIR)/$@ $@

upload: $(UPLOAD_FILES)
	rsync -avz $(UPLOAD_FILES) $(UPLOAD_PATH)/

clean:
	-rm -rf $(CLEAN_FILES)

distclean: clean

publish: $(UPLOAD_FILES)
	rsync -avz -e "$(SSH_COMMAND)" $(UPLOAD_FILES) docs@rita.osmocom.org:web-files/latest/

# Install and uninstall targets
# Notes about OSMO_GSM_MANUALS_NO_INSTALL:
# - osmo-gsm-manuals.git's tests/Makefile.am sets this, so the test pdfs will not
#   get installed
# - installing manuals by default is fine, because Osmocom projects won't include
#   the whole Makefile.common.inc unless --enable-manuals is passed to configure.
install: $(PDF_FILES)
	if [ "$(OSMO_GSM_MANUALS_NO_INSTALL)" != "1" ]; then \
		for i in $(PDF_FILES); do \
			install -vDm644 "$$i" "$(DESTDIR)$(prefix)/share/doc/$(OSMO_REPOSITORY)-doc/$$i" || exit 1; \
		done; \
	fi

uninstall:
	if [ "$(OSMO_GSM_MANUALS_NO_INSTALL)" != "1" ]; then \
		for i in $(PDF_FILES); do \
			rm -v "$(DESTDIR)$(prefix)/share/doc/$(OSMO_REPOSITORY)-doc/$$i"; \
		done; \
	fi
