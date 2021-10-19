#ifndef _TEMPLATE_DATA_INT_NORMALIZED_64_4_H_
#define _TEMPLATE_DATA_INT_NORMALIZED_64_4_H_

namespace TemplateDataIntNormalized64_4
{
	int circleCCWPoints[] = 
	{-1639,4,-1786,397,-1688,807,-1475,1167,-1147,1429,-787,1659,-410,1839,-17,2003,408,2068,834,2052,1244,1954,1571,1692,1817,1347,1948,938,1997,512,2014,86,1981,-339,1834,-732,1686,-1125,1440,-1470,1129,-1764,752,-1945,343,-2027,-66,-1961,-476,-1846,-885,-1732,-1278,-1584,-1655,-1388,-1966,-1093,-2081,-683,-1917,-290,-1737,37};

	int vPoints[] = 
	{-2544,-1,-2313,-100,-2050,30,-1787,162,-1524,294,-1261,409,-1014,557,-751,656,-487,771,-224,869,38,1001,318,1100,597,1198,877,1248,1140,1346,1420,1429,1551,1264,1403,1017,1321,738,1206,475,1074,211,910,-34,762,-281,630,-544,466,-791,334,-1054,202,-1317,71,-1581,5,-1860,-60,-2140,-126,-2420,-175,-2666};

	int pigTailPoints[] = 
	{-2360,-5,-2064,226,-1735,391,-1373,440,-1011,424,-650,325,-304,176,24,11,336,-186,633,-401,896,-665,1110,-962,1241,-1309,1225,-1673,1044,-1970,682,-1953,336,-1788,40,-1574,-222,-1309,-436,-1012,-518,-649,-551,-269,-551,110,-469,473,-386,837,-172,1134,73,1415,369,1646,682,1861,1011,2009,1373,2125,1735,2125};

	int circleCWPoints[] = 
	{-963,4,-1096,-375,-1162,-772,-1063,-1152,-831,-1465,-499,-1697,-118,-1845,263,-1994,661,-1994,992,-1796,1224,-1465,1390,-1102,1506,-706,1589,-309,1606,103,1589,516,1573,912,1490,1308,1324,1672,1092,1985,727,2101,312,2068,-51,1886,-366,1639,-648,1341,-864,1011,-980,615,-1030,218,-1328,-12,-1726,-128,-2108,-227,-2489,-342};

	int nSamplePoints[] = { 64, 64, 64, 64 };

	int * samplePoints[] = 
	{ 
		circleCCWPoints, vPoints, pigTailPoints, circleCWPoints	
	};

	const char * sampleNames[] = 
	{
		"circleCCW", "v", "pigTail", "circleCW"
	};
	
	int nTemplates = 4;

	bool samplesNormalized = true;	
}

#endif
