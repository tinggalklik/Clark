// Andrei Gaponenko, 2013

#ifndef MuCapProtonWindow_h
#define MuCapProtonWindow_h

#include "EventClass.h"
#include "WireCluster.h"
#include "TimeWindow.h"
#include "TDCHitWP.h"

#include "HistTDCWidth.h"
#include "HistProtonWindow.h"
#include "MuCapUVAnalysis.h"
#include "MuCapContainmentCheck.h"

#include "Math/Point2D.h"
#include "TAxis.h"
class TH1;
class TH2;

class HistogramFactory;
class DetectorGeo;
class ConfigFile;

//================================================================
class MuCapProtonWindow {
  void set_cut_bin_labels(TAxis* ax) {
    ax->SetBinLabel(1+CUT_UPSTREAM, "Upstream");
    ax->SetBinLabel(1+CUT_NOPC7, "NOPC7");
    ax->SetBinLabel(1+CUT_RANGE_GAPS, "RANGE_GAPS");
    ax->SetBinLabel(1+CUT_MAX_PLANE, "MAX_PLANE");
    ax->SetBinLabel(1+CUTS_ACCEPTED, "Accepted");
  }

public:
  enum EventCutNumber {
    CUT_UPSTREAM,
    CUT_NOPC7,
    CUT_RANGE_GAPS,
    CUT_MAX_PLANE,
    CUTS_ACCEPTED,
    CUTS_END
  };

  void init(HistogramFactory &hf, const DetectorGeo& geom, const ConfigFile &conf);

  void process(const ROOT::Math::XYPoint& muStopUV,
               const TimeWindow& protonWindowPC,
               const TimeWindow& protonWindowDC,
               const TDCHitWPPtrCollection& unassignedDCHits,
               const EventClass& evt
               );

  MuCapProtonWindow()
    : maxPlane_()
    , h_cuts_r()
    , h_cuts_p()
    , hStartPos_()
    , hStartOffset_()
    , hStartClusterSize_()
    , hLastPlane_()
    , hProtonTime_()
  {}

private :
  int maxPlane_;

  TH1 *h_cuts_r;
  TH1 *h_cuts_p;

  TH2 *hNumClusters_;

  TH2 *hStartPos_;
  TH2 *hStartOffset_; // from the muon stop position
  TH2 *hStartClusterSize_;

  TH1 *hLastPlane_;
  TH1 *hProtonTime_;

  HistTDCWidth hwidthPCProtonWin_;
  HistTDCWidth hwidthDCProtonWin_;
  MuCapUVAnalysis uvan_;
  HistProtonWindow hpw_;

  MuCapContainmentCheck rcheckProtonCandidates_;

  EventCutNumber analyze(const ROOT::Math::XYPoint& muStopUV,
                         const TimeWindow& protonWindowPC,
                         const TimeWindow& protonWindowDC,
                         const TDCHitWPPtrCollection& unassignedDCHits,
                         const EventClass& evt
                         );
};

#endif/*MuCapProtonWindow_h*/
