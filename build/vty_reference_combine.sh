#!/bin/sh
set -e

# the first argument should point at libosmocore/doc/vty/merge_doc.xsl
MERGE_DOC="$1"
shift

combined="generated/combined.xml"
combine_src="generated/combine_src.xml"

reference="vty/*reference.xml"
test "$(ls -1 $reference | wc -l)" = "1"

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
