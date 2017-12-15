#!/bin/sh

set -ex

publish="$1"

base="$PWD"
deps="$base/deps"
export deps

osmo-clean-workspace.sh

mkdir "$deps" || true

cd "$deps"
osmo-deps.sh libosmocore

cd "$base"
$MAKE $PARALLEL_MAKE LIBOSMO_DIR="$deps/libosmocore"
$MAKE $PARALLEL_MAKE LIBOSMO_DIR="$deps/libosmocore" check

if [ "x$publish" = "x--publish" ]; then
  mkdir out/
  cp */*.pdf out/
  rsync -avz --delete -e "ssh -p 48" ./out/ docs@osmocom.org:web-files/latest/
fi

osmo-clean-workspace.sh
