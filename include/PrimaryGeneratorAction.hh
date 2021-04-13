//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// -------------------------------------------------------------------
// -------------------------------------------------------------------

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1


#include "G4ParticleGun.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:

    PrimaryGeneratorAction();

    ~PrimaryGeneratorAction();

    void GeneratePrimaries(G4Event *);

    G4double InverseCumul();

private:

    G4ParticleGun *fParticleGun;
    const std::vector<G4double> sr90Energies = std::vector<G4double>{
            0.00010, 0.00011, 0.00012, 0.00013, 0.00014, 0.00015, 0.00016, 0.00018, 0.00020, 0.00022, 0.00024, 0.00026,
            0.00028, 0.00030, 0.00032, 0.00036, 0.00040, 0.00045, 0.00050, 0.00055, 0.00060, 0.00065, 0.00070, 0.00075,
            0.00080, 0.00085, 0.00090, 0.00100, 0.00110, 0.00120, 0.00130, 0.00140, 0.00150, 0.00160, 0.00180, 0.00200,
            0.00220, 0.00240, 0.00260, 0.00280, 0.00300, 0.00320, 0.00360, 0.00400, 0.00450, 0.00500, 0.00550, 0.00600,
            0.00650, 0.00700, 0.00750, 0.00800, 0.00850, 0.00900, 0.01000, 0.01100, 0.01200, 0.01300, 0.01400, 0.01500,
            0.01600, 0.01800, 0.02000, 0.02200, 0.02400, 0.02600, 0.02800, 0.03000, 0.03200, 0.03600, 0.04000, 0.04500,
            0.05000, 0.05500, 0.06000, 0.06500, 0.07000, 0.07500, 0.08000, 0.08500, 0.09000, 0.10000, 0.11000, 0.12000,
            0.13000, 0.14000, 0.15000, 0.16000, 0.18000, 0.20000, 0.22000, 0.24000, 0.26000, 0.28000, 0.30000, 0.32000,
            0.36000, 0.40000, 0.45000, 0.50000


    };

    const std::vector<G4double> sr90Probability = std::vector<G4double>{
            2.949E+00, 2.949E+00, 2.949E+00, 2.949E+00, 2.948E+00, 2.948E+00, 2.948E+00, 2.948E+00, 2.947E+00,
            2.947E+00, 2.947E+00, 2.947E+00, 2.946E+00, 2.946E+00, 2.946E+00, 2.945E+00, 2.944E+00, 2.944E+00,
            2.943E+00, 2.942E+00, 2.941E+00, 2.941E+00, 2.940E+00, 2.939E+00, 2.938E+00, 2.938E+00, 2.937E+00,
            2.935E+00, 2.934E+00, 2.932E+00, 2.931E+00, 2.929E+00, 2.928E+00, 2.926E+00, 2.923E+00, 2.920E+00,
            2.917E+00, 2.914E+00, 2.911E+00, 2.908E+00, 2.905E+00, 2.902E+00, 2.896E+00, 2.890E+00, 2.882E+00,
            2.875E+00, 2.867E+00, 2.866E+00, 2.864E+00, 2.863E+00, 2.861E+00, 2.860E+00, 2.859E+00, 2.857E+00,
            2.855E+00, 2.852E+00, 2.849E+00, 2.846E+00, 2.843E+00, 2.841E+00, 2.838E+00, 2.833E+00, 2.827E+00,
            2.822E+00, 2.818E+00, 2.813E+00, 2.809E+00, 2.804E+00, 2.800E+00, 2.793E+00, 2.786E+00, 2.777E+00,
            2.770E+00, 2.763E+00, 2.756E+00, 2.750E+00, 2.743E+00, 2.737E+00, 2.731E+00, 2.725E+00, 2.719E+00,
            2.706E+00, 2.693E+00, 2.679E+00, 2.663E+00, 2.647E+00, 2.629E+00, 2.609E+00, 2.563E+00, 2.508E+00,
            2.441E+00, 2.361E+00, 2.267E+00, 2.157E+00, 2.031E+00, 1.887E+00, 1.549E+00, 1.155E+00, 6.310E-01, 1.821E-01
    };
    std::vector<G4double> sr90Dist;
};

#endif
