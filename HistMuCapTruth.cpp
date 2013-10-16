// Andrei Gaponenko, 2013

#include "HistMuCapTruth.h"

#include <cmath>
#include <sstream>
#include <stdexcept>

#include "TH2.h"

#include "HistogramFactory.h"
#include "ConfigFile.h"
#include "MuCapUtilities.h"

//================================================================
void HistMuCapTruth::init(HistogramFactory &hf,
                          const std::string& hdir,
                          const ConfigFile &conf)
{
  static const double PI = 4.*atan(1.);
  hptot_ = hf.DefineTH1D(hdir, "ptot", "MC ptot", 200, 0., 200.);
  hek_ = hf.DefineTH1D(hdir, "ek", "MC Ek", 200, 0., 50.);
  hphi_ = hf.DefineTH1D(hdir, "phi", "MC momentum phi", 100, -PI, +PI);
  hpcos_ = hf.DefineTH2D(hdir, "cosVsPtos", "MC cosTheta vs ptot", 200, 0., 200., 100, -1., 1.);
  hpcos_->SetOption("colz");

  hVUend_ = hf.DefineTH2D(hdir, "uvend", "V vs U primary end vtx for |Zend|<60 cm", 600, -30., 30., 600, -30., 30.);
  hVUend_->SetOption("box");

  hRZend_ = hf.DefineTH2D(hdir, "rzend", "Primary end vtx R vs Z", 1200, -60., 60., 300, 0., 30.);
  hRZend_->SetOption("colz");

  hRendVsPstart_ = hf.DefineTH2D(hdir, "rpstart", "End R vs start ptot for |Zend|<60 cm", 200, 0., 200., 300, 0., 30.);
  hRendVsPstart_->SetOption("colz");

  hZendVsPstart_ = hf.DefineTH2D(hdir, "zpstart", "End Z vs start ptot", 200, 0., 200., 1200, -60., 60.);
  hZendVsPstart_->SetOption("colz");
}

//================================================================
void HistMuCapTruth::fill(const EventClass& evt) {
  const unsigned imcvtx = evt.iCaptureMcVtxStart;
  const unsigned imctrk = evt.iCaptureMcTrk;

  hptot_->Fill(evt.mcvertex_ptot[imcvtx]);
  hek_->Fill(MuCapUtilities::kineticEnergy(evt.mctrack_pid[imctrk], evt.mcvertex_ptot[imcvtx]));
  hphi_->Fill(evt.mcvertex_phimuv[imcvtx]);
  hpcos_->Fill(evt.mcvertex_ptot[imcvtx], evt.mcvertex_costh[imcvtx]);

  const double endR = std::sqrt(std::pow(evt.mcvertex_vu[1], 2) + std::pow(evt.mcvertex_vv[1], 2));
  hRZend_->Fill(evt.mcvertex_vz[1], endR);

  if(std::abs(evt.mcvertex_vz[1]) < 60.) {
    hVUend_->Fill(evt.mcvertex_vu[1], evt.mcvertex_vv[1]);
    hRendVsPstart_->Fill(evt.mcvertex_ptot[imcvtx], endR);
  }

  hZendVsPstart_->Fill(evt.mcvertex_ptot[imcvtx], evt.mcvertex_vz[1]);
}

//================================================================
