#!/bin/bash

# only dilepton samples
declare -a Samples=(ttsl ttdl singletop ttw_mg_lo ttz_mg_lo ttg tth dyjetsll_ht gjets_dr0p05_ht wjets_ht100to200 wjets_ht1200to2500 wjets_ht200to400 wjets_ht2500toInf wjets_ht400to600 wjets_ht600to800 wjets_ht800to1200)

INDIR=/home/users/dpg/MT2AnalysisEdit/MyCode/DDvsMC/SkimmedMC/
OUTDIR=/home/users/dpg/MT2AnalysisEdit/MyCode/LL3BSkim/SkimmedMC/

for SAMPLE in ${Samples[@]}; do
    eval 'nohup nice -n 10 ./LL3BSkim.exe ${INDIR} ${SAMPLE} ${OUTDIR} >& logs/${SAMPLE}_selection_log.txt &'
done

