Module GL_Display

  Use Opengl_GL
  Use Opengl_GLU
  Use Opengl_GLAUX
  Use Opengl_WGL
!---- includes Windows...
!  Use dfwin , C_NULL => NULL
  Use Windows
!------------------------
  implicit none

  Private 

  Interface
    function Key_up(i)
	  Logical(4) :: Key_up
	  Integer(4), intent(in) :: i
	end function Key_up
  End Interface

  Interface
    function Key_down(i)
	  Logical(4) :: Key_down
	  Integer(4), intent(in) :: i
	end function Key_down
  End Interface

  Interface
    Subroutine DrawGLScene()            ! Here's Where We Do All The Drawing
	end Subroutine DrawGLScene
  End Interface

  Interface
    function InitGL()                  ! All Setup For OpenGL Goes Here
       Logical(4) :: InitGL
	end function InitGL
  End Interface


  Interface LOWORD
    module procedure LOWORD_i
  End Interface
  Interface HIWORD
    module procedure HIWORD_i
  End Interface


  Logical(4), save, private :: fullscreen = .true.     ! default use full screen
  Logical(4), save, private :: active     = .true.     ! default use activeted
  Integer(4), save, private :: m_width      = 640      ! default   640
  Integer(4), save, private :: m_height     = 480      !         * 480
  Integer(4), save, private :: m_bits       = 16       !       and 16 bits of color
  Integer(4), save, private :: hRC = 0
  Integer(4), save, private :: hDC = 0
  Integer(4), save :: hwnd = 0
  Integer(4), save, private :: ignor
  Logical(4), save, private :: ignor_l
  Integer(4), save, private :: dwStyle
  Integer(4), save, private :: dwExStyle

  Character*(128), parameter, private :: Def_title = 'OpenGL Windows'C


  TYPE (T_DEVMODE), Pointer :: DevMode_Null => NULL() ! *djip*** pointer null for comback...

  public ReSizeGLScene, &
         InitGL, &
		 KillGLWindow


  contains

    Subroutine ReSizeGLScene (width, height)       !Resize And Initialize The GL Window

      integer(4), intent(in) :: width
      integer(4), intent(in) :: height

      Real(GlDouble) :: Aspect
      Real(GlDouble) :: ZWidth, ZHeight

	  if (height<=0) then; m_height=1; else; m_height=height; endif  ! Prevent A Divide By Zero By
	  if (width<=0) then; m_width=1; else; m_width=width; endif

      call glViewport(0,0,width,height)                    ! Reset The Current Viewport

      call glMatrixMode(GL_PROJECTION)                     ! Select The Projection Matrix
      call glLoadIdentity                                  ! Reset The Projection Matrix

	  ! Calculate The Aspect Ratio Of The Window
      ZWidth=m_Width
      ZHeight=m_Height
      Aspect=ZWidth/ZHeight
      call gluPerspective(45.0_GlDouble,Aspect,0.1_GlDouble,100.0_GlDouble)

      call glMatrixMode(GL_MODELVIEW)                      ! Select The Modelview Matrix
      call glLoadIdentity                                  ! Reset The Modelview Matrix

	End Subroutine ReSizeGLScene

    Subroutine KillGLWindow()       ! Properly Kill The Window

      if (hRC) then                  ! Do We Have A Rendering Context?
        if (.not.(wglMakeCurrent(C_NULL,C_NULL))) then      ! Are We Able To Release The DC And RC Contexts?
          ignor = MessageBox(C_NULL,"Release Of DC And RC Failed."C,"SHUTDOWN ERROR"C,(MB_OK .or. MB_ICONINFORMATION))
		endif
        if (.Not.wglDeleteContext(hRC)) then            ! Are We Able To Delete The RC?
          ignor = MessageBox(C_NULL,"Release Rendering Context Failed."C,"SHUTDOWN ERROR"C,(MB_OK .or. MB_ICONINFORMATION))
		endif
        hRC=C_NULL                                        ! Set RC To NULL
	  endif

      if (hDC .and. (.Not.ReleaseDC(hWnd,hDC)))	then    ! Are We Able To Release The DC
          ignor = MessageBox(C_NULL,"Release Device Context Failed."C,"SHUTDOWN ERROR"C,(MB_OK .or. MB_ICONINFORMATION))
          hDC= C_NULL                                      ! Set DC To NULL
      endif
      if (hWnd .and. (.Not.DestroyWindow(hWnd))) then   ! Are We Able To Destroy The Window?
          ignor = MessageBox(C_NULL,"Could Not Release hWnd."C,"SHUTDOWN ERROR"C,(MB_OK .or. MB_ICONINFORMATION))
          hWnd= C_NULL                                     ! Set hWnd To NULL
      endif
      if (fullscreen) then                              ! Are We In Fullscreen Mode?
          ignor = ChangeDisplaySettings(DevMode_Null,0) ! If So Switch Back To The Desktop
          ignor = ShowCursor(.TRUE.)                    ! Show Mouse Pointer
      endif
 	End Subroutine KillGLWindow

