share_files = $(srcdir)/build $(srcdir)/common $(srcdir)/*.xsl
share_path = "$(DESTDIR)$(prefix)/share/osmo-gsm-manuals"

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = osmo-gsm-manuals.pc
BUILT_SOURCES = $(top_srcdir)/.version
EXTRA_DIST = git-version-gen .version check-depends.sh $(share_files)
SUBDIRS = tests \
	OsmoMGCP \
	OsmoNAT \
	OsmoNITB \
	OsmocomBB

$(top_srcdir)/.version:
	echo $(VERSION) > $@-t && mv $@-t $@

dist-hook:
	echo $(VERSION) > $(distdir)/.tarball-version

install-data-hook:
	cd "$(srcdir)" && \
		files="$$(find $(notdir $(share_files)) -not -type d)" && \
		for i in $$files; do \
			if [ -x "$$i" ]; then \
				mode=755; \
			else \
				mode=644; \
			fi; \
			install -vDm$$mode "$$i" "$(share_path)/$$i" || exit 1; \
		done;
	install -Dm755 "$(srcdir)/check-depends.sh" "$(DESTDIR)$(prefix)/bin/osmo-gsm-manuals-check-depends"

uninstall-local:
	rm -rv "$(share_path)" "$(DESTDIR)$(prefix)/bin/osmo-gsm-manuals-check-depends"

upload:
	for i in Osmo*; do \
		$(MAKE) -C "$$i" upload || exit 1; \
	done
