#!/bin/bash

declare -a Samples=(tth_zero ttz_mg_lo_zero)

for SAMPLE in ${Samples[@]}; do
    eval 'nohup nice -n 10 ./FlavorAndTag.exe ../3BSkim/SkimmedMC_zero/${SAMPLE}.root >& logs/${SAMPLE}_log.txt &'
done



