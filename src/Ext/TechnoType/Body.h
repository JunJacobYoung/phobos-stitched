#pragma once
#include <TechnoTypeClass.h>

#include <Helpers/Macro.h>
#include <Utilities/Container.h>
#include <Utilities/TemplateDef.h>
#include <Utilities/Enum.h>

#include <New/Type/ShieldTypeClass.h>
#include <New/Type/LaserTrailTypeClass.h>
#include <New/Type/AttachmentTypeClass.h>
#include <New/Type/DigitalDisplayTypeClass.h>
#include <New/Type/IonCannonTypeClass.h>
#include <New/Type/GScreenAnimTypeClass.h>
#include <New/Type/AttachEffectTypeClass.h>
#include <New/Type/HealthBarTypeClass.h>

#include <New/AnonymousType/InterceptorTypeClass.h>

class Matrix3D;
class ParticleSystemTypeClass;

class TechnoTypeExt
{
public:
	using base_type = TechnoTypeClass;

	class ExtData final : public Extension<TechnoTypeClass>
	{
	public:
		Valueable<bool> HealthBar_Hide;
		Valueable<CSFText> UIDescription;
		Valueable<bool> LowSelectionPriority;
		PhobosFixedString<0x20> GroupAs;
		Valueable<int> RadarJamRadius;
		Nullable<int> InhibitorRange;
		Nullable<int> DesignatorRange;
		Valueable<Leptons> MindControlRangeLimit;

		Valueable<bool> Interceptor;
		std::unique_ptr<InterceptorTypeClass> InterceptorType;

		Valueable<PartialVector3D<int>> TurretOffset;

		Valueable<bool> Spawner_LimitRange;
		Valueable<int> Spawner_ExtraLimitRange;
		Nullable<int> Spawner_DelayFrames;
		ValueableVector<int> Spawner_DelayFrams_PerSpawn;
		ValueableVector<AircraftTypeClass*> Spawn_Types;
		ValueableVector<int> Spawn_Nums;
		ValueableVector<int> Spawn_RegenRate;
		ValueableVector<int> Spawn_ReloadRate;

		Nullable<bool> Harvester_Counted;
		Valueable<bool> Promote_IncludeSpawns;
		Valueable<bool> ImmuneToCrit;
		Valueable<bool> MultiMindControl_ReleaseVictim;
		Valueable<int> CameoPriority;
		Valueable<bool> NoManualMove;
		Nullable<int> InitialStrength;
		Valueable<int> PassengerDeletion_Rate;
		Valueable<bool> PassengerDeletion_Rate_SizeMultiply;
		Valueable<bool> PassengerDeletion_UseCostAsRate;
		Valueable<double> PassengerDeletion_CostMultiplier;
		Valueable<bool> PassengerDeletion_Soylent;
		Valueable<bool> PassengerDeletion_SoylentFriendlies;
		Valueable<bool> PassengerDeletion_DisplaySoylent;
		Valueable<double> PassengerDeletion_SoylentMultiplier;
		Valueable<AffectedHouse> PassengerDeletion_DisplaySoylentToHouses;
		Valueable<Point2D> PassengerDeletion_DisplaySoylentOffset;
		NullableIdx<VocClass> PassengerDeletion_ReportSound;
		Nullable<AnimTypeClass*> PassengerDeletion_Anim;

		Valueable<bool> AutoDeath_OnAmmoDepletion;
		Valueable<bool> AutoDeath_TechnosDontExist_Any;
		Valueable<bool> AutoDeath_TechnosExist_Any;
		Valueable<int> AutoDeath_AfterDelay;
		Nullable<AutoDeathBehavior> AutoDeath_Behavior;
		ValueableVector<TechnoTypeClass*> AutoDeath_TechnosDontExist;
		Valueable<AffectedHouse> AutoDeath_TechnosDontExist_Houses;
		ValueableVector<TechnoTypeClass*> AutoDeath_TechnosExist;
		Valueable<AffectedHouse> AutoDeath_TechnosExist_Houses;
		Valueable<bool> AutoDeath_OnPassengerDepletion;
		Valueable<int> AutoDeath_OnPassengerDepletion_Delay;

		Valueable<SlaveChangeOwnerType> Slaved_OwnerWhenMasterKilled;
		NullableIdx<VocClass> SellSound;
		NullableIdx<VoxClass> EVA_Sold;

		Valueable<ShieldTypeClass*> ShieldType;

		ValueableVector<AnimTypeClass*> WarpOut;
		ValueableVector<AnimTypeClass*> WarpIn;
		ValueableVector<AnimTypeClass*> WarpAway;
		Nullable<bool> ChronoTrigger;
		Nullable<int> ChronoDistanceFactor;
		Nullable<int> ChronoMinimumDelay;
		Nullable<int> ChronoRangeMinimum;
		Nullable<int> ChronoDelay;

		Nullable<WeaponTypeClass*> WarpInWeapon;
		Nullable<WeaponTypeClass*> WarpInMinRangeWeapon;
		Nullable<WeaponTypeClass*> WarpOutWeapon;
		Valueable<bool> WarpInWeapon_UseDistanceAsDamage;

		ValueableVector<AnimTypeClass*> OreGathering_Anims;
		ValueableVector<int> OreGathering_Tiberiums;
		ValueableVector<int> OreGathering_FramesPerDir;

		std::vector<DynamicVectorClass<CoordStruct>> WeaponBurstFLHs;
		std::vector<DynamicVectorClass<CoordStruct>> VeteranWeaponBurstFLHs;
		std::vector<DynamicVectorClass<CoordStruct>> EliteWeaponBurstFLHs;
		std::vector<CoordStruct> AlternateFLHs;

		Valueable<bool> DestroyAnim_Random;
		Valueable<bool> NotHuman_RandomDeathSequence;

		Nullable<InfantryTypeClass*> DefaultDisguise;
		Nullable<UnitTypeClass*> DefaultVehicleDisguise;
		Valueable<bool> UseDisguiseMovementSpeed;

		Nullable<int> OpenTopped_RangeBonus;
		Nullable<float> OpenTopped_DamageMultiplier;
		Nullable<int> OpenTopped_WarpDistance;
		Valueable<bool> OpenTopped_IgnoreRangefinding;
		Valueable<bool> OpenTopped_AllowFiringIfDeactivated;

