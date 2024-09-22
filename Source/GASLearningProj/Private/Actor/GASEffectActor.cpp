#include "Actor/GASEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/GASAttributeSet.h"
#include "Components/SphereComponent.h"

AGASEffectActor::AGASEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("DefaultMesh");

	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("DefaultSphere");

	Sphere->SetupAttachment(GetRootComponent());
}

void AGASEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{

		auto name = OtherActor->GetName();
		
		//GEngine->AddOnScreenDebugMessage(0,15.0f, FColor::Red, FString::Printf(TEXT("Other Actor's Name is %s"), *name));

		const UGASAttributeSet* GASAttributeSet = Cast<UGASAttributeSet>( ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UGASAttributeSet::StaticClass()));

		UGASAttributeSet* MutableAttributeSet = const_cast<UGASAttributeSet*>(GASAttributeSet);
		
		MutableAttributeSet->SetHealth(GASAttributeSet->GetHealth() + 25.0f);

		Destroy();
	}
}

void AGASEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AGASEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGASEffectActor::OnOverlap);

	Sphere->OnComponentEndOverlap.AddDynamic(this, &AGASEffectActor::OnEndOverlap);
}


