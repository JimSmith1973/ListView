cls

del *.exe

windres Resource.rc -o Resource.o

g++ -mwindows -m64 -static -Wall -Wextra ListView.cpp ^
 ^
 ..\Classes\ArgumentListClass.cpp ^
 ..\Classes\DroppedFilesClass.cpp ^
 ..\Classes\FontClass.cpp ^
 ..\Classes\ListBoxWindowClass.cpp ^
 ..\Classes\ListViewWindowClass.cpp ^
 ..\Classes\MenuClass.cpp ^
 ..\Classes\MessageClass.cpp ^
 ..\Classes\StatusBarWindowClass.cpp ^
 ..\Classes\WindowClass.cpp ^
 ..\Classes\WindowClassClass.cpp ^
 ^
 Resource.o -o ListView.exe