		Nullable<bool> AllowPlanningMode;

		ValueableIdxVector<SuperWeaponTypeClass> SuperWeapon_Quick;

		struct AttachmentDataEntry
		{
			AttachmentTypeClass* Type;
			TechnoTypeClass* TechnoType;
			CoordStruct FLH;
			bool IsOnTurret;

			AttachmentDataEntry() = default;

			AttachmentDataEntry(AttachmentTypeClass* pAttachmentType, TechnoTypeClass* pTechnoType, CoordStruct crdFLH, bool isOnTurret)
				:Type(pAttachmentType), TechnoType(pTechnoType), FLH(crdFLH), IsOnTurret(isOnTurret)
			{ }

			~AttachmentDataEntry() = default;

			bool Load(PhobosStreamReader& stm, bool registerForChange);
			bool Save(PhobosStreamWriter& stm) const;

		private:
			template <typename T>
			bool Serialize(T& stm);
		};

		std::vector<std::unique_ptr<AttachmentDataEntry>> AttachmentData;

		Valueable<bool> AutoFire;
		Valueable<bool> AutoFire_TargetSelf;

		Valueable<bool> NoSecondaryWeaponFallback;

		Valueable<int> NoAmmoWeapon;
		Valueable<int> NoAmmoAmount;

		Nullable<bool> JumpjetAllowLayerDeviation;
		Nullable<bool> JumpjetTurnToTarget;

		Valueable<bool> DeployingAnim_AllowAnyDirection;
		Valueable<bool> DeployingAnim_KeepUnitVisible;
		Valueable<bool> DeployingAnim_ReverseForUndeploy;
		Valueable<bool> DeployingAnim_UseUnitDrawer;

		Valueable<CSFText> EnemyUIName;

		Valueable<int> ForceWeapon_Naval_Decloaked;
		Valueable<int> ForceWeapon_Cloaked;
		Valueable<int> ForceWeapon_Disguised;
		Valueable<int> ForceWeapon_UnderEMP;

		Valueable<bool> Ammo_Shared;
		Valueable<int> Ammo_Shared_Group;

		Valueable<bool> Passengers_ChangeOwnerWithTransport;

		Nullable<SelfHealGainType> SelfHealGainType;
		Valueable<bool> Passengers_SyncOwner;
		Valueable<bool> Passengers_SyncOwner_RevertOnExit;

		Promotable<SHPStruct*> Insignia;
		Valueable<Vector3D<int>> InsigniaFrames;
		Promotable<int> InsigniaFrame;
		Nullable<bool> Insignia_ShowEnemy;

		Valueable<bool> Explodes_KillPassengers;

		struct LaserTrailDataEntry
		{
			ValueableIdx<LaserTrailTypeClass> Type;
			Valueable<CoordStruct> FLH;
			Valueable<bool> IsOnTurret;

			bool Load(PhobosStreamReader& stm, bool registerForChange);
			bool Save(PhobosStreamWriter& stm) const;

		private:
			template <typename T>
			bool Serialize(T& stm);
		};

		ValueableVector<LaserTrailDataEntry> LaserTrailData;

		struct GiftBoxDataEntry
		{
			ValueableVector<TechnoTypeClass*> Types;
			ValueableVector<int> Nums;
			Valueable<bool> Remove;
			Valueable<bool> Destroy;
			Valueable<int> Delay;
			Valueable<Point2D> DelayMinMax;
			Valueable<int> CellRandomRange;
			Valueable<bool> EmptyCell;
			Valueable<bool> RandomType;
			Valueable<bool> ApplyOnce;

			GiftBoxDataEntry()
				: Types {}
				, Nums {}
				, Remove { true }
				, Destroy { false }
				, Delay { 0 }
				, DelayMinMax { { 0, 0 } }
				, CellRandomRange { 0 }
				, EmptyCell { false }
				, RandomType { true }
				, ApplyOnce { false }
			{ }

			operator bool() const
			{
				return !Types.empty() && !Nums.empty();
			}

			bool Load(PhobosStreamReader& stm, bool registerForChange);
			bool Save(PhobosStreamWriter& stm) const;

		private:
			template <typename T>
			bool Serialize(T& stm);
		};

		GiftBoxDataEntry GiftBoxData;

		Nullable<SHPStruct*> SelectBox_Shape;
		CustomPalette SelectBox_Palette;
		Valueable<Vector3D<int>> SelectBox_Frame;
		Nullable<Vector2D<int>> SelectBox_DrawOffset;
		Nullable<int> SelectBox_TranslucentLevel;
		Nullable<AffectedHouse> SelectBox_CanSee;
		Nullable<bool> SelectBox_CanObserverSee;

		Valueable<bool> CanRepairCyborgLegs;

		Nullable<CoordStruct> PronePrimaryFireFLH;
		Nullable<CoordStruct> ProneSecondaryFireFLH;
		Nullable<CoordStruct> DeployedPrimaryFireFLH;
		Nullable<CoordStruct> DeployedSecondaryFireFLH;
		std::vector<DynamicVectorClass<CoordStruct>> CrouchedWeaponBurstFLHs;
		std::vector<DynamicVectorClass<CoordStruct>> VeteranCrouchedWeaponBurstFLHs;
		std::vector<DynamicVectorClass<CoordStruct>> EliteCrouchedWeaponBurstFLHs;
		std::vector<DynamicVectorClass<CoordStruct>> DeployedWeaponBurstFLHs;
		std::vector<DynamicVectorClass<CoordStruct>> VeteranDeployedWeaponBurstFLHs;
		std::vector<DynamicVectorClass<CoordStruct>> EliteDeployedWeaponBurstFLHs;

		Valueable<bool> MobileRefinery;
		Valueable<int> MobileRefinery_TransRate;
		Valueable<float> MobileRefinery_CashMultiplier;
		Valueable<int> MobileRefinery_AmountPerCell;
		ValueableVector<double> MobileRefinery_FrontOffset;
		ValueableVector<double> MobileRefinery_LeftOffset;
		Valueable<bool> MobileRefinery_Display;
		Valueable<ColorStruct> MobileRefinery_DisplayColor;
		ValueableVector<AnimTypeClass*> MobileRefinery_Anims;
		Valueable<bool> MobileRefinery_AnimMove;

