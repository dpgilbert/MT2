#!/bin/bash

declare -a Samples=(dyjetsll_ht qcd_ht singletop ttsl ttdl ttg tth ttw_mg_lo ttz_mg_lo tttt twz wjets ww zinv_ht)

for SAMPLE in ${Samples[@]}; do
    eval 'nohup nice -n 10 ./FlavorAndTag.exe ../3BSkim/SkimmedMC/${SAMPLE}.root >& logs/${SAMPLE}_log.txt &'
done



