// TriangleView.cpp : implementation of the CTriangleView class
#include "stdafx.h"
#include "Triangle.h"

#include "MainFrm.h"
#include "TriangleDoc.h"
#include "TriangleView.h"
#include "body.h"
#include "NameDlg.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl/glaux.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//High light Test
GLfloat lightangle[2] = {0.0f, 0.0f};
GLfloat color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat zero[4] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat one[4] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat mat_specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat low_shininess[ ] = {5.0}; 

GLfloat lightpos[4] = {0.0f, 0.0f, -1.0f, 0.0f};
GLboolean lightchanged[2] = {GL_TRUE, GL_TRUE};
enum{UPDATE_OGL, UPDATE_TEX};

// Forward declarations
void GLResize(GLsizei w, GLsizei h);
void GLRenderScene(void *pData);
void GLSetupRC(void *pData);

/////////////////////////////////////////////////////////////////////////////
// CTriangleView

IMPLEMENT_DYNCREATE(CTriangleView, CView)

BEGIN_MESSAGE_MAP(CTriangleView, CView)
	//{{AFX_MSG_MAP(CTriangleView)
	ON_WM_SIZE()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_TRACKBALLMODE, OnTrackballmode)
	ON_UPDATE_COMMAND_UI(ID_TRACKBALLMODE, OnUpdateTrackballmode)
	ON_COMMAND(ID_TRANSLATEMODE, OnTranslatemode)
	ON_UPDATE_COMMAND_UI(ID_TRANSLATEMODE, OnUpdateTranslatemode)
	ON_COMMAND(ID_DRIVEMODE, OnDrivemode)
	ON_UPDATE_COMMAND_UI(ID_DRIVEMODE, OnUpdateDrivemode)
	ON_COMMAND(ID_SELECTBODYMODE, OnSelectbodymode)
	ON_UPDATE_COMMAND_UI(ID_SELECTBODYMODE, OnUpdateSelectbodymode)
	ON_COMMAND(ID_TRANSLATEBODYMODE, OnTranslatebodymode)
	ON_UPDATE_COMMAND_UI(ID_TRANSLATEBODYMODE, OnUpdateTranslatebodymode)
	ON_COMMAND(ID_CONSTRAIN_XMODE, OnConstrainXmode)
	ON_UPDATE_COMMAND_UI(ID_CONSTRAIN_XMODE, OnUpdateConstrainXmode)
	ON_COMMAND(ID_CONSTRAIN_YMODE, OnConstrainYmode)
	ON_UPDATE_COMMAND_UI(ID_CONSTRAIN_YMODE, OnUpdateConstrainYmode)
	ON_COMMAND(ID_CONSTRAIN_ZMODE, OnConstrainZmode)
	ON_UPDATE_COMMAND_UI(ID_CONSTRAIN_ZMODE, OnUpdateConstrainZmode)
	ON_COMMAND(ID_MOTIONFILEOPEN, OnMotionfileopen)
	ON_COMMAND(ID_MOTIONFILESAVE, OnMotionfilesave)
	ON_COMMAND(ID_RESETSYSTEM, OnResetsystem)
	ON_COMMAND(ID_RESETCURRENTFRAME, OnResetcurrentframe)
	ON_COMMAND(ID_RESETCURRENTSELECTBODY, OnResetcurrentselectbody)
	ON_COMMAND(ID_RESETCAMERA, OnResetcamera)
	ON_COMMAND(ID_COPYFRAME, OnCopyframe)
	ON_COMMAND(ID_PASTEDATA, OnPastedata)
	ON_COMMAND(ID_VIEWMODE1, OnViewmode1)
	ON_UPDATE_COMMAND_UI(ID_VIEWMODE1, OnUpdateViewmode1)
	ON_COMMAND(ID_VIEWMODE2, OnViewmode2)
	ON_UPDATE_COMMAND_UI(ID_VIEWMODE2, OnUpdateViewmode2)
	ON_COMMAND(ID_VIEWMODE3, OnViewmode3)
	ON_UPDATE_COMMAND_UI(ID_VIEWMODE3, OnUpdateViewmode3)
	ON_COMMAND(ID_GHOSTMODE, OnGhostmode)
	ON_UPDATE_COMMAND_UI(ID_GHOSTMODE, OnUpdateGhostmode)
	ON_COMMAND(ID_REFRESHSCREEN, OnRefreshscreen)
	ON_COMMAND(ID_BOUNDINGBOXMODE, OnBoundingboxmode)
	ON_UPDATE_COMMAND_UI(ID_BOUNDINGBOXMODE, OnUpdateBoundingboxmode)
	ON_COMMAND(ID_SOLIDMODE, OnSolidmode)
	ON_UPDATE_COMMAND_UI(ID_SOLIDMODE, OnUpdateSolidmode)
	ON_COMMAND(ID_BOUNDINGBOXANDSOLIDMODE, OnBoundingboxandsolidmode)
	ON_UPDATE_COMMAND_UI(ID_BOUNDINGBOXANDSOLIDMODE, OnUpdateBoundingboxandsolidmode)
	ON_COMMAND(ID_SCENEMODEL, OnScenemodel)
	ON_UPDATE_COMMAND_UI(ID_SCENEMODEL, OnUpdateScenemodel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTriangleView construction/destruction

CTriangleView::CTriangleView()
{
	body_id = BODY;

	m_fHeight = 0.0f;
	vecSetValue(m_vTrackBallOffset, 0.0f, 0.0f, 0.0f);
	vecSetValue(m_vTranslateOffset, 0.0f, 0.0f, 0.0f);
	//Manipulate Mode
	m_iManipulateMode = TRACKBALL;
	//View Mode
	m_iViewMode = VIEWMODE_1;
	//Ghost Mode
	m_bGhostMode = FALSE;
	//Scene Mode
	m_bSceneMode = FALSE;
	//Bounding Box Mode
	m_iBoundingBoxMode = SOLID;

	//Constrain Mode
	m_bConstrainX = FALSE;
	m_bConstrainY = FALSE;
	m_bConstrainZ = FALSE;

	//Left Mouse Button
	m_iLeftCurrentX = 0;
	m_iLeftCurrentY = 0;
	m_iLeftOldX = 0;
	m_iLeftOldY = 0;
	m_bLeftCapture = FALSE;

	//Right Mouse Button
	m_iRightCurrentX = 0;
	m_iRightCurrentY = 0;
	m_iRightOldX = 0;
	m_iRightOldY = 0;
	m_bRightCapture = FALSE;

	m_iTotalGroup = 0;

	InitBody();
	InitTempFrame();
	InitCollideDetection();
}

CTriangleView::~CTriangleView()
{
	LPANIMATION current;
	LPANIMATION last;
	LPANIMATION die;

	current = &Anim;
	last = &Anim;
	do
	{
		if(current->m_iID != 0)
		{
			die = current;
			current = current->next;
			DelGroup(die, FALSE);
		}else
		{
			current = current->next;
		}
	}//do-while
	while(current != last);
}

void CTriangleView::InitBody(void)
{
	body[LOWER_BODY].id = LOWER_BODY;
	body[LOWER_BODY].b_draw = TRUE;
	body[LOWER_BODY].b_scale = TRUE;
	body[LOWER_BODY].b_tran = FALSE;
	vecSetValue(body[LOWER_BODY].scale, 0.275f, 0.153f, 0.152f);

	body[LEFT_LEG].id = LEFT_LEG;
	body[LEFT_LEG].b_tran = TRUE;
	body[LEFT_LEG].b_scale = FALSE;
	body[LEFT_LEG].b_draw = FALSE;
	vecSetValue(body[LEFT_LEG].translate, -0.178f, 0.0f, 0.0f);

	body[RIGHT_LEG].id = RIGHT_LEG;
	body[RIGHT_LEG].b_tran = TRUE;
	body[RIGHT_LEG].b_scale = FALSE;
	body[RIGHT_LEG].b_draw = FALSE;
	vecSetValue(body[RIGHT_LEG].translate, 0.178f, 0.0f, 0.0f);

	body[LEFT_UPPER_LEG].id = LEFT_UPPER_LEG;
	body[LEFT_UPPER_LEG].b_tran = TRUE;
	body[LEFT_UPPER_LEG].b_scale = TRUE;
	body[LEFT_UPPER_LEG].b_draw = TRUE;
	vecSetValue(body[LEFT_UPPER_LEG].translate, 0.0f, -0.425f, 0.0f);
	vecSetValue(body[LEFT_UPPER_LEG].scale, 0.141f, 0.425f, 0.141f);

	body[RIGHT_UPPER_LEG].id = RIGHT_UPPER_LEG;
	body[RIGHT_UPPER_LEG].b_tran = TRUE;
	body[RIGHT_UPPER_LEG].b_scale = TRUE;
	body[RIGHT_UPPER_LEG].b_draw = TRUE;
	vecSetValue(body[RIGHT_UPPER_LEG].translate, 0.0f, -0.425f, 0.0f);
	vecSetValue(body[RIGHT_UPPER_LEG].scale, 0.141f, 0.425f, 0.141f);

	body[LEFT_KNEE].id = LEFT_KNEE;
	body[LEFT_KNEE].b_tran = TRUE;
	body[LEFT_KNEE].b_scale = TRUE;
	body[LEFT_KNEE].b_draw = TRUE;
	vecSetValue(body[LEFT_KNEE].translate, 0.0f, -0.425f, 0.0f);
	vecSetValue(body[LEFT_KNEE].scale, 0.05f, 0.05f, 0.05f);

	body[RIGHT_KNEE].id = RIGHT_KNEE;
	body[RIGHT_KNEE].b_tran = TRUE;
	body[RIGHT_KNEE].b_scale = TRUE;
	body[RIGHT_KNEE].b_draw = TRUE;
	vecSetValue(body[RIGHT_KNEE].translate, 0.0f, -0.425f, 0.0f);
	vecSetValue(body[RIGHT_KNEE].scale, 0.05f, 0.05f, 0.05f);

	body[LEFT_LOWER_LEG].id = LEFT_LOWER_LEG;
	body[LEFT_LOWER_LEG].b_tran = TRUE;
	body[LEFT_LOWER_LEG].b_scale = TRUE;
	body[LEFT_LOWER_LEG].b_draw = TRUE;
	vecSetValue(body[LEFT_LOWER_LEG].translate, 0.0f, -0.425f, 0.0f);
	vecSetValue(body[LEFT_LOWER_LEG].scale, 0.141f, 0.425f, 0.141f);

	body[RIGHT_LOWER_LEG].id = RIGHT_LOWER_LEG;
	body[RIGHT_LOWER_LEG].b_tran = TRUE;
	body[RIGHT_LOWER_LEG].b_scale = TRUE;
	body[RIGHT_LOWER_LEG].b_draw = TRUE;
	vecSetValue(body[RIGHT_LOWER_LEG].translate, 0.0f, -0.425f, 0.0f);
	vecSetValue(body[RIGHT_LOWER_LEG].scale, 0.141f, 0.425f, 0.141f);

	body[LEFT_ANKLE].id = LEFT_ANKLE;
	body[LEFT_ANKLE].b_tran = TRUE;
	body[LEFT_ANKLE].b_scale = TRUE;
	body[LEFT_ANKLE].b_draw = TRUE;
	vecSetValue(body[LEFT_ANKLE].translate, 0.0f, -0.425f, 0.0f);
	vecSetValue(body[LEFT_ANKLE].scale, 0.04f, 0.04f, 0.04f);

	body[RIGHT_ANKLE].id = RIGHT_ANKLE;
	body[RIGHT_ANKLE].b_tran = TRUE;
	body[RIGHT_ANKLE].b_scale = TRUE;
	body[RIGHT_ANKLE].b_draw = TRUE;
	vecSetValue(body[RIGHT_ANKLE].translate, 0.0f, -0.425f, 0.0f);
	vecSetValue(body[RIGHT_ANKLE].scale, 0.04f, 0.04f, 0.04f);

	body[LEFT_FOOT].id = LEFT_FOOT;
	body[LEFT_FOOT].b_tran = TRUE;
	body[LEFT_FOOT].b_scale = TRUE;
	body[LEFT_FOOT].b_draw = TRUE;
	vecSetValue(body[LEFT_FOOT].translate, 0.0f, -0.05f, -0.12f);
	vecSetValue(body[LEFT_FOOT].scale, 0.08f, 0.05f, 0.19f);

	body[RIGHT_FOOT].id = RIGHT_FOOT;
	body[RIGHT_FOOT].b_tran = TRUE;
	body[RIGHT_FOOT].b_scale = TRUE;
	body[RIGHT_FOOT].b_draw = TRUE;
	vecSetValue(body[RIGHT_FOOT].translate, 0.0f, -0.05f, -0.12f);
	vecSetValue(body[RIGHT_FOOT].scale, 0.08f, 0.05f, 0.19f);

	body[UPPER_BODY].id = UPPER_BODY;
	body[UPPER_BODY].b_tran = TRUE;
	body[UPPER_BODY].b_scale = TRUE;
	body[UPPER_BODY].b_draw = TRUE;
	vecSetValue(body[UPPER_BODY].translate, 0.0f, 0.62f, 0.0f);
	vecSetValue(body[UPPER_BODY].scale, 0.306f, 0.5f, 0.21f);

	body[SHOULDER].id = SHOULDER;
	body[SHOULDER].b_tran = TRUE;
	body[SHOULDER].b_scale = TRUE;
	body[SHOULDER].b_draw = TRUE;
	vecSetValue(body[SHOULDER].translate, 0.0f, 0.37f, 0.0f);
	vecSetValue(body[SHOULDER].scale, 0.45f, 0.12f, 0.153f);

	body[LEFT_ARM].id = LEFT_ARM;
	body[LEFT_ARM].b_tran = TRUE;
	body[LEFT_ARM].b_scale = FALSE;
	body[LEFT_ARM].b_draw = FALSE;
	vecSetValue(body[LEFT_ARM].translate, -0.45f, 0.0f, 0.0f);

	body[RIGHT_ARM].id = RIGHT_ARM;
	body[RIGHT_ARM].b_tran = TRUE;
	body[RIGHT_ARM].b_scale = FALSE;
	body[RIGHT_ARM].b_draw = FALSE;
	vecSetValue(body[RIGHT_ARM].translate, 0.45f, 0.0f, 0.0f);

	body[LEFT_UPPER_ARM].id = LEFT_UPPER_ARM;
	body[LEFT_UPPER_ARM].b_tran = TRUE;
	body[LEFT_UPPER_ARM].b_scale = TRUE;
	body[LEFT_UPPER_ARM].b_draw = TRUE;
	vecSetValue(body[LEFT_UPPER_ARM].translate, 0.0f, -0.275f, 0.0f);
	vecSetValue(body[LEFT_UPPER_ARM].scale, 0.09f, 0.275f, 0.09f);

	body[RIGHT_UPPER_ARM].id = RIGHT_UPPER_ARM;
	body[RIGHT_UPPER_ARM].b_tran = TRUE;
	body[RIGHT_UPPER_ARM].b_scale = TRUE;
	body[RIGHT_UPPER_ARM].b_draw = TRUE;
	vecSetValue(body[RIGHT_UPPER_ARM].translate, 0.0f, -0.275f, 0.0f);
	vecSetValue(body[RIGHT_UPPER_ARM].scale, 0.09f, 0.275f, 0.09f);

	body[LEFT_ELBOW].id = LEFT_ELBOW;
	body[LEFT_ELBOW].b_tran = TRUE;
	body[LEFT_ELBOW].b_scale = TRUE;
	body[LEFT_ELBOW].b_draw = TRUE;
	vecSetValue(body[LEFT_ELBOW].translate, 0.0f, -0.275f, 0.0f);
	vecSetValue(body[LEFT_ELBOW].scale, 0.05f, 0.05f, 0.05f);

	body[RIGHT_ELBOW].id = RIGHT_ELBOW;
	body[RIGHT_ELBOW].b_tran = TRUE;
	body[RIGHT_ELBOW].b_scale = TRUE;
	body[RIGHT_ELBOW].b_draw = TRUE;
	vecSetValue(body[RIGHT_ELBOW].translate, 0.0f, -0.275f, 0.0f);
	vecSetValue(body[RIGHT_ELBOW].scale, 0.05f, 0.05f, 0.05f);

	body[LEFT_LOWER_ARM].id = LEFT_LOWER_ARM;
	body[LEFT_LOWER_ARM].b_tran = TRUE;
	body[LEFT_LOWER_ARM].b_scale = TRUE;
	body[LEFT_LOWER_ARM].b_draw = TRUE;
	vecSetValue(body[LEFT_LOWER_ARM].translate, 0.0f, -0.25f, 0.0f);
	vecSetValue(body[LEFT_LOWER_ARM].scale, 0.08f, 0.25f, 0.08f);

	body[RIGHT_LOWER_ARM].id = RIGHT_LOWER_ARM;
	body[RIGHT_LOWER_ARM].b_tran = TRUE;
	body[RIGHT_LOWER_ARM].b_scale = TRUE;
	body[RIGHT_LOWER_ARM].b_draw = TRUE;
	vecSetValue(body[RIGHT_LOWER_ARM].translate, 0.0f, -0.25f, 0.0f);
	vecSetValue(body[RIGHT_LOWER_ARM].scale, 0.08f, 0.25f, 0.08f);

	body[LEFT_WRIST].id = LEFT_WRIST;
	body[LEFT_WRIST].b_tran = TRUE;
	body[LEFT_WRIST].b_scale = TRUE;
	body[LEFT_WRIST].b_draw = TRUE;
	vecSetValue(body[LEFT_WRIST].translate, 0.0f, -0.25f, 0.0f);
	vecSetValue(body[LEFT_WRIST].scale, 0.04f, 0.04f, 0.04f);

	body[RIGHT_WRIST].id = RIGHT_WRIST;
	body[RIGHT_WRIST].b_tran = TRUE;
	body[RIGHT_WRIST].b_scale = TRUE;
	body[RIGHT_WRIST].b_draw = TRUE;
	vecSetValue(body[RIGHT_WRIST].translate, 0.0f, -0.25f, 0.0f);
	vecSetValue(body[RIGHT_WRIST].scale, 0.04f, 0.04f, 0.04f);

	body[LEFT_HAND].id = LEFT_HAND;
	body[LEFT_HAND].b_tran = TRUE;
	body[LEFT_HAND].b_scale = TRUE;
	body[LEFT_HAND].b_draw = TRUE;
	vecSetValue(body[LEFT_HAND].translate, 0.0f, -0.155f, 0.0f);
	vecSetValue(body[LEFT_HAND].scale, 0.052f, 0.155f, 0.091f);

	body[RIGHT_HAND].id = RIGHT_HAND;
	body[RIGHT_HAND].b_tran = TRUE;
	body[RIGHT_HAND].b_scale = TRUE;
	body[RIGHT_HAND].b_draw = TRUE;
	vecSetValue(body[RIGHT_HAND].translate, 0.0f, -0.155f, 0.0f);
	vecSetValue(body[RIGHT_HAND].scale, 0.052f, 0.155f, 0.091f);

	body[HEAD].id = HEAD;
	body[HEAD].b_tran = TRUE;
	body[HEAD].b_scale = TRUE;
	body[HEAD].b_draw = TRUE;
	vecSetValue(body[HEAD].translate, 0.0f, 0.4f, 0.0f);
	vecSetValue(body[HEAD].scale, 0.2f, 0.3f, 0.23f);	
}

void CTriangleView::InitAnim(void)
{
	m_iTotalGroup = 1;
	m_iPlayCount = 0;
	m_iPlaySpeed = 0;
	m_bPlay = FALSE;

	m_pCurrentAnim = &Anim;

	Anim.next = Anim.prev = &Anim;
	strcpy(Anim.name, "Default");

	Anim.m_iID = 0;

	Anim.m_iTotalFrame = 1;
	Anim.m_iCurrentFrame = 1;
	Anim.m_fBaseHeight = 0.0f;
	Anim.FrameList.next = Anim.FrameList.prev = &Anim.FrameList;
	Anim.FrameList.m_iFrame = 1;
	Anim.FrameList.m_fHeadX = 0.0f;
	Anim.FrameList.m_fHeadY = 0.0f;
	Anim.FrameList.m_fShoulderX = 0.0f;
	Anim.FrameList.m_fShoulderY = 0.0f;
	Anim.FrameList.m_fLeftUpperArmX = 0.0f;
	Anim.FrameList.m_fLeftUpperArmY = 0.0f;
	Anim.FrameList.m_fLeftLowerArmX = 0.0f;
	Anim.FrameList.m_fLeftLowerArmY = 0.0f;
	Anim.FrameList.m_fLeftHandX = 0.0f;
	Anim.FrameList.m_fLeftHandY = 0.0f;
	Anim.FrameList.m_fRightUpperArmX = 0.0f;
	Anim.FrameList.m_fRightUpperArmY = 0.0f;
	Anim.FrameList.m_fRightLowerArmX = 0.0f;
	Anim.FrameList.m_fRightLowerArmY = 0.0f;
	Anim.FrameList.m_fRightHandX = 0.0f;
	Anim.FrameList.m_fRightHandY = 0.0f;
	Anim.FrameList.m_fUpperBodyX = 0.0f;
	Anim.FrameList.m_fUpperBodyY = 0.0f;
	Anim.FrameList.m_fLowerBodyX = 0.0f;
	Anim.FrameList.m_fLowerBodyY = 0.0f;
	Anim.FrameList.m_fLeftUpperLegX = 0.0f;
	Anim.FrameList.m_fLeftUpperLegY = 0.0f;
	Anim.FrameList.m_fLeftLowerLegX = 0.0f;
	Anim.FrameList.m_fLeftLowerLegY = 0.0f;
	Anim.FrameList.m_fLeftFootX = 0.0f;
	Anim.FrameList.m_fLeftFootY = 0.0f;
	Anim.FrameList.m_fRightUpperLegX = 0.0f;
	Anim.FrameList.m_fRightUpperLegY = 0.0f;
	Anim.FrameList.m_fRightLowerLegX = 0.0f;
	Anim.FrameList.m_fRightLowerLegY = 0.0f;
	Anim.FrameList.m_fRightFootX = 0.0f;
	Anim.FrameList.m_fRightFootY = 0.0f;
	Anim.FrameList.m_fTranslateY = 0.0f;
}

void CTriangleView::SetBoundingBox(vector *pbox, GLfloat x, GLfloat y, GLfloat z)
{
	pbox[0][X] = x;
	pbox[0][Y] = y;
	pbox[0][Z] = z;

	pbox[1][X] = x;
	pbox[1][Y] = -y;
	pbox[1][Z] = z;

	pbox[2][X] = -x;
	pbox[2][Y] = -y;
	pbox[2][Z] = z;

	pbox[3][X] = -x;
	pbox[3][Y] = y;
	pbox[3][Z] = z;

	pbox[4][X] = x;
	pbox[4][Y] = y;
	pbox[4][Z] = -z;

	pbox[5][X] = x;
	pbox[5][Y] = -y;
	pbox[5][Z] = -z;

	pbox[6][X] = -x;
	pbox[6][Y] = -y;
	pbox[6][Z] = -z;

	pbox[7][X] = -x;
	pbox[7][Y] = y;
	pbox[7][Z] = -z;
}

void CTriangleView::InitScene(void)
{
	SetBoundingBox(scene, 3.0f, 0.2f, 3.0f);
}

void CTriangleView::InitBodyBoundingBox(void)
{
	SetBoundingBox(lower_body_box, 0.275f, 0.153f, 0.152f);
	SetBoundingBox(left_upper_leg_box, 0.141f, 0.425f, 0.141f);
	SetBoundingBox(right_upper_leg_box, 0.141f, 0.425f, 0.141f);
	SetBoundingBox(left_lower_leg_box, 0.141f, 0.425f, 0.141f);
	SetBoundingBox(right_lower_leg_box, 0.141f, 0.425f, 0.141f);
	SetBoundingBox(left_foot_box, 0.08f, 0.05f, 0.19f);
	SetBoundingBox(right_foot_box, 0.08f, 0.05f, 0.19f);

	SetBoundingBox(upper_body_box, 0.306f, 0.5f, 0.21f);
	SetBoundingBox(shoulder_box, 0.45f, 0.12f, 0.153f);
	SetBoundingBox(head_box, 0.2f, 0.3f, 0.23f);
	SetBoundingBox(left_upper_arm_box, 0.09f, 0.275f, 0.09f);
	SetBoundingBox(left_lower_arm_box, 0.08f, 0.25f, 0.08f);
	SetBoundingBox(left_hand_box, 0.052f, 0.155f, 0.091f);
	SetBoundingBox(right_upper_arm_box, 0.09f, 0.275f, 0.09f);
	SetBoundingBox(right_lower_arm_box, 0.08f, 0.25f, 0.08f);
	SetBoundingBox(right_hand_box, 0.052f, 0.155f, 0.091f);

	vecSetValue(left_leg_offset, -0.178f, 0.0f, 0.0f);
	vecSetValue(right_leg_offset, 0.178f, 0.0f, 0.0f);

	vecSetValue(left_arm_offset, -0.45f, 0.0f, 0.0f);
	vecSetValue(right_arm_offset, 0.45f, 0.0f, 0.0f);
}

void CTriangleView::InitTempFrame(void)
{
	TempFrame.m_fHeadX = 0.0f;
	TempFrame.m_fHeadY = 0.0f;

	TempFrame.m_fShoulderX = 0.0f;
	TempFrame.m_fShoulderY = 0.0f;

	TempFrame.m_fUpperBodyX = 0.0f;
	TempFrame.m_fUpperBodyY = 0.0f;

	TempFrame.m_fLowerBodyX = 0.0f;
	TempFrame.m_fLowerBodyY = 0.0f;

	TempFrame.m_fLeftUpperArmX = 0.0f;
	TempFrame.m_fLeftUpperArmY = 0.0f;

	TempFrame.m_fLeftLowerArmX = 0.0f;
	TempFrame.m_fLeftLowerArmY = 0.0f;

	TempFrame.m_fLeftHandX = 0.0f;
	TempFrame.m_fLeftHandY = 0.0f;

	TempFrame.m_fRightUpperArmX = 0.0f;
	TempFrame.m_fRightUpperArmY = 0.0f;

	TempFrame.m_fRightLowerArmX = 0.0f;
	TempFrame.m_fRightLowerArmY = 0.0f;

	TempFrame.m_fRightHandX = 0.0f;
	TempFrame.m_fRightHandY = 0.0f;

	TempFrame.m_fLeftUpperLegX = 0.0f;
	TempFrame.m_fLeftUpperLegY = 0.0f;

	TempFrame.m_fLeftLowerLegX = 0.0f;
	TempFrame.m_fLeftLowerLegY = 0.0f;

	TempFrame.m_fLeftFootX = 0.0f;
	TempFrame.m_fLeftFootY = 0.0f;

	TempFrame.m_fRightUpperLegX = 0.0f;
	TempFrame.m_fRightUpperLegY = 0.0f;

	TempFrame.m_fRightLowerLegX = 0.0f;
	TempFrame.m_fRightLowerLegY = 0.0f;

	TempFrame.m_fRightFootX = 0.0f;
	TempFrame.m_fRightFootY = 0.0f;
}

void CTriangleView::InitCollideDetection(void)
{
	m_bLeftFootHit = FALSE;
	m_bRightFootHit = FALSE;
}

void CTriangleView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	InitAnim();
	InitScene();

	CMainFrame *pMainFrame;
	LPANIMATION pAnim = this->GetCurrentAnimation();

	pMainFrame = (CMainFrame*)AfxGetMainWnd();
	
	pMainFrame->SetCurrentView(this);
	pMainFrame->SetRoot();

	CString str;
	str.GetBuffer(20);
	str.Format("%s", pAnim->name);

	pMainFrame->AddGroupString(&str);

	pMainFrame->SetCurrentAnim(&str);

	this->UpdateFrameInfo();
	this->PlaySpeed(UP);

	SetTimer(1, 100, NULL);	
}

