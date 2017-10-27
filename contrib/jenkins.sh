#!/bin/sh

set -ex

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

osmo-clean-workspace.sh
