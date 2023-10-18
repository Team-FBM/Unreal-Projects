// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Display, TEXT("Trigger Component alive"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (Mover == nullptr)
        return;
    AActor *Actor = GetAcceptableActor();
    if (Actor != nullptr)
    {
        UPrimitiveComponent *Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
        if (!Actor->ActorHasTag("Grabbed"))
        {
            if (Component != nullptr)
            {
                Component->SetSimulatePhysics(false);
            }
            Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
            Mover->SetShouldMove(true);
        }
        else
        {
            if (Component != nullptr)
            {
                Component->SetSimulatePhysics(true);
            }
            Actor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
            Mover->SetShouldMove(false);
        }
    }
    else
    {
        Mover->SetShouldMove(false);
    }
}

void UTriggerComponent::SetMover(UMover *NewMover)
{
    Mover = NewMover;
}

AActor *UTriggerComponent::GetAcceptableActor() const
{
    TArray<AActor *> Actors;
    GetOverlappingActors(Actors);
    for (auto i : Actors)
        if (i->ActorHasTag(AcceptableActorTag))
            return i;

    return nullptr;
}
