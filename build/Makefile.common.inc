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
PUBLISH_REF ?= master
PUBLISH_TEMPDIR = _publish_tmpdir

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
        [ -n "$(OSMO_REPOSITORY)" && -n "$(PUBLISH_REF)" ] || exit 1
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
