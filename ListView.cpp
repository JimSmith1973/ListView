// ListView.cpp

#include "ListView.h"

// Global variables
ListViewWindow g_listViewWindow;
StatusBarWindow g_statusBarWindow;

void ListViewWindowSelectionChangedFunction( LPTSTR lpszItemText )
{
	// Show item text on status bat window
	g_statusBarWindow.SetText( lpszItemText );

} // End of function ListViewWindowSelectionChangedFunction

void ListViewWindowDoubleClickFunction( LPTSTR lpszItemText )
{
	// Display item text
	MessageBox( NULL, lpszItemText, INFORMATION_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );

} // End of function ListViewWindowDoubleClickFunction

int CALLBACK ListViewWindowCompare( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort )
{
	int nResult = 0;

	// Allocate string memory
	LPTSTR lpszItemText1 = new char[ STRING_LENGTH + sizeof( char ) ];
	LPTSTR lpszItemText2 = new char[ STRING_LENGTH + sizeof( char ) ];

	// Get first item text
	g_listViewWindow.GetItemText( lParam1, lParamSort, lpszItemText1 );

	// Get second item text
	g_listViewWindow.GetItemText( lParam2, lParamSort, lpszItemText2 );

	// Compare item texts
	nResult = lstrcmpi( lpszItemText1, lpszItemText2 );

	// Free string memory
	delete [] lpszItemText1;
	delete [] lpszItemText2;

	return nResult;

} // End of function ListViewWindowCompare

void OpenFileFunction( LPCTSTR lpszFilePath )
{
	// Add file to list box window
	g_listViewWindow.AddItem( lpszFilePath );

} // End of function OpenFileFunction

int ShowAboutMessage( HWND hWndParent )
{
	int nResult = 0;

	MSGBOXPARAMS mbp;

	// Clear message box parameter structure
	ZeroMemory( &mbp, sizeof( mbp ) );

	// Initialise message box parameter structure
	mbp.cbSize		= sizeof( MSGBOXPARAMS );
	mbp.hwndOwner	= hWndParent;
	mbp.hInstance	= NULL;
	mbp.lpszText	= ABOUT_MESSAGE_TEXT;
	mbp.lpszCaption	= ABOUT_MESSAGE_CAPTION;
	mbp.dwStyle		= ( MB_OK | MB_USERICON );
	mbp.lpszIcon	= WINDOW_CLASS_CLASS_DEFAULT_ICON_NAME;

	// Show message box
	nResult = MessageBoxIndirect( &mbp );

	return nResult;

} // End of function ShowAboutMessage

