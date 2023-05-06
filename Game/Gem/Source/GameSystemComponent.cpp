
#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/EditContextConstants.inl>

#include "GameSystemComponent.h"

namespace Game
{
    void GameSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<GameSystemComponent, AZ::Component>()
                ->Version(0)
                ;

            if (AZ::EditContext* ec = serialize->GetEditContext())
            {
                ec->Class<GameSystemComponent>("Game", "[Description of functionality provided by this System Component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ;
            }
        }
    }

    void GameSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC("GameService"));
    }

    void GameSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC("GameService"));
    }

    void GameSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void GameSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    GameSystemComponent::GameSystemComponent()
    {
        if (GameInterface::Get() == nullptr)
        {
            GameInterface::Register(this);
        }
    }

    GameSystemComponent::~GameSystemComponent()
    {
        if (GameInterface::Get() == this)
        {
            GameInterface::Unregister(this);
        }
    }

    void GameSystemComponent::Init()
    {
    }

    void GameSystemComponent::Activate()
    {
        GameRequestBus::Handler::BusConnect();
    }

    void GameSystemComponent::Deactivate()
    {
        GameRequestBus::Handler::BusDisconnect();
    }
}
