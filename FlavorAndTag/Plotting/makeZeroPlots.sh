#!/bin/bash

declare -a Samples=(tth_zero ttz_mg_lo_zero)

for SAMPLE in ${Samples[@]}; do
    eval './plotMaker.exe ../hists/${SAMPLE}.root >& logs/${SAMPLE}.log &'
done