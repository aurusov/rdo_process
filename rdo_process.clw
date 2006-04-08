; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=RP_GENERATION_TYPE_MJ
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "rdo_process.h"
LastPage=0

ClassCount=23
Class1=RDOLink
Class2=RPDockWnd
Class3=RPPageCtrl
Class4=RPPageCtrlItemLabel
Class5=RPPageCtrlItem
Class6=RPProjectBar
Class7=CSizingControlBarG
Class8=CSizingControlBar
Class9=CSCBMiniDockFrameWnd
Class10=RPApp
Class11=RPAboutDlg
Class12=RPChildFrame
Class13=RPFlowChart
Class14=RPMainFrame
Class15=RPShapeCreateDlg1_MJ
Class16=RPShapeCreateDlg2_MJ
Class17=RPListBox
Class18=RPShapeProcessDlg1_MJ
Class19=RPShapeProcessDlg2_MJ
Class20=RPShapeTerminateDlg1_MJ

ResourceCount=12
Resource1=TOOLBARBLOCKMJ
Resource2=IDD_DIALOG_CREATE_1_MJ
Resource3=IDD_ABOUT
Resource4=IDD_DIALOG_RESOURCE_DLG1
Resource5=IDD_DIALOG_CREATE_2_MJ
Resource6=IDD_DIALOG_TERMINATE_1_MJ
Resource7=IDR_RDO_PRTYPE (English (U.S.))
Resource8=IDD_DIALOG_GEN_TYPE
Class21=RPShapeResourceDLG1_MJ
Resource9=IDD_DIALOG_PROCESS_1_MJ
Resource10=IDR_TOOLBAR1
Class22=RPToolBarBlockMJ
Resource11=IDD_DIALOG_PROCESS_2_MJ
Class23=RP_GENERATION_TYPE_MJ
Resource12=IDR_MAINFRAME (English (U.S.))

[CLS:RDOLink]
Type=0
BaseClass=CWnd
HeaderFile=ctrl\rdolink.h
ImplementationFile=ctrl\rdolink.cpp

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
LastObject=CSCBMiniDockFrameWnd

[CLS:RPApp]
Type=0
BaseClass=CWinApp
HeaderFile=rdoprocess_app.h
ImplementationFile=rdoprocess_app.cpp
LastObject=ID_FLOW_ROTATE

