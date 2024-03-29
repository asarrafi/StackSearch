/*
Copyright (C) 2011 MoSync AB

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.
*/

/**
 * @file StackSearch.cpp
 * @author Ali Sarrafi
 *
 * Application that provides basic search functionality for
 * stackoverflow questions.
 *
 * The entire UI and most of the application logic is implemented
 * in JavaScript.
 */

#include <Wormhole/WebAppMoblet.h>	// Moblet for web applications.
#include "MessageHandler.h"

using namespace MAUtil;
using namespace NativeUI;
using namespace Wormhole;

/**
 * The application class.
 */
class StackOverflowMoblet : public WebAppMoblet
{
private:
	/**
	 * Object that handles messages from JavaScript.
	 */
	MessageHandler mMessageHandler;

public:
	StackOverflowMoblet()
	{
		enableWebViewMessages();
		getWebView()->disableZoom();
		showPage("index.html");
	}

	/**
	 * This method handles messages sent from the WebView.
	 * @param webView The WebView that sent the message.
	 * @param urlData Data object that holds message content.
	 * Note that the data object will be valid only during
	 * the life-time of the call of this method, then it
	 * will be deallocated.
	 */
	void handleWebViewMessage(WebView* webView, MAHandle urlData)
	{
		// Create message object. This parses the message.
		WebViewMessage message(webView, urlData);

		// Let the message handler handle the message.
		mMessageHandler.handleMessage(message);

		// Tell the WebView that we have processed the message, so that
		// it can send the next one.
		callJS("bridge.messagehandler.processedMessage()");
	}

	/**
	 * This method is called when a key is pressed. It closes
	 * the application when the back key (on Android) is pressed.
	 * Override to implement your own behavior.
	 */
	void keyPressEvent(int keyCode, int nativeCode)
	{
		if (MAK_BACK == keyCode)
		{
			// forward the event to application
			callJS("handleBackKey()");
		}
	}

};
// End of class StackOverflowMoblet

/**
 * Main function that is called when the program starts.
 */
extern "C" int MAMain()
{
	Moblet::run(new StackOverflowMoblet());
	return 0;
}
