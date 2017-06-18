#!/bin/bash

MY_PATH="`dirname \"$0\"`"
MY_PATH="`( cd \"$MY_PATH\" && pwd )`"
raiz=$(dirname "$MY_PATH")
input_dir="$raiz""/inputs"
fabiano_dir="$raiz""/fabiano"
h1_exe="$fabiano_dir/floodit_h1"
h2_exe="$fabiano_dir/floodit_h2"
h4_exe="$fabiano_dir/floodit_h4"
h6_exe="$fabiano_dir/floodit_h6"
solucoes_dir="$raiz/solucoes"
h1_sol="$solucoes_dir/h1"
h2_sol="$solucoes_dir/h2"
h4_sol="$solucoes_dir/h4"
h6_sol="$solucoes_dir/h6"

for mapa_path in $input_dir/*
do
	mapa_name=$(echo $mapa_path| rev | cut -d'/' -f1 | rev | cut -d'.' -f1)
	echo "$mapa_name"
	echo "H1"
	{ time "$h1_exe" < "$mapa_path" > "$h1_sol/$mapa_name.sol"; } 2> "$h1_sol/tempo/$mapa_name.time"
	echo "H2"
	{ time "$h2_exe" < "$mapa_path" > "$h2_sol/$mapa_name.sol"; } 2> "$h2_sol/tempo/$mapa_name.time"
	echo "H4"
	{ time "$h4_exe" < "$mapa_path" > "$h4_sol/$mapa_name.sol"; } 2> "$h4_sol/tempo/$mapa_name.time"
	echo "H6"
	{ time "$h6_exe" < "$mapa_path" > "$h6_sol/$mapa_name.sol"; } 2> "$h6_sol/tempo/$mapa_name.time"

done