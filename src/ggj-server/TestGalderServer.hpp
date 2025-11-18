//
// Created by robin on 10.11.24.
//

#ifndef GALDER_GAME_JAM_2024_PROJECT_TESTGALDERSERVER_HPP
#define GALDER_GAME_JAM_2024_PROJECT_TESTGALDERSERVER_HPP

namespace ggj
{
    
    class TestGalderServer : public ggj::Server<TestServerData, TestClientData>
    {
        public:
            TestGalderServer(ILogger &logger, IIpAddressResolver &ipAddressResolver) :
                    ggj::Server<TestServerData, TestClientData>(logger, ipAddressResolver)
            {
            
            }
            
            void onSteamNetConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t *pInfo) override
            {
                char temp[1024];
                
                // What's the state of the connection?
                switch ( pInfo->m_info.m_eState )
                {
                    case k_ESteamNetworkingConnectionState_None:
                        // NOTE: We will get callbacks here when we destroy connections.  You can ignore these.
                        break;
                    
                    case k_ESteamNetworkingConnectionState_ClosedByPeer:
                    case k_ESteamNetworkingConnectionState_ProblemDetectedLocally:
                    {
                        // Ignore if they were not previously connected.  (If they disconnected
                        // before we accepted the connection.)
                        if ( pInfo->m_eOldState == k_ESteamNetworkingConnectionState_Connected )
                        {
                            
                            // Locate the client.  Note that it should have been found, because this
                            // is the only codepath where we remove clients (except on shutdown),
                            // and connection change callbacks are dispatched in queue order.
                            auto itClient = m_mapClients.find( pInfo->m_hConn );
                            //assert( itClient != m_mapClients.end() );
                            
                            // Select appropriate log messages
                            const char *pszDebugLogAction;
                            if ( pInfo->m_info.m_eState == k_ESteamNetworkingConnectionState_ProblemDetectedLocally )
                            {
                                pszDebugLogAction = "problem detected locally";
                                sprintf( temp, "Alas, %s hath fallen into shadow.  (%s)", itClient->second.nick.c_str(),
                                         pInfo->m_info.m_szEndDebug );
                            }
                            else
                            {
                                // Note that here we could check the reason code to see if
                                // it was a "usual" connection or an "unusual" one.
                                pszDebugLogAction = "closed by peer";
                                sprintf( temp, "%s hath departed", itClient->second.nick.c_str() );
                            }
                            
                            // Spew something to our own log.  Note that because we put their nick
                            // as the connection description, it will show up, along with their
                            // transport-specific data (e.g. their IP address)
                            m_logger.information(fmt::format("Connection {0} {1}, reason {2}: {3}\n",
                                                             pInfo->m_info.m_szConnectionDescription,
                                                             pszDebugLogAction,
                                                             pInfo->m_info.m_eEndReason,
                                                             pInfo->m_info.m_szEndDebug
                            ));
                            
                            m_mapClients.erase( itClient );
                            
                            // Send a message so everybody else knows what happened
                            //sendStringToAllClients( temp );
                        }
                        else
                        {
                            //assert( pInfo->m_eOldState == k_ESteamNetworkingConnectionState_Connecting );
                        }
                        
                        // Clean up the connection.  This is important!
                        // The connection is "closed" in the network sense, but
                        // it has not been destroyed.  We must close it on our end, too
                        // to finish up.  The reason information do not matter in this case,
                        // and we cannot linger because it's already closed on the other end,
                        // so we just pass 0's.
                        m_netInterface->CloseConnection( pInfo->m_hConn, 0, nullptr, false );
                        break;
                    }
                    
                    case k_ESteamNetworkingConnectionState_Connecting:
                    {
                        // This must be a new connection
                        //assert( m_mapClients.find( pInfo->m_hConn ) == m_mapClients.end() );
                        
                        m_logger.information(fmt::format("Connection request from {0}", pInfo->m_info.m_szConnectionDescription));
                        
                        // A client is attempting to connect
                        // Try to accept the connection.
                        if ( m_netInterface->AcceptConnection( pInfo->m_hConn ) != k_EResultOK )
                        {
                            // This could fail.  If the remote host tried to connect, but then
                            // disconnected, the connection may already be half closed.  Just
                            // destroy whatever we have on our side.
                            m_netInterface->CloseConnection( pInfo->m_hConn, 0, nullptr, false );
                            m_logger.information(fmt::format("Can't accept connection.  (It was already closed?)"));
                            break;
                        }
                        
                        // Assign the poll group
                        if ( !m_netInterface->SetConnectionPollGroup( pInfo->m_hConn, m_pollGroup ) )
                        {
                            m_netInterface->CloseConnection( pInfo->m_hConn, 0, nullptr, false );
                            m_logger.information(fmt::format("Failed to set poll group?"));
                            break;
                        }
                        
                        // Generate a random nick.  A random temporary nick
                        // is really dumb and not how you would write a real chat server.
                        // You would want them to have some sort of signon message,
                        // and you would keep their client in a state of limbo (connected,
                        // but not logged on) until them.  I'm trying to keep this example
                        // code really simple.
                        char nick[ 64 ];
                        sprintf( nick, "GalderLover%d", 10000 + ( rand() % 100000 ) );
                        
                        // Send them a welcome message
                        std::string helloMsg = fmt::format("Welcome to {0}, stranger.  I don't care about your name, so I'll just call you '{1}'.", m_info.getName(), nick);
                        //sendStringToClient( pInfo->m_hConn, helloMsg.c_str() );
                        TestServerData helloData = {false, 1000, ""};
                        helloData.message = stringToMessage(helloMsg);
                        send(pInfo->m_hConn, helloData); //helloMsg});
                        
                        // Also send them a list of everybody who is already connected
                        if ( m_mapClients.empty() )
                        {
                            send(pInfo->m_hConn, {false, 2000, "Seems like you have no friends. Sadface :("});
                        }
                        else
                        {
                            sprintf( temp, "%d companions greet you:", (int)m_mapClients.size() );
                            for ( auto &c: m_mapClients )
                            {
                                TestServerData data = {false, 3000, ""};
                                //strcpy(data.message, c.second.nick.c_str());
                                helloData.message = stringToMessage(c.second.nick);
                                send(pInfo->m_hConn, data);
                            }
                            //sendStringToClient( pInfo->m_hConn, c.second.nick.c_str() );
                        }
                        
                        // Let everybody else know who they are for now
                        sprintf( temp, "Hark!  A stranger hath joined this merry host.  For now we shall call them '%s'", nick );
                        //sendStringToAllClients( temp, pInfo->m_hConn );
                        
                        // Add them to the client list, using std::map wacky syntax
                        m_mapClients[ pInfo->m_hConn ];
                        setClientNick( pInfo->m_hConn, nick );
                        break;
                    }
                    
                    case k_ESteamNetworkingConnectionState_Connected:
                        // We will get a callback immediately after accepting the connection.
                        // Since we are the server, we can ignore this, it's not news to us.
                        break;
                    
                    default:
                        // Silences -Wswitch
                        break;
                }
            }
        
