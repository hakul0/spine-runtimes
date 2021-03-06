/******************************************************************************
 * Spine Runtimes Software License v2.5
 *
 * Copyright (c) 2013-2016, Esoteric Software
 * All rights reserved.
 *
 * You are granted a perpetual, non-exclusive, non-sublicensable, and
 * non-transferable license to use, install, execute, and perform the Spine
 * Runtimes software and derivative works solely for personal or internal
 * use. Without the written permission of Esoteric Software (see Section 2 of
 * the Spine Software License Agreement), you may not (a) modify, translate,
 * adapt, or develop new applications using the Spine Runtimes or otherwise
 * create derivative works or improvements of the Spine Runtimes or (b) remove,
 * delete, alter, or obscure any trademarks or any copyright, trademark, patent,
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS INTERRUPTION, OR LOSS OF
 * USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#pragma once

#include "Components/ActorComponent.h"
#include "SpineSkeletonDataAsset.h"
#include "spine/spine.h"
#include "SpineSkeletonComponent.generated.h"

class USpineSkeletonComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpineBeforeUpdateWorldTransformDelegate, USpineSkeletonComponent*, skeleton);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpineAfterUpdateWorldTransformDelegate, USpineSkeletonComponent*, skeleton);

class USpineAtlasAsset;
UCLASS(ClassGroup=(Spine), meta=(BlueprintSpawnableComponent))
class SPINEPLUGIN_API USpineSkeletonComponent: public UActorComponent {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spine)
	USpineAtlasAsset* Atlas;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spine)
	USpineSkeletonDataAsset* SkeletonData;
	
	spine::Skeleton* GetSkeleton () { return skeleton; };

	UFUNCTION(BlueprintPure, Category = "Components|Spine|Skeleton")
	void GetSkins(TArray<FString> &Skins);
	
	UFUNCTION(BlueprintCallable, Category = "Components|Spine|Skeleton")
	bool SetSkin (const FString SkinName);

	UFUNCTION(BlueprintCallable, Category = "Components|Spine|Skeleton")
	bool HasSkin(const FString SkinName);
	
	UFUNCTION(BlueprintCallable, Category = "Components|Spine|Skeleton")
	bool SetAttachment (const FString slotName, const FString attachmentName);
	
	UFUNCTION(BlueprintCallable, Category = "Components|Spine|Skeleton")
	FTransform GetBoneWorldTransform (const FString& BoneName);
	
	UFUNCTION(BlueprintCallable, Category = "Components|Spine|Skeleton")
	void SetBoneWorldPosition (const FString& BoneName, const FVector& position);

	UFUNCTION(BlueprintCallable, Category = "Components|Spine|Skeleton")
	void UpdateWorldTransform();
	
	UFUNCTION(BlueprintCallable, Category = "Components|Spine|Skeleton")
	void SetToSetupPose ();
	
	UFUNCTION(BlueprintCallable, Category = "Components|Spine|Skeleton")
	void SetBonesToSetupPose ();

	UFUNCTION(BlueprintCallable, Category = "Components|Spine|Skeleton")
	void SetSlotsToSetupPose();

	UFUNCTION(BlueprintCallable, Category = "Components|Spine|Skeleton")
	void SetScaleX(float scaleX);

	UFUNCTION(BlueprintCallable, Category = "Components|Spine|Skeleton")
	float GetScaleX();

	UFUNCTION(BlueprintCallable, Category = "Components|Spine|Skeleton")
	void SetScaleY(float scaleY);

	UFUNCTION(BlueprintCallable, Category = "Components|Spine|Skeleton")
	float GetScaleY();

	UFUNCTION(BlueprintPure, Category = "Components|Spine|Skeleton")
	void GetBones(TArray<FString> &Bones);

	UFUNCTION(BlueprintCallable, Category = "Components|Spine|Skeleton")
	bool HasBone(const FString BoneName);

	UFUNCTION(BlueprintPure, Category = "Components|Spine|Skeleton")
	void GetSlots(TArray<FString> &Slots);

	UFUNCTION(BlueprintCallable, Category = "Components|Spine|Skeleton")
	bool HasSlot(const FString SlotName);

	UFUNCTION(BlueprintPure, Category = "Components|Spine|Skeleton")
	void GetAnimations(TArray<FString> &Animations);

	UFUNCTION(BlueprintCallable, Category = "Components|Spine|Skeleton")
	bool HasAnimation(FString AnimationName);

	UFUNCTION(BlueprintCallable, Category = "Components|Spine|Skeleton")
	float GetAnimationDuration(FString AnimationName);
	
	UPROPERTY(BlueprintAssignable, Category = "Components|Spine|Skeleton")
	FSpineBeforeUpdateWorldTransformDelegate BeforeUpdateWorldTransform;
	
	UPROPERTY(BlueprintAssignable, Category = "Components|Spine|Skeleton")
	FSpineAfterUpdateWorldTransformDelegate AfterUpdateWorldTransform;
		
	USpineSkeletonComponent ();
	
	virtual void BeginPlay () override;
		
	virtual void TickComponent (float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

	virtual void FinishDestroy () override;
	
protected:
	virtual void CheckState ();
	virtual void InternalTick(float DeltaTime, bool CallDelegates = true);
	virtual void DisposeState ();

	spine::Skeleton* skeleton;
	USpineAtlasAsset* lastAtlas = nullptr;
	spine::Atlas* lastSpineAtlas = nullptr;
	USpineSkeletonDataAsset* lastData = nullptr;	
};
