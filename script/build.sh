#!/bin/sh

uname_grep() {
  uname -a | grep $@ 1>/dev/null 2>/dev/null
}

call_make() {
  if uname_grep SunOS; then
    make
  else
    make -j4
  fi
}

mkdir -p build && cd build
cmake $@ .. && call_make
