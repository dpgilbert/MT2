#!/bin/bash

declare -a Samples=(dyjetsll_ht qcd_ht singletop ttsl ttdl ttg tth ttw_mg_lo ttz_mg_lo tttt twz wjets ww zinv_ht)

for SAMPLE in ${Samples[@]}; do
    eval './plotMaker.exe ../hists/${SAMPLE}.root >& logs/${SAMPLE}.log &'
done