
#pragma once

#include <AzCore/Component/Component.h>

#include <Game/GameBus.h>

namespace Game
{
    class GameSystemComponent
        : public AZ::Component
        , protected GameRequestBus::Handler
    {
    public:
        AZ_COMPONENT(GameSystemComponent, "{D2137B28-9CF1-488E-85D4-945EBD4FEE37}");

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        GameSystemComponent();
        ~GameSystemComponent();

    protected:
        ////////////////////////////////////////////////////////////////////////
        // GameRequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////
    };
}
