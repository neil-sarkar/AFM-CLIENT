#include "constants.h"

const QString ADC_Read = "ADC_Read";
const QString AFM_Begin_Auto_Approach = "AFM_Begin_Auto_Approach";
const QString AFM_Calibrate = "AFM_Calibrate";
const QString AFM_Generate_Force_Curve = "AFM_Generate_Force_Curve";
const QString AFM_Get_Auto_Approach_Status = "AFM_Get_Auto_Approach_Status";
const QString AFM_Read_Signal_Phase_Offset = "AFM_Read_Signal_Phase_Offset";
const QString AFM_Set_Dac_Table = "AFM_Set_Dac_Table";
const QString AFM_Set_Scan_Parameters = "AFM_Set_Scan_Parameters";
const QString AFM_Set_Signal_Generation = "AFM_Set_Signal_Generation";
const QString AFM_Start_Frequency_Sweep_AD5932 = "AFM_Start_Frequency_Sweep_AD5932";
const QString AFM_Start_Frequency_Sweep_AD9837 = "AFM_Start_Frequency_Sweep_AD9837";
const QString AFM_Start_Scan = "AFM_Start_Scan";
const QString AFM_Step_Scan = "AFM_Step_Scan";
const QString AFM_Stop_Auto_Approach = "AFM_Stop_Auto_Approach";
const QString DAC_Read = "DAC_Read";
const QString DAC_Set_Max_Value = "DAC_Set_Max_Value";
const QString DAC_Write = "DAC_Write";
const QString DDS_Set_AD5932 = "DDS_Set_AD5932";
const QString DDS_Set_AD9837 = "DDS_Set_AD9837";
const QString Motor_Run_Continuous = "Motor_Run_Continuous";
const QString Motor_Set_Direction = "Motor_Set_Direction";
const QString Motor_Set_Microstep = "Motor_Set_Microstep";
const QString Motor_Set_Single_Step = "Motor_Set_Single_Step";
const QString Motor_Set_Speed = "Motor_Set_Speed";
const QString Motor_Set_State_Asleep = "Motor_Set_State_Asleep";
const QString Motor_Set_State_Awake = "Motor_Set_State_Awake";
const QString Motor_Stop_Continuous = "Motor_Stop_Continuous";
const QString PGA_Set = "PGA_Set";
const QString PID_Disable = "PID_Disable";
const QString PID_Enable = "PID_Enable";
const QString PID_Set_Derivative = "PID_Set_Derivative";
const QString PID_Set_Integral = "PID_Set_Integral";
const QString PID_Set_Proportional = "PID_Set_Proportional";
const QString PID_Set_Setpoint = "PID_Set_Setpoint";
const QString Stage_Set_Pulse_Step = "Stage_Set_Pulse_Step";
const QString Stage_Set_Pulse_Width = "Stage_Set_Pulse_Width";
const QString Scanner_Set_Dwell_Time = "Scanner_Set_Dwell_Time";
const QString AFM_Get_Resistances = "AFM_Get_Resistances";
const QString Scanner_Set_Num_Averages = "Scanner_Set_Num_Averages";
const QString Scanner_Set_Send_Back_Count = "Scanner_Set_Send_Back_Count";

const char Message_Delimiter = 0x0A;
const char Newline_Character = 0x0A;
const char Escape_Character = 0x10;
const char Mask_Character = 0x80;
const char AFM_Success_Response = 0x6f;
const int Special_Message_Character = 0xF2;
const int Auto_Approach_Info_Character = 0x9C;
const int Auto_Approach_Stopped_Character = 0x9B;
const int Num_Meta_Data_Bytes = 2; // tag and id are the only two bytes that are 'metadata'
const int Message_Size_Minimum = 2; // tag and id make up the minimum message
const int Set_Receive_Bytes_Error = -1;

// serial port
const QString AFM_Port_Name = "FTDI";
const int AFM_Baud_Rate = 76800;
const int AFM_Success = 0;
const int AFM_Fail = -1;

