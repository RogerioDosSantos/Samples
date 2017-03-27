@echo off

set clang_dir=%~dp0
rem echo clang_dir:%clang_dir%

set file_path=%~1
echo File Path: %file_path%

set file_dir=%~dp1
rem echo %file_dir%

for %%F in (%file_path%) do set file_name=%%~nxF
echo File: %file_name%

set clang_name=clang-format.exe
rem echo %clang_name%

set clang_format_name=.clang-format
rem echo %clang_format_name%

set initial_line=%2
set final_line=%3

IF %final_line% == 0 echo Parsing all lines
IF NOT %final_line% == 0 echo Parsing line %initial_line% to %final_line%

XCOPY "%clang_dir%%clang_format_name%" "%file_dir%" /R /Y

IF %final_line% == 0 "%clang_dir%%clang_name%" -i -style=file  "%file_path%"
IF NOT %final_line% == 0 "%clang_dir%%clang_name%" -i -style=file  -lines="%initial_line%:%final_line%" "%file_path%"

IF EXIST %file_dir%*.tmp del %file_dir%*.tmp /Q
IF EXIST %file_dir%%clang_format_name% del %file_dir%%clang_format_name% /Q
