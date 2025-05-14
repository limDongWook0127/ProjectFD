// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGamePlayTags.h"

namespace BaseGamePlayTags
{
	//Input Tags ================================================================================
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Run, "InputTag.Run")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Evade, "InputTag.Evade")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip1, "InputTag.Equip1")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip2, "InputTag.Equip2")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_Axe, "InputTag.LightAttack.Axe")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_HeavyAttack_Axe, "InputTag.HeavyAttack.Axe")

    UE_DEFINE_GAMEPLAY_TAG(InputTag_Reload, "InputTag.Reload")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_ShootBullet, "InputTag.ShootBullet")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_Shouldering, "InputTag.Shouldering")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_ZoomIn, "InputTag.ZoomIn")

    UE_DEFINE_GAMEPLAY_TAG(InputTag_Skill_Sprint, "InputTag.Skill.Sprint")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_Skill_SpawnSparkBall, "InputTag.Skill.SpawnSparkBall")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_Skill_SpawnSparkRing, "InputTag.Skill.SpawnSparkRing")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_Skill_SpawnSparkLaser, "InputTag.Skill.SpawnSparkLaser")
        
    //Player Tags ================================================================================
    UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Axe, "Player.Weapon.Axe")
    UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_AR, "Player.Weapon.AR")
    UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_SCR, "Player.Weapon.SCR")

    UE_DEFINE_GAMEPLAY_TAG(Player_SetBycaller_AttackType_Light, "Player.SetBycaller.AttackType.Light")
    UE_DEFINE_GAMEPLAY_TAG(Player_SetBycaller_AttackType_Heavy, "Player.SetBycaller.AttackType.Heavy")
    UE_DEFINE_GAMEPLAY_TAG(Player_SetBycaller_AttackType_Skill, "Player.SetBycaller.AttackType.Skill")
    UE_DEFINE_GAMEPLAY_TAG(Player_SetBycaller_AttackType_Bullet, "Player.SetBycaller.AttackType.Bullet")

    UE_DEFINE_GAMEPLAY_TAG(Player_SetBycaller_UsingPassive, "Player.SetBycaller.UsingPassive")
    UE_DEFINE_GAMEPLAY_TAG(Player_SetBycaller_GainingShield, "Player.SetBycaller.GainingShield")
    UE_DEFINE_GAMEPLAY_TAG(Player_SetBycaller_UsingMana, "Player.SetBycaller.UsingMana")
    UE_DEFINE_GAMEPLAY_TAG(Player_SetBycaller_GainingHeal, "Player.SetBycaller.GainingHeal")

    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Axe, "Player.Ability.Equip.Axe")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Axe, "Player.Ability.Unequip.Axe")

    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_AR, "Player.Ability.Equip.AR")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_SCR, "Player.Ability.Equip.SCR")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Reload, "Player.Ability.Reload")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Shouldering, "Player.Ability.Shouldering")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_ZoomIn, "Player.Ability.ZoomIn")

    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Axe, "Player.Ability.Attack.Light.Axe")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Axe, "Player.Ability.Attack.Heavy.Axe")

    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Bullet, "Player.Ability.Attack.Bullet")

    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_LandingSkill, "Player.Ability.Attack.LandingSkill")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Skill_SprintSkill, "Player.Ability.Skill.SprintSkill")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_SpawnSparkBallSkill, "Player.Ability.Attack.SpawnSparkBallSkill")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_SpawnSparkRingSkill, "Player.Ability.Attack.SpawnSparkRingSkill")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_SpawnSparkLaserSkill, "Player.Ability.Attack.SpawnSparkLaserSkill")

    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause, "Player.Ability.HitPause")

    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Evade, "Player.Ability.Evade")

    UE_DEFINE_GAMEPLAY_TAG(Player_Event_SkillHit_LandingSpark, "Player.Event.SkillHit.LandingSpark")
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_SkillHit_SparkBall, "Player.Event.SkillHit.SparkBall")
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_SkillHit_SparkLaser, "Player.Event.SkillHit.SparkLaser")
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_SkillHit_SparkRing, "Player.Event.SkillHit.SparkRing")

    UE_DEFINE_GAMEPLAY_TAG(Player_Event_Hit_Bullet, "Player.Event.Hit.Bullet")

    UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_Equip, "Player.Event.Weapon.Equip")
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_UnEquip, "Player.Event.Weapon.UnEquip")
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitPause, "Player.Event.HitPause")

    UE_DEFINE_GAMEPLAY_TAG(Player_Event_GetHealed, "Player.Event.GetHealed")

    UE_DEFINE_GAMEPLAY_TAG(Player_Status_JumpToFinisher, "Player.Status.JumpToFinisher")
    UE_DEFINE_GAMEPLAY_TAG(Player_Status_Evading, "Player.Status.Evading")
    UE_DEFINE_GAMEPLAY_TAG(Player_Status_LosingPassive, "Player.Status.LosingPassive")
    UE_DEFINE_GAMEPLAY_TAG(Player_Status_GainingPassive, "Player.Status.GainingPassive")

    //Cooldown Tags =================================================================================
    UE_DEFINE_GAMEPLAY_TAG(Player_Cooldown_Sprint, "Player.Cooldown.Sprint")
    UE_DEFINE_GAMEPLAY_TAG(Player_Cooldown_SparkBall, "Player.Cooldown.SparkBall")
    UE_DEFINE_GAMEPLAY_TAG(Player_Cooldown_SparkRing, "Player.Cooldown.SparkRing")
    UE_DEFINE_GAMEPLAY_TAG(Player_Cooldown_SparkLaser, "Player.Cooldown.SparkLaser")

    //Enemy Tags ================================================================================
    UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon")
    UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon_Left, "Enemy.Weapon.Left")
    UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon_Right,"Enemy.Weapon.Right")

    UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee")
    UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged, "Enemy.Ability.Ranged")
    UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Reload, "Enemy.Ability.Reload")
    UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Evade, "Enemy.Ability.Evade")

    UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Strafing, "Enemy.Status.Strafing")
    UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Alert, "Enemy.Status.Alert")
    UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnderAttack, "Enemy.Status.UnderAttack")
    UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_MoveAttack, "Enemy.Status.MoveAttack")//12/16 추가
    UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_ShieldDestroy, "Enemy.Status.ShieldDestroy")
    UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_ShieldOpen, "Enemy.Status.ShieldOpen")
   
    

        //Boss Tags==============================================================================
    UE_DEFINE_GAMEPLAY_TAG(Boss_Ability_PhotonCannon, "Boss.Ability.PhotonCannon")
    UE_DEFINE_GAMEPLAY_TAG(Boss_Ability_Promenade, "Boss.Ability.Promenade")
    UE_DEFINE_GAMEPLAY_TAG(Boss_Ability_Teleport, "Boss.Ability.Teleport")
    UE_DEFINE_GAMEPLAY_TAG(Boss_Ability_ElectricDischarging, "Boss.Ability.ElectricDischarging")
    UE_DEFINE_GAMEPLAY_TAG(Boss_Ability_SummonMinions,"Boss.Ability.SummonMinions")
    UE_DEFINE_GAMEPLAY_TAG(Boss_Ability_Berserk, "Boss.Ability.Berserk")
    UE_DEFINE_GAMEPLAY_TAG(Boss_Ability_Stump, "Boss.Ability.Stump")
    

    UE_DEFINE_GAMEPLAY_TAG(Boss_Status_Teleport, "Boss.Status.Teleport")
    UE_DEFINE_GAMEPLAY_TAG(Boss_Status_Idle, "Boss.Status.Idle")
    UE_DEFINE_GAMEPLAY_TAG(Boss_Status_Berserk, "Boss.Status.Berserk")


        UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_SummonEnemies, "Enemy.Ability.SummonEnemies")
        UE_DEFINE_GAMEPLAY_TAG(Enemy_Event_SummonEnemies, "Enemy.Event.SummonEnemies")
    //sharedTags ================================================================================
    UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit")
    UE_DEFINE_GAMEPLAY_TAG(Shared_Event_ProjectileHit, "Shared.Event.ProjectileHit")
    UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetbyCaller.BaseDamage")

    UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact")
    UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact")

    UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death")
    UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Death, "Shared.Status.Death")

    UE_DEFINE_GAMEPLAY_TAG(Shared_Event_SpawnProjectile, "Shared.Event.SpawnProjectile")//12/17추가
        
}