void CTriangleView::SetActiveBody(int index)
{
	body_id = index; 
	ManipulateBody(0.0f, 0.0f);
	Invalidate(FALSE);
}

BOOL CTriangleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// Add Window styles required for OpenGL before window is created
	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS | CS_OWNDC);

	return CView::PreCreateWindow(cs);
}

void CTriangleView::OnDraw(CDC* pDC)
{
	// Make the rendering context current
	wglMakeCurrent(m_hDC,m_hRC);

	// Call our external OpenGL code
	GLRenderScene(NULL);
	
	// Swap our scene to the front
	SwapBuffers(m_hDC);

	// Allow other rendering contexts to co-exist
	wglMakeCurrent(m_hDC,NULL);
}

#ifdef _DEBUG
void CTriangleView::AssertValid() const
{
	CView::AssertValid();
}

void CTriangleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTriangleDoc* CTriangleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTriangleDoc)));
	return (CTriangleDoc*)m_pDocument;
}
#endif //_DEBUG

void CTriangleView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTriangleView::OnTimer(UINT nIDEvent) 
{
	LPANIMATION pAnim = this->GetCurrentAnimation();

	if(m_bPlay == TRUE)
	{
		m_iPlayCount++;
		if(m_iPlayCount >= m_iPlaySpeed)
		{
			m_iPlayCount = 0;
			pAnim->m_iCurrentFrame ++;
			if(pAnim->m_iCurrentFrame > pAnim->m_iTotalFrame)
			{
				pAnim->m_iCurrentFrame = 1;
			}

			this->UpdateFrameInfo();
			Invalidate(FALSE);
		}
	}

	CView::OnTimer(nIDEvent);
}

void CTriangleView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bLeftCapture = TRUE;
	m_iLeftCurrentX = point.x;
	m_iLeftCurrentY = point.y;
	m_iLeftOldX = point.x;
	m_iLeftOldY = point.y;
	
	CView::OnLButtonDown(nFlags, point);
}

void CTriangleView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bLeftCapture = FALSE;

	CView::OnLButtonUp(nFlags, point);
}

void CTriangleView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	m_bRightCapture = TRUE;
	m_iRightCurrentX = point.x;
	m_iRightCurrentY = point.y;
	m_iRightOldX = point.x;
	m_iRightOldY = point.y;
	
	CView::OnRButtonDown(nFlags, point);
}

void CTriangleView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	m_bRightCapture = FALSE;
	
	CView::OnRButtonUp(nFlags, point);
}

void CTriangleView::OnMouseMove(UINT nFlags, CPoint point) 
{
	float offsetX;
	float offsetY;
	float offsetZ;

	LPANIMATION pAnim = this->GetCurrentAnimation();
	LPFRAME pFrame = this->GetCurrentFrame(pAnim);

	int WinW, WinH;
	RECT rect;

	this->GetClientRect(&rect);

	WinW = rect.left - rect.right;
	WinH = rect.bottom - rect.top;

	if(WinW < 0)
	{
		WinW = -WinW;
	}

	if(WinH < 0)
	{
		WinH = -WinH;
	}

	if(TRUE == m_bLeftCapture)
	{
		m_iLeftOldX = m_iLeftCurrentX;
		m_iLeftOldY = m_iLeftCurrentY;
		m_iLeftCurrentX = point.x;
		m_iLeftCurrentY = point.y;
		offsetX = (float)(m_iLeftCurrentX - m_iLeftOldX);
		offsetY = (float)(m_iLeftCurrentY - m_iLeftOldY);
		offsetZ = offsetY;

		if(TRUE == m_bConstrainX)
		{
			offsetX = 0.0f;
		}

		if(TRUE == m_bConstrainY)
		{
			offsetY = 0.0f;
		}

		if(TRUE == m_bConstrainZ)
		{
			offsetZ = 0.0f;
		}

		switch(m_iManipulateMode)
		{
		  case TRACKBALL:
			m_vTrackBallOffset[X] += offsetX;
			m_vTrackBallOffset[Y] += offsetY;

			  if(m_vTrackBallOffset[X] >= 360.0f)
			  {
				  m_vTrackBallOffset[X] -= 360.0f;
			  }

			  if(m_vTrackBallOffset[Y] >= 360.0f)
			  {
				  m_vTrackBallOffset[Y] -= 360.0f;
			  }

			  if(m_vTrackBallOffset[X] <= 0.0f)
			  {
				  m_vTrackBallOffset[X] += 360.0f;
			  }

			  if(m_vTrackBallOffset[Y] <= 0.0f)
			  {
				  m_vTrackBallOffset[Y] += 360.0f;
			  }
		  break;

		 case TRANSLATE:
			m_vTranslateOffset[X] += offsetX/50.0f;
			m_vTranslateOffset[Y] += -(offsetY/50.0f);
		 break;

		  case DRIVE:
			m_vTrackBallOffset[Z] += offsetY;
		  break;

		  case SELECTBODY:
			ManipulateBody(offsetX, offsetY);
		  break;

		  case TRANSLATEBODY:
			  this->TranslateBody(offsetY);
		  break;
		}
	}

	if(m_bRightCapture)
	{
		m_iRightOldX = m_iRightCurrentX;
		m_iRightOldY = m_iRightCurrentY;
		m_iRightCurrentX = point.x;
		m_iRightCurrentY = point.y;

		lightangle[X] = (m_iRightCurrentX - WinW/2.0f) * 2.0f * M_PI/WinW;
		lightangle[Y] = (WinH/2.0f - m_iRightCurrentY) * 2.0f * M_PI/WinH;

		lightpos[Y] = sin(lightangle[Y]);
		lightpos[X] = cos(lightangle[Y]) * sin(lightangle[X]);
		lightpos[Z] =  cos(lightangle[Y]) * cos(lightangle[X]);
		lightpos[W] = 0.0f;
		lightchanged[UPDATE_OGL] = GL_TRUE;
		lightchanged[UPDATE_TEX] = GL_TRUE;
	}

	Invalidate(FALSE);
	CView::OnMouseMove(nFlags, point);
}

void CTriangleView::TranslateBody(float Height)
{
	LPANIMATION pAnim = this->GetCurrentAnimation();
	LPFRAME pFrame = this->GetCurrentFrame(pAnim);

	m_fHeight -= (Height/100.0f);

	if(pFrame->m_iFrame == 1)
	{
		pAnim->m_fBaseHeight = m_fHeight;
	}
	pFrame->m_fTranslateY = m_fHeight;
	this->UpdateFrameInfo();
}

void CTriangleView::ManipulateBody(float offsetX, float offsetY)
{
	LPANIMATION pAnim = this->GetCurrentAnimation();
	LPFRAME pFrame = this->GetCurrentFrame(pAnim);

	float tempX;
	float tempY;

	this->GetMotionBody(pFrame, body_id, &tempX, &tempY);

	tempX += offsetX;
	tempY -= offsetY;

	this->SetMotionBody(pFrame, body_id, tempX, tempY);

	this->UpdateFrameInfo();
}

void CTriangleView::OnTrackballmode() 
{
	m_iManipulateMode = TRACKBALL;	
}

