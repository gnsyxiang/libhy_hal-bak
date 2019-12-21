#!/bin/sh

TOP_DIR=./
RES_DIR=$TOP_DIR/res
SCRIPT_DIR=$RES_DIR/script

# use autotools to configure
autotools_configure()
{
  autoreconf -fvi -Im4
}

autotools_configure
