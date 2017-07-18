#!/bin/bash

declare -a Samples=(ttz_mg_lo)

for SAMPLE in ${Samples[@]}; do
    eval 'nohup nice -n 10 ./contam.exe ${SAMPLE} >& logs/${SAMPLE}_contam_log.txt &'
done

