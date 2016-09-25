// -*- C++ -*-
//
// Package:    HBHETimingValidation/MakeTimingMaps
// Class:      MakeTimingMaps
// 
/**\class MakeTimingMaps MakeTimingMaps.cc HBHETimingValidation/MakeTimingMaps/plugins/MakeTimingMaps.cc

 Description: Quick example code for making HBHE timing monitoring plots
*/
//
// Original Author:  Stephanie Brandt
//         Created:  Fri, 21 Aug 2015 11:42:17 GMT
//
//


// system include files
#include <memory>
#include <string>
#include <map>
#include <iostream>
using namespace std;

// user include files
#include "TLine.h"
#include "TStyle.h"
#include "TTree.h"
#include "TFile.h"
#include "TProfile.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TProfile2D.h"
#include "TLatex.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/Event.h"

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/HcalRecHit/interface/HBHERecHit.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"

#include "SimDataFormats/CaloHit/interface/PCaloHit.h"
#include "SimDataFormats/CaloHit/interface/PCaloHitContainer.h"

#include "SimCalorimetry/HcalSimAlgos/interface/HcalSimParameterMap.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class MakePhase1Plots : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit MakePhase1Plots(const edm::ParameterSet&);
      ~MakePhase1Plots();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      
      std::string int2string(int i);
      
      void ClearVariables();
      
      // some variables for storing information
      double Method0Energy;
      double RecHitEnergy;
      double RecHitTime;
      double RecHitChi2;
      int LumiBlock;
      double iEta;
      double iPhi; 
      int depth;
      int RunNumber;
      int EvtNumber;
      
      // create the output file
      edm::Service<TFileService> FileService;
      // create the token to retrieve hit information
      edm::EDGetTokenT<HBHERecHitCollection>    hRhToken;
      edm::EDGetTokenT<bool> hIsoToken;
    
      TH2F *hCheckEnergyM0MX_barrel;
      TH2F *hCheckEnergyM0MX_endcap;

      TH1F *hCheckTimingMX_barrel;
      TH1F *hCheckTimingMX_endcap;

      TH1F *hCheckTimingMX_barrel_gt5;
      TH1F *hCheckTimingMX_endcap_gt5;

      TH1F *hCheckChi2MX_barrel_gt5;
      TH1F *hCheckChi2MX_endcap_gt5;

      TH1F *hCheckTimingMX_endcap_depth1_gt5;
      TH1F *hCheckTimingMX_endcap_depth2_gt5;
      TH1F *hCheckTimingMX_endcap_depth3_gt5;
      TH1F *hCheckTimingMX_endcap_depth4_gt5;

      TH2F *hCheckEnergyTiming_barrel;
      TH2F *hCheckEnergyTiming_endcap;

      TH2F *hCheckT45ratioVST4_barrel;
      TH2F *hCheckT45ratioVST4_endcap;

      TH1F *hCheckT45ratio_barrel;
      TH1F *hCheckT45ratio_endcap;

      TProfile2D *hHBHEChi2;
      TProfile2D *hHBHEChi2_depth1;
      TProfile2D *hHBHEChi2_depth2;
      TProfile2D *hHBHEChi2_depth3;
      TProfile2D *hHBHEChi2_depth4;
      TProfile2D *hHBHEChi2_depth5;
      TProfile2D *hHBHEChi2_depth6;

      TH2F *occupancy_d1;
      TH2F *occupancy_d2;
      TH2F *occupancy_d3;
      TH2F *occupancy_d4;
      TH2F *occupancy_d5;
      TH2F *occupancy_d6;

  /*  

      // 2-d profiles which will hold the average time per channel, 1 for each depth
      TProfile2D *hHBHETiming_Depth1;
      TProfile2D *hHBHETiming_Depth2;
      TProfile2D *hHBHETiming_Depth3;

      // pointer to pointer to pointers to make a 2-d array of histograms
      // These are used to hold the individual rechit timing histograms for each channel
      TH1F ***hTiming_Depth1 = new TH1F**[59];
      TH1F ***hTiming_Depth2 = new TH1F**[59];
      TH1F ***hTiming_Depth3 = new TH1F**[6];
      
      // Check for correlation between same iphi or adjacent iphi
      TH1F *hCheckTimingPhi67Plus;
      TH1F *hCheckTiming66to67P;
      TH2F *hCorrTimingPhi67Plus;
      TH2F *hCorrTiming66to67P;
      
      // Get energy distributions of channels
      TH1F *hCheckEnergyIT;
      TH1F *hCheckEnergyOOT1;
      TH1F *hCheckEnergyOOT2;
      
      TH1F *hCheckEnergyITip51;
      TH1F *hCheckEnergyOOT1ip51;
      TH1F *hCheckEnergyOOT2ip51;
      
      TH1F *hCheckEnergyITip54;
      TH1F *hCheckEnergyOOT1ip54;
      TH1F *hCheckEnergyOOT2ip54;
  */
      
      // Sample histogram for storing time slice information
      TH1F *hTimeSlices;
      
      int runNumber_;
      double energyCut_;
      double timeLow_;
      double timeHigh_;
      std::vector<double> etas67;
      std::vector<double> etas66;
        
    // crap for trouble-shooting, create a TCanvas here to print out pulse shapes of problem channels
   TCanvas *c1 = new TCanvas("c1","c1",900,700);
   int nProblems = 0;
};


