# USAGE:
#
# - define 'OSMO_GSM_MANUALS_DIR' to point at the osmo-gsm-manuals shared files
#   installation path as returned by "pkg-config osmo-gsm-manuals --variable=osmogsmmanualsdir"
#   (project specific repos set this with configure.ac),
# - define in 'ASCIIDOC' all root .adoc files,
# - optionally define in 'ASCIIDOC_DEPS' all dependencies common to all .adocs,
# - include this file,
# - optionally define further dependencies for individual .pdf targets.
#
# e.g.
#
#     OSMO_GSM_MANUALS_DIR = ..
#     ASCIIDOC = osmo_yada.adoc osmo_moo.adoc
#     ASCIIDOC_DEPS = $(srcdir)/for_all/*.adoc
#     include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.asciidoc.inc
#     osmo_yada.pdf: yada/*.adoc yada/*.msc

BUILDDIR = $(OSMO_GSM_MANUALS_DIR)/build
COMMONDIR = $(OSMO_GSM_MANUALS_DIR)/common

GIT_VERSION := $(shell git describe --abbrev=4 --dirty --always --tags)
GIT_DATE := $(shell $(OSMO_GSM_MANUALS_DIR)/build/unix-time-to-fmt.py `git log -n 1 "--pretty=%at" ../.`)

# prepend the document name with the version numbe suffix
#DOCS_VER = $(foreach P, $(ASCIIDOC_NAME), $(P)-v$(shell xmllint --recover --xpath "//revnumber[position()=last()]/text()" $(P)-docinfo.xml 2>/dev/null))
#PDFS = $(DOCS_VER:%=%.pdf)

# generate list of PDFs that we're supposed to render
ASCIIDOC_NAME = $(patsubst %.adoc,%,$(ASCIIDOC))
ASCIIDOC_PDF = $(ASCIIDOC_NAME:%=%.pdf)
ASCIIDOC_CHECKS = $(ASCIIDOC_NAME:%=%.check)

ASCIIDOCSTYLE ?= $(BUILDDIR)/custom-dblatex.sty

CLEAN_FILES += $(ASCIIDOC_NAME:%=%__*.png) $(ASCIIDOC_NAME:%=%__*.svg) $(ASCIIDOC_CHECKS)
CLEAN_FILES += $(ASCIIDOC_PDF) $(ASCIIDOC_NAME:%=%.html)
UPLOAD_FILES += $(ASCIIDOC_PDF)

ASCIIDOC_OPTS := -f $(BUILDDIR)/mscgen-filter.conf -f $(BUILDDIR)/diag-filter.conf -f $(BUILDDIR)/docinfo-releaseinfo.conf -a srcdir='$(abs_srcdir)' -a commondir='$(COMMONDIR)'
DBLATEX_OPTS := -s $(ASCIIDOCSTYLE) -P draft.mode=yes -P draft.watermark=0

ifeq (,$(BUILD_RELEASE))
	REVNUMBER := DRAFT $(GIT_VERSION)
else
	REVNUMBER := $(GIT_VERSION)
endif

A2X_OPTS := -L --asciidoc-opts="$(ASCIIDOC_OPTS)" --dblatex-opts="$(DBLATEX_OPTS)" -a docinfo -a revnumber="$(REVNUMBER)" -a revdate="$(GIT_DATE)"


all: $(ASCIIDOC_PDF)

$(ASCIIDOC_PDF): %.pdf: %.adoc %-docinfo.xml \
		$(ASCIIDOC_DEPS) \
		$(ASCIIDOCSTYLE) \
		$(COMMONDIR)/*/*.adoc \
		$(COMMONDIR)/images/* \
		build common

	# a2x can't use a different output file. To support out-of-tree builds,
	# we create a symlink at $(builddir)/srcfile.adoc pointing at
	# $(srcdir)/srcfile.adoc. $< is the $(srcdir)/srcfile.adoc,
	# $(notdir) is like basename from coreutils, and $(builddir) is $PWD.
	if ! [ -f $(notdir $<) ]; then \
		ln -s $< $(notdir $<); \
	fi

	# TEXINPUTS: find LaTeX includes like \includegraphics{./common/images/sysmocom.pdf}
	# in $(OSMO_GSM_MANUALS_DIR).
	@test -n "$(BUILD_RELEASE)" && echo -e "\n\n\
	  NOTE: TO REMOVE DRAFT MODE, YOU NEED TO EDIT build/custom-dblatex.sty\n\
	        and remove three lines starting with '% \"DRAFT\" on first page'\n" \
	  || true
	TEXINPUTS="$(OSMO_GSM_MANUALS_DIR)" \
		a2x -vv $(A2X_OPTS) $(notdir $<)

check:
	if [ -n "$$ASCIIDOC_WARNINGS_CHECK" ]; then \
		$(MAKE) $(ASCIIDOC_CHECKS); \
	fi

$(ASCIIDOC_CHECKS): %.check: %.adoc %-docinfo.xml \
		$(ASCIIDOCSTYLE) \
		$(COMMONDIR)/chapters/*.adoc \
		$(ASCIIDOC_DEPS) \
		build common

	# out-of-tree building: use a symlink to the output file like done in
	# the non-check build above, so the relative include paths work the
	# same.
	if ! [ -f $(notdir $<) ]; then \
		ln -s $< $(notdir $<); \
	fi

	asciidoc -v $(ASCIIDOC_OPTS) $(notdir $<) > $(notdir $@) 2>&1

	# Make absolutely sure that the %.check target is updated.
	touch $(notdir $@)
	# Do print the WARNING output but return error if any was found
	# (grep -v would omit the WARNING output from the log).
	@grep WARNING $(notdir $@) && exit 1 || exit 0
