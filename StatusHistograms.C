//////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// Anthony Hillairet, April 2008
///
//////////////////////////////////////////////////////////////////////////////////////////////////////

// Includes here 

class StatusHistograms : public ModuleClass{
	public :
		StatusHistograms()		{};
		StatusHistograms(string N, string T)		{Name = N; Title = T;};
		~StatusHistograms()		{};
		bool	Init(EventClass &E, HistogramFactory &H, ConfigFile &Conf, log4cpp::Category *TmpLog) ;
		bool	Process(EventClass &E, HistogramFactory &H);

	private :
		log4cpp::Category *Log;

		string Name;
		string Title;

		bool PerWindowType;
		bool PhiQuadrants;

		double tec_x;
		double tec_y;
		double tec_tanthx;
		double tec_tanthy;

};

bool StatusHistograms::Init(EventClass &E, HistogramFactory &H, ConfigFile &Conf, log4cpp::Category *TmpLog)
{
	Log	= TmpLog;

	if (not Conf.read<bool>("StatusHistograms/Do"))
	{
		Log->info( "StatusHistograms %s turned OFF",Title.c_str());
		return false ;
	}
	Log->info( "Register Status Histograms %s", Title.c_str());

	string N = Name;
	string T = Title;

	//	 --------- Parameters initialization ---------		//
	PerWindowType	= Conf.read<bool>("StatusHistograms/PerWindowType");
	PhiQuadrants	= Conf.read<bool>("PhiQuadrantSpectra/Do");

	//	 --------- Histograms initialization ---------		//
	//______________________ Event Branch __________________________ //
	H.DefineTH1D( "Status",	"EvtType_"+N,	"Event Type "+T+";Event type",36, -0.5,35.5);

	H.DefineTH2D( "Status",	"m12VsTCAP_"+N,	"m12 vs TCAP "+T+";TCAP [ns];m12 width [ns]",200, 0,200,300, 0, 30000);
	H.DefineTH1D( "Status",	"NumWin_"+N,	"Number of windows "+T,11, -0.5,10.5);
	H.DefineTH1D( "Status",	"NumTrk_"+N,	"Number of tracks "+T,11, -0.5,10.5);

	//_________________________ TEC ________________________ //
	if ( E.Exists("tanthxy") && E.Exists("xy0") )
	{
		H.DefineTH2D( "Status","TECyvsx_"+N, "TEC y vs x "+T+";x [cm];y [cm]",160, -4,4,160, -4,4);
		H.DefineTH2D( "Status","TECtanthyvstanthx_"+N, "TEC tanthy vs tanthx "+T+";tan theta_x;tan theta_y",200, -0.2,0.2, 200, -0.2,0.2);
	}

	//_________________________ Windows ________________________ //
	H.DefineTH1D( "Status",	"Win_Type_"+N,	"Window Type "+T,22, -0.5,21.5);
	H.DefineTH2D( "Status",	"Win_FlagVsType_"+N, "Windowing flag versus window type "+T,22, -0.5,21.5, 31, -0.5,30.5);
	H.DefineTH2D( "Status", "Win_PCWidthAvg_"+N, "Average PC width vs window type "+T+";Window type;Average PC width [ns]",22,-0.5,21.5,400,0,400);
	H.DefineTH2D( "Status", "Win_PCtof_"+N, "PC time of flight vs window type "+T+";Window type;PC time of flight [ns]",22,-0.5,21.5,300,-150,150);
	H.DefineTH2D( "Status",	"Win_Time_Vs_WinType_"+N,	"Window time vs window type "+T+";Window time [ns]",22,-0.5,21.5,320, -6000,10000);
	if (PerWindowType)
	{
		string wtstr;
		for (int W = 0; W < 22; W++)
		{
			wtstr	= IntToStr(W);
			H.DefineTH2D( "Status",	"Win_uvfirst_PerWinType_"+wtstr+"_"+N,	"First plane v vs u position for the window type "+wtstr+" "+T+";u position [cm];v position [cm]",80, -16.0,16.0,80, -16.0,16.0);
			H.DefineTH2D( "Status",	"Win_uvlast_PerWinType_"+wtstr+"_"+N,	"Last plane v vs u position for the window type "+wtstr+" "+T+";u position [cm];v position [cm]",80, -16.0,16.0,80, -16.0,16.0);
			H.DefineTH1D( "Status",	"Win_pfirst_PerWinType_"+wtstr+"_"+N,	"First plane for the window type "+wtstr+" "+T, 56, 0.5,56.5);
			H.DefineTH2D( "Status",	"Win_pupvlast_PerWinType_"+wtstr+"_"+N,	"Last planes v vs last plane u for the window type "+wtstr+" "+T,56, 0.5,56.5, 56, 0.5,56.5);
		}
	}

	//___________________ Helix fit tracks ______________________ //
	H.DefineTH1D( "Status",	"DkFitTime_"+N,	"Decay fit time for selected the tracks "+T,10000, 0.,10000.);
	H.DefineTH1D( "Status",	"DkFitTime_US_"+N,	"Decay fit time for selected US tracks "+T,10000, 0.,10000.);
	H.DefineTH1D( "Status",	"DkFitTime_DS_"+N,	"Decay fit time for selected DS tracks "+T,10000, 0.,10000.);

	H.DefineTH1D( "Status",	"Chi2_"+N,		"Reduced Chisquare of the selected tracks "+T,1000, 0,10);
	H.DefineTH1D( "Status",	"Chi2Full_"+N,	"Reduced Chisquare of the selected tracks "+T,1000, 0,1000);

	H.DefineTH1D( "Status",	"Ndof_"+N,		"Number of degrees of freedom of the selected tracks "+T,1000, 0,10);
	H.DefineTH1D( "Status",	"NdofFull_"+N,	"Number of degrees of freedom of the selected tracks "+T,1000, 0,1000);

	//___________________ Quadrant study ______________________ //
	if ( PhiQuadrants)
	{
		H.DefineTH2D("Status","UvsV_helixcenter_"+N, "UV position of the center of the helix "+T, 320, -16.,16., 320, -16.,16.);
		H.DefineTH2D("Status","UvsV_helixcenter_US_"+N, "UV position of the center of the helix "+T+", upstream tracks", 320, -16.,16., 320, -16.,16.);
		H.DefineTH2D("Status","UvsV_helixcenter_DS_"+N, "UV position of the center of the helix "+T+", downstream tracks", 320, -16.,16., 320, -16.,16.);
		H.DefineTH2D("Status","PtVsPhi_"+N,		"Transverse momentum versus target phi "+T,16,-1.*M_PI,M_PI,1200,10,50);
		H.DefineTH2D("Status","Chi2VsPhi_"+N,	"chisquare versus target phi "+T,16,-1.*M_PI,M_PI,1000,0,10);
	}

	return true;
}

