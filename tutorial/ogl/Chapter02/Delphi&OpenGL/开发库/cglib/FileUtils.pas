unit FileUtils;

interface

uses
  Forms, Windows, ShellAPI, SysUtils, Classes, Dialogs;

function GetFileNames(path: String; attrib: Integer): TStringList;
function GetDirNames(path: String): TStringList;
function FileInfo(filename: String): TSearchRec;
function HasAttrib(fileAttrib, testAttrib: Integer): Boolean;
procedure ExecWait(FileName: String; WorkingDir: String; showCmd: Integer);
function GetFileSize(FileName: String): Cardinal;

implementation

{ GetFileNames() enumerates all files within the given path and with the given
  attributes. The attributes must be a combination of the following:
    -> faReadOnly, faHidden, faSysFile, faVolumeID, faDirectory, faArchive, faAnyFile.
  To find only normal files, pass 0 as the attrib parameter. REMEMBER TO ADD WILDCARDS
  TO THE PATH, OR YOU WON'T FIND ANYTHING!!! }
function GetFileNames(path: String; attrib: Integer): TStringList;
var
  srec: TSearchRec;
begin

  Result := TStringList.Create;
  FillChar(srec, SizeOf(srec), 0);
  if FindFirst(path, attrib, srec) = 0 then
  begin
    Result.Add(srec.Name);
    while FindNext(srec) = 0 do Result.Add(srec.Name);
    FindClose(srec);
  end;

end;

{ GetDirNames() retrieves the names of all subdirectories in a given path. }
function GetDirNames(path: String): TStringList;
var
  i: Integer;
begin

  Result := GetFileNames(path + '*.*', faDirectory);
  i := 0;
  while i < Result.Count do
  begin
    if (not HasAttrib(FileGetAttr(Result[i]), faDirectory))
      or (Result[i][1] = '.') then Result.Delete(i)
    else INC(i);
  end;

end;

{ FileInfo() retrieves information on any given file or directory in the form of
  a TSearchRec structure. If the file does not exist, an exception is raised. }
function FileInfo(filename: String): TSearchRec;
var
  s: TSearchRec;
begin

  if not FileExists(filename) then
    raise Exception.Create('File not found: ' + filename);
  FindFirst(filename, faAnyFile, s);
  Result := s;
  FindClose(s);

end;

{ HasAttrib() tests whether or not a file (with attributes fileAttrib) has the
  testAttrib attribute bit set. }
function HasAttrib(fileAttrib, testAttrib: Integer): Boolean;
begin

  Result := (fileAttrib and testAttrib) <> 0;

end;

{ ExecWait() executes the application indicated by FileName, and doesn't return
  until that application terminates. }
procedure ExecWait(FileName: String; WorkingDir: String; showCmd: Integer);
var
  startinfo: TStartupInfo;
  processinfo: TProcessInformation;
  hProcess: Integer;
  exitCode: Cardinal;
  wdir: PChar;
begin

  FillChar(startinfo, SizeOf(startinfo), 0);
  with startinfo do
  begin
    cb := SizeOf(startinfo);
    lpReserved := nil;
    lpTitle := nil;
    dwFlags := STARTF_USESHOWWINDOW;
    wShowWindow := showCmd;
  end;
  if WorkingDir = '' then wdir := nil else wdir := PChar(WorkingDir);
  if CreateProcess(nil, PChar(FileName), nil, nil, FALSE, CREATE_DEFAULT_ERROR_MODE,
                  nil, wdir, startinfo, processinfo) then
  begin
    hProcess := processinfo.hProcess;
    exitCode := STILL_ACTIVE;
    while exitCode = STILL_ACTIVE do GetExitCodeProcess(hProcess, exitCode);
  end;

end;

function GetFileSize(FileName: String): Cardinal;
var
  f: File;
begin

  AssignFile(f, FileName);
  Reset(f, 1);
  Result := FileSize(f);
  CloseFile(f);

end;

end.
