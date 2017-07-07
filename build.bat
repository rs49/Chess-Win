set objs= 
for /R %%f in (src\*.cpp) do call set objs=%%objs%% %%f
set includes= /I %cd%\deps\include\
set libs= /LIBPATH:%cd%\deps\libs\ SDL2.lib SDL2main.lib SDL2_image.lib

cl %objs% -Oi %includes% /link /out:chess.exe %libs% /SUBSYSTEM:WINDOWS,5.02

del *.obj
