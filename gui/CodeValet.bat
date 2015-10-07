@ECHO off
python -m cogapp -e -r -c afm.h
python -m cogapp -e -r receive_worker.cpp
pause