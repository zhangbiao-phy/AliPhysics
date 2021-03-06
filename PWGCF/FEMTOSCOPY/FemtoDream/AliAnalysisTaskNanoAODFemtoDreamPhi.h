#ifndef PWGCF_FEMTOSCOPY_FEMTODREAM_AliAnalysisTaskNanoAODFemtoDreamPhi_H_
#define PWGCF_FEMTOSCOPY_FEMTODREAM_AliAnalysisTaskNanoAODFemtoDreamPhi_H_
#include "Rtypes.h"
#include "AliAODTrack.h"
#include "AliAnalysisTaskSE.h"
#include "AliFemtoDreamCollConfig.h"
#include "AliFemtoDreamEvent.h"
#include "AliFemtoDreamEventCuts.h"
#include "AliFemtoDreamPairCleaner.h"
#include "AliFemtoDreamPartCollection.h"
#include "AliFemtoDreamTrack.h"
#include "AliFemtoDreamTrackCuts.h"
#include "AliFemtoDreamv0.h"
#include "AliFemtoDreamv0Cuts.h"
#include "AliFemtoDreamControlSample.h"


class AliVParticle;
class AliVTrack;

class AliAnalysisTaskNanoAODFemtoDreamPhi : public AliAnalysisTaskSE {
 public:
  AliAnalysisTaskNanoAODFemtoDreamPhi();
  AliAnalysisTaskNanoAODFemtoDreamPhi(const char *name, bool isMC);
  virtual ~AliAnalysisTaskNanoAODFemtoDreamPhi();
  virtual void UserCreateOutputObjects();
  virtual void UserExec(Option_t *);
  virtual void Terminate(Option_t *){};
  void SetEventCuts(AliFemtoDreamEventCuts *evtCuts) { fEventCuts = evtCuts; };

  void SetProtonCuts(AliFemtoDreamTrackCuts *cuts) {
    fTrackCutsPartProton = cuts;
  }
  void SetAntiProtonCuts(AliFemtoDreamTrackCuts *cuts) {
    fTrackCutsPartAntiProton = cuts;
  }
  void SetPosKaonCuts(AliFemtoDreamTrackCuts *trkCuts) {
    fPosKaonCuts = trkCuts;
  }
  void SetNegKaonCuts(AliFemtoDreamTrackCuts *trkCuts) {
    fNegKaonCuts = trkCuts;
  }
  void SetPhiCuts(AliFemtoDreamv0Cuts *phiCuts) { fPhiCuts = phiCuts; }
  void SetCollectionConfig(AliFemtoDreamCollConfig *config) {
    fConfig = config;
  }
  void SetTrigger(UInt_t trigger) { fTrigger = trigger; }
  void SetOEventMixing(bool mix) {  fUseOMixing = mix; }
  void SetMCTruth(bool mct) {  fIsMCTruth = mct; }
  void SetmixTRUTHREAL(bool mct) {  fIsmixTRUTHREAL = mct; }
  void SetmixTRUTFAKE(bool mct) {  fIsmixTRUTHFAKE = mct; }
  void SetmixREC(bool mct) {  fIsmixREC = mct; }

  void SetCutWindowMCTRUTH(float down, float up) {
    fInvMassCutSBdown = down;
    fInvMassCutSBup = up;
  }

  void SetpTprotonMCTRUTH(float pT) {
    fprotonpT = pT;
  }

  void SetetaprotonMCTRUTH(float eta) {
    fprotoneta = eta;
  }

  void SetpTkaonMCTRUTH(float pT) {
    fkaonpT = pT;
  }

  void SetetakaonMCTRUTH(float eta) {
    fkaoneta = eta;
  }


 private:
  AliAnalysisTaskNanoAODFemtoDreamPhi(const AliAnalysisTaskNanoAODFemtoDreamPhi &);
  AliAnalysisTaskNanoAODFemtoDreamPhi &operator=(const AliAnalysisTaskNanoAODFemtoDreamPhi &);
  void ResetGlobalTrackReference();
  void StoreGlobalTrackReference(AliVTrack *track);
  bool fIsMC;                            //
  bool fIsMCTruth;                       //
  bool fIsmixTRUTHREAL;                  //
  bool fIsmixTRUTHFAKE;                  //
  bool fIsmixREC;                        //
  bool fUseOMixing;                      //
  float fInvMassCutSBdown;               //
  float fInvMassCutSBup;                 //
  float fprotonpT;                       //
  float fprotoneta;                      //
  float fkaonpT;                         //
  float fkaoneta;                        //
  UInt_t fTrigger;                       //
  TList *fOutput;                        //!
  AliVEvent *fInputEvent;                //! current event
  AliFemtoDreamEvent *fEvent;            //!
  AliFemtoDreamTrack *fTrack;            //!
  AliFemtoDreamv0 *fPhiParticle;         //!
  AliFemtoDreamEventCuts *fEventCuts;    //
  AliFemtoDreamTrackCuts *fPosKaonCuts;  //
  AliFemtoDreamTrackCuts *fNegKaonCuts;  //
  AliFemtoDreamv0Cuts *fPhiCuts;         //
  AliFemtoDreamTrackCuts *fTrackCutsPartProton;      //
  AliFemtoDreamTrackCuts *fTrackCutsPartAntiProton;  //
  AliFemtoDreamCollConfig *fConfig;        //
  AliFemtoDreamPairCleaner *fPairCleaner;  //!
  AliFemtoDreamPartCollection *fPartColl;  //!
  AliFemtoDreamControlSample *fSample;   //!  
  AliVTrack **fGTI;                        //!
  int fTrackBufferSize;                    //
  ClassDef(AliAnalysisTaskNanoAODFemtoDreamPhi, 9)
};

#endif /* PWGCF_FEMTOSCOPY_FEMTODREAM_AliAnalysisTaskNanoAODFemtoDreamPhi_H_ */
