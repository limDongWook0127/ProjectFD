// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DT_ItemInfo.h"

int32 FItemInfo_::DPS()
{
	float DPS;
	float APS = AttackSpeed / 60.f; // 초당 발사속도
	float AT = Bullet_Capacity / APS; // 한 탄창 발사 시간

	// 제장전 2초라 가정
	// 총기 데미지 + 장탄수 / 한 탄창 발사시간 + 재장전 시간
	DPS = (Damage * Bullet_Capacity) / AT + 2;

	return DPS;
}
