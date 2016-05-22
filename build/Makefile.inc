# XSL stylesheets downloaded from http://docbook.sourceforge.net/release/xsl/current/html/
# Makefile from BitBake/OpenEmbedded manuals

LIBOSMO_DIR := ~/source/gsm/libosmocore
MERGE_DOC := $(LIBOSMO_DIR)/doc/vty/merge_doc.xsl
UPLOAD_PATH := generic@sysmocom-downloads:documents

pdfs = $(patsubst %.xml,%.pdf,$(manuals))
lint = $(patsubst %.xml,%.xml-lint,$(manuals))

#cleanfiles = $(foreach i,$(types),$(topdir)/$(i))
cleanfiles += $(pdfs) $(lint)

ifdef DEBUG
dblatex_quiet =
define command
	$(1)
endef
else
dblatex_quiet = -q
define command
	@echo $(2) $(3)
	@$(1)
endef
endif

all: $(types)


$(types): FORCE


pdf: $(pdfs) $(manuals)


# Lint the file
%.xml-lint: %.xml FORCE
	$(call command,xmllint --xinclude --postvalid --noout $<,XMLLINT,$<)

# Create a PDF file and lint it before
%.pdf: %.xml %.xml-lint $(EXTRA_DEPS) FORCE
	$(call command,dblatex $(dblatex_quiet) -P draft.mode=no $<,DBLATEX,$<)

upload: $(pdfs) $(ASCIIDOCPDFS)
	rsync -avz $(pdfs) $(ASCIIDOCPDFS) $(UPLOAD_PATH)/

FORCE:
