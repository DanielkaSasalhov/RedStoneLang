#!/bin/zsh
# Build script for chilling project using clang

clang src/main.c src/open.c src/keywords.c src/signals.c src/state.c -o redstone

echo "Build complete. Run ./redstone <filename> to execute."