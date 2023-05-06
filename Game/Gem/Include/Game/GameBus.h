
#pragma once

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace Game
{
    class GameRequests
    {
    public:
        AZ_RTTI(GameRequests, "{0E7EE778-2665-4F37-9073-02ED8FF9ADB7}");
        virtual ~GameRequests() = default;
        // Put your public methods here
    };

    class GameBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using GameRequestBus = AZ::EBus<GameRequests, GameBusTraits>;
    using GameInterface = AZ::Interface<GameRequests>;

} // namespace Game
