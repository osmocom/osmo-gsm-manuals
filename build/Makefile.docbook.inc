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
#     DOCBOOKS_DEPS = $(srcdir)/for_all/*.xml
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

# Allow the users to re-define the include directory
INC_DIR ?= $(shell pwd)/generated

# Lint the file
%.xml-lint: %.xml
	xmllint --xinclude --postvalid --noout $<

GIT_VERSION := $(shell git describe --abbrev=4 --dirty --always --tags)
GIT_DATE := $(shell $(OSMO_GSM_MANUALS_DIR)/build/unix-time-to-fmt.py `git log -n 1 "--pretty=%at" ../.`)
ifeq (,$(BUILD_RELEASE))
	REVNUMBER := DRAFT $(GIT_VERSION)
else
	REVNUMBER := $(GIT_VERSION)
endif

# Create a PDF file and lint it before
# xslt path: find includes in both $(OSMO_GSM_MANUALS_DIR)/common/chapters and $(builddir)/generated
%.pdf: %.xml %.xml-lint $(DOCBOOKS_DEPS) build common
	set -x && \
	export GIT_DATE="$(GIT_DATE)" && \
	export REVNUMBER="$(REVNUMBER)" && \
	export TEMPFILE="$(INC_DIR)/_temp_$(notdir $<)" && \
	$(OSMO_GSM_MANUALS_DIR)/build/docbook-set-revhistory.py "$<" && \
	dblatex --xslt-opts="--path $(realpath $(OSMO_GSM_MANUALS_DIR))/common/chapters:$(INC_DIR)" \
		$(dblatex_quiet) -P draft.mode=no -o $@ "$$TEMPFILE" && \
	rm $$TEMPFILE