void CTriangleView::OnUpdateTrackballmode(CCmdUI* pCmdUI) 
{
	if(m_iManipulateMode == TRACKBALL)
	{
		pCmdUI->SetCheck(TRUE);
	}else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CTriangleView::OnTranslatemode() 
{
	m_iManipulateMode = TRANSLATE;	
}

void CTriangleView::OnUpdateTranslatemode(CCmdUI* pCmdUI) 
{
	if(m_iManipulateMode == TRANSLATE)
	{
		pCmdUI->SetCheck(TRUE);
	}else
	{
		pCmdUI->SetCheck(FALSE);
	}	
}

void CTriangleView::OnDrivemode() 
{
	m_iManipulateMode = DRIVE;	
}

void CTriangleView::OnUpdateDrivemode(CCmdUI* pCmdUI) 
{
	if(m_iManipulateMode == DRIVE)
	{
		pCmdUI->SetCheck(TRUE);
	}else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CTriangleView::OnSelectbodymode() 
{
	m_iManipulateMode = SELECTBODY;		
}

void CTriangleView::OnUpdateSelectbodymode(CCmdUI* pCmdUI) 
{
	if(m_iManipulateMode == SELECTBODY)
	{
		pCmdUI->SetCheck(TRUE);
	}else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CTriangleView::OnTranslatebodymode() 
{
	m_iManipulateMode = TRANSLATEBODY;		
}

void CTriangleView::OnUpdateTranslatebodymode(CCmdUI* pCmdUI) 
{
	if(m_iManipulateMode == TRANSLATEBODY)
	{
		pCmdUI->SetCheck(TRUE);
	}else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CTriangleView::OnConstrainXmode() 
{
	if(TRUE == m_bConstrainX)
	{
		m_bConstrainX = FALSE;
	}else
	{
		m_bConstrainX = TRUE;
	}
}

void CTriangleView::OnUpdateConstrainXmode(CCmdUI* pCmdUI) 
{
	if(m_iManipulateMode == TRACKBALL ||
		m_iManipulateMode == TRANSLATE ||
		m_iManipulateMode == SELECTBODY)
	{
		pCmdUI->Enable(TRUE);
		if(TRUE == m_bConstrainX)
		{
			pCmdUI->SetCheck(TRUE);
		}else
		{
			pCmdUI->SetCheck(FALSE);
		}
	}else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CTriangleView::OnConstrainYmode() 
{
	if(TRUE == m_bConstrainY)
	{
		m_bConstrainY = FALSE;
	}else
	{
		m_bConstrainY = TRUE;
	}	
}

void CTriangleView::OnUpdateConstrainYmode(CCmdUI* pCmdUI) 
{
	if(m_iManipulateMode == TRACKBALL ||
		m_iManipulateMode == TRANSLATE ||
		m_iManipulateMode == SELECTBODY ||
		m_iManipulateMode == TRANSLATEBODY)
	{
		pCmdUI->Enable(TRUE);
		if(TRUE == m_bConstrainY)
		{
			pCmdUI->SetCheck(TRUE);
		}else
		{
			pCmdUI->SetCheck(FALSE);
		}
	}else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CTriangleView::OnConstrainZmode() 
{
	if(TRUE == m_bConstrainZ)
	{
		m_bConstrainZ = FALSE;
	}else
	{
		m_bConstrainZ = TRUE;
	}		
}

void CTriangleView::OnUpdateConstrainZmode(CCmdUI* pCmdUI) 
{
	if(m_iManipulateMode == DRIVE)
	{
		pCmdUI->Enable(TRUE);
		if(TRUE == m_bConstrainZ)
		{
			pCmdUI->SetCheck(TRUE);
		}else
		{
			pCmdUI->SetCheck(FALSE);
		}
	}else
	{
		pCmdUI->Enable(FALSE);
	}
}

//Frame Management
void CTriangleView::FramePlay(void)
{
	m_bPlay = TRUE;
}

void CTriangleView::FrameStop(void)
{
	m_bPlay = FALSE;
}

void CTriangleView::FrameAddGroup(void)
{
	NameDlg dlg;
	CString sName;
	
	if(dlg.DoModal() == IDOK)
	{
		sName = dlg.m_sName;
	
		this->AddGroup(&sName);
		this->UpdateFrameInfo();
		this->UpdateGroupInfo();

		LPANIMATION pAnim = this->GetCurrentAnimation();
		CMainFrame *pMainFrame;
		pMainFrame = (CMainFrame*)AfxGetMainWnd();
	
		CString str;
		str.GetBuffer(20);
		str.Format("%s", pAnim->name);

		pMainFrame->AddGroupString(&str);
		pMainFrame->SetCurrentAnim(&str);
	}
	Invalidate(FALSE);
}

void CTriangleView::FrameDelGroup(void)
{
	LPANIMATION pAnim = this->GetCurrentAnimation();

	CMainFrame *pMainFrame;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();
	
	CString str;

	if(pAnim->m_iID == 0)
	{
		AfxMessageBox("You can't delete the default group");
	}else
	{
		m_iTotalGroup--;
		if(m_iTotalGroup < 0)
		{
			AfxMessageBox("Frame Management Error Occur");
			return;
		}else
		{
			this->DelGroup(pAnim);
			str.GetBuffer(20);
			str.Format("%s", pAnim->name);

			m_pCurrentAnim = &Anim;
			str.Empty();
			str.GetBuffer(20);
			str.Format("%s", m_pCurrentAnim->name);
			pMainFrame->SetCurrentAnim(&str);
		}
	}
	this->UpdateFrameInfo();
	Invalidate(FALSE);
}

void CTriangleView::FrameAddFrame(void)
{
	LPANIMATION pAnim = this->GetCurrentAnimation();
	this->AddFrame(pAnim);
	this->UpdateFrameInfo();
	Invalidate(FALSE);
}

void CTriangleView::FrameDelFrame(void)
{
	LPANIMATION pAnim = this->GetCurrentAnimation();
	LPFRAME pLast = pAnim->FrameList.prev;

	pAnim->m_iTotalFrame --;
	if(pAnim->m_iTotalFrame <= 0)
	{
		pAnim->m_iTotalFrame = 1;
		pAnim->m_iCurrentFrame = pAnim->m_iTotalFrame;
		AfxMessageBox("At least one frame");
	}else
	{
		pAnim->m_iCurrentFrame = pAnim->m_iTotalFrame;
		this->DelFrame(pLast);
	}

	this->UpdateFrameInfo();
	Invalidate(FALSE);
}

void CTriangleView::FrameNext(void)
{
	LPANIMATION pAnim = this->GetCurrentAnimation();
	pAnim->m_iCurrentFrame ++;
	if(pAnim->m_iCurrentFrame >= pAnim->m_iTotalFrame)
	{
		pAnim->m_iCurrentFrame = pAnim->m_iTotalFrame;
	}

	this->UpdateFrameInfo();
	Invalidate(FALSE);
}

void CTriangleView::FramePrev(void)
{
	LPANIMATION pAnim = this->GetCurrentAnimation();
	pAnim->m_iCurrentFrame --;
	if(pAnim->m_iCurrentFrame <= 1)
	{
		pAnim->m_iCurrentFrame = 1;
	}
	this->UpdateFrameInfo();
	Invalidate(FALSE);
}

void CTriangleView::FrameFirst(void)
{
	LPANIMATION pAnim = this->GetCurrentAnimation();
	pAnim->m_iCurrentFrame = 1;

	this->UpdateFrameInfo();
	Invalidate(FALSE);
}

void CTriangleView::FrameLast(void)
{
	LPANIMATION pAnim = this->GetCurrentAnimation();
	pAnim->m_iCurrentFrame = pAnim->m_iTotalFrame;

	this->UpdateFrameInfo();
	Invalidate(FALSE);
}

void CTriangleView::OnResetsystem() 
{
	this->ResetSystem();

	CMainFrame *pMainFrame;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();

	CString str;
	str.GetBuffer(20);
	str.Format("%s", this->Anim.name);
	
	pMainFrame->AddGroupString(&str);

	this->UpdateFrameInfo();
	Invalidate(FALSE);
}

void CTriangleView::OnResetcurrentframe() 
{
	LPANIMATION pAnim = this->GetCurrentAnimation();
	LPFRAME pFrame = this->GetCurrentFrame(pAnim);
	LPFRAME pPrevFrame;

	if(pFrame->m_iFrame == 1)
	{
		pFrame->m_fHeadX = 0.0f;
		pFrame->m_fHeadY = 0.0f;

		pFrame->m_fShoulderX = 0.0f;
		pFrame->m_fShoulderY = 0.0f;

		pFrame->m_fLeftUpperArmX = 0.0f;
		pFrame->m_fLeftUpperArmY = 0.0f;
		
		pFrame->m_fLeftLowerArmX = 0.0f;
		pFrame->m_fLeftLowerArmY = 0.0f;
		
		pFrame->m_fLeftHandX = 0.0f;
		pFrame->m_fLeftHandY = 0.0f;

		pFrame->m_fRightUpperArmX = 0.0f;
		pFrame->m_fRightUpperArmY = 0.0f;
		
		pFrame->m_fRightLowerArmX = 0.0f;
		pFrame->m_fRightLowerArmY = 0.0f;

		pFrame->m_fRightHandX = 0.0f;
		pFrame->m_fRightHandY = 0.0f;

		pFrame->m_fUpperBodyX = 0.0f;
		pFrame->m_fUpperBodyY = 0.0f;

		pFrame->m_fLowerBodyX = 0.0f;
		pFrame->m_fLowerBodyY = 0.0f;

		pFrame->m_fLeftUpperLegX = 0.0f;
		pFrame->m_fLeftUpperLegY = 0.0f;

		pFrame->m_fLeftLowerLegX = 0.0f;
		pFrame->m_fLeftLowerLegY = 0.0f;

		pFrame->m_fLeftFootX = 0.0f;
		pFrame->m_fLeftFootY = 0.0f;

		pFrame->m_fRightUpperLegX = 0.0f;
		pFrame->m_fRightUpperLegY = 0.0f;

		pFrame->m_fRightLowerLegX = 0.0f;
		pFrame->m_fRightLowerLegY = 0.0f;

		pFrame->m_fRightFootX = 0.0f;
		pFrame->m_fRightFootY = 0.0f;
	}else
	{
		pPrevFrame = pFrame->prev;

		pFrame->m_fHeadX = pPrevFrame->m_fHeadX;
		pFrame->m_fHeadY = pPrevFrame->m_fHeadY;

		pFrame->m_fShoulderX = pPrevFrame->m_fShoulderX;
		pFrame->m_fShoulderY = pPrevFrame->m_fShoulderY;

		pFrame->m_fLeftUpperArmX = pPrevFrame->m_fLeftUpperArmX;
		pFrame->m_fLeftUpperArmY = pPrevFrame->m_fLeftUpperArmY;
		
		pFrame->m_fLeftLowerArmX = pPrevFrame->m_fLeftLowerArmX;
		pFrame->m_fLeftLowerArmY = pPrevFrame->m_fLeftLowerArmY;
		
		pFrame->m_fLeftHandX = pPrevFrame->m_fLeftHandX;
		pFrame->m_fLeftHandY = pPrevFrame->m_fLeftHandY;

		pFrame->m_fRightUpperArmX = pPrevFrame->m_fRightUpperArmX;
		pFrame->m_fRightUpperArmY = pPrevFrame->m_fRightUpperArmY;
		
		pFrame->m_fRightLowerArmX = pPrevFrame->m_fRightLowerArmX;
		pFrame->m_fRightLowerArmY = pPrevFrame->m_fRightLowerArmY;

		pFrame->m_fRightHandX = pPrevFrame->m_fRightHandX;
		pFrame->m_fRightHandY = pPrevFrame->m_fRightHandY;

		pFrame->m_fUpperBodyX = pPrevFrame->m_fUpperBodyX;
		pFrame->m_fUpperBodyY = pPrevFrame->m_fUpperBodyY;

		pFrame->m_fLowerBodyX = pPrevFrame->m_fLowerBodyX;
		pFrame->m_fLowerBodyY = pPrevFrame->m_fLowerBodyY;

		pFrame->m_fLeftUpperLegX = pPrevFrame->m_fLeftUpperLegX;
		pFrame->m_fLeftUpperLegY = pPrevFrame->m_fLeftUpperLegY;

		pFrame->m_fLeftLowerLegX = pPrevFrame->m_fLeftLowerLegX;
		pFrame->m_fLeftLowerLegY = pPrevFrame->m_fLeftLowerLegY;

		pFrame->m_fLeftFootX = pPrevFrame->m_fLeftFootX;
		pFrame->m_fLeftFootY = pPrevFrame->m_fLeftFootY;

		pFrame->m_fRightUpperLegX = pPrevFrame->m_fRightUpperLegX;
		pFrame->m_fRightUpperLegY = pPrevFrame->m_fRightUpperLegY;

		pFrame->m_fRightLowerLegX = pPrevFrame->m_fRightLowerLegX;
		pFrame->m_fRightLowerLegY = pPrevFrame->m_fRightLowerLegY;

		pFrame->m_fRightFootX = pPrevFrame->m_fRightFootX;
		pFrame->m_fRightFootY = pPrevFrame->m_fRightFootY;
	}

	Invalidate(FALSE);
}

void CTriangleView::OnResetcurrentselectbody() 
{
	LPANIMATION pAnim = this->GetCurrentAnimation();
	LPFRAME pFrame = this->GetCurrentFrame(pAnim);
	LPFRAME pPrevFrame;		

	if(pFrame->m_iFrame == 1)
	{
		SetMotionBody(pFrame, body_id, 0.0f, 0.0f);
	}else
	{
		pPrevFrame = pFrame->prev;
		switch(body_id)
		{
		case HEAD:
			pFrame->m_fHeadX = pPrevFrame->m_fHeadX;
			pFrame->m_fHeadY = pPrevFrame->m_fHeadY;
		break;

		case SHOULDER:
			pFrame->m_fShoulderX = pPrevFrame->m_fShoulderX;
			pFrame->m_fShoulderY = pPrevFrame->m_fShoulderY;
		break;

		case UPPER_BODY:
			pFrame->m_fUpperBodyX = pPrevFrame->m_fUpperBodyX;
			pFrame->m_fUpperBodyY = pPrevFrame->m_fUpperBodyY;
		break;

		case LOWER_BODY:
			pFrame->m_fLowerBodyX = pPrevFrame->m_fLowerBodyX;
			pFrame->m_fLowerBodyY = pPrevFrame->m_fLowerBodyY;
		break;

		case LEFT_UPPER_ARM:
			pFrame->m_fLeftUpperArmX = pPrevFrame->m_fLeftUpperArmX;
			pFrame->m_fLeftUpperArmY = pPrevFrame->m_fLeftUpperArmY;
		break;

		case LEFT_LOWER_ARM:
			pFrame->m_fLeftLowerArmX = pPrevFrame->m_fLeftLowerArmX;
			pFrame->m_fLeftLowerArmY = pPrevFrame->m_fLeftLowerArmY;			
		break;

		case LEFT_HAND:
			pFrame->m_fLeftHandX = pPrevFrame->m_fLeftHandX;
			pFrame->m_fLeftHandY = pPrevFrame->m_fLeftHandY;
		break;

		case RIGHT_UPPER_ARM:
			pFrame->m_fRightUpperArmX = pPrevFrame->m_fRightUpperArmX;
			pFrame->m_fRightUpperArmY = pPrevFrame->m_fRightUpperArmY;
		break;

		case RIGHT_LOWER_ARM:
			pFrame->m_fRightLowerArmX = pPrevFrame->m_fRightLowerArmX;
			pFrame->m_fRightLowerArmY = pPrevFrame->m_fRightLowerArmY;
		break;

		case RIGHT_HAND:
			pFrame->m_fRightHandX = pPrevFrame->m_fRightHandX;
			pFrame->m_fRightHandY = pPrevFrame->m_fRightHandY;
		break;

		case LEFT_UPPER_LEG:
			pFrame->m_fLeftUpperLegX = pPrevFrame->m_fLeftUpperLegX;
			pFrame->m_fLeftUpperLegY = pPrevFrame->m_fLeftUpperLegY;
		break;

		case LEFT_LOWER_LEG:
			pFrame->m_fLeftLowerLegX = pPrevFrame->m_fLeftLowerLegX;
			pFrame->m_fLeftLowerLegY = pPrevFrame->m_fLeftLowerLegY;
		break;

		case LEFT_FOOT:
			pFrame->m_fLeftFootX = pPrevFrame->m_fLeftFootX;
			pFrame->m_fLeftFootY = pPrevFrame->m_fLeftFootY;
		break;

		case RIGHT_UPPER_LEG:
			pFrame->m_fRightUpperLegX = pPrevFrame->m_fRightUpperLegX;
			pFrame->m_fRightUpperLegY = pPrevFrame->m_fRightUpperLegY;
		break;

		case RIGHT_LOWER_LEG:
			pFrame->m_fRightLowerLegX = pPrevFrame->m_fRightLowerLegX;
			pFrame->m_fRightLowerLegY = pPrevFrame->m_fRightLowerLegY;
		break;

		case RIGHT_FOOT:
			pFrame->m_fRightFootX = pPrevFrame->m_fRightFootX;
			pFrame->m_fRightFootY = pPrevFrame->m_fRightFootY;	  
		break;

	  default:
	  break;
	}
	}

	Invalidate(FALSE);
}

void CTriangleView::OnResetcamera() 
{
	vecSetValue(m_vTrackBallOffset, 0.0f, 0.0f, 0.0f);
	vecSetValue(m_vTranslateOffset, 0.0f, 0.0f, 0.0f);

	Invalidate(FALSE);
}

void CTriangleView::OnCopyframe() 
{
	LPANIMATION pAnim = this->GetCurrentAnimation();
	LPFRAME pFrame = this->GetCurrentFrame(pAnim);

	TempFrame.m_fHeadX = pFrame->m_fHeadX;
	TempFrame.m_fHeadY = pFrame->m_fHeadY;

	TempFrame.m_fShoulderX = pFrame->m_fShoulderX;
	TempFrame.m_fShoulderY = pFrame->m_fShoulderY;

	TempFrame.m_fUpperBodyX = pFrame->m_fUpperBodyX;
	TempFrame.m_fUpperBodyY = pFrame->m_fUpperBodyY;

	TempFrame.m_fLowerBodyX = pFrame->m_fLowerBodyX;
	TempFrame.m_fLowerBodyY = pFrame->m_fLowerBodyY;

	TempFrame.m_fLeftUpperArmX = pFrame->m_fLeftUpperArmX;
	TempFrame.m_fLeftUpperArmY = pFrame->m_fLeftUpperArmY;

	TempFrame.m_fLeftLowerArmX = pFrame->m_fLeftLowerArmX;
	TempFrame.m_fLeftLowerArmY = pFrame->m_fLeftLowerArmY;

	TempFrame.m_fLeftHandX = pFrame->m_fLeftHandX;
	TempFrame.m_fLeftHandY = pFrame->m_fLeftHandY;

	TempFrame.m_fRightUpperArmX = pFrame->m_fRightUpperArmX;
	TempFrame.m_fRightUpperArmY = pFrame->m_fRightUpperArmY;

	TempFrame.m_fRightLowerArmX = pFrame->m_fRightLowerArmX;
	TempFrame.m_fRightLowerArmY = pFrame->m_fRightLowerArmY;

	TempFrame.m_fRightHandX = pFrame->m_fRightHandX;
	TempFrame.m_fRightHandY = pFrame->m_fRightHandY;

	TempFrame.m_fLeftUpperLegX = pFrame->m_fLeftUpperLegX;
	TempFrame.m_fLeftUpperLegY = pFrame->m_fLeftUpperLegY;

	TempFrame.m_fLeftLowerLegX = pFrame->m_fLeftLowerLegX;
	TempFrame.m_fLeftLowerLegY = pFrame->m_fLeftLowerLegY;

	TempFrame.m_fLeftFootX = pFrame->m_fLeftFootX;
	TempFrame.m_fLeftFootY = pFrame->m_fLeftFootY;

	TempFrame.m_fRightUpperLegX = pFrame->m_fRightUpperLegX;
	TempFrame.m_fRightUpperLegY = pFrame->m_fRightUpperLegY;

	TempFrame.m_fRightLowerLegX = pFrame->m_fRightLowerLegX;
	TempFrame.m_fRightLowerLegY = pFrame->m_fRightLowerLegY;

	TempFrame.m_fRightFootX = pFrame->m_fRightFootX;
	TempFrame.m_fRightFootY = pFrame->m_fRightFootY;
}

void CTriangleView::OnPastedata() 
{
	LPANIMATION pAnim = this->GetCurrentAnimation();
	LPFRAME pFrame = this->GetCurrentFrame(pAnim);

	pFrame->m_fHeadX = TempFrame.m_fHeadX;
	pFrame->m_fHeadY = TempFrame.m_fHeadY;

	pFrame->m_fShoulderX = TempFrame.m_fShoulderX;
	pFrame->m_fShoulderY = TempFrame.m_fShoulderY;

	pFrame->m_fUpperBodyX = TempFrame.m_fUpperBodyX;
	pFrame->m_fUpperBodyY = TempFrame.m_fUpperBodyY;

	pFrame->m_fLowerBodyX = TempFrame.m_fLowerBodyX;
	pFrame->m_fLowerBodyY = TempFrame.m_fLowerBodyY;

	pFrame->m_fLeftUpperArmX = TempFrame.m_fLeftUpperArmX;
	pFrame->m_fLeftUpperArmY = TempFrame.m_fLeftUpperArmY;

	pFrame->m_fLeftLowerArmX = TempFrame.m_fLeftLowerArmX;
	pFrame->m_fLeftLowerArmY = TempFrame.m_fLeftLowerArmY;

	pFrame->m_fLeftHandX = TempFrame.m_fLeftHandX;
	pFrame->m_fLeftHandY = TempFrame.m_fLeftHandY;

	pFrame->m_fRightUpperArmX = TempFrame.m_fRightUpperArmX;
	pFrame->m_fRightUpperArmY = TempFrame.m_fRightUpperArmY;

	pFrame->m_fRightLowerArmX = TempFrame.m_fRightLowerArmX;
	pFrame->m_fRightLowerArmY = TempFrame.m_fRightLowerArmY;

	pFrame->m_fRightHandX = TempFrame.m_fRightHandX;
	pFrame->m_fRightHandY = TempFrame.m_fRightHandY;

	pFrame->m_fLeftUpperLegX = TempFrame.m_fLeftUpperLegX;
	pFrame->m_fLeftUpperLegY = TempFrame.m_fLeftUpperLegY;

	pFrame->m_fLeftLowerLegX = TempFrame.m_fLeftLowerLegX;
	pFrame->m_fLeftLowerLegY = TempFrame.m_fLeftLowerLegY;

	pFrame->m_fLeftFootX = TempFrame.m_fLeftFootX;
	pFrame->m_fLeftFootY = TempFrame.m_fLeftFootY;

	pFrame->m_fRightUpperLegX = TempFrame.m_fRightUpperLegX;
	pFrame->m_fRightUpperLegY = TempFrame.m_fRightUpperLegY;

	pFrame->m_fRightLowerLegX = TempFrame.m_fRightLowerLegX;
	pFrame->m_fRightLowerLegY = TempFrame.m_fRightLowerLegY;

	pFrame->m_fRightFootX = TempFrame.m_fRightFootX;
	pFrame->m_fRightFootY = TempFrame.m_fRightFootY;	

	Invalidate(FALSE);
}

void CTriangleView::OnViewmode1() 
{
	m_iViewMode = VIEWMODE_1;
	Invalidate(FALSE);
}

void CTriangleView::OnUpdateViewmode1(CCmdUI* pCmdUI) 
{
	if(m_iViewMode == VIEWMODE_1)
	{
		pCmdUI->SetCheck(TRUE);
	}else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CTriangleView::OnViewmode2() 
{
	m_iViewMode = VIEWMODE_2;
	Invalidate(FALSE);	
}

void CTriangleView::OnUpdateViewmode2(CCmdUI* pCmdUI) 
{
	if(m_iViewMode == VIEWMODE_2)
	{
		pCmdUI->SetCheck(TRUE);
	}else
	{
		pCmdUI->SetCheck(FALSE);
	}	
}

void CTriangleView::OnViewmode3() 
{
	m_iViewMode = VIEWMODE_3;
	Invalidate(FALSE);	
}

void CTriangleView::OnUpdateViewmode3(CCmdUI* pCmdUI) 
{
	if(m_iViewMode == VIEWMODE_3)
	{
		pCmdUI->SetCheck(TRUE);
	}else
	{
		pCmdUI->SetCheck(FALSE);
	}	
}

void CTriangleView::OnGhostmode() 
{
	if(TRUE == m_bGhostMode)
	{
		m_bGhostMode = FALSE;
	}else
	{
		m_bGhostMode = TRUE;
	}

	Invalidate(FALSE);
}

void CTriangleView::OnUpdateGhostmode(CCmdUI* pCmdUI) 
{
	if(m_bGhostMode == TRUE)
	{
		pCmdUI->SetCheck(TRUE);
	}else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CTriangleView::OnBoundingboxmode() 
{
	m_iBoundingBoxMode = BOUNDINGBOX;
	Invalidate(FALSE);
}

void CTriangleView::OnUpdateBoundingboxmode(CCmdUI* pCmdUI) 
{
	if(m_iBoundingBoxMode == BOUNDINGBOX)
	{
		pCmdUI->SetCheck(TRUE);
	}else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CTriangleView::OnSolidmode() 
{
	m_iBoundingBoxMode = SOLID;
	Invalidate(FALSE);	
}

void CTriangleView::OnUpdateSolidmode(CCmdUI* pCmdUI) 
{
	if(m_iBoundingBoxMode == SOLID)
	{
		pCmdUI->SetCheck(TRUE);
	}else
	{
		pCmdUI->SetCheck(FALSE);
	}	
}

void CTriangleView::OnBoundingboxandsolidmode() 
{
	m_iBoundingBoxMode = BOUNDINGBOXANDSOLID;
	Invalidate(FALSE);	
}

void CTriangleView::OnUpdateBoundingboxandsolidmode(CCmdUI* pCmdUI) 
{
	if(m_iBoundingBoxMode == BOUNDINGBOXANDSOLID)
	{
		pCmdUI->SetCheck(TRUE);
	}else
	{
		pCmdUI->SetCheck(FALSE);
	}	
}

void CTriangleView::OnScenemodel() 
{
	if(TRUE == m_bSceneMode)
	{
		m_bSceneMode = FALSE;
	}else
	{
		m_bSceneMode = TRUE;
	}

	Invalidate(FALSE);
}

void CTriangleView::OnUpdateScenemodel(CCmdUI* pCmdUI) 
{
	if(TRUE == m_bSceneMode)
	{
		pCmdUI->SetCheck(TRUE);
	}else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CTriangleView::OnRefreshscreen() 
{
	Invalidate(FALSE);	
}

void CTriangleView::LinkFrame(LPFRAME pFrame, LPFRAME pLast)
{
	pFrame->next = pLast->next;
	pFrame->prev = pLast;
	pLast->next->prev = pFrame;
	pLast->next = pFrame;
}

void CTriangleView::DelFrame(LPFRAME pLast)
{
	pLast->next->prev = pLast->prev;
	pLast->prev->next = pLast->next;

	LocalFree(pLast);
}

void CTriangleView::DelGroup(LPANIMATION pLastAnim, BOOL bClearString)
{
	pLastAnim->next->prev =  pLastAnim->prev;
	pLastAnim->prev->next = pLastAnim->next;
	
	CMainFrame *pMainFrame;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();

	CString str;
	str.GetBuffer(20);
	str.Format("%s", pLastAnim->name);

	if(bClearString == TRUE)
		pMainFrame->DelGroupString(&str);

	ClearGroupFrame(pLastAnim);

	LocalFree(pLastAnim);
}

void CTriangleView::ClearGroupFrame(LPANIMATION pAnim)
{
	LPFRAME current;
	LPFRAME last;
	LPFRAME die;

	current = &pAnim->FrameList;
	last = &pAnim->FrameList;

	do
	{
		if(current->m_iFrame != 1)
		{
			die = current;
			current = current->next;
			DelFrame(die);
		}else
		{
			current = current->next;
		}
	}
	while(current != last);
}

void CTriangleView::AddGroup(CString *str)
{
	LPANIMATION pAnim;
	LPANIMATION pLastAnim = Anim.prev;

	m_iTotalGroup ++;

	pAnim = (LPANIMATION)LocalAlloc(LPTR, sizeof(ANIMATION));

	if(pAnim == NULL)
	{
		AfxMessageBox("Error of add group into list");
		return;
	}

	pAnim->m_iID = pLastAnim->m_iID + 1;
	
	strcpy(pAnim->name, (char*)(LPCSTR)(LPCTSTR)*str);

	pAnim->FrameList.next = pAnim->FrameList.prev = &pAnim->FrameList;

	pAnim->m_iTotalFrame = 1;
	pAnim->m_iCurrentFrame = 1;

	pAnim->m_fBaseHeight = 0.0f;

	pAnim->FrameList.m_iFrame = 1;

	pAnim->FrameList.m_fHeadX = 0.0f;
	pAnim->FrameList.m_fHeadY = 0.0f;

	pAnim->FrameList.m_fShoulderX = 0.0f;
	pAnim->FrameList.m_fShoulderY = 0.0f;

	pAnim->FrameList.m_fLeftUpperArmX = 0.0f;
	pAnim->FrameList.m_fLeftUpperArmY = 0.0f;

	pAnim->FrameList.m_fLeftLowerArmX = 0.0f;
	pAnim->FrameList.m_fLeftLowerArmY = 0.0f;

	pAnim->FrameList.m_fLeftHandX = 0.0f;
	pAnim->FrameList.m_fLeftHandY = 0.0f;

	pAnim->FrameList.m_fRightUpperArmX = 0.0f;
	pAnim->FrameList.m_fRightUpperArmY = 0.0f;

	pAnim->FrameList.m_fRightLowerArmX = 0.0f;
	pAnim->FrameList.m_fRightLowerArmY = 0.0f;

	pAnim->FrameList.m_fRightHandX = 0.0f;
	pAnim->FrameList.m_fRightHandY = 0.0f;

	pAnim->FrameList.m_fUpperBodyX = 0.0f;
	pAnim->FrameList.m_fUpperBodyY = 0.0f;

	pAnim->FrameList.m_fLowerBodyX = 0.0f;
	pAnim->FrameList.m_fLowerBodyY = 0.0f;

	pAnim->FrameList.m_fLeftUpperLegX = 0.0f;
	pAnim->FrameList.m_fLeftUpperLegY = 0.0f;

	pAnim->FrameList.m_fLeftLowerLegX = 0.0f;
	pAnim->FrameList.m_fLeftLowerLegY = 0.0f;

	pAnim->FrameList.m_fLeftFootX = 0.0f;
	pAnim->FrameList.m_fLeftFootY = 0.0f;

	pAnim->FrameList.m_fRightUpperLegX = 0.0f;
	pAnim->FrameList.m_fRightUpperLegY = 0.0f;

	pAnim->FrameList.m_fRightLowerLegX = 0.0f;
	pAnim->FrameList.m_fRightLowerLegY = 0.0f;

	pAnim->FrameList.m_fRightFootX = 0.0f;
	pAnim->FrameList.m_fRightFootY = 0.0f;

	pAnim->FrameList.m_fTranslateY = 0.0f;	

	m_pCurrentAnim = pAnim;

	this->LinkGroup(pAnim, pLastAnim);
}

void CTriangleView::LinkGroup(LPANIMATION pAnim, LPANIMATION pLastAnim)
{
	pAnim->next = pLastAnim->next;
	pAnim->prev = pLastAnim;
	pLastAnim->next->prev = pAnim;
	pLastAnim->next = pAnim;
}

void CTriangleView::AddFrame(LPANIMATION pAnim)
{
	LPFRAME pFrame;

	pAnim->m_iTotalFrame ++;
	pAnim->m_iCurrentFrame = pAnim->m_iTotalFrame;

	pFrame = (LPFRAME)LocalAlloc(LPTR, sizeof(FRAME));

	if(pFrame == NULL)
	{
		AfxMessageBox("Error of add frame into list");
		return;
	}

	LPFRAME pLast;
	pLast = pAnim->FrameList.prev;

	pFrame->m_iFrame = pLast->m_iFrame + 1;

	pFrame->m_fHeadX = pLast->m_fHeadX;
	pFrame->m_fHeadY = pLast->m_fHeadY;

	pFrame->m_fShoulderX = pLast->m_fShoulderX;
	pFrame->m_fShoulderY = pLast->m_fShoulderY;

	pFrame->m_fLeftUpperArmX = pLast->m_fLeftUpperArmX;
	pFrame->m_fLeftUpperArmY = pLast->m_fLeftUpperArmY;

	pFrame->m_fLeftLowerArmX = pLast->m_fLeftLowerArmX;
	pFrame->m_fLeftLowerArmY= pLast->m_fLeftLowerArmY;

	pFrame->m_fLeftHandX = pLast->m_fLeftHandX;
	pFrame->m_fLeftHandY = pLast->m_fLeftHandY;

	pFrame->m_fRightUpperArmX = pLast->m_fRightUpperArmX;
	pFrame->m_fRightUpperArmY = pLast->m_fRightUpperArmY;

	pFrame->m_fRightLowerArmX = pLast->m_fRightLowerArmX;
	pFrame->m_fRightLowerArmY= pLast->m_fRightLowerArmY;

	pFrame->m_fRightHandX = pLast->m_fRightHandX;
	pFrame->m_fRightHandY = pLast->m_fRightHandY;

	pFrame->m_fUpperBodyX = pLast->m_fUpperBodyX;
	pFrame->m_fUpperBodyY = pLast->m_fUpperBodyY;

	pFrame->m_fLowerBodyX = pLast->m_fLowerBodyX;
	pFrame->m_fLowerBodyY = pLast->m_fLowerBodyY;

	pFrame->m_fLeftUpperLegX = pLast->m_fLeftUpperLegX;
	pFrame->m_fLeftUpperLegY = pLast->m_fLeftUpperLegY;

	pFrame->m_fLeftLowerLegX = pLast->m_fLeftLowerLegX;
	pFrame->m_fLeftLowerLegY = pLast->m_fLeftLowerLegY;

	pFrame->m_fLeftFootX = pLast->m_fLeftFootX;
	pFrame->m_fLeftFootY = pLast->m_fLeftFootY;

	pFrame->m_fRightUpperLegX = pLast->m_fRightUpperLegX;
	pFrame->m_fRightUpperLegY = pLast->m_fRightUpperLegY;

	pFrame->m_fRightLowerLegX = pLast->m_fRightLowerLegX;
	pFrame->m_fRightLowerLegY = pLast->m_fRightLowerLegY;

	pFrame->m_fRightFootX = pLast->m_fRightFootX;
	pFrame->m_fRightFootY = pLast->m_fRightFootY;

	pFrame->m_fTranslateY = pLast->m_fTranslateY;

	LinkFrame(pFrame, pLast);
}

LPFRAME CTriangleView::GetCurrentFrame(LPANIMATION pAnim)
{
	LPFRAME current;
	LPFRAME last;

	current = &pAnim->FrameList;
	last = &pAnim->FrameList;

	do
	{
		if(current->m_iFrame == pAnim->m_iCurrentFrame)
		{
			return current;
		}
		current = current->next;
	}//do-while
	while(current != last);

	return &pAnim->FrameList;
}

LPANIMATION CTriangleView::GetCurrentAnimation(void)
{
	return m_pCurrentAnim;
}

void CTriangleView::PlaySpeed(int updown)
{
	if(updown == UP)
	{
		m_iPlaySpeed--;
		if(m_iPlaySpeed <= 0)
		{
			m_iPlaySpeed = 0;
		}
	}else
	{
		m_iPlaySpeed ++;
		if(m_iPlaySpeed >= 30)
		{
			m_iPlaySpeed = 30;
		}
	}

	CMainFrame *pMainFrame;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();

	pMainFrame->UpdatePlaySpeedInfo(30 - m_iPlaySpeed);
}

void CTriangleView::ChangeCurrentAnimation(int i, CString& str)
{
	LPANIMATION current;
	LPANIMATION last;

	current = &Anim;
	last = &Anim;

//	int index = 0;
	CString name;
	name.GetBuffer(20);
	do
	{
		name.Format("%s", current->name);
		if(str == name)
		{
			m_pCurrentAnim =  current;
			m_pCurrentAnim->m_iCurrentFrame = 1;
			this->UpdateFrameInfo();
			Invalidate(FALSE);
			return;
		}
		current = current->next;
//		index++;
	}//do-while
	while(current != last);

	this->UpdateFrameInfo();
	m_pCurrentAnim = &Anim;
	m_pCurrentAnim->m_iCurrentFrame = 1;
	Invalidate(FALSE);
}

void CTriangleView::UpdateGroupInfo(void)
{
}

void CTriangleView::UpdateFrameInfo(void)
{
	float x, y;
	CMainFrame *pMainFrame;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();

	LPANIMATION pAnim = this->GetCurrentAnimation();
	LPFRAME pFrame = this->GetCurrentFrame(pAnim);
	pMainFrame->UpdateFrame(pAnim->m_iCurrentFrame, pAnim->m_iTotalFrame);

	this->GetMotionBody(pFrame, body_id, &x, &y);

	pMainFrame->UpdateOrientation(body_id, x, y);
	pMainFrame->UpdatePosition(pFrame->m_fTranslateY);
}

void CTriangleView::ChangeGroupName()
{
	LPANIMATION pAnim = GetCurrentAnimation();
	NameDlg dlg;
	CString sName;
	CString temp;
	
	temp.GetBuffer(20);
	sName.GetBuffer(20);

	if(dlg.DoModal() == IDOK)
	{
		sName = dlg.m_sName;
	
	
	CMainFrame *pMainFrame;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();
	
	temp.Format("%s", pAnim->name);

	pMainFrame->DelGroupString(&temp);

	strcpy(pAnim->name, (char*)(LPCSTR)(LPCTSTR)sName);

	pMainFrame->AddGroupString(&sName);
	pMainFrame->SetCurrentAnim(&sName);
	this->ChangeCurrentAnimation(0, sName);
	}
}

void CTriangleView::GetMotionBody(LPFRAME pFrame, int body_id, float *fOffsetX, float *fOffsetY)
{
	switch(body_id)
	{
	  case HEAD:
		  *fOffsetX = pFrame->m_fHeadX;
		  *fOffsetY = pFrame->m_fHeadY;
	  break;

	  case SHOULDER:
		  *fOffsetX = pFrame->m_fShoulderX;
		  *fOffsetY = pFrame->m_fShoulderY;
	  break;

	  case UPPER_BODY:
		  *fOffsetX = pFrame->m_fUpperBodyX;
		  *fOffsetY = pFrame->m_fUpperBodyY;
	  break;

	  case LOWER_BODY:
		  *fOffsetX = pFrame->m_fLowerBodyX;
		  *fOffsetY = pFrame->m_fLowerBodyY;
	  break;

	  case LEFT_UPPER_ARM:
		  *fOffsetX = pFrame->m_fLeftUpperArmX;
		  *fOffsetY = pFrame->m_fLeftUpperArmY;
	  break;

	  case LEFT_LOWER_ARM:
		  *fOffsetX = pFrame->m_fLeftLowerArmX;
		  *fOffsetY = pFrame->m_fLeftLowerArmY;
	  break;

	  case LEFT_HAND:
		  *fOffsetX = pFrame->m_fLeftHandX;
		  *fOffsetY = pFrame->m_fLeftHandY;
	  break;

	  case RIGHT_UPPER_ARM:
		  *fOffsetX = pFrame->m_fRightUpperArmX;
		  *fOffsetY = pFrame->m_fRightUpperArmY;
	  break;

	  case RIGHT_LOWER_ARM:
		  *fOffsetX = pFrame->m_fRightLowerArmX;
		  *fOffsetY = pFrame->m_fRightLowerArmY;
	  break;

	  case RIGHT_HAND:
		  *fOffsetX = pFrame->m_fRightHandX;
		  *fOffsetY = pFrame->m_fRightHandY;
	  break;

	  case LEFT_UPPER_LEG:
		  *fOffsetX = pFrame->m_fLeftUpperLegX;
		  *fOffsetY = pFrame->m_fLeftUpperLegY;
	  break;

	  case LEFT_LOWER_LEG:
		  *fOffsetX = pFrame->m_fLeftLowerLegX;
		  *fOffsetY = pFrame->m_fLeftLowerLegY;
	  break;

	  case LEFT_FOOT:
		  *fOffsetX = pFrame->m_fLeftFootX;
		  *fOffsetY = pFrame->m_fLeftFootY;
	  break;

	  case RIGHT_UPPER_LEG:
		  *fOffsetX = pFrame->m_fRightUpperLegX;
		  *fOffsetY = pFrame->m_fRightUpperLegY;
	  break;

	  case RIGHT_LOWER_LEG:
		  *fOffsetX = pFrame->m_fRightLowerLegX;
		  *fOffsetY = pFrame->m_fRightLowerLegY;
	  break;

	  case RIGHT_FOOT:
		  *fOffsetX = pFrame->m_fRightFootX;
		  *fOffsetY = pFrame->m_fRightFootY;
	  break;

	  default:
		  *fOffsetX = 0;
		  *fOffsetY = 0;
	  break;
	}
}

void CTriangleView::CheckAngle(float *x, float *y)
{
	if(*x > 360.0f)
	{
		*x -= 360.0f;
	} 

	if(*x < 0.0f)
	{
		*x += 360.0f;
	}

	if(*y > 360.0f)
	{
		*y -= 360.0f;
	} 

	if(*y < 0.0f)
	{
		*y+= 360.0f;
	}
}

void CTriangleView::SetMotionBody(LPFRAME pFrame, int body_id, float fOffsetX, float fOffsetY)
{
	switch(body_id)
	{
	  case HEAD:
		  pFrame->m_fHeadX = fOffsetX;
		  pFrame->m_fHeadY = fOffsetY;
		  this->CheckAngle(&pFrame->m_fHeadX, &pFrame->m_fHeadY);
	  break;

	  case SHOULDER:
		  pFrame->m_fShoulderX = fOffsetX;
		  pFrame->m_fShoulderY = fOffsetY;
		  this->CheckAngle(&pFrame->m_fShoulderX, &pFrame->m_fShoulderY);
	  break;

	  case UPPER_BODY:
		  pFrame->m_fUpperBodyX = fOffsetX;
		  pFrame->m_fUpperBodyY = fOffsetY;
		  this->CheckAngle(&pFrame->m_fUpperBodyX, &pFrame->m_fUpperBodyY);
	  break;

	  case LOWER_BODY:
		  pFrame->m_fLowerBodyX = fOffsetX;
		  pFrame->m_fLowerBodyY = fOffsetY;
		  this->CheckAngle(&pFrame->m_fLowerBodyX, &pFrame->m_fLowerBodyY);
	  break;

	  case LEFT_UPPER_ARM:
		  pFrame->m_fLeftUpperArmX = fOffsetX;
		  pFrame->m_fLeftUpperArmY = fOffsetY;
		  this->CheckAngle(&pFrame->m_fLeftUpperArmX, &pFrame->m_fLeftUpperArmY);
	  break;

	  case LEFT_LOWER_ARM:
		  pFrame->m_fLeftLowerArmX = fOffsetX;
		  pFrame->m_fLeftLowerArmY = fOffsetY;
		  this->CheckAngle(&pFrame->m_fLeftLowerArmX, &pFrame->m_fLeftLowerArmY);
	  break;

	  case LEFT_HAND:
		  pFrame->m_fLeftHandX = fOffsetX;
		  pFrame->m_fLeftHandY = fOffsetY;
		  this->CheckAngle(&pFrame->m_fLeftHandX, &pFrame->m_fLeftHandY);
	  break;

	  case RIGHT_UPPER_ARM:
		  pFrame->m_fRightUpperArmX = fOffsetX;
		  pFrame->m_fRightUpperArmY = fOffsetY;
		  this->CheckAngle(&pFrame->m_fRightUpperArmX, &pFrame->m_fRightUpperArmY);
	  break;

	  case RIGHT_LOWER_ARM:
		  pFrame->m_fRightLowerArmX = fOffsetX;
		  pFrame->m_fRightLowerArmY = fOffsetY;
		  this->CheckAngle(&pFrame->m_fRightLowerArmX, &pFrame->m_fRightLowerArmY);
	  break;

	  case RIGHT_HAND:
		  pFrame->m_fRightHandX = fOffsetX;
		  pFrame->m_fRightHandY = fOffsetY;
		  this->CheckAngle(&pFrame->m_fRightHandX, &pFrame->m_fRightHandY);
	  break;

	  case LEFT_UPPER_LEG:
		  pFrame->m_fLeftUpperLegX = fOffsetX;
		  pFrame->m_fLeftUpperLegY = fOffsetY;
		  this->CheckAngle(&pFrame->m_fLeftUpperLegX, &pFrame->m_fLeftUpperLegY);
	  break;

	  case LEFT_LOWER_LEG:
		  pFrame->m_fLeftLowerLegX = fOffsetX;
		  pFrame->m_fLeftLowerLegY = fOffsetY;
		  this->CheckAngle(&pFrame->m_fLeftLowerLegX, &pFrame->m_fLeftLowerLegY);
	  break;

	  case LEFT_FOOT:
		  pFrame->m_fLeftFootX = fOffsetX;
		  pFrame->m_fLeftFootY = fOffsetY;
		  this->CheckAngle(&pFrame->m_fLeftFootX, &pFrame->m_fLeftFootY);
	  break;

	  case RIGHT_UPPER_LEG:
		  pFrame->m_fRightUpperLegX = fOffsetX;
		  pFrame->m_fRightUpperLegY = fOffsetY;
		  this->CheckAngle(&pFrame->m_fRightUpperLegX, &pFrame->m_fRightUpperLegY);
	  break;

	  case RIGHT_LOWER_LEG:
		  pFrame->m_fRightLowerLegX = fOffsetX;
		  pFrame->m_fRightLowerLegY = fOffsetY;
		  this->CheckAngle(&pFrame->m_fRightLowerLegX, &pFrame->m_fRightLowerLegY);
	  break;

	  case RIGHT_FOOT:
		  pFrame->m_fRightFootX = fOffsetX;
		  pFrame->m_fRightFootY = fOffsetY;
		  this->CheckAngle(&pFrame->m_fRightFootX, &pFrame->m_fRightFootY);
	  break;

	  default:
	  break;
	}
}

void CTriangleView::OnMotionfileopen() 
{
    CString strFile;    

    CFileDialog dlg(TRUE,    // Save
                    NULL,    // No default extension
                    NULL,    // No initial file name
                    OFN_OVERWRITEPROMPT
                    | OFN_HIDEREADONLY,
                    "motion files (*.mot)|*.mot|All files (*.*)|*.*||");

    if (dlg.DoModal() == IDOK) 
	{
      strFile = dlg.GetPathName();
	  if(LoadMotion2File((LPSTR)(LPCTSTR)strFile) == FALSE)
	  {
		  ResetSystem();
	  }
	}			
}

BOOL CTriangleView::LoadMotion2File(LPSTR pszFileName)
{
    // Try to open the file for write access.
    CString strFile = pszFileName;    
    CFile file;
     if (! file.Open(strFile,
                    CFile::modeRead | CFile::shareDenyWrite)) 
	 {
        TRACE("Failed to open file");
        return FALSE;
    }

    BOOL bResult = LoadMotion2File(&file);
    file.Close();
    if (!bResult) AfxMessageBox("Failed to load file");
    return bResult;
}

BOOL CTriangleView::LoadMotion2File(CFile* fp)
{
	ResetSystem();

    DWORD dwFileStart = fp->GetPosition();

	int head1;
	int head2;

	CMainFrame *pMainFrame;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CString str;

	fp->Read(&head1, sizeof(int));
	fp->Read(&head2, sizeof(int));

	if(head1 != 3120 || head2 != 2590)
	{
		AfxMessageBox("Error of motion file format");
		return FALSE;
	}

	int iMaxGroup;

	fp->Read(&iMaxGroup, sizeof(int));

	this->m_iTotalGroup = iMaxGroup;

	int i;
	
	fp->Read(&this->Anim, sizeof(ANIMATION));

	Anim.next = Anim.prev = &Anim;

	LoadFrame2File(fp, &this->Anim);

	LPANIMATION pAnim = NULL;
	LPANIMATION pLast = NULL;

//	pAnim = (LPANIMATION)LocalAlloc(LPTR, sizeof(ANIMATION));

	for(i=2; i<=iMaxGroup; i++)
	{
		pAnim = (LPANIMATION)LocalAlloc(LPTR, sizeof(ANIMATION));

		fp->Read(pAnim, sizeof(ANIMATION));

		LoadFrame2File(fp, pAnim);

		if(pAnim == NULL)
		{
			AfxMessageBox("Error of add Group into list\n");
			return FALSE;
		}
//		this->AddGroupFromFile(pAnim);
		pLast = this->Anim.prev;

		LinkGroup(pAnim, pLast);

		str.GetBuffer(20);
		str.Format("%s", pAnim->name);
		pMainFrame->AddGroupString(&str);

		str.Empty();
	}

//	LocalFree(pAnim);

	str.GetBuffer(20);
	str.Format("%s", this->Anim.name);
	pMainFrame->AddGroupString(&str);

	pMainFrame->SetCurrentAnim(&str);

	this->UpdateFrameInfo();

	Invalidate(FALSE);

   return TRUE;
}

BOOL CTriangleView::LoadFrame2File(CFile *fp, LPANIMATION pAnim)
{
	int TotalFrame = pAnim->m_iTotalFrame;
	int iSize;
	int i;

	iSize = sizeof(FRAME);

	fp->Read(&pAnim->FrameList, iSize);

	pAnim->FrameList.next = pAnim->FrameList.prev = &pAnim->FrameList;

	LPFRAME temp;

	temp = (LPFRAME)LocalAlloc(LPTR, iSize);

	if(temp == NULL)
	{
		AfxMessageBox("Error of temp frame 2107");
		return FALSE;
	}

	TRACE("Total Frame is %d\n", TotalFrame);

	for(i=2; i<=TotalFrame; i++)
	{
		fp->Read(temp, sizeof(FRAME));
		this->AddFrameFromFile(temp, pAnim);
	}

	LocalFree(temp);

	return TRUE;
}

void CTriangleView::AddGroupFromFile(LPANIMATION pFileAnim)
{
	LPANIMATION pAnim;

	pAnim = (LPANIMATION)LocalAlloc(LPTR, sizeof(ANIMATION));

	if(pAnim == NULL)
	{
		AfxMessageBox("Error of add Group into list\n");
		return;
	}

	memcpy((void*)pAnim, (void*)pFileAnim, sizeof(ANIMATION));

	LPANIMATION pLast = this->Anim.prev;

	LinkGroup(pAnim, pLast);
}

void CTriangleView::AddFrameFromFile(LPFRAME pFileFrame, LPANIMATION pAnim)
{
	LPFRAME pFrame;

	pFrame = (LPFRAME)LocalAlloc(LPTR, sizeof(FRAME));

	if(pFrame == NULL)
	{
		AfxMessageBox("Error of add frame into list\n");
		return;
	}

	memcpy((void*)pFrame, (void*)pFileFrame, sizeof(FRAME));

	LPFRAME pLast;

	pLast = pAnim->FrameList.prev;

	LinkFrame(pFrame, pLast);
}

void CTriangleView::OnMotionfilesave() 
{
    CString strFile;    

    CFileDialog dlg(FALSE,    // Save
                    NULL,    // No default extension
                    NULL,    // No initial file name
                    OFN_OVERWRITEPROMPT
                    | OFN_HIDEREADONLY,
                    "motion files (*.mot)|*.mot|All files (*.*)|*.*||");
    if (dlg.DoModal() == IDOK) 
	{
      strFile = dlg.GetPathName();
	  SaveMotion2File((LPSTR)(LPCTSTR)strFile);
	}	
}

BOOL CTriangleView::SaveMotion2File(LPSTR pszFileName)
{
    // Try to open the file for write access.
    CString strFile = pszFileName;    
    CFile file;
    if (!file.Open(strFile,
                    CFile::modeReadWrite
                     | CFile::modeCreate
                     | CFile::shareExclusive)) 
	{
        AfxMessageBox("Failed to open file");
        return FALSE;
    }

    BOOL bResult = SaveMotion2File(&file);
    file.Close();
    if (!bResult) AfxMessageBox("Failed to save file");
    return bResult;
}

BOOL CTriangleView::SaveMotion2File(CFile* fp)
{
	CMainFrame *pFrame;
	pFrame = (CMainFrame*)AfxGetMainWnd();

    int iSize = sizeof(int);
	int head = 3120;

    TRY 
	{
        fp->Write(&head, iSize);
    } CATCH(CFileException, e) 
	{
        TRACE("Failed to write file header");
        return FALSE;
    } END_CATCH

	head = 2590;

    TRY 
	{
        fp->Write(&head, iSize);
    } CATCH(CFileException, e) 
	{
        TRACE("Failed to write file header");
        return FALSE;
    } END_CATCH

	int iMaxGroup = this->m_iTotalGroup;
	
    TRY 
	{
        fp->Write(&iMaxGroup, iSize);
    } CATCH(CFileException, e) 
	{
        TRACE("Failed to write file header");
        return FALSE;
    } END_CATCH

	LPANIMATION current;
	LPANIMATION last;
	LPANIMATION save;

	current = &this->Anim;
	last = &this->Anim;

	iSize = sizeof(ANIMATION);

	do
	{
		save = current;
		current = current->next;

		TRY 
		{
			fp->Write(save, iSize);
		} CATCH(CFileException, e) 
		{
	       TRACE("Failed to write file header");
			return FALSE;
		} END_CATCH

		if(FALSE == SaveFrame2File(fp, save))
		{
			AfxMessageBox("Error of Save Frame");
		}

	}//do-while...
	while( current != last);

    return TRUE;
}

BOOL CTriangleView::SaveFrame2File(CFile *fp, LPANIMATION pAnim)
{
	LPFRAME current;
	LPFRAME last;
	LPFRAME save;
	
	current = &pAnim->FrameList;
	last = &pAnim->FrameList;

	int iSize = sizeof(FRAME);

	do
	{
		save = current;
		current = current->next;

		TRY 
		{
			fp->Write(save, iSize);
		} CATCH(CFileException, e) 
		{
	       TRACE("Failed to write file header");
			return FALSE;
		} END_CATCH

	}//do-while...
	while( current != last);

	return TRUE;
}

void CTriangleView::ResetSystem()
{
	LPANIMATION current;
	LPANIMATION last;
	LPANIMATION die;

	current = &Anim;
	last = &Anim;

	do
	{
		if(current->m_iID != 0)
		{
			die = current;
			current = current->next;
			DelGroup(die);
		}else
		{
			current = current->next;
		}
	}//do-while
	while(current != last);
	
	CMainFrame *pMainFrame;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();

	CString str;
	str.GetBuffer(20);
	str.Format("%s", Anim.name);

	pMainFrame->DelGroupString(&str);

	InitAnim();
}

void CTriangleView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	VERIFY(wglMakeCurrent(m_hDC,m_hRC));
	GLResize(cx, cy);
	VERIFY(wglMakeCurrent(NULL,NULL));
}

BOOL CTriangleView::OnQueryNewPalette() 
{
	// If the palette was created.
	if((HPALETTE)m_GLPalette)
		{
		int nRet;

		// Selects the palette into the current device context
		SelectPalette(m_hDC, (HPALETTE)m_GLPalette, FALSE);

		// Map entries from the currently selected palette to
		// the system palette.  The return value is the number 
		// of palette entries modified.
		nRet = RealizePalette(m_hDC);

		// Repaint, forces remap of palette in current window
		InvalidateRect(NULL,FALSE);

		return nRet;
		}

	return CView::OnQueryNewPalette();
}

void CTriangleView::OnPaletteChanged(CWnd* pFocusWnd) 
{
	if(((HPALETTE)m_GLPalette != NULL) && (pFocusWnd != this))
		{
		// Select the palette into the device context
		SelectPalette(m_hDC,(HPALETTE)m_GLPalette,FALSE);

		// Map entries to system palette
		RealizePalette(m_hDC);
				
		// Remap the current colors to the newly realized palette
		UpdateColors(m_hDC);
		return;
		}

	CView::OnPaletteChanged(pFocusWnd);
}

int CTriangleView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	int nPixelFormat;					// Pixel format index
	m_hDC = ::GetDC(m_hWnd);			// Get the Device context

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),	// Size of this structure
		1,								// Version of this structure	
		PFD_DRAW_TO_WINDOW |			// Draw to Window (not to bitmap)
		PFD_SUPPORT_OPENGL |			// Support OpenGL calls in window
		PFD_DOUBLEBUFFER,				// Double buffered mode
		PFD_TYPE_RGBA,					// RGBA Color mode
		24,								// Want 24bit color 
		0,0,0,0,0,0,					// Not used to select mode
		0,0,							// Not used to select mode
		0,0,0,0,0,						// Not used to select mode
		32,								// Size of depth buffer
		0,								// Not used to select mode
		0,								// Not used to select mode
		PFD_MAIN_PLANE,					// Draw in main plane
		0,								// Not used to select mode
		0,0,0 };						// Not used to select mode

	// Choose a pixel format that best matches that described in pfd
	nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);

	// Set the pixel format for the device context
	VERIFY(SetPixelFormat(m_hDC, nPixelFormat, &pfd));

	// Create the rendering context
	m_hRC = wglCreateContext(m_hDC);

	// Make the rendering context current, perform initialization, then
	// deselect it
	VERIFY(wglMakeCurrent(m_hDC,m_hRC));
	GLSetupRC(m_hDC);
	wglMakeCurrent(NULL,NULL);

	// Create the palette if needed
	InitializePalette();

	return 0;
}

void CTriangleView::OnDestroy() 
{
	CView::OnDestroy();

	// Clean up rendering context stuff
	wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd,m_hDC);
}

BOOL CTriangleView::OnEraseBkgnd(CDC* pDC) 
{
	return FALSE;
}


// Initializes the CPalette object
void CTriangleView::InitializePalette(void)
{
	PIXELFORMATDESCRIPTOR pfd;	// Pixel Format Descriptor
	LOGPALETTE *pPal;			// Pointer to memory for logical palette
	int nPixelFormat;			// Pixel format index
	int nColors;				// Number of entries in palette
	int i;						// Counting variable
	BYTE RedRange,GreenRange,BlueRange;
								// Range for each color entry (7,7,and 3)

	// Get the pixel format index and retrieve the pixel format description
	nPixelFormat = GetPixelFormat(m_hDC);
	DescribePixelFormat(m_hDC, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	// Does this pixel format require a palette?  If not, do not create a
	// palette and just return NULL
	if(!(pfd.dwFlags & PFD_NEED_PALETTE))
		return;

	// Number of entries in palette.  8 bits yeilds 256 entries
	nColors = 1 << pfd.cColorBits;	

	// Allocate space for a logical palette structure plus all the palette entries
	pPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) +nColors*sizeof(PALETTEENTRY));

	// Fill in palette header 
	pPal->palVersion = 0x300;		// Windows 3.0
	pPal->palNumEntries = nColors; // table size

	// Build mask of all 1's.  This creates a number represented by having
	// the low order x bits set, where x = pfd.cRedBits, pfd.cGreenBits, and
	// pfd.cBlueBits.  
	RedRange = (1 << pfd.cRedBits) -1;
	GreenRange = (1 << pfd.cGreenBits) - 1;
	BlueRange = (1 << pfd.cBlueBits) -1;

	// Loop through all the palette entries
	for(i = 0; i < nColors; i++)
		{
		// Fill in the 8-bit equivalents for each component
		pPal->palPalEntry[i].peRed = (i >> pfd.cRedShift) & RedRange;
		pPal->palPalEntry[i].peRed = (unsigned char)(
			(double) pPal->palPalEntry[i].peRed * 255.0 / RedRange);

		pPal->palPalEntry[i].peGreen = (i >> pfd.cGreenShift) & GreenRange;
		pPal->palPalEntry[i].peGreen = (unsigned char)(
			(double)pPal->palPalEntry[i].peGreen * 255.0 / GreenRange);

		pPal->palPalEntry[i].peBlue = (i >> pfd.cBlueShift) & BlueRange;
		pPal->palPalEntry[i].peBlue = (unsigned char)(
			(double)pPal->palPalEntry[i].peBlue * 255.0 / BlueRange);

		pPal->palPalEntry[i].peFlags = (unsigned char) NULL;
		}
		
	// Create the palette
	m_GLPalette.CreatePalette(pPal);

	// Go ahead and select and realize the palette for this device context
	SelectPalette(m_hDC,(HPALETTE)m_GLPalette,FALSE);
	RealizePalette(m_hDC);

	// Free the memory used for the logical palette structure
	free(pPal);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
// Called by Windows when it receives the WM_SIZE message.
// Put any code needed here to recalc the viewing volume and
// viewport info
void CTriangleView::GLResize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 100.0f;

	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    gluPerspective(30.0, (GLfloat)w/(GLfloat)h, 1.0, 0200.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CTriangleView::DrawBox(vector *pbox)
{
	glPushMatrix();
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);
		glBegin(GL_LINES);
			glVertex3fv(pbox[0]);
			glVertex3fv(pbox[1]);

			glVertex3fv(pbox[1]);
			glVertex3fv(pbox[2]);

			glVertex3fv(pbox[2]);
			glVertex3fv(pbox[3]);

			glVertex3fv(pbox[3]);
			glVertex3fv(pbox[0]);

			glVertex3fv(pbox[4]);
			glVertex3fv(pbox[5]);

			glVertex3fv(pbox[5]);
			glVertex3fv(pbox[6]);

			glVertex3fv(pbox[6]);
			glVertex3fv(pbox[7]);

			glVertex3fv(pbox[7]);
			glVertex3fv(pbox[4]);

			glVertex3fv(pbox[0]);
			glVertex3fv(pbox[1]);

			glVertex3fv(pbox[1]);
			glVertex3fv(pbox[5]);

			glVertex3fv(pbox[5]);
			glVertex3fv(pbox[4]);

			glVertex3fv(pbox[4]);
			glVertex3fv(pbox[0]);

			glVertex3fv(pbox[3]);
			glVertex3fv(pbox[2]);

			glVertex3fv(pbox[2]);
			glVertex3fv(pbox[6]);

			glVertex3fv(pbox[6]);
			glVertex3fv(pbox[7]);

			glVertex3fv(pbox[7]);
			glVertex3fv(pbox[3]);

			glVertex3fv(pbox[0]);
			glVertex3fv(pbox[4]);

			glVertex3fv(pbox[4]);
			glVertex3fv(pbox[7]);

			glVertex3fv(pbox[7]);
			glVertex3fv(pbox[3]);

			glVertex3fv(pbox[3]);
			glVertex3fv(pbox[0]);
			  
			glVertex3fv(pbox[1]);
			glVertex3fv(pbox[5]);

			glVertex3fv(pbox[5]);
			glVertex3fv(pbox[6]);

			glVertex3fv(pbox[6]);
			glVertex3fv(pbox[2]);

			glVertex3fv(pbox[2]);
			glVertex3fv(pbox[1]);

		glEnd();
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

void CTriangleView::DrawSolidBox(vector *pbox)
{
	glPushMatrix();
		glDisable(GL_CULL_FACE);
		glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (0.0f, 0.0f);
			glVertex3fv(pbox[0]);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (0.0f, 0.2f);
			glVertex3fv(pbox[1]);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (0.2f, 0.2f);
			glVertex3fv(pbox[2]);
			glTexCoord2f (0.2f, 0.0f);
			glVertex3fv(pbox[3]);

			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (0.0f, 0.0f);
			glVertex3fv(pbox[4]);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (0.2f, 0.0f);
			glVertex3fv(pbox[5]);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (0.2f, 0.2f);
			glVertex3fv(pbox[6]);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (0.0f, 0.2f);
			glVertex3fv(pbox[7]);

			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (0.0f, 0.0f);
			glVertex3fv(pbox[0]);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (1.0f, 0.0f);
			glVertex3fv(pbox[3]);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (1.0f, 1.0f);
			glVertex3fv(pbox[7]);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (0.0f, 1.0f);
			glVertex3fv(pbox[4]);

			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (0.0f, 0.0f);
			glVertex3fv(pbox[1]);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (1.0f, 0.0f);
			glVertex3fv(pbox[2]);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (1.0f, 1.0f);
			glVertex3fv(pbox[6]);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (0.0f, 1.0f);
			glVertex3fv(pbox[5]);

			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (0.0f, 0.0f);
			glVertex3fv(pbox[0]);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (0.2f, 0.0f);
			glVertex3fv(pbox[1]);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (0.2f, 0.2f);
			glVertex3fv(pbox[5]);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (0.0f, 0.2f);
			glVertex3fv(pbox[4]);

			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (0.0f, 0.0f);
			glVertex3fv(pbox[3]);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (0.2f, 0.0f);
			glVertex3fv(pbox[2]);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (0.2f, 0.2f);
			glVertex3fv(pbox[6]);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f (0.0f, 0.2f);
			glVertex3fv(pbox[7]);

		glEnd();
		glEnable(GL_CULL_FACE);
	glPopMatrix();
}

void CTriangleView::DrawBodyBoundingBox(void)
{
	int i;

	float ltempx, ltempy, ltempz;
	float rtempx, rtempy, rtempz;

	LPANIMATION pAnim = this->GetCurrentAnimation();
	LPFRAME pFrame = this->GetCurrentFrame(pAnim);

	glColor3f(1.0f, 1.0f, 1.0f);

	InitBodyBoundingBox();

	//Upper Body
	for(i=0; i<8; i++)
	{
		vecTranslate(upper_body_box[i], 0.0f, 0.62f, 0.0f);//0.153f+0.5f
		vecRotateX(upper_body_box[i], upper_body_box[i], -pFrame->m_fUpperBodyY);
		vecRotateY(upper_body_box[i], upper_body_box[i], -pFrame->m_fUpperBodyX);
	}

	for(i=0; i<8; i++)
	{
		vecTranslate(shoulder_box[i], 0.0f, 0.37f, 0.0f);
		vecRotateX(shoulder_box[i], shoulder_box[i], -pFrame->m_fShoulderY);
		vecRotateY(shoulder_box[i], shoulder_box[i], -pFrame->m_fShoulderX);
		vecTranslate(shoulder_box[i], 0.0f, 0.62f, 0.0f);
		vecRotateX(shoulder_box[i], shoulder_box[i], -pFrame->m_fUpperBodyY);
		vecRotateY(shoulder_box[i], shoulder_box[i], -pFrame->m_fUpperBodyX);
	}

	for(i=0; i<8; i++)
	{
		vecTranslate(head_box[i], 0.0f, 0.4f, 0.0f);
		vecRotateX(head_box[i], head_box[i], -pFrame->m_fHeadY);
		vecRotateY(head_box[i], head_box[i], -pFrame->m_fHeadX);
		vecTranslate(head_box[i], 0.0f, 0.37f, 0.0f);
		vecRotateX(head_box[i], head_box[i], -pFrame->m_fShoulderY);
		vecRotateY(head_box[i], head_box[i], -pFrame->m_fShoulderX);
		vecTranslate(head_box[i], 0.0f, 0.62f, 0.0f);
		vecRotateX(head_box[i], head_box[i], -pFrame->m_fUpperBodyY);
		vecRotateY(head_box[i], head_box[i], -pFrame->m_fUpperBodyX);
	}

	for(i=0; i<8; i++)
	{
		vecTranslate(upper_body_box[i], 0.0f, pFrame->m_fTranslateY, 0.0f);
		vecTranslate(shoulder_box[i], 0.0f, pFrame->m_fTranslateY, 0.0f);
		vecTranslate(head_box[i], 0.0f, pFrame->m_fTranslateY, 0.0f);
	}

	for(i=0; i<8; i++)
	{
		vecTranslate(left_upper_arm_box[i], 0.0f, -0.275f, 0.0f);
		vecRotateX(left_upper_arm_box[i], left_upper_arm_box[i], -pFrame->m_fLeftUpperArmY);
		vecRotateY(left_upper_arm_box[i], left_upper_arm_box[i], -pFrame->m_fLeftUpperArmX);

		vecTranslate(left_upper_arm_box[i], left_arm_offset[X], left_arm_offset[Y], left_arm_offset[Z]);

		vecTranslate(left_upper_arm_box[i], 0.0f, 0.37f, 0.0f);
		vecRotateX(left_upper_arm_box[i], left_upper_arm_box[i], -pFrame->m_fShoulderY);
		vecRotateY(left_upper_arm_box[i], left_upper_arm_box[i], -pFrame->m_fShoulderX);

		vecTranslate(left_upper_arm_box[i], 0.0f, 0.62f, 0.0f);
		vecRotateX(left_upper_arm_box[i], left_upper_arm_box[i], -pFrame->m_fUpperBodyY);
		vecRotateY(left_upper_arm_box[i], left_upper_arm_box[i], -pFrame->m_fUpperBodyX);

		vecTranslate(left_upper_arm_box[i], 0.0f, pFrame->m_fTranslateY, 0.0f);
	}

	for(i=0; i<8; i++)
	{
		vecTranslate(right_upper_arm_box[i], 0.0f, -0.275f, 0.0f);
		vecRotateX(right_upper_arm_box[i], right_upper_arm_box[i], -pFrame->m_fRightUpperArmY);
		vecRotateY(right_upper_arm_box[i], right_upper_arm_box[i], -pFrame->m_fRightUpperArmX);

		vecTranslate(right_upper_arm_box[i], right_arm_offset[X], right_arm_offset[Y], right_arm_offset[Z]);

		vecTranslate(right_upper_arm_box[i], 0.0f, 0.37f, 0.0f);
		vecRotateX(right_upper_arm_box[i], right_upper_arm_box[i], -pFrame->m_fShoulderY);
		vecRotateY(right_upper_arm_box[i], right_upper_arm_box[i], -pFrame->m_fShoulderX);

		vecTranslate(right_upper_arm_box[i], 0.0f, 0.62f, 0.0f);
		vecRotateX(right_upper_arm_box[i], right_upper_arm_box[i], -pFrame->m_fUpperBodyY);
		vecRotateY(right_upper_arm_box[i], right_upper_arm_box[i], -pFrame->m_fUpperBodyX);

		vecTranslate(right_upper_arm_box[i], 0.0f, pFrame->m_fTranslateY, 0.0f);
	}

	for(i=0; i<8; i++)
	{
		vecTranslate(left_lower_arm_box[i], 0.0f, -0.25f, 0.0f);
		vecRotateX(left_lower_arm_box[i], left_lower_arm_box[i], -pFrame->m_fLeftLowerArmY);
		vecRotateY(left_lower_arm_box[i], left_lower_arm_box[i], -pFrame->m_fLeftLowerArmX);
		vecTranslate(left_lower_arm_box[i], 0.0f, -0.25f, 0.0f);

		vecTranslate(left_lower_arm_box[i], 0.0f, -0.275f, 0.0f);
		vecRotateX(left_lower_arm_box[i], left_lower_arm_box[i], -pFrame->m_fLeftUpperArmY);
		vecRotateY(left_lower_arm_box[i], left_lower_arm_box[i], -pFrame->m_fLeftUpperArmX);

		vecTranslate(left_lower_arm_box[i], left_arm_offset[X], left_arm_offset[Y], left_arm_offset[Z]);

		vecTranslate(left_lower_arm_box[i], 0.0f, 0.37f, 0.0f);
		vecRotateX(left_lower_arm_box[i], left_lower_arm_box[i], -pFrame->m_fShoulderY);
		vecRotateY(left_lower_arm_box[i], left_lower_arm_box[i], -pFrame->m_fShoulderX);

		vecTranslate(left_lower_arm_box[i], 0.0f, 0.62f, 0.0f);
		vecRotateX(left_lower_arm_box[i], left_lower_arm_box[i], -pFrame->m_fUpperBodyY);
		vecRotateY(left_lower_arm_box[i], left_lower_arm_box[i], -pFrame->m_fUpperBodyX);

		vecTranslate(left_lower_arm_box[i], 0.0f, pFrame->m_fTranslateY, 0.0f);
	}

	for(i=0; i<8; i++)
	{
		vecTranslate(right_lower_arm_box[i], 0.0f, -0.25f, 0.0f);
		vecRotateX(right_lower_arm_box[i], right_lower_arm_box[i], -pFrame->m_fRightLowerArmY);
		vecRotateY(right_lower_arm_box[i], right_lower_arm_box[i], -pFrame->m_fRightLowerArmX);
		vecTranslate(right_lower_arm_box[i], 0.0f, -0.25f, 0.0f);

		vecTranslate(right_lower_arm_box[i], 0.0f, -0.275f, 0.0f);
		vecRotateX(right_lower_arm_box[i], right_lower_arm_box[i], -pFrame->m_fRightUpperArmY);
		vecRotateY(right_lower_arm_box[i], right_lower_arm_box[i], -pFrame->m_fRightUpperArmX);

		vecTranslate(right_lower_arm_box[i], right_arm_offset[X], left_arm_offset[Y], right_arm_offset[Z]);

		vecTranslate(right_lower_arm_box[i], 0.0f, 0.37f, 0.0f);
		vecRotateX(right_lower_arm_box[i], right_lower_arm_box[i], -pFrame->m_fShoulderY);
		vecRotateY(right_lower_arm_box[i], right_lower_arm_box[i], -pFrame->m_fShoulderX);

		vecTranslate(right_lower_arm_box[i], 0.0f, 0.62f, 0.0f);
		vecRotateX(right_lower_arm_box[i], right_lower_arm_box[i], -pFrame->m_fUpperBodyY);
		vecRotateY(right_lower_arm_box[i], right_lower_arm_box[i], -pFrame->m_fUpperBodyX);

		vecTranslate(right_lower_arm_box[i], 0.0f, pFrame->m_fTranslateY, 0.0f);
	}

	for(i=0; i<8; i++)
	{
		vecTranslate(left_hand_box[i], 0.0f, -0.155f, 0.0f);
		vecRotateX(left_hand_box[i], left_hand_box[i], -pFrame->m_fLeftHandY);
		vecRotateY(left_hand_box[i], left_hand_box[i], -pFrame->m_fLeftHandX);
		vecTranslate(left_hand_box[i], 0.0f, -(0.155f+0.08f), 0.0f);

		vecTranslate(left_hand_box[i], 0.0f, -0.25f, 0.0f);
		vecRotateX(left_hand_box[i], left_hand_box[i], -pFrame->m_fLeftLowerArmY);
		vecRotateY(left_hand_box[i], left_hand_box[i], -pFrame->m_fLeftLowerArmX);
		vecTranslate(left_hand_box[i], 0.0f, -0.25f, 0.0f);

		vecTranslate(left_hand_box[i], 0.0f, -0.275f, 0.0f);
		vecRotateX(left_hand_box[i], left_hand_box[i], -pFrame->m_fLeftUpperArmY);
		vecRotateY(left_hand_box[i], left_hand_box[i], -pFrame->m_fLeftUpperArmX);

		vecTranslate(left_hand_box[i], left_arm_offset[X], left_arm_offset[Y], left_arm_offset[Z]);

		vecTranslate(left_hand_box[i], 0.0f, 0.37f, 0.0f);
		vecRotateX(left_hand_box[i], left_hand_box[i], -pFrame->m_fShoulderY);
		vecRotateY(left_hand_box[i], left_hand_box[i], -pFrame->m_fShoulderX);

		vecTranslate(left_hand_box[i], 0.0f, 0.62f, 0.0f);
		vecRotateX(left_hand_box[i], left_hand_box[i], -pFrame->m_fUpperBodyY);
		vecRotateY(left_hand_box[i], left_hand_box[i], -pFrame->m_fUpperBodyX);

		vecTranslate(left_hand_box[i], 0.0f, pFrame->m_fTranslateY, 0.0f);
	}

	for(i=0; i<8; i++)
	{
		vecTranslate(right_hand_box[i], 0.0f, -(0.155f), 0.0f);
		vecRotateX(right_hand_box[i], right_hand_box[i], -pFrame->m_fRightHandY);
		vecRotateY(right_hand_box[i], right_hand_box[i], -pFrame->m_fRightHandX);
		vecTranslate(right_hand_box[i], 0.0f, -(0.155f+0.08f), 0.0f);

		vecTranslate(right_hand_box[i], 0.0f, -0.25f, 0.0f);
		vecRotateX(right_hand_box[i], right_hand_box[i], -pFrame->m_fRightLowerArmY);
		vecRotateY(right_hand_box[i], right_hand_box[i], -pFrame->m_fRightLowerArmX);
		vecTranslate(right_hand_box[i], 0.0f, -0.25f, 0.0f);

		vecTranslate(right_hand_box[i], 0.0f, -0.275f, 0.0f);
		vecRotateX(right_hand_box[i], right_hand_box[i], -pFrame->m_fRightUpperArmY);
		vecRotateY(right_hand_box[i], right_hand_box[i], -pFrame->m_fRightUpperArmX);

		vecTranslate(right_hand_box[i], right_arm_offset[X], left_arm_offset[Y], right_arm_offset[Z]);

		vecTranslate(right_hand_box[i], 0.0f, 0.37f, 0.0f);
		vecRotateX(right_hand_box[i], right_hand_box[i], -pFrame->m_fShoulderY);
		vecRotateY(right_hand_box[i], right_hand_box[i], -pFrame->m_fShoulderX);

		vecTranslate(right_hand_box[i], 0.0f, 0.62f, 0.0f);
		vecRotateX(right_hand_box[i], right_hand_box[i], -pFrame->m_fUpperBodyY);
		vecRotateY(right_hand_box[i], right_hand_box[i], -pFrame->m_fUpperBodyX);

		vecTranslate(right_hand_box[i], 0.0f, pFrame->m_fTranslateY, 0.0f);
	}

	DrawBox(upper_body_box);
	DrawBox(shoulder_box);
	DrawBox(head_box);
	DrawBox(left_upper_arm_box);
	DrawBox(right_upper_arm_box);
	DrawBox(left_lower_arm_box);
	DrawBox(right_lower_arm_box);
	DrawBox(left_hand_box);
	DrawBox(right_hand_box);
	//Lower Body

	for(i=0; i<8; i++)
	{
		vecRotateX(lower_body_box[i], lower_body_box[i], -pFrame->m_fLowerBodyY);
		vecRotateY(lower_body_box[i], lower_body_box[i], -pFrame->m_fLowerBodyX);
		vecTranslate(lower_body_box[i], 0.0f, pFrame->m_fTranslateY, 0.0f);
	}

	vecRotateX(left_leg_offset, left_leg_offset, -pFrame->m_fLowerBodyY);
	vecRotateY(left_leg_offset, left_leg_offset, -pFrame->m_fLowerBodyX);

	vecRotateX(right_leg_offset, right_leg_offset, -pFrame->m_fLowerBodyY);
	vecRotateY(right_leg_offset, right_leg_offset, -pFrame->m_fLowerBodyX);

	for(i=0; i<8; i++)
	{
		vecTranslate(left_foot_box[i], 0.0f, -0.05f, -0.12f);
		vecTranslate(right_foot_box[i], 0.0f, -0.05f, -0.12f);

		vecRotateX(left_foot_box[i], left_foot_box[i], -pFrame->m_fLeftFootY);
		vecRotateY(left_foot_box[i], left_foot_box[i], -pFrame->m_fLeftFootX);

		vecRotateX(right_foot_box[i], right_foot_box[i], -pFrame->m_fRightFootY);
		vecRotateY(right_foot_box[i], right_foot_box[i], -pFrame->m_fRightFootX);

		vecTranslate(left_foot_box[i], 0.0f, -(0.425f), 0.0f);
		vecTranslate(right_foot_box[i], 0.0f, -(0.425f), 0.0f);
	}

	for(i=0; i<8; i++)
	{
		vecTranslate(left_lower_leg_box[i], 0.0f, -(0.425f), 0.0f);
		vecTranslate(right_lower_leg_box[i], 0.0f, -(0.425f), 0.0f);

		vecTranslate(left_foot_box[i], 0.0f, -(0.425f), 0.0f);
		vecTranslate(right_foot_box[i], 0.0f, -(0.425f), 0.0f);

		vecRotateX(left_lower_leg_box[i], left_lower_leg_box[i], -pFrame->m_fLeftLowerLegY);
		vecRotateY(left_lower_leg_box[i], left_lower_leg_box[i], -pFrame->m_fLeftLowerLegX);

		vecRotateX(left_foot_box[i], left_foot_box[i], -pFrame->m_fLeftLowerLegY);
		vecRotateY(left_foot_box[i], left_foot_box[i], -pFrame->m_fLeftLowerLegX);

		vecRotateX(right_lower_leg_box[i], right_lower_leg_box[i], -pFrame->m_fRightLowerLegY);
		vecRotateY(right_lower_leg_box[i], right_lower_leg_box[i], -pFrame->m_fRightLowerLegX);

		vecRotateX(right_foot_box[i], right_foot_box[i], -pFrame->m_fRightLowerLegY);
		vecRotateY(right_foot_box[i], right_foot_box[i], -pFrame->m_fRightLowerLegX);

		vecTranslate(left_lower_leg_box[i], 0.0f, -(0.85f), 0.0f);
		vecTranslate(right_lower_leg_box[i], 0.0f, -(0.85f), 0.0f);

		vecTranslate(left_foot_box[i], 0.0f, -(0.85f), 0.0f);
		vecTranslate(right_foot_box[i], 0.0f, -(0.85f), 0.0f);
	}

	for(i=0; i<8; i++)
	{
		vecTranslate(left_upper_leg_box[i], 0.0f, -0.425f, 0.0f);
		vecTranslate(right_upper_leg_box[i], 0.0f, -0.425f, 0.0f);
	}

	for(i=0; i<8; i++)
	{
		vecRotateX(left_upper_leg_box[i], left_upper_leg_box[i], -pFrame->m_fLeftUpperLegY);
		vecRotateY(left_upper_leg_box[i], left_upper_leg_box[i], -pFrame->m_fLeftUpperLegX);

		vecRotateX(right_upper_leg_box[i], right_upper_leg_box[i], -pFrame->m_fRightUpperLegY);
		vecRotateY(right_upper_leg_box[i], right_upper_leg_box[i], -pFrame->m_fRightUpperLegX);

		vecRotateX(left_lower_leg_box[i], left_lower_leg_box[i], -pFrame->m_fLeftUpperLegY);
		vecRotateY(left_lower_leg_box[i], left_lower_leg_box[i], -pFrame->m_fLeftUpperLegX);

		vecRotateX(right_lower_leg_box[i], right_lower_leg_box[i], -pFrame->m_fRightUpperLegY);
		vecRotateY(right_lower_leg_box[i], right_lower_leg_box[i], -pFrame->m_fRightUpperLegX);

		vecRotateX(left_foot_box[i], left_foot_box[i], -pFrame->m_fLeftUpperLegY);
		vecRotateY(left_foot_box[i], left_foot_box[i], -pFrame->m_fLeftUpperLegX);

		vecRotateX(right_foot_box[i], right_foot_box[i], -pFrame->m_fRightUpperLegY);
		vecRotateY(right_foot_box[i], right_foot_box[i], -pFrame->m_fRightUpperLegX);
	}

	for(i=0; i<8; i++)
	{
		vecRotateX(left_upper_leg_box[i], left_upper_leg_box[i], -pFrame->m_fLowerBodyY);
		vecRotateY(left_upper_leg_box[i], left_upper_leg_box[i], -pFrame->m_fLowerBodyX);

		vecRotateX(right_upper_leg_box[i], right_upper_leg_box[i], -pFrame->m_fLowerBodyY);
		vecRotateY(right_upper_leg_box[i], right_upper_leg_box[i], -pFrame->m_fLowerBodyX);

		vecRotateX(left_lower_leg_box[i], left_lower_leg_box[i], -pFrame->m_fLowerBodyY);
		vecRotateY(left_lower_leg_box[i], left_lower_leg_box[i], -pFrame->m_fLowerBodyX);

		vecRotateX(right_lower_leg_box[i], right_lower_leg_box[i], -pFrame->m_fLowerBodyY);
		vecRotateY(right_lower_leg_box[i], right_lower_leg_box[i], -pFrame->m_fLowerBodyX);

		vecRotateX(left_foot_box[i], left_foot_box[i], -pFrame->m_fLowerBodyY);
		vecRotateY(left_foot_box[i], left_foot_box[i], -pFrame->m_fLowerBodyX);

		vecRotateX(right_foot_box[i], right_foot_box[i], -pFrame->m_fLowerBodyY);
		vecRotateY(right_foot_box[i], right_foot_box[i], -pFrame->m_fLowerBodyX);
	}

	ltempx = left_leg_offset[X];
	ltempy = left_leg_offset[Y] + pFrame->m_fTranslateY;
	ltempz = left_leg_offset[Z];

	rtempx = right_leg_offset[X];
	rtempy = right_leg_offset[Y] + pFrame->m_fTranslateY;
	rtempz = right_leg_offset[Z];

	for(i=0; i<8; i++)
	{
		vecTranslate(left_upper_leg_box[i], ltempx, ltempy, ltempz);
		vecTranslate(right_upper_leg_box[i], rtempx, rtempy, rtempz);
		vecTranslate(left_lower_leg_box[i], ltempx, ltempy, ltempz);
		vecTranslate(right_lower_leg_box[i], rtempx, rtempy, rtempz);
		vecTranslate(left_foot_box[i], ltempx, ltempy, ltempz);
		vecTranslate(right_foot_box[i], rtempx, rtempy, rtempz);
	}

	DrawBox(lower_body_box);
	DrawBox(left_upper_leg_box);
	DrawBox(right_upper_leg_box);
	DrawBox(left_lower_leg_box);
	DrawBox(right_lower_leg_box);
	if(m_bLeftFootHit == TRUE)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		DrawBox(left_foot_box);
		glColor3f(1.0f, 1.0f, 1.0f);
	}else
	{
		DrawBox(left_foot_box);
	}
	
	if(m_bRightFootHit == TRUE)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		DrawBox(right_foot_box);
		glColor3f(1.0f, 1.0f, 1.0f);
	}else
	{
		DrawBox(right_foot_box);
	}
}

void CTriangleView::DrawSphere(LPBONE bone)
{
	glColor3f(1.0f, 1.0f, 1.0f);

	if(TRUE == bone->b_tran)
	{
		glTranslatef(bone->translate[X], bone->translate[Y], bone->translate[Z]);
	}

	glPushMatrix();

	if(TRUE == bone->b_scale)
	{
		glScalef(bone->scale[X], bone->scale[Y], bone->scale[Z]);
	}

	if(TRUE == bone->b_draw)
	{
		if(body_id == bone->id)
		{
			auxWireSphere(1.0f);
		}else
		{
			auxSolidSphere(1.0f);
		}
	}
	glPopMatrix();
}

void CTriangleView::DrawLeftArm(LPFRAME pFrame)
{
	DrawSphere(&body[LEFT_ARM]);

	glRotatef(pFrame->m_fLeftUpperArmX, 0.0f, 1.0f, 0.0f);
	glRotatef(pFrame->m_fLeftUpperArmY, 1.0f, 0.0f, 0.0f);

	DrawSphere(&body[LEFT_UPPER_ARM]);

	DrawSphere(&body[LEFT_ELBOW]);

	glRotatef(pFrame->m_fLeftLowerArmX, 0.0f, 1.0f, 0.0f);
	glRotatef(pFrame->m_fLeftLowerArmY, 1.0f, 0.0f, 0.0f);

	DrawSphere(&body[LEFT_LOWER_ARM]);

	DrawSphere(&body[LEFT_WRIST]);

	glRotatef(pFrame->m_fLeftHandX, 0.0f, 1.0f, 0.0f);
	glRotatef(pFrame->m_fLeftHandY, 1.0f, 0.0f, 0.0f);

	DrawSphere(&body[LEFT_HAND]);
}

void CTriangleView::DrawRightArm(LPFRAME pFrame)
{
	DrawSphere(&body[RIGHT_ARM]);

	glRotatef(pFrame->m_fRightUpperArmX, 0.0f, 1.0f, 0.0f);
	glRotatef(pFrame->m_fRightUpperArmY, 1.0f, 0.0f, 0.0f);

	DrawSphere(&body[RIGHT_UPPER_ARM]);

	DrawSphere(&body[RIGHT_ELBOW]);

	glRotatef(pFrame->m_fRightLowerArmX, 0.0f, 1.0f, 0.0f);
	glRotatef(pFrame->m_fRightLowerArmY, 1.0f, 0.0f, 0.0f);

	DrawSphere(&body[RIGHT_LOWER_ARM]);

	DrawSphere(&body[RIGHT_WRIST]);

	glRotatef(pFrame->m_fRightHandX, 0.0f, 1.0f, 0.0f);
	glRotatef(pFrame->m_fRightHandY, 1.0f, 0.0f, 0.0f);

	DrawSphere(&body[RIGHT_HAND]);
}

void CTriangleView::DrawUpperBody(LPFRAME pFrame)
{
	glRotatef(pFrame->m_fUpperBodyX, 0.0f, 1.0f, 0.0f);
	glRotatef(pFrame->m_fUpperBodyY, 1.0f, 0.0f, 0.0f);

	DrawSphere(&body[UPPER_BODY]);

	glRotatef(pFrame->m_fShoulderX, 0.0f, 1.0f, 0.0f);
	glRotatef(pFrame->m_fShoulderY, 1.0f, 0.0f, 0.0f);

	DrawSphere(&body[SHOULDER]);

	glPushMatrix();
	  DrawLeftArm(pFrame);
	glPopMatrix();

	glPushMatrix();
	  DrawRightArm(pFrame);
	glPopMatrix();

	glRotatef(pFrame->m_fHeadX, 0.0f, 1.0f, 0.0f);
	glRotatef(pFrame->m_fHeadY, 1.0f, 0.0f, 0.0f);

	DrawSphere(&body[HEAD]);

	glPushMatrix();
	  glTranslatef(0.0f, -0.04f, -0.22f);
	  DrawNose();
	glPopMatrix();

}

void CTriangleView::DrawLeftLeg(LPFRAME pFrame)
{
	DrawSphere(&body[LEFT_LEG]);
	
	glRotatef(pFrame->m_fLeftUpperLegX, 0.0f, 1.0f, 0.0f);
	glRotatef(pFrame->m_fLeftUpperLegY, 1.0f, 0.0f, 0.0f);

	DrawSphere(&body[LEFT_UPPER_LEG]);

	DrawSphere(&body[LEFT_KNEE]);

	glRotatef(pFrame->m_fLeftLowerLegX, 0.0f, 1.0f, 0.0f);
	glRotatef(pFrame->m_fLeftLowerLegY, 1.0f, 0.0f, 0.0f);

	DrawSphere(&body[LEFT_LOWER_LEG]);

	DrawSphere(&body[LEFT_ANKLE]);

	glRotatef(pFrame->m_fLeftFootX, 0.0f, 1.0f, 0.0f);
	glRotatef(pFrame->m_fLeftFootY, 1.0f, 0.0f, 0.0f);

	DrawSphere(&body[LEFT_FOOT]);
}

void CTriangleView::DrawRightLeg(LPFRAME pFrame)
{
	DrawSphere(&body[RIGHT_LEG]);
	
	glRotatef(pFrame->m_fRightUpperLegX, 0.0f, 1.0f, 0.0f);
	glRotatef(pFrame->m_fRightUpperLegY, 1.0f, 0.0f, 0.0f);

	DrawSphere(&body[RIGHT_UPPER_LEG]);

	DrawSphere(&body[RIGHT_KNEE]);

	glRotatef(pFrame->m_fRightLowerLegX, 0.0f, 1.0f, 0.0f);
	glRotatef(pFrame->m_fRightLowerLegY, 1.0f, 0.0f, 0.0f);

	DrawSphere(&body[RIGHT_LOWER_LEG]);

	DrawSphere(&body[RIGHT_ANKLE]);

	glRotatef(pFrame->m_fRightFootX, 0.0f, 1.0f, 0.0f);
	glRotatef(pFrame->m_fRightFootY, 1.0f, 0.0f, 0.0f);

	DrawSphere(&body[RIGHT_FOOT]);
}

void CTriangleView::DrawTorso(LPFRAME pFrame)
{
	glPushMatrix();

		glRotatef(pFrame->m_fLowerBodyX, 0.0f, 1.0f, 0.0f);
		glRotatef(pFrame->m_fLowerBodyY, 1.0f, 0.0f, 0.0f);
		DrawSphere(&body[LOWER_BODY]);

		glPushMatrix();
			DrawLeftLeg(pFrame);
		glPopMatrix();

		glPushMatrix();
			DrawRightLeg(pFrame);
		glPopMatrix();

	glPopMatrix();

	glPushMatrix();
		glPushMatrix();
			DrawUpperBody(pFrame);
		glPopMatrix();
	glPopMatrix();
}

void CTriangleView::Draw_Big_QuadView()
{
	LPANIMATION pAnim = this->GetCurrentAnimation();
	LPFRAME pFrame = this->GetCurrentFrame(pAnim);
	LPFRAME pPrevFrame;

	if(pFrame->m_iFrame != 1)
	{
		pPrevFrame = pFrame->prev;
	}else
	{
		pPrevFrame = pFrame;
	}

	float quadWidth;
	float quadHeight;
	int WinW, WinH;
	RECT rect;

	this->GetClientRect(&rect);

	WinW = rect.left - rect.right;
	WinH = rect.bottom - rect.top;

	if(WinW < 0)
	{
		WinW = -WinW;
	}

	if(WinH < 0)
	{
		WinH = -WinH;
	}

	quadWidth = (float)WinW / 2.0f;
	quadHeight = (float)WinH / 2.0f;

	glColor3f(0.0f, 0.0f, 0.5f);

    glMatrixMode (GL_PROJECTION);
	glPushMatrix();//1
    glLoadIdentity ();
	  
    gluOrtho2D(-0.01f, quadWidth + 0.01f, 0.0f, quadHeight);

    glMatrixMode (GL_MODELVIEW);
	glPushMatrix();//2
    glLoadIdentity ();
	
	glDisable(GL_LIGHTING);
    glViewport(0.0f, 0.0f, floor(quadWidth), floor(quadHeight));

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex2f(0.0f, quadHeight);
		glVertex2f(quadWidth, quadHeight);
	glEnd();

	glColor3f(0.5f, 0.5f, 0.5f);
    glBegin (GL_QUADS);
    glVertex2f (0.0f, 0.0f);
    glVertex2f (quadWidth, 0.0f);
    glVertex2f (quadWidth, quadHeight);
    glVertex2f (0.0f, quadHeight);
    glEnd ();

    glViewport(floor(WinW - quadWidth), 1.0f, floor(quadWidth), floor(quadHeight));

	glColor3f(0.0f, 0.0f, 0.5f);
	glBegin (GL_QUADS);
	glVertex2f (0.0f, 0.0f);
	glVertex2f (quadWidth, 0.0f);
	glVertex2f (quadWidth, quadHeight);
	glVertex2f (0.0f, quadHeight);
	glEnd ();

	glViewport(0.0f, floor(WinH - quadHeight), floor(quadWidth), floor(quadHeight));

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex2f(quadWidth, 0.0f);
		glVertex2f(quadWidth, quadHeight);
	glEnd();

	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin (GL_QUADS);
	glVertex2f (0.0f, 0.0f);
	glVertex2f (quadWidth, 0.0f);
	glVertex2f (quadWidth, quadHeight);
	glVertex2f (0.0f, quadHeight);
	glEnd ();

	glViewport(floor(WinW - quadWidth), floor(WinH - quadHeight), floor(quadWidth), floor(quadHeight));

	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin (GL_QUADS);
	glVertex2f (0.0f, 0.0f);
	glVertex2f (quadWidth, 0.0f);
	glVertex2f (quadWidth, quadHeight);
	glVertex2f (0.0f, quadHeight);
	glEnd ();

	glEnable(GL_LIGHTING);

    glClear(GL_DEPTH_BUFFER_BIT);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	{
	glPushMatrix();//5

    glViewport(0.0f, 0.0f, floor(quadWidth), floor(quadHeight));

	  glTranslatef(0.0f, 0.0f, -8.0f);
	  glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	  DrawTorso(pFrame);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glPopMatrix();//5
	}

	{
	glPushMatrix();//5

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

    glViewport(floor(WinW - quadWidth), 1.0f, floor(quadWidth), floor(quadHeight));

	glPushMatrix();
	  glTranslatef(m_vTranslateOffset[X], m_vTranslateOffset[Y], m_vTranslateOffset[Z]);
	  glTranslatef(0.0f, 0.0f, -8.0f+m_vTrackBallOffset[Z]);

	  glRotatef(m_vTrackBallOffset[X], 0.0f, 1.0f, 0.0f);
	  glRotatef(m_vTrackBallOffset[Y], 1.0f, 0.0f, 0.0f);

	  glRotatef(180.0f, 0.0f, 1.0f, 0.0f);

		if(lightchanged[UPDATE_OGL])
		{
			glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
			lightchanged[UPDATE_OGL] = GL_FALSE;
		}

		glDisable(GL_LIGHTING);
		glPushMatrix();
			glColor3f(1.0f, 0.0f, 0.0f);
			glTranslatef(lightpos[X], lightpos[Y]+pFrame->m_fTranslateY, lightpos[Z]);
			auxWireCube(0.1);
			glPopMatrix();
		glEnable(GL_LIGHTING);

		glPushMatrix();
			glTranslatef(0.0f, pFrame->m_fTranslateY, 0.0f);			
			if(m_iBoundingBoxMode != BOUNDINGBOX)
			{
				DrawTorso(pFrame);
			}
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0f, pPrevFrame->m_fTranslateY, 0.0f);			
			if(m_bGhostMode == TRUE)
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_ONE, GL_ONE);
				if(m_iBoundingBoxMode != BOUNDINGBOX)
				{
					DrawTorso(pPrevFrame);
				}
				glDisable(GL_BLEND);
			}
		glPopMatrix();

		glPushMatrix();
			if(TRUE == m_bSceneMode)
			{
				DrawScene();
			}
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();

		glTranslatef(m_vTranslateOffset[X], m_vTranslateOffset[Y], m_vTranslateOffset[Z]);
		glTranslatef(0.0f, 0.0f, -8.0f+m_vTrackBallOffset[Z]);

		glRotatef(m_vTrackBallOffset[X], 0.0f, 1.0f, 0.0f);
		glRotatef(m_vTrackBallOffset[Y], 1.0f, 0.0f, 0.0f);

		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);

		if(m_iBoundingBoxMode != SOLID)
		{
			DrawBodyBoundingBox();
		}
	glPopMatrix();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glPopMatrix();//5

	glEnable(GL_LIGHTING);

	}

	{
	glPushMatrix();//5

	glViewport(0.0f, floor(WinH - quadHeight), floor(quadWidth), floor(quadHeight));

	  glTranslatef(0.0f, 0.0f, -8.0f);
	  glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	  DrawTorso(pFrame);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glPopMatrix();//5

	}

	{
	glPushMatrix();//5

	glViewport(floor(WinW - quadWidth), floor(WinH - quadHeight), floor(quadWidth), floor(quadHeight));

	  glTranslatef(0.0f, 0.0f, -8.0f);
	  glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	  DrawTorso(pFrame);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glPopMatrix();//5

	}

    glViewport (0.0, 0.0, floor(WinW), floor(WinH));

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void CTriangleView::Draw_Small_QuadView()
{
	LPANIMATION pAnim = this->GetCurrentAnimation();
	LPFRAME pFrame = this->GetCurrentFrame(pAnim);

	float quadWidth;
	float quadHeight;
	int WinW, WinH;
	RECT rect;

	this->GetClientRect(&rect);

	WinW = rect.left - rect.right;
	WinH = rect.bottom - rect.top;

	if(WinW < 0)
	{
		WinW = -WinW;
	}

	if(WinH < 0)
		WinH = -WinH;
	quadWidth = (float)WinW / 6.0f;
	quadHeight = (float)WinH / 6.0f;

	glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

    glMatrixMode (GL_PROJECTION);
	glPushMatrix();//1
    glLoadIdentity ();
	  
    gluOrtho2D(-0.01f, quadWidth + 0.01f, 0.0f, quadHeight);

    glMatrixMode (GL_MODELVIEW);
	glPushMatrix();//2
    glLoadIdentity ();
	
	glDisable(GL_LIGHTING);
    glViewport(0.0, 0.0, floor(quadWidth), floor(quadHeight));

    glBegin (GL_QUADS);
    glVertex2f (0.0f, 0.0f);
    glVertex2f (quadWidth, 0.0f);
    glVertex2f (quadWidth, quadHeight);
    glVertex2f (0.0f, quadHeight);
    glEnd ();

    glViewport(floor(WinW - quadWidth), 1.0f, floor(quadWidth), floor(quadHeight));

	glBegin (GL_QUADS);
	glVertex2f (0.0f, 0.0f);
	glVertex2f (quadWidth, 0.0f);
	glVertex2f (quadWidth, quadHeight);
	glVertex2f (0.0f, quadHeight);
	glEnd ();

	glViewport(0.0f, floor(WinH - quadHeight), floor(quadWidth), floor(quadHeight));

	glBegin (GL_QUADS);
	glVertex2f (0.0f, 0.0f);
	glVertex2f (quadWidth, 0.0f);
	glVertex2f (quadWidth, quadHeight);
	glVertex2f (0.0f, quadHeight);
	glEnd ();

	glViewport(floor(WinW - quadWidth), floor(WinH - quadHeight), floor(quadWidth), floor(quadHeight));

	glBegin (GL_QUADS);
	glVertex2f (0.0f, 0.0f);
	glVertex2f (quadWidth, 0.0f);
	glVertex2f (quadWidth, quadHeight);
	glVertex2f (0.0f, quadHeight);
	glEnd ();

	glDisable(GL_BLEND);

	glEnable(GL_LIGHTING);

    glClear(GL_DEPTH_BUFFER_BIT);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();//5
    glViewport(0.0, 0.0, floor(quadWidth), floor(quadHeight));
    glTranslatef(0.0f, 0.0f, -8.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    DrawTorso(pFrame);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPopMatrix();//5

	glPushMatrix();//5
    glViewport(floor(WinW - quadWidth), 1.0f, floor(quadWidth), floor(quadHeight));
    glTranslatef(0.0f, 0.0f, -8.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    DrawTorso(pFrame);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPopMatrix();//5

	glPushMatrix();//5
	glViewport(0.0f, floor(WinH - quadHeight), floor(quadWidth), floor(quadHeight));
    glTranslatef(0.0f, 0.0f, -8.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    DrawTorso(pFrame);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPopMatrix();//5

	glPushMatrix();//5
	glViewport(floor(WinW - quadWidth), floor(WinH - quadHeight), floor(quadWidth), floor(quadHeight));
    glTranslatef(0.0f, 0.0f, -8.0f);
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    DrawTorso(pFrame);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPopMatrix();//5

    glViewport (0.0, 0.0, floor(WinW), floor(WinH));
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void CTriangleView::Draw_Mode1(void)
{
	LPANIMATION pAnim = this->GetCurrentAnimation();
	LPFRAME pFrame = this->GetCurrentFrame(pAnim);
	LPFRAME pPrevFrame;

	if(pFrame->m_iFrame != 1)
	{
		pPrevFrame = pFrame->prev;
	}else
	{
		pPrevFrame = pFrame;
	}

	glPushMatrix();

		glTranslatef(m_vTranslateOffset[X], m_vTranslateOffset[Y], m_vTranslateOffset[Z]);
		glTranslatef(0.0f, 0.0f, -8.0f+m_vTrackBallOffset[Z]);

		glRotatef(m_vTrackBallOffset[X], 0.0f, 1.0f, 0.0f);
		glRotatef(m_vTrackBallOffset[Y], 1.0f, 0.0f, 0.0f);

		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);

		if(lightchanged[UPDATE_OGL])
		{
			glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
			lightchanged[UPDATE_OGL] = GL_FALSE;
		}

		glDisable(GL_LIGHTING);
		glPushMatrix();
			glColor3f(1.0f, 0.0f, 0.0f);
			glTranslatef(lightpos[X], lightpos[Y]+pFrame->m_fTranslateY, lightpos[Z]);
			auxWireCube(0.1);
			glPopMatrix();
		glEnable(GL_LIGHTING);

		glPushMatrix();
			glTranslatef(0.0f, pFrame->m_fTranslateY, 0.0f);			
			if(m_iBoundingBoxMode != BOUNDINGBOX)
			{
				DrawTorso(pFrame);
			}
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0f, pPrevFrame->m_fTranslateY, 0.0f);			
			if(m_bGhostMode == TRUE)
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_ONE, GL_ONE);
				if(m_iBoundingBoxMode != BOUNDINGBOX)
				{
					DrawTorso(pPrevFrame);
				}
				glDisable(GL_BLEND);
			}
		glPopMatrix();

		glPushMatrix();
			if(TRUE == m_bSceneMode)
			{
				DrawScene();
			}
		glPopMatrix();

	glPopMatrix();

	glPushMatrix();

		glTranslatef(m_vTranslateOffset[X], m_vTranslateOffset[Y], m_vTranslateOffset[Z]);
		glTranslatef(0.0f, 0.0f, -8.0f+m_vTrackBallOffset[Z]);

		glRotatef(m_vTrackBallOffset[X], 0.0f, 1.0f, 0.0f);
		glRotatef(m_vTrackBallOffset[Y], 1.0f, 0.0f, 0.0f);

		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	
		if(m_iBoundingBoxMode != SOLID)
		{
			DrawBodyBoundingBox();
		}
	glPopMatrix();
}