		NullableVector<int> Overload_Count;
		NullableVector<int> Overload_Damage;
		NullableVector<int> Overload_Frames;
		NullableIdx<VocClass> Overload_DeathSound;
		Nullable<ParticleSystemTypeClass*> Overload_ParticleSys;
		Nullable<int> Overload_ParticleSysCount;
		Valueable<bool> Draw_MindControlLink;

		ValueableVector<DigitalDisplayTypeClass*> DigitalDisplayTypes;
		Valueable<bool> DigitalDisplay_Disable;

		ValueableVector<TechnoTypeClass*> RandomProduct;

		ValueableIdxVector<SuperWeaponTypeClass> KickOutSW_Types;
		Valueable<bool> KickOutSW_Random;
		Valueable<Vector2D<int>> KickOutSW_Offset;

		Valueable<bool> SkipOpenDoor;
		Valueable<Vector2D<int>> SkipOpenDoor_Offset;
		Nullable<AnimTypeClass*> SkipOpenDoor_Anim;

		Valueable<bool> HugeBar;
		Valueable<int> HugeBar_Priority;

		DamageableVector<WeaponTypeClass*> FireSelf_Weapon;
		DamageableVector<int> FireSelf_ROF;
		Damageable<bool> FireSelf_Immediately;

		Nullable<IonCannonTypeClass*> IonCannonType;

		Nullable<GScreenAnimTypeClass*> GScreenAnimType;

		Valueable<bool> MovePassengerToSpawn;
		Valueable<bool> SilentPassenger;
		Valueable<bool> Spawner_SameLoseTarget;

		Valueable<bool> DeterminedByRange;
		Valueable<int> DeterminedByRange_ExtraRange;
		Valueable<int> DeterminedByRange_MainWeapon;

		ValueableVector<TechnoTypeClass*> BuildLimit_Group_Types;
		Valueable<bool> BuildLimit_Group_Any;
		ValueableVector<int> BuildLimit_Group_Limits;

		ValueableVector<TechnoTypeClass*> BuildLimit_As;

		Valueable<bool> VehicleImmuneToMindControl;

		TechnoTypeClass* Convert_Deploy;
		Valueable<AnimTypeClass*> Convert_DeployAnim;

		TechnoTypeClass* Convert_Script;
		TechnoTypeClass* Convert_Water;
		TechnoTypeClass* Convert_Land;
		TechnoTypeClass* Promote_VeteranType;
		TechnoTypeClass* Promote_EliteType;

		Valueable<bool> EMPulseCannon;

		Valueable<bool> Gattling_SelectWeaponByVersus;
		Valueable<bool> IsExtendGattling;
		Valueable<bool> Gattling_Cycle;
		Valueable<bool> Gattling_Charge;

		PromotableVector<WeaponStruct> Weapons;

		std::vector<DynamicVectorClass<int>> Stages;
		std::vector<DynamicVectorClass<int>> VeteranStages;
		std::vector<DynamicVectorClass<int>> EliteStages;
		std::vector<DynamicVectorClass<CoordStruct>> WeaponFLHs;
		std::vector<DynamicVectorClass<CoordStruct>> VeteranWeaponFLHs;
		std::vector<DynamicVectorClass<CoordStruct>> EliteWeaponFLHs;

		Promotable<WeaponStruct> OccupyWeapons;

		Valueable<UnitTypeClass*> JJConvert_Unload;

		TechnoTypeClass* Convert_AI;
		TechnoTypeClass* Convert_Player;
		TechnoTypeClass* Convert_Netural;
		TechnoTypeClass* Convert_Stand;
		TechnoTypeClass* Convert_Move;

		Promotable<int> CrushLevel;
		Promotable<int> CrushableLevel;
		Promotable<int> DeployCrushableLevel;

		Nullable<bool> IronCurtain_KeptOnDeploy;
		Nullable<IronCurtainEffect> IronCurtain_Effect;
		Nullable<WarheadTypeClass*> IronCuratin_KillWarhead;

		ValueableVector<WeaponTypeClass*> AttackedWeapon;
		ValueableVector<WeaponTypeClass*> AttackedWeapon_Veteran;
		ValueableVector<WeaponTypeClass*> AttackedWeapon_Elite;
		ValueableVector<int> AttackedWeapon_ROF;
		ValueableVector<bool> AttackedWeapon_FireToAttacker;
		ValueableVector<bool> AttackedWeapon_IgnoreROF;
		ValueableVector<bool> AttackedWeapon_IgnoreRange;
		ValueableVector<Leptons> AttackedWeapon_Range;
		ValueableVector<WarheadTypeClass*> AttackedWeapon_ResponseWarhead;
		ValueableVector<WarheadTypeClass*> AttackedWeapon_NoResponseWarhead;
		ValueableVector<bool> AttackedWeapon_ResponseZeroDamage;
		std::vector<AffectedHouse> AttackedWeapon_ResponseHouse;
		ValueableVector<int> AttackedWeapon_ActiveMaxHealth;
		ValueableVector<int> AttackedWeapon_ActiveMinHealth;
		std::vector<CoordStruct> AttackedWeapon_FLHs;

		Promotable<WeaponStruct> WeaponInTransport;

		Valueable<bool> UseNewWeapon;
		Valueable<int> NewWeapon_FireIndex;
		Promotable<WeaponStruct> NewDeployWeapon;
		Promotable<WeaponStruct> NewWeapon_Infantry;
		Promotable<WeaponStruct> NewWeapon_Infantry_AIR;
		Promotable<WeaponStruct> NewWeapon_Unit;
		Promotable<WeaponStruct> NewWeapon_Unit_AIR;
		Promotable<WeaponStruct> NewWeapon_Aircraft;
		Promotable<WeaponStruct> NewWeapon_Aircraft_AIR;
		Promotable<WeaponStruct> NewWeapon_Building;

