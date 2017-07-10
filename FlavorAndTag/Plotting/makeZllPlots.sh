#!/bin/bash

declare -a Samples=(zll_dyjetsll_ht)

for SAMPLE in ${Samples[@]}; do
    eval './plotMaker.exe ../hists/${SAMPLE}.root >& logs/${SAMPLE}.log &'
done