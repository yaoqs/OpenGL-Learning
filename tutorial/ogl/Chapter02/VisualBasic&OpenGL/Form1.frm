VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "VB����OpenGLӦ�ó���"
   ClientHeight    =   3192
   ClientLeft      =   60
   ClientTop       =   348
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   266
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   390
   StartUpPosition =   2  'CenterScreen
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

' Note the ScaleMode of this form is set to pixels

Private Sub Form_KeyDown(KeyCode As Integer, Shift As Integer)
    Keys(KeyCode) = True
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
    Keys(KeyCode) = False
End Sub

Private Sub Form_Resize()
    ReSizeGLScene ScaleWidth, ScaleHeight
End Sub

Private Sub Form_Unload(Cancel As Integer)
    KillGLWindow
End Sub