void CTriangleView::Draw_Mode2(void)
{
	LPANIMATION pAnim = this->GetCurrentAnimation();
	LPFRAME pFrame = this->GetCurrentFrame(pAnim);
	LPFRAME pPrevFrame;

	if(pFrame->m_iFrame != 1)
	{
		pPrevFrame = pFrame->prev;
	}else
	{
		pPrevFrame = pFrame;
	}

	glPushMatrix();

		glTranslatef(m_vTranslateOffset[X], m_vTranslateOffset[Y], m_vTranslateOffset[Z]);
		glTranslatef(0.0f, 0.0f, -8.0f+m_vTrackBallOffset[Z]);

		glRotatef(m_vTrackBallOffset[X], 0.0f, 1.0f, 0.0f);
		glRotatef(m_vTrackBallOffset[Y], 1.0f, 0.0f, 0.0f);

		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);

		if(lightchanged[UPDATE_OGL])
		{
			glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
			lightchanged[UPDATE_OGL] = GL_FALSE;
		}

		glDisable(GL_LIGHTING);
		glPushMatrix();
			glColor3f(1.0f, 0.0f, 0.0f);
			glTranslatef(lightpos[X], lightpos[Y]+pFrame->m_fTranslateY, lightpos[Z]);
			auxWireCube(0.1);
			glPopMatrix();
		glEnable(GL_LIGHTING);

		glPushMatrix();
			glTranslatef(0.0f, pFrame->m_fTranslateY, 0.0f);			
			if(m_iBoundingBoxMode != BOUNDINGBOX)
			{
				DrawTorso(pFrame);
			}
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0.0f, pPrevFrame->m_fTranslateY, 0.0f);			
			if(m_bGhostMode == TRUE)
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_ONE, GL_ONE);
				if(m_iBoundingBoxMode != BOUNDINGBOX)
				{
					DrawTorso(pPrevFrame);
				}
				glDisable(GL_BLEND);
			}
		glPopMatrix();

		glPushMatrix();
			if(TRUE == m_bSceneMode)
			{
				DrawScene();
			}
		glPopMatrix();

	glPopMatrix();

	glPushMatrix();

		glTranslatef(m_vTranslateOffset[X], m_vTranslateOffset[Y], m_vTranslateOffset[Z]);
		glTranslatef(0.0f, 0.0f, -8.0f+m_vTrackBallOffset[Z]);

		glRotatef(m_vTrackBallOffset[X], 0.0f, 1.0f, 0.0f);
		glRotatef(m_vTrackBallOffset[Y], 1.0f, 0.0f, 0.0f);

		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);

		if(m_iBoundingBoxMode != SOLID)
		{
			DrawBodyBoundingBox();
		}
	glPopMatrix();

	glPushMatrix();
		glDisable(GL_LIGHTING);
		Draw_Small_QuadView();
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