        protected:
            
            std::array<char, 256> stringToMessage(const std::string &str)
            {
                std::array<char, 256> result = {};  // Initialize to zero for safety
                
                // Copy up to 20 characters from source, leaving space for null terminator
                std::size_t lengthToCopy = std::min(str.size(), result.size() - 1);
                std::copy_n(str.begin(), lengthToCopy, result.begin());
                
                // Ensure null-termination
                result[lengthToCopy] = '\0';
                return result;
            }
            
            void serverProgram() override
            {
                pollSpecialClientMessages();
                //pollIncomingMessages();
                pollConnectionStateChanges();
                pollLocalUserInput();
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            
            void pollSpecialClientMessages()
            {
                char temp[ 1024 ];
                
                while ( !m_quit )
                {
                    ISteamNetworkingMessage *incomingMsg = nullptr;
                    int numMsgs = m_netInterface->ReceiveMessagesOnPollGroup(m_pollGroup, &incomingMsg, 1 );
                    if ( numMsgs == 0 )
                        break;
                    if ( numMsgs < 0 )
                        m_logger.error(fmt::format("Error checking for messages"));
                    //assert( numMsgs == 1 && pIncomingMsg );
                    auto itClient = m_mapClients.find(incomingMsg->m_conn );
                    //assert( itClient != m_mapClients.end() );
                    
                    // '\0'-terminate it to make it easier to parse
                    TestClientData *dataPtr = (TestClientData*)incomingMsg->m_pData;
                    TestClientData data = (dataPtr != nullptr) ? *dataPtr : TestClientData();
                    
                    // We don't need this anymore.
                    incomingMsg->Release();
                    
                    // Check for known commands.  None of this example code is secure or robust.
                    // Don't write a real server like this, please.
                    
                    if ( data.isValid )
                    {
                        std::string playerInfo = fmt::format("Got some player info, yo! \n"
                                                             "Position: X: {0}, Y: {1} \n"
                                                             "Action: {2}\nFrame: {3}\nState: {4}\n",
                                                             data.position.x, data.position.y, data.action, data.animationFrame, data.animationState);
                        
                        std::string messageToClient = fmt::format("Hello there, {0}! I got your message! And I know where you are ({1}, {2})\n", data.nickname.data(), data.position.x, data.position.y);
                        
                        
                        m_logger.information(playerInfo);
                        TestServerData msg
                                {
                                        false,
                                        4000,
                                        stringToMessage(messageToClient),
                                        data.color
                                };
                        
                        if(!send(itClient->first, msg))
                        {
                            m_logger.error("Well, fuck! Couldn't send the message to client :(");
                        }
//                        // Let everybody else know they changed their name
//                        sprintf( temp, "%s shall henceforth be known as %s", itClient->second.nick.c_str(), nick );
//                        sendStringToAllClients( temp, itClient->first );
//
//                        // Respond to client
//                        sprintf( temp, "Ye shall henceforth be known as %s", nick );
//                        sendStringToClient( itClient->first, temp );
//
//                        // Actually change their name
//                        setClientNick( itClient->first, nick );
                        continue;
                    }
                    
                    // Assume it's just a ordinary chat message, dispatch to everybody else
//                    sprintf( temp, "%s: %s", itClient->second.nick.c_str(), cmd );
//                    sendStringToAllClients( temp, itClient->first );
                }
            }
        
    };
    
} // ggj



#endif //GALDER_GAME_JAM_2024_PROJECT_TESTGALDERSERVER_HPP
