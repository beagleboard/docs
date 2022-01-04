#!/bin/bash
cd $(dirname $0)
git pull
git submodule update --init --recursive
./build.sh