		Valueable<bool> ProtectPassengers;
		Valueable<bool> ProtectPassengers_Clear;
		Valueable<bool> ProtectPassengers_Release;
		Valueable<bool> ProtectPassengers_Damage;

		Valueable<AffectedHouse> Dodge_Houses;
		Valueable<double> Dodge_MaxHealthPercent;
		Valueable<double> Dodge_MinHealthPercent;
		Valueable<double> Dodge_Chance;
		Nullable<AnimTypeClass*> Dodge_Anim;
		Valueable<bool> Dodge_OnlyDodgePositiveDamage;

		Valueable<int> MoveDamage;
		Valueable<int> MoveDamage_Delay;
		Nullable<WarheadTypeClass*> MoveDamage_Warhead;
		Nullable<AnimTypeClass*> MoveDamage_Anim;
		Valueable<int> StopDamage;
		Valueable<int> StopDamage_Delay;
		Nullable<WarheadTypeClass*> StopDamage_Warhead;
		Valueable<AnimTypeClass*> StopDamage_Anim;

		ValueableVector<TechnoTypeClass*> WeaponRangeShare_Technos;
		Valueable<double> WeaponRangeShare_Range;
		Valueable<bool> WeaponRangeShare_ForceAttack;
		Valueable<int> WeaponRangeShare_UseWeapon;

		Valueable<int> AllowMinHealth;

		Valueable<Vector2D<int>> AllowMaxDamage;
		Valueable<Vector2D<int>> AllowMinDamage;

		Valueable<bool> ImmuneToAbsorb;

		ValueableVector<AttachEffectTypeClass*> AttachEffects;
		ValueableVector<AttachEffectTypeClass*> AttachEffects_Immune;
		NullableVector<AttachEffectTypeClass*> AttachEffects_OnlyAccept;

		ValueableVector<AttachEffectTypeClass*> DeployAttachEffects;
		Valueable<int> DeployAttachEffects_Delay;

		Valueable<bool> TeamAffect;
		Valueable<double> TeamAffect_Range;
		ValueableVector<TechnoTypeClass*> TeamAffect_Technos;
		Valueable<AffectedHouse> TeamAffect_Houses;
		Valueable<AffectedTarget> TeamAffect_Targets;
		Valueable<int> TeamAffect_Number;
		Valueable<WeaponTypeClass*> TeamAffect_Weapon;
		Nullable<int> TeamAffect_ROF;
		Valueable<WeaponTypeClass*> TeamAffect_LoseEfficacyWeapon;
		Nullable<int> TeamAffect_LoseEfficacyROF;
		Nullable<AnimTypeClass*> TeamAffect_Anim;
		Valueable<bool> TeamAffect_ShareDamage;
		Valueable<double> TeamAffect_ShareDamagePercent;
		Valueable<int> TeamAffect_MaxNumber;

		ValueableVector<TechnoTypeClass*> PoweredUnitBy;
		Valueable<bool> PoweredUnitBy_Any;
		Nullable<AnimTypeClass*> PoweredUnitBy_Sparkles;
		Nullable<ParticleSystemTypeClass*> PoweredUnitBy_ParticleSystem;
		Valueable<Vector2D<int>> PoweredUnitBy_ParticleSystemXOffset;
		Valueable<Vector2D<int>> PoweredUnitBy_ParticleSystemYOffset;
		Valueable<int> PoweredUnitBy_ParticleSystemSpawnDelay;

		Valueable<int> Power;
		Valueable<bool> Powered;

		Valueable<bool> Locomotor_Change;
		Valueable<Locomotors> Locomotor_ChangeTo;
		Valueable<int> Locomotor_ChangeMinRange;
		Valueable<int> Locomotor_ChangeMaxRange;

		Valueable<int> PassengerHeal_Rate;
		Valueable<bool> PassengerHeal_HealAll;
		Valueable<int> PassengerHeal_Amount;
		Valueable<AffectedHouse> PassengerHeal_Houses;
		NullableIdx<VocClass> PassengerHeal_Sound;
		Nullable<AnimTypeClass*> PassengerHeal_Anim;

		std::unordered_map<size_t, int> Temperature;
		std::unordered_map<size_t, int> Temperatrue_Disable;
		std::unordered_map<size_t, int> Temperature_HeatUpFrame;
		std::unordered_map<size_t, int> Temperature_HeatUpAmount;
		std::unordered_map<size_t, int> Temperature_HeatUpDelay;

		std::vector<DynamicVectorClass<int>> Turrets;

		Valueable<bool> UseConvert;
		ValueableIdxVector<TechnoTypeClass> Convert_Passengers;
		ValueableIdxVector<TechnoTypeClass> Convert_Types;

		Nullable<AnimTypeClass*> VeteranAnim;
		Nullable<AnimTypeClass*> EliteAnim;

		Valueable<bool> IsExtendAcademy;
		Valueable<bool> Academy_Immediately;
		Valueable<bool> Academy_Immediately_Addition;
		Valueable<bool> Academy_Powered;
		Valueable<double> Academy_InfantryVeterancy;
		Valueable<double> Academy_VehicleVeterancy;
		Valueable<double> Academy_NavalVeterancy;
		Valueable<double> Academy_AircraftVeterancy;
		Valueable<double> Academy_BuildingVeterancy;
		ValueableVector<TechnoTypeClass*> Academy_InfantryVeterancy_Types;
		ValueableVector<TechnoTypeClass*> Academy_VehicleVeterancy_Types;
		ValueableVector<TechnoTypeClass*> Academy_NavalVeterancy_Types;
		ValueableVector<TechnoTypeClass*> Academy_AircraftVeterancy_Types;
		ValueableVector<TechnoTypeClass*> Academy_BuildingVeterancy_Types;
		ValueableVector<TechnoTypeClass*> Academy_InfantryVeterancy_Ignore;
		ValueableVector<TechnoTypeClass*> Academy_VehicleVeterancy_Ignore;
		ValueableVector<TechnoTypeClass*> Academy_NavalVeterancy_Ignore;
		ValueableVector<TechnoTypeClass*> Academy_AircraftVeterancy_Ignore;
		ValueableVector<TechnoTypeClass*> Academy_BuildingVeterancy_Ignore;
		Valueable<bool> Academy_InfantryVeterancy_Cumulative;
		Valueable<bool> Academy_VehicleVeterancy_Cumulative;
		Valueable<bool> Academy_NavalVeterancy_Cumulative;
		Valueable<bool> Academy_AircraftVeterancy_Cumulative;
		Valueable<bool> Academy_BuildingVeterancy_Cumulative;

