# Usage:
#
# Other makefiles like Makefile.asciidoc.inc and Makefile.vty-reference.inc add
# entries to UPLOAD_FILES and CLEAN_FILES.
#
# Include this file at the end to have 'upload' and 'clean' targets.

UPLOAD_PATH ?= generic@sysmocom-downloads:documents

upload: $(UPLOAD_FILES)
	rsync -avz $(UPLOAD_FILES) $(UPLOAD_PATH)/

clean:
	-rm -rf $(CLEAN_FILES)