const int DAC_Table_Values[4096] = {124,139,152,164,175,186,196,206,215,224,232,240,248,256,263,270,277,284,291,297,304,310,316,322,328,334,340,345,351,356,362,367,372,377,382,387,392,397,402,407,411,416,421,425,430,434,439,443,447,452,456,460,464,468,472,476,480,484,488,492,496,500,504,508,511,515,519,523,526,530,534,537,541,544,548,551,555,558,562,565,568,572,575,579,582,585,588,592,595,598,601,605,608,611,614,617,620,623,626,629,633,636,639,642,645,648,651,653,656,659,662,665,668,671,674,677,679,682,685,688,691,693,696,699,702,704,707,710,713,715,718,721,723,726,729,731,734,736,739,742,744,747,749,752,755,757,760,762,765,767,770,772,775,777,780,782,785,787,789,792,794,797,799,802,804,806,809,811,813,816,818,820,823,825,827,830,832,834,837,839,841,844,846,848,850,853,855,857,859,862,864,866,868,871,873,875,877,879,882,884,886,888,890,892,895,897,899,901,903,905,907,909,912,914,916,918,920,922,924,926,928,930,932,934,937,939,941,943,945,947,949,951,953,955,957,959,961,963,965,967,969,971,973,975,977,979,981,983,985,987,988,990,992,994,996,998,1000,1002,1004,1006,1008,1010,1012,1013,1015,1017,1019,1021,1023,1025,1027,1029,1030,1032,1034,1036,1038,1040,1042,1043,1045,1047,1049,1051,1053,1054,1056,1058,1060,1062,1063,1065,1067,1069,1071,1072,1074,1076,1078,1080,1081,1083,1085,1087,1089,1090,1092,1094,1096,1097,1099,1101,1103,1104,1106,1108,1110,1111,1113,1115,1116,1118,1120,1122,1123,1125,1127,1128,1130,1132,1134,1135,1137,1139,1140,1142,1144,1145,1147,1149,1150,1152,1154,1155,1157,1159,1160,1162,1164,1165,1167,1169,1170,1172,1174,1175,1177,1178,1180,1182,1183,1185,1187,1188,1190,1191,1193,1195,1196,1198,1199,1201,1203,1204,1206,1207,1209,1211,1212,1214,1215,1217,1219,1220,1222,1223,1225,1226,1228,1230,1231,1233,1234,1236,1237,1239,1240,1242,1244,1245,1247,1248,1250,1251,1253,1254,1256,1257,1259,1260,1262,1264,1265,1267,1268,1270,1271,1273,1274,1276,1277,1279,1280,1282,1283,1285,1286,1288,1289,1291,1292,1294,1295,1297,1298,1300,1301,1303,1304,1305,1307,1308,1310,1311,1313,1314,1316,1317,1319,1320,1322,1323,1324,1326,1327,1329,1330,1332,1333,1335,1336,1337,1339,1340,1342,1343,1345,1346,1348,1349,1350,1352,1353,1355,1356,1357,1359,1360,1362,1363,1365,1366,1367,1369,1370,1372,1373,1374,1376,1377,1379,1380,1381,1383,1384,1386,1387,1388,1390,1391,1392,1394,1395,1397,1398,1399,1401,1402,1403,1405,1406,1408,1409,1410,1412,1413,1414,1416,1417,1418,1420,1421,1423,1424,1425,1427,1428,1429,1431,1432,1433,1435,1436,1437,1439,1440,1441,1443,1444,1445,1447,1448,1449,1451,1452,1453,1455,1456,1457,1459,1460,1461,1463,1464,1465,1466,1468,1469,1470,1472,1473,1474,1476,1477,1478,1480,1481,1482,1483,1485,1486,1487,1489,1490,1491,1492,1494,1495,1496,1498,1499,1500,1501,1503,1504,1505,1507,1508,1509,1510,1512,1513,1514,1515,1517,1518,1519,1521,1522,1523,1524,1526,1527,1528,1529,1531,1532,1533,1534,1536,1537,1538,1539,1541,1542,1543,1544,1546,1547,1548,1549,1551,1552,1553,1554,1556,1557,1558,1559,1560,1562,1563,1564,1565,1567,1568,1569,1570,1572,1573,1574,1575,1576,1578,1579,1580,1581,1583,1584,1585,1586,1587,1589,1590,1591,1592,1593,1595,1596,1597,1598,1599,1601,1602,1603,1604,1605,1607,1608,1609,1610,1611,1613,1614,1615,1616,1617,1619,1620,1621,1622,1623,1625,1626,1627,1628,1629,1630,1632,1633,1634,1635,1636,1637,1639,1640,1641,1642,1643,1645,1646,1647,1648,1649,1650,1652,1653,1654,1655,1656,1657,1658,1660,1661,1662,1663,1664,1665,1667,1668,1669,1670,1671,1672,1674,1675,1676,1677,1678,1679,1680,1682,1683,1684,1685,1686,1687,1688,1690,1691,1692,1693,1694,1695,1696,1697,1699,1700,1701,1702,1703,1704,1705,1707,1708,1709,1710,1711,1712,1713,1714,1716,1717,1718,1719,1720,1721,1722,1723,1724,1726,1727,1728,1729,1730,1731,1732,1733,1734,1736,1737,1738,1739,1740,1741,1742,1743,1744,1746,1747,1748,1749,1750,1751,1752,1753,1754,1755,1756,1758,1759,1760,1761,1762,1763,1764,1765,1766,1767,1769,1770,1771,1772,1773,1774,1775,1776,1777,1778,1779,1780,1782,1783,1784,1785,1786,1787,1788,1789,1790,1791,1792,1793,1794,1795,1797,1798,1799,1800,1801,1802,1803,1804,1805,1806,1807,1808,1809,1810,1811,1813,1814,1815,1816,1817,1818,1819,1820,1821,1822,1823,1824,1825,1826,1827,1828,1829,1830,1832,1833,1834,1835,1836,1837,1838,1839,1840,1841,1842,1843,1844,1845,1846,1847,1848,1849,1850,1851,1852,1853,1855,1856,1857,1858,1859,1860,1861,1862,1863,1864,1865,1866,1867,1868,1869,1870,1871,1872,1873,1874,1875,1876,1877,1878,1879,1880,1881,1882,1883,1884,1885,1886,1887,1888,1889,1890,1891,1892,1894,1895,1896,1897,1898,1899,1900,1901,1902,1903,1904,1905,1906,1907,1908,1909,1910,1911,1912,1913,1914,1915,1916,1917,1918,1919,1920,1921,1922,1923,1924,1925,1926,1927,1928,1929,1930,1931,1932,1933,1934,1935,1936,1937,1938,1939,1940,1941,1942,1943,1944,1945,1946,1947,1948,1949,1950,1951,1952,1953,1954,1954,1955,1956,1957,1958,1959,1960,1961,1962,1963,1964,1965,1966,1967,1968,1969,1970,1971,1972,1973,1974,1975,1976,1977,1978,1979,1980,1981,1982,1983,1984,1985,1986,1987,1988,1989,1990,1991,1992,1993,1993,1994,1995,1996,1997,1998,1999,2000,2001,2002,2003,2004,2005,2006,2007,2008,2009,2010,2011,2012,2013,2014,2015,2016,2016,2017,2018,2019,2020,2021,2022,2023,2024,2025,2026,2027,2028,2029,2030,2031,2032,2033,2034,2035,2035,2036,2037,2038,2039,2040,2041,2042,2043,2044,2045,2046,2047,2048,2049,2050,2051,2051,2052,2053,2054,2055,2056,2057,2058,2059,2060,2061,2062,2063,2064,2065,2066,2066,2067,2068,2069,2070,2071,2072,2073,2074,2075,2076,2077,2078,2079,2079,2080,2081,2082,2083,2084,2085,2086,2087,2088,2089,2090,2090,2091,2092,2093,2094,2095,2096,2097,2098,2099,2100,2101,2102,2102,2103,2104,2105,2106,2107,2108,2109,2110,2111,2112,2112,2113,2114,2115,2116,2117,2118,2119,2120,2121,2122,2122,2123,2124,2125,2126,2127,2128,2129,2130,2131,2132,2132,2133,2134,2135,2136,2137,2138,2139,2140,2141,2141,2142,2143,2144,2145,2146,2147,2148,2149,2149,2150,2151,2152,2153,2154,2155,2156,2157,2158,2158,2159,2160,2161,2162,2163,2164,2165,2166,2166,2167,2168,2169,2170,2171,2172,2173,2174,2174,2175,2176,2177,2178,2179,2180,2181,2181,2182,2183,2184,2185,2186,2187,2188,2188,2189,2190,2191,2192,2193,2194,2195,2196,2196,2197,2198,2199,2200,2201,2202,2203,2203,2204,2205,2206,2207,2208,2209,2209,2210,2211,2212,2213,2214,2215,2216,2216,2217,2218,2219,2220,2221,2222,2223,2223,2224,2225,2226,2227,2228,2229,2229,2230,2231,2232,2233,2234,2235,2235,2236,2237,2238,2239,2240,2241,2241,2242,2243,2244,2245,2246,2247,2247,2248,2249,2250,2251,2252,2253,2253,2254,2255,2256,2257,2258,2259,2259,2260,2261,2262,2263,2264,2265,2265,2266,2267,2268,2269,2270,2270,2271,2272,2273,2274,2275,2276,2276,2277,2278,2279,2280,2281,2281,2282,2283,2284,2285,2286,2286,2287,2288,2289,2290,2291,2292,2292,2293,2294,2295,2296,2297,2297,2298,2299,2300,2301,2302,2302,2303,2304,2305,2306,2307,2307,2308,2309,2310,2311,2312,2312,2313,2314,2315,2316,2317,2317,2318,2319,2320,2321,2322,2322,2323,2324,2325,2326,2327,2327,2328,2329,2330,2331,2331,2332,2333,2334,2335,2336,2336,2337,2338,2339,2340,2341,2341,2342,2343,2344,2345,2345,2346,2347,2348,2349,2350,2350,2351,2352,2353,2354,2354,2355,2356,2357,2358,2359,2359,2360,2361,2362,2363,2363,2364,2365,2366,2367,2368,2368,2369,2370,2371,2372,2372,2373,2374,2375,2376,2376,2377,2378,2379,2380,2380,2381,2382,2383,2384,2385,2385,2386,2387,2388,2389,2389,2390,2391,2392,2393,2393,2394,2395,2396,2397,2397,2398,2399,2400,2401,2401,2402,2403,2404,2405,2405,2406,2407,2408,2409,2409,2410,2411,2412,2413,2413,2414,2415,2416,2417,2417,2418,2419,2420,2421,2421,2422,2423,2424,2425,2425,2426,2427,2428,2428,2429,2430,2431,2432,2432,2433,2434,2435,2436,2436,2437,2438,2439,2440,2440,2441,2442,2443,2443,2444,2445,2446,2447,2447,2448,2449,2450,2451,2451,2452,2453,2454,2454,2455,2456,2457,2458,2458,2459,2460,2461,2462,2462,2463,2464,2465,2465,2466,2467,2468,2469,2469,2470,2471,2472,2472,2473,2474,2475,2476,2476,2477,2478,2479,2479,2480,2481,2482,2483,2483,2484,2485,2486,2486,2487,2488,2489,2489,2490,2491,2492,2493,2493,2494,2495,2496,2496,2497,2498,2499,2500,2500,2501,2502,2503,2503,2504,2505,2506,2506,2507,2508,2509,2509,2510,2511,2512,2513,2513,2514,2515,2516,2516,2517,2518,2519,2519,2520,2521,2522,2522,2523,2524,2525,2526,2526,2527,2528,2529,2529,2530,2531,2532,2532,2533,2534,2535,2535,2536,2537,2538,2538,2539,2540,2541,2541,2542,2543,2544,2545,2545,2546,2547,2548,2548,2549,2550,2551,2551,2552,2553,2554,2554,2555,2556,2557,2557,2558,2559,2560,2560,2561,2562,2563,2563,2564,2565,2566,2566,2567,2568,2569,2569,2570,2571,2572,2572,2573,2574,2575,2575,2576,2577,2578,2578,2579,2580,2581,2581,2582,2583,2584,2584,2585,2586,2586,2587,2588,2589,2589,2590,2591,2592,2592,2593,2594,2595,2595,2596,2597,2598,2598,2599,2600,2601,2601,2602,2603,2604,2604,2605,2606,2606,2607,2608,2609,2609,2610,2611,2612,2612,2613,2614,2615,2615,2616,2617,2618,2618,2619,2620,2620,2621,2622,2623,2623,2624,2625,2626,2626,2627,2628,2629,2629,2630,2631,2631,2632,2633,2634,2634,2635,2636,2637,2637,2638,2639,2639,2640,2641,2642,2642,2643,2644,2645,2645,2646,2647,2647,2648,2649,2650,2650,2651,2652,2653,2653,2654,2655,2655,2656,2657,2658,2658,2659,2660,2661,2661,2662,2663,2663,2664,2665,2666,2666,2667,2668,2668,2669,2670,2671,2671,2672,2673,2674,2674,2675,2676,2676,2677,2678,2679,2679,2680,2681,2681,2682,2683,2684,2684,2685,2686,2686,2687,2688,2689,2689,2690,2691,2691,2692,2693,2694,2694,2695,2696,2696,2697,2698,2699,2699,2700,2701,2701,2702,2703,2704,2704,2705,2706,2706,2707,2708,2709,2709,2710,2711,2711,2712,2713,2714,2714,2715,2716,2716,2717,2718,2718,2719,2720,2721,2721,2722,2723,2723,2724,2725,2726,2726,2727,2728,2728,2729,2730,2730,2731,2732,2733,2733,2734,2735,2735,2736,2737,2738,2738,2739,2740,2740,2741,2742,2742,2743,2744,2745,2745,2746,2747,2747,2748,2749,2749,2750,2751,2752,2752,2753,2754,2754,2755,2756,2756,2757,2758,2759,2759,2760,2761,2761,2762,2763,2763,2764,2765,2765,2766,2767,2768,2768,2769,2770,2770,2771,2772,2772,2773,2774,2774,2775,2776,2777,2777,2778,2779,2779,2780,2781,2781,2782,2783,2783,2784,2785,2786,2786,2787,2788,2788,2789,2790,2790,2791,2792,2792,2793,2794,2795,2795,2796,2797,2797,2798,2799,2799,2800,2801,2801,2802,2803,2803,2804,2805,2806,2806,2807,2808,2808,2808,2811,2811,2811,2812,2812,2813,2814,2814,2815,2816,2816,2817,2818,2819,2819,2820,2821,2821,2822,2823,2823,2824,2825,2825,2826,2827,2827,2828,2829,2829,2830,2831,2831,2832,2833,2833,2834,2835,2836,2836,2837,2838,2838,2839,2840,2840,2841,2842,2842,2843,2844,2844,2845,2846,2846,2847,2848,2848,2849,2850,2850,2851,2852,2852,2853,2854,2854,2855,2856,2856,2857,2858,2858,2859,2860,2861,2861,2862,2863,2863,2864,2865,2865,2866,2867,2867,2868,2869,2869,2870,2871,2871,2872,2873,2873,2874,2875,2875,2876,2877,2877,2878,2879,2879,2880,2881,2881,2882,2883,2883,2884,2885,2885,2886,2887,2887,2888,2889,2889,2890,2891,2891,2892,2893,2893,2894,2895,2895,2896,2897,2897,2898,2899,2899,2900,2901,2901,2902,2903,2903,2904,2905,2905,2906,2907,2907,2908,2909,2909,2910,2911,2911,2912,2912,2913,2914,2914,2915,2916,2916,2917,2918,2918,2919,2920,2920,2921,2922,2922,2923,2924,2924,2925,2926,2926,2927,2928,2928,2929,2930,2930,2931,2932,2932,2933,2934,2934,2935,2936,2936,2937,2937,2938,2939,2939,2940,2941,2941,2942,2943,2943,2944,2945,2945,2946,2947,2947,2948,2949,2949,2950,2951,2951,2952,2953,2953,2954,2954,2955,2956,2956,2957,2958,2958,2959,2960,2960,2961,2962,2962,2963,2964,2964,2965,2966,2966,2967,2967,2968,2969,2969,2970,2971,2971,2972,2973,2973,2974,2975,2975,2976,2977,2977,2978,2978,2979,2980,2980,2981,2982,2982,2983,2984,2984,2985,2986,2986,2987,2987,2988,2989,2989,2990,2991,2991,2992,2993,2993,2994,2995,2995,2996,2996,2997,2998,2998,2999,3000,3000,3001,3002,3002,3003,3004,3004,3005,3005,3006,3007,3007,3008,3009,3009,3010,3011,3011,3012,3012,3013,3014,3014,3015,3016,3016,3017,3018,3018,3019,3019,3020,3021,3021,3022,3023,3023,3024,3025,3025,3026,3026,3027,3028,3028,3029,3030,3030,3031,3032,3032,3033,3033,3034,3035,3035,3036,3037,3037,3038,3039,3039,3040,3040,3041,3042,3042,3043,3044,3044,3045,3046,3046,3047,3047,3048,3049,3049,3050,3051,3051,3052,3052,3053,3054,3054,3055,3056,3056,3057,3057,3058,3059,3059,3060,3061,3061,3062,3063,3063,3064,3064,3065,3066,3066,3067,3068,3068,3069,3069,3070,3071,3071,3072,3073,3073,3074,3074,3075,3076,3076,3077,3078,3078,3079,3079,3080,3081,3081,3082,3083,3083,3084,3084,3085,3086,3086,3087,3088,3088,3089,3089,3090,3091,3091,3092,3093,3093,3094,3094,3095,3096,3096,3097,3097,3098,3099,3099,3100,3101,3101,3102,3102,3103,3104,3104,3105,3106,3106,3107,3107,3108,3109,3109,3110,3110,3111,3112,3112,3113,3114,3114,3115,3115,3116,3117,3117,3118,3119,3119,3120,3120,3121,3122,3122,3123,3123,3124,3125,3125,3126,3127,3127,3128,3128,3129,3130,3130,3131,3131,3132,3133,3133,3134,3135,3135,3136,3136,3137,3138,3138,3139,3139,3140,3141,3141,3142,3142,3143,3144,3144,3145,3146,3146,3147,3147,3148,3149,3149,3150,3150,3151,3152,3152,3153,3153,3154,3155,3155,3156,3157,3157,3158,3158,3159,3160,3160,3161,3161,3162,3163,3163,3164,3164,3165,3166,3166,3167,3167,3168,3169,3169,3170,3171,3171,3172,3172,3173,3174,3174,3175,3175,3176,3177,3177,3178,3178,3179,3180,3180,3181,3181,3182,3183,3183,3184,3184,3185,3186,3186,3187,3187,3188,3189,3189,3190,3190,3191,3192,3192,3193,3193,3194,3195,3195,3196,3197,3197,3198,3198,3199,3200,3200,3201,3201,3202,3203,3203,3204,3204,3205,3206,3206,3207,3207,3208,3209,3209,3210,3210,3211,3212,3212,3213,3213,3214,3215,3215,3216,3216,3217,3217,3218,3219,3219,3220,3220,3221,3222,3222,3223,3223,3224,3225,3225,3226,3226,3227,3228,3228,3229,3229,3230,3231,3231,3232,3232,3233,3234,3234,3235,3235,3236,3237,3237,3238,3238,3239,3240,3240,3241,3241,3242,3243,3243,3244,3244,3245,3245,3246,3247,3247,3248,3248,3249,3250,3250,3251,3251,3252,3253,3253,3254,3254,3255,3256,3256,3257,3257,3258,3258,3259,3260,3260,3261,3261,3262,3263,3263,3264,3264,3265,3266,3266,3267,3267,3268,3269,3269,3270,3270,3271,3271,3272,3273,3273,3274,3274,3275,3276,3276,3277,3277,3278,3278,3279,3280,3280,3281,3281,3282,3283,3283,3284,3284,3285,3286,3286,3287,3287,3288,3288,3289,3290,3290,3291,3291,3292,3293,3293,3294,3294,3295,3295,3296,3297,3297,3298,3298,3299,3300,3300,3301,3301,3302,3302,3303,3304,3304,3305,3305,3306,3307,3307,3308,3308,3309,3309,3310,3311,3311,3312,3312,3313,3314,3314,3315,3315,3316,3316,3317,3318,3318,3319,3319,3320,3320,3321,3322,3322,3323,3323,3324,3325,3325,3326,3326,3327,3327,3328,3329,3329,3330,3330,3331,3331,3332,3333,3333,3334,3334,3335,3335,3336,3337,3337,3338,3338,3339,3340,3340,3341,3341,3342,3342,3343,3344,3344,3345,3345,3346,3346,3347,3348,3348,3349,3349,3350,3350,3351,3352,3352,3353,3353,3354,3354,3355,3356,3356,3357,3357,3358,3358,3359,3360,3360,3361,3361,3362,3362,3363,3364,3364,3365,3365,3366,3366,3367,3368,3368,3369,3369,3370,3370,3371,3372,3372,3373,3373,3374,3374,3375,3376,3376,3377,3377,3378,3378,3379,3380,3380,3381,3381,3382,3382,3383,3384,3384,3385,3385,3386,3386,3387,3388,3388,3389,3389,3390,3390,3391,3392,3392,3393,3393,3394,3394,3395,3396,3396,3397,3397,3398,3398,3399,3399,3400,3401,3401,3402,3402,3403,3403,3404,3405,3405,3406,3406,3407,3407,3408,3409,3409,3410,3410,3411,3411,3412,3412,3413,3414,3414,3415,3415,3416,3416,3417,3418,3418,3419,3419,3420,3420,3421,3421,3422,3423,3423,3424,3424,3425,3425,3426,3427,3427,3428,3428,3429,3429,3430,3430,3431,3432,3432,3433,3433,3434,3434,3435,3435,3436,3437,3437,3438,3438,3439,3439,3440,3441,3441,3442,3442,3443,3443,3444,3444,3445,3446,3446,3447,3447,3448,3448,3449,3449,3450,3451,3451,3452,3452,3453,3453,3454,3454,3455,3456,3456,3457,3457,3458,3458,3459,3459,3460,3461,3461,3462,3462,3463,3463,3464,3464,3465,3466,3466,3467,3467,3468,3468,3469,3469,3470,3471,3471,3472,3472,3473,3473,3474,3474,3475,3476,3476,3477,3477,3478,3478,3479,3479,3480,3481,3481,3482,3482,3483,3483,3484,3484,3485,3486,3486,3487,3487,3488,3488,3489,3489,3490,3490,3491,3492,3492,3493,3493,3494,3494,3495,3495,3496,3497,3497,3498,3498,3499,3499,3500,3500,3501,3501,3502,3503,3503,3504,3504,3505,3505,3506,3506,3507,3508,3508,3509,3509,3510,3510,3511,3511,3512,3512,3513,3514,3514,3515,3515,3516,3516,3517,3517,3518,3518,3519,3520,3520,3521,3521,3522,3522,3523,3523,3524,3524,3525,3526,3526,3527,3527,3528,3528,3529,3529,3530,3530,3531,3532,3532,3533,3533,3534,3534,3535,3535,3536,3536,3537,3538,3538,3539,3539,3540,3540,3541,3541,3542,3542,3543,3544,3544,3545,3545,3546,3546,3547,3547,3548,3548,3549,3549,3550,3551,3551,3552,3552,3553,3553,3554,3554,3555,3555,3556,3557,3557,3558,3558,3559,3559,3560,3560,3561,3561,3562,3562,3563,3564,3564,3565,3565,3566,3566,3567,3567,3568,3568,3569,3569,3570,3571,3571,3572,3572,3573,3573,3574,3574,3575,3575,3576,3576,3577,3578,3578,3579,3579,3580,3580,3581,3581,3582,3582,3583,3583,3584,3585,3585,3586,3586,3587,3587,3588,3588,3589,3589,3590,3590,3591,3592,3592,3593,3593,3594,3594,3595,3595,3596,3596,3597,3597,3598,3598,3599,3600,3600,3601,3601,3602,3602,3603,3603,3604,3604,3605,3605,3606,3606,3607,3608,3608,3609,3609,3610,3610,3611,3611,3612,3612,3613,3613,3614,3614,3615,3616,3616,3617,3617,3618,3618,3619,3619,3620,3620,3621,3621,3622,3622,3623,3624,3624,3625,3625,3626,3626,3627,3627,3628,3628,3629,3629,3630,3630,3631,3631,3632,3633,3633,3634,3634,3635,3635,3636,3636,3637,3637,3638,3638,3639,3639,3640,3640,3641,3642,3642,3643,3643,3644,3644,3645,3645,3646,3646,3647,3647,3648,3648,3649,3649,3650,3650,3651,3652,3652,3653,3653,3654,3654,3655,3655,3656,3656,3657,3657,3658,3658,3659,3659,3660,3660,3661,3662,3662,3663,3663,3664,3664,3665,3665,3666,3666,3667,3667,3668,3668,3669,3669,3670,3670,3671,3671,3672,3673,3673,3674,3674,3675,3675,3676,3676,3677,3677,3678,3678,3679,3679,3680,3680,3681,3681,3682,3682,3683,3684,3684,3685,3685,3686,3686,3687,3687,3688,3688,3689,3689,3690,3690,3691,3691,3692,3692,3693,3693,3694,3694,3695,3696,3696,3697,3697,3698,3698,3699,3699,3700,3700,3701,3701,3702,3702,3703,3703,3704,3704,3705,3705,3706,3706,3707,3707,3708,3709,3709,3710,3710,3711,3711,3712,3712,3713,3713,3714,3714,3715,3715,3716,3716,3717,3717,3718,3718,3719,3719,3720,3720,3721,3721,3722,3722,3723,3724,3724,3725,3725,3726,3726,3727,3727,3728,3728,3729,3729,3730,3730,3731,3731,3732,3732,3733,3733,3734,3734,3735,3735,3736,3736,3737,3737,3738,3738,3739,3739,3740,3741,3741,3742,3742,3743,3743,3744,3744,3745,3745,3746,3746,3747,3747,3748,3748,3749,3749,3750,3750,3751,3751,3752,3752,3753,3753,3754,3754,3755,3755,3756,3756,3757,3757,3758,3758,3759,3760,3760,3761,3761,3762,3762,3763,3763,3764,3764,3765,3765,3766,3766,3767,3767,3768,3768,3769,3769,3770,3770,3771,3771,3772,3772,3773,3773,3774,3774,3775,3775,3776,3776,3777,3777,3778,3778,3779,3779,3780,3780,3781,3781,3782,3782,3783,3783,3784,3784,3785,3786,3786,3787,3787,3788,3788,3789,3789,3790,3790,3791,3791,3792,3792,3793,3793,3794,3794,3795,3795,3796,3796,3797,3797,3798,3798,3799,3799,3800,3800,3801,3801,3802,3802,3803,3803,3804,3804,3805,3805,3806,3806,3807,3807,3808,3808,3809,3809,3810,3810,3811,3811,3812,3812,3813,3813,3814,3814,3815,3815,3816,3816,3817,3817,3818,3818,3819,3819,3820,3820,3821,3821,3822,3822,3823,3823,3824,3824,3825,3825,3826,3826,3827,3827,3828,3828,3829,3829,3830,3830,3831,3831,3832,3832,3833,3833,3834,3834,3835,3835,3836,3836,3837,3837,3838,3838,3839,3839,3840,3840,3841,3841,3842,3842,3843,3843,3844,3844,3845,3845,3846,3846,3847,3847,3848,3848,3849,3849,3850,3850,3851,3851,3852,3852,3853,3853,3854,3854,3855,3855,3856,3856,3857,3857,3858,3858,3859,3859,3860,3860,3861,3861,3862,3862,3863,3863,3864,3864,3865,3865,3866,3866,3867,3867,3868,3868,3869,3869,3870,3870,3871,3871,3872,3872,3873,3873,3874,3874,3875,3875,3876,3876,3877,3877,3878,3878,3879,3879,3880,3880,3881,3881,3882,3882,3883,3883,3884,3884,3885,3885,3886,3886,3887,3887,3888,3888,3889,3889,3890,3890,3891,3891,3892,3892,3893,3893,3894,3894,3895,3895,3896,3896,3897,3897,3898,3898,3899,3899,3900,3900,3901,3901,3902,3902,3903,3903,3904,3904,3905,3905,3906,3906,3907,3907,3908,3908,3909,3909,3909,3910,3910,3911,3911,3912,3912,3913,3913,3914,3914,3915,3915,3916,3916,3917,3917,3918,3918,3919,3919,3920,3920,3921,3921,3922,3922,3923,3923,3924,3924,3925,3925,3926,3926,3927,3927,3928,3928,3929,3929,3930,3930,3931,3931,3932,3932,3933,3933,3934,3934,3935,3935,3935,3936,3936,3937,3937,3938,3938,3939,3939,3940,3940,3941,3941,3942,3942,3943,3943,3944,3944,3945,3945,3946,3946,3947,3947,3948,3948,3949,3949,3950,3950,3951,3951,3952,3952,3953,3953,3954,3954,3954,3955,3955,3956,3956,3957,3957,3958,3958,3959,3959,3960,3960,3961,3961,3962,3962,3963,3963,3964,3964,3965,3965,3966,3966,3967,3967,3968,3968,3969,3969,3970,3970,3971,3971};