[CLS:RPAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=rdoprocess_app.h
ImplementationFile=rdoprocess_app.cpp

[CLS:RPChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=rdoprocess_childfrm.h
ImplementationFile=rdoprocess_childfrm.cpp

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
LastObject=ID_GEN_TYPE
Filter=T
VirtualFilter=fWC

[CLS:RPShapeCreateDlg1_MJ]
Type=0
BaseClass=CDialog
HeaderFile=rdoprocess_shape_create_dlg1_MJ.h
ImplementationFile=rdoprocess_shape_create_dlg1_MJ.cpp
LastObject=ID_APP_ABOUT
Filter=D
VirtualFilter=dWC

[CLS:RPShapeCreateDlg2_MJ]
Type=0
BaseClass=CDialog
HeaderFile=rdoprocess_shape_create_dlg2_MJ.h
ImplementationFile=rdoprocess_shape_create_dlg2_MJ.cpp
Filter=D
VirtualFilter=dWC
LastObject=ID_FLOW_ROTATE

[CLS:RPListBox]
Type=0
BaseClass=CListBox
HeaderFile=rdoprocess_shape_process_dlg1_MJ.h
ImplementationFile=rdoprocess_shape_process_dlg1_MJ.cpp
Filter=W
VirtualFilter=bWC
LastObject=ID_APP_ABOUT

[CLS:RPShapeProcessDlg1_MJ]
Type=0
BaseClass=CDialog
HeaderFile=rdoprocess_shape_process_dlg1_MJ.h
ImplementationFile=rdoprocess_shape_process_dlg1_MJ.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_BUTTON1

[CLS:RPShapeProcessDlg2_MJ]
Type=0
BaseClass=CDialog
HeaderFile=rdoprocess_shape_process_dlg2_MJ.h
ImplementationFile=rdoprocess_shape_process_dlg2_MJ.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_COMBO1

[CLS:RPShapeTerminateDlg1_MJ]
Type=0
BaseClass=CDialog
HeaderFile=rdoprocess_shape_terminate_dlg1_MJ.h
ImplementationFile=rdoprocess_shape_terminate_dlg1_MJ.cpp

[DLG:IDD_ABOUT]
Type=1
Class=RPAboutDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDC_ABOUT_PICTURE,static,1342177283
Control3=IDC_ABOUT_CAPTION,static,1342308353
Control4=IDC_ABOUT_ADDRESS,static,1342308353
Control5=IDC_ABOUT_TEL,static,1342308354
Control6=IDC_ABOUR_EMAIL_STATIC,static,1342308354
Control7=IDC_ABOUT_EMAIL,static,1342308608
Control8=IDC_ABOUR_WEB_STATIC,static,1342308354
Control9=IDC_ABOUT_WEB,static,1342308608

[DLG:IDD_DIALOG_CREATE_1_MJ]
Type=1
Class=RPShapeCreateDlg1_MJ
ControlCount=22
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT2,edit,1350631552
Control7=IDC_EDIT3,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352
Control11=IDC_COMBO1,combobox,1344340227
Control12=IDC_EDIT4,edit,1350631552
Control13=IDC_EDIT5,edit,1484849280
Control14=IDC_EDIT6,edit,1476460672
Control15=IDC_EDIT7,edit,1476460672
Control16=IDC_EDIT8,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_BUTTON1,button,1342242816

[DLG:IDD_DIALOG_CREATE_2_MJ]
Type=1
Class=RPShapeCreateDlg2_MJ
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT2,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT3,edit,1350631552
Control10=IDC_EDIT4,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT5,edit,1350631552
Control13=IDC_STATIC,button,1342177287

[DLG:IDD_DIALOG_PROCESS_1_MJ]
Type=1
Class=RPShapeProcessDlg1_MJ
ControlCount=30
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_COMBO1,combobox,1344340227
Control6=IDC_EDIT4,edit,1350631552
Control7=IDC_EDIT5,edit,1484849280
Control8=IDC_EDIT6,edit,1476460672
Control9=IDC_EDIT7,edit,1476460672
Control10=IDC_EDIT8,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_EDIT1,edit,1350631552
Control18=IDC_STATIC,static,1342308352
Control19=IDC_COMBO2,combobox,1344339971
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EDIT2,edit,1350631552
Control22=IDC_STATIC,button,1342177287
Control23=IDC_BUTTON1,button,1342242816
Control24=IDC_BUTTON2,button,1342242816
Control25=IDC_LIST1,listbox,1352728833
Control26=IDC_STATIC,static,1342308352
Control27=IDC_COMBO3,combobox,1344340227
Control28=IDC_STATIC,button,1342177287
Control29=IDC_STATIC,static,1342308352
Control30=IDC_COMBO4,combobox,1344340227

[DLG:IDD_DIALOG_PROCESS_2_MJ]
Type=1
Class=RPShapeProcessDlg2_MJ
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO1,combobox,1344340226

[DLG:IDD_DIALOG_TERMINATE_1_MJ]
Type=1
Class=RPShapeTerminateDlg1_MJ
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=RPMainFrame
Command1=ID_FILE_NEW
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_FLOW_SELECT
Command6=ID_FLOW_CONNECTOR
Command7=ID_FLOW_ROTATE
Command8=ID_GENERATE
Command9=ID_GEN_TYPE
CommandCount=9

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

[DLG:IDD_DIALOG_RESOURCE_DLG1]
Type=1
Class=RPShapeResourceDLG1_MJ
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT2,edit,1350631552
Control7=IDC_STATIC,static,1342308352

[CLS:RPShapeResourceDLG1_MJ]
Type=0
HeaderFile=rdoprocess_shape_resource_DLG1_MJ.h
ImplementationFile=rdoprocess_shape_resource_DLG1_MJ.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT2

[TB:IDR_TOOLBAR1]
Type=1
Command1=ID_BUTTON32779
CommandCount=1

[TB:TOOLBARBLOCKMJ]
Type=1
Class=RPToolBarBlockMJ
Command1=ID_BUTTON32779
Command2=ID_BUTTON32781
Command3=ID_BUTTON32782
Command4=ID_BUTTON32783
CommandCount=4

[CLS:RPToolBarBlockMJ]
Type=0
HeaderFile=rdoprocess_tool_bar_blockMJ.h
ImplementationFile=rdoprocess_tool_bar_blockMJ.cpp
BaseClass=CStatusBarCtrl
Filter=W
VirtualFilter=WC
LastObject=ID_APP_ABOUT

[DLG:IDD_DIALOG_GEN_TYPE]
Type=1
Class=RP_GENERATION_TYPE_MJ
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COMBO1,combobox,1344339970
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352

[CLS:RP_GENERATION_TYPE_MJ]
Type=0
HeaderFile=rdoprocess_generation_type_MJ.h
ImplementationFile=rdoprocess_generation_type_MJ.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_COMBO1