bool StatusHistograms::Process(EventClass &E, HistogramFactory &H)
{
	//_________ Event Branch ________//
	H.Fill("EvtType_"+Name,E.type);
	H.Fill("NumWin_"+Name,E.nwin);
	H.Fill("NumTrk_"+Name,E.ntr);

	for ( int i = 0; i < 3; i++)
		H.Fill("m12VsTCAP_"+Name,E.cptime[i], E.m12width);

	//_________ TEC ________//
	if ( E.Exists("tanthxy") && E.Exists("xy0") )
	{
		tec_tanthx = E.tanthxy[0];
		tec_tanthy = E.tanthxy[1];
		tec_x = tec_tanthx*(-191.944)+E.xy0[0];
		tec_y = tec_tanthy*(-191.944)+E.xy0[1];
		H.Fill("TECyvsx_"+Name,tec_x,tec_y);
		H.Fill("TECtanthyvstanthx_"+Name,tec_tanthx,tec_tanthy);
	}

	//_________ Windows ________//
	string wtstr;
	for ( int w = 0; w < E.nwin; w++)
	{
		wtstr	= E.win_type[w];
		H.Fill("Win_Type_"+Name,E.win_type[w]);
		H.Fill("Win_FlagVsType_"+Name,E.win_type[w],E.win_flag[w]);
		H.Fill("Win_PCWidthAvg_"+Name,E.win_type[w],E.win_pcwidthavg[w]);
		H.Fill("Win_PCtof_"+Name,E.win_type[w],E.win_pctof[w]);
		H.Fill("Win_Time_Vs_WinType_"+Name,E.win_type[w],E.win_time[w]);
		if (PerWindowType)
		{
			H.Fill("Win_uvfirst_PerWinType_"+wtstr+"_"+Name,E.win_ufirst[w],E.win_vfirst[w]);
			H.Fill("Win_uvlast_PerWinType_"+wtstr+"_"+Name,E.win_ulast[w],E.win_vlast[w]);
			H.Fill("Win_pfirst_PerWinType_"+wtstr+"_"+Name,E.win_pfirst[w]);
			H.Fill("Win_pupvlast_PerWinType_"+wtstr+"_"+Name,E.win_pulast[w],E.win_pvlast[w]);
		}
	}

	//_________ Helix fit tracks ________//

	for(vector<int>::iterator t = E.seltrack.begin(); t != E.seltrack.end(); t++)
	{
		if (fabs(E.hefit_z[*t])<5 && E.ptot[*t]>32.)
		{
			H.Fill("DkFitTime_"+Name, E.hefit_time[*t] );
			if (E.hefit_pz[*t]>0)
			{
				H.Fill("DkFitTime_DS_"+Name, E.hefit_time[*t] );
			}
			else {
				H.Fill("DkFitTime_US_"+Name, E.hefit_time[*t] );
			}
		}
		if (E.hefit_ndof[*t] > 0)
		{
			H.Fill("Chi2_"+Name,				E.hefit_chi2[*t] / E.hefit_ndof[*t]);
			H.Fill("Chi2Full_"+Name,			E.hefit_chi2[*t] / E.hefit_ndof[*t]);
			H.Fill("Ndof_"+Name,				E.hefit_ndof[*t]);
			H.Fill("NdofFull_"+Name,			E.hefit_ndof[*t]);
		}
		if ( PhiQuadrants )
		{
			H.Fill("UvsV_helixcenter_"+Name,	E.hefit_ucenter[*t],E.hefit_vcenter[*t]);
			if (E.is_upstreamdk)
				H.Fill("UvsV_helixcenter_US_"+Name,	E.hefit_ucenter[*t],E.hefit_vcenter[*t]);
			else
				H.Fill("UvsV_helixcenter_DS_"+Name,	E.hefit_ucenter[*t],E.hefit_vcenter[*t]);
			H.Fill("PtVsPhi_"+Name,				E.hefit_phiquad[*t], E.pt[*t]);
			H.Fill("Chi2VsPhi_"+Name,			E.hefit_phiquad[*t], E.hefit_chi2[*t]/E.hefit_ndof[*t]);
		}
	}

	return true;
}

