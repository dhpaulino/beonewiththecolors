#!/bin/bash

if [ $# -ne 1 ]
  then
    echo "Chame corretamente: $0 NOME_HEURISTICA"
    exit -1
fi

nome=$1
MY_PATH="`dirname \"$0\"`"
MY_PATH="`( cd \"$MY_PATH\" && pwd )`"
raiz=$(dirname "$MY_PATH")
input_dir="$raiz""/inputs"
solucoes_dir="$raiz/solucoes"
dir_heuristica="$solucoes_dir/$nome"
tempo_heuristica="$dir_heuristica/tempo"
exe_path="$raiz/flood_it_solver"


mkdir -p "$tempo_heuristica" 2> /dev/null

for mapa_name in $(ls $input_dir | sort -h)
do
	mapa_path="$input_dir/$mapa_name"
	mapa_name=$(echo "$mapa_name" | cut -d'.' -f1)

	echo "$mapa_name"

	{ time "$exe_path" < "$mapa_path" > "$dir_heuristica/$mapa_name.sol"; } 2> "$tempo_heuristica/$mapa_name.time"
	
	
done