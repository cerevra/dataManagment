@echo off
dir %QT_DIR%\bin /B /A:-D | findstr /R "^[li].*\.dll$"