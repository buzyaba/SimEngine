#! /bin/bash

SCRIPTPATH=$(realpath `dirname $0`)

rm `find $SCRIPTPATH/../assets -name *.so`