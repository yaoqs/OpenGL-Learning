// TriangleView.h : interface of the CTriangleView class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __TRIANGLEVIEW_H__
#define __TRIANGLEVIEW_H__

#include "vector.h"

#define M_PI			3.14159265

#define EYESIZE			0.09f
#define MOUTHSIZE		0.05f

#define TRACKBALL		1
#define DRIVE			2
#define TRANSLATE		3
#define SELECTBODY		4
#define TRANSLATEBODY		5

#define VIEWMODE_1		1
#define VIEWMODE_2		2
#define VIEWMODE_3		3

#define BOUNDINGBOX		1
#define SOLID			2
#define BOUNDINGBOXANDSOLID	3

typedef struct _BONE
{
	GLint id;
	BOOL b_scale;
	BOOL b_tran;
	BOOL b_draw;
	vector translate;
	vector scale;
}BONE;

typedef BONE FAR *LPBONE;

typedef struct _FRAME 
{
	struct _FRAME FAR *prev;
	struct _FRAME FAR *next;

	int m_iFrame;  // Global frame

	float m_fHeadX;
	float m_fHeadY;

	float  m_fShoulderX;
	float  m_fShoulderY;

	float m_fLeftUpperArmX;
	float m_fLeftUpperArmY;

	float m_fLeftLowerArmX;
	float m_fLeftLowerArmY;

	float m_fLeftHandX;
	float m_fLeftHandY;

	float m_fRightUpperArmX;
	float m_fRightUpperArmY;

	float m_fRightLowerArmX;
	float m_fRightLowerArmY;

	float m_fRightHandX;
	float m_fRightHandY;

	float m_fUpperBodyX;
	float m_fUpperBodyY;

	float m_fLowerBodyX;
	float m_fLowerBodyY;

	float m_fLeftUpperLegX;
	float m_fLeftUpperLegY;

	float m_fLeftLowerLegX;
	float m_fLeftLowerLegY;

	float m_fLeftFootX;
	float m_fLeftFootY;

	float m_fRightUpperLegX;
    float m_fRightUpperLegY;

	float m_fRightLowerLegX;
	float m_fRightLowerLegY;

	float m_fRightFootX;
	float m_fRightFootY;

	float m_fTranslateY;
}FRAME;

typedef FRAME FAR *LPFRAME;

typedef struct _ANIMATION
{
	struct _ANIMATION FAR *prev;
	struct _ANIMATION FAR *next;

	char name[20];

	int m_iID;

	int m_iTotalFrame;
	int m_iCurrentFrame;

	FRAME FrameList;

	float m_fBaseHeight;

}ANIMATION;

typedef ANIMATION FAR *LPANIMATION;

class CTriangleDoc;

class CTriangleView : public CView
{
protected: // create from serialization only
	CTriangleView();
	DECLARE_DYNCREATE(CTriangleView)

// My Code : Motion Editer
public:
// body variable
	BONE body[30];

	vector  scene[8];
	vector lower_body_box[8];
	vector left_upper_leg_box[8];
	vector left_lower_leg_box[8];
	vector left_foot_box[8];
	vector right_upper_leg_box[8];
	vector right_lower_leg_box[8];
	vector right_foot_box[8];
	vector left_leg_offset;
	vector right_leg_offset;

	vector upper_body_box[8];
	vector shoulder_box[8];
	vector head_box[8];
	vector	left_upper_arm_box[8];
	vector left_lower_arm_box[8];
	vector left_hand_box[8];
	vector right_upper_arm_box[8];
	vector right_lower_arm_box[8];
	vector right_hand_box[8];
	vector left_arm_offset;
	vector right_arm_offset;

	//Manipulate Mode
	int m_iManipulateMode;
	int m_iViewMode;
	int m_iBoundingBoxMode;
	BOOL m_bGhostMode;
	BOOL m_bSceneMode;
//	BOOL m_bBoundingBoxMode;

	//Constrain Mode
	BOOL m_bConstrainX;
	BOOL m_bConstrainY;
	BOOL m_bConstrainZ;

	//Left Mouse Button
	int m_iLeftCurrentX;
	int m_iLeftCurrentY;
	int m_iLeftOldX;
	int m_iLeftOldY;
	BOOL m_bLeftCapture;

	//Right Mouse Button
	int m_iRightCurrentX;
	int m_iRightCurrentY;
	int m_iRightOldX;
	int m_iRightOldY;
	BOOL m_bRightCapture;

	//TrackBall variable
	vector m_vTrackBallOffset;
	vector m_vTranslateOffset;
	float m_fHeight;

//function
	void InitBody(void);
	void InitAnim(void);
	void InitTempFrame(void);
	void InitScene(void);
	void InitBodyBoundingBox(void);
	void SetBoundingBox(vector *pbox, GLfloat x, GLfloat y, GLfloat z);

	void DrawSphere(LPBONE);
	void DrawLeftArm(LPFRAME pFrame);
	void DrawRightArm(LPFRAME pFrame);
	void DrawLeftLeg(LPFRAME pFrame);
	void DrawRightLeg(LPFRAME pFrame);
	void DrawUpperBody(LPFRAME pFrame);
	void DrawTorso(LPFRAME pFrame);
	void ManipulateBody(float offsetX, float offsetY);
	void TranslateBody(float Height);
	void DrawNose(void);
	void DrawMouth(void);
	void DrawEye(int LR);
	void DrawScene(void);
	void DrawBodyBoundingBox(void);
	void DrawBox(vector *pbox);
	void DrawSolidBox(vector *pbox);
	void DrawText(GLuint x, GLuint y, int WinW, int WinH, GLfloat scale, char* format, ...);

