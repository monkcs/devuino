#!/bin/bash

rm -frd prepared
mkdir prepared
rm -frd prepared/*
find ./src -mindepth 1 -type f -exec cp -t ./prepared -i '{}' +
