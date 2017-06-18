#!/bin/bash

MY_PATH="`dirname \"$0\"`"
MY_PATH="`( cd \"$MY_PATH\" && pwd )`"
raiz=$(dirname "$MY_PATH")
input_dir="$raiz""/inputs"

for mapa_path in $input_dir/*
do
	sol=$("$raiz"/flood_it_solver < "$mapa_path")
	
	mapa=$(cat "$mapa_path")

	echo -e "$mapa""\n""$sol" | "$raiz"/fabiano/verifica
	resolveu=$?
	if [[ $resolveu != 0 ]];then
		filename=$(echo $mapa_path| rev | cut -d'/' -f1 | rev)
		echo "Não resolveu:$filename";
		#echo "Solução:$sol" 
	fi

done
#echo $PWD
#echo "$mapa"
#$raizflood_it_solver < "$mapa"

