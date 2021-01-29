
//    **********************************
//    *                                *
//    *     PhysicsList Class          *
//    *                                *
//    **********************************
//


  // Electromagnetic process
  #include "G4EmLivermorePhysics.hh"
  #include "G4EmStandardPhysics.hh"
  #include "G4EmStandardPhysics_option1.hh"
  #include "G4EmStandardPhysics_option2.hh"
  #include "G4EmStandardPhysics_option3.hh"
  #include "G4EmStandardPhysics_option4.hh"
  #include "G4DecayPhysics.hh"
  #include "G4RadioactiveDecayPhysics.hh"
  #include "G4EmPenelopePhysics.hh"
  #include "G4EmLowEPPhysics.hh" // added TO USE
  
  #include "PhysicsList.hh"
  #include "PhysicsListMessenger.hh"
  
  #include "G4VPhysicsConstructor.hh"
  #include "G4ParticleDefinition.hh"
  #include "G4ProductionCutsTable.hh"
  #include "G4ProcessManager.hh"
  #include "G4ParticleTypes.hh"
  
  #include "G4ios.hh"
  #include "G4StepLimiter.hh"
  
  #include "globals.hh"
  #include "G4SystemOfUnits.hh"
  #include "G4UAtomicDeexcitation.hh"
  #include "G4LossTableManager.hh"
  
  #include "G4EmParameters.hh"
  
  // Particles
  #include "G4Gamma.hh"
  #include "G4Electron.hh"
  #include "G4Positron.hh"
  #include "G4LeptonConstructor.hh"
  #include "G4BosonConstructor.hh"


  PhysicsList::PhysicsList():  G4VModularPhysicsList()
  {
  SetVerboseLevel(1); 
   
  // EM physics: default
  fEmPhysicsList = new G4EmLivermorePhysics();
  fEmName="emlivermore";
  
  // Add Decay (je la garde en cas où on teste une source radioactive...)
  fDecPhysicsList      = new G4DecayPhysics();
  fRadDecayPhysicsList = new G4RadioactiveDecayPhysics();
  fMessenger           = new PhysicsListMessenger(this);
  }
  
  PhysicsList::~PhysicsList()
  {  
  delete fMessenger;
  delete fDecPhysicsList;
  delete fRadDecayPhysicsList;
  delete fEmPhysicsList;
  }

//-------------------------------------------------------------------------------
//                             Particle construction 
//-------------------------------------------------------------------------------

  void PhysicsList::ConstructParticle()
  {
  fDecPhysicsList -> ConstructParticle(); 
  fEmPhysicsList  -> ConstructParticle();

//[ GABRIEL JE NE SAIS PAS SI ÇA SERAIT MIEUX DE DÉFINIR AINSI, CONFUS..]
//---------
// Leptons
//---------
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();

//--------
// Bosons
//--------
  G4Gamma::GammaDefinition();
  
  //G4LeptonConstructor lepton;
  //lepton.ConstructParticle();
  //
  //G4BosonConstructor boson;
  //boson.ConstructParticle();


  }

//-------------------------------------------------------------------------------
//                            Construction des processus
//                            Activation de phénomènes particuliers
//-------------------------------------------------------------------------------

  void PhysicsList::ConstructProcess()
  {
  AddTransportation();
  fEmPhysicsList       -> ConstructProcess();
  fDecPhysicsList      -> ConstructProcess();
  fRadDecayPhysicsList -> ConstructProcess();

// *********************************************************************
// GRABRIEL, SI JE FAIS CECI, ÇA MODIFIE GRANDEMENT LES RÉSULTATS..
//
//  G4VModularPhysicsList::ConstructProcess();
//
//  // Define energy interval for loss processes
//
//  G4EmParameters* param = G4EmParameters::Instance();
//  param->SetMinEnergy(1.0*keV);  
//  param->SetMaxEnergy(10.0*GeV);
//  //param->SetNumberOfBinsPerDecade(10);
//  param->SetVerbose(2);
// *********************************************************************

// Activation de phénomènes liés à la Déexcitation
// GABRIEL, comment activer la cascade de fluoresence, STP ?

G4VAtomDeexcitation* de = new G4UAtomicDeexcitation();
G4LossTableManager::Instance()->SetAtomDeexcitation(de);
de -> SetFluo (true);             // Activation de l'émission de fluorescence
de -> SetAuger(true);             // Activation de l'émission Auger
de -> SetAugerCascade(true);      // Activation de la cascade Auger



G4EmParameters::Instance()-> SetDeexcitationIgnoreCut(true);
G4EmParameters::Instance()-> SetMinEnergy(1.0*keV);
G4EmParameters::Instance()-> SetMaxEnergy(10.0*GeV);
// G4EmParameters::Instance()-> SetBremsstrahlungTh(1.0*eV);
// G4EmParameters::Instance()-> SetPixe(true);
}

//-------------------------------------------------------------------------------
//                 Possibilité de tester d'autres bibliothèques
//-------------------------------------------------------------------------------

