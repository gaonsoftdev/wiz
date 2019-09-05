/* -------------------------------------------------------------------- */
/*      Shape types (nSHPType)                                          */
/* -------------------------------------------------------------------- */
#define SHPT_NULL	0
#define SHPT_POINT	1
#define SHPT_ARC	3
#define SHPT_POLYGON	5
#define SHPT_MULTIPOINT	8
#define SHPT_POINTZ	11
#define SHPT_ARCZ	13
#define SHPT_POLYGONZ	15
#define SHPT_MULTIPOINTZ 18
#define SHPT_POINTM	21
#define SHPT_ARCM	23
#define SHPT_POLYGONM	25
#define SHPT_MULTIPOINTM 28
#define SHPT_MULTIPATCH 31

#define DEFAULT_PADDING 10

/* -------------------------------------------------------------------- */
/*      Minimum Bounding Rectangle                                      */
/* -------------------------------------------------------------------- */
typedef struct
{
	double	xmin;
	double	ymin;
	double	xmax;
	double	ymax;
} MBR;

/* -------------------------------------------------------------------- */
/*      Point Struct                                                    */
/* -------------------------------------------------------------------- */
typedef struct {
	double x;
	double y;
} GeoPoint;

/* -------------------------------------------------------------------- */
/*      PoliLine & Polygon                                              */
/* -------------------------------------------------------------------- */
typedef struct {
	MBR			m_MBR;
	int			m_nNumParts;
	int			m_nNumPoints;
	int*		m_pParts;
	GeoPoint*	m_pPoints;
} PolyObject;


// User data struct
/* -------------------------------------------------------------------- */
/*      Network component                                               */
/* -------------------------------------------------------------------- */
typedef struct {
	int			m_ID;
	int			m_classID;
	double		m_Y; // 위도-latitude(Y)
	double		m_X; // 경도-longitude(X)
	int			m_linkID;
	long		m_reconstCost; // Reconstruction cost
	char*		m_soilType;
	double		m_fundPeriod; // Fundamental period(sec)
} NetworkComponent;

/* -------------------------------------------------------------------- */
/*      Fragility curve parameter                                       */
/* -------------------------------------------------------------------- */
typedef struct {
	int			m_classID;
	double		m_DS1IMm;
	double		m_DS2IMm;
	double		m_DS3IMm;
	double		m_DS4IMm;
	double		m_DS1Beta;
	double		m_DS2Beta;
	double		m_DS3Beta;
	double		m_DS4Beta;
} FragilityCurveParam;