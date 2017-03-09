@echo off
set main_dir=%~dp0
set md_dir=.
set md_list=
set pandoc_dir=

SETLOCAL EnableDelayedExpansion

cd %md_dir%
echo deleting the old instances...
del /F /Q relazione.pdf

for /R "." %%f in (*.md) do (
	SET md_list=!md_list! %%f
	echo added %%f in list...
)

echo processing %md_list% into a book...

%pandoc_dir%pandoc.exe %md_list% ^
	-t latex --latex-engine=xelatex ^
	-V lang=it ^
	--dpi=300 ^
	--variable documentclass=report ^
	-o "relazione.pdf"

	REM --variable fontsize=12pt ^
	REM -t latex --latex-engine=pdflatex ^
	REM --wrap=none ^
	REM --standalone --normalize --smart --self-contained ^

cd %main_dir%
start %md_dir%/relazione.pdf
REM pause
