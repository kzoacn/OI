@echo off
set pro=bzoj2331
:loop
%pro%_data.exe > %pro%.in
%pro%.exe <%pro%.in >%pro%.out
_%pro%.exe <%pro%.in >%pro%.ans
fc %pro%.out %pro%.ans
if %errorlevel%==0 goto loop
pause