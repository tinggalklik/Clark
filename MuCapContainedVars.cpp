#include "MuCapContainedVars.h"

#include "EventClass.h"
#include "WireCluster.h"
#include "MuCapUtilities.h"

namespace MuCapContainedVars {

  //================================================================
  std::string RangeCosVsP::xtitle_("ptot [MeV/c]");
  std::string RangeCosVsP::ytitle_("(extplane-28)/|cos(theta)|");


  void RangeCosVsP::init(const std::string& hdir,
                         HistogramFactory &hf,
                         const DetectorGeo& geom,
                         const ConfigFile& conf)
  {
    ccut_.init(hdir, hf, geom, conf);
  }

  Result RangeCosVsP::compute(const EventClass& evt, int iPosTrack, const ClustersByPlane& protonGlobalClusters) {
    int lastPlane=0;
    const bool contained = ccut_.contained(evt, iPosTrack, protonGlobalClusters, &lastPlane);
    double ptot = 0.;
    double rangePIDVar = 0.;

    if(contained) {
      ptot = evt.ptot[iPosTrack];
      rangePIDVar = (lastPlane-28)/std::abs(evt.costh[iPosTrack]);
    }

    return Result(ptot, rangePIDVar, contained);
  }

  //================================================================
  std::string RangeVsP::xtitle_("ptot [MeV/c]");
  std::string RangeVsP::ytitle_("(extplane-28)");

  void RangeVsP::init(const std::string& hdir,
                         HistogramFactory &hf,
                         const DetectorGeo& geom,
                         const ConfigFile& conf)
  {
    ccut_.init(hdir, hf, geom, conf);
  }

  Result RangeVsP::compute(const EventClass& evt, int iPosTrack, const ClustersByPlane& protonGlobalClusters) {
    int lastPlane = 0;
    const bool contained = ccut_.contained(evt, iPosTrack, protonGlobalClusters, &lastPlane);
    double ptot = 0.;
    double rangePIDVar = 0.;

    if(contained) {
      ptot = evt.ptot[iPosTrack];
      rangePIDVar = (lastPlane-28);
    }

    return Result(ptot, rangePIDVar, contained);
  }

  //================================================================
  std::string RangeVsPz::xtitle_("pz [MeV/c]");
  std::string RangeVsPz::ytitle_("(extplane-28)");


  void RangeVsPz::init(const std::string& hdir,
                         HistogramFactory &hf,
                         const DetectorGeo& geom,
                         const ConfigFile& conf)
  {
    ccut_.init(hdir, hf, geom, conf);
  }

  Result RangeVsPz::compute(const EventClass& evt, int iPosTrack, const ClustersByPlane& protonGlobalClusters) {
    int lastPlane = 0;
    const bool contained = ccut_.contained(evt, iPosTrack, protonGlobalClusters, &lastPlane);
    double pz = 0.;
    double rangePIDVar = 0.;

    if(contained) {
      pz = evt.ptot[iPosTrack] * evt.costh[iPosTrack];
      rangePIDVar = (lastPlane-28);
    }

    return Result(pz, rangePIDVar, contained);
  }

  //================================================================

}
