// Select good DIO tracks.  In case of multiple tracks prefer those
// that start closer to the target.
//
// Andrei Gaponenko, 2013

#ifndef MuCapUVAnalysis_h
#define MuCapUVAnalysis_h

#include <string>

#include "TimeWindow.h"
#include "WireCluster.h"

#include "TAxis.h"
#include "Math/Point2D.h"

class TH1;
class TH2;

class HistogramFactory;
class ConfigFile;
class EventClass;

//================================================================
class MuCapUVAnalysis {
  void set_cut_bin_labels(TAxis* ax) {
    ax->SetBinLabel(1+CUT_IERROR, "ierror");
    ax->SetBinLabel(1+CUT_CHARGE, "charge");
    ax->SetBinLabel(1+CUT_STREAM, "stream");
    ax->SetBinLabel(1+CUT_TIME, "time");
    ax->SetBinLabel(1+CUT_RADIUS, "radius");

    ax->SetBinLabel(1+CUT_COSTHETAMIN, "cos(theta) min");
    ax->SetBinLabel(1+CUT_COSTHETAMAX, "cos(theta) max");
    ax->SetBinLabel(1+CUT_PTMIN, "pt min");
    ax->SetBinLabel(1+CUT_PZMIN, "pz min");
    ax->SetBinLabel(1+CUT_PTOTMIN, "ptot min");
    ax->SetBinLabel(1+CUT_PTOTMAX, "ptot max");

    ax->SetBinLabel(1+CUT_TRACK_MUON_OFFSET, "drmu");
    ax->SetBinLabel(1+CUTS_ACCEPTED, "Accepted");
  }

public:
  enum CutNumber {
    CUT_IERROR,
    CUT_CHARGE,
    CUT_STREAM,
    CUT_TIME,
    CUT_RADIUS,
    CUT_COSTHETAMIN,
    CUT_COSTHETAMAX,
    CUT_PTMIN,
    CUT_PZMIN,
    CUT_PTOTMIN,
    CUT_PTOTMAX,
    CUT_TRACK_MUON_OFFSET,
    CUTS_ACCEPTED,
    CUTS_END
  };

  void init(const std::string& hdir,
            HistogramFactory &hf,
            const ConfigFile &conf,
            TimeWindow::StreamType cutStream,
            double cutTrackMinTime);

  // Returns the index of an accepted track in the event, or -1
  int process(const EventClass& evt, const ROOT::Math::XYPoint& muStopUV);

  MuCapUVAnalysis()
    : cutCharge_()
    , cutTrackMinTime_()
    , cutTrackRmax_()
    , cutCosThetaMin_()
    , cutCosThetaMax_()
    , cutPtMin_()
    , cutPzMin_()
    , cutPtotMin_()
    , cutPtotMax_()
    , cutTrackMuonOffset_()

    , h_cuts_r()
    , h_cuts_p()

    , trackTime_()
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

    , hNumTracks_()
  {}

private :
  int cutCharge_;
  TimeWindow::StreamType cutStream_;
  double cutTrackMinTime_;
  double cutTrackRmax_;
  double cutCosThetaMin_;
  double cutCosThetaMax_;
  double cutPtMin_;
  double cutPzMin_;
  double cutPtotMin_;
  double cutPtotMax_;
  double cutTrackMuonOffset_;

  TH1 *h_cuts_r;
  TH1 *h_cuts_p;

  TH1 *trackTime_;

  TH2 *trackRL_;
  TH2 *costhVsPtot_;

  TH2 *hStartStop_;
  TH1 *trackz_;
  TH2 *trackMuonOffset_;
  TH1 *trackMuondr_;

  TH2 *helixCenterUV_;

  TH2 *final_trackRL_; // radius and wavelength
  TH2 *final_costhVsPtot_;
  TH2 *final_u0v0_;
  TH1 *final_trackROut_;
  TH1 *final_trackTime_;

  TH1 *hNumTracks_;

  // true iff the track passed the cuts
  bool processTrack(int itrack,
                    const EventClass& evt,
                    const ROOT::Math::XYPoint& muStopUV
                    );

  CutNumber analyzeTrack(int itrack,
                         const EventClass& evt,
                         const ROOT::Math::XYPoint& muStopUV
                         );
};

#endif/*MuCapUVAnalysis_h*/
