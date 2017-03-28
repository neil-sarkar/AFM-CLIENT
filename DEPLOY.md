Find macdeployqt and windeployqt scripts in qt directory.

	{QTDIR}/5.5/{compiler}/bin/
							   windeployqt.exe
							   macdeployqt.sh
	*For windows, ensure compiler is in path.
	**Scriptable proc, example code

		cd c:\DEP
		del /s /q "c:\DEP\*.*"
		copy c:\ICSPI_CONF\AFM-CLIENT\qt_quick_app\nGauge.exe .\

		C:\Qt\Qt5.5.1\5.5\mingw492_32\bin\windeployqt.exe nGauge.exe
		pause


Run NSIS Script (Ensure updated information in script)