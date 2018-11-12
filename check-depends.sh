#!/bin/sh

# $1: program name, $2: package name
check_dep_bin() {
	if ! type "$1" >/dev/null 2>&1; then
		echo "Binary '$1' not found in path, please install $2."
		exit 1
	fi
}

# $1: module name, $2: package name
check_dep_python2_module() {
	if ! echo "import $1" | python2 - >/dev/null 2>&1; then
		echo "Failed to import '$1' module, please install $2."
		exit 1
	fi
}

check_dep_bin mscgen mscgen
check_dep_bin xsltproc libxslt
check_dep_bin git git
check_dep_bin a2x asciidoc
check_dep_bin asciidoc asciidoc
check_dep_bin dblatex dblatex
check_dep_bin packetdiag nwdiag
check_dep_bin dot graphviz
check_dep_bin python2 python2
check_dep_python2_module pychart python2-pychart

echo "All dependencies installed!"
