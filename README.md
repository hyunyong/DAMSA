Geant4 setup and compile
```
git clone git@github.com:hyunyong/DAMSA.git -b ALPGun
mkdir DAMSA_build
cd DAMSA_build
source /cvmfs/sft.cern.ch/lcg/views/LCG_106/x86_64-el9-gcc13-dbg/setup.sh
cmake ../DAMSA
make
```
Test run
```
./ALPGun gun.mac
```
Batch job for 1000 MeV ALP
```
./makeJob.py 1000
```
