#!/bin/bash

declare -a Samples=(zinv_ht)

for SAMPLE in ${Samples[@]}; do
    eval 'nohup nice -n 10 ./FlavorAndTag.exe ../3BSkim/SkimmedMC/${SAMPLE}.root >& logs/${SAMPLE}_log.txt &'
done