		Valueable<int> ReturnMoney;
		Valueable<double> ReturnMoney_Percentage;
		Valueable<bool> ReturnMoney_Display;
		Valueable<AffectedHouse> ReturnMoney_Display_Houses;
		Valueable<Point2D> ReturnMoney_Display_Offset;

		Valueable<bool> LimitedAttackRange;

		Valueable<bool> MindControl_SyncDeath;

		Valueable<AnimTypeClass*> LandAnim;

		Valueable<bool> PassengerProduct;
		ValueableVector<TechnoTypeClass*> PassengerProduct_Type;
		Valueable<int> PassengerProduct_Rate;
		Valueable<int> PassengerProduct_Amount;
		Valueable<bool> PassengerProduct_RandomPick;

		Nullable<bool> DirectionalArmor;
		Nullable<float> DirectionalArmor_FrontMultiplier;
		Nullable<float> DirectionalArmor_SideMultiplier;
		Nullable<float> DirectionalArmor_BackMultiplier;
		Nullable<float> DirectionalArmor_FrontField;
		Nullable<float> DirectionalArmor_BackField;

		Valueable<float> Experience_VictimMultiple;
		Valueable<float> Experience_KillerMultiple;

		Nullable<AnimTypeClass*> Parachute_Anim;
		Nullable<int> Parachute_OpenHeight;

		Nullable<ParticleSystemTypeClass*> Parasite_ParticleSystem;
		Valueable<bool> Parasite_NoParticleSystem;
		Valueable<bool> Parasite_NoRock;
		ValueableVector<AttachEffectTypeClass*> Parasite_AttachEffects;

		ValueableIdxVector<SuperWeaponTypeClass> DeathSW_Types;

		//Ares
		ValueableVector<TechnoTypeClass*> InitialPayload_Types;
		ValueableVector<int> InitialPayload_Nums;
		ValueableVector<BuildingTypeClass*> BuiltAt;
		Nullable<int> TurretROT;
		Valueable<bool> Passengers_BySize;
		Nullable<bool> ImmuneToEMP;

		/*
		EatPassengers
		MovePassengerToSpawn
		IonCannon
		AutoDeath
		AttackedWeapon
		PoweredShield
		PassengerHeal
		*/
		bool Subset_1_Used() const;

		/*
		EatPassengers
		MovePassengerToSpawn
		IonCannon
		AutoDeath
		AttackedWeapon
		PoweredShield
		PassengerHeal
		*/
		bool Subset_1 = false;

		/*
		SilentPassenger
		Spawner_SameLoseTarget
		Spawn_LimitRange
		MindControlRange
		MobileRefinery
		*/
		bool Subset_2_Used() const;
		/*
		SilentPassenger
		Spawner_SameLoseTarget
		Spawn_LimitRange
		MindControlRange
		MobileRefinery
		*/
		bool Subset_2 = false;

		/*
		ExtendGattling
		FireSelf
		TeamAffect
		PoweredUnit
		PassengerProduct
		*/
		bool Subset_3_Used() const;
		/*
		ExtendGattling
		FireSelf
		TeamAffect
		PoweredUnit
		PassengerProduct
		*/
		bool Subset_3 = false;

		bool CanBeBuiltAt_Ares(BuildingTypeClass* pFactoryType);

		Valueable<bool> BaseNormal;
		Valueable<bool> EligibileForAllyBuilding;

		Nullable<int> DrainMoneyFrameDelay;
		Nullable<int> DrainMoneyAmount;
		Nullable<AnimTypeClass*> DrainAnimationType;
		Valueable<bool> DrainMoney_Display;
		Valueable<AffectedHouse> DrainMoney_Display_Houses;
		Valueable<bool> DrainMoney_Display_AtFirer;
		Valueable<Point2D> DrainMoney_Display_Offset;

		NullableVector<AnimTypeClass*> OnFire;

		Nullable<WeaponTypeClass*> Line_Attack_Weapon;
		Nullable<WeaponTypeClass*> Line_Move_Weapon;
		Valueable<bool> Line_Attack_Dashed;
		Valueable<bool> Line_Move_Dashed;
		Valueable<ColorStruct> Line_Attack_Color;
		Valueable<ColorStruct> Line_Move_Color;

		Nullable<bool> ClickCameoToFocus;

		Valueable<float> HarvesterDumpAmount;

		Nullable<HealthBarTypeClass*> HealthBarType;
		Nullable<HealthBarTypeClass*> ShieldBarType;

		Nullable<WeaponTypeClass*> RevengeWeapon;
		Valueable<AffectedHouse> RevengeWeapon_AffectsHouses;

		Valueable<int> FallRate_NoParachute;
		Nullable<int> FallRate_NoParachuteMax;

		Valueable<double> AttackIndicator_Range;

		ExtData(TechnoTypeClass* OwnerObject) : Extension<TechnoTypeClass>(OwnerObject)
			, HealthBar_Hide { false }
			, UIDescription {}
			, LowSelectionPriority { false }
			, GroupAs { NONE_STR }
			, RadarJamRadius { 0 }
			, InhibitorRange { }
			, DesignatorRange { }
			, MindControlRangeLimit {}

			, Interceptor { false }
			, InterceptorType {}

			, TurretOffset { { 0, 0, 0 } }

			, Spawner_LimitRange { false }
			, Spawner_ExtraLimitRange { 0 }
			, Spawner_DelayFrames {}
			, Spawner_DelayFrams_PerSpawn {}
			, Spawn_Types {}
			, Spawn_Nums {}
			, Spawn_RegenRate {}
			, Spawn_ReloadRate {}

			, Harvester_Counted {}
			, Promote_IncludeSpawns { false }
			, ImmuneToCrit { false }
			, MultiMindControl_ReleaseVictim { false }
			, CameoPriority { 0 }
			, NoManualMove { false }
			, InitialStrength {}