void CTriangleView::Draw_Mode3(void)
{
	LPANIMATION pAnim = this->GetCurrentAnimation();
	LPFRAME pFrame = this->GetCurrentFrame(pAnim);

	glPushMatrix();

		Draw_Big_QuadView();
		
	glPopMatrix();
}

void CTriangleView::DrawScene(void)
{
	int i;

	this->InitScene();
	
	for(i=0; i<8; i++)
	{
	  vecTranslate(scene[i], 0.0f, -2.5f, 0.0f);
	}

	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDisable(GL_LIGHTING);
	DrawSolidBox(scene);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
}

void CTriangleView::DrawNose(void)
{
	glScalef(0.025f, 0.025f, 0.05f);
	auxSolidSphere(1.0f);
}

BOOL CTriangleView::CheckPointInBox(vector point, vector *pBox)
{
	if(point[X] <= pBox[0][X] &&
		point[X] >= pBox[3][X] &&
		point[Y] <= pBox[0][Y] &&
		point[Y] >= pBox[1][Y] &&
		point[Z] <= pBox[0][Z] &&
		point[Z] >= pBox[4][Z])
	{
		return TRUE;
	}else
	{
		return FALSE;
	}
}

void CTriangleView::CollideDetection(void)
{
	int i;

	m_bLeftFootHit = FALSE;
	m_bRightFootHit = FALSE;

	for(i=0; i<8; i++)
	{
		if(CheckPointInBox(left_foot_box[i], scene) == TRUE)
		{
			m_bLeftFootHit = TRUE;
			break;
		}
	}

	for(i=0; i<8; i++)
	{
		if(CheckPointInBox(right_foot_box[i], scene) == TRUE)
		{
			m_bRightFootHit = TRUE;
			break;
		}
	}

}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
// Render your OpenGL Scene here.
void CTriangleView::GLRenderScene(void *pData)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.1f, 0.1f, 0.5f, 1.0f);

	CollideDetection();

	glPushMatrix();

	  switch(m_iViewMode)
	  {
	    case VIEWMODE_1:
			Draw_Mode1();
		break;

	    case VIEWMODE_2:
			Draw_Mode2();
		break;

	    case VIEWMODE_3:
			Draw_Mode3();
		break;
	  }
	glPopMatrix();

	glFlush();
}

//////////////////////////////////////////////////////////////////
// Do any initialization of the rendering context here, such as
// setting background colors, setting up lighting, or performing
// preliminary calculations.
void CTriangleView::GLSetupRC(void *pData)
{
    GLfloat Ambient0[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient0);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

	lightchanged[UPDATE_TEX] = GL_TRUE;
	lightchanged[UPDATE_OGL] = GL_TRUE;

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}
