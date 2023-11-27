// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatNotifyState_HitWindow.h"

#include "CombatNotifyState_HitSphere.generated.h"

UCLASS()
class GASCOMBATHELPER_API UCombatNotifyState_HitSphere : public UCombatNotifyState_HitWindow
{
	GENERATED_BODY()
protected:
	// 3D widget for some reason not working in anim montage editor
	UPROPERTY(EditAnywhere, Category = "GASCombat")
	TArray<FSphere> _hitSpheres;

	UPROPERTY(EditAnywhere, Category = "GASCombat")
	UClass* actorsToHit;

	UPROPERTY(EditAnywhere, Category = "GASCombat")
	FColor _debugColor = FColor::Red;

private:
	TArray<AActor*> GetHitActors(AActor* owner, float frameDeltaSeconds) const override;

	void DebugDrawEditor(const UWorld* world, float frameDeltaSeconds) const override;

	void DebugDrawGame(AActor* owner, float frameDeltaSeconds) const override;
};