			, ShieldType {}

			, WarpOut {}
			, WarpIn {}
			, WarpAway {}
			, ChronoTrigger {}
			, ChronoDistanceFactor {}
			, ChronoMinimumDelay {}
			, ChronoRangeMinimum {}
			, ChronoDelay {}
			, WarpInWeapon {}
			, WarpInMinRangeWeapon {}
			, WarpOutWeapon {}
			, WarpInWeapon_UseDistanceAsDamage { false }

			, OreGathering_Anims {}
			, OreGathering_Tiberiums {}
			, OreGathering_FramesPerDir {}

			, LaserTrailData {}
			, DestroyAnim_Random { true }
			, NotHuman_RandomDeathSequence { false }
			, GiftBoxData {}

			, PassengerDeletion_Rate { 0 }
			, PassengerDeletion_Rate_SizeMultiply { true }
			, PassengerDeletion_UseCostAsRate { false }
			, PassengerDeletion_CostMultiplier { 1.0 }
			, PassengerDeletion_Soylent { false }
			, PassengerDeletion_SoylentMultiplier { 1.0 }
			, PassengerDeletion_SoylentFriendlies { false }
			, PassengerDeletion_DisplaySoylent { false }
			, PassengerDeletion_DisplaySoylentToHouses { AffectedHouse::All }
			, PassengerDeletion_DisplaySoylentOffset { { 0, 0 } }
			, PassengerDeletion_ReportSound {}
			, PassengerDeletion_Anim {}

			, DefaultDisguise {}
			, DefaultVehicleDisguise {}
			, UseDisguiseMovementSpeed {}

			, OpenTopped_RangeBonus {}
			, OpenTopped_DamageMultiplier {}
			, OpenTopped_WarpDistance {}
			, OpenTopped_IgnoreRangefinding { false }
			, OpenTopped_AllowFiringIfDeactivated { true }

			, AllowPlanningMode { }

			, AttachmentData {}
			, AutoFire { false }
			, AutoFire_TargetSelf { false }
			, NoSecondaryWeaponFallback { false }
			, NoAmmoWeapon { -1 }
			, NoAmmoAmount { 0 }
			, JumpjetAllowLayerDeviation {}
			, JumpjetTurnToTarget {}
			, DeployingAnim_AllowAnyDirection { false }
			, DeployingAnim_KeepUnitVisible { false }
			, DeployingAnim_ReverseForUndeploy { true }
			, DeployingAnim_UseUnitDrawer { true }

			, AutoDeath_Behavior { }
			, AutoDeath_OnAmmoDepletion { false }
			, AutoDeath_AfterDelay { 0 }
			, AutoDeath_TechnosDontExist {}
			, AutoDeath_TechnosDontExist_Any { false }
			, AutoDeath_TechnosDontExist_Houses { AffectedHouse::Owner }
			, AutoDeath_TechnosExist {}
			, AutoDeath_TechnosExist_Any { true }
			, AutoDeath_TechnosExist_Houses { AffectedHouse::Owner }
			, AutoDeath_OnPassengerDepletion { false }
			, AutoDeath_OnPassengerDepletion_Delay { 0 }

			, Slaved_OwnerWhenMasterKilled { SlaveChangeOwnerType::Killer }
			, SellSound { }
			, EVA_Sold { }
			, EnemyUIName {}

			, ForceWeapon_Naval_Decloaked { -1 }
			, ForceWeapon_Cloaked { -1 }
			, ForceWeapon_Disguised { -1 }
			, ForceWeapon_UnderEMP { -1 }

			, Ammo_Shared { false }
			, Ammo_Shared_Group { -1 }
			, Passengers_ChangeOwnerWithTransport { false }

			, SelectBox_Shape {}
			, SelectBox_Palette {}
			, SelectBox_Frame { { -1, -1, -1 } }
			, SelectBox_DrawOffset {}
			, SelectBox_TranslucentLevel {}
			, SelectBox_CanSee {}
			, SelectBox_CanObserverSee {}

			, PronePrimaryFireFLH { }
			, ProneSecondaryFireFLH { }
			, DeployedPrimaryFireFLH { }
			, DeployedSecondaryFireFLH { }
			, CanRepairCyborgLegs { false }
			, Draw_MindControlLink { true }
			, Overload_Count {}
			, Overload_Damage {}
			, Overload_Frames {}
			, Overload_DeathSound {}
			, Overload_ParticleSys {}
			, Overload_ParticleSysCount {}
			, SelfHealGainType {}
			, Passengers_SyncOwner { false }
			, Passengers_SyncOwner_RevertOnExit { true }
			, Insignia {}
			, InsigniaFrame { -1 }
			, InsigniaFrames { { -1, -1, -1 } }
			, Insignia_ShowEnemy {}

			, MobileRefinery { false }
			, MobileRefinery_TransRate { 30 }
			, MobileRefinery_CashMultiplier { 1.0 }
			, MobileRefinery_AmountPerCell { 0 }
			, MobileRefinery_FrontOffset { }
			, MobileRefinery_LeftOffset { }
			, MobileRefinery_Display { true }
			, MobileRefinery_DisplayColor { { 57,197,187 } }
			, MobileRefinery_Anims { }
			, MobileRefinery_AnimMove { true }

			, DigitalDisplayTypes {}
			, DigitalDisplay_Disable { false }
			, HugeBar { false }
			, HugeBar_Priority { -1 }

			, KickOutSW_Types { }
			, KickOutSW_Random { false }
			, KickOutSW_Offset { { 0, 0 } }

			, SkipOpenDoor { false }
			, SkipOpenDoor_Offset { { 0, 0 } }
			, SkipOpenDoor_Anim { }

			, IonCannonType {}
			, FireSelf_Weapon {}
			, FireSelf_ROF {}
			, FireSelf_Immediately { false }

