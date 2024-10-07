
! Module de variables globale...
Module VarGlob

    Use Opengl_GL
    Use Opengl_GLU

    Private

    Real(GLfloat), Public ::	rtri	! Angle For The Triangle
    Real(GLfloat), Public ::	rquad	! Angle For The Quad

End Module VarGlob



function InitGL()            ! All Setup For OpenGL Goes Here
 
  Use Opengl_GL
  Use Opengl_GLU

  Logical(4) :: InitGL

  call glShadeModel(GL_SMOOTH)                                          ! Enable Smooth Shading
  call glClearColor(0.0_glfloat, 0.0_glfloat, 0.0_glfloat, 0.5_glfloat) ! Black Background
  call glClearDepth(1.0_glclampd)                                       ! Depth Buffer Setup
  call glEnable(GL_DEPTH_TEST)                                          ! Enables Depth Testing
  call glDepthFunc(GL_LEQUAL)                                           ! The Type Of Depth Testing To Do
  call glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST)                ! Really Nice Perspective Calculations

  InitGL=.true.              ! Initialization Went OK

end function initGL


function DrawGLScene()                                 ! Here's Where We Do All The Drawing

  Use VarGlob
  Use Opengl_GL
  Use Opengl_GLU

  Logical(4) :: DrawGLScene

	call glClear(ior(GL_COLOR_BUFFER_BIT,GL_DEPTH_BUFFER_BIT)) ! Clear The Screen And The Depth Buffer
	call glLoadIdentity()									   ! Reset The View

	call glTranslatef(-1.5_glfloat,0.0_glfloat,-6.0_glfloat)

	call glRotatef(rtri,0.0_glfloat,1.0_glfloat,0.0_glfloat)	! Rotate The Triangle On The Y Axis

	call glBegin(GL_POLYGON)									! Start Drawing A Polygon
		call glColor3f(1.0_glfloat,0.0_glfloat,0.0_glfloat)		! Red
		call glVertex3f( 0.0_glfloat, 1.0_glfloat, 0.0_glfloat)	! Top Of Triangle (Front)
		call glColor3f(0.0_glfloat,1.0_glfloat,0.0_glfloat)		! Green
		call glVertex3f(-1.0_glfloat,-1.0_glfloat, 1.0_glfloat)	! Left Of Triangle (Front)
		call glColor3f(0.0_glfloat,0.0_glfloat,1.0_glfloat)		! Blue
		call glVertex3f( 1.0_glfloat,-1.0_glfloat, 1.0_glfloat)	! Right Of Triangle (Front)

		call glColor3f(1.0_glfloat,0.0_glfloat,0.0_glfloat)		! Red
		call glVertex3f( 0.0_glfloat, 1.0_glfloat, 0.0_glfloat)	! Top Of Triangle (Right)
		call glColor3f(0.0_glfloat,0.0_glfloat,1.0_glfloat)		! Blue
		call glVertex3f( 1.0_glfloat,-1.0_glfloat, 1.0_glfloat)	! Left Of Triangle (Right)
		call glColor3f(0.0_glfloat,1.0_glfloat,0.0_glfloat)		! Green
		call glVertex3f( 1.0_glfloat,-1.0_glfloat, -1.0_glfloat)! Right Of Triangle (Right)

		call glColor3f(1.0_glfloat,0.0_glfloat,0.0_glfloat)		! Red
		call glVertex3f( 0.0_glfloat, 1.0_glfloat, 0.0_glfloat)	! Top Of Triangle (Back)
		call glColor3f(0.0_glfloat,1.0_glfloat,0.0_glfloat)		! Green
		call glVertex3f( 1.0_glfloat,-1.0_glfloat, -1.0_glfloat)! Left Of Triangle (Back)
		call glColor3f(0.0_glfloat,0.0_glfloat,1.0_glfloat)		! Blue
		call glVertex3f(-1.0_glfloat,-1.0_glfloat, -1.0_glfloat)! Right Of Triangle (Back)

		call glColor3f(1.0_glfloat,0.0_glfloat,0.0_glfloat)		! Red
		call glVertex3f( 0.0_glfloat, 1.0_glfloat, 0.0_glfloat)	! Top Of Triangle (Left)
		call glColor3f(0.0_glfloat,0.0_glfloat,1.0_glfloat)		! Blue
		call glVertex3f(-1.0_glfloat,-1.0_glfloat,-1.0_glfloat)	! Left Of Triangle (Left)
		call glColor3f(0.0_glfloat,1.0_glfloat,0.0_glfloat)		! Green
		call glVertex3f(-1.0_glfloat,-1.0_glfloat, 1.0_glfloat)	! Right Of Triangle (Left)
	call glEnd()												! Done Drawing The Polygon

	call glLoadIdentity()
	call glTranslatef(1.5_glfloat,0.0_glfloat,-6.0_glfloat)		! Move Right 1.5 Units

	call glRotatef(rquad,1.0_glfloat,0.0_glfloat,0.0_glfloat)	! Rotate The Quad On The X Axis

	call glColor3f(0.5_glfloat,0.5_glfloat,1.0_glfloat)			! Set The Color To A Nice Blue Shade
	call glBegin(GL_QUADS)										! Start Drawing A Quad
		call glColor3f(0.0_glfloat,1.0_glfloat,0.0_glfloat)		! Blue
		call glVertex3f( 1.0_glfloat, 1.0_glfloat,-1.0_glfloat)	! Top Right Of The Quad (Top)
		call glVertex3f(-1.0_glfloat, 1.0_glfloat,-1.0_glfloat)	! Top Left Of The Quad (Top)
		call glVertex3f(-1.0_glfloat, 1.0_glfloat, 1.0_glfloat)	! Bottom Left Of The Quad (Top)
		call glVertex3f( 1.0_glfloat, 1.0_glfloat, 1.0_glfloat)	! Bottom Right Of The Quad (Top)

		call glColor3f(1.0_glfloat,0.5_glfloat,0.0_glfloat)		! Orange
		call glVertex3f( 1.0_glfloat,-1.0_glfloat, 1.0_glfloat)	! Top Right Of The Quad (Bottom)
		call glVertex3f(-1.0_glfloat,-1.0_glfloat, 1.0_glfloat)	! Top Left Of The Quad (Bottom)
		call glVertex3f(-1.0_glfloat,-1.0_glfloat,-1.0_glfloat)	! Bottom Left Of The Quad (Bottom)
		call glVertex3f( 1.0_glfloat,-1.0_glfloat,-1.0_glfloat)	! Bottom Right Of The Quad (Bottom)

		call glColor3f(1.0_glfloat,0.0_glfloat,0.0_glfloat)		! Red
		call glVertex3f( 1.0_glfloat, 1.0_glfloat, 1.0_glfloat)	! Top Right Of The Quad (Front)
		call glVertex3f(-1.0_glfloat, 1.0_glfloat, 1.0_glfloat)	! Top Left Of The Quad (Front)
		call glVertex3f(-1.0_glfloat,-1.0_glfloat, 1.0_glfloat)	! Bottom Left Of The Quad (Front)
		call glVertex3f( 1.0_glfloat,-1.0_glfloat, 1.0_glfloat)	! Bottom Right Of The Quad (Front)

		call glColor3f(1.0_glfloat,1.0_glfloat,0.0_glfloat)		! Yellow
		call glVertex3f( 1.0_glfloat,-1.0_glfloat,-1.0_glfloat)	! Top Right Of The Quad (Back)
		call glVertex3f(-1.0_glfloat,-1.0_glfloat,-1.0_glfloat)	! Top Left Of The Quad (Back)
		call glVertex3f(-1.0_glfloat, 1.0_glfloat,-1.0_glfloat)	! Bottom Left Of The Quad (Back)
		call glVertex3f( 1.0_glfloat, 1.0_glfloat,-1.0_glfloat)	! Bottom Right Of The Quad (Back)

		call glColor3f(0.0_glfloat,0.0_glfloat,1.0_glfloat)		! Blue
		call glVertex3f(-1.0_glfloat, 1.0_glfloat, 1.0_glfloat)	! Top Right Of The Quad (Left)
		call glVertex3f(-1.0_glfloat, 1.0_glfloat,-1.0_glfloat)	! Top Left Of The Quad (Left)
		call glVertex3f(-1.0_glfloat,-1.0_glfloat,-1.0_glfloat)	! Bottom Left Of The Quad (Left)
		call glVertex3f(-1.0_glfloat,-1.0_glfloat, 1.0_glfloat)	! Bottom Right Of The Quad (Left)

		call glColor3f(1.0_glfloat,0.0_glfloat,1.0_glfloat)		! Violet
		call glVertex3f( 1.0_glfloat, 1.0_glfloat,-1.0_glfloat)	! Top Right Of The Quad (Right)
		call glVertex3f( 1.0_glfloat, 1.0_glfloat, 1.0_glfloat)	! Top Left Of The Quad (Right)
		call glVertex3f( 1.0_glfloat,-1.0_glfloat, 1.0_glfloat)	! Bottom Left Of The Quad (Right)
		call glVertex3f( 1.0_glfloat,-1.0_glfloat,-1.0_glfloat)	! Bottom Right Of The Quad (Right)
	call glEnd()												! Done Drawing The Quad

	rtri=rtri+0.2_glfloat						! Increase Rotation Variable For The Triangle
	rquad=rquad-0.15_glfloat					! Decrease Rotation Variable For The Quad

	DrawGLScene = .TRUE.   ! Keep Going

end function DrawGLScene

function Key_up(i)
  Logical(4) :: Key_up
  Integer(4), intent(in) :: i
  
  Key_up = .false.    
end function Key_up

function Key_down(i)
  Logical(4) :: Key_down
  Integer(4), intent(in) :: i

  Key_down = .false.    
end function Key_down