!/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
! *	title			- Title To Appear At The Top Of The Window				*
! *	width			- Width Of The GL Window Or Fullscreen Mode				*
! *	height			- Height Of The GL Window Or Fullscreen Mode			*
! *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
! *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
    Function CreateGLWindow(title, width, height, bits, fullscreenflag)

      Logical :: CreateGLWindow
	  Character*(*), Intent(in), Optional :: title
	  Integer, Intent(in), Optional :: width, height, bits
	  Logical, Intent(in), Optional :: fullscreenflag

      TYPE (T_DEVMODE) :: dmScreenSettings                   ! Device Mode
      character szApp*20

      Integer(GLuint) :: PixelFormat    ! Holds The Results After Searching For A Match
      Integer hInstance                 ! Holds The Instance Of The Application
      Type (t_WNDCLASS) wc              ! Windows Class Structure

      integer  ipfd
      parameter (ipfd=or(or(   PFD_DRAW_TO_WINDOW,  &  ! Format Must Support Window
                               PFD_SUPPORT_OPENGL), &  ! Format Must Support OpenGL 
			                   PFD_DOUBLEBUFFER))      ! Must Support Double Buffering

	  ! pfd Tells Windows How We Want Things To Be
      Type (t_PIXELFORMATDESCRIPTOR):: pfd
	  pfd = t_PIXELFORMATDESCRIPTOR( sizeof(pfd),       &  ! Size Of This Pixel Format Descriptor
                                     1,                 &  ! Version Number (?)
                                     ipfd,              &
                                     PFD_TYPE_RGBA,     &  ! Request An RGBA Format
                                     bits,              &  ! Select Our Color Depth
                                     0, 0, 0, 0, 0, 0,  &  ! color bits ignord (?)
                                     0,                 &  ! no alpha buffer
                                     0,                 &  ! Shift Bit Ignored (?)
                                     0,                 &  ! no accumulation buffer
                                     0, 0, 0, 0,        &  ! Accumulation Bits Ignored (?)
                                     16,                &  ! 16Bit Z-Buffer (Depth Buffer)  
                                     0,                 &  ! no stencil buffer
                                     0,                 &  ! no auxiliary buffer
                                     PFD_MAIN_PLANE,    &  ! Main Drawing Layer
                                     0,                 &  ! Reserved (?)
                                     0, 0, 0 )             ! Layer Masks Ignored (?)

      if (PRESENT(fullscreenflag)) fullscreen=fullscreenflag    ! Set The Global Fullscreen Flag
      if (PRESENT(width)) m_width=width                         ! Set The Global width
      if (PRESENT(height)) m_height=height                      ! Set The Global height
      if (PRESENT(bits)) m_bits=bits                            ! Set The Global height

      hInstance         = GetModuleHandle(C_NULL)                    ! Grab An Instance For Our Window

      szApp = 'OpenGL'C             ! *DJIP*** C is use for C string..with DVF..

      wc%style          = ior(ior(CS_HREDRAW,CS_VREDRAW),CS_OWNDC) ! Redraw On Size, And Own DC For Window.
      wc%lpfnWndProc    = loc(WndProc)                             ! WndProc Handles Messages
      wc%cbClsExtra     = 0                                        ! No Extra Window Data
      wc%cbWndExtra     = 0                                        ! No Extra Window Data
      wc%hInstance      = hInstance                                ! Set The Instance
      wc%hIcon          = LoadIcon(C_NULL, IDI_WINLOGO)            ! Load The Default Icon
      wc%hCursor        = LoadCursor(C_NULL, IDC_ARROW)            ! Load The Arrow Pointer
      wc%hbrBackground	= C_NULL                                   ! No Background Required For GL
      wc%lpszMenuName   = C_NULL                                   ! We Don't Want A Menu
      wc%lpszClassName  = loc(szApp)                               ! Set The Class Name

      if (RegisterClass(wc) .eq. 0) then                           ! Attempt To Register The Window Class
        ignor = MessageBox(C_NULL,"Failed To Register The Window Class."C,"ERROR"C, (MB_OK .or.MB_ICONEXCLAMATION))
        CreateGLWindow = .FALSE.                                   ! Return FALSE
        return
      endif

	
      if (fullscreen)  then                                      ! Attempt Fullscreen Mode?
