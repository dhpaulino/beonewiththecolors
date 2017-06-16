#!/bin/bash

of=$(echo $1 | cut -d'.' -f1)
#echo "$of.pdf"
dot -Tpdf $1 -o "$of.pdf"