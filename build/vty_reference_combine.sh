#!/bin/sh
# usage: vty_reference_combine.sh path/to/merge_doc.xsl path/to/*reference.xml [paths to additional xmls]
# the result of combination is printed to stdout
# see Makefile.vty-reference.inc
set -e

# first argument: merge_doc.xsl
MERGE_DOC="$1"
shift

# second argument: *reference.xml
reference="$1"
test "$(ls -1 $reference | wc -l)" = "1"
shift

set -x

# we cannot use the same file as input and output, because
# xsltproc would override the input immediately :/
combined=$(mktemp)
combine_src=$(mktemp)
cp $reference $combined

while [ -n "$1" ]; do
	addition="$(realpath "$1")"
	shift

	# sync both input and output files
	cp $combined $combine_src

	xsltproc -o "$combined" \
		--stringparam with "$addition" \
		"$MERGE_DOC" "$combine_src"
done

# print the results to stdout
cat $combined >&1

# clean up temporary files
rm -f $combine_src
rm -f $combined