			, GScreenAnimType {}
			, MovePassengerToSpawn { false }
			, SilentPassenger { false }
			, Spawner_SameLoseTarget { false }
			, DeterminedByRange { false }
			, DeterminedByRange_ExtraRange { 0 }
			, DeterminedByRange_MainWeapon { -1 }
			, BuildLimit_Group_Types {}
			, BuildLimit_Group_Any { false }
			, BuildLimit_Group_Limits {}
			, VehicleImmuneToMindControl { false }
			, Convert_Deploy {}
			, Convert_DeployAnim {}
			, Convert_Script {}
			, Convert_Water {}
			, Convert_Land {}
			, Promote_VeteranType {}
			, Promote_EliteType {}
			, Gattling_SelectWeaponByVersus { false }
			, IsExtendGattling { false }
			, Gattling_Cycle { false }
			, Gattling_Charge { false }
			, Weapons(ValueableVector<WeaponStruct>(2))
			, Stages {}
			, VeteranStages {}
			, EliteStages {}

			, EMPulseCannon { false }

			, WeaponFLHs {}
			, VeteranWeaponFLHs {}
			, EliteWeaponFLHs {}
			, AlternateFLHs {}

			, OccupyWeapons {}
			, JJConvert_Unload {}

			, Convert_AI {}
			, Convert_Player {}
			, Convert_Netural {}
			, Convert_Stand {}
			, Convert_Move {}

			, CrushLevel {}
			, CrushableLevel {}
			, DeployCrushableLevel {}

			, IronCurtain_KeptOnDeploy {}
			, IronCurtain_Effect {}
			, IronCuratin_KillWarhead {}

			, BuildLimit_As {}

			, AttackedWeapon {}
			, AttackedWeapon_FireToAttacker {}
			, AttackedWeapon_ROF {}
			, AttackedWeapon_IgnoreROF {}
			, AttackedWeapon_IgnoreRange {}
			, AttackedWeapon_Range {}
			, AttackedWeapon_ResponseWarhead {}
			, AttackedWeapon_NoResponseWarhead {}
			, AttackedWeapon_ResponseZeroDamage {}
			, AttackedWeapon_ResponseHouse {}
			, AttackedWeapon_ActiveMaxHealth {}
			, AttackedWeapon_ActiveMinHealth {}
			, AttackedWeapon_FLHs {}

			, WeaponInTransport {}

			, UseNewWeapon { false }
			, NewWeapon_FireIndex { 1 }
			, NewDeployWeapon { nullptr }
			, NewWeapon_Infantry { nullptr }
			, NewWeapon_Infantry_AIR { nullptr }
			, NewWeapon_Unit { nullptr }
			, NewWeapon_Unit_AIR { nullptr }
			, NewWeapon_Aircraft { nullptr }
			, NewWeapon_Aircraft_AIR { nullptr }
			, NewWeapon_Building { nullptr }

			, ProtectPassengers { false }
			, ProtectPassengers_Clear { false }
			, ProtectPassengers_Release { false }
			, ProtectPassengers_Damage { false }

			, Dodge_Houses { AffectedHouse::All }
			, Dodge_MaxHealthPercent { 1.0 }
			, Dodge_MinHealthPercent { 0.0 }
			, Dodge_Chance { 0.0 }
			, Dodge_Anim {}
			, Dodge_OnlyDodgePositiveDamage { true }

			, MoveDamage { 0 }
			, MoveDamage_Delay { 0 }
			, MoveDamage_Warhead {}
			, MoveDamage_Anim {}
			, StopDamage { 0 }
			, StopDamage_Delay { 0 }
			, StopDamage_Warhead {}
			, StopDamage_Anim {}

			, WeaponRangeShare_Technos {}
			, WeaponRangeShare_Range { 0.0 }
			, WeaponRangeShare_ForceAttack { false }
			, WeaponRangeShare_UseWeapon { 0 }

			, AllowMinHealth { 0 }
			, Turrets {}
			, AllowMaxDamage { { INT_MAX, -INT_MAX } }
			, AllowMinDamage { { -INT_MAX, INT_MAX } }
			, ImmuneToAbsorb { false }

			, TeamAffect { false }
			, TeamAffect_Range { 0.0 }
			, TeamAffect_Technos {}
			, TeamAffect_Houses { AffectedHouse::Owner }
			, TeamAffect_Targets { AffectedTarget::AllTechnos }
			, TeamAffect_Number { 0 }
			, TeamAffect_Weapon {}
			, TeamAffect_ROF {}
			, TeamAffect_LoseEfficacyWeapon {}
			, TeamAffect_LoseEfficacyROF {}
			, TeamAffect_Anim {}
			, TeamAffect_ShareDamage { false }
			, TeamAffect_ShareDamagePercent { -1.0 }
			, TeamAffect_MaxNumber { 0 }

			, AttachEffects {}
			, AttachEffects_Immune {}
			, AttachEffects_OnlyAccept {}

			, DeployAttachEffects {}
			, DeployAttachEffects_Delay { -1 }

			, PoweredUnitBy {}
			, PoweredUnitBy_Any { true }
			, PoweredUnitBy_Sparkles {}
			, PoweredUnitBy_ParticleSystem {}
			, PoweredUnitBy_ParticleSystemXOffset { { -128, 128 } }
			, PoweredUnitBy_ParticleSystemYOffset { { -128, 128 } }
			, PoweredUnitBy_ParticleSystemSpawnDelay { 30 }

			, Power { 0 }
			, Powered { false }

			, Locomotor_Change { false }
			, Locomotor_ChangeTo {}
			, Locomotor_ChangeMinRange { 0 }
			, Locomotor_ChangeMaxRange { INT_MAX }

			, PassengerHeal_Rate { 0 }
			, PassengerHeal_HealAll { false }
			, PassengerHeal_Amount { 0 }
			, PassengerHeal_Houses { AffectedHouse::Team }
			, PassengerHeal_Sound {}
			, PassengerHeal_Anim {}

			, Temperature {}
			, Temperature_HeatUpFrame {}
			, Temperature_HeatUpAmount {}
			, Temperature_HeatUpDelay {}
			, Temperatrue_Disable {}

			, PassengerProduct { false }
			, PassengerProduct_Type {}
			, PassengerProduct_Rate { -1 }
			, PassengerProduct_Amount { 1 }
			, PassengerProduct_RandomPick { false }

			, DirectionalArmor {}
			, DirectionalArmor_FrontMultiplier {}
			, DirectionalArmor_SideMultiplier {}
			, DirectionalArmor_BackMultiplier {}
			, DirectionalArmor_FrontField {}
			, DirectionalArmor_BackField {}

