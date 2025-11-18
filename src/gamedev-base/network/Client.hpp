//
// Created by robin on 08.11.24.
//

#ifndef GALDER_GAME_JAM_2024_PROJECT_CLIENT_HPP
#define GALDER_GAME_JAM_2024_PROJECT_CLIENT_HPP

#include "../interfaces/system/ILogger.h"
#include "../interfaces/network/IIpAddressResolver.h"
#include "../interfaces/network/IClient.h"
#include "fmt/format.h"
#include "StringTrim.hpp"

#include <steam/steamnetworkingsockets.h>
#include <steam/isteamnetworkingutils.h>
#ifndef STEAMNETWORKINGSOCKETS_OPENSOURCE
#include <steam/steam_api.h>
#endif

#include <chrono>
#include <thread>
#include <mutex>
#include <map>
#include <queue>

namespace ggj
{
    template <class TClientData, class TServerData>
    class Client : public IClient<TClientData, TServerData>
    {
        public:
            Client(ILogger &logger, IIpAddressResolver &ipAddressResolver) : m_logger {logger}, m_resolver {ipAddressResolver}
            {
            
            }
            bool initialize() override;
            void connect(uint16_t port, std::string ipAddress) override;
            [[nodiscard]] ServerHostInfo getServerInfo() const override;
            void ping() const override;
            void disconnect() const override;
            
            virtual void onSteamNetConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t *pInfo);
        
        protected:
            bool m_quit = false;
            ILogger &m_logger;
            IIpAddressResolver &m_resolver;
            
            bool send(const TClientData &data) override;
            TServerData receive() override;
            void clientProgram() override
            {
                pollIncomingMessages();
                pollConnectionStateChanges();
                pollLocalUserInput();
                std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
            }
            
            void pollIncomingMessages();
            void pollConnectionStateChanges();
            void pollLocalUserInput();
            bool localUserInputGetNext(std::string &result);
            
            //private:
            
