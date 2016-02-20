BUILDDIR = $(TOPDIR)/build

# prepend the document name with the version numbe suffix
#DOCS_VER = $(foreach P, $(ASCIIDOCS), $(P)-v$(shell xmllint --recover --xpath "//revnumber[position()=last()]/text()" $(P)-docinfo.xml 2>/dev/null))
#PDFS = $(DOCS_VER:%=%.pdf)

# generate list of PDFs that we're supposed to render
ASCIIDOCPDFS = $(ASCIIDOCS:%=%.pdf)

ASCIIDOCSTYLE ?= $(BUILDDIR)/custom-dblatex.sty

cleanfiles += $(ASCIIDOCPDFS)

all: $(ASCIIDOCPDFS)

$(ASCIIDOCPDFS): %.pdf: %.adoc %-docinfo.xml $(ASCIIDOCSTYLE) $(TOPDIR)/common/chapters/*.adoc
	a2x -L --asciidoc-opts="-f $(BUILDDIR)/mscgen-filter.conf -f $(BUILDDIR)/diag-filter.conf" --dblatex-opts=" -s $(ASCIIDOCSTYLE)" -a docinfo $< || asciidoc -f $(BUILDDIR)/mscgen-filter.conf -f $(BUILDDIR)/diag-filter.conf $<
