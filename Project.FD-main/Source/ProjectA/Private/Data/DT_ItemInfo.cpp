// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DT_ItemInfo.h"

int32 FItemInfo_::DPS()
{
	float DPS;
	float APS = AttackSpeed / 60.f; // �ʴ� �߻�ӵ�
	float AT = Bullet_Capacity / APS; // �� źâ �߻� �ð�

	// ������ 2�ʶ� ����
	// �ѱ� ������ + ��ź�� / �� źâ �߻�ð� + ������ �ð�
	DPS = (Damage * Bullet_Capacity) / AT + 2;

	return DPS;
}
