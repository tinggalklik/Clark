#include "ConfigFile.h"

template<class T>
void SetKey(ConfigFile &Conf, string key, const T& t)
{
	if (! Conf.keyExists( key))
	{
		Conf.add(key, t);
	}
}

void SetDefault(ConfigFile &Conf)
{
	// ================ Standard Analysis =============== //

	//	TCAPm12widthCut
	SetKey(Conf, "TCAPm12widthCut/Do", true);
	SetKey(Conf, "TCAPm12widthCut/TCAPMin", 0.0);
	SetKey(Conf, "TCAPm12widthCut/TCAPMax", 200.0);
	SetKey(Conf, "TCAPm12widthCut/m12widthMin", 0.0);
	SetKey(Conf, "TCAPm12widthCut/m12widthMax", 20000.0);

	//	EventTypeCut
	SetKey(Conf, "EventTypeCut/Do", true);
	SetKey(Conf, "EventTypeCut/Types", "1,2,6,7,10,11,21,22");
	
	//	MuLastPCut
	SetKey(Conf, "MuLastPCut/Do", true);
	SetKey(Conf, "MuLastPCut/LastPlane", 28);
	
	//	MuUVCut
	SetKey(Conf, "MuUVCut/Do", true);
	SetKey(Conf, "MuUVCut/MaxRadius", 2.5);
	
	//	DkWinTimeCut
	SetKey(Conf, "DkWinTimeCut/Do", true);
	SetKey(Conf, "DkWinTimeCut/Min", -100000.0);
	SetKey(Conf, "DkWinTimeCut/Max", 100000.0);
	
	//	NtracksCut
	SetKey(Conf, "NtracksCut/Do", true);
	
	//	IerrorCut
	SetKey(Conf, "IerrorCut/Do", true);
	SetKey(Conf, "IerrorCut/SelectIerror", "0");
	
	//	StartStopCut
	SetKey(Conf, "StartStopCut/Do", true);

	//	ChargeCut
	SetKey(Conf, "ChargeCut/Do", true);
	SetKey(Conf, "ChargeCut/SelectCharge", 1);

	//	PairMatchingCut
	SetKey(Conf, "PairMatchingCut/Do", true);
	SetKey(Conf, "PairMatchingCut/MinCDA", 0.5);
	SetKey(Conf, "PairMatchingCut/MinDT", 60.0);
	SetKey(Conf, "PairMatchingCut/tolerance_abs", 1.e-4); /*cm*/
	SetKey(Conf, "PairMatchingCut/tolerance_rel", 0.);
	SetKey(Conf, "PairMatchingCut/max_iter", 100);
	
	//	DistToTargetSel
	SetKey(Conf, "DistToTargetSel/Do", true);
	
	//	Mu_eVertexSel
	SetKey(Conf, "Mu_eVertexSel/Do", true);
	SetKey(Conf, "Mu_eVertexSel/Do_mu_e_Calc-MOFIA", 0);
	
	//	DkFitTimeCut
	SetKey(Conf, "DkFitTimeCut/Do", true);
	SetKey(Conf, "DkFitTimeCut/Min", 1050.0);	// in ns
	SetKey(Conf, "DkFitTimeCut/Max", 9000.0);	// in ns
	
	//	PACTCut
	SetKey(Conf, "PACTCut/Do", 0);
	SetKey(Conf, "PACTCut/NbBins", 500);
	SetKey(Conf, "PACTCut/MaximumWidth", 500.0);	// ns
	SetKey(Conf, "PACTCut/quadrant_11", 1);
	SetKey(Conf, "PACTCut/quadrant_12", 1);
	SetKey(Conf, "PACTCut/quadrant_21", 1);
	SetKey(Conf, "PACTCut/quadrant_22", 1);
	SetKey(Conf, "PACTCut/region_11", "1.634, -5.428, -61.26, 642.3");
	SetKey(Conf, "PACTCut/region_12", "1.634, -5.428, -61.26, 642.3");
	SetKey(Conf, "PACTCut/region_21", "1.634, -5.428, -61.26, 642.3");
	SetKey(Conf, "PACTCut/region_22", "1.634, -5.428, -61.26, 642.3");
	
	//	StatusHistograms
	SetKey(Conf, "StatusHistograms/Do", false);
	SetKey(Conf, "StatusHistograms/PerWindowType", false);

	// ==================== Special Analyses ======================== //
	
	// AsymmetryPlots
	SetKey(Conf, "AsymmetryPlots/WeightedPlots", 1); // default ON
	SetKey(Conf, "AsymmetryPlots/UnweightedPlots", 0); // default OFF
	SetKey(Conf, "AsymmetryPlots/tmu", 2197.03);			// ns
	SetKey(Conf, "AsymmetryPlots/t_min", 245.28);		// ns
	SetKey(Conf, "AsymmetryPlots/t_width_min", 68.435);	// ns
	SetKey(Conf, "AsymmetryPlots/Fiducial/costh_min", 	0.50);
	SetKey(Conf, "AsymmetryPlots/Fiducial/costh_max", 	0.94);
	SetKey(Conf, "AsymmetryPlots/Fiducial/ptot_min", 	31.0);
	SetKey(Conf, "AsymmetryPlots/Fiducial/ptot_max", 	51.5);
	SetKey(Conf, "AsymmetryPlots/Fiducial/long_min", 	13.7);
	SetKey(Conf, "AsymmetryPlots/Fiducial/trans_max", 	43.0);
	SetKey(Conf, "AsymmetryPlots/Weighting", 2.718);

	
	// ================== Detector Parameters ======================== //
	SetKey(Conf, "Detector/BField",	2.0);
	SetKey(Conf, "Detector/GeometryFile",	"");	// CFM number of the file

	// ================== General Parameters ======================== //
	// Kinematic end point
	SetKey(Conf, "Parameters/KinematicPmax",		 	52.828);

	// Speed of light
	SetKey(Conf, "Parameters/c",29.979245800);	// cm/ns

	// Michel spectrum histogram
	SetKey(Conf, "Parameters/NCosThBinsMichel", 110);
	SetKey(Conf, "Parameters/NXBinsMichel", 110);
	SetKey(Conf, "Parameters/XMinMichel", 0.0);
	SetKey(Conf, "Parameters/XMaxMichel", 55.0);

	SetKey(Conf, "Parameters/MuonWinType",	1);

	SetKey(Conf, "Parameters/UpDkWinType",		"2,7,9,14");
	SetKey(Conf, "Parameters/DownDkWinType",	"3,8,10,15");
	SetKey(Conf, "Parameters/DCplanes",		"5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52");
	SetKey(Conf, "Parameters/PCplanes",		"1, 2, 3, 4, 27, 28, 29, 30, 53, 54, 55, 56");
	SetKey(Conf, "Parameters/PlaneType",	"PC,PC,PC,PC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,PC,PC,PC,PC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,DC,PC,PC,PC,PC");
	SetKey(Conf, "Parameters/DCzposition",	"-49.7924,-49.3923,-48.9923,-48.5922,-48.1921,-47.7921,-47.3920,-46.9919,-42.1920,-41.7921,-36.9923,-36.5924,-29.7941,-29.3941,-22.5960,-22.1961,-15.3980,-14.9981,-10.1987, -9.7988, -4.9995, -4.5995,  4.5998,  4.9998,  9.7994, 10.1993, 14.9976, 15.3976, 22.1960, 22.5959, 29.3943, 29.7942, 36.5927, 36.9926, 41.7924, 42.1924, 46.9924, 47.3923, 47.7922, 48.1922, 48.5922, 48.9922, 49.3922, 49.7922");
}