#ifndef DDVSMC_PLOTTING_H
#define DDVSMC_PLOTTING_H

TH1F* GetDataDrivenHist (const std::string& filename, const std::string& SR_key);
TH1F* GetMonteCarloHist (const std::string& filename, const std::string* SR_key);

#endif
