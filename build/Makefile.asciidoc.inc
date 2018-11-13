# USAGE:
#
# - define 'TOPDIR' to point at the git root,
# - define in 'ASCIIDOC' all root .adoc files,
# - optionally define in 'ASCIIDOC_DEPS' all dependencies common to all .adocs,
# - include this file,
# - optionally define further dependencies for individual .pdf targets.
#
# e.g.
#
#     TOPDIR = ..
#     ASCIIDOC = osmo_yada.adoc osmo_moo.adoc
#     ASCIIDOC_DEPS = for_all/*.adoc
#     include $(TOPDIR)/build/Makefile.asciidoc.inc
#     osmo_yada.pdf: yada/*.adoc yada/*.msc

BUILDDIR = $(TOPDIR)/build

GIT_VERSION := $(shell git describe --abbrev=4 --dirty --always --tags)
GIT_DATE := $(shell $(TOPDIR)/build/unix-time-to-fmt.py `git log -n 1 "--pretty=%at" ../.`)

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

ASCIIDOC_OPTS := -f $(BUILDDIR)/mscgen-filter.conf -f $(BUILDDIR)/diag-filter.conf -f $(BUILDDIR)/docinfo-releaseinfo.conf -f $(BUILDDIR)/python2-filter.conf
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
		$(TOPDIR)/common/*/*.adoc \
		$(TOPDIR)/common/images/*
	@test -n "$(BUILD_RELEASE)" && echo -e "\n\n\
	  NOTE: TO REMOVE DRAFT MODE, YOU NEED TO EDIT build/custom-dblatex.sty\n\
	        and remove three lines starting with '% \"DRAFT\" on first page'\n" \
	  || true
	a2x $(A2X_OPTS) $< || (echo "ERROR: a2x failed! Running asciidoc to get verbose errors..."; \
		asciidoc -v $(ASCIIDOC_OPTS) $<; exit 1)

check: $(ASCIIDOC_CHECKS)

$(ASCIIDOC_CHECKS): %.check: %.adoc %-docinfo.xml $(ASCIIDOCSTYLE) $(TOPDIR)/common/chapters/*.adoc $(ASCIIDOC_DEPS)
	asciidoc -v $(ASCIIDOC_OPTS) $< > $@ 2>&1
	# Make absolutely sure that the %.check target is updated.
	touch $@
	# Do print the WARNING output but return error if any was found
	# (grep -v would omit the WARNING output from the log).
	@grep WARNING $@ && exit 1 || exit 0
