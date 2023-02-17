#echo off
cd %~dp0
rd /q /s Listing
rd /q /s Output
cd Project
rd /q /s DebugConfig
del /q /s *uvguix*
del /q /s *uvoptx*
exit