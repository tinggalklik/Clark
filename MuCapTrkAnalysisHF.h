// A track-based capture analysis that used helix fit results as inputs
//
// Andrei Gaponenko, 2013

#ifndef MuCapTrkAnalysisHF_h
#define MuCapTrkAnalysisHF_h

#include <string>

#include "TimeWindow.h"
#include "WireCluster.h"
#include "HistMuCapTruth.h"
#include "RecoResMuCapTrk.h"

#include "TAxis.h"
#include "Math/Point2D.h"

class TH1;
class TH2;

class HistogramFactory;
class ConfigFile;
class EventClass;

//================================================================
class MuCapTrkAnalysisHF {
  void set_cut_bin_labels(TAxis* ax) {
    ax->SetBinLabel(1+CUT_IERROR, "ierror");
    ax->SetBinLabel(1+CUT_CHARGE, "charge");
    ax->SetBinLabel(1+CUT_STREAM, "stream");
    ax->SetBinLabel(1+CUT_STARTPLANE, "startPlane");
    ax->SetBinLabel(1+CUT_TIME, "time");
    ax->SetBinLabel(1+CUT_RADIUS, "radius");

    ax->SetBinLabel(1+CUT_COSTHETAMIN, "cos(theta) min");
    ax->SetBinLabel(1+CUT_COSTHETAMAX, "cos(theta) max");
    ax->SetBinLabel(1+CUT_PTMIN, "pt min");
    ax->SetBinLabel(1+CUT_PZMIN, "pz min");
    ax->SetBinLabel(1+CUT_PTOTMIN, "ptot min");
    ax->SetBinLabel(1+CUT_PTOTMAX, "ptot max");
    ax->SetBinLabel(1+CUT_CHI2,     "chi2");

    ax->SetBinLabel(1+CUT_TRACK_MUON_OFFSET, "drmu");
    ax->SetBinLabel(1+CUTS_ACCEPTED, "Accepted");
  }

public:
  enum CutNumber {
    CUT_IERROR,
    CUT_CHARGE,
    CUT_STREAM,
    CUT_STARTPLANE,
    CUT_TIME,
    CUT_RADIUS,
    CUT_COSTHETAMIN,
    CUT_COSTHETAMAX,
    CUT_PTMIN,
    CUT_PZMIN,
    CUT_PTOTMIN,
    CUT_PTOTMAX,
    CUT_CHI2,
    CUT_TRACK_MUON_OFFSET,
    CUTS_ACCEPTED,
    CUTS_END
  };

  void init(const std::string& hdir,
            HistogramFactory &hf,
            const ConfigFile &conf,
            TimeWindow::StreamType cutStream,
            double cutTrackMinTime,
            RecoResMuCapTrk *result);

  // Returns the index of an accepted track in the event, or -1
  int process(const EventClass& evt,
              const ROOT::Math::XYPoint& muStopUV,
              const TimeWindow& protonWin);

  MuCapTrkAnalysisHF()
    : doMCTruth_(false)
    , result_(nullptr)
    , cutCharge_()
    , cutStartPlane_()
    , cutTrackMinTime_()
    , cutTrackRmax_()
    , cutCosThetaMin_()
    , cutCosThetaMax_()
    , cutPtMin_()
    , cutPzMin_()
    , cutPtotMin_()
    , cutPtotMax_()
    , cutChi2_()
    , cutTrackMuonOffset_()

    , h_cuts_r()
    , h_cuts_p()

    , trackTime_()
    , trackWinTime_()
    , trackRL_()
    , costhVsPtot_()

    , hStartStop_()
    , trackz_()

    , trackMuonOffset_()
    , trackMuondr_()

    , helixCenterUV_()

    , final_trackRL_()
    , final_costhVsPtot_()
    , final_u0v0_()
    , final_trackROut_()
    , final_trackTime_()
    , final_trackWinTime_()

    , hNumTracks_()
  {}

private :
  bool doMCTruth_;
  RecoResMuCapTrk *result_;
  int cutCharge_;
  TimeWindow::StreamType cutStream_;
  int cutStartPlane_;
  double cutTrackMinTime_;
  double cutTrackRmax_;
  double cutCosThetaMin_;
  double cutCosThetaMax_;
  double cutPtMin_;
  double cutPzMin_;
  double cutPtotMin_;
  double cutPtotMax_;
  double cutChi2_;
  double cutTrackMuonOffset_;

  TH1 *h_cuts_r;
  TH1 *h_cuts_p;

  TH1 *trackTime_;
  TH1 *trackWinTime_;

  TH2 *trackRL_;
  TH2 *costhVsPtot_;

  TH2 *hStartStop_;
  TH1 *trackz_;
  TH1 *trackChi2_;
  TH2 *trackMuonOffset_;
  TH1 *trackMuondr_;

  TH2 *helixCenterUV_;

  TH2 *final_trackRL_; // radius and wavelength
  TH2 *final_costhVsPtot_;
  TH2 *final_u0v0_;
  TH1 *final_trackROut_;
  TH1 *final_trackTime_;
  TH1 *final_trackWinTime_;

  TH1 *hNumTracks_;

  HistMuCapTruth htruthAccepted_;

  // true iff the track passed the cuts
  bool processTrack(int itrack,
                    const EventClass& evt,
                    const ROOT::Math::XYPoint& muStopUV,
                    const TimeWindow& protonWin);

  CutNumber analyzeTrack(int itrack,
                         const EventClass& evt,
                         const ROOT::Math::XYPoint& muStopUV,
                         const TimeWindow& protonWin);
};

#endif/*MuCapTrkAnalysisHF_h*/
