#!/bin/sh
# usage: vty_reference_combine.sh path/to/merge_doc.xsl path/to/*reference.xml [paths to additional xmls]
# see Makefile.vty-reference.inc
set -e

# first argument: merge_doc.xsl
MERGE_DOC="$1"
shift

# second argument: *reference.xml
reference="$1"
test "$(ls -1 $reference | wc -l)" = "1"
shift

combined="generated/combined.xml"
combine_src="generated/combine_src.xml"

set -x
mkdir -p generated
cp $reference "$combined"

while [ -n "$1" ]; do
	addition="$(realpath "$1")"
	shift
	mv "$combined" "$combine_src"
	xsltproc -o "$combined" \
		--stringparam with "$addition" \
		"$MERGE_DOC" "$combine_src"
done