			, Experience_VictimMultiple { 1.0 }
			, Experience_KillerMultiple { 1.0 }

			, Parachute_Anim {}
			, Parachute_OpenHeight {}

			, Parasite_ParticleSystem {}
			, Parasite_NoParticleSystem { false }
			, Parasite_NoRock { false }
			, Parasite_AttachEffects {}

			, UseConvert { false }
			, Convert_Passengers {}
			, Convert_Types {}

			, VeteranAnim {}
			, EliteAnim {}

			, IsExtendAcademy { false }
			, Academy_Immediately { false }
			, Academy_Immediately_Addition { false }
			, Academy_Powered { true }
			, Academy_InfantryVeterancy { 0.0 }
			, Academy_VehicleVeterancy { 0.0 }
			, Academy_NavalVeterancy { 0.0 }
			, Academy_AircraftVeterancy { 0.0 }
			, Academy_BuildingVeterancy { 0.0 }
			, Academy_InfantryVeterancy_Types {}
			, Academy_VehicleVeterancy_Types {}
			, Academy_NavalVeterancy_Types {}
			, Academy_AircraftVeterancy_Types {}
			, Academy_BuildingVeterancy_Types {}
			, Academy_InfantryVeterancy_Ignore {}
			, Academy_VehicleVeterancy_Ignore {}
			, Academy_NavalVeterancy_Ignore {}
			, Academy_AircraftVeterancy_Ignore {}
			, Academy_BuildingVeterancy_Ignore {}
			, Academy_InfantryVeterancy_Cumulative { false }
			, Academy_VehicleVeterancy_Cumulative { false }
			, Academy_NavalVeterancy_Cumulative { false }
			, Academy_AircraftVeterancy_Cumulative { false }
			, Academy_BuildingVeterancy_Cumulative { false }

			, ReturnMoney { 0 }
			, ReturnMoney_Percentage { 0.0 }
			, ReturnMoney_Display { false }
			, ReturnMoney_Display_Houses { AffectedHouse::All }
			, ReturnMoney_Display_Offset { { 0, 0 } }

			, LimitedAttackRange { false }

			, MindControl_SyncDeath { false }

			, LandAnim { nullptr }

			, Explodes_KillPassengers{ true }

			, TurretROT {}
			, InitialPayload_Types {}
			, InitialPayload_Nums {}
			, ImmuneToEMP { }

			, SuperWeapon_Quick { }

			, BaseNormal { false }
			, EligibileForAllyBuilding { false }

			, DrainMoneyFrameDelay {}
			, DrainMoneyAmount {}
			, DrainAnimationType {}
			, DrainMoney_Display { false }
			, DrainMoney_Display_Houses { AffectedHouse::All }
			, DrainMoney_Display_AtFirer { true }
			, DrainMoney_Display_Offset { { 0,0 } }

			, OnFire { }

			, Line_Attack_Weapon { }
			, Line_Move_Weapon { }
			, Line_Attack_Dashed { false }
			, Line_Move_Dashed { false }
			, Line_Attack_Color { { 255, 0, 0 } }
			, Line_Move_Color { { 0, 255, 0 } }

			, ClickCameoToFocus { }

			, HarvesterDumpAmount { 0 }

			, HealthBarType {}
			, ShieldBarType {}

			, RevengeWeapon {}
			, RevengeWeapon_AffectsHouses { AffectedHouse::All }

			, FallRate_NoParachute { 1 }
			, FallRate_NoParachuteMax {}

			, AttackIndicator_Range { -1 }

			, DeathSW_Types { }
		{ }

		virtual ~ExtData() = default;
		virtual void LoadFromINIFile(CCINIClass* pINI) override;
		virtual void Initialize() override;

		virtual void InvalidatePointer(void* ptr, bool bRemoved) override { }

		virtual void LoadFromStream(PhobosStreamReader& Stm) override;
		virtual void SaveToStream(PhobosStreamWriter& Stm) override;

		void ApplyTurretOffset(Matrix3D* mtx, double factor = 1.0);
		void ReadWeapons(CCINIClass* const pINI);

		// Ares 0.A
		const char* GetSelectionGroupID() const;

	private:
		template <typename T>
		void Serialize(T& Stm);
	};

	class ExtContainer final : public Container<TechnoTypeExt>
	{
	public:
		ExtContainer();
		~ExtContainer();
	};

	static ExtContainer ExtMap;

	static void ApplyTurretOffset(TechnoTypeClass* pType, Matrix3D* mtx, double factor = 1.0);
	static void GetBurstFLHs(TechnoTypeClass* pThis, INI_EX& exArtINI, const char* pArtSection, std::vector<DynamicVectorClass<CoordStruct>>& nFLH, std::vector<DynamicVectorClass<CoordStruct>>& nVFlh, std::vector<DynamicVectorClass<CoordStruct>>& nEFlh, const char* pPrefixTag);
	static TechnoTypeClass* GetTechnoType(ObjectTypeClass* pType);
	static void GetWeaponStages(TechnoTypeClass* pThis, INI_EX& exINI, const char* pSection, std::vector<DynamicVectorClass<int>>& nStage, std::vector<DynamicVectorClass<int>>& nStageV, std::vector<DynamicVectorClass<int>>& nStageE);
	static void GetWeaponFLHs(TechnoTypeClass* pThis, INI_EX& exArtINI, const char* pArtSection, std::vector<DynamicVectorClass<CoordStruct>>& nFLH, std::vector<DynamicVectorClass<CoordStruct>>& nVFlh, std::vector<DynamicVectorClass<CoordStruct>>& nEFlh);
	static void GetIFVTurrets(TechnoTypeClass* pThis, INI_EX& exINI, const char* pSection, std::vector<DynamicVectorClass<int>>& nturret);
	static std::vector<WeaponTypeClass*> GetAllWeapons(TechnoTypeClass* pThis);

	// Ares 0.A
	static const char* GetSelectionGroupID(ObjectTypeClass* pType);
	static bool HasSelectionGroupID(ObjectTypeClass* pType, const char* pID);
};
