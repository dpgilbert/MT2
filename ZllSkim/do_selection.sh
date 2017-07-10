#!/bin/bash

declare -a Samples=(dyjetsll_ht)

INDIR=/nfs-6/userdata/mt2/V00-08-18_mc_skim_base_mt2gt200_ZinvV6_JECs/
OUTDIR=SkimmedMC/

for SAMPLE in ${Samples[@]}; do
    eval 'nohup nice -n 10 ./ZllSkim.exe ${INDIR} ${SAMPLE} ${OUTDIR} >& logs/${SAMPLE}_selection_log.txt &'
done

