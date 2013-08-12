// -*- C++ -*-
#ifndef TEMPLATES_H
#define TEMPLATES_H
#include "Math/LorentzVector.h"
#include "Math/Point3D.h"
#include "TMath.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH1F.h"
#include "TFile.h"
#include "TBits.h"
#include <vector> 
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

#define PARANOIA

using namespace std; 
class TEMPLATES {
private: 
protected: 
	unsigned int index;
	int	run_;
	TBranch *run_branch;
	bool run_isLoaded;
	int	lumi_;
	TBranch *lumi_branch;
	bool lumi_isLoaded;
	int	event_;
	TBranch *event_branch;
	bool event_isLoaded;
	int	nvtx_;
	TBranch *nvtx_branch;
	bool nvtx_isLoaded;
	float	weight_;
	TBranch *weight_branch;
	bool weight_isLoaded;
	float	pthat_;
	TBranch *pthat_branch;
	bool pthat_isLoaded;
	int	failjetid_;
	TBranch *failjetid_branch;
	bool failjetid_isLoaded;
	float	maxemf_;
	TBranch *maxemf_branch;
	bool maxemf_isLoaded;
	float	maxleppt_;
	TBranch *maxleppt_branch;
	bool maxleppt_isLoaded;
	int	elveto_;
	TBranch *elveto_branch;
	bool elveto_isLoaded;
	float	ht30_;
	TBranch *ht30_branch;
	bool ht30_isLoaded;
	float	ht40_;
	TBranch *ht40_branch;
	bool ht40_isLoaded;
	float	jzb_;
	TBranch *jzb_branch;
	bool jzb_isLoaded;
	float	pfmet_;
	TBranch *pfmet_branch;
	bool pfmet_isLoaded;
	float	pfmett1_;
	TBranch *pfmett1_branch;
	bool pfmett1_isLoaded;
	float	pfmett1new_;
	TBranch *pfmett1new_branch;
	bool pfmett1new_isLoaded;
	float	pfmet_type1_pt30_;
	TBranch *pfmet_type1_pt30_branch;
	bool pfmet_type1_pt30_isLoaded;
	float	pfmet_type1_pt15_;
	TBranch *pfmet_type1_pt15_branch;
	bool pfmet_type1_pt15_isLoaded;
	float	pfmetphi_;
	TBranch *pfmetphi_branch;
	bool pfmetphi_isLoaded;
	float	pfmett1phi_;
	TBranch *pfmett1phi_branch;
	bool pfmett1phi_isLoaded;
	float	pfmett1newphi_;
	TBranch *pfmett1newphi_branch;
	bool pfmett1newphi_isLoaded;
	float	pfsumet_;
	TBranch *pfsumet_branch;
	bool pfsumet_isLoaded;
	float	met_;
	TBranch *met_branch;
	bool met_isLoaded;
	float	metphi_;
	TBranch *metphi_branch;
	bool metphi_isLoaded;
	float	sumet_;
	TBranch *sumet_branch;
	bool sumet_isLoaded;
	float	mumet_;
	TBranch *mumet_branch;
	bool mumet_isLoaded;
	float	mumetphi_;
	TBranch *mumetphi_branch;
	bool mumetphi_isLoaded;
	float	musumet_;
	TBranch *musumet_branch;
	bool musumet_isLoaded;
	float	mujesmet_;
	TBranch *mujesmet_branch;
	bool mujesmet_isLoaded;
	float	mujesmetphi_;
	TBranch *mujesmetphi_branch;
	bool mujesmetphi_isLoaded;
	float	mujessumet_;
	TBranch *mujessumet_branch;
	bool mujessumet_isLoaded;
	float	genmet_;
	TBranch *genmet_branch;
	bool genmet_isLoaded;
	float	genmetphi_;
	TBranch *genmetphi_branch;
	bool genmetphi_isLoaded;
	float	gensumet_;
	TBranch *gensumet_branch;
	bool gensumet_isLoaded;
	float	dphixmet_;
	TBranch *dphixmet_branch;
	bool dphixmet_isLoaded;
	float	metpar_;
	TBranch *metpar_branch;
	bool metpar_isLoaded;
	float	metperp_;
	TBranch *metperp_branch;
	bool metperp_isLoaded;
	float	tcmet_;
	TBranch *tcmet_branch;
	bool tcmet_isLoaded;
	float	tcmetphi_;
	TBranch *tcmetphi_branch;
	bool tcmetphi_isLoaded;
	float	tcsumet_;
	TBranch *tcsumet_branch;
	bool tcsumet_isLoaded;
	float	tcmetNew_;
	TBranch *tcmetNew_branch;
	bool tcmetNew_isLoaded;
	float	tcmetNew_type1_pt30_;
	TBranch *tcmetNew_type1_pt30_branch;
	bool tcmetNew_type1_pt30_isLoaded;
	float	tcmetNew_type1_pt15_;
	TBranch *tcmetNew_type1_pt15_branch;
	bool tcmetNew_type1_pt15_isLoaded;
	float	tcmetphiNew_;
	TBranch *tcmetphiNew_branch;
	bool tcmetphiNew_isLoaded;
	float	tcsumetNew_;
	TBranch *tcsumetNew_branch;
	bool tcsumetNew_isLoaded;
	int	njets_;
	TBranch *njets_branch;
	bool njets_isLoaded;
	int	njets10_;
	TBranch *njets10_branch;
	bool njets10_isLoaded;
	int	njets15_;
	TBranch *njets15_branch;
	bool njets15_isLoaded;
	int	njets20_;
	TBranch *njets20_branch;
	bool njets20_isLoaded;
	int	njets40_;
	TBranch *njets40_branch;
	bool njets40_isLoaded;
	float	ht_;
	TBranch *ht_branch;
	bool ht_isLoaded;
	float	ht10_;
	TBranch *ht10_branch;
	bool ht10_isLoaded;
	float	vecjetpt_;
	TBranch *vecjetpt_branch;
	bool vecjetpt_isLoaded;
	int	nbl_;
	TBranch *nbl_branch;
	bool nbl_isLoaded;
	int	nbm_;
	TBranch *nbm_branch;
	bool nbm_isLoaded;
	int	nbt_;
	TBranch *nbt_branch;
	bool nbt_isLoaded;
	float	ndphijetmet_;
	TBranch *ndphijetmet_branch;
	bool ndphijetmet_isLoaded;
	float	maxjetpt_;
	TBranch *maxjetpt_branch;
	bool maxjetpt_isLoaded;
	float	maxjetdphimet_;
	TBranch *maxjetdphimet_branch;
	bool maxjetdphimet_isLoaded;
	int	hlt20_;
	TBranch *hlt20_branch;
	bool hlt20_isLoaded;
	int	hlt30_;
	TBranch *hlt30_branch;
	bool hlt30_isLoaded;
	int	hlt50_;
	TBranch *hlt50_branch;
	bool hlt50_isLoaded;
	int	hlt75_;
	TBranch *hlt75_branch;
	bool hlt75_isLoaded;
	int	hlt90_;
	TBranch *hlt90_branch;
	bool hlt90_isLoaded;
	int	hlt135_;
	TBranch *hlt135_branch;
	bool hlt135_isLoaded;
	int	hlt150_;
	TBranch *hlt150_branch;
	bool hlt150_isLoaded;
	int	hlt160_;
	TBranch *hlt160_branch;
	bool hlt160_isLoaded;
	int	hgg22_;
	TBranch *hgg22_branch;
	bool hgg22_isLoaded;
	int	hgg36_;
	TBranch *hgg36_branch;
	bool hgg36_isLoaded;
	int	hgg50_;
	TBranch *hgg50_branch;
	bool hgg50_isLoaded;
	int	hgg75_;
	TBranch *hgg75_branch;
	bool hgg75_isLoaded;
	int	hgg90_;
	TBranch *hgg90_branch;
	bool hgg90_isLoaded;
	float	rho_;
	TBranch *rho_branch;
	bool rho_isLoaded;
	int	vtxidx_;
	TBranch *vtxidx_branch;
	bool vtxidx_isLoaded;
	int	ng_;
	TBranch *ng_branch;
	bool ng_isLoaded;
	float	etg_;
	TBranch *etg_branch;
	bool etg_isLoaded;
	float	etag_;
	TBranch *etag_branch;
	bool etag_isLoaded;
	float	phig_;
	TBranch *phig_branch;
	bool phig_isLoaded;
	float	hoe_;
	TBranch *hoe_branch;
	bool hoe_isLoaded;
	float	eciso_;
	TBranch *eciso_branch;
	bool eciso_isLoaded;
	float	hciso_;
	TBranch *hciso_branch;
	bool hciso_isLoaded;
	float	tkiso_;
	TBranch *tkiso_branch;
	bool tkiso_isLoaded;
	float	swiss_;
	TBranch *swiss_branch;
	bool swiss_isLoaded;
	float	seed_;
	TBranch *seed_branch;
	bool seed_isLoaded;
	float	s4_;
	TBranch *s4_branch;
	bool s4_isLoaded;
	float	r4_;
	TBranch *r4_branch;
	bool r4_isLoaded;
	int	photon_scidx_;
	TBranch *photon_scidx_branch;
	bool photon_scidx_isLoaded;
	int	photon_pixelseed_;
	TBranch *photon_pixelseed_branch;
	bool photon_pixelseed_isLoaded;
	float	photon_e15_;
	TBranch *photon_e15_branch;
	bool photon_e15_isLoaded;
	float	photon_e25max_;
	TBranch *photon_e25max_branch;
	bool photon_e25max_isLoaded;
	float	photon_e33_;
	TBranch *photon_e33_branch;
	bool photon_e33_isLoaded;
	float	photon_e55_;
	TBranch *photon_e55_branch;
	bool photon_e55_isLoaded;
	float	photon_ecalIso03_;
	TBranch *photon_ecalIso03_branch;
	bool photon_ecalIso03_isLoaded;
	float	photon_ecalIso04_;
	TBranch *photon_ecalIso04_branch;
	bool photon_ecalIso04_isLoaded;
	float	photon_hcalIso03_;
	TBranch *photon_hcalIso03_branch;
	bool photon_hcalIso03_isLoaded;
	float	photon_hcalIso04_;
	TBranch *photon_hcalIso04_branch;
	bool photon_hcalIso04_isLoaded;
	float	photon_ntkIsoHollow03_;
	TBranch *photon_ntkIsoHollow03_branch;
	bool photon_ntkIsoHollow03_isLoaded;
	float	photon_ntkIsoHollow04_;
	TBranch *photon_ntkIsoHollow04_branch;
	bool photon_ntkIsoHollow04_isLoaded;
	float	photon_ntkIsoSolid03_;
	TBranch *photon_ntkIsoSolid03_branch;
	bool photon_ntkIsoSolid03_isLoaded;
	float	photon_ntkIsoSolid04_;
	TBranch *photon_ntkIsoSolid04_branch;
	bool photon_ntkIsoSolid04_isLoaded;
	float	photon_sigmaEtaEta_;
	TBranch *photon_sigmaEtaEta_branch;
	bool photon_sigmaEtaEta_isLoaded;
	float	photon_sigmaIEtaIEta_;
	TBranch *photon_sigmaIEtaIEta_branch;
	bool photon_sigmaIEtaIEta_isLoaded;
	float	photon_sigmaIPhiIPhi_;
	TBranch *photon_sigmaIPhiIPhi_branch;
	bool photon_sigmaIPhiIPhi_isLoaded;
	float	photon_tkisoHollow03_;
	TBranch *photon_tkisoHollow03_branch;
	bool photon_tkisoHollow03_isLoaded;
	float	photon_tkisoHollow04_;
	TBranch *photon_tkisoHollow04_branch;
	bool photon_tkisoHollow04_isLoaded;
	float	photon_tkisoSolid03_;
	TBranch *photon_tkisoSolid03_branch;
	bool photon_tkisoSolid03_isLoaded;
	float	photon_tkisoSolid04_;
	TBranch *photon_tkisoSolid04_branch;
	bool photon_tkisoSolid04_isLoaded;
	float	jetdr_;
	TBranch *jetdr_branch;
	bool jetdr_isLoaded;
	float	jetpt_;
	TBranch *jetpt_branch;
	bool jetpt_isLoaded;
	float	calojetpt_;
	TBranch *calojetpt_branch;
	bool calojetpt_isLoaded;
	int	pfjetid_;
	TBranch *pfjetid_branch;
	bool pfjetid_isLoaded;
	float	jeteta_;
	TBranch *jeteta_branch;
	bool jeteta_isLoaded;
	float	jetenergy_;
	TBranch *jetenergy_branch;
	bool jetenergy_isLoaded;
	float	jetchargedemfrac_;
	TBranch *jetchargedemfrac_branch;
	bool jetchargedemfrac_isLoaded;
	float	jetchargedhadfrac_;
	TBranch *jetchargedhadfrac_branch;
	bool jetchargedhadfrac_isLoaded;
	float	jetneutralemfrac_;
	TBranch *jetneutralemfrac_branch;
	bool jetneutralemfrac_isLoaded;
	float	jetneutralhadfrac_;
	TBranch *jetneutralhadfrac_branch;
	bool jetneutralhadfrac_isLoaded;
	int	jetncharged_;
	TBranch *jetncharged_branch;
	bool jetncharged_isLoaded;
	int	jetnmuon_;
	TBranch *jetnmuon_branch;
	bool jetnmuon_isLoaded;
	int	jetnneutral_;
	TBranch *jetnneutral_branch;
	bool jetnneutral_isLoaded;
	float	jetdphimet_;
	TBranch *jetdphimet_branch;
	bool jetdphimet_isLoaded;
	float	jetdpt_;
	TBranch *jetdpt_branch;
	bool jetdpt_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *jet1_;
	TBranch *jet1_branch;
	bool jet1_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *jet2_;
	TBranch *jet2_branch;
	bool jet2_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *jet3_;
	TBranch *jet3_branch;
	bool jet3_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *jet4_;
	TBranch *jet4_branch;
	bool jet4_isLoaded;
	int	jet1flav_;
	TBranch *jet1flav_branch;
	bool jet1flav_isLoaded;
	int	jet2flav_;
	TBranch *jet2flav_branch;
	bool jet2flav_isLoaded;
	int	jet3flav_;
	TBranch *jet3flav_branch;
	bool jet3flav_isLoaded;
	int	jet4flav_;
	TBranch *jet4flav_branch;
	bool jet4flav_isLoaded;
	int	jet1mcfa_;
	TBranch *jet1mcfa_branch;
	bool jet1mcfa_isLoaded;
	int	jet2mcfa_;
	TBranch *jet2mcfa_branch;
	bool jet2mcfa_isLoaded;
	int	jet3mcfa_;
	TBranch *jet3mcfa_branch;
	bool jet3mcfa_isLoaded;
	int	jet4mcfa_;
	TBranch *jet4mcfa_branch;
	bool jet4mcfa_isLoaded;
	int	jet1mcfp_;
	TBranch *jet1mcfp_branch;
	bool jet1mcfp_isLoaded;
	int	jet2mcfp_;
	TBranch *jet2mcfp_branch;
	bool jet2mcfp_isLoaded;
	int	jet3mcfp_;
	TBranch *jet3mcfp_branch;
	bool jet3mcfp_isLoaded;
	int	jet4mcfp_;
	TBranch *jet4mcfp_branch;
	bool jet4mcfp_isLoaded;
	float	csv1_;
	TBranch *csv1_branch;
	bool csv1_isLoaded;
	float	csv2_;
	TBranch *csv2_branch;
	bool csv2_isLoaded;
	float	csv3_;
	TBranch *csv3_branch;
	bool csv3_isLoaded;
	float	csv4_;
	TBranch *csv4_branch;
	bool csv4_isLoaded;
	float	jet1drgen_;
	TBranch *jet1drgen_branch;
	bool jet1drgen_isLoaded;
	float	jet2drgen_;
	TBranch *jet2drgen_branch;
	bool jet2drgen_isLoaded;
	float	jet3drgen_;
	TBranch *jet3drgen_branch;
	bool jet3drgen_isLoaded;
	float	jet4drgen_;
	TBranch *jet4drgen_branch;
	bool jet4drgen_isLoaded;
	float	jet1beta1_01_;
	TBranch *jet1beta1_01_branch;
	bool jet1beta1_01_isLoaded;
	float	jet2beta1_01_;
	TBranch *jet2beta1_01_branch;
	bool jet2beta1_01_isLoaded;
	float	jet3beta1_01_;
	TBranch *jet3beta1_01_branch;
	bool jet3beta1_01_isLoaded;
	float	jet4beta1_01_;
	TBranch *jet4beta1_01_branch;
	bool jet4beta1_01_isLoaded;
	float	jet1beta2_01_;
	TBranch *jet1beta2_01_branch;
	bool jet1beta2_01_isLoaded;
	float	jet2beta2_01_;
	TBranch *jet2beta2_01_branch;
	bool jet2beta2_01_isLoaded;
	float	jet3beta2_01_;
	TBranch *jet3beta2_01_branch;
	bool jet3beta2_01_isLoaded;
	float	jet4beta2_01_;
	TBranch *jet4beta2_01_branch;
	bool jet4beta2_01_isLoaded;
	float	jet1beta1_05_;
	TBranch *jet1beta1_05_branch;
	bool jet1beta1_05_isLoaded;
	float	jet2beta1_05_;
	TBranch *jet2beta1_05_branch;
	bool jet2beta1_05_isLoaded;
	float	jet3beta1_05_;
	TBranch *jet3beta1_05_branch;
	bool jet3beta1_05_isLoaded;
	float	jet4beta1_05_;
	TBranch *jet4beta1_05_branch;
	bool jet4beta1_05_isLoaded;
	float	jet1beta2_05_;
	TBranch *jet1beta2_05_branch;
	bool jet1beta2_05_isLoaded;
	float	jet2beta2_05_;
	TBranch *jet2beta2_05_branch;
	bool jet2beta2_05_isLoaded;
	float	jet3beta2_05_;
	TBranch *jet3beta2_05_branch;
	bool jet3beta2_05_isLoaded;
	float	jet4beta2_05_;
	TBranch *jet4beta2_05_branch;
	bool jet4beta2_05_isLoaded;
	float	jet1beta1_10_;
	TBranch *jet1beta1_10_branch;
	bool jet1beta1_10_isLoaded;
	float	jet2beta1_10_;
	TBranch *jet2beta1_10_branch;
	bool jet2beta1_10_isLoaded;
	float	jet3beta1_10_;
	TBranch *jet3beta1_10_branch;
	bool jet3beta1_10_isLoaded;
	float	jet4beta1_10_;
	TBranch *jet4beta1_10_branch;
	bool jet4beta1_10_isLoaded;
	float	jet1beta2_10_;
	TBranch *jet1beta2_10_branch;
	bool jet1beta2_10_isLoaded;
	float	jet2beta2_10_;
	TBranch *jet2beta2_10_branch;
	bool jet2beta2_10_isLoaded;
	float	jet3beta2_10_;
	TBranch *jet3beta2_10_branch;
	bool jet3beta2_10_isLoaded;
	float	jet4beta2_10_;
	TBranch *jet4beta2_10_branch;
	bool jet4beta2_10_isLoaded;
	int	csc_;
	TBranch *csc_branch;
	bool csc_isLoaded;
	int	hbhe_;
	TBranch *hbhe_branch;
	bool hbhe_isLoaded;
	int	hbhenew_;
	TBranch *hbhenew_branch;
	bool hbhenew_isLoaded;
	int	hcallaser_;
	TBranch *hcallaser_branch;
	bool hcallaser_isLoaded;
	int	ecallaser_;
	TBranch *ecallaser_branch;
	bool ecallaser_isLoaded;
	int	ecaltp_;
	TBranch *ecaltp_branch;
	bool ecaltp_isLoaded;
	int	trkfail_;
	TBranch *trkfail_branch;
	bool trkfail_isLoaded;
	int	eebadsc_;
	TBranch *eebadsc_branch;
	bool eebadsc_isLoaded;
	float	mjj_;
	TBranch *mjj_branch;
	bool mjj_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *pujets_;
	TBranch *pujets_branch;
	bool pujets_isLoaded;
	int	npujets_;
	TBranch *npujets_branch;
	bool npujets_isLoaded;
public: 
void Init(TTree *tree) {
	jet1_branch = 0;
	if (tree->GetBranch("jet1") != 0) {
		jet1_branch = tree->GetBranch("jet1");
		if (jet1_branch) {jet1_branch->SetAddress(&jet1_);}
	}
	jet2_branch = 0;
	if (tree->GetBranch("jet2") != 0) {
		jet2_branch = tree->GetBranch("jet2");
		if (jet2_branch) {jet2_branch->SetAddress(&jet2_);}
	}
	jet3_branch = 0;
	if (tree->GetBranch("jet3") != 0) {
		jet3_branch = tree->GetBranch("jet3");
		if (jet3_branch) {jet3_branch->SetAddress(&jet3_);}
	}
	jet4_branch = 0;
	if (tree->GetBranch("jet4") != 0) {
		jet4_branch = tree->GetBranch("jet4");
		if (jet4_branch) {jet4_branch->SetAddress(&jet4_);}
	}
	pujets_branch = 0;
	if (tree->GetBranch("pujets") != 0) {
		pujets_branch = tree->GetBranch("pujets");
		if (pujets_branch) {pujets_branch->SetAddress(&pujets_);}
	}
  tree->SetMakeClass(1);
	run_branch = 0;
	if (tree->GetBranch("run") != 0) {
		run_branch = tree->GetBranch("run");
		if (run_branch) {run_branch->SetAddress(&run_);}
	}
	lumi_branch = 0;
	if (tree->GetBranch("lumi") != 0) {
		lumi_branch = tree->GetBranch("lumi");
		if (lumi_branch) {lumi_branch->SetAddress(&lumi_);}
	}
	event_branch = 0;
	if (tree->GetBranch("event") != 0) {
		event_branch = tree->GetBranch("event");
		if (event_branch) {event_branch->SetAddress(&event_);}
	}
	nvtx_branch = 0;
	if (tree->GetBranch("nvtx") != 0) {
		nvtx_branch = tree->GetBranch("nvtx");
		if (nvtx_branch) {nvtx_branch->SetAddress(&nvtx_);}
	}
	weight_branch = 0;
	if (tree->GetBranch("weight") != 0) {
		weight_branch = tree->GetBranch("weight");
		if (weight_branch) {weight_branch->SetAddress(&weight_);}
	}
	pthat_branch = 0;
	if (tree->GetBranch("pthat") != 0) {
		pthat_branch = tree->GetBranch("pthat");
		if (pthat_branch) {pthat_branch->SetAddress(&pthat_);}
	}
	failjetid_branch = 0;
	if (tree->GetBranch("failjetid") != 0) {
		failjetid_branch = tree->GetBranch("failjetid");
		if (failjetid_branch) {failjetid_branch->SetAddress(&failjetid_);}
	}
	maxemf_branch = 0;
	if (tree->GetBranch("maxemf") != 0) {
		maxemf_branch = tree->GetBranch("maxemf");
		if (maxemf_branch) {maxemf_branch->SetAddress(&maxemf_);}
	}
	maxleppt_branch = 0;
	if (tree->GetBranch("maxleppt") != 0) {
		maxleppt_branch = tree->GetBranch("maxleppt");
		if (maxleppt_branch) {maxleppt_branch->SetAddress(&maxleppt_);}
	}
	elveto_branch = 0;
	if (tree->GetBranch("elveto") != 0) {
		elveto_branch = tree->GetBranch("elveto");
		if (elveto_branch) {elveto_branch->SetAddress(&elveto_);}
	}
	ht30_branch = 0;
	if (tree->GetBranch("ht30") != 0) {
		ht30_branch = tree->GetBranch("ht30");
		if (ht30_branch) {ht30_branch->SetAddress(&ht30_);}
	}
	ht40_branch = 0;
	if (tree->GetBranch("ht40") != 0) {
		ht40_branch = tree->GetBranch("ht40");
		if (ht40_branch) {ht40_branch->SetAddress(&ht40_);}
	}
	jzb_branch = 0;
	if (tree->GetBranch("jzb") != 0) {
		jzb_branch = tree->GetBranch("jzb");
		if (jzb_branch) {jzb_branch->SetAddress(&jzb_);}
	}
	pfmet_branch = 0;
	if (tree->GetBranch("pfmet") != 0) {
		pfmet_branch = tree->GetBranch("pfmet");
		if (pfmet_branch) {pfmet_branch->SetAddress(&pfmet_);}
	}
	pfmett1_branch = 0;
	if (tree->GetBranch("pfmett1") != 0) {
		pfmett1_branch = tree->GetBranch("pfmett1");
		if (pfmett1_branch) {pfmett1_branch->SetAddress(&pfmett1_);}
	}
	pfmett1new_branch = 0;
	if (tree->GetBranch("pfmett1new") != 0) {
		pfmett1new_branch = tree->GetBranch("pfmett1new");
		if (pfmett1new_branch) {pfmett1new_branch->SetAddress(&pfmett1new_);}
	}
	pfmet_type1_pt30_branch = 0;
	if (tree->GetBranch("pfmet_type1_pt30") != 0) {
		pfmet_type1_pt30_branch = tree->GetBranch("pfmet_type1_pt30");
		if (pfmet_type1_pt30_branch) {pfmet_type1_pt30_branch->SetAddress(&pfmet_type1_pt30_);}
	}
	pfmet_type1_pt15_branch = 0;
	if (tree->GetBranch("pfmet_type1_pt15") != 0) {
		pfmet_type1_pt15_branch = tree->GetBranch("pfmet_type1_pt15");
		if (pfmet_type1_pt15_branch) {pfmet_type1_pt15_branch->SetAddress(&pfmet_type1_pt15_);}
	}
	pfmetphi_branch = 0;
	if (tree->GetBranch("pfmetphi") != 0) {
		pfmetphi_branch = tree->GetBranch("pfmetphi");
		if (pfmetphi_branch) {pfmetphi_branch->SetAddress(&pfmetphi_);}
	}
	pfmett1phi_branch = 0;
	if (tree->GetBranch("pfmett1phi") != 0) {
		pfmett1phi_branch = tree->GetBranch("pfmett1phi");
		if (pfmett1phi_branch) {pfmett1phi_branch->SetAddress(&pfmett1phi_);}
	}
	pfmett1newphi_branch = 0;
	if (tree->GetBranch("pfmett1newphi") != 0) {
		pfmett1newphi_branch = tree->GetBranch("pfmett1newphi");
		if (pfmett1newphi_branch) {pfmett1newphi_branch->SetAddress(&pfmett1newphi_);}
	}
	pfsumet_branch = 0;
	if (tree->GetBranch("pfsumet") != 0) {
		pfsumet_branch = tree->GetBranch("pfsumet");
		if (pfsumet_branch) {pfsumet_branch->SetAddress(&pfsumet_);}
	}
	met_branch = 0;
	if (tree->GetBranch("met") != 0) {
		met_branch = tree->GetBranch("met");
		if (met_branch) {met_branch->SetAddress(&met_);}
	}
	metphi_branch = 0;
	if (tree->GetBranch("metphi") != 0) {
		metphi_branch = tree->GetBranch("metphi");
		if (metphi_branch) {metphi_branch->SetAddress(&metphi_);}
	}
	sumet_branch = 0;
	if (tree->GetBranch("sumet") != 0) {
		sumet_branch = tree->GetBranch("sumet");
		if (sumet_branch) {sumet_branch->SetAddress(&sumet_);}
	}
	mumet_branch = 0;
	if (tree->GetBranch("mumet") != 0) {
		mumet_branch = tree->GetBranch("mumet");
		if (mumet_branch) {mumet_branch->SetAddress(&mumet_);}
	}
	mumetphi_branch = 0;
	if (tree->GetBranch("mumetphi") != 0) {
		mumetphi_branch = tree->GetBranch("mumetphi");
		if (mumetphi_branch) {mumetphi_branch->SetAddress(&mumetphi_);}
	}
	musumet_branch = 0;
	if (tree->GetBranch("musumet") != 0) {
		musumet_branch = tree->GetBranch("musumet");
		if (musumet_branch) {musumet_branch->SetAddress(&musumet_);}
	}
	mujesmet_branch = 0;
	if (tree->GetBranch("mujesmet") != 0) {
		mujesmet_branch = tree->GetBranch("mujesmet");
		if (mujesmet_branch) {mujesmet_branch->SetAddress(&mujesmet_);}
	}
	mujesmetphi_branch = 0;
	if (tree->GetBranch("mujesmetphi") != 0) {
		mujesmetphi_branch = tree->GetBranch("mujesmetphi");
		if (mujesmetphi_branch) {mujesmetphi_branch->SetAddress(&mujesmetphi_);}
	}
	mujessumet_branch = 0;
	if (tree->GetBranch("mujessumet") != 0) {
		mujessumet_branch = tree->GetBranch("mujessumet");
		if (mujessumet_branch) {mujessumet_branch->SetAddress(&mujessumet_);}
	}
	genmet_branch = 0;
	if (tree->GetBranch("genmet") != 0) {
		genmet_branch = tree->GetBranch("genmet");
		if (genmet_branch) {genmet_branch->SetAddress(&genmet_);}
	}
	genmetphi_branch = 0;
	if (tree->GetBranch("genmetphi") != 0) {
		genmetphi_branch = tree->GetBranch("genmetphi");
		if (genmetphi_branch) {genmetphi_branch->SetAddress(&genmetphi_);}
	}
	gensumet_branch = 0;
	if (tree->GetBranch("gensumet") != 0) {
		gensumet_branch = tree->GetBranch("gensumet");
		if (gensumet_branch) {gensumet_branch->SetAddress(&gensumet_);}
	}
	dphixmet_branch = 0;
	if (tree->GetBranch("dphixmet") != 0) {
		dphixmet_branch = tree->GetBranch("dphixmet");
		if (dphixmet_branch) {dphixmet_branch->SetAddress(&dphixmet_);}
	}
	metpar_branch = 0;
	if (tree->GetBranch("metpar") != 0) {
		metpar_branch = tree->GetBranch("metpar");
		if (metpar_branch) {metpar_branch->SetAddress(&metpar_);}
	}
	metperp_branch = 0;
	if (tree->GetBranch("metperp") != 0) {
		metperp_branch = tree->GetBranch("metperp");
		if (metperp_branch) {metperp_branch->SetAddress(&metperp_);}
	}
	tcmet_branch = 0;
	if (tree->GetBranch("tcmet") != 0) {
		tcmet_branch = tree->GetBranch("tcmet");
		if (tcmet_branch) {tcmet_branch->SetAddress(&tcmet_);}
	}
	tcmetphi_branch = 0;
	if (tree->GetBranch("tcmetphi") != 0) {
		tcmetphi_branch = tree->GetBranch("tcmetphi");
		if (tcmetphi_branch) {tcmetphi_branch->SetAddress(&tcmetphi_);}
	}
	tcsumet_branch = 0;
	if (tree->GetBranch("tcsumet") != 0) {
		tcsumet_branch = tree->GetBranch("tcsumet");
		if (tcsumet_branch) {tcsumet_branch->SetAddress(&tcsumet_);}
	}
	tcmetNew_branch = 0;
	if (tree->GetBranch("tcmetNew") != 0) {
		tcmetNew_branch = tree->GetBranch("tcmetNew");
		if (tcmetNew_branch) {tcmetNew_branch->SetAddress(&tcmetNew_);}
	}
	tcmetNew_type1_pt30_branch = 0;
	if (tree->GetBranch("tcmetNew_type1_pt30") != 0) {
		tcmetNew_type1_pt30_branch = tree->GetBranch("tcmetNew_type1_pt30");
		if (tcmetNew_type1_pt30_branch) {tcmetNew_type1_pt30_branch->SetAddress(&tcmetNew_type1_pt30_);}
	}
	tcmetNew_type1_pt15_branch = 0;
	if (tree->GetBranch("tcmetNew_type1_pt15") != 0) {
		tcmetNew_type1_pt15_branch = tree->GetBranch("tcmetNew_type1_pt15");
		if (tcmetNew_type1_pt15_branch) {tcmetNew_type1_pt15_branch->SetAddress(&tcmetNew_type1_pt15_);}
	}
	tcmetphiNew_branch = 0;
	if (tree->GetBranch("tcmetphiNew") != 0) {
		tcmetphiNew_branch = tree->GetBranch("tcmetphiNew");
		if (tcmetphiNew_branch) {tcmetphiNew_branch->SetAddress(&tcmetphiNew_);}
	}
	tcsumetNew_branch = 0;
	if (tree->GetBranch("tcsumetNew") != 0) {
		tcsumetNew_branch = tree->GetBranch("tcsumetNew");
		if (tcsumetNew_branch) {tcsumetNew_branch->SetAddress(&tcsumetNew_);}
	}
	njets_branch = 0;
	if (tree->GetBranch("njets") != 0) {
		njets_branch = tree->GetBranch("njets");
		if (njets_branch) {njets_branch->SetAddress(&njets_);}
	}
	njets10_branch = 0;
	if (tree->GetBranch("njets10") != 0) {
		njets10_branch = tree->GetBranch("njets10");
		if (njets10_branch) {njets10_branch->SetAddress(&njets10_);}
	}
	njets15_branch = 0;
	if (tree->GetBranch("njets15") != 0) {
		njets15_branch = tree->GetBranch("njets15");
		if (njets15_branch) {njets15_branch->SetAddress(&njets15_);}
	}
	njets20_branch = 0;
	if (tree->GetBranch("njets20") != 0) {
		njets20_branch = tree->GetBranch("njets20");
		if (njets20_branch) {njets20_branch->SetAddress(&njets20_);}
	}
	njets40_branch = 0;
	if (tree->GetBranch("njets40") != 0) {
		njets40_branch = tree->GetBranch("njets40");
		if (njets40_branch) {njets40_branch->SetAddress(&njets40_);}
	}
	ht_branch = 0;
	if (tree->GetBranch("ht") != 0) {
		ht_branch = tree->GetBranch("ht");
		if (ht_branch) {ht_branch->SetAddress(&ht_);}
	}
	ht10_branch = 0;
	if (tree->GetBranch("ht10") != 0) {
		ht10_branch = tree->GetBranch("ht10");
		if (ht10_branch) {ht10_branch->SetAddress(&ht10_);}
	}
	vecjetpt_branch = 0;
	if (tree->GetBranch("vecjetpt") != 0) {
		vecjetpt_branch = tree->GetBranch("vecjetpt");
		if (vecjetpt_branch) {vecjetpt_branch->SetAddress(&vecjetpt_);}
	}
	nbl_branch = 0;
	if (tree->GetBranch("nbl") != 0) {
		nbl_branch = tree->GetBranch("nbl");
		if (nbl_branch) {nbl_branch->SetAddress(&nbl_);}
	}
	nbm_branch = 0;
	if (tree->GetBranch("nbm") != 0) {
		nbm_branch = tree->GetBranch("nbm");
		if (nbm_branch) {nbm_branch->SetAddress(&nbm_);}
	}
	nbt_branch = 0;
	if (tree->GetBranch("nbt") != 0) {
		nbt_branch = tree->GetBranch("nbt");
		if (nbt_branch) {nbt_branch->SetAddress(&nbt_);}
	}
	ndphijetmet_branch = 0;
	if (tree->GetBranch("ndphijetmet") != 0) {
		ndphijetmet_branch = tree->GetBranch("ndphijetmet");
		if (ndphijetmet_branch) {ndphijetmet_branch->SetAddress(&ndphijetmet_);}
	}
	maxjetpt_branch = 0;
	if (tree->GetBranch("maxjetpt") != 0) {
		maxjetpt_branch = tree->GetBranch("maxjetpt");
		if (maxjetpt_branch) {maxjetpt_branch->SetAddress(&maxjetpt_);}
	}
	maxjetdphimet_branch = 0;
	if (tree->GetBranch("maxjetdphimet") != 0) {
		maxjetdphimet_branch = tree->GetBranch("maxjetdphimet");
		if (maxjetdphimet_branch) {maxjetdphimet_branch->SetAddress(&maxjetdphimet_);}
	}
	hlt20_branch = 0;
	if (tree->GetBranch("hlt20") != 0) {
		hlt20_branch = tree->GetBranch("hlt20");
		if (hlt20_branch) {hlt20_branch->SetAddress(&hlt20_);}
	}
	hlt30_branch = 0;
	if (tree->GetBranch("hlt30") != 0) {
		hlt30_branch = tree->GetBranch("hlt30");
		if (hlt30_branch) {hlt30_branch->SetAddress(&hlt30_);}
	}
	hlt50_branch = 0;
	if (tree->GetBranch("hlt50") != 0) {
		hlt50_branch = tree->GetBranch("hlt50");
		if (hlt50_branch) {hlt50_branch->SetAddress(&hlt50_);}
	}
	hlt75_branch = 0;
	if (tree->GetBranch("hlt75") != 0) {
		hlt75_branch = tree->GetBranch("hlt75");
		if (hlt75_branch) {hlt75_branch->SetAddress(&hlt75_);}
	}
	hlt90_branch = 0;
	if (tree->GetBranch("hlt90") != 0) {
		hlt90_branch = tree->GetBranch("hlt90");
		if (hlt90_branch) {hlt90_branch->SetAddress(&hlt90_);}
	}
	hlt135_branch = 0;
	if (tree->GetBranch("hlt135") != 0) {
		hlt135_branch = tree->GetBranch("hlt135");
		if (hlt135_branch) {hlt135_branch->SetAddress(&hlt135_);}
	}
	hlt150_branch = 0;
	if (tree->GetBranch("hlt150") != 0) {
		hlt150_branch = tree->GetBranch("hlt150");
		if (hlt150_branch) {hlt150_branch->SetAddress(&hlt150_);}
	}
	hlt160_branch = 0;
	if (tree->GetBranch("hlt160") != 0) {
		hlt160_branch = tree->GetBranch("hlt160");
		if (hlt160_branch) {hlt160_branch->SetAddress(&hlt160_);}
	}
	hgg22_branch = 0;
	if (tree->GetBranch("hgg22") != 0) {
		hgg22_branch = tree->GetBranch("hgg22");
		if (hgg22_branch) {hgg22_branch->SetAddress(&hgg22_);}
	}
	hgg36_branch = 0;
	if (tree->GetBranch("hgg36") != 0) {
		hgg36_branch = tree->GetBranch("hgg36");
		if (hgg36_branch) {hgg36_branch->SetAddress(&hgg36_);}
	}
	hgg50_branch = 0;
	if (tree->GetBranch("hgg50") != 0) {
		hgg50_branch = tree->GetBranch("hgg50");
		if (hgg50_branch) {hgg50_branch->SetAddress(&hgg50_);}
	}
	hgg75_branch = 0;
	if (tree->GetBranch("hgg75") != 0) {
		hgg75_branch = tree->GetBranch("hgg75");
		if (hgg75_branch) {hgg75_branch->SetAddress(&hgg75_);}
	}
	hgg90_branch = 0;
	if (tree->GetBranch("hgg90") != 0) {
		hgg90_branch = tree->GetBranch("hgg90");
		if (hgg90_branch) {hgg90_branch->SetAddress(&hgg90_);}
	}
	rho_branch = 0;
	if (tree->GetBranch("rho") != 0) {
		rho_branch = tree->GetBranch("rho");
		if (rho_branch) {rho_branch->SetAddress(&rho_);}
	}
	vtxidx_branch = 0;
	if (tree->GetBranch("vtxidx") != 0) {
		vtxidx_branch = tree->GetBranch("vtxidx");
		if (vtxidx_branch) {vtxidx_branch->SetAddress(&vtxidx_);}
	}
	ng_branch = 0;
	if (tree->GetBranch("ng") != 0) {
		ng_branch = tree->GetBranch("ng");
		if (ng_branch) {ng_branch->SetAddress(&ng_);}
	}
	etg_branch = 0;
	if (tree->GetBranch("etg") != 0) {
		etg_branch = tree->GetBranch("etg");
		if (etg_branch) {etg_branch->SetAddress(&etg_);}
	}
	etag_branch = 0;
	if (tree->GetBranch("etag") != 0) {
		etag_branch = tree->GetBranch("etag");
		if (etag_branch) {etag_branch->SetAddress(&etag_);}
	}
	phig_branch = 0;
	if (tree->GetBranch("phig") != 0) {
		phig_branch = tree->GetBranch("phig");
		if (phig_branch) {phig_branch->SetAddress(&phig_);}
	}
	hoe_branch = 0;
	if (tree->GetBranch("hoe") != 0) {
		hoe_branch = tree->GetBranch("hoe");
		if (hoe_branch) {hoe_branch->SetAddress(&hoe_);}
	}
	eciso_branch = 0;
	if (tree->GetBranch("eciso") != 0) {
		eciso_branch = tree->GetBranch("eciso");
		if (eciso_branch) {eciso_branch->SetAddress(&eciso_);}
	}
	hciso_branch = 0;
	if (tree->GetBranch("hciso") != 0) {
		hciso_branch = tree->GetBranch("hciso");
		if (hciso_branch) {hciso_branch->SetAddress(&hciso_);}
	}
	tkiso_branch = 0;
	if (tree->GetBranch("tkiso") != 0) {
		tkiso_branch = tree->GetBranch("tkiso");
		if (tkiso_branch) {tkiso_branch->SetAddress(&tkiso_);}
	}
	swiss_branch = 0;
	if (tree->GetBranch("swiss") != 0) {
		swiss_branch = tree->GetBranch("swiss");
		if (swiss_branch) {swiss_branch->SetAddress(&swiss_);}
	}
	seed_branch = 0;
	if (tree->GetBranch("seed") != 0) {
		seed_branch = tree->GetBranch("seed");
		if (seed_branch) {seed_branch->SetAddress(&seed_);}
	}
	s4_branch = 0;
	if (tree->GetBranch("s4") != 0) {
		s4_branch = tree->GetBranch("s4");
		if (s4_branch) {s4_branch->SetAddress(&s4_);}
	}
	r4_branch = 0;
	if (tree->GetBranch("r4") != 0) {
		r4_branch = tree->GetBranch("r4");
		if (r4_branch) {r4_branch->SetAddress(&r4_);}
	}
	photon_scidx_branch = 0;
	if (tree->GetBranch("photon_scidx") != 0) {
		photon_scidx_branch = tree->GetBranch("photon_scidx");
		if (photon_scidx_branch) {photon_scidx_branch->SetAddress(&photon_scidx_);}
	}
	photon_pixelseed_branch = 0;
	if (tree->GetBranch("photon_pixelseed") != 0) {
		photon_pixelseed_branch = tree->GetBranch("photon_pixelseed");
		if (photon_pixelseed_branch) {photon_pixelseed_branch->SetAddress(&photon_pixelseed_);}
	}
	photon_e15_branch = 0;
	if (tree->GetBranch("photon_e15") != 0) {
		photon_e15_branch = tree->GetBranch("photon_e15");
		if (photon_e15_branch) {photon_e15_branch->SetAddress(&photon_e15_);}
	}
	photon_e25max_branch = 0;
	if (tree->GetBranch("photon_e25max") != 0) {
		photon_e25max_branch = tree->GetBranch("photon_e25max");
		if (photon_e25max_branch) {photon_e25max_branch->SetAddress(&photon_e25max_);}
	}
	photon_e33_branch = 0;
	if (tree->GetBranch("photon_e33") != 0) {
		photon_e33_branch = tree->GetBranch("photon_e33");
		if (photon_e33_branch) {photon_e33_branch->SetAddress(&photon_e33_);}
	}
	photon_e55_branch = 0;
	if (tree->GetBranch("photon_e55") != 0) {
		photon_e55_branch = tree->GetBranch("photon_e55");
		if (photon_e55_branch) {photon_e55_branch->SetAddress(&photon_e55_);}
	}
	photon_ecalIso03_branch = 0;
	if (tree->GetBranch("photon_ecalIso03") != 0) {
		photon_ecalIso03_branch = tree->GetBranch("photon_ecalIso03");
		if (photon_ecalIso03_branch) {photon_ecalIso03_branch->SetAddress(&photon_ecalIso03_);}
	}
	photon_ecalIso04_branch = 0;
	if (tree->GetBranch("photon_ecalIso04") != 0) {
		photon_ecalIso04_branch = tree->GetBranch("photon_ecalIso04");
		if (photon_ecalIso04_branch) {photon_ecalIso04_branch->SetAddress(&photon_ecalIso04_);}
	}
	photon_hcalIso03_branch = 0;
	if (tree->GetBranch("photon_hcalIso03") != 0) {
		photon_hcalIso03_branch = tree->GetBranch("photon_hcalIso03");
		if (photon_hcalIso03_branch) {photon_hcalIso03_branch->SetAddress(&photon_hcalIso03_);}
	}
	photon_hcalIso04_branch = 0;
	if (tree->GetBranch("photon_hcalIso04") != 0) {
		photon_hcalIso04_branch = tree->GetBranch("photon_hcalIso04");
		if (photon_hcalIso04_branch) {photon_hcalIso04_branch->SetAddress(&photon_hcalIso04_);}
	}
	photon_ntkIsoHollow03_branch = 0;
	if (tree->GetBranch("photon_ntkIsoHollow03") != 0) {
		photon_ntkIsoHollow03_branch = tree->GetBranch("photon_ntkIsoHollow03");
		if (photon_ntkIsoHollow03_branch) {photon_ntkIsoHollow03_branch->SetAddress(&photon_ntkIsoHollow03_);}
	}
	photon_ntkIsoHollow04_branch = 0;
	if (tree->GetBranch("photon_ntkIsoHollow04") != 0) {
		photon_ntkIsoHollow04_branch = tree->GetBranch("photon_ntkIsoHollow04");
		if (photon_ntkIsoHollow04_branch) {photon_ntkIsoHollow04_branch->SetAddress(&photon_ntkIsoHollow04_);}
	}
	photon_ntkIsoSolid03_branch = 0;
	if (tree->GetBranch("photon_ntkIsoSolid03") != 0) {
		photon_ntkIsoSolid03_branch = tree->GetBranch("photon_ntkIsoSolid03");
		if (photon_ntkIsoSolid03_branch) {photon_ntkIsoSolid03_branch->SetAddress(&photon_ntkIsoSolid03_);}
	}
	photon_ntkIsoSolid04_branch = 0;
	if (tree->GetBranch("photon_ntkIsoSolid04") != 0) {
		photon_ntkIsoSolid04_branch = tree->GetBranch("photon_ntkIsoSolid04");
		if (photon_ntkIsoSolid04_branch) {photon_ntkIsoSolid04_branch->SetAddress(&photon_ntkIsoSolid04_);}
	}
	photon_sigmaEtaEta_branch = 0;
	if (tree->GetBranch("photon_sigmaEtaEta") != 0) {
		photon_sigmaEtaEta_branch = tree->GetBranch("photon_sigmaEtaEta");
		if (photon_sigmaEtaEta_branch) {photon_sigmaEtaEta_branch->SetAddress(&photon_sigmaEtaEta_);}
	}
	photon_sigmaIEtaIEta_branch = 0;
	if (tree->GetBranch("photon_sigmaIEtaIEta") != 0) {
		photon_sigmaIEtaIEta_branch = tree->GetBranch("photon_sigmaIEtaIEta");
		if (photon_sigmaIEtaIEta_branch) {photon_sigmaIEtaIEta_branch->SetAddress(&photon_sigmaIEtaIEta_);}
	}
	photon_sigmaIPhiIPhi_branch = 0;
	if (tree->GetBranch("photon_sigmaIPhiIPhi") != 0) {
		photon_sigmaIPhiIPhi_branch = tree->GetBranch("photon_sigmaIPhiIPhi");
		if (photon_sigmaIPhiIPhi_branch) {photon_sigmaIPhiIPhi_branch->SetAddress(&photon_sigmaIPhiIPhi_);}
	}
	photon_tkisoHollow03_branch = 0;
	if (tree->GetBranch("photon_tkisoHollow03") != 0) {
		photon_tkisoHollow03_branch = tree->GetBranch("photon_tkisoHollow03");
		if (photon_tkisoHollow03_branch) {photon_tkisoHollow03_branch->SetAddress(&photon_tkisoHollow03_);}
	}
	photon_tkisoHollow04_branch = 0;
	if (tree->GetBranch("photon_tkisoHollow04") != 0) {
		photon_tkisoHollow04_branch = tree->GetBranch("photon_tkisoHollow04");
		if (photon_tkisoHollow04_branch) {photon_tkisoHollow04_branch->SetAddress(&photon_tkisoHollow04_);}
	}
	photon_tkisoSolid03_branch = 0;
	if (tree->GetBranch("photon_tkisoSolid03") != 0) {
		photon_tkisoSolid03_branch = tree->GetBranch("photon_tkisoSolid03");
		if (photon_tkisoSolid03_branch) {photon_tkisoSolid03_branch->SetAddress(&photon_tkisoSolid03_);}
	}
	photon_tkisoSolid04_branch = 0;
	if (tree->GetBranch("photon_tkisoSolid04") != 0) {
		photon_tkisoSolid04_branch = tree->GetBranch("photon_tkisoSolid04");
		if (photon_tkisoSolid04_branch) {photon_tkisoSolid04_branch->SetAddress(&photon_tkisoSolid04_);}
	}
	jetdr_branch = 0;
	if (tree->GetBranch("jetdr") != 0) {
		jetdr_branch = tree->GetBranch("jetdr");
		if (jetdr_branch) {jetdr_branch->SetAddress(&jetdr_);}
	}
	jetpt_branch = 0;
	if (tree->GetBranch("jetpt") != 0) {
		jetpt_branch = tree->GetBranch("jetpt");
		if (jetpt_branch) {jetpt_branch->SetAddress(&jetpt_);}
	}
	calojetpt_branch = 0;
	if (tree->GetBranch("calojetpt") != 0) {
		calojetpt_branch = tree->GetBranch("calojetpt");
		if (calojetpt_branch) {calojetpt_branch->SetAddress(&calojetpt_);}
	}
	pfjetid_branch = 0;
	if (tree->GetBranch("pfjetid") != 0) {
		pfjetid_branch = tree->GetBranch("pfjetid");
		if (pfjetid_branch) {pfjetid_branch->SetAddress(&pfjetid_);}
	}
	jeteta_branch = 0;
	if (tree->GetBranch("jeteta") != 0) {
		jeteta_branch = tree->GetBranch("jeteta");
		if (jeteta_branch) {jeteta_branch->SetAddress(&jeteta_);}
	}
	jetenergy_branch = 0;
	if (tree->GetBranch("jetenergy") != 0) {
		jetenergy_branch = tree->GetBranch("jetenergy");
		if (jetenergy_branch) {jetenergy_branch->SetAddress(&jetenergy_);}
	}
	jetchargedemfrac_branch = 0;
	if (tree->GetBranch("jetchargedemfrac") != 0) {
		jetchargedemfrac_branch = tree->GetBranch("jetchargedemfrac");
		if (jetchargedemfrac_branch) {jetchargedemfrac_branch->SetAddress(&jetchargedemfrac_);}
	}
	jetchargedhadfrac_branch = 0;
	if (tree->GetBranch("jetchargedhadfrac") != 0) {
		jetchargedhadfrac_branch = tree->GetBranch("jetchargedhadfrac");
		if (jetchargedhadfrac_branch) {jetchargedhadfrac_branch->SetAddress(&jetchargedhadfrac_);}
	}
	jetneutralemfrac_branch = 0;
	if (tree->GetBranch("jetneutralemfrac") != 0) {
		jetneutralemfrac_branch = tree->GetBranch("jetneutralemfrac");
		if (jetneutralemfrac_branch) {jetneutralemfrac_branch->SetAddress(&jetneutralemfrac_);}
	}
	jetneutralhadfrac_branch = 0;
	if (tree->GetBranch("jetneutralhadfrac") != 0) {
		jetneutralhadfrac_branch = tree->GetBranch("jetneutralhadfrac");
		if (jetneutralhadfrac_branch) {jetneutralhadfrac_branch->SetAddress(&jetneutralhadfrac_);}
	}
	jetncharged_branch = 0;
	if (tree->GetBranch("jetncharged") != 0) {
		jetncharged_branch = tree->GetBranch("jetncharged");
		if (jetncharged_branch) {jetncharged_branch->SetAddress(&jetncharged_);}
	}
	jetnmuon_branch = 0;
	if (tree->GetBranch("jetnmuon") != 0) {
		jetnmuon_branch = tree->GetBranch("jetnmuon");
		if (jetnmuon_branch) {jetnmuon_branch->SetAddress(&jetnmuon_);}
	}
	jetnneutral_branch = 0;
	if (tree->GetBranch("jetnneutral") != 0) {
		jetnneutral_branch = tree->GetBranch("jetnneutral");
		if (jetnneutral_branch) {jetnneutral_branch->SetAddress(&jetnneutral_);}
	}
	jetdphimet_branch = 0;
	if (tree->GetBranch("jetdphimet") != 0) {
		jetdphimet_branch = tree->GetBranch("jetdphimet");
		if (jetdphimet_branch) {jetdphimet_branch->SetAddress(&jetdphimet_);}
	}
	jetdpt_branch = 0;
	if (tree->GetBranch("jetdpt") != 0) {
		jetdpt_branch = tree->GetBranch("jetdpt");
		if (jetdpt_branch) {jetdpt_branch->SetAddress(&jetdpt_);}
	}
	jet1flav_branch = 0;
	if (tree->GetBranch("jet1flav") != 0) {
		jet1flav_branch = tree->GetBranch("jet1flav");
		if (jet1flav_branch) {jet1flav_branch->SetAddress(&jet1flav_);}
	}
	jet2flav_branch = 0;
	if (tree->GetBranch("jet2flav") != 0) {
		jet2flav_branch = tree->GetBranch("jet2flav");
		if (jet2flav_branch) {jet2flav_branch->SetAddress(&jet2flav_);}
	}
	jet3flav_branch = 0;
	if (tree->GetBranch("jet3flav") != 0) {
		jet3flav_branch = tree->GetBranch("jet3flav");
		if (jet3flav_branch) {jet3flav_branch->SetAddress(&jet3flav_);}
	}
	jet4flav_branch = 0;
	if (tree->GetBranch("jet4flav") != 0) {
		jet4flav_branch = tree->GetBranch("jet4flav");
		if (jet4flav_branch) {jet4flav_branch->SetAddress(&jet4flav_);}
	}
	jet1mcfa_branch = 0;
	if (tree->GetBranch("jet1mcfa") != 0) {
		jet1mcfa_branch = tree->GetBranch("jet1mcfa");
		if (jet1mcfa_branch) {jet1mcfa_branch->SetAddress(&jet1mcfa_);}
	}
	jet2mcfa_branch = 0;
	if (tree->GetBranch("jet2mcfa") != 0) {
		jet2mcfa_branch = tree->GetBranch("jet2mcfa");
		if (jet2mcfa_branch) {jet2mcfa_branch->SetAddress(&jet2mcfa_);}
	}
	jet3mcfa_branch = 0;
	if (tree->GetBranch("jet3mcfa") != 0) {
		jet3mcfa_branch = tree->GetBranch("jet3mcfa");
		if (jet3mcfa_branch) {jet3mcfa_branch->SetAddress(&jet3mcfa_);}
	}
	jet4mcfa_branch = 0;
	if (tree->GetBranch("jet4mcfa") != 0) {
		jet4mcfa_branch = tree->GetBranch("jet4mcfa");
		if (jet4mcfa_branch) {jet4mcfa_branch->SetAddress(&jet4mcfa_);}
	}
	jet1mcfp_branch = 0;
	if (tree->GetBranch("jet1mcfp") != 0) {
		jet1mcfp_branch = tree->GetBranch("jet1mcfp");
		if (jet1mcfp_branch) {jet1mcfp_branch->SetAddress(&jet1mcfp_);}
	}
	jet2mcfp_branch = 0;
	if (tree->GetBranch("jet2mcfp") != 0) {
		jet2mcfp_branch = tree->GetBranch("jet2mcfp");
		if (jet2mcfp_branch) {jet2mcfp_branch->SetAddress(&jet2mcfp_);}
	}
	jet3mcfp_branch = 0;
	if (tree->GetBranch("jet3mcfp") != 0) {
		jet3mcfp_branch = tree->GetBranch("jet3mcfp");
		if (jet3mcfp_branch) {jet3mcfp_branch->SetAddress(&jet3mcfp_);}
	}
	jet4mcfp_branch = 0;
	if (tree->GetBranch("jet4mcfp") != 0) {
		jet4mcfp_branch = tree->GetBranch("jet4mcfp");
		if (jet4mcfp_branch) {jet4mcfp_branch->SetAddress(&jet4mcfp_);}
	}
	csv1_branch = 0;
	if (tree->GetBranch("csv1") != 0) {
		csv1_branch = tree->GetBranch("csv1");
		if (csv1_branch) {csv1_branch->SetAddress(&csv1_);}
	}
	csv2_branch = 0;
	if (tree->GetBranch("csv2") != 0) {
		csv2_branch = tree->GetBranch("csv2");
		if (csv2_branch) {csv2_branch->SetAddress(&csv2_);}
	}
	csv3_branch = 0;
	if (tree->GetBranch("csv3") != 0) {
		csv3_branch = tree->GetBranch("csv3");
		if (csv3_branch) {csv3_branch->SetAddress(&csv3_);}
	}
	csv4_branch = 0;
	if (tree->GetBranch("csv4") != 0) {
		csv4_branch = tree->GetBranch("csv4");
		if (csv4_branch) {csv4_branch->SetAddress(&csv4_);}
	}
	jet1drgen_branch = 0;
	if (tree->GetBranch("jet1drgen") != 0) {
		jet1drgen_branch = tree->GetBranch("jet1drgen");
		if (jet1drgen_branch) {jet1drgen_branch->SetAddress(&jet1drgen_);}
	}
	jet2drgen_branch = 0;
	if (tree->GetBranch("jet2drgen") != 0) {
		jet2drgen_branch = tree->GetBranch("jet2drgen");
		if (jet2drgen_branch) {jet2drgen_branch->SetAddress(&jet2drgen_);}
	}
	jet3drgen_branch = 0;
	if (tree->GetBranch("jet3drgen") != 0) {
		jet3drgen_branch = tree->GetBranch("jet3drgen");
		if (jet3drgen_branch) {jet3drgen_branch->SetAddress(&jet3drgen_);}
	}
	jet4drgen_branch = 0;
	if (tree->GetBranch("jet4drgen") != 0) {
		jet4drgen_branch = tree->GetBranch("jet4drgen");
		if (jet4drgen_branch) {jet4drgen_branch->SetAddress(&jet4drgen_);}
	}
	jet1beta1_01_branch = 0;
	if (tree->GetBranch("jet1beta1_01") != 0) {
		jet1beta1_01_branch = tree->GetBranch("jet1beta1_01");
		if (jet1beta1_01_branch) {jet1beta1_01_branch->SetAddress(&jet1beta1_01_);}
	}
	jet2beta1_01_branch = 0;
	if (tree->GetBranch("jet2beta1_01") != 0) {
		jet2beta1_01_branch = tree->GetBranch("jet2beta1_01");
		if (jet2beta1_01_branch) {jet2beta1_01_branch->SetAddress(&jet2beta1_01_);}
	}
	jet3beta1_01_branch = 0;
	if (tree->GetBranch("jet3beta1_01") != 0) {
		jet3beta1_01_branch = tree->GetBranch("jet3beta1_01");
		if (jet3beta1_01_branch) {jet3beta1_01_branch->SetAddress(&jet3beta1_01_);}
	}
	jet4beta1_01_branch = 0;
	if (tree->GetBranch("jet4beta1_01") != 0) {
		jet4beta1_01_branch = tree->GetBranch("jet4beta1_01");
		if (jet4beta1_01_branch) {jet4beta1_01_branch->SetAddress(&jet4beta1_01_);}
	}
	jet1beta2_01_branch = 0;
	if (tree->GetBranch("jet1beta2_01") != 0) {
		jet1beta2_01_branch = tree->GetBranch("jet1beta2_01");
		if (jet1beta2_01_branch) {jet1beta2_01_branch->SetAddress(&jet1beta2_01_);}
	}
	jet2beta2_01_branch = 0;
	if (tree->GetBranch("jet2beta2_01") != 0) {
		jet2beta2_01_branch = tree->GetBranch("jet2beta2_01");
		if (jet2beta2_01_branch) {jet2beta2_01_branch->SetAddress(&jet2beta2_01_);}
	}
	jet3beta2_01_branch = 0;
	if (tree->GetBranch("jet3beta2_01") != 0) {
		jet3beta2_01_branch = tree->GetBranch("jet3beta2_01");
		if (jet3beta2_01_branch) {jet3beta2_01_branch->SetAddress(&jet3beta2_01_);}
	}
	jet4beta2_01_branch = 0;
	if (tree->GetBranch("jet4beta2_01") != 0) {
		jet4beta2_01_branch = tree->GetBranch("jet4beta2_01");
		if (jet4beta2_01_branch) {jet4beta2_01_branch->SetAddress(&jet4beta2_01_);}
	}
	jet1beta1_05_branch = 0;
	if (tree->GetBranch("jet1beta1_05") != 0) {
		jet1beta1_05_branch = tree->GetBranch("jet1beta1_05");
		if (jet1beta1_05_branch) {jet1beta1_05_branch->SetAddress(&jet1beta1_05_);}
	}
	jet2beta1_05_branch = 0;
	if (tree->GetBranch("jet2beta1_05") != 0) {
		jet2beta1_05_branch = tree->GetBranch("jet2beta1_05");
		if (jet2beta1_05_branch) {jet2beta1_05_branch->SetAddress(&jet2beta1_05_);}
	}
	jet3beta1_05_branch = 0;
	if (tree->GetBranch("jet3beta1_05") != 0) {
		jet3beta1_05_branch = tree->GetBranch("jet3beta1_05");
		if (jet3beta1_05_branch) {jet3beta1_05_branch->SetAddress(&jet3beta1_05_);}
	}
	jet4beta1_05_branch = 0;
	if (tree->GetBranch("jet4beta1_05") != 0) {
		jet4beta1_05_branch = tree->GetBranch("jet4beta1_05");
		if (jet4beta1_05_branch) {jet4beta1_05_branch->SetAddress(&jet4beta1_05_);}
	}
	jet1beta2_05_branch = 0;
	if (tree->GetBranch("jet1beta2_05") != 0) {
		jet1beta2_05_branch = tree->GetBranch("jet1beta2_05");
		if (jet1beta2_05_branch) {jet1beta2_05_branch->SetAddress(&jet1beta2_05_);}
	}
	jet2beta2_05_branch = 0;
	if (tree->GetBranch("jet2beta2_05") != 0) {
		jet2beta2_05_branch = tree->GetBranch("jet2beta2_05");
		if (jet2beta2_05_branch) {jet2beta2_05_branch->SetAddress(&jet2beta2_05_);}
	}
	jet3beta2_05_branch = 0;
	if (tree->GetBranch("jet3beta2_05") != 0) {
		jet3beta2_05_branch = tree->GetBranch("jet3beta2_05");
		if (jet3beta2_05_branch) {jet3beta2_05_branch->SetAddress(&jet3beta2_05_);}
	}
	jet4beta2_05_branch = 0;
	if (tree->GetBranch("jet4beta2_05") != 0) {
		jet4beta2_05_branch = tree->GetBranch("jet4beta2_05");
		if (jet4beta2_05_branch) {jet4beta2_05_branch->SetAddress(&jet4beta2_05_);}
	}
	jet1beta1_10_branch = 0;
	if (tree->GetBranch("jet1beta1_10") != 0) {
		jet1beta1_10_branch = tree->GetBranch("jet1beta1_10");
		if (jet1beta1_10_branch) {jet1beta1_10_branch->SetAddress(&jet1beta1_10_);}
	}
	jet2beta1_10_branch = 0;
	if (tree->GetBranch("jet2beta1_10") != 0) {
		jet2beta1_10_branch = tree->GetBranch("jet2beta1_10");
		if (jet2beta1_10_branch) {jet2beta1_10_branch->SetAddress(&jet2beta1_10_);}
	}
	jet3beta1_10_branch = 0;
	if (tree->GetBranch("jet3beta1_10") != 0) {
		jet3beta1_10_branch = tree->GetBranch("jet3beta1_10");
		if (jet3beta1_10_branch) {jet3beta1_10_branch->SetAddress(&jet3beta1_10_);}
	}
	jet4beta1_10_branch = 0;
	if (tree->GetBranch("jet4beta1_10") != 0) {
		jet4beta1_10_branch = tree->GetBranch("jet4beta1_10");
		if (jet4beta1_10_branch) {jet4beta1_10_branch->SetAddress(&jet4beta1_10_);}
	}
	jet1beta2_10_branch = 0;
	if (tree->GetBranch("jet1beta2_10") != 0) {
		jet1beta2_10_branch = tree->GetBranch("jet1beta2_10");
		if (jet1beta2_10_branch) {jet1beta2_10_branch->SetAddress(&jet1beta2_10_);}
	}
	jet2beta2_10_branch = 0;
	if (tree->GetBranch("jet2beta2_10") != 0) {
		jet2beta2_10_branch = tree->GetBranch("jet2beta2_10");
		if (jet2beta2_10_branch) {jet2beta2_10_branch->SetAddress(&jet2beta2_10_);}
	}
	jet3beta2_10_branch = 0;
	if (tree->GetBranch("jet3beta2_10") != 0) {
		jet3beta2_10_branch = tree->GetBranch("jet3beta2_10");
		if (jet3beta2_10_branch) {jet3beta2_10_branch->SetAddress(&jet3beta2_10_);}
	}
	jet4beta2_10_branch = 0;
	if (tree->GetBranch("jet4beta2_10") != 0) {
		jet4beta2_10_branch = tree->GetBranch("jet4beta2_10");
		if (jet4beta2_10_branch) {jet4beta2_10_branch->SetAddress(&jet4beta2_10_);}
	}
	csc_branch = 0;
	if (tree->GetBranch("csc") != 0) {
		csc_branch = tree->GetBranch("csc");
		if (csc_branch) {csc_branch->SetAddress(&csc_);}
	}
	hbhe_branch = 0;
	if (tree->GetBranch("hbhe") != 0) {
		hbhe_branch = tree->GetBranch("hbhe");
		if (hbhe_branch) {hbhe_branch->SetAddress(&hbhe_);}
	}
	hbhenew_branch = 0;
	if (tree->GetBranch("hbhenew") != 0) {
		hbhenew_branch = tree->GetBranch("hbhenew");
		if (hbhenew_branch) {hbhenew_branch->SetAddress(&hbhenew_);}
	}
	hcallaser_branch = 0;
	if (tree->GetBranch("hcallaser") != 0) {
		hcallaser_branch = tree->GetBranch("hcallaser");
		if (hcallaser_branch) {hcallaser_branch->SetAddress(&hcallaser_);}
	}
	ecallaser_branch = 0;
	if (tree->GetBranch("ecallaser") != 0) {
		ecallaser_branch = tree->GetBranch("ecallaser");
		if (ecallaser_branch) {ecallaser_branch->SetAddress(&ecallaser_);}
	}
	ecaltp_branch = 0;
	if (tree->GetBranch("ecaltp") != 0) {
		ecaltp_branch = tree->GetBranch("ecaltp");
		if (ecaltp_branch) {ecaltp_branch->SetAddress(&ecaltp_);}
	}
	trkfail_branch = 0;
	if (tree->GetBranch("trkfail") != 0) {
		trkfail_branch = tree->GetBranch("trkfail");
		if (trkfail_branch) {trkfail_branch->SetAddress(&trkfail_);}
	}
	eebadsc_branch = 0;
	if (tree->GetBranch("eebadsc") != 0) {
		eebadsc_branch = tree->GetBranch("eebadsc");
		if (eebadsc_branch) {eebadsc_branch->SetAddress(&eebadsc_);}
	}
	mjj_branch = 0;
	if (tree->GetBranch("mjj") != 0) {
		mjj_branch = tree->GetBranch("mjj");
		if (mjj_branch) {mjj_branch->SetAddress(&mjj_);}
	}
	npujets_branch = 0;
	if (tree->GetBranch("npujets") != 0) {
		npujets_branch = tree->GetBranch("npujets");
		if (npujets_branch) {npujets_branch->SetAddress(&npujets_);}
	}
  tree->SetMakeClass(0);
}
void GetEntry(unsigned int idx) 
	// this only marks branches as not loaded, saving a lot of time
	{
		index = idx;
		run_isLoaded = false;
		lumi_isLoaded = false;
		event_isLoaded = false;
		nvtx_isLoaded = false;
		weight_isLoaded = false;
		pthat_isLoaded = false;
		failjetid_isLoaded = false;
		maxemf_isLoaded = false;
		maxleppt_isLoaded = false;
		elveto_isLoaded = false;
		ht30_isLoaded = false;
		ht40_isLoaded = false;
		jzb_isLoaded = false;
		pfmet_isLoaded = false;
		pfmett1_isLoaded = false;
		pfmett1new_isLoaded = false;
		pfmet_type1_pt30_isLoaded = false;
		pfmet_type1_pt15_isLoaded = false;
		pfmetphi_isLoaded = false;
		pfmett1phi_isLoaded = false;
		pfmett1newphi_isLoaded = false;
		pfsumet_isLoaded = false;
		met_isLoaded = false;
		metphi_isLoaded = false;
		sumet_isLoaded = false;
		mumet_isLoaded = false;
		mumetphi_isLoaded = false;
		musumet_isLoaded = false;
		mujesmet_isLoaded = false;
		mujesmetphi_isLoaded = false;
		mujessumet_isLoaded = false;
		genmet_isLoaded = false;
		genmetphi_isLoaded = false;
		gensumet_isLoaded = false;
		dphixmet_isLoaded = false;
		metpar_isLoaded = false;
		metperp_isLoaded = false;
		tcmet_isLoaded = false;
		tcmetphi_isLoaded = false;
		tcsumet_isLoaded = false;
		tcmetNew_isLoaded = false;
		tcmetNew_type1_pt30_isLoaded = false;
		tcmetNew_type1_pt15_isLoaded = false;
		tcmetphiNew_isLoaded = false;
		tcsumetNew_isLoaded = false;
		njets_isLoaded = false;
		njets10_isLoaded = false;
		njets15_isLoaded = false;
		njets20_isLoaded = false;
		njets40_isLoaded = false;
		ht_isLoaded = false;
		ht10_isLoaded = false;
		vecjetpt_isLoaded = false;
		nbl_isLoaded = false;
		nbm_isLoaded = false;
		nbt_isLoaded = false;
		ndphijetmet_isLoaded = false;
		maxjetpt_isLoaded = false;
		maxjetdphimet_isLoaded = false;
		hlt20_isLoaded = false;
		hlt30_isLoaded = false;
		hlt50_isLoaded = false;
		hlt75_isLoaded = false;
		hlt90_isLoaded = false;
		hlt135_isLoaded = false;
		hlt150_isLoaded = false;
		hlt160_isLoaded = false;
		hgg22_isLoaded = false;
		hgg36_isLoaded = false;
		hgg50_isLoaded = false;
		hgg75_isLoaded = false;
		hgg90_isLoaded = false;
		rho_isLoaded = false;
		vtxidx_isLoaded = false;
		ng_isLoaded = false;
		etg_isLoaded = false;
		etag_isLoaded = false;
		phig_isLoaded = false;
		hoe_isLoaded = false;
		eciso_isLoaded = false;
		hciso_isLoaded = false;
		tkiso_isLoaded = false;
		swiss_isLoaded = false;
		seed_isLoaded = false;
		s4_isLoaded = false;
		r4_isLoaded = false;
		photon_scidx_isLoaded = false;
		photon_pixelseed_isLoaded = false;
		photon_e15_isLoaded = false;
		photon_e25max_isLoaded = false;
		photon_e33_isLoaded = false;
		photon_e55_isLoaded = false;
		photon_ecalIso03_isLoaded = false;
		photon_ecalIso04_isLoaded = false;
		photon_hcalIso03_isLoaded = false;
		photon_hcalIso04_isLoaded = false;
		photon_ntkIsoHollow03_isLoaded = false;
		photon_ntkIsoHollow04_isLoaded = false;
		photon_ntkIsoSolid03_isLoaded = false;
		photon_ntkIsoSolid04_isLoaded = false;
		photon_sigmaEtaEta_isLoaded = false;
		photon_sigmaIEtaIEta_isLoaded = false;
		photon_sigmaIPhiIPhi_isLoaded = false;
		photon_tkisoHollow03_isLoaded = false;
		photon_tkisoHollow04_isLoaded = false;
		photon_tkisoSolid03_isLoaded = false;
		photon_tkisoSolid04_isLoaded = false;
		jetdr_isLoaded = false;
		jetpt_isLoaded = false;
		calojetpt_isLoaded = false;
		pfjetid_isLoaded = false;
		jeteta_isLoaded = false;
		jetenergy_isLoaded = false;
		jetchargedemfrac_isLoaded = false;
		jetchargedhadfrac_isLoaded = false;
		jetneutralemfrac_isLoaded = false;
		jetneutralhadfrac_isLoaded = false;
		jetncharged_isLoaded = false;
		jetnmuon_isLoaded = false;
		jetnneutral_isLoaded = false;
		jetdphimet_isLoaded = false;
		jetdpt_isLoaded = false;
		jet1_isLoaded = false;
		jet2_isLoaded = false;
		jet3_isLoaded = false;
		jet4_isLoaded = false;
		jet1flav_isLoaded = false;
		jet2flav_isLoaded = false;
		jet3flav_isLoaded = false;
		jet4flav_isLoaded = false;
		jet1mcfa_isLoaded = false;
		jet2mcfa_isLoaded = false;
		jet3mcfa_isLoaded = false;
		jet4mcfa_isLoaded = false;
		jet1mcfp_isLoaded = false;
		jet2mcfp_isLoaded = false;
		jet3mcfp_isLoaded = false;
		jet4mcfp_isLoaded = false;
		csv1_isLoaded = false;
		csv2_isLoaded = false;
		csv3_isLoaded = false;
		csv4_isLoaded = false;
		jet1drgen_isLoaded = false;
		jet2drgen_isLoaded = false;
		jet3drgen_isLoaded = false;
		jet4drgen_isLoaded = false;
		jet1beta1_01_isLoaded = false;
		jet2beta1_01_isLoaded = false;
		jet3beta1_01_isLoaded = false;
		jet4beta1_01_isLoaded = false;
		jet1beta2_01_isLoaded = false;
		jet2beta2_01_isLoaded = false;
		jet3beta2_01_isLoaded = false;
		jet4beta2_01_isLoaded = false;
		jet1beta1_05_isLoaded = false;
		jet2beta1_05_isLoaded = false;
		jet3beta1_05_isLoaded = false;
		jet4beta1_05_isLoaded = false;
		jet1beta2_05_isLoaded = false;
		jet2beta2_05_isLoaded = false;
		jet3beta2_05_isLoaded = false;
		jet4beta2_05_isLoaded = false;
		jet1beta1_10_isLoaded = false;
		jet2beta1_10_isLoaded = false;
		jet3beta1_10_isLoaded = false;
		jet4beta1_10_isLoaded = false;
		jet1beta2_10_isLoaded = false;
		jet2beta2_10_isLoaded = false;
		jet3beta2_10_isLoaded = false;
		jet4beta2_10_isLoaded = false;
		csc_isLoaded = false;
		hbhe_isLoaded = false;
		hbhenew_isLoaded = false;
		hcallaser_isLoaded = false;
		ecallaser_isLoaded = false;
		ecaltp_isLoaded = false;
		trkfail_isLoaded = false;
		eebadsc_isLoaded = false;
		mjj_isLoaded = false;
		pujets_isLoaded = false;
		npujets_isLoaded = false;
	}

void LoadAllBranches() 
	// load all branches
{
	if (run_branch != 0) run();
	if (lumi_branch != 0) lumi();
	if (event_branch != 0) event();
	if (nvtx_branch != 0) nvtx();
	if (weight_branch != 0) weight();
	if (pthat_branch != 0) pthat();
	if (failjetid_branch != 0) failjetid();
	if (maxemf_branch != 0) maxemf();
	if (maxleppt_branch != 0) maxleppt();
	if (elveto_branch != 0) elveto();
	if (ht30_branch != 0) ht30();
	if (ht40_branch != 0) ht40();
	if (jzb_branch != 0) jzb();
	if (pfmet_branch != 0) pfmet();
	if (pfmett1_branch != 0) pfmett1();
	if (pfmett1new_branch != 0) pfmett1new();
	if (pfmet_type1_pt30_branch != 0) pfmet_type1_pt30();
	if (pfmet_type1_pt15_branch != 0) pfmet_type1_pt15();
	if (pfmetphi_branch != 0) pfmetphi();
	if (pfmett1phi_branch != 0) pfmett1phi();
	if (pfmett1newphi_branch != 0) pfmett1newphi();
	if (pfsumet_branch != 0) pfsumet();
	if (met_branch != 0) met();
	if (metphi_branch != 0) metphi();
	if (sumet_branch != 0) sumet();
	if (mumet_branch != 0) mumet();
	if (mumetphi_branch != 0) mumetphi();
	if (musumet_branch != 0) musumet();
	if (mujesmet_branch != 0) mujesmet();
	if (mujesmetphi_branch != 0) mujesmetphi();
	if (mujessumet_branch != 0) mujessumet();
	if (genmet_branch != 0) genmet();
	if (genmetphi_branch != 0) genmetphi();
	if (gensumet_branch != 0) gensumet();
	if (dphixmet_branch != 0) dphixmet();
	if (metpar_branch != 0) metpar();
	if (metperp_branch != 0) metperp();
	if (tcmet_branch != 0) tcmet();
	if (tcmetphi_branch != 0) tcmetphi();
	if (tcsumet_branch != 0) tcsumet();
	if (tcmetNew_branch != 0) tcmetNew();
	if (tcmetNew_type1_pt30_branch != 0) tcmetNew_type1_pt30();
	if (tcmetNew_type1_pt15_branch != 0) tcmetNew_type1_pt15();
	if (tcmetphiNew_branch != 0) tcmetphiNew();
	if (tcsumetNew_branch != 0) tcsumetNew();
	if (njets_branch != 0) njets();
	if (njets10_branch != 0) njets10();
	if (njets15_branch != 0) njets15();
	if (njets20_branch != 0) njets20();
	if (njets40_branch != 0) njets40();
	if (ht_branch != 0) ht();
	if (ht10_branch != 0) ht10();
	if (vecjetpt_branch != 0) vecjetpt();
	if (nbl_branch != 0) nbl();
	if (nbm_branch != 0) nbm();
	if (nbt_branch != 0) nbt();
	if (ndphijetmet_branch != 0) ndphijetmet();
	if (maxjetpt_branch != 0) maxjetpt();
	if (maxjetdphimet_branch != 0) maxjetdphimet();
	if (hlt20_branch != 0) hlt20();
	if (hlt30_branch != 0) hlt30();
	if (hlt50_branch != 0) hlt50();
	if (hlt75_branch != 0) hlt75();
	if (hlt90_branch != 0) hlt90();
	if (hlt135_branch != 0) hlt135();
	if (hlt150_branch != 0) hlt150();
	if (hlt160_branch != 0) hlt160();
	if (hgg22_branch != 0) hgg22();
	if (hgg36_branch != 0) hgg36();
	if (hgg50_branch != 0) hgg50();
	if (hgg75_branch != 0) hgg75();
	if (hgg90_branch != 0) hgg90();
	if (rho_branch != 0) rho();
	if (vtxidx_branch != 0) vtxidx();
	if (ng_branch != 0) ng();
	if (etg_branch != 0) etg();
	if (etag_branch != 0) etag();
	if (phig_branch != 0) phig();
	if (hoe_branch != 0) hoe();
	if (eciso_branch != 0) eciso();
	if (hciso_branch != 0) hciso();
	if (tkiso_branch != 0) tkiso();
	if (swiss_branch != 0) swiss();
	if (seed_branch != 0) seed();
	if (s4_branch != 0) s4();
	if (r4_branch != 0) r4();
	if (photon_scidx_branch != 0) photon_scidx();
	if (photon_pixelseed_branch != 0) photon_pixelseed();
	if (photon_e15_branch != 0) photon_e15();
	if (photon_e25max_branch != 0) photon_e25max();
	if (photon_e33_branch != 0) photon_e33();
	if (photon_e55_branch != 0) photon_e55();
	if (photon_ecalIso03_branch != 0) photon_ecalIso03();
	if (photon_ecalIso04_branch != 0) photon_ecalIso04();
	if (photon_hcalIso03_branch != 0) photon_hcalIso03();
	if (photon_hcalIso04_branch != 0) photon_hcalIso04();
	if (photon_ntkIsoHollow03_branch != 0) photon_ntkIsoHollow03();
	if (photon_ntkIsoHollow04_branch != 0) photon_ntkIsoHollow04();
	if (photon_ntkIsoSolid03_branch != 0) photon_ntkIsoSolid03();
	if (photon_ntkIsoSolid04_branch != 0) photon_ntkIsoSolid04();
	if (photon_sigmaEtaEta_branch != 0) photon_sigmaEtaEta();
	if (photon_sigmaIEtaIEta_branch != 0) photon_sigmaIEtaIEta();
	if (photon_sigmaIPhiIPhi_branch != 0) photon_sigmaIPhiIPhi();
	if (photon_tkisoHollow03_branch != 0) photon_tkisoHollow03();
	if (photon_tkisoHollow04_branch != 0) photon_tkisoHollow04();
	if (photon_tkisoSolid03_branch != 0) photon_tkisoSolid03();
	if (photon_tkisoSolid04_branch != 0) photon_tkisoSolid04();
	if (jetdr_branch != 0) jetdr();
	if (jetpt_branch != 0) jetpt();
	if (calojetpt_branch != 0) calojetpt();
	if (pfjetid_branch != 0) pfjetid();
	if (jeteta_branch != 0) jeteta();
	if (jetenergy_branch != 0) jetenergy();
	if (jetchargedemfrac_branch != 0) jetchargedemfrac();
	if (jetchargedhadfrac_branch != 0) jetchargedhadfrac();
	if (jetneutralemfrac_branch != 0) jetneutralemfrac();
	if (jetneutralhadfrac_branch != 0) jetneutralhadfrac();
	if (jetncharged_branch != 0) jetncharged();
	if (jetnmuon_branch != 0) jetnmuon();
	if (jetnneutral_branch != 0) jetnneutral();
	if (jetdphimet_branch != 0) jetdphimet();
	if (jetdpt_branch != 0) jetdpt();
	if (jet1_branch != 0) jet1();
	if (jet2_branch != 0) jet2();
	if (jet3_branch != 0) jet3();
	if (jet4_branch != 0) jet4();
	if (jet1flav_branch != 0) jet1flav();
	if (jet2flav_branch != 0) jet2flav();
	if (jet3flav_branch != 0) jet3flav();
	if (jet4flav_branch != 0) jet4flav();
	if (jet1mcfa_branch != 0) jet1mcfa();
	if (jet2mcfa_branch != 0) jet2mcfa();
	if (jet3mcfa_branch != 0) jet3mcfa();
	if (jet4mcfa_branch != 0) jet4mcfa();
	if (jet1mcfp_branch != 0) jet1mcfp();
	if (jet2mcfp_branch != 0) jet2mcfp();
	if (jet3mcfp_branch != 0) jet3mcfp();
	if (jet4mcfp_branch != 0) jet4mcfp();
	if (csv1_branch != 0) csv1();
	if (csv2_branch != 0) csv2();
	if (csv3_branch != 0) csv3();
	if (csv4_branch != 0) csv4();
	if (jet1drgen_branch != 0) jet1drgen();
	if (jet2drgen_branch != 0) jet2drgen();
	if (jet3drgen_branch != 0) jet3drgen();
	if (jet4drgen_branch != 0) jet4drgen();
	if (jet1beta1_01_branch != 0) jet1beta1_01();
	if (jet2beta1_01_branch != 0) jet2beta1_01();
	if (jet3beta1_01_branch != 0) jet3beta1_01();
	if (jet4beta1_01_branch != 0) jet4beta1_01();
	if (jet1beta2_01_branch != 0) jet1beta2_01();
	if (jet2beta2_01_branch != 0) jet2beta2_01();
	if (jet3beta2_01_branch != 0) jet3beta2_01();
	if (jet4beta2_01_branch != 0) jet4beta2_01();
	if (jet1beta1_05_branch != 0) jet1beta1_05();
	if (jet2beta1_05_branch != 0) jet2beta1_05();
	if (jet3beta1_05_branch != 0) jet3beta1_05();
	if (jet4beta1_05_branch != 0) jet4beta1_05();
	if (jet1beta2_05_branch != 0) jet1beta2_05();
	if (jet2beta2_05_branch != 0) jet2beta2_05();
	if (jet3beta2_05_branch != 0) jet3beta2_05();
	if (jet4beta2_05_branch != 0) jet4beta2_05();
	if (jet1beta1_10_branch != 0) jet1beta1_10();
	if (jet2beta1_10_branch != 0) jet2beta1_10();
	if (jet3beta1_10_branch != 0) jet3beta1_10();
	if (jet4beta1_10_branch != 0) jet4beta1_10();
	if (jet1beta2_10_branch != 0) jet1beta2_10();
	if (jet2beta2_10_branch != 0) jet2beta2_10();
	if (jet3beta2_10_branch != 0) jet3beta2_10();
	if (jet4beta2_10_branch != 0) jet4beta2_10();
	if (csc_branch != 0) csc();
	if (hbhe_branch != 0) hbhe();
	if (hbhenew_branch != 0) hbhenew();
	if (hcallaser_branch != 0) hcallaser();
	if (ecallaser_branch != 0) ecallaser();
	if (ecaltp_branch != 0) ecaltp();
	if (trkfail_branch != 0) trkfail();
	if (eebadsc_branch != 0) eebadsc();
	if (mjj_branch != 0) mjj();
	if (pujets_branch != 0) pujets();
	if (npujets_branch != 0) npujets();
}

