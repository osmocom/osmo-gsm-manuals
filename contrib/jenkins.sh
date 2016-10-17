#!/usr/bin/env bash

set -ex

base="$PWD"
deps="$base/deps"

mkdir "$deps" || true

cd "$deps"
osmo-deps.sh libosmocore

cd "$base"
$MAKE $PARALLEL_MAKE LIBOSMO_DIR="$deps/libosmocore"
$MAKE $PARALLEL_MAKE LIBOSMO_DIR="$deps/libosmocore" check
