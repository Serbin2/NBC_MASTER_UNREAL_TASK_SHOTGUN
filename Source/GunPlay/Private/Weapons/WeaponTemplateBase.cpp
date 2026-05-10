// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponTemplateBase.h"


void AWeaponTemplateBase::Fire()
{
	if ( !CanFire ) return;
	
	if (CheckAmmo())
	{
		PlayEffect();
		ProcessFiring();
		UpdateAmmo();
		
		Super::Fire();
	}
}

void AWeaponTemplateBase::UpdateAmmo_Implementation()
{
	CurrentAmmo -= AmmoPerFire;
}

bool AWeaponTemplateBase::CheckAmmo_Implementation()
{	
	return AmmoPerFire <= CurrentAmmo;
}

void AWeaponTemplateBase::Reload_Implementation()
{
	CurrentAmmo = MaxAmmo;
}
