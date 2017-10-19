# USAGE:
#
# - define 'TOPDIR' to point at the git root,
# - define in 'DOCBOOKS' all root .xml files,
# - optionally define in 'DOCBOOKS_DEPS' all dependencies common to all .xmls,
# - include this file,
# - optionally define further dependencies for individual .pdf targets.
#
# e.g.
#
#     TOPDIR = ..
#     DOCBOOKS = osmo_yada.xml osmo_moo.xml
#     ASCIIDOC_DEPS = for_all/*.xml
#     include $(TOPDIR)/build/Makefile.docbook.inc
#     osmo_yada.pdf: yada/*.xml
#
# XSL stylesheets downloaded from http://docbook.sourceforge.net/release/xsl/current/html/
# Makefile from BitBake/OpenEmbedded manuals, edited.

DOCBOOKS_PDF = $(patsubst %.xml,%.pdf,$(DOCBOOKS))
lint = $(patsubst %.xml,%.lint,$(DOCBOOKS))

CLEAN_FILES += $(DOCBOOKS_PDF) $(lint)
UPLOAD_FILES += $(DOCBOOKS_PDF)

all: $(DOCBOOKS_PDF)

# Lint the file
%.xml-lint: %.xml
	xmllint --xinclude --postvalid --noout $<

# Create a PDF file and lint it before
%.pdf: %.xml %.xml-lint $(DOCBOOKS_DEPS)
	dblatex $(dblatex_quiet) -P draft.mode=no $<

