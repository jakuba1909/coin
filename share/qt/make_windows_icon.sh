#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/monkey.ico

convert ../../src/qt/res/icons/monkey-16.png ../../src/qt/res/icons/monkey-32.png ../../src/qt/res/icons/monkey-48.png ${ICON_DST}
