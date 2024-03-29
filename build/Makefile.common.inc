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
CLEAN_FILES += $(SYMLINKS) $(SHRINK_MARKER)
PDF_FILES = $(patsubst %.adoc,%.pdf,$(ASCIIDOC)) $(patsubst %.xml,%.pdf,$(VTY_REFERENCE))
SHRINK_MARKER = generated/.pdf_shrink_marker
PUBLISH_REF ?= master
PUBLISH_TEMPDIR = _publish_tmpdir

# Prefix (Makefile.am sets this to configure's --prefix when including)
prefix ?= /usr/local

$(SYMLINKS):
	ln -s $(OSMO_GSM_MANUALS_DIR)/$@ $@

# Reduce pdf size by storing the embedded images with less quality (SYS#6380)
shrink: $(SHRINK_MARKER)
$(SHRINK_MARKER): $(UPLOAD_FILES)
	$(OSMO_GSM_MANUALS_DIR)/build/shrink-pdfs.sh $(UPLOAD_FILES)

# Publish to $UPLOAD_PATH
upload: shrink
	rsync -avz $(UPLOAD_FILES) $(UPLOAD_PATH)/

# Publish to https://ftp.osmocom.org/docs/
publish: shrink
	[ -n "$(OSMO_REPOSITORY)" ] || exit 1
	rm -rf "$(PUBLISH_TEMPDIR)"
	mkdir -p "$(PUBLISH_TEMPDIR)/$(OSMO_REPOSITORY)/$(PUBLISH_REF)"
	cp $(UPLOAD_FILES) "$(PUBLISH_TEMPDIR)/$(OSMO_REPOSITORY)/$(PUBLISH_REF)"
	cd "$(PUBLISH_TEMPDIR)" && \
		rsync \
			-avzR \
			-e "$(SSH_COMMAND)" \
			"$(OSMO_REPOSITORY)" \
			docs@ftp.osmocom.org:web-files/
	rm -rf "$(PUBLISH_TEMPDIR)"

# Install and uninstall targets
# Notes about OSMO_GSM_MANUALS_NO_INSTALL:
# - osmo-gsm-manuals.git's tests/Makefile.am sets this, so the test pdfs will not
#   get installed
# - installing manuals by default is fine, because Osmocom projects won't include
#   the whole Makefile.common.inc unless --enable-manuals is passed to configure.
install: $(PDF_FILES)
	[ -n "$(OSMO_REPOSITORY)" ] || exit 1
	if [ "$(OSMO_GSM_MANUALS_NO_INSTALL)" != "1" ]; then \
		for i in $(PDF_FILES); do \
			install -vDm644 "$$i" "$(DESTDIR)$(prefix)/share/doc/$(OSMO_REPOSITORY)-doc/$$i" || exit 1; \
		done; \
	fi

uninstall:
	[ -n "$(OSMO_REPOSITORY)" ] || exit 1
	if [ "$(OSMO_GSM_MANUALS_NO_INSTALL)" != "1" ]; then \
		for i in $(PDF_FILES); do \
			rm -v "$(DESTDIR)$(prefix)/share/doc/$(OSMO_REPOSITORY)-doc/$$i"; \
		done; \
	fi

clean:
	-rm -rf $(CLEAN_FILES)

distclean: clean
