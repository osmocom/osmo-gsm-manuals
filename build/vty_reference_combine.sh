#!/bin/sh
# usage: vty_reference_combine.sh path/to/merge_doc.xsl path/to/*reference.xml [paths to additional xmls]
# see Makefile.vty-reference.inc
set -e

# Allow overriding the "generated" output dir, so we don't have collisions when building multiple VTY references in one
# Osmocom project (OS#4292)
VTYGEN=${VTYGEN:-generated}

# first argument: merge_doc.xsl
MERGE_DOC="$1"
shift

# second argument: *reference.xml
reference="$1"
test "$(ls -1 $reference | wc -l)" = "1"
shift

combined="$VTYGEN/combined.xml"
combine_src="$VTYGEN/combine_src.xml"

set -x
mkdir -p "$VTYGEN"
cp $reference "$combined"

while [ -n "$1" ]; do
	addition="$(realpath "$1")"
	shift

	# Fix permissions: xsltproc sets the output permissions the same as the
	# input file, which means during "make distcheck" our output file will
	# become read-only.
	if [ -f "$combine_src" ]; then
		chmod 644 "$combine_src"
	fi

	mv "$combined" "$combine_src"
	xsltproc -o "$combined" \
		--stringparam with "$addition" \
		"$MERGE_DOC" "$combine_src"
done
