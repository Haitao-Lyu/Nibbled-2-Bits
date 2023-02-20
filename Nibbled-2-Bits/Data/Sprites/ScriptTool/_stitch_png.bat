@echo off
setlocal EnableDelayedExpansion

set "output=output.png"
set "images="

for %%i in (%*) do (
  set "images=!images! "%%~i""
)

magick convert +append !images! "%output%"