MakePhase1Plots::MakePhase1Plots(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   usesResource("TFileService");

  // Tell which collection is consumed
   hRhToken = consumes<HBHERecHitCollection >(iConfig.getUntrackedParameter<string>("HBHERecHits","hbhereco"));
   //  hRhToken = consumes<HBHERecHitCollection >(iConfig.getUntrackedParameter<string>("HBHERecHits","hbheprereco"));
  hIsoToken = consumes<bool >(iConfig.getUntrackedParameter<string>("HBHENoiseFilterResultProducer", "HBHEIsoNoiseFilterResult"));
  

  // example histogram for storing time slice information
  /*
  // Get Configurable parameters
  runNumber_ = iConfig.getParameter<int>("runNumber");
  energyCut_ = iConfig.getParameter<double>("rechitEnergy");
  
  timeLow_ = iConfig.getParameter<double>("timeLowBound");
  timeHigh_ = iConfig.getParameter<double>("timeHighBound");
  */

  hCheckEnergyM0MX_barrel = FileService->make<TH2F>("M0MXplot_barrel","M0MXplot_barrel",20,0.,100.,20,0.,100.);
  hCheckEnergyM0MX_endcap = FileService->make<TH2F>("M0MXplot_endcap","M0MXplot_endcap",20,0.,100.,20,0.,100.);

  hCheckEnergyM0MX_barrel->GetXaxis()->SetTitle("M0 Energy");
  hCheckEnergyM0MX_endcap->GetXaxis()->SetTitle("M0 Energy");

  hCheckEnergyM0MX_barrel->GetYaxis()->SetTitle("M2 Energy");
  hCheckEnergyM0MX_endcap->GetYaxis()->SetTitle("M2 Energy");

  hCheckTimingMX_barrel = FileService->make<TH1F>("TimingMX_barrel","TimingMX_barrel",25,-12.5,12.5);
  hCheckTimingMX_endcap = FileService->make<TH1F>("TimingMX_endcap","TimingMX_endcap",25,-12.5,12.5);

  hCheckTimingMX_barrel_gt5 = FileService->make<TH1F>("TimingMX_barrel_gt5","TimingMX_barrel_gt5",25,-12.5,12.5);
  hCheckTimingMX_endcap_gt5 = FileService->make<TH1F>("TimingMX_endcap_gt5","TimingMX_endcap_gt5",25,-12.5,12.5);

  hCheckTimingMX_barrel_gt5->GetXaxis()->SetTitle("M2 Timing");
  hCheckTimingMX_endcap_gt5->GetXaxis()->SetTitle("M2 Timing");

  hCheckChi2MX_barrel_gt5 = FileService->make<TH1F>("Chi2MX_barrel_gt5","chi2MX_barrel_gt5",1000,-10,500);
  hCheckChi2MX_endcap_gt5 = FileService->make<TH1F>("Chi2MX_endcap_gt5","chi2MX_endcap_gt5",1000,-10,500);

  hCheckChi2MX_barrel_gt5->GetXaxis()->SetTitle("M2 chi2");
  hCheckChi2MX_endcap_gt5->GetXaxis()->SetTitle("M2 chi2");

  hCheckEnergyTiming_barrel = FileService->make<TH2F>("EnergyTiming_barrel","EnergyTiming_barrel",25,-12.5,12.5,20,0.,100.);
  hCheckEnergyTiming_endcap = FileService->make<TH2F>("EnergyTiming_endcap","EnergyTiming_endcap",25,-12.5,12.5,20,0.,100.);

  hCheckT45ratioVST4_barrel = FileService->make<TH2F>("T45ratioVST4_barrel","T45ratioVST4_barrel", 30,0.,3., 500,0.,500.);
  hCheckT45ratioVST4_endcap = FileService->make<TH2F>("T45ratioVST4_endcap","T45ratioVST4_endcap", 30,0.,3., 500,0.,500.);

  hCheckT45ratio_barrel = FileService->make<TH1F>("T45ratio_barrel","T45ratio_barrel", 30,0.,3.);
  hCheckT45ratio_endcap = FileService->make<TH1F>("T45ratio_endcap","T45ratio_endcap", 30,0.,3.);

  hCheckTimingMX_endcap_depth1_gt5 = FileService->make<TH1F>("TimingMX_endcap_depth1_gt5","TimingMX_endcap_depth1_gt5",25,-12.5,12.5);
  hCheckTimingMX_endcap_depth2_gt5 = FileService->make<TH1F>("TimingMX_endcap_depth2_gt5","TimingMX_endcap_depth2_gt5",25,-12.5,12.5);
  hCheckTimingMX_endcap_depth3_gt5 = FileService->make<TH1F>("TimingMX_endcap_depth3_gt5","TimingMX_endcap_depth3_gt5",25,-12.5,12.5);
  hCheckTimingMX_endcap_depth4_gt5 = FileService->make<TH1F>("TimingMX_endcap_depth4_gt5","TimingMX_endcap_depth4_gt5",25,-12.5,12.5);

  hHBHEChi2 = FileService->make<TProfile2D>("hHBHEChi2","hHBHEChi2",59,-29.5,29.5,72,0.5,72.5, 0, 950.,"s");
  hHBHEChi2->GetXaxis()->SetTitle("i#eta");
  hHBHEChi2->GetYaxis()->SetTitle("i#phi");
  hHBHEChi2->GetZaxis()->SetTitle("M2 chi2");

  hHBHEChi2_depth1 = FileService->make<TProfile2D>("hHBHEChi2_depth1","hHBHEChi2_depth1",59,-29.5,29.5,72,0.5,72.5, 0, 950.,"s");
  hHBHEChi2_depth1->GetXaxis()->SetTitle("i#eta");
  hHBHEChi2_depth1->GetYaxis()->SetTitle("i#phi");
  hHBHEChi2_depth1->GetZaxis()->SetTitle("M2 chi2");

  hHBHEChi2_depth2 = FileService->make<TProfile2D>("hHBHEChi2_depth2","hHBHEChi2_depth2",59,-29.5,29.5,72,0.5,72.5, 0, 950.,"s");
  hHBHEChi2_depth2->GetXaxis()->SetTitle("i#eta");
  hHBHEChi2_depth2->GetYaxis()->SetTitle("i#phi");
  hHBHEChi2_depth2->GetZaxis()->SetTitle("M2 chi2");

  hHBHEChi2_depth3 = FileService->make<TProfile2D>("hHBHEChi2_depth3","hHBHEChi2_depth3",59,-29.5,29.5,72,0.5,72.5, 0, 950.,"s");
  hHBHEChi2_depth3->GetXaxis()->SetTitle("i#eta");
  hHBHEChi2_depth3->GetYaxis()->SetTitle("i#phi");
  hHBHEChi2_depth3->GetZaxis()->SetTitle("M2 chi2");

  hHBHEChi2_depth4 = FileService->make<TProfile2D>("hHBHEChi2_depth4","hHBHEChi2_depth4",59,-29.5,29.5,72,0.5,72.5, 0, 950.,"s");
  hHBHEChi2_depth4->GetXaxis()->SetTitle("i#eta");
  hHBHEChi2_depth4->GetYaxis()->SetTitle("i#phi");
  hHBHEChi2_depth4->GetZaxis()->SetTitle("M2 chi2");

  hHBHEChi2_depth5 = FileService->make<TProfile2D>("hHBHEChi2_depth5","hHBHEChi2_depth5",59,-29.5,29.5,72,0.5,72.5, 0, 950.,"s");
  hHBHEChi2_depth5->GetXaxis()->SetTitle("i#eta");
  hHBHEChi2_depth5->GetYaxis()->SetTitle("i#phi");
  hHBHEChi2_depth5->GetZaxis()->SetTitle("M2 chi2");

  hHBHEChi2_depth6 = FileService->make<TProfile2D>("hHBHEChi2_depth6","hHBHEChi2_depth6",59,-29.5,29.5,72,0.5,72.5, 0, 950.,"s");
  hHBHEChi2_depth6->GetXaxis()->SetTitle("i#eta");
  hHBHEChi2_depth6->GetYaxis()->SetTitle("i#phi");
  hHBHEChi2_depth6->GetZaxis()->SetTitle("M2 chi2");

  occupancy_d1 = FileService->make<TH2F>("occupancy_d1","occupancy_depth1",59,-29.5,29.5,72,0.5,72.5);
  occupancy_d2 = FileService->make<TH2F>("occupancy_d2","occupancy_depth2",59,-29.5,29.5,72,0.5,72.5);
  occupancy_d3 = FileService->make<TH2F>("occupancy_d3","occupancy_depth3",59,-29.5,29.5,72,0.5,72.5);
  occupancy_d4 = FileService->make<TH2F>("occupancy_d4","occupancy_depth4",59,-29.5,29.5,72,0.5,72.5);
  occupancy_d5 = FileService->make<TH2F>("occupancy_d5","occupancy_depth5",59,-29.5,29.5,72,0.5,72.5);
  occupancy_d6 = FileService->make<TH2F>("occupancy_d6","occupancy_depth6",59,-29.5,29.5,72,0.5,72.5);



}


