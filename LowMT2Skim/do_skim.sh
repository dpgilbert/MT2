#!/bin/bash

declare -a Samples=(ttz_mg_lo tth)

INDIR=/hadoop/cms/store/user/olivito/AutoTwopler_babies/merged/MT2/V00-08-18_mc/output/
OUTDIR=/home/users/dpg/MT2AnalysisEdit/MyCode/LowMT2Skim/SkimmedMC/

for SAMPLE in ${Samples[@]}; do
    eval 'nohup nice -n 10 ./LowMT2Skim.exe ${INDIR} ${SAMPLE} ${OUTDIR} >& logs/${SAMPLE}_selection_log.txt &'
done

