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


for mapa_name in $(ls $input_dir | sort -h)
do
	mapa_path="$input_dir/$mapa_name"
	mapa_name=$(echo "$mapa_name" | cut -d'.' -f1)
	sol="$dir_heuristica/$mapa_name.sol"
	
	cat "$mapa_path" "$sol"| "$raiz"/fabiano/verifica
	
	resolveu=$?
	filename=$(echo $mapa_path| rev | cut -d'/' -f1 | rev)
	if [[ $resolveu != 0 ]];then
		echo "Não resolveu:$filename";
		#echo "Solução:$sol" 
	else
		echo "Resolveu:$filename";
	fi

done
#echo $PWD
#echo "$mapa"
#$raizflood_it_solver < "$mapa"

