CXX=@cl.exe
CXXFLAGS=/MT /EHa /O1 /Ob1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS"

LINK32=@link.exe
LINK32FLAGS=/dll /machine:x64 /nologo

LoadDLL64.dll: LoadDLL.obj
	$(LINK32) $(LINK32FLAGS) LoadDLL.obj /out:LoadDLL64.dll

LoadDLL.obj: LoadDLL.cpp
	$(CXX) $(CXXFLAGS) LoadDLL.cpp -c