MakePhase1Plots::~MakePhase1Plots(){} // destructor

// funtion so you can turn an integer into a string for labels and stuff
std::string MakePhase1Plots::int2string(int i) {
  stringstream ss;
  string ret;
  ss << i;
  ss >> ret;
  return ret;
}

// ------------ method called for each event  ------------
void
MakePhase1Plots::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;

  // Read events
  Handle<HBHERecHitCollection> hRecHits; // create handle
  iEvent.getByToken(hRhToken, hRecHits); // get events based on token
  
  double TS4=-100;
  double TS5=0.;

  // Loop over all rechits in one event
  for(int i = 0; i < (int)hRecHits->size(); i++) {
    //    ClearVariables(); // sets a bunch of stuff to zero
    
    RunNumber = iEvent.id().run(); // get the run number for the event
    EvtNumber = iEvent.id().event(); // get the event number
    LumiBlock = iEvent.id().luminosityBlock();

    // Just in case the file you are running over contains events from multiple runs,
    // remove everything except the run you are interested in
    //  if(RunNumber != runNumber_) continue;
    
    // get ID information for the reconstructed hit
    HcalDetId detID_rh = (*hRecHits)[i].id().rawId();
    
    // ID information can get us detector coordinates
    depth = (*hRecHits)[i].id().depth();
    iEta = detID_rh.ieta();
    iPhi = detID_rh.iphi();
    
    // get some variables
    Method0Energy = (*hRecHits)[i].eraw();
    RecHitEnergy = (*hRecHits)[i].energy();
    RecHitTime = (*hRecHits)[i].time();
    RecHitChi2 = (*hRecHits)[i].chi2();

    //    if(Method0Energy>5) cout << "energy="<< Method0Energy << "  ; chi2=" << (*hRecHits)[i].chi2() << endl;
    
    // this block of code is to extract the charge in individual time slices from 
    // the auxiliary information 
                                                                                                                                                                         
    // Not  used at the moment, but useful for trouble-shooting if we identify a
    //  problem with some channels

    int adc[10]; 

    int auxwd1 = (*hRecHits)[i].aux();  // TS = 0,1,2,3 info
    int auxwd2 = (*hRecHits)[i].auxHBHE();      // TS = 4,5,6,7 info
    int auxwd3 = (*hRecHits)[i].auxPhase1();      // TS = 8,9 info

    // 0x7F --> 7bits 127
    // 0xFF --> 8bits 255

    // 
    adc[0] = (auxwd1)       & 0xFF;
    adc[1] = (auxwd1 >> 8)  & 0xFF;
    adc[2] = (auxwd1 >> 16) & 0xFF;
    adc[3] = (auxwd1 >> 24) & 0xFF;
    
    adc[4] = (auxwd2)       & 0xFF;
    adc[5] = (auxwd2 >> 8)  & 0xFF;
    adc[6] = (auxwd2 >> 16) & 0xFF;
    adc[7] = (auxwd2 >> 24) & 0xFF;

    adc[8] = (auxwd3 )      & 0xFF;
    adc[9] = (auxwd3 >> 8)  & 0xFF;
     
    TS4=adc[4];
    TS5=adc[5];    

    // example on how to fill the time slices if you need it
    if(Method0Energy > 20){

      hTimeSlices = FileService->make<TH1F>(Form("hTimeSlices_%4.2f",Method0Energy),Form("hTimeSlices_%4.2f",Method0Energy),10,-100,150);

      std::cout << "event number is " << EvtNumber << std::endl;
      std::cout << "iphi, ieta = " << detID_rh.iphi() << " " << detID_rh.ieta() << " time = " << RecHitTime << " energy = " << RecHitEnergy << std::endl;
      for(int nadc = 0; nadc < 10; nadc++){
	hTimeSlices->SetBinContent(nadc+1,adc[nadc]);
	std::cout << adc[nadc] << "  " ;
      }
      std::cout << std::endl;

      hTimeSlices->GetXaxis()->SetBinLabel(1,"TS0");
      hTimeSlices->GetXaxis()->SetBinLabel(2,"TS1");
      hTimeSlices->GetXaxis()->SetBinLabel(3,"TS2");
      hTimeSlices->GetXaxis()->SetBinLabel(4,"TS3");
      hTimeSlices->GetXaxis()->SetBinLabel(5,"TS4");
      hTimeSlices->GetXaxis()->SetBinLabel(6,"TS5");
      hTimeSlices->GetXaxis()->SetBinLabel(7,"TS6");
      hTimeSlices->GetXaxis()->SetBinLabel(8,"TS7");
      hTimeSlices->GetXaxis()->SetBinLabel(9,"TS8");
      hTimeSlices->GetXaxis()->SetBinLabel(10,"TS9");

      hTimeSlices->SetTitle("");
      hTimeSlices->GetYaxis()->SetTitle("tsAdc");

      gStyle->SetOptStat(000000);

      hTimeSlices->SetLineWidth(3);
      hTimeSlices->Draw();

      ///////////
      //pedestal Line

      double ped=3;
      if(std::abs(iEta) < 14) ped=3.;
      if(std::abs(iEta) >=19  && std::abs(iEta)<=26) ped=17.3;

      TLine *line = new TLine(hTimeSlices->GetXaxis()->GetBinLowEdge(0),ped,hTimeSlices->GetXaxis()->GetBinUpEdge(hTimeSlices->GetXaxis()->GetNbins()),ped);
      line->SetLineColor(kRed);
      line->SetLineWidth(3);
      line->Draw("same");

      ///////////// 

      TLatex *t = new TLatex();
      t->SetTextFont(32);
      t->SetTextColor(1);
      //      t->SetTextSize(0.08);
      t->SetTextAlign(12);
      t->SetTextSize(0.05);
      t->DrawLatex(hTimeSlices->GetXaxis()->GetBinLowEdge(1),1.1*hTimeSlices->GetMaximum(),Form("M0=%4.2f  ieta=%d iphi=%d depth=%d ,    M2=%4.2f",Method0Energy,detID_rh.ieta(),detID_rh.iphi(),depth,RecHitEnergy));
      //      t->DrawLatex(0.,0.75*hTimeSlices->GetMaximum(),Form("M0=%4.2f",Method0Energy));
      //      t->DrawLatex(0.15,0.65*hTimeSlices->GetMaximum(),Form("M2=%4.2f",Method2Energy));

      // comment the plotting
      //      if(std::abs(iEta) < 14) c1->SaveAs(Form("Pulse_Barrel_%d_%d_%d_Energy%4.2f.png",RunNumber,LumiBlock,EvtNumber,Method0Energy));
      //      if(std::abs(iEta) >=19  && std::abs(iEta)<=26) c1->SaveAs(Form("Pulse_Endcap_%d_%d_%d_Energy%4.2f.png",RunNumber,LumiBlock,EvtNumber,Method0Energy));
      //("test_phi"+int2string(detID_rh.iphi())+"eta"+int2string(detID_rh.ieta())+"energy"+int2string((int)RecHitEnergy)+"time"+int2string((int)RecHitTime)+".png").c_str());
      ///       ++nProblems;
    }

    if(std::abs(iEta) < 14 )  hCheckT45ratioVST4_barrel->Fill(TS5/TS4,TS4);
    if(std::abs(iEta) >=19  && std::abs(iEta)<=26 )  hCheckT45ratioVST4_endcap->Fill(TS5/TS4,TS4);

    if(std::abs(iEta) < 14 )  hCheckT45ratio_barrel->Fill(TS5/TS4);
    if(std::abs(iEta) >=19  && std::abs(iEta)<=26 )  hCheckT45ratio_endcap->Fill(TS5/TS4);

//    if(RecHitEnergy > energyCut_)
    if(std::abs(iEta) < 14 )  hCheckEnergyM0MX_barrel->Fill(Method0Energy,RecHitEnergy);
    if(std::abs(iEta) >=19  && std::abs(iEta)<=26 )  hCheckEnergyM0MX_endcap->Fill(Method0Energy,RecHitEnergy);

    if(std::abs(iEta) < 14 )  hCheckTimingMX_barrel->Fill(RecHitTime);
    if(std::abs(iEta) >=19  && std::abs(iEta)<=26 )  hCheckTimingMX_endcap->Fill(RecHitTime);

    if(depth==1) occupancy_d1->Fill(detID_rh.ieta(), detID_rh.iphi(),1);
    if(depth==2) occupancy_d2->Fill(detID_rh.ieta(), detID_rh.iphi(),1);
    if(depth==3) occupancy_d3->Fill(detID_rh.ieta(), detID_rh.iphi(),1);
    if(depth==4) occupancy_d4->Fill(detID_rh.ieta(), detID_rh.iphi(),1);
    if(depth==5) occupancy_d5->Fill(detID_rh.ieta(), detID_rh.iphi(),1);
    if(depth==6) occupancy_d6->Fill(detID_rh.ieta(), detID_rh.iphi(),1);

    if(Method0Energy>5) {

      hHBHEChi2->Fill(detID_rh.ieta(), detID_rh.iphi(), RecHitChi2);
      if(Method0Energy>5 && depth==1) hHBHEChi2_depth1->Fill(detID_rh.ieta(), detID_rh.iphi(), RecHitChi2);
      if(Method0Energy>5 && depth==2) hHBHEChi2_depth2->Fill(detID_rh.ieta(), detID_rh.iphi(), RecHitChi2);
      if(Method0Energy>5 && depth==3) hHBHEChi2_depth3->Fill(detID_rh.ieta(), detID_rh.iphi(), RecHitChi2);
      if(Method0Energy>5 && depth==4) hHBHEChi2_depth4->Fill(detID_rh.ieta(), detID_rh.iphi(), RecHitChi2);
      if(Method0Energy>5 && depth==5) hHBHEChi2_depth5->Fill(detID_rh.ieta(), detID_rh.iphi(), RecHitChi2);
      if(Method0Energy>5 && depth==6) hHBHEChi2_depth6->Fill(detID_rh.ieta(), detID_rh.iphi(), RecHitChi2);

      if(std::abs(iEta) < 14 )  hCheckChi2MX_barrel_gt5->Fill(RecHitChi2);
      if(std::abs(iEta) >=19  && std::abs(iEta)<=26 )  hCheckChi2MX_endcap_gt5->Fill(RecHitChi2);


      if(std::abs(iEta) < 14 )  hCheckTimingMX_barrel_gt5->Fill(RecHitTime);
      if(std::abs(iEta) >=19  && std::abs(iEta)<=26 )  hCheckTimingMX_endcap_gt5->Fill(RecHitTime);

      if( std::abs(iEta) < 14 ) hCheckEnergyTiming_barrel->Fill(RecHitTime,Method0Energy);
      if( std::abs(iEta) >=19  && std::abs(iEta)<=26  ) hCheckEnergyTiming_endcap->Fill(RecHitTime,Method0Energy);

      if(std::abs(iEta) >=19  && std::abs(iEta)<=26 ) {
	if(depth==1) hCheckTimingMX_endcap_depth1_gt5->Fill(RecHitTime);
	if(depth==2) hCheckTimingMX_endcap_depth2_gt5->Fill(RecHitTime);
	if(depth==3) hCheckTimingMX_endcap_depth3_gt5->Fill(RecHitTime);
	if(depth==4) hCheckTimingMX_endcap_depth4_gt5->Fill(RecHitTime);

      }
    }


  } // recHit

}


// ------------ method called once each job just before starting event loop  ------------
void MakePhase1Plots::beginJob(){}

// ------------ method called once each job just after ending the event loop  ------------
void MakePhase1Plots::endJob(){}

void MakePhase1Plots::ClearVariables(){
 RecHitEnergy = 0;
 RunNumber = 0;
 depth=0;
 iEta = 0;
 iPhi = 0;
 RecHitTime = 0;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void MakePhase1Plots::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  // The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MakePhase1Plots);
