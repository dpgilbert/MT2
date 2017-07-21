#!/bin/bash

declare -a Samples=(tth_low ttz_mg_lo_low)

for SAMPLE in ${Samples[@]}; do
    eval './plotMaker.exe ../hists/${SAMPLE}.root >& logs/${SAMPLE}.log &'
done