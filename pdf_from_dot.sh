#!/bin/bash

normal="out_grafo"
agm="out_agm_grafo"

dot -Tpdf "$normal".dot -o "$normal".pdf
dot -Tpdf "$agm".dot -o "$agm".pdf