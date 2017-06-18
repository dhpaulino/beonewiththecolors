#!/bin/bash
MY_PATH="`dirname \"$0\"`"
MY_PATH="`( cd \"$MY_PATH\" && pwd )`"
raiz=$(dirname "$MY_PATH")
solucoes_dir="$raiz/solucoes"

if [ $# -ne 1 ]
  then
    echo "Chame corretamente: $0 NOME_MAPA"
    echo "NOME_MAPA=LINHAS_COLUNAS_CORES_NUMERO"
    exit -1
fi

mapa=$1
heuristicas=$(ls "$solucoes_dir")
#echo "$heuristicas" | tr '\n' '\t'
#passos=""
#tempo=""
saida=""
for h in $heuristicas
do
	if [  -e "$solucoes_dir/$h/$mapa.sol" ];then
		passos=$(head -1 "$solucoes_dir/$h/$mapa.sol")
		tempo=$(cat "$solucoes_dir/$h/tempo/$mapa.time" | grep real | cut -d'	' -f2)
		
	else
		passos="NULL"
		tempo="NULL"

	fi
	saida="$saida\n$h\t$passos\t$tempo"
done
echo "Ordenado por: NUM_PASSOS"
echo -e "$saida" | sort -n -k2
