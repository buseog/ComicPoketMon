@echo off
rem System 
rem Utility
rem Resource
rem Client
rem Reference
rem Engine
rem Export

set System=.\Engine\System\
set Utility=.\Engine\Utility\
set Resource=.\Engine\Resource\
set Client=.\Client\
set Tool=.\Tool\
set Reference=.\Reference\
set Engine=.\Engine\
set Export=.\Engine\Export\


::dll 파일 -> 클라
xcopy		/y		%System%bin\*.dll		%Client%bin\ 
xcopy		/y		%Utility%bin\*.dll		%Client%bin\ 
xcopy		/y		%Resource%bin\*.dll		%Client%bin\ 

::dll파일 -> 툴
xcopy		/y		%System%bin\*.dll		%Tool%bin\ 
xcopy		/y		%Utility%bin\*.dll		%Tool%bin\ 
xcopy		/y		%Resource%bin\*.dll		%Tool%bin\ 

::라이브러리 파일
xcopy		/y		%System%bin\*.lib		%Reference%\Libraries\ 
xcopy		/y		%Utility%bin\*.lib		%Reference%\Libraries\ 
xcopy		/y		%Resource%bin\*.lib		%Reference%\Libraries\ 


:: 헤더들
xcopy		/y		%System%Code\*.h		%Reference%\Headers\ 
xcopy		/y		%Utility%Code\*.h		%Reference%\Headers\ 
xcopy		/y		%Resource%Code\*.h		%Reference%\Headers\ 

::인클루드 헤더들
xcopy		/y		%Engine%Headers\*.h		%Reference%\Headers\ 

::export 헤더들
xcopy		/y		%Export%*.*			%Reference%\Headers\
