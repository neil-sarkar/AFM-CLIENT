@ECHO off
python -m cogapp -e -r -c afm.h
python -m cogapp -e -r receive_worker.cpp
python -m cogapp -e -r afm_data.h
ECHO ----- Completed -----
ECHO If some files were not updated, try again in a few minutes.
ECHO Google Drive may not have updated the CSV yet
ECHO ---------------------
pause