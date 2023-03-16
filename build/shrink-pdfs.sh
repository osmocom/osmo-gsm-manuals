#!/bin/sh -e
# Reduce pdf size by storing the embedded images with less quality (SYS#6380)
# usage: shrink-pdfs.sh first.pdf [second.pdf [...]]
mkdir -p generated

for i in $@; do
	out="generated/shrink_temp.pdf"
	ps2pdf -dPDFSETTINGS=/ebook "$i" "$out"

	size_old=$(du "$i" | cut -f1)
	size_old_h=$(du -h "$i" | cut -f1)
	size_new=$(du "$out" | cut -f1)
	size_new_h=$(du -h "$out" | cut -f1)

	if [ "$size_new" -lt "$size_old" ]; then
		echo "* $i: $size_new_h (shrunk from $size_old_h)"
		mv "$out" "$i"
	else
		echo "* $i: $size_old_h"
		rm "$out"
	fi
done

# Add a marker so the Makefile knows that the shrink script ran. The generated
# dir is already in the gitignore files of repositories using osmo-gsm-manuals,
# so put it there.
touch generated/.pdf_shrink_marker
