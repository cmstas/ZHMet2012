#include "TH1.h"
#include "TMath.h"

// float dRGenJet ( LorentzVector p4, vector <LorentzVector> &genjetsp4, bool isData, float ptcut = 20.0 ) 
// {
//   if( isData ) return -99.0;
//   float mindr = 999.0;

//   for( size_t i = 0 ; i < genjetsp4.size() ; i++){
//     // require genjet pt > ptcut
//     if( genjetsp4.at(i).pt() < ptcut ) continue;
//     // dR(jet,genjet)
//     float dr = ROOT::Math::VectorUtil::DeltaR( p4 , genjetsp4.at(i) );
//     // store minimum dR
//     if( dr < mindr ) mindr = dr;
//   }
//   return mindr;
// }

void fillUnderOverFlow( TH1F * &h1, const float value, const float weight)
{
  float fillvalue = value;
  if (fillvalue > h1->GetXaxis()->GetXmax() ) fillvalue = h1->GetBinCenter(h1->GetNbinsX());
  if (fillvalue < h1->GetXaxis()->GetXmin() ) fillvalue = h1->GetBinCenter(1);
  h1->Fill(fillvalue, weight);
  return;
}

//--------------------------------------------------------------------

float deltaPhi( const float phi1 , const float phi2)
{
  float dphi = fabs( phi1 - phi2 );
  if( dphi > TMath::Pi() ) dphi = TMath::TwoPi() - dphi;
  return dphi;
}

// int isGenQGLMatched ( LorentzVector p4, bool isData, float dR = 0.4 ) {

//   if( isData ) return -99;

//   //Start from the end that seems to have the decay products of the W first
        
//   for (int igen = (genps_p4().size()-1); igen >-1; igen--) {

//     float deltaR = ROOT::Math::VectorUtil::DeltaR( p4 , genps_p4().at(igen) );
//     if ( deltaR > dR ) continue;

//     int id     = genps_id().at(igen);
//     int mothid = genps_id_mother().at(igen);
//     // cout<<"status 3 particle ID "<<id<<" mother "<<mothid                                                                         
//     //  <<" dR to jet "<<deltaR<<endl;

//     // light quark from W
//     if (abs(id)<6 && abs(mothid)==24)
//       return (mothid>0) ? 2 : -2;

//     // b quark from top
//     if (abs(id)==5 && abs(mothid)==6)
//       return (mothid>0) ? 1 : -1;

//     // lepton: e, mu, or tau
//     if (abs(id)==11 && abs(mothid)==24)
//       return (mothid>0) ? 11 : -11;
//     if (abs(id)==13 && abs(mothid)==24)
//       return (mothid>0) ? 13 : -13;
//     if (abs(id)==15 && abs(mothid)==24)
//       return (mothid>0) ? 15 : -15;

//     // gluon
//     if (abs(id)==21) return 3;

//     // light not from W
//     if (abs(id)<6) return 4;

//   }
  
//   // no match
//   return -9;
// }

// //--------------------------------------------------------------------

// int getJetIndex( LorentzVector thisJet , FactorizedJetCorrector *jet_corrector_pfL1FastJetL2L3 ){

//   for (unsigned int ijet = 0 ; ijet < pfjets_p4().size() ; ijet++) {

//     if( fabs( pfjets_p4().at(ijet).eta() ) > 5.0 ) continue;

//     //---------------------------------------------------------------------------
//     // get total correction: L1FastL2L3 for MC, L1FastL2L3Residual for data
//     //---------------------------------------------------------------------------
    
//     jet_corrector_pfL1FastJetL2L3->setRho   ( cms2.evt_ww_rho_vor()           );
//     jet_corrector_pfL1FastJetL2L3->setJetA  ( cms2.pfjets_area().at(ijet)     );
//     jet_corrector_pfL1FastJetL2L3->setJetPt ( cms2.pfjets_p4().at(ijet).pt()  );
//     jet_corrector_pfL1FastJetL2L3->setJetEta( cms2.pfjets_p4().at(ijet).eta() );
//     double corr = jet_corrector_pfL1FastJetL2L3->getCorrection();
    
//     LorentzVector vjet   = corr * pfjets_p4().at(ijet);

//     if( fabs( vjet.pt() - thisJet.pt() ) < 0.1 && fabs( vjet.eta() - thisJet.eta() ) < 0.1 && fabs( vjet.phi() - thisJet.phi() ) < 0.1 ) return ijet;

//   }

//   cout << __FILE__ << " " << __LINE__ << " WARNING! should never get here!" << endl;
//   cout << evt_run() << " " << evt_lumiBlock() << " " << evt_event() << endl;
//   cout << thisJet.pt() << " " << thisJet.eta() << " " << thisJet.phi() << endl;

//   return 0;
// }

// //--------------------------------------------------------------------

// float getJetUnc( const float jetcorpt, const float jeteta , JetCorrectionUncertainty *pfUncertainty ){

//   pfUncertainty->setJetEta(jeteta);
//   pfUncertainty->setJetPt(jetcorpt);   // here you must use the CORRECTED jet pt
//   return pfUncertainty->getUncertainty(true);
// }

// int getLeptonID( LorentzVector thisLepton ){

//   for (unsigned int imu = 0 ; imu < mus_p4().size() ; imu++) {
    
//     LorentzVector vmu   = mus_p4().at(imu);
//     if( vmu.pt() < 10.0 ) continue;

//     if( fabs( vmu.pt() - thisLepton.pt() ) < 0.001 && fabs( vmu.eta() - thisLepton.eta() ) < 0.001 && fabs( vmu.phi() - thisLepton.phi() ) < 0.001 ) return -13 * mus_charge().at(imu);
//   }

//   for (unsigned int iel = 0 ; iel < els_p4().size() ; iel++) {
    
//     LorentzVector vel   = els_p4().at(iel);
//     if( vel.pt() < 10.0 ) continue;

//     if( fabs( vel.pt() - thisLepton.pt() ) < 0.001 && fabs( vel.eta() - thisLepton.eta() ) < 0.001 && fabs( vel.phi() - thisLepton.phi() ) < 0.001 ) return -11 * els_charge().at(iel);
//   }

//   cout << __FILE__ << " " << __LINE__ << " WARNING! should never get here! couldn't find matching lepton" << endl;
//   cout << evt_run() << " " << evt_lumiBlock() << " " << evt_event() << endl;
//   cout << thisLepton.pt() << " " << thisLepton.eta() << " " << thisLepton.phi() << endl;

//   return 0;
// }

// pair<float, float> ScaleMET( pair<float, float> p_met, LorentzVector p4_dilep, double rescale = 1.0 ){
//   float met = p_met.first;
//   float metPhi = p_met.second;
//   float metx = met*cos(metPhi);
//   float mety = met*sin(metPhi);

//   float lepx = p4_dilep.Px();
//   float lepy = p4_dilep.Py();
      
//   //hadronic component of MET (well, mostly), scaled
//   float metHx = (metx + lepx)*rescale;
//   float metHy = (mety + lepy)*rescale;
//   float metNewx = metHx - lepx;
//   float metNewy = metHy - lepy;
//   float metNewPhi = atan2(metNewy, metNewx);
      
//   pair<float, float> p_met2 = make_pair(sqrt(metNewx*metNewx + metNewy*metNewy), metNewPhi);
//   return p_met2;
// }

