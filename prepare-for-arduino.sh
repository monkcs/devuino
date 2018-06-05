#!/bin/bash

mkdir prepared
rm -frd prepared/*
find ./source -mindepth 1 -type f -exec cp -t ./prepared -i '{}' +
