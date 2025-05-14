// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/PawnUIInterface.h"

// Add default functionality here for any IPawnUIInterface functions that are not pure virtual.

UHeroPawnUIComponent* IPawnUIInterface::GetHeroUIComponent() const
{
    return nullptr;
}

UEnemyPawnUIComponent* IPawnUIInterface::GetEnemyUIComponent() const
{
    return nullptr;
}