LRESULT CALLBACK MainWindowProcedure( HWND hWndMain, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	LRESULT lr = 0;

	// Select message
	switch( uMessage )
	{
		case WM_CREATE:
		{
			// A create message
			HINSTANCE hInstance;

			// Get instance
			hInstance = ( ( LPCREATESTRUCT )lParam )->hInstance;

			// Create list box window
			if( g_listViewWindow.Create( hWndMain, hInstance ) )
			{
				// Successfully created list box window
				Font font;

				// Get font
				font = DEFAULT_GUI_FONT;

				// Set list box window font
				g_listViewWindow.SetFont( font );

				// Create status bar window
				if( g_statusBarWindow.Create( hWndMain, hInstance ) )
				{
					// Successfully created status bar window

					// Set status bar window font
					g_statusBarWindow.SetFont( font );

				} // End of successfully created status bar window

			} // End of successfully created list box window

			// Break out of switch
			break;

		} // End of a create message
		case WM_SIZE:
		{
			// A size message
			int nClientWidth;
			int nClientHeight;
			RECT rcStatus;
			int nStatusWindowHeight;
			int nListViewWindowHeight;

			// Store client width and height
			nClientWidth	= ( int )LOWORD( lParam );
			nClientHeight	= ( int )HIWORD( lParam );

			// Size status bar window
			g_statusBarWindow.Size();

			// Get status window size
			g_statusBarWindow.GetWindowRect( &rcStatus );

			// Calculate window sizes
			nStatusWindowHeight		= ( rcStatus.bottom - rcStatus.top );
			nListViewWindowHeight	= ( nClientHeight - nStatusWindowHeight );

			// Move list box window
			g_listViewWindow.Move( 0, 0, nClientWidth, nListViewWindowHeight, TRUE );

			// Break out of switch
			break;

		} // End of a size message
		case WM_ACTIVATE:
		{
			// An activate message

			// Focus on list box window
			g_listViewWindow.SetFocus();

			// Break out of switch
			break;

		} // End of an activate message
		case WM_GETMINMAXINFO:
		{
			// A get min max info message
			MINMAXINFO FAR *lpMinMaxInfo;

			// Get min max info structure
			lpMinMaxInfo = ( MINMAXINFO FAR * )lParam;

			// Update min max info structure
			lpMinMaxInfo->ptMinTrackSize.x = WINDOW_CLASS_DEFAULT_MINIMUM_WIDTH;
			lpMinMaxInfo->ptMinTrackSize.y = WINDOW_CLASS_DEFAULT_MINIMUM_HEIGHT;

			// Break out of switch
			break;

		} // End of a get min max info message
		case WM_DROPFILES:
		{
			// A drop files message
			DroppedFiles droppedFiles;

			// Get dropped files
			if( droppedFiles.Get( wParam ) )
			{
				// Successfully got dropped files

				// Process dropped files
				droppedFiles.Process( &OpenFileFunction );

			} // End of successfully got dropped files

			// Break out of switch
			break;

		} // End of a drop files message
		case WM_COMMAND:
		{
			// A command message

			// Select command
			switch( LOWORD( wParam ) )
			{
				case IDM_FILE_EXIT:
				{
					// A file exit command

					// Destroy window
					DestroyWindow( hWndMain );

					// Break out of switch
					break;

				} // End of a file exit command
				case IDM_HELP_ABOUT:
				{
					// A help about command

					// Show about message
					ShowAboutMessage( hWndMain );

					// Break out of switch
					break;

				} // End of a help about command
				default:
				{
					// Default command

					// Call default procedure
					lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

					// Break out of switch
					break;

				} // End of default command

			}; // End of selection for command

			// Break out of switch
			break;

		} // End of a command message
		case WM_SYSCOMMAND:
		{
			// A system command message

			// Select system command
			switch( LOWORD( wParam ) )
			{
				case IDM_HELP_ABOUT:
				{
					// A help about system command

					// Show about message
					ShowAboutMessage( hWndMain );

					// Break out of switch
					break;

				} // End of a help about system command
				default:
				{
					// Default system command

					// Call default procedure
					lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

					// Break out of switch
					break;

				} // End of default system command

			}; // End of selection for system command

			// Break out of switch
			break;

		} // End of a system command message
		case WM_NOTIFY:
		{
			// A notify message
			LPNMHDR lpNmHdr;

			// Get notify message handler
			lpNmHdr = ( LPNMHDR )lParam;

			// See if notify message is from list view window
			if( lpNmHdr->hwndFrom == g_listViewWindow )
			{
				// Notify message is from list view window

				// Handle notify message from list view window
				if( !( g_listViewWindow.HandleNotifyMessage( wParam, lParam, &ListViewWindowSelectionChangedFunction, &ListViewWindowDoubleClickFunction, &ListViewWindowCompare ) ) )
				{
					// Notify message was not handled from list view window

					// Call default handler
					lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

				} // End of notify message was not handled from list view window

			} // End of notify message is from list view window
			else
			{
				// Notify message is not from list view window

				// Call default handler
				lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

			} // End of notify message is not from list view window

			// Break out of switch
			break;

		} // End of a notify message
		case WM_CONTEXTMENU:
		{
			// A context menu message
			Menu popupMenu;

			// Load popup menu
			popupMenu.Load( MAKEINTRESOURCE( IDR_CONTEXT_MENU ) );

			// Show popup menu
			popupMenu.TrackPopupMenu( 0, lParam, hWndMain );

			// Break out of switch
			break;

		} // End of a context menu message
		case WM_CLOSE:
		{
			// A close message

			// Destroy main window
			DestroyWindow( hWndMain );

			// Break out of switch
			break;

		} // End of a close message
		case WM_DESTROY:
		{
			// A destroy message

			// Terminate thread
			PostQuitMessage( 0 );

			// Break out of switch
			break;

		} // End of a destroy message
		default:
		{
			// Default message

			// Call default window procedure
			lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

			// Break out of switch
			break;

		} // End of default message

	}; // End of selection for message

	return lr;

} // End of function MainWindowProcedure

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow )
{
	Message message;

	WindowClass mainWindowClass;

	// Initialise main window class
	mainWindowClass.Initialise( MAIN_WINDOW_CLASS_NAME, hInstance, MainWindowProcedure, MAIN_WINDOW_CLASS_MENU_NAME );

	// Register main window class
	if( mainWindowClass.Register() )
	{
		// Successfully registered main window class
		Window mainWindow;

		// Create main window
		if( mainWindow.Create( MAIN_WINDOW_CLASS_NAME, NULL, hInstance, MAIN_WINDOW_TEXT ) )
		{
			// Successfully created main window
			Menu systemMenu;
			ArgumentList argumentList;

			// Get system menu
			systemMenu.GetSystem( mainWindow );

			// Add separator item to system menu
			systemMenu.InsertSeparator( MENU_CLASS_SYSTEM_MENU_SEPARATOR_ITEM_POSITION );

			// Add about item to system menu
			systemMenu.InsertItem( MENU_CLASS_SYSTEM_MENU_ABOUT_ITEM_POSITION, IDM_HELP_ABOUT, MENU_CLASS_SYSTEM_MENU_ABOUT_ITEM_TEXT );

			// Get argument list
			if( argumentList.Get() )
			{
				// Successfully got argument list

				// Process arguments
				argumentList.ProcessArguments( &OpenFileFunction );

			} // End of successfully got argument list

			// Show main window
			mainWindow.Show( nCmdShow );

			// Update main window
			mainWindow.Update();

			// Add columns to list view window
			g_listViewWindow.AddColumn( "Column 1" );
			g_listViewWindow.AddColumn( "Column 2" );
			g_listViewWindow.AddColumn( "Column 3" );

			// Add items to list view window
			g_listViewWindow.AddItem( "Item 1" );
			g_listViewWindow.AddItem( "Item 2" );
			g_listViewWindow.AddItem( "Item 3" );

			// Set item texts on list view window
			g_listViewWindow.SetItemText( 1, 1, "Item 2, Column 2" );
			g_listViewWindow.SetItemText( 0, 2, "Item 1, Column 3" );
			g_listViewWindow.SetItemText( 2, 2, "Item 3, Column 3" );

			// Auto-size all list view window columns
			g_listViewWindow.AutoSizeAllColumns();

			// Message loop
			while( message.Get() > 0 )
			{
				// Translate message
				message.Translate();

				// Dispatch message
				message.Dispatch();

			}; // End of message loop

		} // End of successfully created main window
		else
		{
			// Unable to create main window

			// Display error message
			MessageBox( NULL, WINDOW_CLASS_UNABLE_TO_CREATE_WINDOW_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

		} // End of unable to create main window

	} // End of successfully registered main window class
	else
	{
		// Unable to register main window class

		// Display error message
		MessageBox( NULL, WINDOW_CLASS_CLASS_UNABLE_TO_REGISTER_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

	} // End of unable to register main window class

	return message;

} // End of function WinMain