void PhysicsList::AddPhysicsList(const G4String& name)
{
  
  if (name == fEmName) return;

  if (name == "emstandard_opt0")
  {

    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics();

    // Print the physics list
    G4cout << "*** USED PHYSICS LIST *** <" << name << ">" 
           << G4endl;

  } 

  else if (name == "emstandard_opt1")
  {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option1();
    G4cout << "*** USED PHYSICS LIST *** <" << name << ">" 
           << G4endl;
  } 

  else if (name == "emstandard_opt2")
  {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option2();
    G4cout << "*** USED PHYSICS LIST *** <" << name << ">" 
           << G4endl;
  } 

  else if (name == "emstandard_opt3")
  {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option3();
    G4cout << "*** USED PHYSICS LIST *** <" << name << ">" 
           << G4endl;
  } 

  else if (name == "emstandard_opt4")
  {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option4();
    G4cout << "*** USED PHYSICS LIST *** <" << name << ">" 
           << G4endl;
  } 

  else if (name == "emlowphysics")
  {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmLowEPPhysics();
    G4cout << "*** USED PHYSICS LIST *** <" << name << ">" 
           << G4endl;
  } 

  else if (name == "empenelope")
  {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmPenelopePhysics();
    G4cout << "*** USED PHYSICS LIST *** <" << name << ">" 
           << G4endl;
  } 

  else if (name == "emlivermore")
  {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmLivermorePhysics();
    G4cout << "*** USED PHYSICS LIST *** <" << name << ">" 
           << G4endl;  
  } 

  else 
  {

    G4cout << "PhysicsList::AddPhysicsList : <" << name << ">"
           << " is not defined"
           << G4endl;
  }


    G4cout << "*** NOTE THAT THE PHYSICS LIST *** <" << name << ">"
           << " is activated"
           << G4endl;
}

void PhysicsList::SetCuts()
{

//-------------------------------------------------------------------------------
//                      Transport range cut
//-------------------------------------------------------------------------------
//---   
// Outil pouvant être d'intérêt pour la comparaison avec Serpent.
//---
// This is defined in range.
// This range cut value is converted threshold energies for each material 
// and for each particle type (i.e. electron, positron and gamma) so that the 
// particle with threshold energy stops (or is absorbed) after traveling the range   
// cut distance. The defaultCutValue is set to 1.0 mm by default.
// /run/setCut could be used in macro
// /run/setCutForAGivenParticle   could be used in macro
//-------------------------------------------------------------------------------

// Possibilité de faire un cut en mm (0.05 mm Valeur de l'exemple de Curiethérapie)
// On utilise la valeur la plus haute pour que tous les particules secondaires (brem...) 
// soient transportées  
   G4double defaultCutValue = 10.0 * m;

// Possibilité de faire un cut en eV pour éliminer les phénomènes secondaires
//   G4double defaultCutValue = 1.0 * keV;  // la limite de Serpent-2


   SetCutValue(defaultCutValue, "gamma");
   SetCutValue(defaultCutValue, "e-");
   SetCutValue(defaultCutValue, "e+");
  
// By default the low energy limit to produce  secondary particles is 990 eV.
// This value is correct when using the EM Standard Physics.
// When using the Low Energy Livermore this value can be 
// changed to 250 eV corresponding to the limit
// of validity of the physics models.

//-------------------------------------------------------------------------------
//       Défini les limites de transport dépendamment de la bibliothèque
//-------------------------------------------------------------------------------

// GABRIEL, En agissant ainsi, est-ce que cela affecte SetCut en la corrigeant ou non ?

// ------------------
// Livermore physics
// ------------------

//    G4double lowLimit  = 250.0  *  eV;
//    G4double highLimit = 100.0  * GeV;
//
//    G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(lowLimit,
//                                                                highLimit);
//    G4cout << "*** Limits used *** :"
//           << "\n LOWER  LIMIT :"  <<lowLimit  
//           << "\n HIGHER LIMIT :"  <<highLimit 
//           << G4endl;

// -----------------------
// Serpent physics limits
// -----------------------
   G4double lowLimit  = 1.0    * keV;
   G4double highLimit = 100.0  * MeV;

   G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(lowLimit,
                                                               highLimit);

   G4cout 
      << "************************ "
      << "\n *** Limits used *** :"
      << "\n LOWER  LIMIT :"  <<lowLimit  
      << "\n HIGHER LIMIT :"  <<highLimit 
      << "\n ************************ "
      << G4endl;



// PAS RÉUSSI À FAIRE MARCHER, CETTE BOUCLE, i.e. automatiser ce qui précède

//  if (name == "emlivermore")
//  {
//    G4double lowLimit  = 250.0  * keV;
//    G4double highLimit = 100.0  * GeV;
//
//    G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(lowLimit,
//                                                                highLimit);
//    G4cout << "*** Limits used *** :"
//           << "\n LOWER  LIMIT :"  <<lowLimit  
//           << "\n HIGHER LIMIT :"  <<highLimit 
//           << G4endl;
//  } 
//
//  else if (name == "empenelope")
//  {
//    G4double lowLimit  = 1.0  * keV;
//    G4double highLimit = 100.0  * MeV;
//
//    G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(lowLimit,
//                                                                highLimit);
//
//    G4cout << "*** Limits used *** :"
//       << "\n LOWER  LIMIT :"  <<lowLimit  
//       << "\n HIGHER LIMIT :"  <<highLimit 
//       << G4endl;
//  } 
//
//  else 
//  {
//
//    G4cout << "*** Limits used *** : Default Geant limits " 
//           << G4endl;
//  }

  // Print the cuts 
  if (verboseLevel>0) DumpCutValuesTable();

}
