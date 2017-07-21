#!/bin/bash

declare -a Samples=(tth_low ttz_mg_lo_low)

for SAMPLE in ${Samples[@]}; do
    eval 'nohup nice -n 10 ./FlavorAndTag.exe ../3BSkim/SkimmedMC_low/${SAMPLE}.root >& logs/${SAMPLE}_log.txt &'
done



