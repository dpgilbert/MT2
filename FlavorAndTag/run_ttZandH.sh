#!/bin/bash

declare -a Samples=(tth ttz_mg_lo)

for SAMPLE in ${Samples[@]}; do
    eval 'nohup nice -n 10 ./FlavorAndTag.exe ../3BSkim/SkimmedMC/${SAMPLE}.root >& logs/${SAMPLE}_log.txt &'
done



