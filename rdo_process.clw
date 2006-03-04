; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=RPChildFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "rdo_process.h"
LastPage=0

ClassCount=13
Class1=RPDockWnd
Class2=RPPageCtrl
Class3=RPPageCtrlItemLabel
Class4=RPPageCtrlItem
Class5=RPProjectBar
Class6=CSizingControlBarG
Class7=CSizingControlBar
Class8=CSCBMiniDockFrameWnd
Class9=RPApp
Class10=RPAboutDlg
Class11=RPChildFrame
Class12=RPFlowChart
Class13=RPMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME (English (U.S.))
Resource2=IDR_RDO_PRTYPE (English (U.S.))
Resource3=IDD_ABOUTBOX (English (U.S.))

[CLS:RPDockWnd]
Type=0
BaseClass=CSizingControlBarG
HeaderFile=ctrl\rdoprocess_dockwnd.h
ImplementationFile=ctrl\rdoprocess_dockwnd.cpp

[CLS:RPPageCtrl]
Type=0
BaseClass=CWnd
HeaderFile=ctrl\rdoprocess_pagectrl.h
ImplementationFile=ctrl\rdoprocess_pagectrl.cpp

[CLS:RPPageCtrlItemLabel]
Type=0
BaseClass=CWnd
HeaderFile=ctrl\rdoprocess_pagectrl.h
ImplementationFile=ctrl\rdoprocess_pagectrl.cpp

[CLS:RPPageCtrlItem]
Type=0
BaseClass=CWnd
HeaderFile=ctrl\rdoprocess_pagectrl.h
ImplementationFile=ctrl\rdoprocess_pagectrl.cpp

[CLS:RPProjectBar]
Type=0
BaseClass=RPDockWnd
HeaderFile=ctrl\rdoprocess_projectbar.h
ImplementationFile=ctrl\rdoprocess_projectbar.cpp

[CLS:CSizingControlBarG]
Type=0
BaseClass=baseCSizingControlBarG
HeaderFile=ctrl\sizecbar\scbarg.h
ImplementationFile=ctrl\sizecbar\scbarg.cpp

[CLS:CSizingControlBar]
Type=0
BaseClass=baseCSizingControlBar
HeaderFile=ctrl\sizecbar\sizecbar.h
ImplementationFile=ctrl\sizecbar\sizecbar.cpp

[CLS:CSCBMiniDockFrameWnd]
Type=0
BaseClass=baseCSCBMiniDockFrameWnd
HeaderFile=ctrl\sizecbar\sizecbar.h
ImplementationFile=ctrl\sizecbar\sizecbar.cpp
Filter=N
LastObject=CSCBMiniDockFrameWnd

[CLS:RPApp]
Type=0
BaseClass=CWinApp
HeaderFile=rdoprocess_app.h
ImplementationFile=rdoprocess_app.cpp

[CLS:RPAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=rdoprocess_app.cpp
ImplementationFile=rdoprocess_app.cpp

[CLS:RPChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=rdoprocess_childfrm.h
ImplementationFile=rdoprocess_childfrm.cpp
Filter=M
LastObject=ID_APP_ABOUT

[CLS:RPFlowChart]
Type=0
BaseClass=CWnd
HeaderFile=rdoprocess_flowchart.h
ImplementationFile=rdoprocess_flowchart.cpp

[CLS:RPMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=rdoprocess_mainfrm.h
ImplementationFile=rdoprocess_mainfrm.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=RPAboutDlg

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_FLOW_SELECT
Command6=ID_FLOW_CONNECTOR
Command7=ID_FLOW_ROTATE
CommandCount=7

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
Command3=ID_VIEW_TOOLBAR
Command4=ID_VIEW_STATUS_BAR
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_RDO_PRTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_CLOSE
Command3=ID_APP_EXIT
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_VIEW_TOOLBAR
Command9=ID_VIEW_STATUS_BAR
Command10=ID_WINDOW_CASCADE
Command11=ID_WINDOW_TILE_HORZ
Command12=ID_WINDOW_ARRANGE
Command13=ID_APP_ABOUT
CommandCount=13

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_EDIT_PASTE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_NEXT_PANE
Command7=ID_PREV_PANE
Command8=ID_EDIT_COPY
Command9=ID_EDIT_PASTE
Command10=ID_EDIT_CUT
Command11=ID_EDIT_UNDO
CommandCount=11

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

