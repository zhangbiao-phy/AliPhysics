AliAnalysisTask *AddTask_hmurakam_highmultpp(Bool_t getFromAlien=kFALSE,
					     TString year ="16",
					     Bool_t hasSpline =kFALSE,
					     TString cFileName = "Config_hmurakam_pp.C",
					     Char_t* outputFileName="LMEE.root",
					     ULong64_t triggerMask = AliVEvent::kHighMultV0,
					     Bool_t rejectPileup = kTRUE,
					     Int_t pileuprej = AliDielectronEventCuts::kSPDInMultBins,
					     Float_t cent_min = 0.0,
					     Float_t cent_max = 0.05,
					     Int_t wagonnr=0
                                            ){
    
    //=== get the current analysis manager ===========================
    AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
    if (!mgr) {
        Error("AddTask_hmurakam_highmultpp", "No analysis manager found.");
        return 0;
    }
    
    //Base Directory for GRID / LEGO Train
    TString configBasePath= "$ALICE_PHYSICS/PWGDQ/dielectron/macrosLMEE/";
    if(getFromAlien && (!gSystem->Exec(Form("alien_cp alien:///alice/cern.ch/user/h/hmurakam/PWGDQ/dielectron/macrosLMEE/%s .",cFileName.Data()))) ){
        configBasePath=Form("%s/",gSystem->pwd());
    }
    
    TString configFilePath(configBasePath+cFileName);
    
    std::cout << "Configpath: " << configFilePath << std::endl;

    TString configFunction(cFileName(0,cFileName.Length() - 2));
    
    if (!gROOT->GetListOfGlobalFunctions()->FindObject(configFunction.Data()))
        gROOT->LoadMacro(configFilePath.Data());
    
    //Do we have an MC handler?
    hasMC = (AliAnalysisManager::GetAnalysisManager()->GetMCtruthEventHandler()!=0x0);
    std::cout << "hasMC = " << hasMC << std::endl;
    if(hasMC) kMixing = 0;
    
    //=== Create the main dielectron task =============================
    AliAnalysisTaskMultiDielectron *task=new AliAnalysisTaskMultiDielectron(Form("MultiDielectron_hm_%d",wagonnr));
    if (!hasMC) task->UsePhysicsSelection();
    task->SetTriggerMask(triggerMask);
    task->SetTriggerOnV0AND(kTRUE); // only for cross-check
    
    // SPD pile-up rejection in mult. bins
    if (rejectPileup) {
        task->SetRejectPileup(kTRUE);
        task->SetPileupRejTool(pileuprej);
    }
    
    // randomize daughters
    task->SetRandomizeDaughters(kTRUE);
    
    //=== Add event filter ============================================

    task->SetEventFilter(GetEventCutsHighMult(cent_min,cent_max));
    //add dielectron analysis with different cuts to the task
    for (Int_t i=0; i<nDie; ++i){ //nDie defined in config file
        
        AliDielectron *diele = Config_hmurakam_pp(i,year.Data(),hasSpline);
        if(!diele)continue;
        task->AddDielectron(diele);
    }
    
    mgr->AddTask(task);
    
    //=== create output containers ===========================
    AliAnalysisDataContainer *coutput1 =0x0;
    AliAnalysisDataContainer *cOutputHist1 =0x0;
    AliAnalysisDataContainer *cOutputHist2 =0x0;
    AliAnalysisDataContainer *coutput1 =0x0;

    if(wagonnr == 0){
      coutput1 = mgr->CreateContainer("tree_lowmass_hm",TTree::Class(),
				      AliAnalysisManager::kExchangeContainer,outputFileName);

      cOutputHist1 = mgr->CreateContainer("Output_Histos_hm",TList::Class(),
					  AliAnalysisManager::kOutputContainer,outputFileName);

      cOutputHist2 = mgr->CreateContainer("Output_CF_hm",TList::Class(),
					  AliAnalysisManager::kOutputContainer,outputFileName);

      cOutputHist3 = mgr->CreateContainer("Output_EventStat_hm", TH1D::Class(),
					  AliAnalysisManager::kOutputContainer,outputFileName);
    }else{
      coutput1 = mgr->CreateContainer(Form("tree_lowmass_hm_%d",wagonnr),TTree::Class(),
				      AliAnalysisManager::kExchangeContainer,outputFileName);

      cOutputHist1 = mgr->CreateContainer(Form("Output_Histos_hm_%d",wagonnr),TList::Class(),
					  AliAnalysisManager::kOutputContainer,outputFileName);

      cOutputHist2 = mgr->CreateContainer(Form("Output_CF_hm_%d",wagonnr),TList::Class(),
					  AliAnalysisManager::kOutputContainer,outputFileName);

      cOutputHist3 = mgr->CreateContainer(Form("Output_EventStat_hm_%d",wagonnr),TH1D::Class(),
					  AliAnalysisManager::kOutputContainer,outputFileName);
    }
    
    mgr->ConnectInput(task,  0, mgr->GetCommonInputContainer());
    mgr->ConnectOutput(task, 0, coutput1 );
    mgr->ConnectOutput(task, 1, cOutputHist1);
    mgr->ConnectOutput(task, 2, cOutputHist2);
    mgr->ConnectOutput(task, 3, cOutputHist3);
    
    return task;
}

