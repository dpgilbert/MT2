{
  TCanvas *c1 = new TCanvas();
  c1->SetLogy();
  c1->cd();

  // Initial
  TString title = h_mt2_nocut->GetTitle();
  h_mt2_nocut->SetTitle(title.Append(";M_{T2} (GeV);Counts at 1 fb^{-1}"));
  h_mt2_nocut->SetFillColor(kRed);
  h_mt2_nocut->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/mt2_nocut.pdf");
  
  title = h_ht_nocut->GetTitle();
  h_ht_nocut->SetTitle(title.Append(";H_{T} (GeV);Count at 1 fb^{-1}"));
  h_ht_nocut->SetFillColor(kRed);
  h_ht_nocut->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/ht_nocut.pdf");
  
  title = h_dphi_nocut->GetTitle();
  h_dphi_nocut->SetTitle(title.Append(";#Delta#phi_{min};Count at 1 fb^{-1}"));
  h_dphi_nocut->SetFillColor(kRed);
  h_dphi_nocut->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/dphi_nocut.pdf");
  
  title = h_diff_nocut->GetTitle();
  h_diff_nocut->SetTitle(title.Append(";|MHT-MET|/MET;Count at 1 fb^{-1}"));
  h_diff_nocut->SetFillColor(kRed);
  h_diff_nocut->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/diff_nocut.pdf");
  
  
  // Trigger
  h_mt2_trigger->SetTitle(title.Append(";M_{T2} (GeV);Counts at 1 fb^{-1}"));
  h_mt2_trigger->SetFillColor(kRed);
  h_mt2_trigger->Draw("Ehist");
  c1->SetLogy();
  c1->Print("../../UnskimmedPlots/mt2_trigger.pdf");
  
  title = h_ht_trigger->GetTitle();
  h_ht_trigger->SetTitle(title.Append(";H_{T} (GeV);Count at 1 fb^{-1}"));
  h_ht_trigger->SetFillColor(kRed);
  h_ht_trigger->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/ht_trigger.pdf");
  
  title = h_dphi_trigger->GetTitle();
  h_dphi_trigger->SetTitle(title.Append(";#Delta#phi_{min};Count at 1 fb^{-1}"));
  h_dphi_trigger->SetFillColor(kRed);
  h_dphi_trigger->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/dphi_trigger.pdf");
  
  title = h_diff_trigger->GetTitle();
  h_diff_trigger->SetTitle(title.Append(";|MHT-MET|/MET;Count at 1 fb^{-1}"));
  h_diff_trigger->SetFillColor(kRed);
  h_diff_trigger->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/diff_trigger.pdf");
      
  // njet
  h_mt2_njet->SetTitle(title.Append(";M_{T2} (GeV);Counts at 1 fb^{-1}"));
  h_mt2_njet->SetFillColor(kRed);
  h_mt2_njet->Draw("Ehist");
  c1->SetLogy();
  c1->Print("../../UnskimmedPlots/mt2_njet.pdf");
  
  title = h_ht_njet->GetTitle();
  h_ht_njet->SetTitle(title.Append(";H_{T} (GeV);Count at 1 fb^{-1}"));
  h_ht_njet->SetFillColor(kRed);
  h_ht_njet->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/ht_njet.pdf");
  
  title = h_dphi_njet->GetTitle();
  h_dphi_njet->SetTitle(title.Append(";#Delta#phi_{min};Count at 1 fb^{-1}"));
  h_dphi_njet->SetFillColor(kRed);
  h_dphi_njet->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/dphi_njet.pdf");
  
  title = h_diff_njet->GetTitle();
  h_diff_njet->SetTitle(title.Append(";|MHT-MET|/MET;Count at 1 fb^{-1}"));
  h_diff_njet->SetFillColor(kRed);
  h_diff_njet->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/diff_njet.pdf");
  
  // dphi
  h_mt2_dphi->SetTitle(title.Append(";M_{T2} (GeV);Counts at 1 fb^{-1}"));
  h_mt2_dphi->SetFillColor(kRed);
  h_mt2_dphi->Draw("Ehist");
  c1->SetLogy();
  c1->Print("../../UnskimmedPlots/mt2_dphi.pdf");
  
  title = h_ht_dphi->GetTitle();
  h_ht_dphi->SetTitle(title.Append(";H_{T} (GeV);Count at 1 fb^{-1}"));
  h_ht_dphi->SetFillColor(kRed);
  h_ht_dphi->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/ht_dphi.pdf");
  
  title = h_dphi_dphi->GetTitle();
  h_dphi_dphi->SetTitle(title.Append(";#Delta#phi_{min};Count at 1 fb^{-1}"));
  h_dphi_dphi->SetFillColor(kRed);
  h_dphi_dphi->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/dphi_dphi.pdf");
      
  title = h_diff_dphi->GetTitle();
  h_diff_dphi->SetTitle(title.Append(";|MHT-MET|/MET;Count at 1 fb^{-1}"));
  h_diff_dphi->SetFillColor(kRed);
  h_diff_dphi->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/diff_dphi.pdf");
      
  // diff
  h_mt2_diff->SetTitle(title.Append(";M_{T2} (GeV);Counts at 1 fb^{-1}"));
  h_mt2_diff->SetFillColor(kRed);
  h_mt2_diff->Draw("Ehist");
  c1->SetLogy();
  c1->Print("../../UnskimmedPlots/mt2_diff.pdf");
  
  title = h_ht_diff->GetTitle();
  h_ht_diff->SetTitle(title.Append(";H_{T} (GeV);Count at 1 fb^{-1}"));
  h_ht_diff->SetFillColor(kRed);
  h_ht_diff->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/ht_diff.pdf");
  
  title = h_dphi_diff->GetTitle();
  h_dphi_diff->SetTitle(title.Append(";#Delta#phi_{min};Count at 1 fb^{-1}"));
  h_dphi_diff->SetFillColor(kRed);
  h_dphi_diff->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/dphi_diff.pdf");
  
  title = h_diff_diff->GetTitle();
  h_diff_diff->SetTitle(title.Append(";|MHT-MET|/MET;Count at 1 fb^{-1}"));
  h_diff_diff->SetFillColor(kRed);
  h_diff_diff->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/diff_diff.pdf");
  
  // lep
  h_mt2_lep->SetTitle(title.Append(";M_{T2} (GeV);Counts at 1 fb^{-1}"));
  h_mt2_lep->SetFillColor(kRed);
  h_mt2_lep->Draw("Ehist");
  c1->SetLogy();
  c1->Print("../../UnskimmedPlots/mt2_lep.pdf");
  
  title = h_ht_lep->GetTitle();
  h_ht_lep->SetTitle(title.Append(";H_{T} (GeV);Count at 1 fb^{-1}"));
  h_ht_lep->SetFillColor(kRed);
  h_ht_lep->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/ht_lep.pdf");
  
  title = h_dphi_lep->GetTitle();
  h_dphi_lep->SetTitle(title.Append(";#Delta#phi_{min};Count at 1 fb^{-1}"));
  h_dphi_lep->SetFillColor(kRed);
  h_dphi_lep->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/dphi_lep.pdf");
  
  title = h_diff_lep->GetTitle();
  h_diff_lep->SetTitle(title.Append(";|MHT-MET|/MET;Count at 1 fb^{-1}"));
  h_diff_lep->SetFillColor(kRed);
  h_diff_lep->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/diff_lep.pdf");
  
  // MT2
  h_mt2_mt2->SetTitle(title.Append(";M_{T2} (GeV);Counts at 1 fb^{-1}"));
  h_mt2_mt2->SetFillColor(kRed);
  h_mt2_mt2->Draw("Ehist");
  c1->SetLogy();
  c1->Print("../../UnskimmedPlots/mt2_mt2.pdf");
  
  title = h_ht_mt2->GetTitle();
  h_ht_mt2->SetTitle(title.Append(";H_{T} (GeV);Count at 1 fb^{-1}"));
  h_ht_mt2->SetFillColor(kRed);
  h_ht_mt2->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/ht_mt2.pdf");
  
  title = h_dphi_mt2->GetTitle();
  h_dphi_mt2->SetTitle(title.Append(";#Delta#phi_{min};Count at 1 fb^{-1}"));
  h_dphi_mt2->SetFillColor(kRed);
  h_dphi_mt2->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/dphi_mt2.pdf");
  
  title = h_diff_mt2->GetTitle();
  h_diff_mt2->SetTitle(title.Append(";|MHT-MET|/MET;Count at 1 fb^{-1}"));
  h_diff_mt2->SetFillColor(kRed);
  h_diff_mt2->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/diff_mt2.pdf");
}
