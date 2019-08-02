#!/bin/sh

set -ex

if [ -n "$1" ]; then
    echo "ERROR: --publish has been deprecated!"
    echo "Manuals have been moved to the projects, and need to be published from there."
    echo "See INSTALL.txt for more information."
    exit 1
fi

osmo-clean-workspace.sh

autoreconf -fi
./configure --enable-asciidoc-warnings-check
$MAKE $PARALLEL_MAKE
$MAKE $PARALLEL_MAKE check
$MAKE $PARALLEL_MAKE distcheck
$MAKE maintainer-clean

osmo-clean-workspace.sh
