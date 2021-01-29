//
// ****************************************************************************************************
// *  Rogers and Mohan (2000) Benchmark                                                               *
// *  - Goal-Global:   Study the limits of Nuclear Reactor Physics methods in radiotherapy            *
// *  - Methods:       Slab (Water[1,4]cm-Bone[4,6]cm-Lung[6,13]cm-Water[13,31]cm) construction       *
// *                 Isotropic source                                                                 *
// *                 Transport electrons, positrons and gammas                                        *
// *  - Specific-Goal: Dose distribution along x                                                      *
// *  - Author: Ahmed Naceur, École Polytechnique de Montréal                                         *
// *  - Affilation:  Nuclear Engineering Institute, Department of Engineering Physics                 *
// *  - Date : 11 december 2020 (Creation)                                                            *
// *  - Reference for Benchmark:                                                                      *
// *    Rogers, D. W. O., & Mohan, R. (2000). Questions for comparison of clinical Monte Carlo codes. *
// *    In The Use of Computers in Radiation Therapy (pp. 120-122). Springer, Berlin, Heidelberg      *                           
// *                                                                                                  *
// ****************************************************************************************************
//    ***********************************************
//    *                                             *
//    * Main Prog. of the Rogers & Mohan Benchmark  *
//    *                                             *
//    ***********************************************


#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "PhysicsList.hh"
#include "PhysicsListMessenger.hh"
#include "G4ScoringManager.hh"
#include "G4VScoringMesh.hh"
#include "G4VScoreWriter.hh"
#include "globals.hh"
#include "StackingAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"

#include "G4RunManagerFactory.hh"

#include "G4UImanager.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

#include "g4analysis.hh"  // permet d'afficher des fichiers de sortie

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Optionally: choose a different Random engine...
  // G4Random::setTheEngine(new CLHEP::MTwistEngine);
  
  //-------------------------------------------------------------------------------
  // Data flow control 
  //-------------------------------------------------------------------------------
  // controls the flow of the program and manages the event loop(s) within a run.
  //-------------------------------------------------------------------------------
  auto* runManager =
    G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

  //-------------------------------------------------------------------------------
  // Activate command-based scoring functionality
  //-------------------------------------------------------------------------------
   
   G4ScoringManager * scManager = G4ScoringManager::GetScoringManager();
   scManager->SetVerboseLevel(1);  
  
  //-------------------------------------------------------------------------------
  // Set mandatory initialization classes
  //-------------------------------------------------------------------------------
  // Detector construction
  //-------------------------------------------------------------------------------
  runManager->SetUserInitialization(new DetectorConstruction());
  
  //-------------------------------------------------------------------------------
  // Physics list
  //-------------------------------------------------------------------------------

  // Geant-4 predifined physics list

  // G4PhysListFactory factory;
  // G4VModularPhysicsList* physicsList = factory.GetReferencePhysList("FTFP_BERT_EMV");
  // physicsList->SetVerboseLevel(2);
  // runManager->SetUserInitialization(physicsList);

  // Specific physics list

  runManager->SetUserInitialization(new PhysicsList);
  
  //-------------------------------------------------------------------------------
  // User action initialization
  //-------------------------------------------------------------------------------

  //runManager->SetUserInitialization(new ActionInitialization());

  //-------------------------------------------------------------------------------
  // Gabriel
  //-------------------------------------------------------------------------------

  PrimaryGeneratorAction *thePrimaryGeneratorAction = new PrimaryGeneratorAction();
  RunAction *theRunAction = new RunAction();
  runManager->SetUserAction(thePrimaryGeneratorAction);
  //SteppingAction *theSteppingAction = new SteppingAction();
  //runManager->SetUserAction(theSteppingAction);
  runManager->SetUserAction(theRunAction);
  runManager->SetUserAction(new StackingAction(theRunAction));
  //EventAction* pEventAction = new EventAction();
  //runManager->SetUserAction(pEventAction);
  
  //-------------------------------------------------------------------------------
  // Initialize visualization
  //-------------------------------------------------------------------------------
  G4VisManager* visManager = new G4VisExecutive;
 
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  

  //-------------------------------------------------------------------------------
  // Process macro or start UI session
  //-------------------------------------------------------------------------------
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }
  
  //-------------------------------------------------------------------------------
  // Job termination
  //-------------------------------------------------------------------------------
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  delete visManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
