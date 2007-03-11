//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: wspgconn.h 5827 2007-01-04 16:35:14 hiroshi $
// Copyright (C) 2002 - 2007, The pgAdmin Development Team
// This software is released under the Artistic Licence
//
// wspgconn.h - debugger 
//
//////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// class wsPgConn
//
//	A wsPgConn object encapsulates the connection to a PostgreSQL server.  This
//  class is a wrapper around a Pgconn that provides a convenient constructor 
//  and a few member functions.  
//
//	This class doesn't do much - instead, the real work happens in a wsPgThread
//  (a separate thread) that initiates commands and processes result sets.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef WSPGCONNH
#define WSPGCONNH

#include <wx/string.h>
#include <wx/event.h>
#include <libpq-fe.h>

#include "wspgthread.h"
#include "wsconnprop.h"

class wsPgConn 
{
  public:

    wsPgConn( const wxString & server   = wxT( "" ), 
			  const wxString & database = wxT( "" ), 
			  const wxString & username = wxT( "" ), 
			  const wxString & password = wxT( "" ), 
			  const wxString & port     = wxT( "5432" ), 
			  int sslmode               = 0 );

	wsPgConn( const wsConnProp & props, bool startThread = true );

	~wsPgConn();

    bool  	 	    isConnected() const;	// Returns true if the connection attempt succeeded
    const wxString  getName() const;		// Returns human-friendly name for this connection
    const wxString  getHost() const;		// Returns the host-name (or IP address) for this connection
    const wxString  getDatabase() const;	// Returns the name of the database that we're connected to
    PGconn        * getConnection();		// Returns the libpq connection handle
	void	        close(); 				// Close this connection

    void  		startCommand( const wxString & command, wxEvtHandler * caller, wxEventType eventType = wxEVT_NULL );	// Starts executing a command	
    void  		setNoticeHandler( PQnoticeProcessor handler, void * arg );			// Registers a NOTICE handler
	PGresult  * waitForCommand( const wxString & command );							// Starts a command and waits for completion

  private:

	void Init( const wxString & server, const wxString & database, const wxString & userName, const wxString & password, const wxString & port, int sslmode, bool startThread );

    PGconn    * m_pgConn;				// libpq connection handler
    wsPgThread  * m_workerThread;		// Worker thread (this thread interacts with the server)
};

#endif // WSPGCONNH