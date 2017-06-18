#!/bin/bash


MY_PATH="`dirname \"$0\"`"
MY_PATH="`( cd \"$MY_PATH\" && pwd )`"
raiz=$(dirname "$MY_PATH")
input_dir="$raiz""/inputs"
solucoes_dir="$raiz/solucoes"


for mapa_name in $(ls $input_dir | sort -h)
do
	mapa_path="$input_dir/$mapa_name"
	mapa_name=$(echo "$mapa_name" | cut -d'.' -f1)

	echo "$mapa_name"


	bash "$raiz/scripts/compare_heuristicas.sh" "$mapa_name"	
	
done