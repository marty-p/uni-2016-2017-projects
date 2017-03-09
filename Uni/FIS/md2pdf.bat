@echo off
set main_dir=%~dp0
set md_dir="%1"
set md_list=../author.md
set pandoc_dir=

SETLOCAL EnableDelayedExpansion

cd %md_dir%
echo deleting the old instances...
del /F /Q notes.pdf

for /R "." %%f in (*.md) do (
	SET md_list=!md_list! %%f
	echo added %%f in list...
)

echo processing %md_list% into a notes...

%pandoc_dir%pandoc.exe %md_list% ^
	-t latex --latex-engine=xelatex ^
	--toc --toc-depth=6 ^
	-V lang=it ^
	-V geometry=a4paper --top-level-division=section ^
	--dpi=300 ^
	--variable fontsize=12pt ^
	-o "notes.pdf"

	REM --variable documentclass=report ^
	REM -t latex --latex-engine=pdflatex ^
	REM --wrap=none ^
	REM --standalone --normalize --smart --self-contained ^
	REM -V fontsize=11pt ^

start notes.pdf
cd %main_dir%
REM pause
