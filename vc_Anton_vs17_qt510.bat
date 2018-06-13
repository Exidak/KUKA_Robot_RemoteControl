call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Auxiliary\Build\vcvarsall.bat" x86
set QTDIR32=c:\Qt\Qt5.10.1\5.10.1\msvc2015\
set QTCOREP32=%QTDIR32%include\QtCore\5.10.1\QtCore\
set QTLIB32=%QTDIR32%lib
set QTDIR64=c:\Qt\Qt5.10.1\5.10.1\msvc2017_64\
set QTCOREP64=%QTDIR64%include\QtCore\5.10.1\QtCore
set QTLIB64=%QTDIR64%lib

devenv RemoteControl.sln