	void Draw_Mode1(void);
	void Draw_Mode2(void);
	void Draw_Mode3(void);
	void Draw_Big_QuadView(void);
	void Draw_Small_QuadView(void);
	void SetActiveBody(int index);

// Frame Management
	int m_iTotalGroup;
	int m_iPlaySpeed;
	int m_iPlayCount;
	BOOL m_bPlay;

	ANIMATION Anim;
	LPANIMATION m_pCurrentAnim;

	FRAME TempFrame;

	void FramePlay(void);
	void FrameStop(void);
	void FrameAddGroup(void);
	void FrameDelGroup(void);
	void FrameAddFrame(void);
	void FrameDelFrame(void);
	void FrameNext(void);
	void FramePrev(void);
	void FrameFirst(void);
	void FrameLast(void);

	void PlaySpeed(int updown);

	void AddGroup(CString *str);
	void DelGroup(LPANIMATION pLastAnim, BOOL bClearString = TRUE);
	void LinkGroup(LPANIMATION pAnim, LPANIMATION pLastAnim);
	void AddFrame(LPANIMATION pAnim);
	void LinkFrame(LPFRAME pFrame, LPFRAME pLast);
	void DelFrame(LPFRAME pLast);
	void ClearGroupFrame(LPANIMATION pAnim);
	void AddGroupFromFile(LPANIMATION pAnim);
	void AddFrameFromFile(LPFRAME pFrame, LPANIMATION pAnim);

	void ResetSystem();

	void UpdateFrameInfo(void);
	void UpdateGroupInfo(void);

	void ChangeCurrentAnimation(int i, CString& str);
	LPANIMATION GetCurrentAnimation(void);
	LPFRAME GetCurrentFrame(LPANIMATION pAnim);
	void GetMotionBody(LPFRAME pFrame, int body_id, float *fOffsetX, float *fOffsetY);
	void SetMotionBody(LPFRAME pFrame, int body_id, float fOffsetX, float fOffsetY);
	void CheckAngle(float  *x, float  *y);
	void ChangeGroupName(void);

	BOOL LoadMotion2File(LPSTR pszFileName);
	BOOL LoadMotion2File(CFile *fp);
	BOOL SaveMotion2File(LPSTR pszFileName);
	BOOL SaveMotion2File(CFile *fp);
	BOOL SaveFrame2File(CFile *fp, LPANIMATION pAnim);
	BOOL LoadFrame2File(CFile *fp, LPANIMATION pAnim);

//Collide detection
	BOOL m_bLeftFootHit;
	BOOL m_bRightFootHit;

	void InitCollideDetection(void);
	void CollideDetection(void);
	BOOL CheckPointInBox(vector point, vector *pBox);

//Facial Expression Animation
	int m_iEyeOpenClose;

// Attributes
public:
	CTriangleDoc* GetDocument();

	HGLRC m_hRC;	// Rendering Context
	HDC m_hDC;		// Device Context

	CPalette m_GLPalette;	// Logical Palette

	int body_id;
// Operations
public:
	void GLResize(GLsizei w, GLsizei h);
	void GLRenderScene(void *pData);
	void GLSetupRC(void *pData);

protected:
	void InitializePalette(void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTriangleView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTriangleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTriangleView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTrackballmode();
	afx_msg void OnUpdateTrackballmode(CCmdUI* pCmdUI);
	afx_msg void OnTranslatemode();
	afx_msg void OnUpdateTranslatemode(CCmdUI* pCmdUI);
	afx_msg void OnDrivemode();
	afx_msg void OnUpdateDrivemode(CCmdUI* pCmdUI);
	afx_msg void OnSelectbodymode();
	afx_msg void OnUpdateSelectbodymode(CCmdUI* pCmdUI);
	afx_msg void OnTranslatebodymode();
	afx_msg void OnUpdateTranslatebodymode(CCmdUI* pCmdUI);
	afx_msg void OnConstrainXmode();
	afx_msg void OnUpdateConstrainXmode(CCmdUI* pCmdUI);
	afx_msg void OnConstrainYmode();
	afx_msg void OnUpdateConstrainYmode(CCmdUI* pCmdUI);
	afx_msg void OnConstrainZmode();
	afx_msg void OnUpdateConstrainZmode(CCmdUI* pCmdUI);
	afx_msg void OnMotionfileopen();
	afx_msg void OnMotionfilesave();
	afx_msg void OnResetsystem();
	afx_msg void OnResetcurrentframe();
	afx_msg void OnResetcurrentselectbody();
	afx_msg void OnResetcamera();
	afx_msg void OnCopyframe();
	afx_msg void OnPastedata();
	afx_msg void OnViewmode1();
	afx_msg void OnUpdateViewmode1(CCmdUI* pCmdUI);
	afx_msg void OnViewmode2();
	afx_msg void OnUpdateViewmode2(CCmdUI* pCmdUI);
	afx_msg void OnViewmode3();
	afx_msg void OnUpdateViewmode3(CCmdUI* pCmdUI);
	afx_msg void OnGhostmode();
	afx_msg void OnUpdateGhostmode(CCmdUI* pCmdUI);
	afx_msg void OnRefreshscreen();
	afx_msg void OnBoundingboxmode();
	afx_msg void OnUpdateBoundingboxmode(CCmdUI* pCmdUI);
	afx_msg void OnSolidmode();
	afx_msg void OnUpdateSolidmode(CCmdUI* pCmdUI);
	afx_msg void OnBoundingboxandsolidmode();
	afx_msg void OnUpdateBoundingboxandsolidmode(CCmdUI* pCmdUI);
	afx_msg void OnScenemodel();
	afx_msg void OnUpdateScenemodel(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TriangleView.cpp
inline CTriangleDoc* CTriangleView::GetDocument()
   { return (CTriangleDoc*)m_pDocument; }
#endif

#endif
/////////////////////////////////////////////////////////////////////////////
