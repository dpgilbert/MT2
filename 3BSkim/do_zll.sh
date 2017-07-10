#!/bin/bash

# only dilepton samples
declare -a Samples=(zll_dyjetsll_ht)

INDIR=/home/users/dpg/MT2AnalysisEdit/MyCode/ZllSkim/SkimmedMC/
OUTDIR=/home/users/dpg/MT2AnalysisEdit/MyCode/3BSkim/SkimmedMC/

for SAMPLE in ${Samples[@]}; do
    eval 'nohup nice -n 10 ./3BSkim.exe ${INDIR} ${SAMPLE} ${OUTDIR} >& logs/${SAMPLE}_3B_selection_log.txt &'
done

