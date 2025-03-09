@echo off
for %%f in (*.ui) do (
    uic -o "%%~nf.h" "%%f"
)