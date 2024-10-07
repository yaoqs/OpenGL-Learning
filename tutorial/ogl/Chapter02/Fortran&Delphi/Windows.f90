Module Windows_Type

    integer, parameter :: C_NULL     = 0

    !       First some base types
    !DEC$ IF DEFINED (_ALPHA_)
    integer, parameter :: PVOID64 = 8       ! INTEGER(8)
    integer, parameter :: DWORDLONG = 8     ! INTEGER(8)
    integer, parameter :: POINTER_LEN = 8
    type T_LARGE_INTEGERX
       sequence
       integer(8) value
     end type T_LARGE_INTEGERX
    !DEC$ ELSE
    integer, parameter :: POINTER_LEN = 4
    type T_LARGE_INTEGERX
       sequence
       integer LowPart
       integer HighPart
     end type T_LARGE_INTEGERX
    !DEC$ ENDIF
    
    integer, parameter :: ANYSIZE_ARRAY = 1 ! used for foo[]
    integer, parameter :: DOUBLE = 8        ! REAL(8)
	! The S (for single) is to avoid conflict with the FLOAT intrinsic
    integer, parameter :: SFLOAT  = 4        ! REAL(4)
    integer, parameter :: HANDLE = 4        ! INTEGER(4)
    integer, parameter :: DWORD  = 4        ! INTEGER(4)
    integer, parameter :: ULONG  = 4        ! INTEGER(4) 
    integer, parameter :: LONG   = 4        ! INTEGER(4) 
    integer, parameter :: UINT   = 4        ! INTEGER(4) 
        ! The S (for signed) is to avoid conflict with the INT intrinsic
    integer, parameter :: SINT   = 4        ! INTEGER(4) 
    integer, parameter :: ENUM   = 4        ! INTEGER(4) 
    integer, parameter :: BOOL   = 4        ! INTEGER(4)
    integer, parameter :: WORD   = 2        ! INTEGER(2)
    integer, parameter :: USHORT = 2        ! INTEGER(2)
    integer, parameter :: SHORT  = 2        ! INTEGER(2)
    integer, parameter :: BYTE   = 1        ! INTEGER(1)
    integer, parameter :: UCHAR  = 1        ! INTEGER(1)
	! The S (for signed) is to avoid conflict with the CHAR intrinsic
    integer, parameter :: SCHAR  = 1        ! INTEGER(1)
    integer, parameter :: WCHAR  = 1        ! INTEGER(2)
    character, pointer :: NULL_CHARACTER
    
    ! some pointer names, they are all integer(4) for the moment 
    integer, parameter :: PDOUBLE  = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: PFLOAT   = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: PHANDLE  = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: PDWORD   = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: PULONG   = POINTER_LEN      ! INTEGER(4) 
    integer, parameter :: PLONG    = POINTER_LEN      ! INTEGER(4) 
    integer, parameter :: PUINT    = POINTER_LEN      ! INTEGER(4) 
    integer, parameter :: PINT     = POINTER_LEN      ! INTEGER(4) 
    integer, parameter :: PBOOL    = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: PWORD    = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: PUSHORT  = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: PSHORT   = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: PBYTE    = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: PUCHAR   = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: PCHAR    = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: PVOID    = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: PCVOID   = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: PCSTR    = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: PCWSTR   = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: PWSTR    = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: PSTR     = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: LPDOUBLE = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: LPFLOAT  = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: LPHANDLE = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: LPDWORD  = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: LPULONG  = POINTER_LEN      ! INTEGER(4) 
    integer, parameter :: LPLONG   = POINTER_LEN      ! INTEGER(4) 
    integer, parameter :: LPUINT   = POINTER_LEN      ! INTEGER(4) 
    integer, parameter :: LPINT    = POINTER_LEN      ! INTEGER(4) 
    integer, parameter :: LPBOOL   = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: LPWORD   = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: LPUSHORT = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: LPSHORT  = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: LPBYTE   = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: LPUCHAR  = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: LPCHAR   = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: LPVOID   = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: LPCVOID  = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: LPCSTR   = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: LPCWSTR  = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: LPWSTR   = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: LPSTR    = POINTER_LEN      ! INTEGER(4)
    integer, parameter :: APPLICATION_ERROR_MASK        =  #20000000
    integer, parameter :: ERROR_SEVERITY_SUCCESS        =  #00000000
    integer, parameter :: ERROR_SEVERITY_INFORMATIONAL  =  #40000000
    integer, parameter :: ERROR_SEVERITY_WARNING        =  #80000000 
    integer, parameter :: ERROR_SEVERITY_ERROR          =  #C0000000 
    
    type T_LARGE_INTEGER
       sequence
       integer LowPart
       integer HighPart
    end type T_LARGE_INTEGER
    
    ! 
    !   Doubly linked list structure.  Can be used as either a list head, or
    !   as link words.
    ! 
    
    type  T_LIST_ENTRY
      sequence
      integer Flink 
      integer Blink 
    end type  T_LIST_ENTRY
    
    ! 
    !   Singly linked list structure. Can be used as either a list head, or
    !   as link words.
    ! 
    
    type  T_SINGLE_LIST_ENTRY
      sequence
      integer Next 
    end type  T_SINGLE_LIST_ENTRY
    
    integer, parameter :: MINCHAR  =  #80        
    integer, parameter :: MAXCHAR  =  #7f        
    integer, parameter :: MINSHORT =  #8000      
    integer, parameter :: MAXSHORT =  #7fff      
    integer, parameter :: MINLONG  =  #80000000 
    integer, parameter :: MAXLONG  =  #7fffffff  
    integer, parameter :: MAXBYTE  =  #ff        
    integer, parameter :: MAXWORD  =  #ffff      
    integer, parameter :: MAXDWORD =  #FFFFFFFF

    !  * Dialog Box Command IDs
    integer, parameter :: IDOK = 1
    integer, parameter :: IDCANCEL = 2
    integer, parameter :: IDABORT = 3
    integer, parameter :: IDRETRY = 4
    integer, parameter :: IDIGNORE = 5
    integer, parameter :: IDYES = 6
    integer, parameter :: IDNO = 7
    integer, parameter :: IDCLOSE = 8
    integer, parameter :: IDHELP = 9

    integer, parameter :: VK_LBUTTON    =  #01
    integer, parameter :: VK_RBUTTON    =  #02
    integer, parameter :: VK_CANCEL     =  #03
    integer, parameter :: VK_MBUTTON    =  #04    !  NOT contiguous with L & RBUTTON   
    integer, parameter :: VK_BACK       =  #08
    integer, parameter :: VK_TAB        =  #09
    integer, parameter :: VK_CLEAR      =  #0C
    integer, parameter :: VK_RETURN     =  #0D
    integer, parameter :: VK_SHIFT      =  #10
    integer, parameter :: VK_CONTROL    =  #11
    integer, parameter :: VK_MENU       =  #12
    integer, parameter :: VK_PAUSE      =  #13
    integer, parameter :: VK_CAPITAL    =  #14
    integer, parameter :: VK_ESCAPE     =  #1B
    integer, parameter :: VK_SPACE      =  #20
    integer, parameter :: VK_PRIOR      =  #21
    integer, parameter :: VK_NEXT       =  #22
    integer, parameter :: VK_END        =  #23
    integer, parameter :: VK_HOME       =  #24
    integer, parameter :: VK_LEFT       =  #25
    integer, parameter :: VK_UP         =  #26
    integer, parameter :: VK_RIGHT      =  #27
    integer, parameter :: VK_DOWN       =  #28
    integer, parameter :: VK_SELECT     =  #29
    integer, parameter :: VK_PRINT      =  #2A
    integer, parameter :: VK_EXECUTE    =  #2B
    integer, parameter :: VK_SNAPSHOT   =  #2C
    integer, parameter :: VK_INSERT     =  #2D
    integer, parameter :: VK_DELETE     =  #2E
    integer, parameter :: VK_HELP       =  #2F
    !   VK_0 thru VK_9 are the same as ASCII '0' thru '9' (0x30 - 0x39)   
    !   VK_A thru VK_Z are the same as ASCII 'A' thru 'Z' (0x41 - 0x5A)   
    integer, parameter :: VK_NUMPAD0    =  #60
    integer, parameter :: VK_NUMPAD1    =  #61
    integer, parameter :: VK_NUMPAD2    =  #62
    integer, parameter :: VK_NUMPAD3    =  #63
    integer, parameter :: VK_NUMPAD4    =  #64
    integer, parameter :: VK_NUMPAD5    =  #65
    integer, parameter :: VK_NUMPAD6    =  #66
    integer, parameter :: VK_NUMPAD7    =  #67
    integer, parameter :: VK_NUMPAD8    =  #68
    integer, parameter :: VK_NUMPAD9    =  #69
    integer, parameter :: VK_MULTIPLY   =  #6A
    integer, parameter :: VK_ADD        =  #6B
    integer, parameter :: VK_SEPARATOR  =  #6C
    integer, parameter :: VK_SUBTRACT   =  #6D
    integer, parameter :: VK_DECIMAL    =  #6E
    integer, parameter :: VK_DIVIDE     =  #6F
    integer, parameter :: VK_F1 =  #70
    integer, parameter :: VK_F2 =  #71
    integer, parameter :: VK_F3 =  #72
    integer, parameter :: VK_F4 =  #73
    integer, parameter :: VK_F5 =  #74
    integer, parameter :: VK_F6 =  #75
    integer, parameter :: VK_F7 =  #76
    integer, parameter :: VK_F8 =  #77
    integer, parameter :: VK_F9 =  #78
    integer, parameter :: VK_F10 =  #79
    integer, parameter :: VK_F11 =  #7A
    integer, parameter :: VK_F12 =  #7B
    integer, parameter :: VK_F13 =  #7C
    integer, parameter :: VK_F14 =  #7D
    integer, parameter :: VK_F15 =  #7E
    integer, parameter :: VK_F16 =  #7F
    integer, parameter :: VK_F17 =  #80
    integer, parameter :: VK_F18 =  #81
    integer, parameter :: VK_F19 =  #82
    integer, parameter :: VK_F20 =  #83
    integer, parameter :: VK_F21 =  #84
    integer, parameter :: VK_F22 =  #85
    integer, parameter :: VK_F23 =  #86
    integer, parameter :: VK_F24 =  #87
    integer, parameter :: VK_NUMLOCK =  #90
    integer, parameter :: VK_SCROLL =  #91
    !  * VK_L* & VK_R* - left and right Alt, Ctrl and Shift virtual keys.
    integer, parameter :: VK_LSHIFT     =  #A0
    integer, parameter :: VK_RSHIFT     =  #A1
    integer, parameter :: VK_LCONTROL   =  #A2
    integer, parameter :: VK_RCONTROL   =  #A3
    integer, parameter :: VK_LMENU      =  #A4
    integer, parameter :: VK_RMENU      =  #A5
    integer, parameter :: VK_ATTN       =  #F6
    integer, parameter :: VK_CRSEL      =  #F7
    integer, parameter :: VK_EXSEL      =  #F8
    integer, parameter :: VK_EREOF      =  #F9
    integer, parameter :: VK_PLAY       =  #FA
    integer, parameter :: VK_ZOOM       =  #FB
    integer, parameter :: VK_NONAME     =  #FC
    integer, parameter :: VK_PA1        =  #FD
    integer, parameter :: VK_OEM_CLEAR  =  #FE
    integer, parameter :: VK_KANA = #15
    integer, parameter :: VK_HANGEUL = #15
    integer, parameter :: VK_HANGUL = #15
    integer, parameter :: VK_JUNJA = #17
    integer, parameter :: VK_FINAL = #18
    integer, parameter :: VK_HANJA = #19
    integer, parameter :: VK_KANJI = #19
    integer, parameter :: VK_CONVERT = #1C
    integer, parameter :: VK_NONCONVERT = #1D
    integer, parameter :: VK_ACCEPT = #1E
    integer, parameter :: VK_MODECHANGE = #1F
    integer, parameter :: VK_LWIN = #5B
    integer, parameter :: VK_RWIN = #5C
    integer, parameter :: VK_APPS = #5D
    integer, parameter :: VK_PROCESSKEY = #E5

    integer, parameter :: MB_OK                 =  #00000000
    integer, parameter :: MB_OKCANCEL           =  #00000001
    integer, parameter :: MB_ABORTRETRYIGNORE   =  #00000002
    integer, parameter :: MB_YESNOCANCEL        =  #00000003
    integer, parameter :: MB_YESNO              =  #00000004
    integer, parameter :: MB_RETRYCANCEL        =  #00000005
    integer, parameter :: MB_ICONHAND           =  #00000010
    integer, parameter :: MB_ICONQUESTION       =  #00000020
    integer, parameter :: MB_ICONEXCLAMATION    =  #00000030
    integer, parameter :: MB_ICONASTERISK       =  #00000040
    integer, parameter :: MB_ICONINFORMATION    = MB_ICONASTERISK
    integer, parameter :: MB_ICONSTOP           = MB_ICONHAND
    integer, parameter :: MB_DEFBUTTON1         =  #00000000
    integer, parameter :: MB_DEFBUTTON2         =  #00000100
    integer, parameter :: MB_DEFBUTTON3         =  #00000200
    integer, parameter :: MB_APPLMODAL          =  #00000000
    integer, parameter :: MB_SYSTEMMODAL        =  #00001000
    integer, parameter :: MB_TASKMODAL          =  #00002000
    integer, parameter :: MB_NOFOCUS                =  #00008000
    integer, parameter :: MB_SETFOREGROUND          =  #00010000
    integer, parameter :: MB_DEFAULT_DESKTOP_ONLY   =  #00020000
    integer, parameter :: MB_TYPEMASK   =  #0000000F
    integer, parameter :: MB_ICONMASK   =  #000000F0
    integer, parameter :: MB_DEFMASK    =  #00000F00
    integer, parameter :: MB_MODEMASK   =  #00003000
    integer, parameter :: MB_MISCMASK   =  #0000C000
    integer, parameter :: MB_PRECOMPOSED    =  #00000001     !  use precomposed chars   
    integer, parameter :: MB_COMPOSITE      =  #00000002     !  use composite chars   
    integer, parameter :: MB_USEGLYPHCHARS  =  #00000004     !  use glyph chars, not ctrl chars   
    integer, parameter :: MB_USERICON = #00000080
    integer, parameter :: MB_DEFBUTTON4 = #00000300
    integer, parameter :: MB_HELP = #00004000
    integer, parameter :: MB_TOPMOST = #00040000
    integer, parameter :: MB_RIGHT = #00080000
    integer, parameter :: MB_RTLREADING = #00100000
    integer, parameter :: MB_ERR_INVALID_CHARS = #00000008
    integer, parameter :: MB_SERVICE_NOTIFICATION = #00200000
    integer, parameter :: MB_SERVICE_NOTIFICATION_NT3X = #00040000

    !$DEFINE IDI_APPLICATION   = MAKEINTRESOURCE(32512)
    !$DEFINE  IDI_HAND          = MAKEINTRESOURCE(32513)
    !$DEFINE  IDI_QUESTION      = MAKEINTRESOURCE(32514)
    !$DEFINE  IDI_EXCLAMATION   = MAKEINTRESOURCE(32515)
    !$DEFINE  IDI_ASTERISK      = MAKEINTRESOURCE(32516)
    !integer, parameter :: IDI_APPLICATION   = MAKEINTRESOURCE(32512)
    !integer, parameter :: IDI_HAND          = MAKEINTRESOURCE(32513)
    !integer, parameter :: IDI_QUESTION      = MAKEINTRESOURCE(32514)
    !integer, parameter :: IDI_EXCLAMATION   = MAKEINTRESOURCE(32515)
    !integer, parameter :: IDI_ASTERISK      = MAKEINTRESOURCE(32516)
    integer*4, parameter :: IDI_APPLICATION     =  #00007F00
    integer*4, parameter :: IDI_HAND            =  #00007F01
    integer*4, parameter :: IDI_QUESTION        =  #00007F02
    integer*4, parameter :: IDI_EXCLAMATION     =  #00007F03
    integer*4, parameter :: IDI_ASTERISK        =  #00007F04
    integer*4, parameter :: IDI_WINLOGO =  ( ( (32517)))

    !$DEFINE  IDC_ARROW           = MAKEINTRESOURCE(32512)
    !$DEFINE   IDC_IBEAM           = MAKEINTRESOURCE(32513)
    !$DEFINE   IDC_WAIT            = MAKEINTRESOURCE(32514)
    !$DEFINE   IDC_CROSS           = MAKEINTRESOURCE(32515)
    !$DEFINE   IDC_UPARROW         = MAKEINTRESOURCE(32516)
    !$DEFINE   IDC_SIZE            = MAKEINTRESOURCE(32640)
    !$DEFINE   IDC_ICON            = MAKEINTRESOURCE(32641)
    !$DEFINE   IDC_SIZENWSE        = MAKEINTRESOURCE(32642)
    !$DEFINE   IDC_SIZENESW        = MAKEINTRESOURCE(32643)
    !$DEFINE   IDC_SIZEWE          = MAKEINTRESOURCE(32644)
    !$DEFINE   IDC_SIZENS          = MAKEINTRESOURCE(32645)
    !$DEFINE   IDC_SIZEALL         = MAKEINTRESOURCE(32646) !  not in win3.1   
    !$DEFINE   IDC_NO              = MAKEINTRESOURCE(32648) !  not in win3.1   
    !$DEFINE   IDC_APPSTARTING     = MAKEINTRESOURCE(32650) !  not in win3.1   
    !integer, parameter :: IDC_ARROW           = MAKEINTRESOURCE(32512)
    !integer, parameter :: IDC_IBEAM           = MAKEINTRESOURCE(32513)
    !integer, parameter :: IDC_WAIT            = MAKEINTRESOURCE(32514)
    !integer, parameter :: IDC_CROSS           = MAKEINTRESOURCE(32515)
    !integer, parameter :: IDC_UPARROW         = MAKEINTRESOURCE(32516)
    !integer, parameter :: IDC_SIZE            = MAKEINTRESOURCE(32640)
    !integer, parameter :: IDC_ICON            = MAKEINTRESOURCE(32641)
    !integer, parameter :: IDC_SIZENWSE        = MAKEINTRESOURCE(32642)
    !integer, parameter :: IDC_SIZENESW        = MAKEINTRESOURCE(32643)
    !integer, parameter :: IDC_SIZEWE          = MAKEINTRESOURCE(32644)
    !integer, parameter :: IDC_SIZENS          = MAKEINTRESOURCE(32645)
    !integer, parameter :: IDC_SIZEALL         = MAKEINTRESOURCE(32646) !  not in win3.1   
    !integer, parameter :: IDC_NO              = MAKEINTRESOURCE(32648) !  not in win3.1   
    !integer, parameter :: IDC_APPSTARTING     = MAKEINTRESOURCE(32650) !  not in win3.1   
    integer*4, parameter :: IDC_ARROW             =  #00007F00
    integer*4, parameter :: IDC_IBEAM             =  #00007F01
    integer*4, parameter :: IDC_WAIT              =  #00007F02
    integer*4, parameter :: IDC_CROSS             =  #00007F03
    integer*4, parameter :: IDC_UPARROW           =  #00007F04
    integer*4, parameter :: IDC_SIZE              =  #00007F80
    integer*4, parameter :: IDC_ICON              =  #00007F81
    integer*4, parameter :: IDC_SIZENWSE          =  #00007F82
    integer*4, parameter :: IDC_SIZENESW          =  #00007F83
    integer*4, parameter :: IDC_SIZEWE            =  #00007F84
    integer*4, parameter :: IDC_SIZENS            =  #00007F85
    integer*4, parameter :: IDC_SIZEALL           =  #00007F86
    integer*4, parameter :: IDC_NO                =  #00007F88
    integer*4, parameter :: IDC_APPSTARTING       =  #00007F8A
    integer, parameter :: IDC_HELP =  ( ( (32651)))

      integer, parameter :: CDS_UPDATEREGISTRY = #00000001
      integer, parameter :: CDS_TEST = #00000002
      integer, parameter :: CDS_FULLSCREEN = #00000004
      integer, parameter :: CDS_GLOBAL = #00000008
      integer, parameter :: CDS_SET_PRIMARY = #00000010
      integer, parameter :: CDS_RESET = #40000000
      integer, parameter :: CDS_SETRECT = #20000000
      integer, parameter :: CDS_NORESET = #10000000

    integer, parameter :: SW_HIDE               = 0
    integer, parameter :: SW_SHOWNORMAL         = 1
    integer, parameter :: SW_NORMAL             = 1
    integer, parameter :: SW_SHOWMINIMIZED      = 2
    integer, parameter :: SW_SHOWMAXIMIZED      = 3
    integer, parameter :: SW_MAXIMIZE           = 3
    integer, parameter :: SW_SHOWNOACTIVATE     = 4
    integer, parameter :: SW_SHOW               = 5
    integer, parameter :: SW_MINIMIZE           = 6
    integer, parameter :: SW_SHOWMINNOACTIVE    = 7
    integer, parameter :: SW_SHOWNA             = 8
    integer, parameter :: SW_RESTORE            = 9
    integer, parameter :: SW_SHOWDEFAULT        = 10
    integer, parameter :: SW_MAX                = 10
    integer, parameter :: SW_PARENTCLOSING  = 1
    integer, parameter :: SW_OTHERZOOM      = 2
    integer, parameter :: SW_PARENTOPENING  = 3
    integer, parameter :: SW_OTHERUNZOOM    = 4
    integer, parameter :: SW_SCROLLCHILDREN =  #0001  !  Scroll children within *lprcScroll.   
    integer, parameter :: SW_INVALIDATE     =  #0002  !  Invalidate after scrolling   
    integer, parameter :: SW_ERASE          =  #0004  !  If SW_INVALIDATE, don't send WM_ERASEBACKGROUND   
    integer, parameter :: SW_FORCEMINIMIZE = 11


    integer(KIND=4), parameter :: PFD_TYPE_RGBA             = 0
    integer(KIND=4), parameter :: PFD_TYPE_COLORINDEX   = 1
    integer(KIND=4), parameter :: PFD_MAIN_PLANE = 0
    integer(KIND=4), parameter :: PFD_OVERLAY_PLANE = 1
    integer(KIND=4), parameter :: PFD_UNDERLAY_PLANE = -1
    integer(KIND=4), parameter :: PFD_DOUBLEBUFFER         =    #00000001
    integer(KIND=4), parameter :: PFD_STEREO               =    #00000002
    integer(KIND=4), parameter :: PFD_DRAW_TO_WINDOW       =    #00000004
    integer(KIND=4), parameter :: PFD_DRAW_TO_BITMAP       =    #00000008
    integer(KIND=4), parameter :: PFD_SUPPORT_GDI          =    #00000010
    integer(KIND=4), parameter :: PFD_SUPPORT_OPENGL       =    #00000020
    integer(KIND=4), parameter :: PFD_GENERIC_FORMAT       =    #00000040
    integer(KIND=4), parameter :: PFD_NEED_PALETTE         =    #00000080
    integer(KIND=4), parameter :: PFD_NEED_SYSTEM_PALETTE  =    #00000100
    integer(KIND=4), parameter :: PFD_DOUBLEBUFFER_DONTCARE=    #40000000
    integer(KIND=4), parameter :: PFD_STEREO_DONTCARE      =    #80000000
    integer(KIND=4), parameter :: PFD_SWAP_EXCHANGE = #00000200
    integer(KIND=4), parameter :: PFD_SWAP_COPY = #00000400
    integer(KIND=4), parameter :: PFD_SWAP_LAYER_BUFFERS = #00000800
    integer(KIND=4), parameter :: PFD_GENERIC_ACCELERATED = #00001000
    integer(KIND=4), parameter :: PFD_SUPPORT_DIRECTDRAW = #00002000
    integer(KIND=4), parameter :: PFD_DEPTH_DONTCARE = #20000000


    integer(KIND=4), parameter :: CS_VREDRAW =  #0001
    integer(KIND=4), parameter :: CS_HREDRAW =  #0002
    integer(KIND=4), parameter :: CS_KEYCVTWINDOW =  #0004
    integer(KIND=4), parameter :: CS_DBLCLKS =  #0008
    integer(KIND=4), parameter :: CS_OWNDC =  #0020
    integer(KIND=4), parameter :: CS_CLASSDC =  #0040
    integer(KIND=4), parameter :: CS_PARENTDC =  #0080
    integer(KIND=4), parameter :: CS_NOKEYCVT =  #0100
    integer(KIND=4), parameter :: CS_NOCLOSE =  #0200
    integer(KIND=4), parameter :: CS_SAVEBITS =  #0800
    integer(KIND=4), parameter :: CS_BYTEALIGNCLIENT =  #1000
    integer(KIND=4), parameter :: CS_BYTEALIGNWINDOW =  #2000
    integer(KIND=4), parameter :: CS_GLOBALCLASS =  #4000
    integer(KIND=4), parameter :: CS_E_FIRST = #80040164
    integer(KIND=4), parameter :: CS_E_LAST = #80040168
    integer(KIND=4), parameter :: CS_E_PACKAGE_NOTFOUND = ( #80040164)
    integer(KIND=4), parameter :: CS_E_NOT_DELETABLE = ( #80040165)
    integer(KIND=4), parameter :: CS_E_CLASS_NOTFOUND = ( #80040166)
    integer(KIND=4), parameter :: CS_E_INVALID_VERSION = ( #80040167)
    integer(KIND=4), parameter :: CS_E_NO_CLASSSTORE = ( #80040168)
    integer(KIND=4), parameter :: CS_ENABLE = #00000001
    integer(KIND=4), parameter :: CS_DISABLE = #00000002
    integer(KIND=4), parameter :: CS_DELETE_TRANSFORM = #00000003
    integer(KIND=4), parameter :: CS_IME = #00010000
    integer(KIND=4), parameter :: CS_INSERTCHAR = #2000
    integer(KIND=4), parameter :: CS_NOMOVECARET = #4000

    integer(KIND=4), parameter :: WS_OVERLAPPED =  #00000000
    integer(KIND=4), parameter :: WS_POPUP =  #80000000 !-2147483647  
    integer(KIND=4), parameter :: WS_CHILD =  #40000000
    integer(KIND=4), parameter :: WS_MINIMIZE =  #20000000
    integer(KIND=4), parameter :: WS_VISIBLE =  #10000000
    integer(KIND=4), parameter :: WS_DISABLED =  #08000000
    integer(KIND=4), parameter :: WS_CLIPSIBLINGS =  #04000000
    integer(KIND=4), parameter :: WS_CLIPCHILDREN =  #02000000
    integer(KIND=4), parameter :: WS_MAXIMIZE =  #01000000
    integer(KIND=4), parameter :: WS_CAPTION =  #00C00000     !  WS_BORDER | WS_DLGFRAME    
    integer(KIND=4), parameter :: WS_BORDER =  #00800000
    integer(KIND=4), parameter :: WS_DLGFRAME =  #00400000
    integer(KIND=4), parameter :: WS_VSCROLL =  #00200000
    integer(KIND=4), parameter :: WS_HSCROLL =  #00100000
    integer(KIND=4), parameter :: WS_SYSMENU =  #00080000
    integer(KIND=4), parameter :: WS_THICKFRAME =  #00040000
    integer(KIND=4), parameter :: WS_GROUP =  #00020000
    integer(KIND=4), parameter :: WS_TABSTOP =  #00010000
    integer(KIND=4), parameter :: WS_MINIMIZEBOX =  #00020000
    integer(KIND=4), parameter :: WS_MAXIMIZEBOX =  #00010000
    integer(KIND=4), parameter :: WS_TILED      = WS_OVERLAPPED
    integer(KIND=4), parameter :: WS_ICONIC     = WS_MINIMIZE
    integer(KIND=4), parameter :: WS_SIZEBOX    = WS_THICKFRAME
    integer(KIND=4), parameter :: WS_CHILDWINDOW      = WS_CHILD
    integer(KIND=4), parameter :: WS_EX_DLGMODALFRAME =  #00000001
    integer(KIND=4), parameter :: WS_EX_NOPARENTNOTIFY =  #00000004
    integer(KIND=4), parameter :: WS_EX_TOPMOST =  #00000008
    integer(KIND=4), parameter :: WS_EX_ACCEPTFILES =  #00000010
    integer(KIND=4), parameter :: WS_EX_TRANSPARENT =  #00000020
    integer(KIND=4), parameter :: WS_OVERLAPPEDWINDOW   =  #00CF0000
    integer(KIND=4), parameter :: WS_POPUPWINDOW   =  #80880000
    integer(KIND=4), parameter :: WS_TILEDWINDOW  =  #00CF0000
    integer(KIND=4), parameter :: WS_EX_MDICHILD = #00000040
    integer(KIND=4), parameter :: WS_EX_TOOLWINDOW = #00000080
    integer(KIND=4), parameter :: WS_EX_WINDOWEDGE = #00000100
    integer(KIND=4), parameter :: WS_EX_CLIENTEDGE = #00000200
    integer(KIND=4), parameter :: WS_EX_CONTEXTHELP = #00000400
    integer(KIND=4), parameter :: WS_EX_RIGHT = #00001000
    integer(KIND=4), parameter :: WS_EX_LEFT = #00000000
    integer(KIND=4), parameter :: WS_EX_RTLREADING = #00002000
    integer(KIND=4), parameter :: WS_EX_LTRREADING = #00000000
    integer(KIND=4), parameter :: WS_EX_LEFTSCROLLBAR = #00004000
    integer(KIND=4), parameter :: WS_EX_RIGHTSCROLLBAR = #00000000
    integer(KIND=4), parameter :: WS_EX_CONTROLPARENT = #00010000
    integer(KIND=4), parameter :: WS_EX_STATICEDGE = #00020000
    integer(KIND=4), parameter :: WS_EX_APPWINDOW = #00040000
    integer(KIND=4), parameter :: WS_EX_OVERLAPPEDWINDOW = (#00000100 .OR. #00000200)
    integer(KIND=4), parameter :: WS_EX_PALETTEWINDOW = (#00000100 .OR. #00000080 .OR. #00000008)

    integer(KIND=4), parameter :: PM_NOREMOVE   =  #0000
    integer(KIND=4), parameter :: PM_REMOVE     =  #0001
    integer(KIND=4), parameter :: PM_NOYIELD    =  #0002

    !  * Identifiers for the WM_SHOWWINDOW message
    !  * WM_KEYUP/DOWN/CHAR HIWORD(lParam) flags
    integer(KIND=4), parameter :: WM_NULL       =  #0000
    integer(KIND=4), parameter :: WM_CREATE     =  #0001
    integer(KIND=4), parameter :: WM_DESTROY    =  #0002
    integer(KIND=4), parameter :: WM_MOVE       =  #0003
    integer(KIND=4), parameter :: WM_SIZE       =  #0005
    integer(KIND=4), parameter :: WM_ACTIVATE   =  #0006
    !  * WM_ACTIVATE state values
    integer(KIND=4), parameter :: WM_SETFOCUS           =  #0007
    integer(KIND=4), parameter :: WM_KILLFOCUS          =  #0008
    integer(KIND=4), parameter :: WM_ENABLE             =  #000A
    integer(KIND=4), parameter :: WM_SETREDRAW          =  #000B
    integer(KIND=4), parameter :: WM_SETTEXT            =  #000C
    integer(KIND=4), parameter :: WM_GETTEXT            =  #000D
    integer(KIND=4), parameter :: WM_GETTEXTLENGTH      =  #000E
    integer(KIND=4), parameter :: WM_PAINT              =  #000F
    integer(KIND=4), parameter :: WM_CLOSE              =  #0010
    integer(KIND=4), parameter :: WM_QUERYENDSESSION    =  #0011
    integer(KIND=4), parameter :: WM_QUIT               =  #0012
    integer(KIND=4), parameter :: WM_QUERYOPEN          =  #0013
    integer(KIND=4), parameter :: WM_ERASEBKGND         =  #0014
    integer(KIND=4), parameter :: WM_SYSCOLORCHANGE     =  #0015
    integer(KIND=4), parameter :: WM_ENDSESSION         =  #0016
    integer(KIND=4), parameter :: WM_SHOWWINDOW         =  #0018
    integer(KIND=4), parameter :: WM_WININICHANGE       =  #001A
    integer(KIND=4), parameter :: WM_DEVMODECHANGE      =  #001B
    integer(KIND=4), parameter :: WM_ACTIVATEAPP        =  #001C
    integer(KIND=4), parameter :: WM_FONTCHANGE         =  #001D
    integer(KIND=4), parameter :: WM_TIMECHANGE         =  #001E
    integer(KIND=4), parameter :: WM_CANCELMODE         =  #001F
    integer(KIND=4), parameter :: WM_SETCURSOR          =  #0020
    integer(KIND=4), parameter :: WM_MOUSEACTIVATE      =  #0021
    integer(KIND=4), parameter :: WM_CHILDACTIVATE      =  #0022
    integer(KIND=4), parameter :: WM_QUEUESYNC          =  #0023
    integer(KIND=4), parameter :: WM_GETMINMAXINFO      =  #0024
    !  * Struct pointed to by WM_GETMINMAXINFO lParam
    integer(KIND=4), parameter :: WM_PAINTICON              =  #0026
    integer(KIND=4), parameter :: WM_ICONERASEBKGND         =  #0027
    integer(KIND=4), parameter :: WM_NEXTDLGCTL             =  #0028
    integer(KIND=4), parameter :: WM_SPOOLERSTATUS          =  #002A
    integer(KIND=4), parameter :: WM_DRAWITEM               =  #002B
    integer(KIND=4), parameter :: WM_MEASUREITEM            =  #002C
    integer(KIND=4), parameter :: WM_DELETEITEM             =  #002D
    integer(KIND=4), parameter :: WM_VKEYTOITEM             =  #002E
    integer(KIND=4), parameter :: WM_CHARTOITEM             =  #002F
    integer(KIND=4), parameter :: WM_SETFONT                =  #0030
    integer(KIND=4), parameter :: WM_GETFONT                =  #0031
    integer(KIND=4), parameter :: WM_SETHOTKEY              =  #0032
    integer(KIND=4), parameter :: WM_GETHOTKEY              =  #0033
    integer(KIND=4), parameter :: WM_QUERYDRAGICON          =  #0037
    integer(KIND=4), parameter :: WM_COMPAREITEM            =  #0039
    integer(KIND=4), parameter :: WM_COMPACTING             =  #0041
    integer(KIND=4), parameter :: WM_OTHERWINDOWCREATED     =  #0042  !  no longer suported   
    integer(KIND=4), parameter :: WM_OTHERWINDOWDESTROYED   =  #0043  !  no longer suported   
    integer(KIND=4), parameter :: WM_COMMNOTIFY             =  #0044  !  no longer suported   
    integer(KIND=4), parameter :: WM_WINDOWPOSCHANGING      =  #0046
    integer(KIND=4), parameter :: WM_WINDOWPOSCHANGED       =  #0047
    integer(KIND=4), parameter :: WM_POWER =  #0048
    !  * wParam for WM_POWER window message and DRV_POWER driver notification
    integer(KIND=4), parameter :: WM_COPYDATA =  #004A
    integer(KIND=4), parameter :: WM_CANCELJOURNAL =  #004B
    !  * lParam of WM_COPYDATA message points to...
    integer(KIND=4), parameter :: WM_NOTIFY             =  #004E
    integer(KIND=4), parameter :: WM_NOTIFYFORMAT       =  #0055
    integer(KIND=4), parameter :: WM_NCCREATE           =  #0081
    integer(KIND=4), parameter :: WM_NCDESTROY          =  #0082
    integer(KIND=4), parameter :: WM_NCCALCSIZE         =  #0083
    integer(KIND=4), parameter :: WM_NCHITTEST          =  #0084
    integer(KIND=4), parameter :: WM_NCPAINT            =  #0085
    integer(KIND=4), parameter :: WM_NCACTIVATE         =  #0086
    integer(KIND=4), parameter :: WM_GETDLGCODE         =  #0087
    integer(KIND=4), parameter :: WM_NCMOUSEMOVE        =  #00A0
    integer(KIND=4), parameter :: WM_NCLBUTTONDOWN      =  #00A1
    integer(KIND=4), parameter :: WM_NCLBUTTONUP        =  #00A2
    integer(KIND=4), parameter :: WM_NCLBUTTONDBLCLK    =  #00A3
    integer(KIND=4), parameter :: WM_NCRBUTTONDOWN      =  #00A4
    integer(KIND=4), parameter :: WM_NCRBUTTONUP        =  #00A5
    integer(KIND=4), parameter :: WM_NCRBUTTONDBLCLK    =  #00A6
    integer(KIND=4), parameter :: WM_NCMBUTTONDOWN      =  #00A7
    integer(KIND=4), parameter :: WM_NCMBUTTONUP        =  #00A8
    integer(KIND=4), parameter :: WM_NCMBUTTONDBLCLK    =  #00A9
    integer(KIND=4), parameter :: WM_KEYFIRST =  #0100
    integer(KIND=4), parameter :: WM_KEYDOWN =  #0100
    integer(KIND=4), parameter :: WM_KEYUP =  #0101
    integer(KIND=4), parameter :: WM_CHAR =  #0102
    integer(KIND=4), parameter :: WM_DEADCHAR =  #0103
    integer(KIND=4), parameter :: WM_SYSKEYDOWN =  #0104
    integer(KIND=4), parameter :: WM_SYSKEYUP =  #0105
    integer(KIND=4), parameter :: WM_SYSCHAR =  #0106
    integer(KIND=4), parameter :: WM_SYSDEADCHAR =  #0107
    integer(KIND=4), parameter :: WM_KEYLAST =  #0108
    integer(KIND=4), parameter :: WM_INITDIALOG =  #0110
    integer(KIND=4), parameter :: WM_COMMAND =  #0111
    integer(KIND=4), parameter :: WM_SYSCOMMAND =  #0112
    integer(KIND=4), parameter :: WM_TIMER =  #0113
    integer(KIND=4), parameter :: WM_HSCROLL =  #0114
    integer(KIND=4), parameter :: WM_VSCROLL =  #0115
    integer(KIND=4), parameter :: WM_INITMENU =  #0116
    integer(KIND=4), parameter :: WM_INITMENUPOPUP =  #0117
    integer(KIND=4), parameter :: WM_MENUSELECT =  #011F
    integer(KIND=4), parameter :: WM_MENUCHAR =  #0120
    integer(KIND=4), parameter :: WM_ENTERIDLE =  #0121
    integer(KIND=4), parameter :: WM_CTLCOLORMSGBOX     =  #0132
    integer(KIND=4), parameter :: WM_CTLCOLOREDIT       =  #0133
    integer(KIND=4), parameter :: WM_CTLCOLORLISTBOX    =  #0134
    integer(KIND=4), parameter :: WM_CTLCOLORBTN        =  #0135
    integer(KIND=4), parameter :: WM_CTLCOLORDLG        =  #0136
    integer(KIND=4), parameter :: WM_CTLCOLORSCROLLBAR  =  #0137
    integer(KIND=4), parameter :: WM_CTLCOLORSTATIC     =  #0138
    integer(KIND=4), parameter :: WM_MOUSEFIRST =  #0200
    integer(KIND=4), parameter :: WM_MOUSEMOVE =  #0200
    integer(KIND=4), parameter :: WM_LBUTTONDOWN =  #0201
    integer(KIND=4), parameter :: WM_LBUTTONUP =  #0202
    integer(KIND=4), parameter :: WM_LBUTTONDBLCLK =  #0203
    integer(KIND=4), parameter :: WM_RBUTTONDOWN =  #0204
    integer(KIND=4), parameter :: WM_RBUTTONUP =  #0205
    integer(KIND=4), parameter :: WM_RBUTTONDBLCLK =  #0206
    integer(KIND=4), parameter :: WM_MBUTTONDOWN =  #0207
    integer(KIND=4), parameter :: WM_MBUTTONUP =  #0208
    integer(KIND=4), parameter :: WM_MBUTTONDBLCLK =  #0209
    integer(KIND=4), parameter :: WM_MOUSELAST =  #0209
    integer(KIND=4), parameter :: WM_PARENTNOTIFY =  #0210
    integer(KIND=4), parameter :: WM_ENTERMENULOOP =  #0211
    integer(KIND=4), parameter :: WM_EXITMENULOOP =  #0212
    integer(KIND=4), parameter :: WM_MDICREATE =  #0220
    integer(KIND=4), parameter :: WM_MDIDESTROY =  #0221
    integer(KIND=4), parameter :: WM_MDIACTIVATE =  #0222
    integer(KIND=4), parameter :: WM_MDIRESTORE =  #0223
    integer(KIND=4), parameter :: WM_MDINEXT =  #0224
    integer(KIND=4), parameter :: WM_MDIMAXIMIZE =  #0225
    integer(KIND=4), parameter :: WM_MDITILE =  #0226
    integer(KIND=4), parameter :: WM_MDICASCADE =  #0227
    integer(KIND=4), parameter :: WM_MDIICONARRANGE =  #0228
    integer(KIND=4), parameter :: WM_MDIGETACTIVE =  #0229
    integer(KIND=4), parameter :: WM_MDISETMENU =  #0230
    integer(KIND=4), parameter :: WM_DROPFILES =  #0233
    integer(KIND=4), parameter :: WM_MDIREFRESHMENU =  #0234
    integer(KIND=4), parameter :: WM_CUT =  #0300
    integer(KIND=4), parameter :: WM_COPY =  #0301
    integer(KIND=4), parameter :: WM_PASTE =  #0302
    integer(KIND=4), parameter :: WM_CLEAR =  #0303
    integer(KIND=4), parameter :: WM_UNDO =  #0304
    integer(KIND=4), parameter :: WM_RENDERFORMAT =  #0305
    integer(KIND=4), parameter :: WM_RENDERALLFORMATS =  #0306
    integer(KIND=4), parameter :: WM_DESTROYCLIPBOARD =  #0307
    integer(KIND=4), parameter :: WM_DRAWCLIPBOARD =  #0308
    integer(KIND=4), parameter :: WM_PAINTCLIPBOARD =  #0309
    integer(KIND=4), parameter :: WM_VSCROLLCLIPBOARD =  #030A
    integer(KIND=4), parameter :: WM_SIZECLIPBOARD =  #030B
    integer(KIND=4), parameter :: WM_ASKCBFORMATNAME =  #030C
    integer(KIND=4), parameter :: WM_CHANGECBCHAIN =  #030D
    integer(KIND=4), parameter :: WM_HSCROLLCLIPBOARD =  #030E
    integer(KIND=4), parameter :: WM_QUERYNEWPALETTE =  #030F
    integer(KIND=4), parameter :: WM_PALETTEISCHANGING =  #0310
    integer(KIND=4), parameter :: WM_PALETTECHANGED =  #0311
    integer(KIND=4), parameter :: WM_HOTKEY =  #0312
    integer(KIND=4), parameter :: WM_PENWINFIRST =  #0380
    integer(KIND=4), parameter :: WM_PENWINLAST =  #038F
    integer(KIND=4), parameter :: WM_USER =  #0400
    !  * WM_SYNCTASK Commands
    !  * WM_NCHITTEST and T_MOUSEHOOKSTRUCT Mouse Position Codes
    !  * WM_MOUSEACTIVATE Return Codes
    !  * WM_SIZE message wParam values
    !  * WM_WINDOWPOSCHANGING/CHANGED struct pointed to by lParam
    !  * WM_NCCALCSIZE parameter structure
    !  * WM_NCCALCSIZE "window valid rect" return values
    integer(KIND=4),parameter :: WM_MOUSEHOVER =                    Z'02A1'
    integer(KIND=4),parameter :: WM_MOUSELEAVE =                    Z'02A3'
    !  * wParam Flags for WM_MDITILE and WM_MDICASCADE messages.
    integer(KIND=4), parameter :: WM_CHOOSEFONT_GETLOGFONT  = (WM_USER + 1)
    integer(KIND=4), parameter :: WM_DDE_FIRST      =  #03E0
    integer(KIND=4), parameter :: WM_DDE_INITIATE   = (WM_DDE_FIRST)
    integer(KIND=4), parameter :: WM_DDE_TERMINATE  = (WM_DDE_FIRST+1)
    integer(KIND=4), parameter :: WM_DDE_ADVISE     = (WM_DDE_FIRST+2)
    integer(KIND=4), parameter :: WM_DDE_UNADVISE   = (WM_DDE_FIRST+3)
    integer(KIND=4), parameter :: WM_DDE_ACK        = (WM_DDE_FIRST+4)
    integer(KIND=4), parameter :: WM_DDE_DATA       = (WM_DDE_FIRST+5)
    integer(KIND=4), parameter :: WM_DDE_REQUEST    = (WM_DDE_FIRST+6)
    integer(KIND=4), parameter :: WM_DDE_POKE       = (WM_DDE_FIRST+7)
    integer(KIND=4), parameter :: WM_DDE_EXECUTE    = (WM_DDE_FIRST+8)
    integer(KIND=4), parameter :: WM_DDE_LAST       = (WM_DDE_FIRST+8)
    ! | Structure of wStatus (LOWORD(lParam)) in WM_DDE_ACK message
    ! |       sent in response to a WM_DDE_DATA, WM_DDE_REQUEST, WM_DDE_POKE,
    ! |       WM_DDE_ADVISE, or WM_DDE_UNADVISE message.
    ! | WM_DDE_ADVISE parameter structure for hOptions (LOWORD(lParam))
    ! |       WM_DDE_DATA parameter structure for hData (LOWORD(lParam)).
    ! | WM_DDE_POKE parameter structure for hData (LOWORD(lParam)).
    integer(KIND=4), parameter :: WM_INPUTLANGCHANGEREQUEST = #0050
    integer(KIND=4), parameter :: WM_INPUTLANGCHANGE = #0051
    integer(KIND=4), parameter :: WM_TCARD = #0052
    integer(KIND=4), parameter :: WM_HELP = #0053
    integer(KIND=4), parameter :: WM_USERCHANGED = #0054
    integer(KIND=4), parameter :: WM_CONTEXTMENU = #007B
    integer(KIND=4), parameter :: WM_STYLECHANGING = #007C
    integer(KIND=4), parameter :: WM_STYLECHANGED = #007D
    integer(KIND=4), parameter :: WM_DISPLAYCHANGE = #007E
    integer(KIND=4), parameter :: WM_GETICON = #007F
    integer(KIND=4), parameter :: WM_SETICON = #0080
    integer(KIND=4), parameter :: WM_SYNCPAINT = #0088
    integer(KIND=4), parameter :: WM_IME_STARTCOMPOSITION = #010D
    integer(KIND=4), parameter :: WM_IME_ENDCOMPOSITION = #010E
    integer(KIND=4), parameter :: WM_IME_COMPOSITION = #010F
    integer(KIND=4), parameter :: WM_IME_KEYLAST = #010F
    integer(KIND=4), parameter :: WM_NEXTMENU = #0213
    integer(KIND=4), parameter :: WM_SIZING = #0214
    integer(KIND=4), parameter :: WM_CAPTURECHANGED = #0215
    integer(KIND=4), parameter :: WM_MOVING = #0216
    integer(KIND=4), parameter :: WM_POWERBROADCAST = #0218
    integer(KIND=4), parameter :: WM_DEVICECHANGE = #0219
    integer(KIND=4), parameter :: WM_ENTERSIZEMOVE = #0231
    integer(KIND=4), parameter :: WM_EXITSIZEMOVE = #0232
    integer(KIND=4), parameter :: WM_IME_SETCONTEXT = #0281
    integer(KIND=4), parameter :: WM_IME_NOTIFY = #0282
    integer(KIND=4), parameter :: WM_IME_CONTROL = #0283
    integer(KIND=4), parameter :: WM_IME_COMPOSITIONFULL = #0284
    integer(KIND=4), parameter :: WM_IME_SELECT = #0285
    integer(KIND=4), parameter :: WM_IME_CHAR = #0286
    integer(KIND=4), parameter :: WM_IME_KEYDOWN = #0290
    integer(KIND=4), parameter :: WM_IME_KEYUP = #0291
    integer(KIND=4), parameter :: WM_PRINT = #0317
    integer(KIND=4), parameter :: WM_PRINTCLIENT = #0318
    integer(KIND=4), parameter :: WM_HANDHELDFIRST = #0358
    integer(KIND=4), parameter :: WM_HANDHELDLAST = #035F
    integer(KIND=4), parameter :: WM_AFXFIRST = #0360
    integer(KIND=4), parameter :: WM_AFXLAST = #037F
    integer(KIND=4), parameter :: WM_APP = #8000
    integer(KIND=4), parameter :: WM_CHOOSEFONT_SETLOGFONT = (#0400 + 101)
    integer(KIND=4), parameter :: WM_CHOOSEFONT_SETFLAGS = (#0400 + 102)
    integer(KIND=4), parameter :: WM_PSD_PAGESETUPDLG = (#0400 )
    integer(KIND=4), parameter :: WM_PSD_FULLPAGERECT = (#0400+1)
    integer(KIND=4), parameter :: WM_PSD_MINMARGINRECT = (#0400+2)
    integer(KIND=4), parameter :: WM_PSD_MARGINRECT = (#0400+3)
    integer(KIND=4), parameter :: WM_PSD_GREEKTEXTRECT = (#0400+4)
    integer(KIND=4), parameter :: WM_PSD_ENVSTAMPRECT = (#0400+5)
    integer(KIND=4), parameter :: WM_PSD_YAFULLPAGERECT = (#0400+6)
    integer(KIND=4), parameter :: WM_MOUSEWHEEL = #020A

    integer(KIND=4), parameter :: DM_UPDATE   = 1
    integer(KIND=4), parameter :: DM_COPY     = 2
    integer(KIND=4), parameter :: DM_PROMPT   = 4
    integer(KIND=4), parameter :: DM_MODIFY   = 8
    integer(KIND=4), parameter :: DM_IN_BUFFER   = DM_MODIFY
    integer(KIND=4), parameter :: DM_IN_PROMPT   = DM_PROMPT
    integer(KIND=4), parameter :: DM_OUT_BUFFER  = DM_COPY
    integer(KIND=4), parameter :: DM_OUT_DEFAULT = DM_UPDATE
    integer(KIND=4), parameter :: DM_SPECVERSION =  #320
    integer(KIND=4), parameter :: DM_ORIENTATION       =  #0000001
    integer(KIND=4), parameter :: DM_PAPERSIZE         =  #0000002
    integer(KIND=4), parameter :: DM_PAPERLENGTH       =  #0000004
    integer(KIND=4), parameter :: DM_PAPERWIDTH        =  #0000008
    integer(KIND=4), parameter :: DM_SCALE             =  #0000010
    integer(KIND=4), parameter :: DM_COPIES            =  #0000100
    integer(KIND=4), parameter :: DM_DEFAULTSOURCE     =  #0000200
    integer(KIND=4), parameter :: DM_PRINTQUALITY      =  #0000400
    integer(KIND=4), parameter :: DM_COLOR             =  #0000800
    integer(KIND=4), parameter :: DM_DUPLEX            =  #0001000
    integer(KIND=4), parameter :: DM_YRESOLUTION       =  #0002000
    integer(KIND=4), parameter :: DM_TTOPTION          =  #0004000
    integer(KIND=4), parameter :: DM_COLLATE           =  #0008000
    integer(KIND=4), parameter :: DM_FORMNAME          =  #0010000
    integer(KIND=4), parameter :: DM_GRAYSCALE =  #00000001
    integer(KIND=4), parameter :: DM_INTERLACED =  #00000002
    !integer(KIND=4), parameter :: DM_UPDATE  = 1
    !integer(KIND=4), parameter :: DM_COPY    = 2
    !integer(KIND=4), parameter :: DM_PROMPT  = 4
    !integer(KIND=4), parameter :: DM_MODIFY  = 8
    !integer(KIND=4), parameter :: DM_IN_BUFFER     = DM_MODIFY
    !integer(KIND=4), parameter :: DM_IN_PROMPT     = DM_PROMPT
    !integer(KIND=4), parameter :: DM_OUT_BUFFER    = DM_COPY
    !integer(KIND=4), parameter :: DM_OUT_DEFAULT   = DM_UPDATE
    integer(KIND=4), parameter :: DM_GETDEFID         = (WM_USER+0)
    integer(KIND=4), parameter :: DM_SETDEFID         = (WM_USER+1)
    !  * Returned in HIWORD() of DM_GETDEFID result if msg is supported
    integer(KIND=4), parameter :: DM_LOGPIXELS = #00020000
    integer(KIND=4), parameter :: DM_BITSPERPEL = #00040000
    integer(KIND=4), parameter :: DM_PELSWIDTH = #00080000
    integer(KIND=4), parameter :: DM_PELSHEIGHT = #00100000
    integer(KIND=4), parameter :: DM_DISPLAYFLAGS = #00200000
    integer(KIND=4), parameter :: DM_DISPLAYFREQUENCY = #00400000
    integer(KIND=4), parameter :: DM_ICMMETHOD = #00800000
    integer(KIND=4), parameter :: DM_ICMINTENT = #01000000
    integer(KIND=4), parameter :: DM_MEDIATYPE = #02000000
    integer(KIND=4), parameter :: DM_DITHERTYPE = #04000000
    integer(KIND=4), parameter :: DM_PANNINGWIDTH = #08000000
    integer(KIND=4), parameter :: DM_PANNINGHEIGHT = #10000000
    integer(KIND=4), parameter :: DM_REPOSITION = (#0400+2)


! types utils:

    type  T_WNDCLASS
        sequence
        integer         style 
        integer         lpfnWndProc 
        integer         cbClsExtra 
        integer         cbWndExtra 
        integer         hInstance 
        integer         hIcon 
        integer         hCursor 
        integer         hbrBackground 
        integer         lpszMenuName 
        integer         lpszClassName 
    end type  T_WNDCLASS

 TYPE T_WNDCLASSEXA
 SEQUENCE
   integer(UINT) cbSize ! knowns  UINT 
   integer(UINT) style ! knowns  UINT 
   integer(LPVOID) lpfnWndProc ! pointers  WNDPROC 
   integer(SINT) cbClsExtra ! knowns  int 
   integer(SINT) cbWndExtra ! knowns  int 
   integer(HANDLE) hInstance ! handles  HINSTANCE 
   integer(HANDLE) hIcon ! handles  HICON 
   integer(HANDLE) hCursor ! typedefs  HCURSOR 
   integer(HANDLE) hbrBackground ! handles  HBRUSH 
   integer(LPCSTR) lpszMenuName ! knowns  LPCSTR 
   integer(LPCSTR) lpszClassName ! knowns  LPCSTR 
   integer(HANDLE) hIconSm ! handles  HICON 
 END TYPE

    !   size of a device name string   
    integer(KIND=4), parameter :: CCHDEVICENAME = 32
    !   size of a form name string   
    integer(KIND=4), parameter :: CCHFORMNAME = 32
    type T_DEVMODE
        sequence
        character(CCHDEVICENAME) dmDeviceName  
        integer*2 dmSpecVersion 
        integer*2 dmDriverVersion 
        integer*2 dmSize 
        integer*2 dmDriverExtra 
        integer*4 dmFields 
        integer*2 dmOrientation 
        integer*2 dmPaperSize 
        integer*2 dmPaperLength 
        integer*2 dmPaperWidth 
        integer*2 dmScale 
        integer*2 dmCopies 
        integer*2 dmDefaultSource 
        integer*2 dmPrintQuality 
        integer*2 dmColor 
        integer*2 dmDuplex 
        integer*2 dmYResolution 
        integer*2 dmTTOption 
        integer*2 dmCollate 
        character(CCHFORMNAME)   dmFormName 
        integer*2 dmLogPixels 
        integer*4 dmBitsPerPel 
        integer*4 dmPelsWidth 
        integer*4 dmPelsHeight 
        integer*4 dmDisplayFlags 
        integer*4 dmDisplayFrequency 
        integer*4 dmICMMethod 
        integer*4 dmICMIntent 
        integer*4 dmMediaType 
        integer*4 dmDitherType 
        integer*4 dmICCManufacturer 
        integer*4 dmICCModel 
        integer*4 dmPanningWidth 
        integer*4 dmPanningHeight 
    end type T_DEVMODE

    type  T_POINT
        sequence
        integer x 
        integer y 
    end type  T_POINT
    !  * Message structure
    type  T_MSG
        sequence
        integer         hwnd 
        integer         message 
        integer         wParam 
        integer         lParam 
        integer         time 
        type (T_POINT)  pt 
    end type  T_MSG

    type  T_RECT
        sequence
        integer left 
        integer top 
        integer right 
        integer bottom 
    end type  T_RECT
    type  T_PAINTSTRUCT
        sequence
        integer     hdc 
        logical(4)  fErase 
        type (T_RECT) rcPaint 
        logical(4)  fRestore 
        logical(4)  fIncUpdate 
        BYTE        rgbReserved (32 )
    end type  T_PAINTSTRUCT

    type T_PIXELFORMATDESCRIPTOR
        sequence
        integer(2)  nSize
        integer(2)  nVersion
        integer(4)  dwFlags;
        BYTE  iPixelType
        BYTE  cColorBits
        BYTE  cRedBits
        BYTE  cRedShift
        BYTE  cGreenBits
        BYTE  cGreenShift
        BYTE  cBlueBits
        BYTE  cBlueShift
        BYTE  cAlphaBits
        BYTE  cAlphaShift
        BYTE  cAccumBits
        BYTE  cAccumRedBits
        BYTE  cAccumGreenBits
        BYTE  cAccumBlueBits
        BYTE  cAccumAlphaBits
        BYTE  cDepthBits
        BYTE  cStencilBits
        BYTE  cAuxBuffers
        BYTE  iLayerType
        BYTE  bReserved
        integer dwLayerMask
        integer dwVisibleMask
        integer dwDamageMask
    end type T_PIXELFORMATDESCRIPTOR

EndModule Windows_Type

!####################################################################################
!####################################################################################
!####################################################################################
!####################################################################################


Module Windows

Use Windows_Type

!**************************************************************************
!DEC$OBJCOMMENT LIB:"USER32.LIB"

interface MessageBox !lib=user32.lib
	integer(4) function  MessageBox (hWnd  ,lpText ,lpCaption  ,uType ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_MessageBoxA@16' :: MessageBox
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'MessageBoxA'    :: MessageBox
	!DEC$ ENDIF
	!DEC$ ATTRIBUTES REFERENCE :: lpText
	!DEC$ ATTRIBUTES REFERENCE :: lpCaption
	integer(4)      hWnd
	character*(*)   lpText
	character*(*)   lpCaption 
	integer(4)      uType
	end function MessageBox
end interface

interface ReleaseDC !lib=user32.lib
	integer(4) function  ReleaseDC (hWnd ,hDC ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_ReleaseDC@8' :: ReleaseDC
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'ReleaseDC'   :: ReleaseDC
	!DEC$ ENDIF
	integer hWnd
	integer hDC
	end function ReleaseDC
end interface

interface DestroyWindow !lib=user32.lib
	logical(4) function  DestroyWindow (hWnd ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_DestroyWindow@4' :: DestroyWindow
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'DestroyWindow'   :: DestroyWindow
	!DEC$ ENDIF
	integer hWnd
	end function DestroyWindow
end interface

INTERFACE ChangeDisplaySettings  !lib=user32.lib
  FUNCTION ChangeDisplaySettings( lpDevMode, dwFlags)
	Use Windows_Type
	integer(LONG) :: ChangeDisplaySettings ! LONG
    !DEC$IF DEFINED(_X86_)
    !DEC$ ATTRIBUTES STDCALL, ALIAS:'_ChangeDisplaySettingsA@8' :: ChangeDisplaySettings
    !DEC$ ELSE
    !DEC$ ATTRIBUTES STDCALL, ALIAS:'ChangeDisplaySettingsA' :: ChangeDisplaySettings
    !DEC$ ENDIF
      !DEC$ ATTRIBUTES REFERENCE :: lpDevMode
      TYPE (T_DEVMODE) lpDevMode ! LPDEVMODEA lpDevMode
      integer(DWORD) dwFlags ! DWORD dwFlags
  END FUNCTION
END INTERFACE

INTERFACE ChangeDisplaySettingsEx
  FUNCTION ChangeDisplaySettingsEx( lpszDeviceName, &
  								    lpDevMode, &
                                    hwnd, &
                                    dwflags, &
                                    lParam)
	Use Windows_Type
    integer(LONG) :: ChangeDisplaySettingsEx ! LONG
    !DEC$ ATTRIBUTES DEFAULT :: ChangeDisplaySettingsEx
    !DEC$IF DEFINED(_X86_)
    !DEC$ ATTRIBUTES STDCALL, ALIAS:'_ChangeDisplaySettingsExA@20' :: ChangeDisplaySettingsEx
    !DEC$ ELSE
    !DEC$ ATTRIBUTES STDCALL, ALIAS:'ChangeDisplaySettingsExA' :: ChangeDisplaySettingsEx
    !DEC$ ENDIF
      !DEC$ ATTRIBUTES REFERENCE :: lpszDeviceName
      character*(*) lpszDeviceName ! LPCSTR lpszDeviceName
      !DEC$ ATTRIBUTES REFERENCE :: lpDevMode
      TYPE (T_DEVMODE) lpDevMode ! LPDEVMODEA lpDevMode
      integer(HANDLE) hwnd ! HWND hwnd
      integer(DWORD) dwflags ! DWORD dwflags
      integer(LPVOID) lParam ! LPVOID lParam
  END FUNCTION
END INTERFACE

interface ShowCursor !lib=user32.lib
  integer(4) function  ShowCursor (bShow ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_ShowCursor@4' :: ShowCursor
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'ShowCursor'   :: ShowCursor
	!DEC$ ENDIF
	logical(4) bShow
  end function ShowCursor
end interface

interface LoadIcon !lib=user32.lib
  integer(4) function  LoadIcon (hInstance ,lpIconName ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_LoadIconA@8' :: LoadIcon
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'LoadIconA'   :: LoadIcon
	!DEC$ ENDIF
	integer hInstance
	integer lpIconName
  end function LoadIcon
end interface

interface !lib=user32.lib
  integer(4) function  LoadCursor (hInstance ,lpCursorName ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_LoadCursorA@8' :: LoadCursor
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'LoadCursorA'   :: LoadCursor
	!DEC$ ENDIF
	integer hInstance
	integer lpCursorName
  end function LoadCursor
end interface

interface RegisterClass !lib=user32.lib
  integer(4) function  RegisterClass (lpWndClass ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_RegisterClassA@4' :: RegisterClass
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'RegisterClassA'   :: RegisterClass
	!DEC$ ENDIF
	!DEC$ ATTRIBUTES REFERENCE :: lpWndClass
	Use Windows_Type
	type(T_WNDCLASS) lpWndClass
  end function RegisterClass
end interface
interface UnregisterClass !lib=user32.lib
  logical(4) function  UnregisterClass (lpClassName ,hInstance ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_UnregisterClassA@8' :: UnregisterClass
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'UnregisterClassA'   :: UnregisterClass
	!DEC$ ENDIF
	!DEC$ ATTRIBUTES REFERENCE :: lpClassName
	character*(*)   lpClassName
	integer         hInstance
  end function UnregisterClass
end interface
INTERFACE RegisterClassEx !lib=user32.lib
  FUNCTION RegisterClassEx(arg1)
	Use Windows_Type
    integer(USHORT) :: RegisterClassEx ! ATOM
    !DEC$IF DEFINED(_X86_)
    !DEC$ ATTRIBUTES STDCALL, ALIAS:'_RegisterClassExA@4' :: RegisterClassEx
    !DEC$ ELSE
    !DEC$ ATTRIBUTES STDCALL, ALIAS:'RegisterClassExA' :: RegisterClassEx
    !DEC$ ENDIF
    !DEC$ ATTRIBUTES REFERENCE :: arg1
    TYPE (T_WNDCLASSEXA)  arg1 ! WNDCLASSEXA*  arg1
  END FUNCTION
END INTERFACE

interface CreateWindowEx !lib=user32.lib
  integer(4) function  CreateWindowEx (dwExStyle ,lpClassName ,lpWindowName, &
            dwStyle ,X ,Y ,nWidth ,nHeight ,hWndParent  ,hMenu ,hInstance ,lpParam ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_CreateWindowExA@48' :: CreateWindowEx
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'CreateWindowExA'    :: CreateWindowEx
	!DEC$ ENDIF
	!DEC$ ATTRIBUTES REFERENCE :: lpClassName
	!DEC$ ATTRIBUTES REFERENCE :: lpWindowName
	integer         dwExStyle
	character*(*)   lpClassName
	character*(*)   lpWindowName
	integer         dwStyle
	integer         X
	integer         Y
	integer         nWidth
	integer         nHeight
	integer         hWndParent 
	integer         hMenu
	integer         hInstance
	integer         lpParam
  end function CreateWindowEx
end interface

interface GetDC !lib=user32.lib
  integer(4) function  GetDC (hWnd ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_GetDC@4' :: GetDC
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'GetDC'   :: GetDC
	!DEC$ ENDIF
	integer hWnd
  end function GetDC
end interface
interface GetDCEx !lib=user32.lib
  integer(4) function  GetDCEx (hWnd  ,hrgnClip ,flags ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_GetDCEx@12' :: GetDCEx
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'GetDCEx'    :: GetDCEx
	!DEC$ ENDIF
	integer hWnd 
	integer hrgnClip
	integer flags
  end function GetDCEx
end interface

interface ShowWindow !lib=user32.lib
  logical(4) function  ShowWindow (hWnd ,nCmdShow ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_ShowWindow@8' :: ShowWindow
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'ShowWindow'   :: ShowWindow
	!DEC$ ENDIF
	integer hWnd
	integer nCmdShow
  end function ShowWindow
end interface

interface SetForegroundWindow !lib=user32.lib
  logical(4) function  SetForegroundWindow (hWnd ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_SetForegroundWindow@4' :: SetForegroundWindow
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'SetForegroundWindow'   :: SetForegroundWindow
	!DEC$ ENDIF
	integer hWnd
  end function SetForegroundWindow
end interface

interface SetFocus !lib=user32.lib
  integer(4) function  SetFocus (hWnd )
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_SetFocus@4' :: SetFocus
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'SetFocus'   :: SetFocus
	!DEC$ ENDIF
	integer hWnd
  end function SetFocus
end interface

interface WaitMessage !lib=user32.lib
  logical(4) function  WaitMessage () 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_WaitMessage@0' :: WaitMessage
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'WaitMessage'   :: WaitMessage
	!DEC$ ENDIF
  end function WaitMessage
end interface

interface PeekMessage !lib=user32.lib
  logical(4) function  PeekMessage (lpMsg ,hWnd  ,wMsgFilterMin ,wMsgFilterMax ,wRemoveMsg ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_PeekMessageA@20' :: PeekMessage
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'PeekMessageA'    :: PeekMessage
	!DEC$ ENDIF
	!DEC$ ATTRIBUTES REFERENCE :: lpMsg
	Use Windows_Type
	type(T_MSG)     lpMsg
	integer         hWnd 
	integer         wMsgFilterMin
	integer         wMsgFilterMax
	integer         wRemoveMsg
  end function PeekMessage
end interface

interface DefWindowProc !lib=user32.lib
  integer(4) function  DefWindowProc (hWnd ,Msg ,wParam ,lParam ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_DefWindowProcA@16' :: DefWindowProc
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'DefWindowProcA'    :: DefWindowProc
	!DEC$ ENDIF
	integer hWnd
	integer Msg
	integer wParam
	integer lParam
  end function DefWindowProc
end interface

interface TranslateMessage !lib=user32.lib
  logical(4) function  TranslateMessage (lpMsg ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_TranslateMessage@4' :: TranslateMessage
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'TranslateMessage'   :: TranslateMessage
	!DEC$ ENDIF
	!DEC$ ATTRIBUTES REFERENCE :: lpMsg
	Use Windows_Type
	type (T_MSG) lpMsg
  end function TranslateMessage
end interface

interface DispatchMessage !lib=user32.lib
  logical(4) function  DispatchMessage (lpMsg ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_DispatchMessageA@4' :: DispatchMessage
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'DispatchMessageA'   :: DispatchMessage
	!DEC$ ENDIF
	!DEC$ ATTRIBUTES REFERENCE :: lpMsg
	Use Windows_Type
	type (T_MSG) lpMsg
  end function DispatchMessage
end interface

interface SendMessage !lib=user32.lib
  integer*4 function  SendMessage (hWnd ,Msg ,wParam ,lParam ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_SendMessageA@16' :: SendMessage
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'SendMessageA'    :: SendMessage
	!DEC$ ENDIF
	integer hWnd
	integer Msg
	integer wParam
	integer lParam
  end function SendMessage
end interface

interface PostQuitMessage !lib=user32.lib
  subroutine  PostQuitMessage (nExitCode ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_PostQuitMessage@4' :: PostQuitMessage
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'PostQuitMessage'   :: PostQuitMessage
	!DEC$ ENDIF
	integer nExitCode
  end subroutine PostQuitMessage
end interface

interface BeginPaint !lib=user32.lib
  integer(4) function  BeginPaint (hWnd ,lpPaint ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_BeginPaint@8' :: BeginPaint
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'BeginPaint'   :: BeginPaint
	!DEC$ ENDIF
	!DEC$ ATTRIBUTES REFERENCE :: lpPaint
	Use Windows_Type
	integer                 hWnd
	type (T_PAINTSTRUCT)    lpPaint
  end function BeginPaint
end interface

interface EndPaint !lib=user32.lib
  logical(4) function  EndPaint (hWnd ,lpPaint ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_EndPaint@8' :: EndPaint
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'EndPaint'   :: EndPaint
	!DEC$ ENDIF
	!DEC$ ATTRIBUTES REFERENCE :: lpPaint
	Use Windows_Type
	integer                 hWnd
	type (T_PAINTSTRUCT)    lpPaint
  end function EndPaint
end interface


!**************************************************************************
!DEC$OBJCOMMENT LIB:"KERNEL32.LIB"

interface GetModuleHandle !lib=kernel32.lib
  integer(4) function  GetModuleHandle (lpModuleName   ) 
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_GetModuleHandleA@4' :: GetModuleHandle
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'GetModuleHandleA'   :: GetModuleHandle
	!DEC$ ENDIF
	integer lpModuleName   
  end function GetModuleHandle
end interface

!**************************************************************************
!DEC$OBJCOMMENT LIB:"GDI32.LIB"

interface ChoosePixelFormat !lib=gdi32.lib
  integer function ChoosePixelFormat (hDC, lpPixelFormatDescriptor)
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_ChoosePixelFormat@8' :: ChoosePixelFormat
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'ChoosePixelFormat'   :: ChoosePixelFormat
	!DEC$ ENDIF
	!DEC$ ATTRIBUTES REFERENCE :: lppixelFormatDescriptor
	Use Windows_Type
	integer                         hDC
	type (T_PIXELFORMATDESCRIPTOR)  lppixelFormatDescriptor
  end function ChoosePixelFormat
end interface

interface SetPixelFormat !lib=gdi32.lib
  logical(4) function SetPixelFormat (dummy0, dummy1, dummy2)
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_SetPixelFormat@12' :: SetPixelFormat
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'SetPixelFormat'    :: SetPixelFormat
	!DEC$ ENDIF
	!DEC$ ATTRIBUTES REFERENCE :: dummy2
	Use Windows_Type
	integer(4)                      dummy0
	integer(4)                      dummy1
	type (T_PIXELFORMATDESCRIPTOR)  dummy2
  end function SetPixelFormat
end interface

interface !lib=gdi32.lib
  FUNCTION GetPixelFormat( arg1)
	Use Windows_Type
	integer(SINT) :: GetPixelFormat ! int
    !DEC$IF DEFINED(_X86_)
    !DEC$ ATTRIBUTES STDCALL, ALIAS:'_GetPixelFormat@4' :: GetPixelFormat
    !DEC$ ELSE
    !DEC$ ATTRIBUTES STDCALL, ALIAS:'GetPixelFormat' :: GetPixelFormat
    !DEC$ ENDIF
	integer(HANDLE) arg1 ! HDC arg1
  END FUNCTION
END INTERFACE

interface SwapBuffers !lib=gdi32.lib
  logical(4) function SwapBuffers (hDC)
	!DEC$ IF DEFINED(_X86_)
	!DEC$ ATTRIBUTES STDCALL, ALIAS : '_SwapBuffers@4' :: SwapBuffers
	!DEC$ ELSE
	!DEC$ ATTRIBUTES STDCALL, ALIAS :  'SwapBuffers'   :: SwapBuffers
	!DEC$ ENDIF
	integer(4)  hDC
  end function SwapBuffers
end interface


EndModule Windows

