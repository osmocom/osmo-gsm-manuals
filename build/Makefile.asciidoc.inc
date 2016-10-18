BUILDDIR = $(TOPDIR)/build

GIT_VERSION := $(shell git describe --abbrev=4 --dirty --always --tags)
GIT_DATE := $(shell $(TOPDIR)/build/unix-time-to-fmt.py `git log -n 1 "--pretty=%at" ../.`)

# prepend the document name with the version numbe suffix
#DOCS_VER = $(foreach P, $(ASCIIDOCS), $(P)-v$(shell xmllint --recover --xpath "//revnumber[position()=last()]/text()" $(P)-docinfo.xml 2>/dev/null))
#PDFS = $(DOCS_VER:%=%.pdf)

# generate list of PDFs that we're supposed to render
ASCIIDOCPDFS = $(ASCIIDOCS:%=%.pdf)
ASCIIDOC_CHECKS = $(ASCIIDOCS:%=%.check)

ASCIIDOCSTYLE ?= $(BUILDDIR)/custom-dblatex.sty

cleanfiles += $(ASCIIDOCPDFS)

ASCIIDOC_OPTS := -f $(BUILDDIR)/mscgen-filter.conf -f $(BUILDDIR)/diag-filter.conf -f $(BUILDDIR)/docinfo-releaseinfo.conf
DBLATEX_OPTS := -s $(ASCIIDOCSTYLE) -P draft.mode=yes

ifeq (,$(BUILD_RELEASE))
	DBLATEX_OPTS += -P draft.watermark=1
else
	DBLATEX_OPTS += -P draft.watermark=0
endif

A2X_OPTS := -L --asciidoc-opts="$(ASCIIDOC_OPTS)" --dblatex-opts="$(DBLATEX_OPTS)" -a docinfo -a revnumber="$(GIT_VERSION)" -a revdate="$(GIT_DATE)"


all: $(ASCIIDOCPDFS)

$(ASCIIDOCPDFS): %.pdf: %.adoc %-docinfo.xml $(ASCIIDOCSTYLE) $(TOPDIR)/common/chapters/*.adoc
	a2x $(A2X_OPTS) $< || asciidoc -v $(ASCIIDOC_OPTS) $<

check: $(ASCIIDOC_CHECKS)

$(ASCIIDOC_CHECKS): %.check: %.adoc %-docinfo.xml $(ASCIIDOCSTYLE) $(TOPDIR)/common/chapters/*.adoc chapters/*.adoc
	asciidoc -v $(ASCIIDOC_OPTS) $< > $@ 2>&1
	# Make absolutely sure that the %.check target is updated.
	touch $@
	# Do print the WARNING output but return error if any was found
	# (grep -v would omit the WARNING output from the log).
	@grep WARNING $@ && exit 1 || exit 0
