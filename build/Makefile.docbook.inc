# USAGE:
#
# - define 'OSMO_GSM_MANUALS_DIR' to point at the osmo-gsm-manuals shared files
#   installation path as returned by "pkg-config osmo-gsm-manuals --variable=osmogsmmanualsdir"
#   (project specific repos set this with configure.ac),
# - define in 'DOCBOOKS' all root .xml files,
# - optionally define in 'DOCBOOKS_DEPS' all dependencies common to all .xmls,
# - include this file,
# - optionally define further dependencies for individual .pdf targets.
#
# e.g.
#
#     OSMO_GSM_MANUALS_DIR = ..
#     DOCBOOKS = osmo_yada.xml osmo_moo.xml
#     ASCIIDOC_DEPS = for_all/*.xml
#     include $(OSMO_GSM_MANUALS_DIR)/build/Makefile.docbook.inc
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
%.pdf: %.xml %.xml-lint $(DOCBOOKS_DEPS) build common
	dblatex $(dblatex_quiet) -P draft.mode=no $<