            //Steam network stuff
            ISteamNetworkingSockets *m_netInterface;
            HSteamNetConnection m_connection;
            std::mutex m_mutexUserInputQueue;
            std::queue< std::string > m_queueUserInput;
            //std::thread *m_threadUserInput = nullptr;
        
        
    };
    
    template<class TClientData, class TServerData>
    static Client<TClientData, TServerData> *clientCallbackInstance;
    
    template<class TClientData, class TServerData>
    static void SteamClientNetConnectionStatusChangedCallback( SteamNetConnectionStatusChangedCallback_t *pInfo )
    {
        clientCallbackInstance<TClientData, TServerData>->onSteamNetConnectionStatusChanged(pInfo);
    }
    
    template<class TClientData, class TServerData>
    void Client<TClientData, TServerData>::connect(uint16_t port, std::string ipAddress)
    {
        // Select instance to use.  For now we'll always use the default.
        m_netInterface = SteamNetworkingSockets();
        
        SteamNetworkingIPAddr serverAddr {};
        std::string addr = fmt::format("{0}:{1}", ipAddress, port);
        serverAddr.ParseString(addr.c_str());
        
        // Start connecting
        char szAddr[ SteamNetworkingIPAddr::k_cchMaxString ];
        serverAddr.ToString( szAddr, sizeof(szAddr), true );
        m_logger.information(fmt::format("Connecting to chat server at {0}", szAddr));
        SteamNetworkingConfigValue_t opt;
        opt.SetPtr( k_ESteamNetworkingConfig_Callback_ConnectionStatusChanged, (void*)SteamClientNetConnectionStatusChangedCallback<TClientData, TServerData> );
        m_connection = m_netInterface->ConnectByIPAddress( serverAddr, 1, &opt );
        if ( m_connection == k_HSteamNetConnection_Invalid )
            m_logger.critical(fmt::format("Failed to create connection"));
        
        while ( !m_quit )
        {
            clientProgram();
        }
    }
    
    template<class TClientData, class TServerData>
    ServerHostInfo Client<TClientData, TServerData>::getServerInfo() const
    {
        return {};
    }
    
    template<class TClientData, class TServerData>
    void Client<TClientData, TServerData>::ping() const
    {
    
    }
    
    template<class TClientData, class TServerData>
    void Client<TClientData, TServerData>::disconnect() const
    {
    
    }
    
    template<class TClientData, class TServerData>
    void Client<TClientData, TServerData>::onSteamNetConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t *pInfo)
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
                break;
            
            default:
                // Silences -Wswitch
                break;
        }
    }
    
    template<class TClientData, class TServerData>
    void Client<TClientData, TServerData>::pollIncomingMessages()
    {
        while (!m_quit)
        {
            ISteamNetworkingMessage *incomingMsg = nullptr;
            int numMsgs = m_netInterface->ReceiveMessagesOnConnection(m_connection, &incomingMsg, 1 );
            if ( numMsgs == 0 )
                break;
            if ( numMsgs < 0 )
                m_logger.critical(fmt::format("Error checking for messages"));
            
            // Just echo anything we get from the server
            fwrite(incomingMsg->m_pData, 1, incomingMsg->m_cbSize, stdout );
            fputc( '\n', stdout );
            
            // We don't need this anymore.
            incomingMsg->Release();
        }
    }
    
    template<class TClientData, class TServerData>
    void Client<TClientData, TServerData>::pollConnectionStateChanges()
    {
        clientCallbackInstance<TClientData, TServerData> = this;
        m_netInterface->RunCallbacks();
    }
    
    template<class TClientData, class TServerData>
    void Client<TClientData, TServerData>::pollLocalUserInput()
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
            m_netInterface->SendMessageToConnection( m_connection, cmd.c_str(), (uint32)cmd.length(),
                                                     k_nSteamNetworkingSend_Reliable, nullptr );
        }
    }
    
    template<class TClientData, class TServerData>
    bool Client<TClientData, TServerData>::localUserInputGetNext(std::string &result)
    {
        bool got_input = false;
        m_mutexUserInputQueue.lock();
        while ( !m_queueUserInput.empty() && !got_input )
        {
            result = m_queueUserInput.front();
            m_queueUserInput.pop();
            ltrim(result);
            rtrim(result);
            got_input = !result.empty(); // ignore blank lines
        }
        m_mutexUserInputQueue.unlock();
        return got_input;
    }
    
    template<class TClientData, class TServerData>
    bool Client<TClientData, TServerData>::initialize()
    {
        SteamDatagramErrMsg errMsg;
        if (!GameNetworkingSockets_Init( nullptr, errMsg ))
        {
            m_logger.critical(fmt::format("GameNetworkingSockets_Init failed.  {0}", errMsg));
            return false;
        }
        return true;
    }
    
    template<class TClientData, class TServerData>
    bool Client<TClientData, TServerData>::send(const TClientData &data)
    {
        EResult result = m_netInterface->SendMessageToConnection( m_connection, &data, sizeof(data),
                                                                  k_nSteamNetworkingSend_Reliable, nullptr );
        return result == k_EResultOK;
    }
    template<class TClientData, class TServerData>
    TServerData Client<TClientData, TServerData>::receive()
    {
        static TServerData defaultValue {};
        ISteamNetworkingMessage *incomingMsg = nullptr;
        int numMsgs = m_netInterface->ReceiveMessagesOnConnection(m_connection, &incomingMsg, 1 );
        if ( numMsgs == 0 || incomingMsg == nullptr )
            return defaultValue;
        
        TServerData* dataPtr = static_cast<TServerData*>(incomingMsg->m_pData);
        TServerData data = *dataPtr;
        
        incomingMsg->Release();
        
        return data;
    }
    
} // ggj

#endif //GALDER_GAME_JAM_2024_PROJECT_CLIENT_HPP
