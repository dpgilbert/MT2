#ifndef CONTAM_PLOTTING_H
#define CONTAM_PLOTTING_H

TH1F* GetFullHist (const std::string& filename, const std::string& SR_key);
TH1F* GetHiggsHist (const std::string& filename, const std::string* SR_key);

#endif
