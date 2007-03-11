//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: wsquerywindow.h 5827 2007-01-04 16:35:14 hiroshi $
// Copyright (C) 2002 - 2007, The pgAdmin Development Team
// This software is released under the Artistic Licence
//
// wsquerywindow.h - debugger 
//
//////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// class wsQueryWindow
//
//	The wsQueryWindow class extends wsRichWindow to handle command input from
//  the user (in other words, when the user types in a command, he's typing 
//  into a wsQueryWindow).
//
//	This class exists primarily to implement the event handlers for interesting
//	events (like keystrokes, result sets, and debugger messages)
//		
////////////////////////////////////////////////////////////////////////////////

#ifndef WSQUERYWINDOWH
#define WSQUERYWINDOWH

#include <wx/grid.h>
#include <wx/laywin.h>

#include "wsrichwindow.h"
#include "wspgconn.h"
#include "wsdbresult.h"
#include "wsresultgrid.h"

class wsQueryWindow : public wxSashLayoutWindow
{
    DECLARE_CLASS( wsQueryWindow )

 public:
    wsQueryWindow( wxWindow * parent, wxWindowID id, wsPgConn * conn );

    void doExecute( void );

 private:

    wsPgConn 			* m_conn;					// Connection to PostgreSQL server
	wxSashLayoutWindow  * m_gridHolder;
	wxSashLayoutWindow  * m_commandHolder;
	wsResultGrid 		* m_resultGrid;
	wsRichWindow        * m_command;

    void OnKeyEvent( wxKeyEvent & event );			// Intercept Ctrl-Enter, Ctrl-space, and Control-C 
    void OnClose( wxCloseEvent & event );			// Destroy window
    void OnExecute( wxCommandEvent & event );		// Handle the 'Execute' menu option
	void OnResultReady( wxCommandEvent & event );	// Handle an incoming result set
	void OnSpawnDebugger( wxCommandEvent & event );	// Handle an incoming debugger message
	void OnSashDrag( wxSashEvent & event );			// Recompute window layout

    DECLARE_EVENT_TABLE()

};

#endif // WSQUERYWINDOWH