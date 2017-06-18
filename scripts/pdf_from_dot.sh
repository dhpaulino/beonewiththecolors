#!/bin/bash

MY_PATH="`dirname \"$0\"`"
MY_PATH="`( cd \"$MY_PATH\" && pwd )`"
raiz=$(dirname "$MY_PATH")

normal="$raiz""/inteiro_grafo"
agm="$raiz""/agm_grafo"

dot -Tpdf "$normal".dot -o "$normal".pdf
dot -Tpdf "$agm".dot -o "$agm".pdf