!        call memset(dmScreenSettings,0,sizeof(dmScreenSettings)) ! Makes Sure Memory's Cleared
		dmScreenSettings%dmSize=sizeof(dmScreenSettings)         ! Size Of The Devmode Structure
		dmScreenSettings%dmPelsWidth	= width                  ! Selected Screen Width
		dmScreenSettings%dmPelsHeight	= height                 ! Selected Screen Height
		dmScreenSettings%dmBitsPerPel	= bits                   ! Selected Bits Per Pixel
		dmScreenSettings%dmFields=ior(ior(DM_BITSPERPEL,DM_PELSWIDTH),DM_PELSHEIGHT)

        ! Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
        if (ChangeDisplaySettings(dmScreenSettings,CDS_FULLSCREEN)) then !=DISP_CHANGE_SUCCESSFUL)
            ! If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
            if (MessageBox(C_NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?"C,"NeHe GL"C,ior(MB_YESNO,MB_ICONEXCLAMATION))==IDYES) then 
                fullscreen=.FALSE.        ! Windowed Mode Selected.  Fullscreen = FALSE
            else
                ! Pop Up A Message Box Letting User Know The Program Is Closing.
                ignor = MessageBox(C_NULL,"Program Will Now Close."C,"ERROR"C,ior(MB_OK,MB_ICONSTOP))
                CreateGLWindow = .FALSE.                ! Return FALSE
                return
            endif
	    endif
      endif

      if (fullscreen)  then                                         ! Are We Still In Fullscreen Mode?
        dwExStyle=WS_EX_APPWINDOW                                  ! Window Extended Style
        dwStyle=ior(ior(WS_POPUP,WS_CLIPSIBLINGS),WS_CLIPCHILDREN) ! Windows Style
        ignor = ShowCursor(.FALSE.)                                ! Hide Mouse Pointer
      else
        dwExStyle= ior(WS_EX_APPWINDOW, WS_EX_WINDOWEDGE)          ! Window Extended Style
        dwStyle=ior(ior(WS_OVERLAPPEDWINDOW, WS_CLIPSIBLINGS), WS_CLIPCHILDREN) !Windows Style
      endif

      ! Create The Window
      hWnd=CreateWindowEx( dwExStyle,     & ! Extended Style For The Window
                           "OpenGL"C,     & ! Class Name
                           title,         & ! Window Title
                           dwStyle,       & ! Window Style
                           0, 0,          & ! Window Position
                           width, height, & ! Selected Width And Height
                           C_NULL,        & ! No Parent Window
                           C_NULL,        & ! No Menu
                           hInstance,     & ! Instance
                           C_NULL)          ! Dont Pass Anything To WM_CREATE
      if (hWnd == 0) then
        call KillGLWindow()                        ! Reset The Display
        ignor = MessageBox(C_NULL,"Window Creation Error."C,"ERROR"C,ior(MB_OK,MB_ICONEXCLAMATION))
        CreateGLWindow = .FALSE.                   ! Return FALSE
        return
      endif

      hDC=GetDC(hWnd)
      if (hDC == 0)  then                          ! Did We Get A Device Context?
        call KillGLWindow()                        ! Reset The Display
        ignor = MessageBox(C_NULL,"Can't Create A GL Device Context."C,"ERROR"C,ior(MB_OK,MB_ICONEXCLAMATION))
        CreateGLWindow = .FALSE.                   ! Return FALSE
        return
      endif

      PixelFormat=ChoosePixelFormat(hDC,pfd)
	  if (PixelFormat == 0) then                   ! Did Windows Find A Matching Pixel Format?
        call KillGLWindow()                        ! Reset The Display
        ignor = MessageBox(C_NULL,"Can't Find A Suitable PixelFormat."C,"ERROR"C,ior(MB_OK,MB_ICONEXCLAMATION))
        CreateGLWindow = .FALSE.                   ! Return FALSE
        return
      endif

	  if(SetPixelFormat(hDC,PixelFormat,pfd) == 0) then ! Are We Able To Set The Pixel Format?
        call KillGLWindow()                         ! Reset The Display
        ignor = MessageBox(C_NULL,"Can't Set The PixelFormat."C,"ERROR"C,ior(MB_OK,MB_ICONEXCLAMATION))
        CreateGLWindow = .FALSE.                    ! Return FALSE
        return
      endif

      hRC=wglCreateContext(hDC)
      if (hRC == 0) then                            ! Are We Able To Get A Rendering Context?
        call KillGLWindow()                         ! Reset The Display
        ignor = MessageBox(C_NULL,"Can't Create A GL Rendering Context."C,"ERROR"C,ior(MB_OK,MB_ICONEXCLAMATION))
        CreateGLWindow = .FALSE.                    ! Return FALSE
        return
      endif

      if(wglMakeCurrent(hDC,hRC) == 0) then       ! Try To Activate The Rendering Context
        call KillGLWindow()                         ! Reset The Display
        ignor = MessageBox(C_NULL,"Can't Activate The GL Rendering Context."C,"ERROR"C,ior(MB_OK,MB_ICONEXCLAMATION))
        CreateGLWindow = .FALSE.                    ! Return FALSE
        return
      endif

      ignor = ShowWindow(hWnd,SW_SHOW)              ! Show The Window
      ignor = SetForegroundWindow(hWnd)             ! Slightly Higher Priority
      ignor = SetFocus(hWnd)                        ! Sets Keyboard Focus To The Window
      call ReSizeGLScene(width, height)             ! Set Up Our Perspective GL Screen

	  if (.not.(InitGL())) then                     ! Initialize Our Newly Created GL Window
        call KillGLWindow()                         ! Reset The Display
        ignor = MessageBox(C_NULL,"Initialization Failed."C,"ERROR"C,ior(MB_OK,MB_ICONEXCLAMATION))
        CreateGLWindow = .FALSE.                    ! Return FALSE
        return
      endif

      CreateGLWindow = .TRUE.                     ! Success
	  return
    End function CreateGLWindow

    integer function WinMain( hInstance, hPrevInstance, lpCmdLine, nCmdShow )
    !DEC$ IF DEFINED (_X86_)
    !DEC$ attributes stdcall, alias: '_WinMain@16' :: WinMain
    !DEC$ ELSE
    !DEC$ attributes stdcall, alias: 'WinMain' :: WinMain
    !DEC$ ENDIF

        implicit none
        integer hInstance
        integer hPrevInstance
        integer lpCmdLine
        integer nCmdShow

        logical done
     
        type (t_MSG) msg
        type (t_WNDCLASS) wc
        TYPE (T_DEVMODE) dmScreenSettings

    ! Ask The User Which Screen Mode They Prefer
	if (MessageBox(C_NULL,"是否想以全屏模式显示图形?"C, "是否全屏"C,ior(MB_YESNO,MB_ICONQUESTION))==IDNO) then
		fullscreen= .FALSE.                          ! Windowed Mode
      else
		fullscreen= .TRUE.                           ! Windowed Mode
    endif

    ! Create Our OpenGL Window
    if (.not.CreateGLWindow("Fortran开发OpenGL应用程序框架",640,480,16,fullscreen)) then
		WinMain = 0
        return                                       ! Quit If Window Was Not Created
    endif

        done = .true.
        do while  (done)                                ! Loop That Runs While done=.TRUE.
           if (not(active)) then
              ignor = WaitMessage()                     ! wait for a new message...
           endif
           if (PeekMessage(msg, C_NULL, 0, 0, PM_REMOVE)) then
               if (msg%message==WM_QUIT) then
                    done = .false.
                 else
                    ignor = TranslateMessage(msg)       ! Translate The Message
                    ignor = DispatchMessage(msg)        ! Dispatch The Message
			    endif
             else
             call DrawGLScene()
			 ignor_l = SwapBuffers(hDC)
   		   end if
	    end do

    ! Shutdown
    call KillGLWindow()                             ! Kill The Window
    WinMain = msg.wParam
	return                                          ! Exit The Program
    end function WinMain

integer function WndProc( hwnd, message, wParam, lParam )
!DEC$ attributes stdcall :: WndProc

    implicit none

    integer hwnd
    integer message
    integer wParam
    integer lParam
	type (T_PAINTSTRUCT)    lpPaint

    select case (message)				    ! Tells Windows We Want To Check The Message
        case (WM_ACTIVATE)
		    if (HIWORD(wParam) == 0) then
			   active = .true.
			  else
			   active = .false.
			endif
            WndProc = 0
	        return
        case (WM_CREATE)
            WndProc = 0
	        return
        case (WM_DESTROY)
            WndProc = 0
	        return
        case (WM_CLOSE)
            call PostQuitMessage(0)         ! This Sends A 'Message' Telling The Program To Quit
            WndProc = 0
            return
        case (WM_KEYUP)
			if (key_up(wParam)) then
               call DrawGLScene()
			   ignor_l = SwapBuffers(hDC)
            endif
            WndProc = 0
            return
        case (WM_KEYDOWN)
			if (wParam == VK_ESCAPE) then   ! Tells Windows We Want To Check The Message
			    ignor = SendMessage(hWnd,WM_CLOSE,0,0)
			  else
			    if (key_down(wParam)) then
                   call DrawGLScene()
				   ignor_l = SwapBuffers(hDC)
                endif
			end if
            WndProc = 0
            return
        case (WM_SIZE)
			call ReSizeGLScene(LOWORD(lParam),HIWORD(lParam))
            return
!        case (WM_MOUSEMOVE)
!			call motion (LOWORD_1(lParam),HIWORD_1(lParam))
!            return
!        case (WM_LBUTTONDOWN)
!			Type_Render = GL_LINE_STRIP
!			Rotation = .true.
!			mouse_r = coord( LOWORD_1(lParam), -HIWORD_1(lParam) )
!			call DrawGLScene()
!           call SwapBuffers(hDC)
!           return
!        case (WM_LBUTTONUP)
!			Type_Render = GL_QUAD_STRIP
!			Rotation = .false.
!			call DrawGLScene()
!           call SwapBuffers(hDC)
!            return
        case (WM_PAINT)
			ignor = BeginPaint (hwnd, lpPaint)
			call DrawGLScene()
			ignor = EndPaint (hwnd, lpPaint)
            WndProc = 0
			ignor_l = SwapBuffers(hDC)
			return
        case default
            WndProc = DefWindowProc(hwnd, message, wParam, lParam)
            return
        end select
    return
end function WndProc


! *DJIP***  this function do not exist in Fortan let's done it....
    integer function LOWORD_i(lParam)
      integer lParam
      integer glnWidth

      glnWidth = and(lParam, #0000FFFF)  !  low word

      LOWORD_i=glnWidth

    end function LOWORD_i

    integer function HIWORD_i(lParam)
      integer lParam
      integer glnLength

      glnLength = ishft(lParam, -16)     !  high word

      HIWORD_i=glnLength

    end function HIWORD_i

End Module