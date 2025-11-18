//
// Created by robin on 10.11.24.
//

#ifndef GALDER_GAME_JAM_2024_PROJECT_TESTGALDERCLIENT_HPP
#define GALDER_GAME_JAM_2024_PROJECT_TESTGALDERCLIENT_HPP

namespace ggj
{
    
    class TestGalderClient : public ggj::Client<TestClientData, TestServerData>
    {
        public:
            TestGalderClient(ILogger &logger, IIpAddressResolver &ipAddressResolver) :
                    ggj::Client<TestClientData, TestServerData>(logger, ipAddressResolver)
            {
            
            }
        
        protected:
            void clientProgram() override
            {
                //pollIncomingMessages();
                pollSpecialServerMessages();
                pollConnectionStateChanges();
                pollSpecialUserInput();
                std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
            }
            
            void sendMessageToServerNowAndThen()
            {
                if(m_messageSendCounter >= m_messageSendTrigger)
                {
                    m_messageSendCounter = 0;
                    sendMessageToServer();
                }
                ++m_messageSendCounter;
            }
            
            void sendMessageToServer()
            {
//                TestClientData data
//                        {
//                                true,
//                                raylib::Vector2(1337, 1337),
//                                1,
//                                2,
//                                3
//                        };
                
                while (!m_queue.empty()) {
                    if(!send(m_queue.front()))
                        m_logger.error("Tried to send message to server, but it went to hell!");
                    else
                    {
                        m_logger.information("Message sent to server!");
                        m_queue.pop();  // Remove the processed message
                    }
                }
                
            }
            
            void pollSpecialServerMessages()
            {
                while (!m_quit)
                {
                    TestServerData data = receive();
                    if(!data.isInvalid)
                    {
                        m_logger.warning(fmt::format("Server msg: {0} - {1}", data.id, data.message.data()));
                    }
                    else
                        break;
                }
            }
            
            void pollSpecialUserInput()
            {
                std::string cmd;
                while ( !m_quit && localUserInputGetNext( cmd ))
                {
                    
                    // Check for known commands
                    if ( strcmp( cmd.c_str(), "/quit" ) == 0 )
                    {
                        m_quit = true;
                        m_logger.information(fmt::format("Disconnecting from chat server"));
                        
                        // Close the connection gracefully.
                        // We use linger mode to ask for any remaining reliable data
                        // to be flushed out.  But remember this is an application
                        // protocol on UDP.  See ShutdownSteamDatagramConnectionSockets
                        m_netInterface->CloseConnection( m_connection, 0, "Goodbye", true );
                        break;
                    }
                    
                    // Anything else, just send it to the server and let them parse it
                    sendMessageToServer();
//                    m_netInterface->SendMessageToConnection( m_connection, cmd.c_str(), (uint32)cmd.length(),
//                                                             k_nSteamNetworkingSend_Reliable, nullptr );
                }
            }
        
        public:
            void onSteamNetConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t *pInfo) override
            {
                //assert( pInfo->m_hConn == m_connection || m_connection == k_HSteamNetConnection_Invalid );
                
                // What's the state of the connection?
                switch ( pInfo->m_info.m_eState )
                {
                    case k_ESteamNetworkingConnectionState_None:
                        // NOTE: We will get callbacks here when we destroy connections.  You can ignore these.
                        break;
                    
                    case k_ESteamNetworkingConnectionState_ClosedByPeer:
                    case k_ESteamNetworkingConnectionState_ProblemDetectedLocally:
                    {
                        m_quit = true;
                        
                        // Print an appropriate message
                        if ( pInfo->m_eOldState == k_ESteamNetworkingConnectionState_Connecting )
                        {
                            // Note: we could distinguish between a timeout, a rejected connection,
                            // or some other transport problem.
                            m_logger.information(fmt::format( "We sought the remote host, yet our efforts were met with defeat.  ({0})", pInfo->m_info.m_szEndDebug ));
                        }
                        else if ( pInfo->m_info.m_eState == k_ESteamNetworkingConnectionState_ProblemDetectedLocally )
                        {
                            m_logger.information(fmt::format( "Alas, troubles beset us; we have lost contact with the host.  ({0})", pInfo->m_info.m_szEndDebug ));
                        }
                        else
                        {
                            // NOTE: We could check the reason code for a normal disconnection
                            m_logger.information(fmt::format( "The host hath bidden us farewell.  ({0})", pInfo->m_info.m_szEndDebug ));
                        }
                        
                        // Clean up the connection.  This is important!
                        // The connection is "closed" in the network sense, but
                        // it has not been destroyed.  We must close it on our end, too
                        // to finish up.  The reason information do not matter in this case,
                        // and we cannot linger because it's already closed on the other end,
                        // so we just pass 0's.
                        m_netInterface->CloseConnection( pInfo->m_hConn, 0, nullptr, false );
                        m_connection = k_HSteamNetConnection_Invalid;
                        break;
                    }
                    
                    case k_ESteamNetworkingConnectionState_Connecting:
                        // We will get this callback when we start connecting.
                        // We can ignore this.
                        break;
                    
                    case k_ESteamNetworkingConnectionState_Connected:
                        m_logger.information(fmt::format( "Connected to server OK" ));
                        sendMessageToServer();
                        break;
                    
                    default:
                        // Silences -Wswitch
                        break;
                }
            }
        
        private:
            uint32_t m_messageSendCounter {0};
            uint32_t m_messageSendTrigger {100};
    };
    
} // ggj

#endif //GALDER_GAME_JAM_2024_PROJECT_TESTGALDERCLIENT_HPP
