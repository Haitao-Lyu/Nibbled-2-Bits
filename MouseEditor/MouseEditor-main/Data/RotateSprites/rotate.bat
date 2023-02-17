@echo off
setlocal enabledelayedexpansion

rem Find all png files in current directory
for %%F in (*.png) do (
  rem Save original file name without extension
  set "base=%%~nF"
  
  rem Create new filenames for rotated versions
  set "filenamePanel=!base!_panel.png"
  set "filenameRA=!base!_RA.png"
  set "filenameRB=!base!_RB.png"
  set "filenameRC=!base!_RC.png"
  set "filenameRD=!base!_RD.png"
  
  rem Save an unmodified panel version of the original image
  magick "%%F" -define png:color-type=2 "!filenamePanel!"
  
  rem Rotate and scale the original image and save as new files
  magick "%%F" -resize 50%% -rotate 90 "!filenameRD!"
  magick "%%F" -resize 50%% -rotate 180 "!filenameRC!"
  magick "%%F" -resize 50%% -rotate 270 "!filenameRB!"
  magick "%%F" -resize 50%% "!filenameRA!"
  
  rem Remove the original file
  del "%%F"
)