	int &run()
	{
		if (not run_isLoaded) {
			if (run_branch != 0) {
				run_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch run_branch does not exist!\n");
				exit(1);
			}
			run_isLoaded = true;
		}
		return run_;
	}
	int &lumi()
	{
		if (not lumi_isLoaded) {
			if (lumi_branch != 0) {
				lumi_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch lumi_branch does not exist!\n");
				exit(1);
			}
			lumi_isLoaded = true;
		}
		return lumi_;
	}
	int &event()
	{
		if (not event_isLoaded) {
			if (event_branch != 0) {
				event_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch event_branch does not exist!\n");
				exit(1);
			}
			event_isLoaded = true;
		}
		return event_;
	}
	int &nvtx()
	{
		if (not nvtx_isLoaded) {
			if (nvtx_branch != 0) {
				nvtx_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch nvtx_branch does not exist!\n");
				exit(1);
			}
			nvtx_isLoaded = true;
		}
		return nvtx_;
	}
	float &weight()
	{
		if (not weight_isLoaded) {
			if (weight_branch != 0) {
				weight_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch weight_branch does not exist!\n");
				exit(1);
			}
			weight_isLoaded = true;
		}
		return weight_;
	}
	float &pthat()
	{
		if (not pthat_isLoaded) {
			if (pthat_branch != 0) {
				pthat_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pthat_branch does not exist!\n");
				exit(1);
			}
			pthat_isLoaded = true;
		}
		return pthat_;
	}
	int &failjetid()
	{
		if (not failjetid_isLoaded) {
			if (failjetid_branch != 0) {
				failjetid_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch failjetid_branch does not exist!\n");
				exit(1);
			}
			failjetid_isLoaded = true;
		}
		return failjetid_;
	}
	float &maxemf()
	{
		if (not maxemf_isLoaded) {
			if (maxemf_branch != 0) {
				maxemf_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch maxemf_branch does not exist!\n");
				exit(1);
			}
			maxemf_isLoaded = true;
		}
		return maxemf_;
	}
	float &maxleppt()
	{
		if (not maxleppt_isLoaded) {
			if (maxleppt_branch != 0) {
				maxleppt_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch maxleppt_branch does not exist!\n");
				exit(1);
			}
			maxleppt_isLoaded = true;
		}
		return maxleppt_;
	}
	int &elveto()
	{
		if (not elveto_isLoaded) {
			if (elveto_branch != 0) {
				elveto_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch elveto_branch does not exist!\n");
				exit(1);
			}
			elveto_isLoaded = true;
		}
		return elveto_;
	}
	float &ht30()
	{
		if (not ht30_isLoaded) {
			if (ht30_branch != 0) {
				ht30_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ht30_branch does not exist!\n");
				exit(1);
			}
			ht30_isLoaded = true;
		}
		return ht30_;
	}
	float &ht40()
	{
		if (not ht40_isLoaded) {
			if (ht40_branch != 0) {
				ht40_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ht40_branch does not exist!\n");
				exit(1);
			}
			ht40_isLoaded = true;
		}
		return ht40_;
	}
	float &jzb()
	{
		if (not jzb_isLoaded) {
			if (jzb_branch != 0) {
				jzb_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jzb_branch does not exist!\n");
				exit(1);
			}
			jzb_isLoaded = true;
		}
		return jzb_;
	}
	float &pfmet()
	{
		if (not pfmet_isLoaded) {
			if (pfmet_branch != 0) {
				pfmet_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pfmet_branch does not exist!\n");
				exit(1);
			}
			pfmet_isLoaded = true;
		}
		return pfmet_;
	}
	float &pfmett1()
	{
		if (not pfmett1_isLoaded) {
			if (pfmett1_branch != 0) {
				pfmett1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pfmett1_branch does not exist!\n");
				exit(1);
			}
			pfmett1_isLoaded = true;
		}
		return pfmett1_;
	}
	float &pfmett1new()
	{
		if (not pfmett1new_isLoaded) {
			if (pfmett1new_branch != 0) {
				pfmett1new_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pfmett1new_branch does not exist!\n");
				exit(1);
			}
			pfmett1new_isLoaded = true;
		}
		return pfmett1new_;
	}
	float &pfmet_type1_pt30()
	{
		if (not pfmet_type1_pt30_isLoaded) {
			if (pfmet_type1_pt30_branch != 0) {
				pfmet_type1_pt30_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pfmet_type1_pt30_branch does not exist!\n");
				exit(1);
			}
			pfmet_type1_pt30_isLoaded = true;
		}
		return pfmet_type1_pt30_;
	}
	float &pfmet_type1_pt15()
	{
		if (not pfmet_type1_pt15_isLoaded) {
			if (pfmet_type1_pt15_branch != 0) {
				pfmet_type1_pt15_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pfmet_type1_pt15_branch does not exist!\n");
				exit(1);
			}
			pfmet_type1_pt15_isLoaded = true;
		}
		return pfmet_type1_pt15_;
	}
	float &pfmetphi()
	{
		if (not pfmetphi_isLoaded) {
			if (pfmetphi_branch != 0) {
				pfmetphi_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pfmetphi_branch does not exist!\n");
				exit(1);
			}
			pfmetphi_isLoaded = true;
		}
		return pfmetphi_;
	}
	float &pfmett1phi()
	{
		if (not pfmett1phi_isLoaded) {
			if (pfmett1phi_branch != 0) {
				pfmett1phi_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pfmett1phi_branch does not exist!\n");
				exit(1);
			}
			pfmett1phi_isLoaded = true;
		}
		return pfmett1phi_;
	}
	float &pfmett1newphi()
	{
		if (not pfmett1newphi_isLoaded) {
			if (pfmett1newphi_branch != 0) {
				pfmett1newphi_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pfmett1newphi_branch does not exist!\n");
				exit(1);
			}
			pfmett1newphi_isLoaded = true;
		}
		return pfmett1newphi_;
	}
	float &pfsumet()
	{
		if (not pfsumet_isLoaded) {
			if (pfsumet_branch != 0) {
				pfsumet_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pfsumet_branch does not exist!\n");
				exit(1);
			}
			pfsumet_isLoaded = true;
		}
		return pfsumet_;
	}
	float &met()
	{
		if (not met_isLoaded) {
			if (met_branch != 0) {
				met_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch met_branch does not exist!\n");
				exit(1);
			}
			met_isLoaded = true;
		}
		return met_;
	}
	float &metphi()
	{
		if (not metphi_isLoaded) {
			if (metphi_branch != 0) {
				metphi_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch metphi_branch does not exist!\n");
				exit(1);
			}
			metphi_isLoaded = true;
		}
		return metphi_;
	}
	float &sumet()
	{
		if (not sumet_isLoaded) {
			if (sumet_branch != 0) {
				sumet_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch sumet_branch does not exist!\n");
				exit(1);
			}
			sumet_isLoaded = true;
		}
		return sumet_;
	}
	float &mumet()
	{
		if (not mumet_isLoaded) {
			if (mumet_branch != 0) {
				mumet_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mumet_branch does not exist!\n");
				exit(1);
			}
			mumet_isLoaded = true;
		}
		return mumet_;
	}
	float &mumetphi()
	{
		if (not mumetphi_isLoaded) {
			if (mumetphi_branch != 0) {
				mumetphi_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mumetphi_branch does not exist!\n");
				exit(1);
			}
			mumetphi_isLoaded = true;
		}
		return mumetphi_;
	}
	float &musumet()
	{
		if (not musumet_isLoaded) {
			if (musumet_branch != 0) {
				musumet_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch musumet_branch does not exist!\n");
				exit(1);
			}
			musumet_isLoaded = true;
		}
		return musumet_;
	}
	float &mujesmet()
	{
		if (not mujesmet_isLoaded) {
			if (mujesmet_branch != 0) {
				mujesmet_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mujesmet_branch does not exist!\n");
				exit(1);
			}
			mujesmet_isLoaded = true;
		}
		return mujesmet_;
	}
	float &mujesmetphi()
	{
		if (not mujesmetphi_isLoaded) {
			if (mujesmetphi_branch != 0) {
				mujesmetphi_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mujesmetphi_branch does not exist!\n");
				exit(1);
			}
			mujesmetphi_isLoaded = true;
		}
		return mujesmetphi_;
	}
	float &mujessumet()
	{
		if (not mujessumet_isLoaded) {
			if (mujessumet_branch != 0) {
				mujessumet_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mujessumet_branch does not exist!\n");
				exit(1);
			}
			mujessumet_isLoaded = true;
		}
		return mujessumet_;
	}
	float &genmet()
	{
		if (not genmet_isLoaded) {
			if (genmet_branch != 0) {
				genmet_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch genmet_branch does not exist!\n");
				exit(1);
			}
			genmet_isLoaded = true;
		}
		return genmet_;
	}
	float &genmetphi()
	{
		if (not genmetphi_isLoaded) {
			if (genmetphi_branch != 0) {
				genmetphi_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch genmetphi_branch does not exist!\n");
				exit(1);
			}
			genmetphi_isLoaded = true;
		}
		return genmetphi_;
	}
	float &gensumet()
	{
		if (not gensumet_isLoaded) {
			if (gensumet_branch != 0) {
				gensumet_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch gensumet_branch does not exist!\n");
				exit(1);
			}
			gensumet_isLoaded = true;
		}
		return gensumet_;
	}
	float &dphixmet()
	{
		if (not dphixmet_isLoaded) {
			if (dphixmet_branch != 0) {
				dphixmet_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dphixmet_branch does not exist!\n");
				exit(1);
			}
			dphixmet_isLoaded = true;
		}
		return dphixmet_;
	}
	float &metpar()
	{
		if (not metpar_isLoaded) {
			if (metpar_branch != 0) {
				metpar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch metpar_branch does not exist!\n");
				exit(1);
			}
			metpar_isLoaded = true;
		}
		return metpar_;
	}
	float &metperp()
	{
		if (not metperp_isLoaded) {
			if (metperp_branch != 0) {
				metperp_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch metperp_branch does not exist!\n");
				exit(1);
			}
			metperp_isLoaded = true;
		}
		return metperp_;
	}
	float &tcmet()
	{
		if (not tcmet_isLoaded) {
			if (tcmet_branch != 0) {
				tcmet_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch tcmet_branch does not exist!\n");
				exit(1);
			}
			tcmet_isLoaded = true;
		}
		return tcmet_;
	}
	float &tcmetphi()
	{
		if (not tcmetphi_isLoaded) {
			if (tcmetphi_branch != 0) {
				tcmetphi_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch tcmetphi_branch does not exist!\n");
				exit(1);
			}
			tcmetphi_isLoaded = true;
		}
		return tcmetphi_;
	}
	float &tcsumet()
	{
		if (not tcsumet_isLoaded) {
			if (tcsumet_branch != 0) {
				tcsumet_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch tcsumet_branch does not exist!\n");
				exit(1);
			}
			tcsumet_isLoaded = true;
		}
		return tcsumet_;
	}
	float &tcmetNew()
	{
		if (not tcmetNew_isLoaded) {
			if (tcmetNew_branch != 0) {
				tcmetNew_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch tcmetNew_branch does not exist!\n");
				exit(1);
			}
			tcmetNew_isLoaded = true;
		}
		return tcmetNew_;
	}
	float &tcmetNew_type1_pt30()
	{
		if (not tcmetNew_type1_pt30_isLoaded) {
			if (tcmetNew_type1_pt30_branch != 0) {
				tcmetNew_type1_pt30_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch tcmetNew_type1_pt30_branch does not exist!\n");
				exit(1);
			}
			tcmetNew_type1_pt30_isLoaded = true;
		}
		return tcmetNew_type1_pt30_;
	}
	float &tcmetNew_type1_pt15()
	{
		if (not tcmetNew_type1_pt15_isLoaded) {
			if (tcmetNew_type1_pt15_branch != 0) {
				tcmetNew_type1_pt15_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch tcmetNew_type1_pt15_branch does not exist!\n");
				exit(1);
			}
			tcmetNew_type1_pt15_isLoaded = true;
		}
		return tcmetNew_type1_pt15_;
	}
	float &tcmetphiNew()
	{
		if (not tcmetphiNew_isLoaded) {
			if (tcmetphiNew_branch != 0) {
				tcmetphiNew_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch tcmetphiNew_branch does not exist!\n");
				exit(1);
			}
			tcmetphiNew_isLoaded = true;
		}
		return tcmetphiNew_;
	}
	float &tcsumetNew()
	{
		if (not tcsumetNew_isLoaded) {
			if (tcsumetNew_branch != 0) {
				tcsumetNew_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch tcsumetNew_branch does not exist!\n");
				exit(1);
			}
			tcsumetNew_isLoaded = true;
		}
		return tcsumetNew_;
	}
	int &njets()
	{
		if (not njets_isLoaded) {
			if (njets_branch != 0) {
				njets_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch njets_branch does not exist!\n");
				exit(1);
			}
			njets_isLoaded = true;
		}
		return njets_;
	}
	int &njets10()
	{
		if (not njets10_isLoaded) {
			if (njets10_branch != 0) {
				njets10_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch njets10_branch does not exist!\n");
				exit(1);
			}
			njets10_isLoaded = true;
		}
		return njets10_;
	}
	int &njets15()
	{
		if (not njets15_isLoaded) {
			if (njets15_branch != 0) {
				njets15_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch njets15_branch does not exist!\n");
				exit(1);
			}
			njets15_isLoaded = true;
		}
		return njets15_;
	}
	int &njets20()
	{
		if (not njets20_isLoaded) {
			if (njets20_branch != 0) {
				njets20_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch njets20_branch does not exist!\n");
				exit(1);
			}
			njets20_isLoaded = true;
		}
		return njets20_;
	}
	int &njets40()
	{
		if (not njets40_isLoaded) {
			if (njets40_branch != 0) {
				njets40_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch njets40_branch does not exist!\n");
				exit(1);
			}
			njets40_isLoaded = true;
		}
		return njets40_;
	}
	float &ht()
	{
		if (not ht_isLoaded) {
			if (ht_branch != 0) {
				ht_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ht_branch does not exist!\n");
				exit(1);
			}
			ht_isLoaded = true;
		}
		return ht_;
	}
	float &ht10()
	{
		if (not ht10_isLoaded) {
			if (ht10_branch != 0) {
				ht10_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ht10_branch does not exist!\n");
				exit(1);
			}
			ht10_isLoaded = true;
		}
		return ht10_;
	}
	float &vecjetpt()
	{
		if (not vecjetpt_isLoaded) {
			if (vecjetpt_branch != 0) {
				vecjetpt_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch vecjetpt_branch does not exist!\n");
				exit(1);
			}
			vecjetpt_isLoaded = true;
		}
		return vecjetpt_;
	}
	int &nbl()
	{
		if (not nbl_isLoaded) {
			if (nbl_branch != 0) {
				nbl_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch nbl_branch does not exist!\n");
				exit(1);
			}
			nbl_isLoaded = true;
		}
		return nbl_;
	}
	int &nbm()
	{
		if (not nbm_isLoaded) {
			if (nbm_branch != 0) {
				nbm_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch nbm_branch does not exist!\n");
				exit(1);
			}
			nbm_isLoaded = true;
		}
		return nbm_;
	}
	int &nbt()
	{
		if (not nbt_isLoaded) {
			if (nbt_branch != 0) {
				nbt_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch nbt_branch does not exist!\n");
				exit(1);
			}
			nbt_isLoaded = true;
		}
		return nbt_;
	}
	float &ndphijetmet()
	{
		if (not ndphijetmet_isLoaded) {
			if (ndphijetmet_branch != 0) {
				ndphijetmet_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ndphijetmet_branch does not exist!\n");
				exit(1);
			}
			ndphijetmet_isLoaded = true;
		}
		return ndphijetmet_;
	}
	float &maxjetpt()
	{
		if (not maxjetpt_isLoaded) {
			if (maxjetpt_branch != 0) {
				maxjetpt_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch maxjetpt_branch does not exist!\n");
				exit(1);
			}
			maxjetpt_isLoaded = true;
		}
		return maxjetpt_;
	}
	float &maxjetdphimet()
	{
		if (not maxjetdphimet_isLoaded) {
			if (maxjetdphimet_branch != 0) {
				maxjetdphimet_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch maxjetdphimet_branch does not exist!\n");
				exit(1);
			}
			maxjetdphimet_isLoaded = true;
		}
		return maxjetdphimet_;
	}
	int &hlt20()
	{
		if (not hlt20_isLoaded) {
			if (hlt20_branch != 0) {
				hlt20_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hlt20_branch does not exist!\n");
				exit(1);
			}
			hlt20_isLoaded = true;
		}
		return hlt20_;
	}
	int &hlt30()
	{
		if (not hlt30_isLoaded) {
			if (hlt30_branch != 0) {
				hlt30_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hlt30_branch does not exist!\n");
				exit(1);
			}
			hlt30_isLoaded = true;
		}
		return hlt30_;
	}
	int &hlt50()
	{
		if (not hlt50_isLoaded) {
			if (hlt50_branch != 0) {
				hlt50_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hlt50_branch does not exist!\n");
				exit(1);
			}
			hlt50_isLoaded = true;
		}
		return hlt50_;
	}
	int &hlt75()
	{
		if (not hlt75_isLoaded) {
			if (hlt75_branch != 0) {
				hlt75_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hlt75_branch does not exist!\n");
				exit(1);
			}
			hlt75_isLoaded = true;
		}
		return hlt75_;
	}
	int &hlt90()
	{
		if (not hlt90_isLoaded) {
			if (hlt90_branch != 0) {
				hlt90_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hlt90_branch does not exist!\n");
				exit(1);
			}
			hlt90_isLoaded = true;
		}
		return hlt90_;
	}
	int &hlt135()
	{
		if (not hlt135_isLoaded) {
			if (hlt135_branch != 0) {
				hlt135_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hlt135_branch does not exist!\n");
				exit(1);
			}
			hlt135_isLoaded = true;
		}
		return hlt135_;
	}
	int &hlt150()
	{
		if (not hlt150_isLoaded) {
			if (hlt150_branch != 0) {
				hlt150_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hlt150_branch does not exist!\n");
				exit(1);
			}
			hlt150_isLoaded = true;
		}
		return hlt150_;
	}
	int &hlt160()
	{
		if (not hlt160_isLoaded) {
			if (hlt160_branch != 0) {
				hlt160_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hlt160_branch does not exist!\n");
				exit(1);
			}
			hlt160_isLoaded = true;
		}
		return hlt160_;
	}
	int &hgg22()
	{
		if (not hgg22_isLoaded) {
			if (hgg22_branch != 0) {
				hgg22_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hgg22_branch does not exist!\n");
				exit(1);
			}
			hgg22_isLoaded = true;
		}
		return hgg22_;
	}
	int &hgg36()
	{
		if (not hgg36_isLoaded) {
			if (hgg36_branch != 0) {
				hgg36_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hgg36_branch does not exist!\n");
				exit(1);
			}
			hgg36_isLoaded = true;
		}
		return hgg36_;
	}
	int &hgg50()
	{
		if (not hgg50_isLoaded) {
			if (hgg50_branch != 0) {
				hgg50_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hgg50_branch does not exist!\n");
				exit(1);
			}
			hgg50_isLoaded = true;
		}
		return hgg50_;
	}
	int &hgg75()
	{
		if (not hgg75_isLoaded) {
			if (hgg75_branch != 0) {
				hgg75_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hgg75_branch does not exist!\n");
				exit(1);
			}
			hgg75_isLoaded = true;
		}
		return hgg75_;
	}
	int &hgg90()
	{
		if (not hgg90_isLoaded) {
			if (hgg90_branch != 0) {
				hgg90_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hgg90_branch does not exist!\n");
				exit(1);
			}
			hgg90_isLoaded = true;
		}
		return hgg90_;
	}
	float &rho()
	{
		if (not rho_isLoaded) {
			if (rho_branch != 0) {
				rho_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch rho_branch does not exist!\n");
				exit(1);
			}
			rho_isLoaded = true;
		}
		return rho_;
	}
	int &vtxidx()
	{
		if (not vtxidx_isLoaded) {
			if (vtxidx_branch != 0) {
				vtxidx_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch vtxidx_branch does not exist!\n");
				exit(1);
			}
			vtxidx_isLoaded = true;
		}
		return vtxidx_;
	}
	int &ng()
	{
		if (not ng_isLoaded) {
			if (ng_branch != 0) {
				ng_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ng_branch does not exist!\n");
				exit(1);
			}
			ng_isLoaded = true;
		}
		return ng_;
	}
	float &etg()
	{
		if (not etg_isLoaded) {
			if (etg_branch != 0) {
				etg_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch etg_branch does not exist!\n");
				exit(1);
			}
			etg_isLoaded = true;
		}
		return etg_;
	}
	float &etag()
	{
		if (not etag_isLoaded) {
			if (etag_branch != 0) {
				etag_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch etag_branch does not exist!\n");
				exit(1);
			}
			etag_isLoaded = true;
		}
		return etag_;
	}
	float &phig()
	{
		if (not phig_isLoaded) {
			if (phig_branch != 0) {
				phig_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch phig_branch does not exist!\n");
				exit(1);
			}
			phig_isLoaded = true;
		}
		return phig_;
	}
	float &hoe()
	{
		if (not hoe_isLoaded) {
			if (hoe_branch != 0) {
				hoe_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hoe_branch does not exist!\n");
				exit(1);
			}
			hoe_isLoaded = true;
		}
		return hoe_;
	}
	float &eciso()
	{
		if (not eciso_isLoaded) {
			if (eciso_branch != 0) {
				eciso_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch eciso_branch does not exist!\n");
				exit(1);
			}
			eciso_isLoaded = true;
		}
		return eciso_;
	}
	float &hciso()
	{
		if (not hciso_isLoaded) {
			if (hciso_branch != 0) {
				hciso_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hciso_branch does not exist!\n");
				exit(1);
			}
			hciso_isLoaded = true;
		}
		return hciso_;
	}
	float &tkiso()
	{
		if (not tkiso_isLoaded) {
			if (tkiso_branch != 0) {
				tkiso_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch tkiso_branch does not exist!\n");
				exit(1);
			}
			tkiso_isLoaded = true;
		}
		return tkiso_;
	}
	float &swiss()
	{
		if (not swiss_isLoaded) {
			if (swiss_branch != 0) {
				swiss_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch swiss_branch does not exist!\n");
				exit(1);
			}
			swiss_isLoaded = true;
		}
		return swiss_;
	}
	float &seed()
	{
		if (not seed_isLoaded) {
			if (seed_branch != 0) {
				seed_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch seed_branch does not exist!\n");
				exit(1);
			}
			seed_isLoaded = true;
		}
		return seed_;
	}
	float &s4()
	{
		if (not s4_isLoaded) {
			if (s4_branch != 0) {
				s4_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch s4_branch does not exist!\n");
				exit(1);
			}
			s4_isLoaded = true;
		}
		return s4_;
	}
	float &r4()
	{
		if (not r4_isLoaded) {
			if (r4_branch != 0) {
				r4_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch r4_branch does not exist!\n");
				exit(1);
			}
			r4_isLoaded = true;
		}
		return r4_;
	}
	int &photon_scidx()
	{
		if (not photon_scidx_isLoaded) {
			if (photon_scidx_branch != 0) {
				photon_scidx_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_scidx_branch does not exist!\n");
				exit(1);
			}
			photon_scidx_isLoaded = true;
		}
		return photon_scidx_;
	}
	int &photon_pixelseed()
	{
		if (not photon_pixelseed_isLoaded) {
			if (photon_pixelseed_branch != 0) {
				photon_pixelseed_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_pixelseed_branch does not exist!\n");
				exit(1);
			}
			photon_pixelseed_isLoaded = true;
		}
		return photon_pixelseed_;
	}
	float &photon_e15()
	{
		if (not photon_e15_isLoaded) {
			if (photon_e15_branch != 0) {
				photon_e15_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_e15_branch does not exist!\n");
				exit(1);
			}
			photon_e15_isLoaded = true;
		}
		return photon_e15_;
	}
	float &photon_e25max()
	{
		if (not photon_e25max_isLoaded) {
			if (photon_e25max_branch != 0) {
				photon_e25max_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_e25max_branch does not exist!\n");
				exit(1);
			}
			photon_e25max_isLoaded = true;
		}
		return photon_e25max_;
	}
	float &photon_e33()
	{
		if (not photon_e33_isLoaded) {
			if (photon_e33_branch != 0) {
				photon_e33_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_e33_branch does not exist!\n");
				exit(1);
			}
			photon_e33_isLoaded = true;
		}
		return photon_e33_;
	}
	float &photon_e55()
	{
		if (not photon_e55_isLoaded) {
			if (photon_e55_branch != 0) {
				photon_e55_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_e55_branch does not exist!\n");
				exit(1);
			}
			photon_e55_isLoaded = true;
		}
		return photon_e55_;
	}
	float &photon_ecalIso03()
	{
		if (not photon_ecalIso03_isLoaded) {
			if (photon_ecalIso03_branch != 0) {
				photon_ecalIso03_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_ecalIso03_branch does not exist!\n");
				exit(1);
			}
			photon_ecalIso03_isLoaded = true;
		}
		return photon_ecalIso03_;
	}
	float &photon_ecalIso04()
	{
		if (not photon_ecalIso04_isLoaded) {
			if (photon_ecalIso04_branch != 0) {
				photon_ecalIso04_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_ecalIso04_branch does not exist!\n");
				exit(1);
			}
			photon_ecalIso04_isLoaded = true;
		}
		return photon_ecalIso04_;
	}
	float &photon_hcalIso03()
	{
		if (not photon_hcalIso03_isLoaded) {
			if (photon_hcalIso03_branch != 0) {
				photon_hcalIso03_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_hcalIso03_branch does not exist!\n");
				exit(1);
			}
			photon_hcalIso03_isLoaded = true;
		}
		return photon_hcalIso03_;
	}
	float &photon_hcalIso04()
	{
		if (not photon_hcalIso04_isLoaded) {
			if (photon_hcalIso04_branch != 0) {
				photon_hcalIso04_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_hcalIso04_branch does not exist!\n");
				exit(1);
			}
			photon_hcalIso04_isLoaded = true;
		}
		return photon_hcalIso04_;
	}
	float &photon_ntkIsoHollow03()
	{
		if (not photon_ntkIsoHollow03_isLoaded) {
			if (photon_ntkIsoHollow03_branch != 0) {
				photon_ntkIsoHollow03_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_ntkIsoHollow03_branch does not exist!\n");
				exit(1);
			}
			photon_ntkIsoHollow03_isLoaded = true;
		}
		return photon_ntkIsoHollow03_;
	}
	float &photon_ntkIsoHollow04()
	{
		if (not photon_ntkIsoHollow04_isLoaded) {
			if (photon_ntkIsoHollow04_branch != 0) {
				photon_ntkIsoHollow04_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_ntkIsoHollow04_branch does not exist!\n");
				exit(1);
			}
			photon_ntkIsoHollow04_isLoaded = true;
		}
		return photon_ntkIsoHollow04_;
	}
	float &photon_ntkIsoSolid03()
	{
		if (not photon_ntkIsoSolid03_isLoaded) {
			if (photon_ntkIsoSolid03_branch != 0) {
				photon_ntkIsoSolid03_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_ntkIsoSolid03_branch does not exist!\n");
				exit(1);
			}
			photon_ntkIsoSolid03_isLoaded = true;
		}
		return photon_ntkIsoSolid03_;
	}
	float &photon_ntkIsoSolid04()
	{
		if (not photon_ntkIsoSolid04_isLoaded) {
			if (photon_ntkIsoSolid04_branch != 0) {
				photon_ntkIsoSolid04_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_ntkIsoSolid04_branch does not exist!\n");
				exit(1);
			}
			photon_ntkIsoSolid04_isLoaded = true;
		}
		return photon_ntkIsoSolid04_;
	}
	float &photon_sigmaEtaEta()
	{
		if (not photon_sigmaEtaEta_isLoaded) {
			if (photon_sigmaEtaEta_branch != 0) {
				photon_sigmaEtaEta_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_sigmaEtaEta_branch does not exist!\n");
				exit(1);
			}
			photon_sigmaEtaEta_isLoaded = true;
		}
		return photon_sigmaEtaEta_;
	}
	float &photon_sigmaIEtaIEta()
	{
		if (not photon_sigmaIEtaIEta_isLoaded) {
			if (photon_sigmaIEtaIEta_branch != 0) {
				photon_sigmaIEtaIEta_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_sigmaIEtaIEta_branch does not exist!\n");
				exit(1);
			}
			photon_sigmaIEtaIEta_isLoaded = true;
		}
		return photon_sigmaIEtaIEta_;
	}
	float &photon_sigmaIPhiIPhi()
	{
		if (not photon_sigmaIPhiIPhi_isLoaded) {
			if (photon_sigmaIPhiIPhi_branch != 0) {
				photon_sigmaIPhiIPhi_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_sigmaIPhiIPhi_branch does not exist!\n");
				exit(1);
			}
			photon_sigmaIPhiIPhi_isLoaded = true;
		}
		return photon_sigmaIPhiIPhi_;
	}
	float &photon_tkisoHollow03()
	{
		if (not photon_tkisoHollow03_isLoaded) {
			if (photon_tkisoHollow03_branch != 0) {
				photon_tkisoHollow03_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_tkisoHollow03_branch does not exist!\n");
				exit(1);
			}
			photon_tkisoHollow03_isLoaded = true;
		}
		return photon_tkisoHollow03_;
	}
	float &photon_tkisoHollow04()
	{
		if (not photon_tkisoHollow04_isLoaded) {
			if (photon_tkisoHollow04_branch != 0) {
				photon_tkisoHollow04_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_tkisoHollow04_branch does not exist!\n");
				exit(1);
			}
			photon_tkisoHollow04_isLoaded = true;
		}
		return photon_tkisoHollow04_;
	}
	float &photon_tkisoSolid03()
	{
		if (not photon_tkisoSolid03_isLoaded) {
			if (photon_tkisoSolid03_branch != 0) {
				photon_tkisoSolid03_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_tkisoSolid03_branch does not exist!\n");
				exit(1);
			}
			photon_tkisoSolid03_isLoaded = true;
		}
		return photon_tkisoSolid03_;
	}
	float &photon_tkisoSolid04()
	{
		if (not photon_tkisoSolid04_isLoaded) {
			if (photon_tkisoSolid04_branch != 0) {
				photon_tkisoSolid04_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon_tkisoSolid04_branch does not exist!\n");
				exit(1);
			}
			photon_tkisoSolid04_isLoaded = true;
		}
		return photon_tkisoSolid04_;
	}
	float &jetdr()
	{
		if (not jetdr_isLoaded) {
			if (jetdr_branch != 0) {
				jetdr_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jetdr_branch does not exist!\n");
				exit(1);
			}
			jetdr_isLoaded = true;
		}
		return jetdr_;
	}
	float &jetpt()
	{
		if (not jetpt_isLoaded) {
			if (jetpt_branch != 0) {
				jetpt_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jetpt_branch does not exist!\n");
				exit(1);
			}
			jetpt_isLoaded = true;
		}
		return jetpt_;
	}
	float &calojetpt()
	{
		if (not calojetpt_isLoaded) {
			if (calojetpt_branch != 0) {
				calojetpt_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch calojetpt_branch does not exist!\n");
				exit(1);
			}
			calojetpt_isLoaded = true;
		}
		return calojetpt_;
	}
	int &pfjetid()
	{
		if (not pfjetid_isLoaded) {
			if (pfjetid_branch != 0) {
				pfjetid_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pfjetid_branch does not exist!\n");
				exit(1);
			}
			pfjetid_isLoaded = true;
		}
		return pfjetid_;
	}
	float &jeteta()
	{
		if (not jeteta_isLoaded) {
			if (jeteta_branch != 0) {
				jeteta_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jeteta_branch does not exist!\n");
				exit(1);
			}
			jeteta_isLoaded = true;
		}
		return jeteta_;
	}
	float &jetenergy()
	{
		if (not jetenergy_isLoaded) {
			if (jetenergy_branch != 0) {
				jetenergy_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jetenergy_branch does not exist!\n");
				exit(1);
			}
			jetenergy_isLoaded = true;
		}
		return jetenergy_;
	}
	float &jetchargedemfrac()
	{
		if (not jetchargedemfrac_isLoaded) {
			if (jetchargedemfrac_branch != 0) {
				jetchargedemfrac_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jetchargedemfrac_branch does not exist!\n");
				exit(1);
			}
			jetchargedemfrac_isLoaded = true;
		}
		return jetchargedemfrac_;
	}
	float &jetchargedhadfrac()
	{
		if (not jetchargedhadfrac_isLoaded) {
			if (jetchargedhadfrac_branch != 0) {
				jetchargedhadfrac_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jetchargedhadfrac_branch does not exist!\n");
				exit(1);
			}
			jetchargedhadfrac_isLoaded = true;
		}
		return jetchargedhadfrac_;
	}
	float &jetneutralemfrac()
	{
		if (not jetneutralemfrac_isLoaded) {
			if (jetneutralemfrac_branch != 0) {
				jetneutralemfrac_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jetneutralemfrac_branch does not exist!\n");
				exit(1);
			}
			jetneutralemfrac_isLoaded = true;
		}
		return jetneutralemfrac_;
	}
	float &jetneutralhadfrac()
	{
		if (not jetneutralhadfrac_isLoaded) {
			if (jetneutralhadfrac_branch != 0) {
				jetneutralhadfrac_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jetneutralhadfrac_branch does not exist!\n");
				exit(1);
			}
			jetneutralhadfrac_isLoaded = true;
		}
		return jetneutralhadfrac_;
	}
	int &jetncharged()
	{
		if (not jetncharged_isLoaded) {
			if (jetncharged_branch != 0) {
				jetncharged_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jetncharged_branch does not exist!\n");
				exit(1);
			}
			jetncharged_isLoaded = true;
		}
		return jetncharged_;
	}
	int &jetnmuon()
	{
		if (not jetnmuon_isLoaded) {
			if (jetnmuon_branch != 0) {
				jetnmuon_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jetnmuon_branch does not exist!\n");
				exit(1);
			}
			jetnmuon_isLoaded = true;
		}
		return jetnmuon_;
	}
	int &jetnneutral()
	{
		if (not jetnneutral_isLoaded) {
			if (jetnneutral_branch != 0) {
				jetnneutral_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jetnneutral_branch does not exist!\n");
				exit(1);
			}
			jetnneutral_isLoaded = true;
		}
		return jetnneutral_;
	}
	float &jetdphimet()
	{
		if (not jetdphimet_isLoaded) {
			if (jetdphimet_branch != 0) {
				jetdphimet_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jetdphimet_branch does not exist!\n");
				exit(1);
			}
			jetdphimet_isLoaded = true;
		}
		return jetdphimet_;
	}
	float &jetdpt()
	{
		if (not jetdpt_isLoaded) {
			if (jetdpt_branch != 0) {
				jetdpt_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jetdpt_branch does not exist!\n");
				exit(1);
			}
			jetdpt_isLoaded = true;
		}
		return jetdpt_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet1()
	{
		if (not jet1_isLoaded) {
			if (jet1_branch != 0) {
				jet1_branch->GetEntry(index);
				#ifdef PARANOIA
				int e;
				frexp(jet1_->pt(), &e);
				if (not isfinite(jet1_->pt()) || e > 30) {
					printf("branch jet1_branch contains a bad float: %f\n", jet1_->pt());
					exit(1);
				}
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet1_branch does not exist!\n");
				exit(1);
			}
			jet1_isLoaded = true;
		}
		return *jet1_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet2()
	{
		if (not jet2_isLoaded) {
			if (jet2_branch != 0) {
				jet2_branch->GetEntry(index);
				#ifdef PARANOIA
				int e;
				frexp(jet2_->pt(), &e);
				if (not isfinite(jet2_->pt()) || e > 30) {
					printf("branch jet2_branch contains a bad float: %f\n", jet2_->pt());
					exit(1);
				}
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet2_branch does not exist!\n");
				exit(1);
			}
			jet2_isLoaded = true;
		}
		return *jet2_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet3()
	{
		if (not jet3_isLoaded) {
			if (jet3_branch != 0) {
				jet3_branch->GetEntry(index);
				#ifdef PARANOIA
				int e;
				frexp(jet3_->pt(), &e);
				if (not isfinite(jet3_->pt()) || e > 30) {
					printf("branch jet3_branch contains a bad float: %f\n", jet3_->pt());
					exit(1);
				}
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet3_branch does not exist!\n");
				exit(1);
			}
			jet3_isLoaded = true;
		}
		return *jet3_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet4()
	{
		if (not jet4_isLoaded) {
			if (jet4_branch != 0) {
				jet4_branch->GetEntry(index);
				#ifdef PARANOIA
				int e;
				frexp(jet4_->pt(), &e);
				if (not isfinite(jet4_->pt()) || e > 30) {
					printf("branch jet4_branch contains a bad float: %f\n", jet4_->pt());
					exit(1);
				}
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet4_branch does not exist!\n");
				exit(1);
			}
			jet4_isLoaded = true;
		}
		return *jet4_;
	}
	int &jet1flav()
	{
		if (not jet1flav_isLoaded) {
			if (jet1flav_branch != 0) {
				jet1flav_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet1flav_branch does not exist!\n");
				exit(1);
			}
			jet1flav_isLoaded = true;
		}
		return jet1flav_;
	}
	int &jet2flav()
	{
		if (not jet2flav_isLoaded) {
			if (jet2flav_branch != 0) {
				jet2flav_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet2flav_branch does not exist!\n");
				exit(1);
			}
			jet2flav_isLoaded = true;
		}
		return jet2flav_;
	}
	int &jet3flav()
	{
		if (not jet3flav_isLoaded) {
			if (jet3flav_branch != 0) {
				jet3flav_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet3flav_branch does not exist!\n");
				exit(1);
			}
			jet3flav_isLoaded = true;
		}
		return jet3flav_;
	}
	int &jet4flav()
	{
		if (not jet4flav_isLoaded) {
			if (jet4flav_branch != 0) {
				jet4flav_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet4flav_branch does not exist!\n");
				exit(1);
			}
			jet4flav_isLoaded = true;
		}
		return jet4flav_;
	}
	int &jet1mcfa()
	{
		if (not jet1mcfa_isLoaded) {
			if (jet1mcfa_branch != 0) {
				jet1mcfa_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet1mcfa_branch does not exist!\n");
				exit(1);
			}
			jet1mcfa_isLoaded = true;
		}
		return jet1mcfa_;
	}
	int &jet2mcfa()
	{
		if (not jet2mcfa_isLoaded) {
			if (jet2mcfa_branch != 0) {
				jet2mcfa_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet2mcfa_branch does not exist!\n");
				exit(1);
			}
			jet2mcfa_isLoaded = true;
		}
		return jet2mcfa_;
	}
	int &jet3mcfa()
	{
		if (not jet3mcfa_isLoaded) {
			if (jet3mcfa_branch != 0) {
				jet3mcfa_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet3mcfa_branch does not exist!\n");
				exit(1);
			}
			jet3mcfa_isLoaded = true;
		}
		return jet3mcfa_;
	}
	int &jet4mcfa()
	{
		if (not jet4mcfa_isLoaded) {
			if (jet4mcfa_branch != 0) {
				jet4mcfa_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet4mcfa_branch does not exist!\n");
				exit(1);
			}
			jet4mcfa_isLoaded = true;
		}
		return jet4mcfa_;
	}
	int &jet1mcfp()
	{
		if (not jet1mcfp_isLoaded) {
			if (jet1mcfp_branch != 0) {
				jet1mcfp_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet1mcfp_branch does not exist!\n");
				exit(1);
			}
			jet1mcfp_isLoaded = true;
		}
		return jet1mcfp_;
	}
	int &jet2mcfp()
	{
		if (not jet2mcfp_isLoaded) {
			if (jet2mcfp_branch != 0) {
				jet2mcfp_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet2mcfp_branch does not exist!\n");
				exit(1);
			}
			jet2mcfp_isLoaded = true;
		}
		return jet2mcfp_;
	}
	int &jet3mcfp()
	{
		if (not jet3mcfp_isLoaded) {
			if (jet3mcfp_branch != 0) {
				jet3mcfp_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet3mcfp_branch does not exist!\n");
				exit(1);
			}
			jet3mcfp_isLoaded = true;
		}
		return jet3mcfp_;
	}
	int &jet4mcfp()
	{
		if (not jet4mcfp_isLoaded) {
			if (jet4mcfp_branch != 0) {
				jet4mcfp_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet4mcfp_branch does not exist!\n");
				exit(1);
			}
			jet4mcfp_isLoaded = true;
		}
		return jet4mcfp_;
	}
	float &csv1()
	{
		if (not csv1_isLoaded) {
			if (csv1_branch != 0) {
				csv1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch csv1_branch does not exist!\n");
				exit(1);
			}
			csv1_isLoaded = true;
		}
		return csv1_;
	}
	float &csv2()
	{
		if (not csv2_isLoaded) {
			if (csv2_branch != 0) {
				csv2_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch csv2_branch does not exist!\n");
				exit(1);
			}
			csv2_isLoaded = true;
		}
		return csv2_;
	}
	float &csv3()
	{
		if (not csv3_isLoaded) {
			if (csv3_branch != 0) {
				csv3_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch csv3_branch does not exist!\n");
				exit(1);
			}
			csv3_isLoaded = true;
		}
		return csv3_;
	}
	float &csv4()
	{
		if (not csv4_isLoaded) {
			if (csv4_branch != 0) {
				csv4_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch csv4_branch does not exist!\n");
				exit(1);
			}
			csv4_isLoaded = true;
		}
		return csv4_;
	}
	float &jet1drgen()
	{
		if (not jet1drgen_isLoaded) {
			if (jet1drgen_branch != 0) {
				jet1drgen_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet1drgen_branch does not exist!\n");
				exit(1);
			}
			jet1drgen_isLoaded = true;
		}
		return jet1drgen_;
	}
	float &jet2drgen()
	{
		if (not jet2drgen_isLoaded) {
			if (jet2drgen_branch != 0) {
				jet2drgen_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet2drgen_branch does not exist!\n");
				exit(1);
			}
			jet2drgen_isLoaded = true;
		}
		return jet2drgen_;
	}
	float &jet3drgen()
	{
		if (not jet3drgen_isLoaded) {
			if (jet3drgen_branch != 0) {
				jet3drgen_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet3drgen_branch does not exist!\n");
				exit(1);
			}
			jet3drgen_isLoaded = true;
		}
		return jet3drgen_;
	}
	float &jet4drgen()
	{
		if (not jet4drgen_isLoaded) {
			if (jet4drgen_branch != 0) {
				jet4drgen_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet4drgen_branch does not exist!\n");
				exit(1);
			}
			jet4drgen_isLoaded = true;
		}
		return jet4drgen_;
	}
	float &jet1beta1_01()
	{
		if (not jet1beta1_01_isLoaded) {
			if (jet1beta1_01_branch != 0) {
				jet1beta1_01_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet1beta1_01_branch does not exist!\n");
				exit(1);
			}
			jet1beta1_01_isLoaded = true;
		}
		return jet1beta1_01_;
	}
	float &jet2beta1_01()
	{
		if (not jet2beta1_01_isLoaded) {
			if (jet2beta1_01_branch != 0) {
				jet2beta1_01_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet2beta1_01_branch does not exist!\n");
				exit(1);
			}
			jet2beta1_01_isLoaded = true;
		}
		return jet2beta1_01_;
	}
	float &jet3beta1_01()
	{
		if (not jet3beta1_01_isLoaded) {
			if (jet3beta1_01_branch != 0) {
				jet3beta1_01_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet3beta1_01_branch does not exist!\n");
				exit(1);
			}
			jet3beta1_01_isLoaded = true;
		}
		return jet3beta1_01_;
	}
	float &jet4beta1_01()
	{
		if (not jet4beta1_01_isLoaded) {
			if (jet4beta1_01_branch != 0) {
				jet4beta1_01_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet4beta1_01_branch does not exist!\n");
				exit(1);
			}
			jet4beta1_01_isLoaded = true;
		}
		return jet4beta1_01_;
	}
	float &jet1beta2_01()
	{
		if (not jet1beta2_01_isLoaded) {
			if (jet1beta2_01_branch != 0) {
				jet1beta2_01_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet1beta2_01_branch does not exist!\n");
				exit(1);
			}
			jet1beta2_01_isLoaded = true;
		}
		return jet1beta2_01_;
	}
	float &jet2beta2_01()
	{
		if (not jet2beta2_01_isLoaded) {
			if (jet2beta2_01_branch != 0) {
				jet2beta2_01_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet2beta2_01_branch does not exist!\n");
				exit(1);
			}
			jet2beta2_01_isLoaded = true;
		}
		return jet2beta2_01_;
	}
	float &jet3beta2_01()
	{
		if (not jet3beta2_01_isLoaded) {
			if (jet3beta2_01_branch != 0) {
				jet3beta2_01_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet3beta2_01_branch does not exist!\n");
				exit(1);
			}
			jet3beta2_01_isLoaded = true;
		}
		return jet3beta2_01_;
	}
	float &jet4beta2_01()
	{
		if (not jet4beta2_01_isLoaded) {
			if (jet4beta2_01_branch != 0) {
				jet4beta2_01_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet4beta2_01_branch does not exist!\n");
				exit(1);
			}
			jet4beta2_01_isLoaded = true;
		}
		return jet4beta2_01_;
	}
	float &jet1beta1_05()
	{
		if (not jet1beta1_05_isLoaded) {
			if (jet1beta1_05_branch != 0) {
				jet1beta1_05_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet1beta1_05_branch does not exist!\n");
				exit(1);
			}
			jet1beta1_05_isLoaded = true;
		}
		return jet1beta1_05_;
	}
	float &jet2beta1_05()
	{
		if (not jet2beta1_05_isLoaded) {
			if (jet2beta1_05_branch != 0) {
				jet2beta1_05_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet2beta1_05_branch does not exist!\n");
				exit(1);
			}
			jet2beta1_05_isLoaded = true;
		}
		return jet2beta1_05_;
	}
	float &jet3beta1_05()
	{
		if (not jet3beta1_05_isLoaded) {
			if (jet3beta1_05_branch != 0) {
				jet3beta1_05_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet3beta1_05_branch does not exist!\n");
				exit(1);
			}
			jet3beta1_05_isLoaded = true;
		}
		return jet3beta1_05_;
	}
	float &jet4beta1_05()
	{
		if (not jet4beta1_05_isLoaded) {
			if (jet4beta1_05_branch != 0) {
				jet4beta1_05_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet4beta1_05_branch does not exist!\n");
				exit(1);
			}
			jet4beta1_05_isLoaded = true;
		}
		return jet4beta1_05_;
	}
	float &jet1beta2_05()
	{
		if (not jet1beta2_05_isLoaded) {
			if (jet1beta2_05_branch != 0) {
				jet1beta2_05_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet1beta2_05_branch does not exist!\n");
				exit(1);
			}
			jet1beta2_05_isLoaded = true;
		}
		return jet1beta2_05_;
	}
	float &jet2beta2_05()
	{
		if (not jet2beta2_05_isLoaded) {
			if (jet2beta2_05_branch != 0) {
				jet2beta2_05_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet2beta2_05_branch does not exist!\n");
				exit(1);
			}
			jet2beta2_05_isLoaded = true;
		}
		return jet2beta2_05_;
	}
	float &jet3beta2_05()
	{
		if (not jet3beta2_05_isLoaded) {
			if (jet3beta2_05_branch != 0) {
				jet3beta2_05_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet3beta2_05_branch does not exist!\n");
				exit(1);
			}
			jet3beta2_05_isLoaded = true;
		}
		return jet3beta2_05_;
	}
	float &jet4beta2_05()
	{
		if (not jet4beta2_05_isLoaded) {
			if (jet4beta2_05_branch != 0) {
				jet4beta2_05_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet4beta2_05_branch does not exist!\n");
				exit(1);
			}
			jet4beta2_05_isLoaded = true;
		}
		return jet4beta2_05_;
	}
	float &jet1beta1_10()
	{
		if (not jet1beta1_10_isLoaded) {
			if (jet1beta1_10_branch != 0) {
				jet1beta1_10_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet1beta1_10_branch does not exist!\n");
				exit(1);
			}
			jet1beta1_10_isLoaded = true;
		}
		return jet1beta1_10_;
	}
	float &jet2beta1_10()
	{
		if (not jet2beta1_10_isLoaded) {
			if (jet2beta1_10_branch != 0) {
				jet2beta1_10_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet2beta1_10_branch does not exist!\n");
				exit(1);
			}
			jet2beta1_10_isLoaded = true;
		}
		return jet2beta1_10_;
	}
	float &jet3beta1_10()
	{
		if (not jet3beta1_10_isLoaded) {
			if (jet3beta1_10_branch != 0) {
				jet3beta1_10_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet3beta1_10_branch does not exist!\n");
				exit(1);
			}
			jet3beta1_10_isLoaded = true;
		}
		return jet3beta1_10_;
	}
	float &jet4beta1_10()
	{
		if (not jet4beta1_10_isLoaded) {
			if (jet4beta1_10_branch != 0) {
				jet4beta1_10_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet4beta1_10_branch does not exist!\n");
				exit(1);
			}
			jet4beta1_10_isLoaded = true;
		}
		return jet4beta1_10_;
	}
	float &jet1beta2_10()
	{
		if (not jet1beta2_10_isLoaded) {
			if (jet1beta2_10_branch != 0) {
				jet1beta2_10_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet1beta2_10_branch does not exist!\n");
				exit(1);
			}
			jet1beta2_10_isLoaded = true;
		}
		return jet1beta2_10_;
	}
	float &jet2beta2_10()
	{
		if (not jet2beta2_10_isLoaded) {
			if (jet2beta2_10_branch != 0) {
				jet2beta2_10_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet2beta2_10_branch does not exist!\n");
				exit(1);
			}
			jet2beta2_10_isLoaded = true;
		}
		return jet2beta2_10_;
	}
	float &jet3beta2_10()
	{
		if (not jet3beta2_10_isLoaded) {
			if (jet3beta2_10_branch != 0) {
				jet3beta2_10_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet3beta2_10_branch does not exist!\n");
				exit(1);
			}
			jet3beta2_10_isLoaded = true;
		}
		return jet3beta2_10_;
	}
	float &jet4beta2_10()
	{
		if (not jet4beta2_10_isLoaded) {
			if (jet4beta2_10_branch != 0) {
				jet4beta2_10_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jet4beta2_10_branch does not exist!\n");
				exit(1);
			}
			jet4beta2_10_isLoaded = true;
		}
		return jet4beta2_10_;
	}
	int &csc()
	{
		if (not csc_isLoaded) {
			if (csc_branch != 0) {
				csc_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch csc_branch does not exist!\n");
				exit(1);
			}
			csc_isLoaded = true;
		}
		return csc_;
	}
	int &hbhe()
	{
		if (not hbhe_isLoaded) {
			if (hbhe_branch != 0) {
				hbhe_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hbhe_branch does not exist!\n");
				exit(1);
			}
			hbhe_isLoaded = true;
		}
		return hbhe_;
	}
	int &hbhenew()
	{
		if (not hbhenew_isLoaded) {
			if (hbhenew_branch != 0) {
				hbhenew_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hbhenew_branch does not exist!\n");
				exit(1);
			}
			hbhenew_isLoaded = true;
		}
		return hbhenew_;
	}
	int &hcallaser()
	{
		if (not hcallaser_isLoaded) {
			if (hcallaser_branch != 0) {
				hcallaser_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hcallaser_branch does not exist!\n");
				exit(1);
			}
			hcallaser_isLoaded = true;
		}
		return hcallaser_;
	}
	int &ecallaser()
	{
		if (not ecallaser_isLoaded) {
			if (ecallaser_branch != 0) {
				ecallaser_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ecallaser_branch does not exist!\n");
				exit(1);
			}
			ecallaser_isLoaded = true;
		}
		return ecallaser_;
	}
	int &ecaltp()
	{
		if (not ecaltp_isLoaded) {
			if (ecaltp_branch != 0) {
				ecaltp_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ecaltp_branch does not exist!\n");
				exit(1);
			}
			ecaltp_isLoaded = true;
		}
		return ecaltp_;
	}
	int &trkfail()
	{
		if (not trkfail_isLoaded) {
			if (trkfail_branch != 0) {
				trkfail_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch trkfail_branch does not exist!\n");
				exit(1);
			}
			trkfail_isLoaded = true;
		}
		return trkfail_;
	}
	int &eebadsc()
	{
		if (not eebadsc_isLoaded) {
			if (eebadsc_branch != 0) {
				eebadsc_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch eebadsc_branch does not exist!\n");
				exit(1);
			}
			eebadsc_isLoaded = true;
		}
		return eebadsc_;
	}
	float &mjj()
	{
		if (not mjj_isLoaded) {
			if (mjj_branch != 0) {
				mjj_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mjj_branch does not exist!\n");
				exit(1);
			}
			mjj_isLoaded = true;
		}
		return mjj_;
	}
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &pujets()
	{
		if (not pujets_isLoaded) {
			if (pujets_branch != 0) {
				pujets_branch->GetEntry(index);
				#ifdef PARANOIA
				for (vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >::const_iterator i = pujets_->begin(); i != pujets_->end(); ++i) {
					int e;
					frexp(i->pt(), &e);
					if (not isfinite(i->pt()) || e > 30) {
						printf("branch pujets_branch contains a bad float: %f\n", i->pt());
						exit(1);
					}
				}
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pujets_branch does not exist!\n");
				exit(1);
			}
			pujets_isLoaded = true;
		}
		return *pujets_;
	}
	int &npujets()
	{
		if (not npujets_isLoaded) {
			if (npujets_branch != 0) {
				npujets_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch npujets_branch does not exist!\n");
				exit(1);
			}
			npujets_isLoaded = true;
		}
		return npujets_;
	}

  static void progress( int nEventsTotal, int nEventsChain ){
    int period = 1000;
    if(nEventsTotal%1000 == 0) {
      // xterm magic from L. Vacavant and A. Cerri
      if (isatty(1)) {
        if( ( nEventsChain - nEventsTotal ) > period ){
          float frac = (float)nEventsTotal/(nEventsChain*0.01);
          printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
               "\033[0m\033[32m <---\033[0m\015", frac);
          fflush(stdout);
        }
        else {
          printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
                 "\033[0m\033[32m <---\033[0m\015", 100.);
          cout << endl;
        }
      }
    }
  }
  
};

#ifndef __CINT__
extern TEMPLATES templates;
#endif

namespace Templates {
	int &run();
	int &lumi();
	int &event();
	int &nvtx();
	float &weight();
	float &pthat();
	int &failjetid();
	float &maxemf();
	float &maxleppt();
	int &elveto();
	float &ht30();
	float &ht40();
	float &jzb();
	float &pfmet();
	float &pfmett1();
	float &pfmett1new();
	float &pfmet_type1_pt30();
	float &pfmet_type1_pt15();
	float &pfmetphi();
	float &pfmett1phi();
	float &pfmett1newphi();
	float &pfsumet();
	float &met();
	float &metphi();
	float &sumet();
	float &mumet();
	float &mumetphi();
	float &musumet();
	float &mujesmet();
	float &mujesmetphi();
	float &mujessumet();
	float &genmet();
	float &genmetphi();
	float &gensumet();
	float &dphixmet();
	float &metpar();
	float &metperp();
	float &tcmet();
	float &tcmetphi();
	float &tcsumet();
	float &tcmetNew();
	float &tcmetNew_type1_pt30();
	float &tcmetNew_type1_pt15();
	float &tcmetphiNew();
	float &tcsumetNew();
	int &njets();
	int &njets10();
	int &njets15();
	int &njets20();
	int &njets40();
	float &ht();
	float &ht10();
	float &vecjetpt();
	int &nbl();
	int &nbm();
	int &nbt();
	float &ndphijetmet();
	float &maxjetpt();
	float &maxjetdphimet();
	int &hlt20();
	int &hlt30();
	int &hlt50();
	int &hlt75();
	int &hlt90();
	int &hlt135();
	int &hlt150();
	int &hlt160();
	int &hgg22();
	int &hgg36();
	int &hgg50();
	int &hgg75();
	int &hgg90();
	float &rho();
	int &vtxidx();
	int &ng();
	float &etg();
	float &etag();
	float &phig();
	float &hoe();
	float &eciso();
	float &hciso();
	float &tkiso();
	float &swiss();
	float &seed();
	float &s4();
	float &r4();
	int &photon_scidx();
	int &photon_pixelseed();
	float &photon_e15();
	float &photon_e25max();
	float &photon_e33();
	float &photon_e55();
	float &photon_ecalIso03();
	float &photon_ecalIso04();
	float &photon_hcalIso03();
	float &photon_hcalIso04();
	float &photon_ntkIsoHollow03();
	float &photon_ntkIsoHollow04();
	float &photon_ntkIsoSolid03();
	float &photon_ntkIsoSolid04();
	float &photon_sigmaEtaEta();
	float &photon_sigmaIEtaIEta();
	float &photon_sigmaIPhiIPhi();
	float &photon_tkisoHollow03();
	float &photon_tkisoHollow04();
	float &photon_tkisoSolid03();
	float &photon_tkisoSolid04();
	float &jetdr();
	float &jetpt();
	float &calojetpt();
	int &pfjetid();
	float &jeteta();
	float &jetenergy();
	float &jetchargedemfrac();
	float &jetchargedhadfrac();
	float &jetneutralemfrac();
	float &jetneutralhadfrac();
	int &jetncharged();
	int &jetnmuon();
	int &jetnneutral();
	float &jetdphimet();
	float &jetdpt();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet1();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet2();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet3();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet4();
	int &jet1flav();
	int &jet2flav();
	int &jet3flav();
	int &jet4flav();
	int &jet1mcfa();
	int &jet2mcfa();
	int &jet3mcfa();
	int &jet4mcfa();
	int &jet1mcfp();
	int &jet2mcfp();
	int &jet3mcfp();
	int &jet4mcfp();
	float &csv1();
	float &csv2();
	float &csv3();
	float &csv4();
	float &jet1drgen();
	float &jet2drgen();
	float &jet3drgen();
	float &jet4drgen();
	float &jet1beta1_01();
	float &jet2beta1_01();
	float &jet3beta1_01();
	float &jet4beta1_01();
	float &jet1beta2_01();
	float &jet2beta2_01();
	float &jet3beta2_01();
	float &jet4beta2_01();
	float &jet1beta1_05();
	float &jet2beta1_05();
	float &jet3beta1_05();
	float &jet4beta1_05();
	float &jet1beta2_05();
	float &jet2beta2_05();
	float &jet3beta2_05();
	float &jet4beta2_05();
	float &jet1beta1_10();
	float &jet2beta1_10();
	float &jet3beta1_10();
	float &jet4beta1_10();
	float &jet1beta2_10();
	float &jet2beta2_10();
	float &jet3beta2_10();
	float &jet4beta2_10();
	int &csc();
	int &hbhe();
	int &hbhenew();
	int &hcallaser();
	int &ecallaser();
	int &ecaltp();
	int &trkfail();
	int &eebadsc();
	float &mjj();
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &pujets();
	int &npujets();
}
#endif
