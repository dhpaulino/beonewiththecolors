#!/bin/bash

if [ $# -ne 4 ]
  then
    echo "Chame corretamente: $0 N_LINHAS N_COLUNAS N_CORES N_MAPAS"
    exit -1
fi

N_LINHAS=$1
N_COLUNAS=$2
N_CORES=$3
N_MAPAS=$4

i=0;
while [ $i -lt $N_MAPAS ]; do
	fabiano/geramapa $N_LINHAS $N_COLUNAS $N_CORES $RANDOM > inputs/"$N_LINHAS"_"$N_COLUNAS"_"$N_CORES"_"$i".in;
	let i=$i+1;
done